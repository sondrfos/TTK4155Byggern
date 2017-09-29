/*
 * timer.c
 *
 * Created: 20.11.2016 22:34:23
 *  Author: jeandres
 */ 

#include <avr/io.h>

#define F_CPU 4915200
#define PRESCALER_CTC 1024
#define T_MAX 1
#define TOP_SCORE F_CPU*T_MAX/PRESCALER_CTC

void timer_score_init(){
	clear_bit(TCCR1A,WGM10);
	clear_bit(TCCR1A,WGM11);
	set_bit(TCCR1B,WGM12);
	clear_bit(TCCR1B,WGM13);		//Setting the timer/counter to CTC mode
	
	OCR1A = TOP_SCORE;
	
	set_bit(TCCR1B,CS10);
	clear_bit(TCCR1B,CS11);
	set_bit(TCCR1B,CS12);			// Setting the clock source to clk_T2S/1024
	
	set_bit(TIMSK, OCIE1A);		//Enables interrupt on timer 4
}