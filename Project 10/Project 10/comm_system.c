// ============================================================================
// COMM_SYSTEM.C – PC <-> ESP32 UART Bridge + Command Parser
// ============================================================================

#include <string.h>
#include <stdint.h>
#include "msp430.h"
#include "functions.h"
#include "macros.h"

#define RING_SIZE 128

// ============================================================================
// RING BUFFERS
// ============================================================================
volatile char pc_to_iot[RING_SIZE];
volatile char iot_to_pc[RING_SIZE];

volatile uint16_t pc_iot_head = 0;
volatile uint16_t pc_iot_tail = 0;
volatile uint16_t iot_pc_head = 0;
volatile uint16_t iot_pc_tail = 0;

static char cmd_buffer[32];
static uint8_t cmd_index = 0;

// From functions.h
extern volatile unsigned char run_project7;

// ============================================================================
// INTERNAL HELPERS
// ============================================================================
static inline uint16_t next_index(uint16_t i) {
    return (i + 1) & (RING_SIZE - 1);
}

static inline uint8_t ring_has_data(uint16_t head, uint16_t tail) {
    return head != tail;
}

// ============================================================================
// UART INITIALIZATION
// ============================================================================

// ------------------------
// PC UART (UCA1)
// ------------------------
void Init_UART_PC(void) {

    UCA1CTLW0 = UCSWRST;
    UCA1CTLW0 |= UCSSEL__SMCLK;

    // 115200 baud @ 8MHz
    UCA1BRW = 4;
    UCA1MCTLW = 0x5551;

    // P4.2 = RX, P4.3 = TX
    P4SEL0 |= (BIT2 | BIT3);
    P4SEL1 &= ~(BIT2 | BIT3);

    UCA1CTLW0 &= ~UCSWRST;
    UCA1IE |= UCRXIE;
}

void UART_PC_TX(char c) {
    while (!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = c;
}

// ------------------------
// ESP32 UART (UCA0)
// ------------------------
void Init_UART_IOT(uint8_t baud_mode) {

    UCA0CTLW0 = UCSWRST;
    UCA0CTLW0 |= UCSSEL__SMCLK;

    if (baud_mode == BAUD_115200) {
        UCA0BRW = 4;
        UCA0MCTLW = 0x5551;
    } else {
        UCA0BRW = 52;      // 9600 baud
        UCA0MCTLW = 0x4911;
    }

    // P2.0 = RX, P2.1 = TX
    P2SEL0 |= (BIT0 | BIT1);
    P2SEL1 &= ~(BIT0 | BIT1);

    UCA0CTLW0 &= ~UCSWRST;
    UCA0IE |= UCRXIE;
}

// ============================================================================
// ISR CALL-IN ROUTINES
// ============================================================================
void comm_uart_pc_rx(char c) {
    uint16_t next = next_index(pc_iot_head);
    if (next != pc_iot_tail) {
        pc_to_iot[pc_iot_head] = c;
        pc_iot_head = next;
    }
}

void comm_uart_iot_rx(char c) {
    uint16_t next = next_index(iot_pc_head);
    if (next != iot_pc_tail) {
        iot_to_pc[iot_pc_head] = c;
        iot_pc_head = next;
    }
}

// ============================================================================
// COMMAND PARSER
// ============================================================================
static void command_dispatch(char *cmd) {

    if (cmd[0] == '\0')
        return;

    // Project 7 trigger
    if (strcmp(cmd, "P7") == 0) {
        run_project7 = 1;
        return;
    }

    movement_execute_string(cmd);
}

static void command_parser(char c) {

    if (c == '\r' || c == '\n') {
        cmd_buffer[cmd_index] = '\0';
        if (cmd_index > 0)
            command_dispatch(cmd_buffer);

        cmd_index = 0;
        return;
    }

    if (cmd_index < sizeof(cmd_buffer) - 1)
        cmd_buffer[cmd_index++] = c;
}

void command_parser_init(void) {
    cmd_index = 0;
}

// ============================================================================
// FORWARDING ENGINE – CALLED FROM MAIN LOOP
// ============================================================================
void UART_Bridge_Process(void) {

    // ----- PC → ESP32 -----
    while (ring_has_data(pc_iot_head, pc_iot_tail)) {
        char c = pc_to_iot[pc_iot_tail];
        pc_iot_tail = next_index(pc_iot_tail);
        UCA0TXBUF = c;
        command_parser(c);
    }

    // ----- ESP32 → PC -----
    while (ring_has_data(iot_pc_head, iot_pc_tail)) {
        char c = iot_to_pc[iot_pc_tail];
        iot_pc_tail = next_index(iot_pc_tail);
        UART_PC_TX(c);
    }
}
