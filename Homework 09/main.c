//------------------------------------------------------------------------------
// main.c
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Jim Carlson
//  Jan 2023
//  Built with Code Composer Version: CCS12.4.0.00007_win64
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include "macros.h"
#include  "ports.h"

// Function Prototypes
void main(void);
void Init_Conditions(void);
void Display_Process(void);
void Init_LEDs(void);
void stopall(void);
void moveforward(void);
void Carlson_StateMachine(void);
void wait_case(void);
void start_case(void);
void run_case(void);
void end_case(void);
void Run_Straight(void);
void Run_Circle(void);
void Run_Figure8(void);
void LCD_update(void);
void Init_ADC(void);
void Run_Triangle(void);
void blackline_state(void); // Added prototype for Project 06 logic
// Homework 09 menu functions
void Main_Menu(void);
void Resistor_Menu(void);
void Shape_Menu(void);
void Song_Menu(void);


// Global Variables
volatile char slow_input_down;
extern char display_line[FOURTH][ELEVENTH];
extern char *display[FOURTH];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
volatile char control_state[7];
unsigned int Last_Time_Sequence;
unsigned int wheel_move;
unsigned char forward;
unsigned char event;
unsigned int event_count;

extern unsigned int cycle_time;    // Defined in states.c
extern unsigned int time_change;   // Defined in states.c

void main(void){
  WDTCTL = WDTPW | WDTHOLD;
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();
  Init_Clocks();
  Init_Conditions();
  Init_LCD();
  Init_Timers();
  Init_ADC();
  enable_interrupts();


  Splash_Screen();             // <-- show splash



  // Wait for button press before showing menu
  while(1){
  Main_Menu();
  }
}

//------------------------------------------------------------------------------
// Splash Screen
//------------------------------------------------------------------------------
void Splash_Screen(void){
  lcd_BIG_mid();              // use big font centered mode
  Clear_Display();            // ensure blank LCD

  strcpy(display_line[0], "   Juan   ");
  strcpy(display_line[1], "Homework9 ");
  strcpy(display_line[2], "Contreras ");
  Display_Update(0,0,0,0);

  // simple delay (~2 seconds at 8MHz)
  unsigned long i;
  for(i = 0; i < 200000; i++);

  lcd_4line();                // return to normal 4-line mode
  Clear_Display();            // clean up before menus
}

