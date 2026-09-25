
#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include "macros.h"
#include "ports.h"

volatile unsigned int timer_counter = 0;
volatile unsigned int LCD_counter = 0;
volatile unsigned char in_debounce = 0;

extern volatile unsigned int ncount_debounce_SW1;
extern volatile unsigned int ncount_debounce_SW2;

void Init_Timers(void){
	Init_Timer_B0();
}
//------------------------------------------------------------------------------
// Timer B0 initialization sets up both B0_0, B0_1-B0_2 and overflow
void Init_Timer_B0(void) {
 	TB0CTL = TBSSEL__SMCLK; // SMCLK source
 	TB0CTL |= TBCLR; // Resets TB0R, clock divider, count direction
 	TB0CTL |= MC__CONTINOUS; // Continuous up
 	TB0CTL |= ID__8; // Divide clock by 2

 	TB0EX0 = TBIDEX__8; // Divide clock by an additional 8
 	TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
 	TB0CCTL0 |= CCIE; // CCR0 enable interrupt
 
	 TB0CCR1 = TB0CCR1_INTERVAL; // CCR1
 	 TB0CCTL1 |= CCIE; // CCR1 enable interrupt

	// TB0CCR2 = TB0CCR2_INTERVAL; // CCR2
	// TB0CCTL2 |= CCIE; // CCR2 enable interrupt
	
 	TB0CTL &= ~TBIE; // Disable Overflow Interrupt
 	TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}
//---------


#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//----------------------------------------------------------------------------
timer_counter++;
LCD_counter++;
//ADCCTL0 |= ADCSC; // Start next sample


if (!in_debounce){
P6OUT ^= LCD_BACKLITE;
}

 TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
//----------------------------------------------------------------------------
}
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------

 if (in_debounce) {
       P6OUT &= ~LCD_BACKLITE;
     }

 switch(__even_in_range(TB0IV,14)){
 case 0: break; // No interrupt
 case 2:
 if (in_debounce){
 	ncount_debounce_SW1++;
 	ncount_debounce_SW2++;

 	if (ncount_debounce_SW1 >= DEBOUNCE_THRESHOLD) {
 		 P4IFG &= ~SW1;      // Clear pending flag
         P4IE  |= SW1;       // Re-enable SW1 interrupt
         in_debounce = 0;
         ncount_debounce_SW1 = 0;
         P6OUT |= LCD_BACKLITE; // Turn LCD backlight back on
         TB0CCTL1 &= ~CCIE;  // Disable debounce timer
 	}
 	if (ncount_debounce_SW2 >= DEBOUNCE_THRESHOLD) {
 	         P2IFG &= ~SW2;      // Clear pending flag
 	         P2IE  |= SW2;       // Re-enable SW1 interrupt
 	         in_debounce = 0;
 	         ncount_debounce_SW2 = 0;
 	         P6OUT |= LCD_BACKLITE; // Turn LCD backlight back on
 	         TB0CCTL1 &= ~CCIE;  // Disable debounce timer
 	    }
 }

 TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
 break;
 case 4: // CCR2 not used

 TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
 break;
 case 14: // overflow

 break;
 default: break;
 }
//----------------------------------------------------------------------------
}
