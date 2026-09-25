#include "msp430.h"
#include "serial.h"
#include "LCD.h"
#include "functions.h"
#include "macros.h"
#include "ports.h"

extern volatile unsigned char baud_mode;

void Switches_Process(void) {

    // -------------------------
    // SW1: TRANSMIT LAST CMD
    // -------------------------
    if (!(P4IN & SW1)) {
        Transmit_Command();
        __delay_cycles(400000);
    }

    // -------------------------
    // SW2: TOGGLE BAUD RATE
    // -------------------------
    if (!(P2IN & SW2)) {
        __delay_cycles(20000);       // small debounce

        if (!(P2IN & SW2)) {         // still pressed?
            if (baud_mode == BAUD_9600)
                Set_Baud(BAUD_115200);
            else
                Set_Baud(BAUD_9600);

            while(!(P2IN & SW2));    // wait until released
        }
    }

}
