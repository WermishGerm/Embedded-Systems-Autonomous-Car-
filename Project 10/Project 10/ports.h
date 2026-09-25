#ifndef PORTS_H_
#define PORTS_H_

// ============================================================================
// PORT 1
// ============================================================================
#define RED_LED       (0x01)  // P1.0
#define A1_SEEED      (0x02)  // P1.1
#define V_DETECT_L    (0x04)  // P1.2 ADC
#define V_DETECT_R    (0x08)  // P1.3 ADC
#define A4_SEEED      (0x10)  // P1.4
#define V_THUMB       (0x20)  // P1.5 ADC
#define UCA0TXD       (0x40)  // P1.6 UART TX
#define UCA0RXD       (0x80)  // P1.7 UART RX

// ============================================================================
// PORT 2
// ============================================================================
#define SLOW_CLK      (0x01)  // P2.0
#define CHECK_BAT     (0x02)  // P2.1
#define IR_LED        (0x04)  // P2.2
#define SW2           (0x08)  // P2.3
#define IOT_RUN_CPU   (0x10)  // P2.4
#define DAC_ENB       (0x20)  // P2.5
#define LFXOUT        (0x40)  // P2.6
#define LFXIN         (0x80)  // P2.7

// ============================================================================
// PORT 3
// ============================================================================
#define TEST_PROBE    (0x01)  // P3.0
#define DAC_CTRL_2    (0x02)  // P3.1
#define OA2N          (0x04)  // P3.2
#define OA2P          (0x08)  // P3.3
#define SMCLK_OUT     (0x10)  // P3.4
#define DAC_CTRL_3    (0x20)  // P3.5
#define IOT_LINK_CPU  (0x40)  // P3.6
#define IOT_RN_CPU    (0x80)  // P3.7 ESP32 reset

// ============================================================================
// PORT 4
// ============================================================================
#define RESET_LCD     (0x01)  // P4.0
#define SW1           (0x02)  // P4.1
#define UCA1RXD       (0x04)  // P4.2 UART RX PC
#define UCA1TXD       (0x08)  // P4.3 UART TX PC
#define UCB1_CS_LCD   (0x10)  // P4.4 chip select LCD
#define UCB1CLK       (0x20)  // P4.5
#define UCB1SIMO      (0x40)  // P4.6
#define UCB1SOMI      (0x80)  // P4.7

// ============================================================================
// PORT 5
// ============================================================================
#define V_BAT         (0x01)  // P5.0 ADC
#define V_5           (0x02)  // P5.1 ADC
#define V_DAC         (0x04)  // P5.2 ADC
#define V3_3          (0x08)  // P5.3 ADC
#define IOT_BOOT_CPI  (0x10)  // P5.4

// ============================================================================
// PORT 6 — PWM MOTOR CONTROL (Project 9 engine, used by Project 7 behavior)
// ============================================================================
// TB3CCR1 → P6.0  (LEFT FORWARD PWM)
// TB3CCR2 → P6.1  (RIGHT FORWARD PWM)
// TB3CCR3 → P6.2  (LEFT REVERSE PWM)
// TB3CCR4 → P6.3  (RIGHT REVERSE PWM)

#define L_FORWARD     (0x01)  // P6.0
#define R_FORWARD     (0x02)  // P6.1
#define L_REVERSE     (0x04)  // P6.2
#define R_REVERSE     (0x08)  // P6.3

#define LCD_BACKLITE  (0x10)  // P6.4
#define P6_5          (0x20)  // P6.5 unused GPIO
#define GRN_LED       (0x40)  // P6.6

#endif
