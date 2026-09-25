#include "msp430.h"
#include <string.h>

#include "functions.h"
#include "LCD.h"
#include "macros.h"
#include "ports.h"

// ============================================================================
// MAIN PROGRAM — Project 10 (Merged Project 7 + Project 9)
// Follows Carlson Code Review Structure
// ============================================================================

void main(void) {

// --- Disable high-impedance mode ------------------------------------------------
    PM5CTL0 &= ~LOCKLPM5;

// --- Initialize Peripherals -----------------------------------------------------
    Init_Ports();
    Init_Clocks();
    Init_Conditions();
    Init_Timers();
    Init_ADC();
    Init_LCD();

    Init_UART_PC();
    Init_UART_IOT(BAUD_115200);

    movement_init();
    movement_pwm_init();

    command_parser_init();

// --- Enable global interrupts ---------------------------------------------------
    enable_interrupts();

// --- Initial LCD Content --------------------------------------------------------
    strcpy(display_line[0], " Project 10 ");
    strcpy(display_line[1], "  Merged P7 ");
    strcpy(display_line[2], "  +  P9     ");
    strcpy(display_line[3], "  Ready     ");
    display_changed = TRUE;
    update_display  = TRUE;

// ============================================================================
// FOREGROUND / BACKGROUND LOOP (page 3 in review guide)
// ============================================================================
    while(ALWAYS) {

        Switches_Process();     // Handle switch events
        Display_Process();      // Update LCD when needed
        Black_Line_Follow();    // Use ADC values (Project 7 behavior)
        movement_update();      // PWM motion engine
        Shape_Update();         // Circle, Triangle, Figure-8
        UART_Bridge_Process();  // PC <-> ESP32 WiFi bridge
        Carlson_StateMachine(); // LED timing heartbeat

        P6OUT ^= GRN_LED;       // Heartbeat indicator
        P3OUT ^= TEST_PROBE;    // Probe pin toggle
    }
}
