/*
 * adc.c
 *
 * Created: 13.11.2016 10:59:20
 *  Author: sondrfos
 */ 

#include "bit.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void adc_init(){
	set_bit(ADCSRA, ADEN);		//ADC enable
	clear_bit(DDRF, DDF0);		//set PF0 as input
	set_bit(ADMUX, REFS0);	
	clear_bit(ADMUX, REFS1);		//set reference voltage  = 1.1 V
	clear_bit(ADMUX, MUX0);
	clear_bit(ADMUX, MUX1);
	clear_bit(ADMUX, MUX2);
	clear_bit(ADMUX, MUX3);
	clear_bit(ADMUX, MUX4);
	clear_bit(ADCSRB, MUX5);	//set ADC0 as input ADC pin
	set_bit(ADCSRA, ADPS0);
	set_bit(ADCSRA, ADPS1);
	set_bit(ADCSRA, ADPS2);		//set prescaler
	clear_bit(ADMUX, ADLAR);	//right shifted results
}

uint16_t adc_read(){
	set_bit(ADCSRA, ADSC);					//start conversion
	
	loop_until_bit_is_clear(ADCSRA, ADSC);	//loop until conversion finished
	
	return ADC;
}

uint8_t adc_score(uint8_t* IR){
	if (*IR == 0 && adc_read() < 30){
		*IR = 1;
		return 1;
	}
	else if(*IR == 1 && adc_read() < 30){
		return 0;
	}
	*IR = 0;
	return 0;
}