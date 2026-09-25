/*
 * ports.c
 *
 *  Created on: Sep 10, 2025
 *      Author: Juan Contreras
 *
 *  Initializes all GPIO ports used in the project.
 */

#include "msp430.h"
#include <string.h>
#include "functions.h"
#include "LCD.h"
#include "macros.h"
#include "ports.h"

//=========================================================================
// Top-level ports init
//=========================================================================
void Init_Ports(void) {
  Init_Port_1();
  Init_Port_2();
  Init_Port_3();
  Init_Port_4();
  Init_Port_5();
  Init_Port_6();
}

//=========================================================================
// PORT 1 INITIALIZATION
//=========================================================================
void Init_Port_1(void){ //This function will initialize all pins in port 1.
  P1OUT = 0x00;
  P1DIR = 0x00;

  // P1.0 - RED LED
  P1SEL0 &= ~RED_LED;    // GPIO
  P1SEL1 &= ~RED_LED;
  P1OUT  &= ~RED_LED;    // Low
  P1DIR  |= RED_LED;     // Output

  // P1.1 - A1_SEEED
  P1SEL0 &= ~A1_SEEED;   // GPIO
  P1SEL1 &= ~A1_SEEED;
  P1OUT  &= ~A1_SEEED;   // Low
  P1DIR  |= A1_SEEED;    // Output

  // --- START: ADC PINS CONFIGURATION (V_DETECT_L, V_DETECT_R, V_THUMB) ---

  // P1.2 - V_DETECT_L (ADC)
  P1SEL0 |= V_DETECT_L;  // Analog
  P1SEL1 |= V_DETECT_L;
  P1OUT  &= ~V_DETECT_L; // No pullup
  P1DIR  &= ~V_DETECT_L; // Input
  P1REN  &= ~V_DETECT_L; // No pull resistor

  // P1.3 - V_DETECT_R (ADC)
  P1SEL0 |= V_DETECT_R;  // Analog
  P1SEL1 |= V_DETECT_R;
  P1OUT  &= ~V_DETECT_R;
  P1DIR  &= ~V_DETECT_R;
  P1REN  &= ~V_DETECT_R;

  // P1.4 - A4_SEEED (GPIO output)
  P1SEL0 &= ~A4_SEEED;
  P1SEL1 &= ~A4_SEEED;
  P1OUT  &= ~A4_SEEED;   // Low
  P1DIR  |= A4_SEEED;    // Output

  // P1.5 - V_THUMB (ADC)
  P1SEL0 |= V_THUMB;     // Analog
  P1SEL1 |= V_THUMB;
  P1OUT  &= ~V_THUMB;
  P1DIR  &= ~V_THUMB;    // Input
  P1REN  &= ~V_THUMB;    // No pull

  // --- END: ADC PINS CONFIGURATION ---

  // UART PINS FOR PROJECT 8 USING UCA0
  P1SEL0 |= UCA0TXD;
  P1SEL1 &= ~UCA0TXD;

  P1SEL0 |= UCA0RXD;
  P1SEL1 &= ~UCA0RXD;

}

//=========================================================================
// PORT 2 INITIALIZATION
//=========================================================================
void Init_Port_2(void){ // Configure Port 2
//------------------------------------------------------------------------------
  P2OUT = 0x00; // P2 set Low
  P2DIR = 0x00; // Set P2 direction to input initially

  // P2.0 - SLOW_CLK
  P2SEL0 &= ~SLOW_CLK; // GPIO
  P2SEL1 &= ~SLOW_CLK;
  P2OUT  &= ~SLOW_CLK; // Low
  P2DIR  |= SLOW_CLK;  // Output

  // P2.1 - CHECK_BAT
  P2SEL0 &= ~CHECK_BAT; // GPIO
  P2SEL1 &= ~CHECK_BAT;
  P2OUT  &= ~CHECK_BAT;
  P2DIR  |= CHECK_BAT;

  // P2.2 - IR_LED
  P2SEL0 &= ~IR_LED; // GPIO
  P2SEL1 &= ~IR_LED;
  P2OUT  |= IR_LED;  // High / ON
  P2DIR  |= IR_LED;  // Output

  // P2.3 - SW2 (input with pullup)
  P2SEL0 &= ~SW2;
  P2SEL1 &= ~SW2;
  P2OUT  |= SW2;     // Pull-up
  P2DIR  &= ~SW2;    // Input
  P2REN  |= SW2;     // Enable pull

  // P2.4 - IOT_RUN_CPU
  P2SEL0 &= ~IOT_RUN_CPU;
  P2SEL1 &= ~IOT_RUN_CPU;
  P2OUT  |= IOT_RUN_CPU;   // HIGH = buffer ON / IOT power path ON
  P2DIR  |= IOT_RUN_CPU;


  // P2.5 - DAC_ENB
  P2SEL0 &= ~DAC_ENB;
  P2SEL1 &= ~DAC_ENB;
  P2OUT  |= DAC_ENB; // High
  P2DIR  |= DAC_ENB;

  // P2.6 - LFXOUT
  P2SEL0 &= ~LFXOUT;
  P2SEL1 |=  LFXOUT; // Clock function

  // P2.7 - LFXIN
  P2SEL0 &= ~LFXIN;
  P2SEL1 |=  LFXIN;  // Clock function
//------------------------------------------------------------------------------
}

