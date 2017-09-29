/*
 * timer.h
 *
 * Created: 09.11.2016 09:50:07
 *  Author: jeandres
 */ 


#ifndef TIMER_H_
#define TIMER_H_

void timer_pwn_init();
void timer_pwm_send_message(char a,uint8_t invert);
void timer_PID_init();
void timer_PID_disable();
void timer_score_init();


#endif /* TIMER_H_ */