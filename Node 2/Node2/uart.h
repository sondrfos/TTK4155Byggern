/*
 * uart.h
 *
 * Created: 31.08.2016 14:31:35
 *  Author: eiriaha
 */ 

#include <avr/io.h>




#ifndef UART_H_
#define UART_H_


void uart_transmit(unsigned char data);
uint8_t uart_receive(void);
void uart_init(unsigned int ubrr);


#endif /* UART_H_ */