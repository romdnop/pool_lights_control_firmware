#ifndef _UART_H
#define _UART_H

#define RX_BUFFER_SIZE        10
extern __IO uint8_t rx_buffer[RX_BUFFER_SIZE];
extern __IO uint8_t rx_byte_count;
extern uint8_t cmdReceived;

void UART_init(void);
void UART_SendByte(uint8_t data);
uint8_t UART_ReadByte(void);
void UART_SendString(uint8_t *string);
void UART_ReadString(uint8_t *string);
void UART_SetBaudrate(uint16_t);
#endif
