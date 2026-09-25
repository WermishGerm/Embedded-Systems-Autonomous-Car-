#ifndef MACROS_H_
#define MACROS_H_

// ============================================================================
// GENERAL
// ============================================================================
#define TRUE            1
#define FALSE           0
#define ALWAYS          1
#define RESET_STATE     0

#define FOURTH          4
#define ELEVENTH        11

// ============================================================================
// DELAYS
// ============================================================================
#define ONE_SECOND      200
#define TWO_SECONDS     400
#define THREE_SECONDS   600
#define FOUR_SECONDS    800
#define FIVE_SECONDS    1000

// ============================================================================
// PROJECT 7 — STATE MACHINE CONSTANTS
// (WAIT, DRIVE, SPIN ALIGN, REVERSE, NAV, ETC.)
// ============================================================================
#define WAIT_STATE_NUM          1
#define DRIVE_STATE             2
#define SPIN_BLACK_LINE_STATE   3
#define REVERSE_STATE_NUM       5
#define NAVIGATION_STATE        6
#define SPIN_CENTER_STATE       7
#define DRIVE_CENTER_STATE      8

// ============================================================================
// PROJECT 7 — BLACK LINE SYSTEM
// ============================================================================
#define LEFT_BLACK_THRESH       2000
#define RIGHT_BLACK_THRESH      2000

#define SEARCH                  5
#define STOP                    6
#define SECR                    7
#define STOPALL                 8

#define DELAY_START_TICKS       100
#define DETECT_WAIT_TICKS       300
#define TB1_1SEC                100

// ============================================================================
// ADC
// ============================================================================
#define VLEFT_AVERAGE     return_vleft_average()
#define VRIGHT_AVERAGE    return_vright_average()

// ============================================================================
// NAVIGATION (Proj 7 correction controller)
// ============================================================================
#define MIN_SPEED           0
#define MAX_SPEED_NAV       5000
#define BLACK_LINE_VALUE    621
#define WHITE_VALUE_MAX     150
#define OFF_SPEED           1600
#define RECOVERY_TIME       150
#define KP                  25

#define WHITE_STATE         0
#define LEFT_STATE          1
#define RIGHT_STATE         2
#define LINE_STATE          3

// ============================================================================
// TIMER CONSTANTS
// ============================================================================
#define MAX_SCREEN_CLOCK_VALUE 9998

#define TB0CCR0_INTERVAL   (2500)
#define TB0CCR1_INTERVAL   (2500)
#define TB0CCR2_INTERVAL   (2500)

#define TB1CCR0_INTERVAL   4096
#define TB1CCR1_INTERVAL   4000
#define TB1CCR2_INTERVAL   819

#define TB2CCR1_INTERVAL   (4000)

#define TIMER_B0_CCR0_VECTOR        TIMER0_B0_VECTOR
#define TIMER_B0_CCR1_2_OV_VECTOR   TIMER0_B1_VECTOR
#define TIMER_B1_CCR0_VECTOR        TIMER1_B0_VECTOR
#define TIMER_B1_CCR1_2_OV_VECTOR   TIMER1_B1_VECTOR
#define TIMER_B2_CCR0_VECTOR        TIMER2_B0_VECTOR
#define TIMER_B2_CCR1_2_OV_VECTOR   TIMER2_B1_VECTOR
#define TIMER_B3_CCR0_VECTOR        TIMER3_B0_VECTOR
#define TIMER_B3_CCR1_2_OV_VECTOR   TIMER3_B1_VECTOR

// ============================================================================
// PROJECT 7 — DRIVE CONSTANTS
// ============================================================================
#define FORWARD         1
#define REVERSE         0
#define CHANGE_COUNT    5
#define MAX_SPEED       10000

#define WHEEL_PERIOD    10000
#define WHEEL_OFF       0

// ============================================================================
// LCD
// ============================================================================
#define LINE1 0
#define LINE2 1
#define LINE3 2
#define LINE4 3

#define MAX_LCD_LENGTH 11

