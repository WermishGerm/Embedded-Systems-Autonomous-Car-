//------------------------------------------------------------------------------
// main.c — Project 8 (Serial Communication Only)
// Clean version with:
//  • System initialization
//  • Carlson state timing logic still functional (LEDs/timing)
//  • UART receive/transmit (Project 8)
//  • SW1 / SW2 handling
//  • LCD engine
//
//  All BLACK LINE logic has been REMOVED.
//------------------------------------------------------------------------------

#include "msp430.h"
#include <string.h>
#include "functions.h"
#include "LCD.h"
#include "macros.h"
#include "ports.h"
#include "serial.h"

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------
extern char display_line[FOURTH][ELEVENTH];
extern char *display[FOURTH];

extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;

extern volatile unsigned int Time_Sequence;
extern volatile char one_time;

extern unsigned int cycle_time;
extern unsigned int time_change;

// Local variables
unsigned int wheel_move;
unsigned char forward;
unsigned char event;

//------------------------------------------------------------------------------
// MAIN
//------------------------------------------------------------------------------
void main(void) {

    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog
    PM5CTL0 &= ~LOCKLPM5;       // Enable GPIO

    // -------------------------
    // SYSTEM INITIALIZATION
    // -------------------------
    Init_Ports();
    Init_Clocks();
    Init_Conditions();
    Init_LCD();
    Init_Timers();
    Init_ADC();
    Init_Serial();

    enable_interrupts();

    // -------------------------
    // PROJECT 8 INITIAL DISPLAY
    // -------------------------
    strcpy(display_line[0], "Waiting    ");
    strcpy(display_line[1], "  Proj 8   ");
    strcpy(display_line[2], "BR:9600    ");   // Baud label
    strcpy(display_line[3], "          ");

    display_changed = TRUE;
    update_display  = TRUE;

    // -------------------------
    // INITIALIZE STATE MACHINE VARIABLES
    // (Used by Carlson's LED/time engine)
    // -------------------------
    wheel_move = 0;
    forward = TRUE;
    event = 0;   // No-longer used, kept for compatibility

    // -------------------------
    // MAIN OPERATING LOOP
    // -------------------------
    while (1) {

        // -------------------------
        // UART Check for Received Message
        // -------------------------
        Serial_Process_RX();

        // -------------------------
        // Carlson LED + Timing State Machine
        // (Your LEDs, LCD big font, animations, etc.)
        // -------------------------
        Carlson_StateMachine();

        // -------------------------
        // Button Handler
        // - SW1 = Transmit last received 10-char message
        // - SW2 = Toggle baud rate
        // -------------------------
        Switches_Process();

        // -------------------------
        // LCD Display Engine
        // -------------------------
        Display_Process();
        LCD_update();

        // Debug toggle
        P3OUT ^= TEST_PROBE;
    }
}
