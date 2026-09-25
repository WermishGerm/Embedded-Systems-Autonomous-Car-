#include "msp430.h"
#include <string.h>

#include "functions.h"
#include "LCD.h"
#include "macros.h"
#include "ports.h"

// LCD globals
extern char display_line[4][11];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;

void main(void) {

    WDTCTL = WDTPW | WDTHOLD;      // Stop watchdog
    PM5CTL0 &= ~LOCKLPM5;          // Enable GPIO

    // -------------------------
    // INITIALIZATION
    // -------------------------
    Init_Ports();
    Init_Clocks();
    Init_Conditions();
    Init_LCD();
    Init_Timers();

    Init_UART_PC();                 // PC UART
    Init_UART_IOT(BAUD_115200);     // ESP32 UART

    movement_init();                // Motor control
    movement_pwm_init();
    command_parser_init();          // WiFi command handler

    enable_interrupts();

    // Initial LCD contents
    strcpy(display_line[0], " Project 9 ");
    strcpy(display_line[1], "  Waiting  ");
    strcpy(display_line[2], " Commands  ");
    strcpy(display_line[3], "   WiFi    ");

    display_changed = TRUE;
    update_display  = TRUE;

    // -------------------------
    // FOREGROUND / BACKGROUND LOOP
    // -------------------------
    while (ALWAYS) {

        UART_Bridge_Process();      // PC <-> ESP32
        movement_update();          // Drive commands
        Carlson_StateMachine();     // LED blink/timing
        Shape_Update();             // Shape engine

        Display_Process();
        LCD_update();

        P6OUT ^= GRN_LED;           // Heartbeat
        P3OUT ^= TEST_PROBE;
    }
}
