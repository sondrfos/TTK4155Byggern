/*
 * motor.h
 *
 * Created: 16.11.2016 11:04:40
 *  Author: jeandres
 */ 
#include "bit.h"
#include <avr/io.h>

#ifndef MOTOR_H_
#define MOTOR_H_

void motor_init();
int16_t motor_encoder_read();
int16_t motor_encoder_calib();
void motor_encoder_reset();
void motor_set_reference(double ref);
uint8_t motor_speed(uint8_t speed);
void motor_PIDcntrl();
#endif /* MOTOR_H_ */