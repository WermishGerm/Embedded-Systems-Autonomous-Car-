///*
// * usci.c
// *
// *  Created on: Dec 6, 2025
// *      Author: jcont
// */
//
//
//
//
//// usci.c – DISABLED FOR PROJECT 8 (Serial Mode uses serial.c instead)
//
//#include "msp430.h"
//#include "functions.h"
//#include "macros.h"
//#include "LCD.h"
//#include "ports.h"
//
//// -----------------------------------------------------------
//// EVERYTHING BELOW IS COMMENTED OUT FOR PROJECT 8
//// This file normally handles WiFi (Project 9) via UCA0/UCA1
//// but Project 8 uses ONLY UCA0 for AD2 serial in serial.c
//// -----------------------------------------------------------
//
//// ----------------- COMMENT OUT ALL BUFFERS ------------------
//// (kept for compatibility in Project 9)
//
//volatile unsigned int usb_rx_ring_wr;
//volatile unsigned int usb_rx_ring_rd;
//
//volatile char USB_Char_Rx[SMALL_RING_SIZE];
//volatile char USB_Char_Tx[SMALL_RING_SIZE];
//
//volatile unsigned int usb_tx_ring_wr;
//volatile unsigned int usb_tx_ring_rd;
//
//volatile unsigned char IOT_2_PC[LARGE_RING_SIZE];
//volatile unsigned int iot_rx_wr;
//unsigned int iot_rx_rd;
//unsigned int direct_iot;
//
//volatile unsigned char PC_2_IOT[LARGE_RING_SIZE];
//volatile unsigned int usb_rx_wr;
//unsigned int usb_rx_rd;
//unsigned int direct_usb;
//
//unsigned char cmd;
//char prev_usb;
//
//// These variables are unused in Project 8 but retained:
//volatile unsigned char Process_Buff[100];
//unsigned int character;
//unsigned int nextline;
//unsigned int canTrans;
//unsigned int writeDisp;
//unsigned int IOT_ON;
//
//extern volatile unsigned int timer_200ms;
//extern unsigned int dummy;
//extern volatile unsigned int command_executing;
//
//// -----------------------------------------------------------
//// DISABLE UCA0 ISR — serial.c implements UCA0 ISR for Project 8
//// -----------------------------------------------------------
////#pragma vector = EUSCI_A0_VECTOR
////__interrupt void eUSCI_A0_ISR(void) {
////    // Project 8: DO NOTHING
////    // UCA0 RX/TX handled in serial.c
////}
////
////// -----------------------------------------------------------
////// DISABLE UCA1 ISR — Not used in Project 8
////// -----------------------------------------------------------
////#pragma vector = EUSCI_A1_VECTOR
////__interrupt void eUSCI_A1_ISR(void) {
////    // Project 8: DO NOTHING
////}
//
//// -----------------------------------------------------------
//// ALL WiFi AT COMMAND ENGINE DISABLED
//// -----------------------------------------------------------
//void commands(void) {
//    // UNAVAILABLE FOR PROJECT 8
//}
//
//void IOT_Process(void) {
//    // UNAVAILABLE FOR PROJECT 8
//}
//
//void send_at_command(char *command) { }
//void process_at_commands(void) { }
//
