#ifndef SERIAL_H_
#define SERIAL_H_

#define BAUD_9600     0
#define BAUD_115200   1

void Init_Serial(void);
void Set_Baud(unsigned char rate);
void Serial_Process_RX(void);
void Transmit_Command(void);

extern volatile unsigned char baud_mode;     // Current baud rate
extern volatile unsigned char message_ready; // 10-char message received
extern volatile char rx_buffer[11];          // Holds received command

#endif
