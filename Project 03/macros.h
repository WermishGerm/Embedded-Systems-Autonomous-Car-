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

#endif /* MACROS_H_ */