//=========================================================================
// PORT 3 INITIALIZATION
//=========================================================================
void Init_Port_3(void){
  P3OUT = 0x00;
  P3DIR = 0x00;

  // P3.0 - TEST_PROBE
  P3SEL0 &= ~TEST_PROBE;
  P3SEL1 &= ~TEST_PROBE;
  P3OUT  &= ~TEST_PROBE;
  P3DIR  |= TEST_PROBE;

  // P3.1 - DAC_CTRL_2
  P3SEL0 &= ~DAC_CTRL_2;
  P3SEL1 &= ~DAC_CTRL_2;
  P3OUT  &= ~DAC_CTRL_2;
  P3DIR  |= DAC_CTRL_2;

  // P3.2 - OA2N
  P3SEL0 &= ~OA2N;
  P3SEL1 &= ~OA2N;
  P3OUT  &= ~OA2N;
  P3DIR  |= OA2N;

  // P3.3 - OA2P
  P3SEL0 &= ~OA2P;
  P3SEL1 &= ~OA2P;
  P3OUT  &= ~OA2P;
  P3DIR  |= OA2P;

  // P3.4 - SMCLK_OUT
  P3SEL0 &= ~SMCLK_OUT;
  P3SEL1 &= ~SMCLK_OUT;
  P3OUT  &= ~SMCLK_OUT;
  P3DIR  |= SMCLK_OUT;

  // P3.5 - DAC_CTRL_3
  P3SEL0 &= ~DAC_CTRL_3;
  P3SEL1 &= ~DAC_CTRL_3;
  P3OUT  &= ~DAC_CTRL_3;
  P3DIR  |= DAC_CTRL_3;

  // P3.6 - IOT_LINK_CPU
  P3SEL0 &= ~IOT_LINK_CPU;
  P3SEL1 &= ~IOT_LINK_CPU;
  P3OUT  |= IOT_LINK_CPU;  // HIGH = connect ESP32 UART to MSP430 routing
  P3DIR  |= IOT_LINK_CPU;



  // P3.7 - IOT_RN_CPU (Reset pin for ESP32)
  P3SEL0 &= ~IOT_RN_CPU;
  P3SEL1 &= ~IOT_RN_CPU;
  P3OUT  |= IOT_RN_CPU;    // IMPORTANT: high = NOT in reset (module boots)
  P3DIR  |= IOT_RN_CPU;

}

//=========================================================================
// PORT 4 INITIALIZATION
//=========================================================================
void Init_Port_4(void){ // Configure PORT 4
//------------------------------------------------------------------------------
  P4OUT = 0x00; // P4 set Low
  P4DIR = 0x00; // Set P4 direction to input initially

  // P4.0 - RESET_LCD
  P4SEL0 &= ~RESET_LCD;
  P4SEL1 &= ~RESET_LCD;
  P4OUT  &= ~RESET_LCD;
  P4DIR  |= RESET_LCD;

  // P4.1 - SW1 (input with pullup)
  P4SEL0 &= ~SW1;
  P4SEL1 &= ~SW1;
  P4OUT  |= SW1;
  P4DIR  &= ~SW1;
  P4REN  |= SW1;

  // ---------- UCA1 UART PINS ----------
  // P4.2 - UCA1RXD
  P4SEL0 |= UCA1RXD;     // USCI_A1 UART operation
  P4SEL1 &= ~UCA1RXD;

  // P4.3 - UCA1TXD
  P4SEL0 |= UCA1TXD;     // USCI_A1 UART operation
  P4SEL1 &= ~UCA1TXD;

  // P4.4 - UCB1_CS_LCD
  P4SEL0 &= ~UCB1_CS_LCD;
  P4SEL1 &= ~UCB1_CS_LCD;
  P4OUT  |= UCB1_CS_LCD; // CS high (inactive)
  P4DIR  |= UCB1_CS_LCD;

  // P4.5 - UCB1CLK
  P4SEL0 |= UCB1CLK;
  P4SEL1 &= ~UCB1CLK;

  // P4.6 - UCB1SIMO
  P4SEL0 |= UCB1SIMO;
  P4SEL1 &= ~UCB1SIMO;

  // P4.7 - UCB1SOMI
  P4SEL0 |= UCB1SOMI;
  P4SEL1 &= ~UCB1SOMI;
//------------------------------------------------------------------------------
}

