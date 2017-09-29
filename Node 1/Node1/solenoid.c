/*
 * solenoid.c
 *
 * Created: 17.11.2016 11:16:44
 *  Author: jeandres
 */ 

#define F_CPU 4915200
#include "bit.h"
#include <avr/io.h>
#include <util/delay.h>


void solenoid_init(){
	set_bit(DDRD, DDD4);
	set_bit(PORTD, PORTD4);
}
void solenoid_punch(){
	clear_bit(PORTD, PORTD4);
	_delay_ms(100);
	set_bit(PORTD, PORTD4);
}
