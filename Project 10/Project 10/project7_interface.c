/*
 * project7_interface.c
 *
 *  Created on: Dec 6, 2025
 *      Author: jcont
 */
// ============================================================================
// PROJECT7_INTERFACE.C  –  Bridges Project 7 FSM into Project 10
// ============================================================================

#include <stdint.h>
#include "msp430.h"
#include "functions.h"
#include "macros.h"

// External Project 7 variables
extern unsigned char state;      // your P7 state variable
extern const unsigned char STOPPED;   // final state constant

// Internal flag
static uint8_t p7_running = 0;

void project7_start(void) {
    p7_running = 1;
}

uint8_t project7_update(void) {
    if (!p7_running)
        return 0;

    // FSM runs naturally inside your main loop
    if (state == STOPPED) {
        p7_running = 0;
        return 1;       // finished
    }
    return 0;           // still running
}

uint8_t project7_is_running(void) {
    return p7_running;
}




