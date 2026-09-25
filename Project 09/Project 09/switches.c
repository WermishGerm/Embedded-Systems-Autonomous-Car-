#include <stdint.h>
#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include "ports.h"
#include "LCD.h"



// Project 9 Phase 1: SW1 and SW2 do nothing special yet.
// They can be used later (Phase 5) for big font commands, reset, etc.

void Switches_Process(void) {

    // === SW1 PRESSED ===
    if (!(P4IN & SW1)) {
        __delay_cycles(20000);   // debounce
        if (!(P4IN & SW1)) {
            // RESERVED FOR FUTURE USE
            while(!(P4IN & SW1)); // wait for release
        }
    }

    // === SW2 PRESSED ===
    if (!(P2IN & SW2)) {
        __delay_cycles(20000);   // debounce
        if (!(P2IN & SW2)) {
            // RESERVED FOR FUTURE USE
            while(!(P2IN & SW2)); // wait for release
        }
    }
}
