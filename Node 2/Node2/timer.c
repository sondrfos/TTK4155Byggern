/*
 * timer.c
 *
 * Created: 09.11.2016 09:49:55
 *  Author: jeandres
 */
#include "bit.h"

#include <avr/io.h>
#define F_CLOCK	 16000000
#define PRESCALER_PWM 8
#define PRESCALER_CTC 1024
#define T_MAX_PWM 0.02
#define T_MAX_CTC 0.01
#define T_MAX_SCORE 1
#define TOP_PWM F_CLOCK*T_MAX_PWM/PRESCALER_PWM
#define TOP_CTC F_CLOCK*T_MAX_CTC/PRESCALER_CTC
#define TOP_SCORE F_CLOCK*T_MAX_SCORE/PRESCALER_CTC

 
void timer_pwm_init(){
	clear_bit(TCCR1A,WGM10);
	set_bit(TCCR1A,WGM11);
	set_bit(TCCR1B,WGM12);
	set_bit(TCCR1B,WGM13);		//Setting the timer/counter to fast PWM mode
	
	ICR1 = TOP_PWM;				//sets top for interrupt every 20ms
	
	clear_bit(TCCR1B,CS10);
	set_bit(TCCR1B,CS11);
	clear_bit(TCCR1B,CS12);		// Setting the clock source to clk_T2S/8	

	clear_bit(TCCR1A,COM1A0);
	set_bit(TCCR1A,COM1A1);		//Setting to compare output mode
	
	set_bit(DDRB, DDB5);		//sets PIN11 for output for the PWM signal
}

void timer_PID_init(){
	clear_bit(TCCR3A,WGM30);
	clear_bit(TCCR3A,WGM31);
	set_bit(TCCR3B,WGM32);
	clear_bit(TCCR3B,WGM33);	//Setting the timer/counter to CTC mode
		
	OCR3A = TOP_CTC;
		
	set_bit(TCCR3B,CS30);
	clear_bit(TCCR3B,CS31);
	set_bit(TCCR3B,CS32);		// Setting the clock source to clk_T2S/1024
	
	set_bit(TIMSK3, OCIE3A);		//Enables interrupt on timer 3 
}

void timer_PID_disable(){
	clear_bit(TIMSK3, OCIE3A);		//disables interrupt
}



void timer_pwm_send_message(char d,uint8_t invert){
	if (d>100){
		d=100;
	}
	if(d<0){
		d=0;
	}
	if (invert){
		
		d = (d-100)*-1;
	}
	double a = (((double)d/100.0)*1.2+0.9)/(T_MAX_PWM*1000.0);

	OCR1A = floor(a*TOP_PWM); 
}

