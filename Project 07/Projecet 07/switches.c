#include "msp430.h"
#include "switches.h"
#include "functions.h"
#include "macros.h"
#include "ports.h"

// Global flags accessed in main
volatile unsigned char sw1_pressed = 0;
volatile unsigned char sw2_pressed = 0;

//------------------------------------------------------------------------------
// Port 4 ISR - SW1 (P4.0)
//------------------------------------------------------------------------------
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void) {
  if (P4IFG & SW1) {          // Check if SW1 caused interrupt
    __delay_cycles(200000);   // Simple debounce
    if (!(P4IN & SW1)) {      // Confirm button still pressed
      sw1_pressed = 1;        // Set SW1 flag
    }
    P4IFG &= ~SW1;            // Clear interrupt flag
  }
}

//------------------------------------------------------------------------------
// Port 2 ISR - SW2 (P2.2)
//------------------------------------------------------------------------------
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
  if (P2IFG & SW2) {          // Check if SW2 caused interrupt
    __delay_cycles(200000);   // Simple debounce
    if (!(P2IN & SW2)) {      // Confirm button still pressed
      sw2_pressed = 1;        // Set SW2 flag
    }
    P2IFG &= ~SW2;            // Clear interrupt flag
  }
}
