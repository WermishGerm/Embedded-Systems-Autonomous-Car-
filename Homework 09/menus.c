//------------------------------------------------------------------------------
// File Name: menus.c
// Author: Juan Contreras
// Date: November 2025
// Description:
//   Implements the three scrolling menus for Homework 09:
//   1. Resistor Codes
//   2. Shapes
//   3. Red and White Song
//   The thumbwheel (ADC on P1.5) selects items,
//   SW1 enters a submenu, SW2 returns to the previous menu.
//------------------------------------------------------------------------------

#include "msp430.h"
#include "functions.h"
#include "LCD.h"
#include "macros.h"
#include "ports.h"
#include <string.h>

//------------------------------------------------------------------------------
// #defines
//------------------------------------------------------------------------------
#define MAIN_MENU_ITEMS   (3)
#define RES_ITEMS         (10)
#define SHAPE_ITEMS       (10)
#define SONG_SEGMENTS     (40)

// 12-bit ADC range division
#define MAIN_RANGE        (4096 / MAIN_MENU_ITEMS)
#define RES_RANGE         (4096 / RES_ITEMS)
#define SHAPE_RANGE       (4096 / SHAPE_ITEMS)
#define SONG_RANGE        (4096 / SONG_SEGMENTS)

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
void Main_Menu(void);
void Resistor_Menu(void);
void Shape_Menu(void);
void Song_Menu(void);
void Clear_Display(void);

//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------
extern volatile unsigned int ADC_Thumb;
extern char display_line[4][11];

//------------------------------------------------------------------------------
// Lookup Tables
//------------------------------------------------------------------------------
static const char *const resistor_colors[RES_ITEMS] = {
  "Black","Brown","Red","Orange","Yellow",
  "Green","Blue","Violet","Gray","White"
};
static const char *const resistor_values[RES_ITEMS] = {
  "0","1","2","3","4","5","6","7","8","9"
};

static const char *const shapes[SHAPE_ITEMS] = {
  "Circle","Square","Triangle","Octagon","Pentagon",
  "Hexagon","Cube","Oval","Sphere","Cylinder"
};

static const char song_text[] =
"We're the Red and White from State "
"And we know we are the best. "
"A hand behind our back, "
"We can take on all the rest. "
"Come over the hill, Carolina. "
"Devils and Deacs stand in line. "
"The Red and White from N.C. State. "
"Go State!";

//------------------------------------------------------------------------------
// Utility: Clear all display lines (fills with spaces)
//------------------------------------------------------------------------------
void Clear_Display(void){
  strcpy(display_line[0], "           ");
  strcpy(display_line[1], "           ");
  strcpy(display_line[2], "           ");
  strcpy(display_line[3], "           ");
  Display_Update(0,0,0,0);
}

//------------------------------------------------------------------------------
// Main Menu
//------------------------------------------------------------------------------
void Main_Menu(void){
  unsigned char selection = 0;
  unsigned char prev_selection = 255;   // impossible start value

  lcd_4line();
  Clear_Display();

  while(1){
    unsigned int val = ADC_Thumb;
    selection = val / MAIN_RANGE;
    if (selection >= MAIN_MENU_ITEMS) selection = MAIN_MENU_ITEMS - 1;

    // only redraw if selection actually changed
    if(selection != prev_selection){
      Clear_Display();
      switch(selection){
        case 0:
          strcpy(display_line[1], " Resistors ");
          break;
        case 1:
          strcpy(display_line[1], "  Shapes   ");
          break;
        case 2:
          strcpy(display_line[1], "   Song    ");
          break;
      }
      Display_Update(0,0,0,0);
      prev_selection = selection;
    }

    // wait for SW1 press to enter menu
    if(!(P4IN & SW1)){
      while(!(P4IN & SW1));   // debounce
      switch(selection){
        case 0: Resistor_Menu(); break;
        case 1: Shape_Menu();    break;
        case 2: Song_Menu();     break;
      }
      lcd_4line();
      Clear_Display();
      prev_selection = 255;    // force redraw after return
    }
  }
}

//------------------------------------------------------------------------------
// Resistor Menu
//------------------------------------------------------------------------------
void Resistor_Menu(void){
  lcd_4line();
  Clear_Display();

  while(1){
    unsigned int val = ADC_Thumb;
    unsigned char i = val / RES_RANGE;
    if(i >= RES_ITEMS) i = RES_ITEMS - 1;

    Clear_Display();
    strcpy(display_line[0], "Color     ");
    strcpy(display_line[1], resistor_colors[i]);
    strcpy(display_line[2], resistor_values[i]);
    strcpy(display_line[3], "Value     ");
    Display_Update(0,0,0,0);

    if(!(P2IN & SW2)){
      while(!(P2IN & SW2));
      lcd_4line();
      Clear_Display();
      return;
    }
  }
}

//------------------------------------------------------------------------------
// Shape Menu
//------------------------------------------------------------------------------
void Shape_Menu(void){
  lcd_BIG_mid();
  Clear_Display();

  while(1){
    unsigned int val = ADC_Thumb;
    unsigned char idx = val / SHAPE_RANGE;
    if(idx >= SHAPE_ITEMS) idx = SHAPE_ITEMS - 1;

    Clear_Display();
    if(idx == 0)
      strcpy(display_line[0], " ");
    else
      strcpy(display_line[0], shapes[idx-1]);

    strcpy(display_line[1], shapes[idx]);

    if(idx >= SHAPE_ITEMS-1)
      strcpy(display_line[2], " ");
    else
      strcpy(display_line[2], shapes[idx+1]);

    Display_Update(0,0,0,0);

    if(!(P2IN & SW2)){
      while(!(P2IN & SW2));
      lcd_4line();
      Clear_Display();
      return;
    }
  }
}

//------------------------------------------------------------------------------
// Song Menu
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Song_Menu(void){
  unsigned int entry_adc;
  unsigned int val;
  unsigned int prev_val;
  int rel;
  unsigned int scaled;
  unsigned int scroll;
  unsigned int song_length;
  char buf[11];
  unsigned int d;

  const float sensitivity = 3.5f;

  lcd_BIG_mid();
  Clear_Display();

  entry_adc = ADC_Thumb;
  prev_val  = entry_adc;               // store initial ADC value
  song_length = strlen(song_text);

  while(1){
    val = ADC_Thumb;

    // only update when thumbwheel moves forward (CCW)
    if(val > prev_val){
      rel = (int)val - (int)entry_adc;
      if(rel < 0) rel = 0;
      if(rel > 4095) rel = 4095;

      scaled = (unsigned int)(rel * sensitivity);
      if(scaled > 4095) scaled = 4095;

      // faster scroll and full-song coverage
      scroll = (unsigned long)scaled * (song_length - 10) / 2500;
      if(scroll > song_length - 10) scroll = song_length - 10;

      if(scroll & 1){
        strcpy(display_line[0], "   Red   ");
        strcpy(display_line[2], "  White  ");
      } else {
        strcpy(display_line[0], "  White  ");
        strcpy(display_line[2], "   Red   ");
      }

      for(d = 0; d < 10; d++){
        buf[d] = song_text[scroll + d];
      }
      buf[10] = '\0';

      strcpy(display_line[1], buf);
      Display_Update(0,0,0,0);

      prev_val = val;   // remember last ADC so we only move forward
    }

    for(d = 0; d < 20000; d++); // small delay

    if(!(P2IN & SW2)){
      while(!(P2IN & SW2));
      lcd_4line();
      Clear_Display();
      return;
    }
  }
}
