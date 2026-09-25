// ============================================================================
// UART ISR HANDLERS
// ============================================================================

#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include "ports.h"

// ============================================================================
// PC UART (UCA1)
// ============================================================================
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void) {

    switch (__even_in_range(UCA1IV, 0x08)) {

    case 0x00: break;
    case 0x02: {    // RXIFG
        char c = UCA1RXBUF;
        comm_uart_pc_rx(c);
        break;
    }
    }
}

// ============================================================================
// IOT UART (UCA0)
// ============================================================================
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void) {

    switch (__even_in_range(UCA0IV, 0x08)) {

    case 0x02: {    // RXIFG
        char c = UCA0RXBUF;
        UART_PC_TX('#');      // marker
        comm_uart_iot_rx(c);
        break;
    }
    }
}
