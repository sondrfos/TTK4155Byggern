/*
 * Node2.c
 *
 * Created: 26.10.2016 09:43:17
 *  Author: Hugh Mungus
 */ 

 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "spi.h"
#include "mcp2515.h"
#include "MCP2515_adresses.h"
#include "CAN.h"
#include "timer.h"
#include "adc.h"
#include "TWI_Master.h"
#include "solenoid.h"
#include "motor.h"

typedef enum {NOGAME, GAME1, GAME2, LOST} State;

#define F_CPU 16000000
#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
uint8_t mcp_intr = 0;
int16_t speed = 0;

int main(void){
	uint8_t IR = 0;
	uint8_t punching = 1;
	State state = NOGAME;
	uart_init(MYUBRR);
	spi_init();
	CAN_init();
	timer_pwm_init();
	adc_init();
	TWI_Master_Initialise();
	motor_init();
	solenoid_init();
	CAN_message recieved;
	while(1){
		switch (state){
			case NOGAME:
				if(mcp_intr){
					CAN_receive(MCP_RXB0D0, &recieved);
					if(recieved.data[3]){
						state = GAME2;
					}
					else if(recieved.data[3] == 0){
						state = GAME1;
						motor_encoder_reset();
						motor_encoder_calib();
						motor_set_reference(50);
						timer_PID_init();
					}
					mcp_intr = 0;
				}
				break;
			case GAME1:
				if (mcp_intr){
					CAN_receive(MCP_RXB0D0, &recieved);
					motor_set_reference(recieved.data[0]);
					timer_pwm_send_message(recieved.data[0],0);
					if (recieved.data[2] && !punching){
						solenoid_punch();
						punching = 1;
					}
					if(!recieved.data[2]){
						punching = 0;
					}						
					mcp_intr = 0;
				}
				/*if(adc_score(&IR)){
					state = LOST;
				}*/
				break;
			case GAME2:
				if (mcp_intr){
					CAN_receive(MCP_RXB0D0, &recieved);
					motor_speed(recieved.data[0]);
					timer_pwm_send_message(recieved.data[0],0);
					if (recieved.data[2] && !punching){
						solenoid_punch();
						punching = 1;
					}
					if(!recieved.data[2]){
						punching = 0;
					}
					mcp_intr = 0;
				}
				/*if(adc_score(&IR)){
					state = LOST;
				}*/
				break;
			case LOST:
				//CAN_lost();
				//state = GAME2;
				break;
			default:
				break;
		}
	}
}

ISR(INT2_vect){
	mcp_intr = mcp2515_read(MCP_CANINTF);						//reads interrupt register into global variable MCP_INTR to determine what's going on
	mcp2515_bit_modify(MCP_CANINTF, 0b11111111, 0b00000000);	//clears interrupt flags
}

ISR(TIMER3_COMPA_vect){
	motor_PIDcntrl();
}