#include "msp430.h"
#include "functions.h"
#include "LCD.h"
#include "macros.h"

// ============================================================================
// LCD BUFFER
// ============================================================================
char display_line[4][11];
char *display[4];






// ============================================================================
// BLACKLINE / STATE FLAGS
// ============================================================================
volatile unsigned char run_project7 = 0;

// ============================================================================
// UART RING BUFFERS
// ============================================================================
volatile char pc_to_iot[128];
volatile char iot_to_pc[128];



// ============================================================================
// WIFI BUFFER
// ============================================================================
char wifi_rx_buffer[256];
unsigned int wifi_rx_index = 0;

// ============================================================================
// SHAPE ENGINE VARIABLES (Project 7 legacy states)
// ============================================================================
unsigned char state          = 0;
unsigned int time_change     = 0;
unsigned int segment_count   = 0;
unsigned int right_motor_count = 0;
unsigned int left_motor_count  = 0;
unsigned int cycle_time        = 0;
unsigned char event            = 0;
unsigned char side_count       = 0;
unsigned char turning          = 0;
unsigned char loop_side        = 0;

// ============================================================================
// MOVEMENT QUEUE (used by movement.c)
// ============================================================================
MoveCmd move_queue[MOVE_QUEUE_SIZE];
uint8_t move_q_head = 0;
uint8_t move_q_tail = 0;