//=========================================================================
// PORT 5 INITIALIZATION
//=========================================================================
void Init_Port_5(void){
  // --- START: ADC PINS CONFIGURATION (V_BAT, V_5, V_DAC, V3_3) ---

  P5SEL0 |= V_BAT;
  P5SEL1 |= V_BAT;
  P5OUT  &= ~V_BAT;
  P5DIR  &= ~V_BAT;
  P5REN  &= ~V_BAT;

  P5SEL0 |= V_5;
  P5SEL1 |= V_5;
  P5OUT  &= ~V_5;
  P5DIR  &= ~V_5;
  P5REN  &= ~V_5;

  P5SEL0 |= V_DAC;
  P5SEL1 |= V_DAC;
  P5OUT  &= ~V_DAC;
  P5DIR  &= ~V_DAC;
  P5REN  &= ~V_DAC;

  P5SEL0 |= V3_3;
  P5SEL1 |= V3_3;
  P5OUT  &= ~V3_3;
  P5DIR  &= ~V3_3;
  P5REN  &= ~V3_3;

  // --- END: ADC PINS CONFIGURATION ---

  // P5.? - IOT_BOOT_CPI
  P5SEL0 &= ~IOT_BOOT_CPI;
  P5SEL1 &= ~IOT_BOOT_CPI;
  P5OUT  |= IOT_BOOT_CPI;
  P5DIR  |= IOT_BOOT_CPI;
}

//=========================================================================
// PORT 6 INITIALIZATION
//=========================================================================
void Init_Port_6(void){
  // P6.0 - L_FORWARD
  P6SEL0 &= ~L_FORWARD;
  P6SEL1 &= ~L_FORWARD;
  P6OUT  &= ~L_FORWARD;
  P6DIR  |= L_FORWARD;

  // P6.1 - R_FORWARD
  P6SEL0 &= ~R_FORWARD;
  P6SEL1 &= ~R_FORWARD;
  P6OUT  &= ~R_FORWARD;
  P6DIR  |= R_FORWARD;

  // P6.2 - L_REVERSE
  P6SEL0 &= ~L_REVERSE;
  P6SEL1 &= ~L_REVERSE;
  P6OUT  &= ~L_REVERSE;
  P6DIR  |= L_REVERSE;

  // P6.3 - R_REVERSE
  P6SEL0 &= ~R_REVERSE;
  P6SEL1 &= ~R_REVERSE;
  P6OUT  &= ~R_REVERSE;
  P6DIR  |= R_REVERSE;

  // P6.4 - LCD_BACKLITE
  P6SEL0 &= ~LCD_BACKLITE;
  P6SEL1 &= ~LCD_BACKLITE;
  P6OUT  |= LCD_BACKLITE;
  P6DIR  |= LCD_BACKLITE;

  // P6.5 - P6_5
  P6SEL0 &= ~P6_5;
  P6SEL1 &= ~P6_5;
  P6OUT  &= ~P6_5;
  P6DIR  |= P6_5;

  // P6.6 - GRN_LED
  P6SEL0 &= ~GRN_LED;
  P6SEL1 &= ~GRN_LED;
  P6OUT  &= ~GRN_LED;
  P6DIR  |= GRN_LED;

  // Map TB1.1 and TB1.2 to P6.0 and P6.1
  P6SEL0 |= (L_FORWARD | R_FORWARD);
  P6SEL1 &= ~(L_FORWARD | R_FORWARD);

}
