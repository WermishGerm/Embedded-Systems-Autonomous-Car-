#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdint.h>
#include "msp430.h"

// ============================================================================
// SYSTEM INITIALIZATION (Carlson Framework)
// ============================================================================
void Init_Ports(void);
void Init_Clocks(void);
void Init_Conditions(void);
void Init_LCD(void);
void Init_Timers(void);
void enable_interrupts(void);

// Carlson core behavior
void Carlson_StateMachine(void);
void Display_Process(void);

// ============================================================================
// UART / COMMUNICATION SUBSYSTEM
// ============================================================================

// PC UART (UCA1)
void Init_UART_PC(void);
void UART_PC_TX(char c);

// IOT UART (UCA0)
void Init_UART_IOT(uint8_t baud_mode);
void UART_IOT_TX(char c);

// Combined UART bridging (PC <-> ESP32)
void UART_Bridge_Process(void);

// Command parser initialization
void command_parser_init(void);

// ============================================================================
// MOVEMENT SYSTEM — NEW PWM ENGINE
// ============================================================================
void movement_init(void);
void movement_pwm_init(void);
void movement_update(void);

// Execute one command (e.g. 'F', 2)
void movement_execute_command(char direction, uint16_t value);

// Execute string command (e.g. "F2", "L45")
void movement_execute_string(char *cmd);

// Big-font LCD display of movement
void movement_display_big(char direction, uint16_t value);

// ============================================================================
// MOVEMENT SYSTEM — LEGACY DIRECT MOTOR CONTROL
// ============================================================================
void stopall(void);
void moveforward(void);
void movereverse(void);
void spin_clockwise(void);
void spin_counterclockwise(void);

// ============================================================================
// ADC SUBSYSTEM
// ============================================================================
void Init_ADC(void);
void ADC_Process(void);     // if used by your adc.c

// ============================================================================
// BLACK LINE FOLLOWING
// ============================================================================
void Black_Line_Follow(void);   // if used by your black_line.c

// ============================================================================
// STATE MACHINE MOVEMENTS (Triangle/Circle/Figure-8)
// ============================================================================
void Run_Straight(void);
void Run_Circle(void);
void Run_Triangle(void);
void Run_Figure8(void);

// Internal state transitions (exposed if cross-module)
void wait_case(void);
void start_case(void);
void run_case(void);
void end_case(void);

void start_case_circle(void);
void run_case_circle(void);

void start_case_triangle(void);
void run_case_triangle(void);

void start_case_figure8(void);
void run_case_figure8(void);

// ============================================================================
// TIMED MOVEMENT SUPPORT
// ============================================================================
void state_timer(void);
void timed_moves(void);
void LCD_update(void);

// ============================================================================
// SWITCH PROCESSING
// ============================================================================
void Switches_Process(void);

// ============================================================================
// SYSTEM UTILITY
// ============================================================================
void Display_Update(char p_L1, char p_L2, char p_L3, char p_L4);

void Shape_Update(void);
void Run_Straight(void);
void Run_Circle(void);
void Run_Triangle(void);
void Run_Figure8(void);


#endif /* FUNCTIONS_H_ */
