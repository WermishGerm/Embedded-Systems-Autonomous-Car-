#ifndef SWITCHES_H
#define SWITCHES_H

#include "msp430.h"
#include "macros.h"

// ---------------------------
// GLOBAL FLAGS
// ---------------------------
extern volatile unsigned char sw1_pressed;
extern volatile unsigned char sw2_pressed;

// ---------------------------
// FUNCTION PROTOTYPES
// ---------------------------
void Switch1_Process(void);
void Switch2_Process(void);

#endif
