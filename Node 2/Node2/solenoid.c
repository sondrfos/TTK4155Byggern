/*
 * solenoid.c
 *
 * Created: 17.11.2016 11:16:44
 *  Author: jeandres
 */ 

#define F_CPU 16000000
#include "bit.h"
#include <avr/io.h>
#include <util/delay.h>


void solenoid_init(){
	set_bit(DDRF, DDF1);
	set_bit(PORTF, PORTF1);
}
void solenoid_punch(){
	clear_bit(PORTF, PORTF1);
	_delay_ms(70);
	set_bit(PORTF, PORTF1);

}
