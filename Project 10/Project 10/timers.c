#include <stdint.h>
#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include "ports.h"
#include "LCD.h"

volatile unsigned int timer_counter = 0;
volatile unsigned int LCD_counter   = 0;

extern unsigned int delay_start;


void Init_Timers(void) {
    Init_Timer_B0();
}


// ---------------------------------------------------------------------------
// TIMER B0  – SYSTEM TICK (continuous mode)
// ---------------------------------------------------------------------------
void Init_Timer_B0(void) {

    TB0CTL = TBSSEL__SMCLK | TBCLR | MC__CONTINOUS;
    TB0CTL |= ID__2;          // /2
    TB0EX0 = TBIDEX__8;       // /8

    TB0CCR0  = TB0CCR0_INTERVAL;
    TB0CCTL0 = CCIE;

    TB0CTL &= ~TBIE;
    TB0CTL &= ~TBIFG;
}


// ---------------------------------------------------------------------------
// TIMER B0 CCR0 ISR – main timing engine
// ---------------------------------------------------------------------------
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void) {

    timer_counter++;
    LCD_counter++;

    if (delay_start > 0)
        delay_start--;

    TB0CCR0 += TB0CCR0_INTERVAL;
}


// ---------------------------------------------------------------------------
// TIMER B0 CCR1/CCR2/Overflow ISR – unused but required
// ---------------------------------------------------------------------------
#pragma vector = TIMER0_B1_VECTOR
__interrupt void Timer0_B1_ISR(void) {

    switch (__even_in_range(TB0IV, 14)) {

    case 0:  break;
    case 2:  TB0CCR1 += TB0CCR1_INTERVAL; break;
    case 4:  TB0CCR2 += TB0CCR2_INTERVAL; break;
    case 14: break;

    default: break;
    }
}
