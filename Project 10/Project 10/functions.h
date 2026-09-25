#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdint.h>
#include "msp430.h"

extern volatile unsigned char run_project7;

void Init_Ports(void);
void Init_Clocks(void);
void Init_Conditions(void);
void Init_LCD(void);
void Init_Timers(void);
void enable_interrupts(void);

void UART_Bridge_Process(void);
void Init_UART_PC(void);
void Init_UART_IOT(uint8_t);
void command_parser_init(void);

void movement_init(void);
void movement_pwm_init(void);
void movement_update(void);
void movement_execute_command(char, uint16_t);
void movement_execute_string(char *);

void Carlson_StateMachine(void);
void Display_Process(void);
void LCD_update(void);

void Shape_Update(void);

void project10_run_p7(void);
// Project 7 interface
void project7_start(void);
uint8_t project7_update(void);
uint8_t project7_is_running(void);

void project7_state_machine(void);
unsigned char project7_finished(void);

#endif
