/*
 * macros.h
 *
 *  Created on: Sep 10, 2025
 *      Author: Juan Contreras
 *
 *  List of #defines used across the project
 *  (LEDs, test pins, constants, etc.)
 */

#ifndef MACROS_H_
#define MACROS_H_

// General
#define ALWAYS          (1)
#define RESET_STATE     (0)
#define TRUE            (0x01)
#define CLEAR_REGISTER  (0x0000)
#define RED_LED         (0x01)   // Red LED
#define GRN_LED         (0x40)   // Green LED
#define TEST_PROBE      (0x01)   // Test probe
#define MCLK_FREQ_MHZ   (8)      // MCLK = 8 MHz

//numerical defines
#define FOURTH          (4)
#define ELEVENTH        (11)

// STATES ======================================================================
#define NONE ('N')
#define STRAIGHT ('L')
#define CIRCLE ('C')
#define TRIANGLE ('T')
#define FIGURE8 ('F')
#define WAIT ('W')
#define START ('S')
#define RUN ('R')
#define END ('E')
#define WHEEL_COUNT_TIME (20)
#define RIGHT_COUNT_TIME (10)
#define LEFT_COUNT_TIME (10)
#define TRAVEL_DISTANCE (10)
#define WAITING2START (50)

// Run Circle
#define WHEEL_COUNT_TIME_C  (45)
#define RIGHT_COUNT_TIME_C  (45)
#define LEFT_COUNT_TIME_C   (15)
#define TRAVEL_DISTANCE_C   (60)

// Run Triangle
#define WHEEL_COUNT_TIME_T  (15)//previous 10
#define RIGHT_COUNT_TIME_T  (0) //previous 0
#define LEFT_COUNT_TIME_T   (9)
#define TURN_DISTANCE_T     (18)// previous 40
#define TRAVEL_DISTANCE_T   (17) // previous 15

// Run Figure 8
#define WHEEL_COUNT_TIME_8  (30) // 30
#define RIGHT_COUNT_TIME_8  (30) //30 works
#define LEFT_COUNT_TIME_8   (4) // 5 worked
#define TRAVEL_DISTANCE_8   (35) //30 worked

// Port 3 configuration
#define USE_GPIO   (0x00)
#define USE_SMCLK  (0x01)

// New SMCLK frequency
#define SMCLK_500KHZ (500000)



#define PRESSED (0)
#define RELEASED (1)

#define OKAY (1)
#define NOT_OKAY (0)

#define DEBOUNCE_RESTART (0)
#define  DEBOUNCE_TIME (100)

// Project 5
#define TIMER_B0_CCR0_VECTOR TIMER0_B0_VECTOR
#define TIMER_B0_CCR1_2_OV_VECTOR TIMER0_B1_VECTOR
#define TIMER_B1_CCR0_VECTOR TIMER1_B0_VECTOR
#define TIMER_B1_CCR1_2_OV_VECTOR TIMER1_B1_VECTOR
#define TIMER_B2_CCR0_VECTOR TIMER2_B0_VECTOR
#define TIMER_B2_CCR1_2_OV_VECTOR TIMER2_B1_VECTOR
#define TIMER_B3_CCR0_VECTOR TIMER3_B0_VECTOR
#define TIMER_B3_CCR1_2_OV_VECTOR TIMER3_B1_VECTOR

#define PWM_PERIOD (TB3CCR0)
#define LEFT_FORWARD_SPEED (TB3CCR1)
#define RIGHT_FORWARD_SPEED (TB3CCR2)
#define LEFT_REVERSE_SPEED (TB3CCR3)
#define RIGHT_REVERSE_SPEED (TB3CCR4)
#define LCD_BACKLITE_DIMING (TB3CCR5)

#define TB0CCR0_INTERVAL (2500)
#define TB0CCR1_INTERVAL (2500)
#define TB0CCR2_INTERVAL (2500)

#endif /* MACROS_H_ */
