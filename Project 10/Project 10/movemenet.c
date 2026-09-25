#include <stdint.h>
#include "msp430.h"
#include "functions.h"
#include "macros.h"
#include "ports.h"
#include "LCD.h"

// ============================================================================
// PWM SETUP
// ============================================================================
void movement_pwm_init(void) {

    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;
    TB3CCR0 = PWM_PERIOD;

    TB3CCTL1 = OUTMOD_7;   // Left forward
    TB3CCTL2 = OUTMOD_7;   // Right forward
    TB3CCTL3 = OUTMOD_7;   // Left reverse
    TB3CCTL4 = OUTMOD_7;   // Right reverse

    TB3CCTL5 = OUTMOD_7;   // LCD backlight

    P6SEL0 |= (L_FORWARD | R_FORWARD | L_REVERSE | R_REVERSE | LCD_BACKLITE);
    P6SEL1 &= ~(L_FORWARD | R_FORWARD | L_REVERSE | R_REVERSE | LCD_BACKLITE);

    LCD_BACKLITE_DIMING = 8000;
}

// ============================================================================
// INTERNAL WHEEL CONTROL
// ============================================================================
static void wheels_off(void) {
    LEFT_FORWARD_SPEED  = 0;
    RIGHT_FORWARD_SPEED = 0;
    LEFT_REVERSE_SPEED  = 0;
    RIGHT_REVERSE_SPEED = 0;
}

static void wheels_forward(uint16_t s) {
    LEFT_FORWARD_SPEED  = s;
    RIGHT_FORWARD_SPEED = s;
    LEFT_REVERSE_SPEED  = 0;
    RIGHT_REVERSE_SPEED = 0;
}

static void wheels_reverse(uint16_t s) {
    LEFT_FORWARD_SPEED  = 0;
    RIGHT_FORWARD_SPEED = 0;
    LEFT_REVERSE_SPEED  = s;
    RIGHT_REVERSE_SPEED = s;
}

static void wheels_left(uint16_t s) {
    LEFT_FORWARD_SPEED  = 0;
    RIGHT_FORWARD_SPEED = s;
    LEFT_REVERSE_SPEED  = s;
    RIGHT_REVERSE_SPEED = 0;
}

static void wheels_right(uint16_t s) {
    LEFT_FORWARD_SPEED  = s;
    RIGHT_FORWARD_SPEED = 0;
    LEFT_REVERSE_SPEED  = 0;
    RIGHT_REVERSE_SPEED = s;
}

// ============================================================================
// INIT + PERIODIC UPDATE
// ============================================================================
void movement_init(void) {
    wheels_off();
}

void movement_update(void) {
    // placeholder for queued/timed movement (unused in Project 10)
}

// ============================================================================
// COMMAND-BASED MOVEMENT (WiFi, UART, etc.)
// ============================================================================
void movement_execute_command(char dir, uint16_t value) {

    wheels_off();

    switch (dir) {

    case 'F':
        wheels_forward(PWM_SPEED);
        break;

    case 'B':
        wheels_reverse(PWM_SPEED);
        break;

    case 'L':
        wheels_left(PWM_SPEED);
        break;

    case 'R':
        wheels_right(PWM_SPEED);
        break;

    case 'S':
    case 'X':
    default:
        wheels_off();
        break;
    }

    movement_display_big(dir, value);
}

void movement_execute_string(char *cmd) {

    if (!cmd || !cmd[0]) return;

    char d = cmd[0];
    uint16_t v = 0;

    if (cmd[1])
        v = atoi(&cmd[1]);

    movement_execute_command(d, v);
}

// ============================================================================
// LCD FEEDBACK FOR MOVEMENT COMMANDS
// ============================================================================
void movement_display_big(char dir, uint16_t v) {

    char line[11];

    snprintf(line, sizeof(line), " Cmd:%c   ", dir);
    strcpy(display_line[0], line);

    snprintf(line, sizeof(line), " Val:%3u ", v);
    strcpy(display_line[1], line);

    strcpy(display_line[2], " Movement ");
    strcpy(display_line[3], " Active   ");

    display_changed = 1;
    update_display  = 1;
}

// ============================================================================
// LEGACY PROJECT 7 MOVEMENT API (now driven by PWM)
// ============================================================================
void stopall(void) {
    wheels_off();
}

void moveforward(void) {
    wheels_forward(PWM_SPEED);
}

void movereverse(void) {
    wheels_reverse(PWM_SPEED);
}

void spin_clockwise(void) {
    wheels_right(PWM_SPEED);
}

void spin_counterclockwise(void) {
    wheels_left(PWM_SPEED);
}
