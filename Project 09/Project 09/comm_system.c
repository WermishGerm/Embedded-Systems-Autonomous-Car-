// ============================================================================
// COMM_SYSTEM.C  —  Unified PC <-> ESP32 UART Bridge + Command Parser
// Replaces: IOTTrans.c, command_parser.c, serial.c
// ============================================================================

#include <stdint.h>
#include <string.h>
#include "msp430.h"

#include "functions.h"
#include "macros.h"
#include "ports.h"

// ============================================================================
// GLOBAL BUFFERS
// ============================================================================

// UART ring buffers
volatile char pc_to_iot[128];
volatile char iot_to_pc[128];

volatile uint16_t pc_iot_head = 0;
volatile uint16_t pc_iot_tail = 0;
volatile uint16_t iot_pc_head = 0;
volatile uint16_t iot_pc_tail = 0;

// WiFi RX assembly buffer
char wifi_rx_buffer[256];
uint16_t wifi_rx_index = 0;

// ============================================================================
// UART INITIALIZATION
// ============================================================================

// --------------------------
// USB UART (UCA1)
// --------------------------
void Init_UART_PC(void) {
    UCA1CTLW0 = UCSWRST;              // Reset
    UCA1CTLW0 |= UCSSEL__SMCLK;       // SMCLK

    // Baud 115200 (assuming 8MHz clock)
    UCA1BRW = 4;
    UCA1MCTLW = 0x5551;

    // Pins
    P4SEL1 &= ~(BIT2 | BIT3);
    P4SEL0 |=  (BIT2 | BIT3);

    UCA1CTLW0 &= ~UCSWRST;
    UCA1IE |= UCRXIE;                 // Enable RX interrupt
}

// --------------------------
// ESP32 IOT UART (UCA0)
// --------------------------
void Init_UART_IOT(uint8_t baud_mode) {
    UCA0CTLW0 = UCSWRST;
    UCA0CTLW0 |= UCSSEL__SMCLK;

    if (baud_mode == BAUD_115200) {
        UCA0BRW = 4;
        UCA0MCTLW = 0x5551;
    } else {
        // BAUD_9600
        UCA0BRW = 52;
        UCA0MCTLW = 0x4911;
    }

    // Pins
    P2SEL1 &= ~(BIT0 | BIT1);
    P2SEL0 |=  (BIT0 | BIT1);

    UCA0CTLW0 &= ~UCSWRST;
    UCA0IE |= UCRXIE;
}

// ============================================================================
// UART TX HELPERS
// ============================================================================
void UART_PC_TX(char c) {
    while (!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = c;
}

void UART_IOT_TX(char c) {
    while (!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = c;
}

// ============================================================================
// RING BUFFER HELPERS
// ============================================================================
static void buffer_push(volatile char *buf, volatile uint16_t *head, char c) {
    buf[*head] = c;
    *head = (*head + 1) & 0x7F;  // 128 wrap
}

static char buffer_pop(volatile char *buf, volatile uint16_t *tail) {
    char c = buf[*tail];
    *tail = (*tail + 1) & 0x7F;
    return c;
}

static uint8_t buffer_available(uint16_t head, uint16_t tail) {
    return head != tail;
}

// ============================================================================
// UART BRIDGE PROCESS — CALLED FROM MAIN LOOP
// ============================================================================
void UART_Bridge_Process(void) {
    // -------------------------
    // PC -> IOT
    // -------------------------
    while (buffer_available(pc_iot_head, pc_iot_tail)) {
        char c = buffer_pop(pc_to_iot, &pc_iot_tail);
        UART_IOT_TX(c);
    }

    // -------------------------
    // IOT -> PC
    // -------------------------
    while (buffer_available(iot_pc_head, iot_pc_tail)) {
        char c = buffer_pop(iot_to_pc, &iot_pc_tail);
        UART_PC_TX(c);
    }
}

// ============================================================================
// COMMAND PARSER
// Supports:
//  • Movement commands: F10, B3, L90, R45, S
//  • Secure commands: PIN1234 F5
//  • WiFi +IPD message extraction
// ============================================================================

static const char *SECRET_PIN = "4321";

// ---------------------------------------------------------------
// REMOVE WHITESPACE
// ---------------------------------------------------------------
static void trim(char *s) {
    uint16_t i = 0, j = 0;
    while (s[i] != '\0') {
        if (s[i] != ' ' && s[i] != '\n' && s[i] != '\r' && s[i] != '\t') {
            s[j++] = s[i];
        }
        i++;
    }
    s[j] = '\0';
}

// ---------------------------------------------------------------
// TRUE parser for movement:
// F10, B2, L45, R90, S, X
// ---------------------------------------------------------------
static void command_movement(const char *cmd) {
    char dir = cmd[0];
    uint16_t value = 0;

    if (cmd[1] != '\0')
        value = atoi(&cmd[1]);   // safe because whitespace already trimmed

    movement_execute_command(dir, value);
}

// ---------------------------------------------------------------
// Secure wrapper: PIN4321F2
// ---------------------------------------------------------------
static void command_secure(char *cmd) {
    if (strncmp(cmd, "PIN", 3) != 0) return;

    if (strncmp(cmd + 3, SECRET_PIN, 4) != 0) {
        UART_PC_TX('X'); // bad pin
        return;
    }

    trim(cmd + 7);
    command_movement(cmd + 7);
}

// ---------------------------------------------------------------
// Dispatch final command
// ---------------------------------------------------------------
void command_parser_init(void) {
    wifi_rx_index = 0;
    memset(wifi_rx_buffer, 0, sizeof(wifi_rx_buffer));
}

static void command_dispatch(char *cmd) {
    if (cmd[0] == '\0') return;

    if (!strncmp(cmd, "PIN", 3)) {
        command_secure(cmd);
        return;
    }

    command_movement(cmd);  // direct, insecure
}

// ============================================================================
// WiFi +IPD MESSAGE PARSER
// Example: +IPD,12:F10
// ============================================================================

static void handle_ipd(char *buffer) {
    char *colon = strchr(buffer, ':');
    if (!colon) return;

    colon++;
    trim(colon);

    command_dispatch(colon);
}

// ============================================================================
// UART RECEIVE HANDLING — ISR SUPPORT HELPERS
// (ISRs remain in their own file, per your instructions)
// ============================================================================
void comm_uart_pc_rx(char c) {
    buffer_push(pc_to_iot, &pc_iot_head, c);
}

void comm_uart_iot_rx(char c) {
    buffer_push(iot_to_pc, &iot_pc_head, c);

    // WiFi assembly buffer
    if (wifi_rx_index < sizeof(wifi_rx_buffer)-1) {
        wifi_rx_buffer[wifi_rx_index++] = c;
        wifi_rx_buffer[wifi_rx_index] = '\0';
    }

    // Check for complete +IPD message
    if (strstr(wifi_rx_buffer, "\r\n")) {
        if (strncmp(wifi_rx_buffer, "+IPD", 4) == 0)
            handle_ipd(wifi_rx_buffer);

        wifi_rx_index = 0;
        memset(wifi_rx_buffer, 0, sizeof(wifi_rx_buffer));
    }
}

