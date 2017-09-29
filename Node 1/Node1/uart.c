/*
 * uart.c
 *
 * Created: 31.08.2016 14:31:19
 *  Author: eiriaha
 */ 

#include <avr/io.h>




void uart_transmit(unsigned char data){
	loop_until_bit_is_set(UCSR0A, UDRE0);		//wait for empty transmit buffer
	UDR0 = data;								//puts data into buffer to be sendt
}

uint8_t uart_receive(void){
	loop_until_bit_is_set(UCSR0A, RXC0);		//wait for data to be recieved
	return UDR0;								// return received value
}

void uart_init(unsigned int ubrr){
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;				//sets baud rate = 9600bps
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);				//enable reciever and tranciever
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);// set frame format: 8 data bit, 2 stop bit
	
	fdevopen(&uart_transmit,&uart_receive);	//makes uart work as printf
}

