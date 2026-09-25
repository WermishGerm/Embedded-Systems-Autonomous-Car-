#include "msp430.h"
#include <string.h>
#include "functions.h"
#include "LCD.h"
#include "macros.h"
#include "ports.h"

// ============================================================================
// TOP-LEVEL PORT INITIALIZATION
// ============================================================================
void Init_Ports(void) {
    Init_Port_1();
    Init_Port_2();
    Init_Port_3();
    Init_Port_4();
    Init_Port_5();
    Init_Port_6();
}

// ============================================================================
// PORT 1
// ============================================================================
void Init_Port_1(void) {

    P1OUT = 0;
    P1DIR = 0;

    // Red LED
    P1SEL0 &= ~RED_LED;
    P1SEL1 &= ~RED_LED;
    P1DIR  |=  RED_LED;
    P1OUT  &= ~RED_LED;

    // A1_SEEED
    P1SEL0 &= ~A1_SEEED;
    P1SEL1 &= ~A1_SEEED;
    P1DIR  |=  A1_SEEED;
    P1OUT  &= ~A1_SEEED;

    // V_DETECT_L (ADC)
    P1SEL0 |=  V_DETECT_L;
    P1SEL1 |=  V_DETECT_L;
    P1DIR  &= ~V_DETECT_L;

    // V_DETECT_R (ADC)
    P1SEL0 |=  V_DETECT_R;
    P1SEL1 |=  V_DETECT_R;
    P1DIR  &= ~V_DETECT_R;

    // P1.4 A4_SEEED
    P1SEL0 &= ~A4_SEEED;
    P1SEL1 &= ~A4_SEEED;
    P1DIR  |=  A4_SEEED;
    P1OUT  &= ~A4_SEEED;

    // Thumbwheel (ADC)
    P1SEL0 |=  V_THUMB;
    P1SEL1 |=  V_THUMB;
    P1DIR  &= ~V_THUMB;

    // UART UCA0 (ESP32)
    P1SEL0 |=  (UCA0TXD | UCA0RXD);
    P1SEL1 &= ~(UCA0TXD | UCA0RXD);
}

// ============================================================================
// PORT 2
// ============================================================================
void Init_Port_2(void) {

    P2OUT = 0;
    P2DIR = 0;

    P2SEL0 &= ~SLOW_CLK;
    P2SEL1 &= ~SLOW_CLK;
    P2DIR  |=  SLOW_CLK;

    P2SEL0 &= ~CHECK_BAT;
    P2SEL1 &= ~CHECK_BAT;
    P2DIR  |=  CHECK_BAT;

    P2SEL0 &= ~IR_LED;
    P2SEL1 &= ~IR_LED;
    P2DIR  |=  IR_LED;
    P2OUT  |=  IR_LED;        // default ON

    // SW2 (pull-up)
    P2SEL0 &= ~SW2;
    P2SEL1 &= ~SW2;
    P2DIR  &= ~SW2;
    P2OUT  |=  SW2;
    P2REN  |=  SW2;

    // ESP32 Power
    P2SEL0 &= ~IOT_RUN_CPU;
    P2SEL1 &= ~IOT_RUN_CPU;
    P2DIR  |=  IOT_RUN_CPU;
    P2OUT  |=  IOT_RUN_CPU;

    // DAC_ENB
    P2SEL0 &= ~DAC_ENB;
    P2SEL1 &= ~DAC_ENB;
    P2DIR  |=  DAC_ENB;
    P2OUT  |=  DAC_ENB;

    // LFXIN/LFXOUT
    P2SEL0 &= ~(LFXIN | LFXOUT);
    P2SEL1 |=  (LFXIN | LFXOUT);
}