#define LCD_OFF     (P6OUT &= ~LCD_BACKLITE)
#define LCD_ON      (P6OUT |=  LCD_BACKLITE)
#define LCD_TOGGLE  (P6OUT ^=  LCD_BACKLITE)

#define LCD_BACKLITE_DIMING   (TB3CCR5)

// ============================================================================
// SWITCHES
// ============================================================================
#define SWITCH_RESET_TIME 20
#define PRESSED   0
#define RELEASED  1

// ============================================================================
// SHAPE ENGINE (Project 9 movement_state.c)
// ============================================================================
#define NONE       'N'
#define STRAIGHT   'L'
#define CIRCLE     'C'
#define TRIANGLE   'T'
#define FIGURE8    'F'
#define WAIT       'W'
#define START      'S'
#define RUN        'R'
#define END        'E'

#define WHEEL_COUNT_TIME   20
#define RIGHT_COUNT_TIME   10
#define LEFT_COUNT_TIME    10
#define TRAVEL_DISTANCE    10
#define WAITING2START      50

// Circle shape
#define WHEEL_COUNT_TIME_C   45
#define RIGHT_COUNT_TIME_C   45
#define LEFT_COUNT_TIME_C    15
#define TRAVEL_DISTANCE_C    60

// Triangle shape
#define WHEEL_COUNT_TIME_T   15
#define RIGHT_COUNT_TIME_T   0
#define LEFT_COUNT_TIME_T    9
#define TURN_DISTANCE_T      18
#define TRAVEL_DISTANCE_T    17

// Figure 8
#define WHEEL_COUNT_TIME_8   30
#define RIGHT_COUNT_TIME_8   30
#define LEFT_COUNT_TIME_8    4
#define TRAVEL_DISTANCE_8    35

// ============================================================================
// UART BAUD
// ============================================================================
#define BAUD_9600     0
#define BAUD_115200   1

// ============================================================================
// PROJECT 9 — PWM CONTROL CONSTANTS
// ============================================================================
#define PWM_PERIOD      10000
#define PWM_SPEED       5500

#define TURN_90_MS      900
#define TURN_45_MS      450

#define FORWARD_MS(v)   ((v) * 1000)
#define BACKWARD_MS(v)  ((v) * 1000)

// ============================================================================
// MOVE QUEUE
// ============================================================================
#define MOVE_QUEUE_SIZE 8

typedef struct {
    char direction;
    uint16_t value;
} MoveCmd;

// ============================================================================
// GLOBAL EXTERNS
// ============================================================================
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern unsigned int ADC_Thumb;

extern volatile unsigned char adc_stage;
extern volatile unsigned int check_line_flag;

extern volatile unsigned int timer_counter;
extern volatile unsigned int LCD_counter;
extern unsigned int delay_start;

// State machine globals
extern unsigned char state;
extern unsigned int time_change;
extern unsigned int segment_count;
extern unsigned int right_motor_count;
extern unsigned int left_motor_count;
extern unsigned int cycle_time;
extern unsigned char event;
extern unsigned char side_count;
extern unsigned char turning;
extern unsigned char loop_side;

// UART buffers
extern volatile char pc_to_iot[128];
extern volatile char iot_to_pc[128];
extern volatile uint16_t pc_iot_head;
extern volatile uint16_t pc_iot_tail;
extern volatile uint16_t iot_pc_head;
extern volatile uint16_t iot_pc_tail;

// WiFi buffer
extern char wifi_rx_buffer[256];
extern uint16_t wifi_rx_index;

// LCD update flags
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;

// LCD lines
extern char display_line[4][11];

// ============================================================================
// PWM REGISTERS (TB3)
// ============================================================================
#define LEFT_FORWARD_SPEED     (TB3CCR1)
#define RIGHT_FORWARD_SPEED    (TB3CCR2)
#define LEFT_REVERSE_SPEED     (TB3CCR3)
#define RIGHT_REVERSE_SPEED    (TB3CCR4)

// ============================================================================
// CLOCK
// ============================================================================
#define MCLK_FREQ_MHZ   8

#endif // MACROS_H_
