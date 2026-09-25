#include <stdint.h>
#include <string.h>
#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include "ports.h"
#include "LCD.h"

extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern unsigned int ADC_Thumb;

extern unsigned int delay_start;
extern volatile unsigned int check_line_flag;

extern volatile unsigned char display_changed;

unsigned char search_state = STOPALL;
char adc_char[4];


static void HEXtoBCD(int v) {
    adc_char[0] = '0' + (v / 1000);
    adc_char[1] = '0' + ((v % 1000) / 100);
    adc_char[2] = '0' + ((v % 100) / 10);
    adc_char[3] = '0' + (v % 10);
}

static void adc_line(char line, char pos) {
    char *d = display_line[line - 1];
    d[pos + 0] = adc_char[0];
    d[pos + 1] = adc_char[1];
    d[pos + 2] = adc_char[2];
    d[pos + 3] = adc_char[3];
}


void search_line(void) {

    strcpy(display_line[3], " SEARCH   ");

    if (delay_start > 0) {
        stopall();
        moveforward();
        return;
    }

    moveforward();

    if (check_line_flag) {
        check_line_flag = 0;
        ADCCTL0 |= ADCSC;
    }

    if (ADC_Left_Detect >= LEFT_BLACK_THRESH ||
        ADC_Right_Detect >= RIGHT_BLACK_THRESH) {

        search_state = STOP;
        delay_start = DETECT_WAIT_TICKS;
    }
}


void stop_on_line(void) {

    stopall();
    strcpy(display_line[3], " DETECTED ");

    if (delay_start > 0)
        return;

    search_state = SECR;
}


void reverse_to_line(void) {

    strcpy(display_line[3], " ALIGNING ");
    spin_clockwise();

    if (check_line_flag) {
        check_line_flag = 0;
        ADCCTL0 |= ADCSC;
    }

    if (ADC_Left_Detect >= LEFT_BLACK_THRESH &&
        ADC_Right_Detect >= RIGHT_BLACK_THRESH) {

        search_state = STOPALL;
    }
}


void Black_Line_Follow(void) {

    switch (search_state) {

    case SEARCH:
        search_line();
        break;

    case STOP:
        stop_on_line();
        break;

    case SECR:
        reverse_to_line();
        break;

    case STOPALL:
    default:
        stopall();
        strcpy(display_line[3], " STOP     ");
        break;
    }

    HEXtoBCD(ADC_Left_Detect);
    adc_line(3, 3);

    HEXtoBCD(ADC_Right_Detect);
    adc_line(3, 8);

    display_changed = 1;
}
