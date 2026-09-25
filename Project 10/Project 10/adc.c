#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include "ports.h"
#include "LCD.h"

unsigned int ADC_Left_Detect  = 0;
unsigned int ADC_Right_Detect = 0;
unsigned int ADC_Thumb        = 0;

volatile unsigned int check_line_flag = 0;
volatile unsigned char adc_stage = 0;       // 0 = Thumb, 1 = Right, 2 = Left


void Init_ADC(void) {

    ADCCTL0 = ADCSHT_2 | ADCON | ADCMSC;
    ADCCTL1 = ADCSHP | ADCCONSEQ_0;
    ADCCTL2 = ADCRES_2;

    ADCMCTL0 = ADCINCH_5;   // Start on Thumb

    ADCIE |= ADCIE0;

    ADCCTL0 |= ADCENC | ADCSC;
}


#pragma vector = ADC_VECTOR
__interrupt void ADC_ISR(void) {

    ADCCTL0 &= ~ADCENC;

    switch (adc_stage) {

    case 0:     // Thumb
        ADC_Thumb = ADCMEM0;
        adc_stage = 1;
        ADCMCTL0 = (ADCMCTL0 & 0xF0) | ADCINCH_3;   // Right
        break;

    case 1:     // Right
        ADC_Right_Detect = ADCMEM0;
        adc_stage = 2;
        ADCMCTL0 = (ADCMCTL0 & 0xF0) | ADCINCH_2;   // Left
        break;

    case 2:     // Left
        ADC_Left_Detect = ADCMEM0;
        check_line_flag = 1;
        adc_stage = 0;
        ADCMCTL0 = (ADCMCTL0 & 0xF0) | ADCINCH_5;   // Back to Thumb
        break;
    }

    ADCCTL0 |= ADCENC | ADCSC;
}