// ============================================================================
// PORT 3
// ============================================================================
void Init_Port_3(void) {

    P3OUT = 0;
    P3DIR = 0;

    P3SEL0 &= ~TEST_PROBE;
    P3SEL1 &= ~TEST_PROBE;
    P3DIR  |=  TEST_PROBE;

    P3DIR  |= (DAC_CTRL_2 | DAC_CTRL_3);
    P3OUT  &= ~(DAC_CTRL_2 | DAC_CTRL_3);

    P3DIR  |= (OA2N | OA2P);

    P3SEL0 &= ~SMCLK_OUT;
    P3SEL1 &= ~SMCLK_OUT;
    P3DIR  |=  SMCLK_OUT;

    // UART routing link to ESP32
    P3SEL0 &= ~IOT_LINK_CPU;
    P3SEL1 &= ~IOT_LINK_CPU;
    P3DIR  |=  IOT_LINK_CPU;
    P3OUT  |=  IOT_LINK_CPU;

    // ESP32 Reset pin
    P3SEL0 &= ~IOT_RN_CPU;
    P3SEL1 &= ~IOT_RN_CPU;
    P3DIR  |=  IOT_RN_CPU;
    P3OUT  |=  IOT_RN_CPU;
}

// ============================================================================
// PORT 4
// ============================================================================
void Init_Port_4(void) {

    P4OUT = 0;
    P4DIR = 0;

    P4SEL0 &= ~RESET_LCD;
    P4SEL1 &= ~RESET_LCD;
    P4DIR  |=  RESET_LCD;

    // SW1 pull-up
    P4SEL0 &= ~SW1;
    P4SEL1 &= ~SW1;
    P4DIR  &= ~SW1;
    P4OUT  |=  SW1;
    P4REN  |=  SW1;

    // PC UART (UCA1)
    P4SEL0 |=  (UCA1RXD | UCA1TXD);
    P4SEL1 &= ~(UCA1RXD | UCA1TXD);

    // LCD SPI
    P4SEL0 &= ~UCB1_CS_LCD;
    P4SEL1 &= ~UCB1_CS_LCD;
    P4DIR  |=  UCB1_CS_LCD;
    P4OUT  |=  UCB1_CS_LCD;

    P4SEL0 |= (UCB1CLK | UCB1SIMO | UCB1SOMI);
    P4SEL1 &= ~(UCB1CLK | UCB1SIMO | UCB1SOMI);
}

// ============================================================================
// PORT 5
// ============================================================================
void Init_Port_5(void) {

    P5SEL0 |= (V_BAT | V_5 | V_DAC | V3_3);
    P5SEL1 |= (V_BAT | V_5 | V_DAC | V3_3);

    P5DIR  &= ~(V_BAT | V_5 | V_DAC | V3_3);

    P5SEL0 &= ~IOT_BOOT_CPI;
    P5SEL1 &= ~IOT_BOOT_CPI;
    P5DIR  |=  IOT_BOOT_CPI;
    P5OUT  |=  IOT_BOOT_CPI;
}

// ============================================================================
// PORT 6 (PWM motors + LCD backlight)
// ============================================================================
void Init_Port_6(void) {

    P6OUT = 0;
    P6DIR = 0;

    // Motor outputs (PWM via TB3)
    P6SEL0 |= (L_FORWARD | R_FORWARD | L_REVERSE | R_REVERSE);
    P6SEL1 &= ~(L_FORWARD | R_FORWARD | L_REVERSE | R_REVERSE);

    P6DIR  |= (L_FORWARD | R_FORWARD | L_REVERSE | R_REVERSE);

    // LCD Backlight
    P6SEL0 |=  LCD_BACKLITE;
    P6SEL1 &= ~LCD_BACKLITE;
    P6DIR  |=  LCD_BACKLITE;
    P6OUT  |=  LCD_BACKLITE;

    // Green LED
    P6SEL0 &= ~GRN_LED;
    P6SEL1 &= ~GRN_LED;
    P6DIR  |=  GRN_LED;
    P6OUT  &= ~GRN_LED;

    // P6.5 spare
    P6SEL0 &= ~P6_5;
    P6SEL1 &= ~P6_5;
    P6DIR  |=  P6_5;
    P6OUT  &= ~P6_5;
}
