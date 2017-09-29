/*
 * motor_control.c
 *
 * Created: 09.11.2016 09:45:29
 *  Author: jeandres
 */ 


#define F_CPU 16000000
#include "bit.h"
#include "TWI_Master.h"
#include <avr/io.h>
#include <util/delay.h>

static int16_t max = 0;
static int16_t reference = 0;
static int16_t pos = 0;
static int32_t sumError = 0;
static int32_t last_pos = 0;

void motor_init(){
	set_bit(DDRH,DDH4);
	set_bit(DDRH,DDH1);				//makes the pins connected to the motorbox output pins			
	set_bit(PORTH, PORTH4);			//Enables the motorbox
	clear_bit(PORTH,PORTH1);		//sets the motor direction
	
}

void motor_speed(uint8_t speed){
	char	mes[3] = {0b01011110,0b00000000,0};		//make message containing address to the DAC and command
		
	if(speed >52){
		set_bit(PORTH,PORTH1);						//set direction by pulling DIR high
		mes[2] = ((255*(speed-50))/100)+10;			//calculate digital voltage value
	}
	
	else if (speed <48){
		clear_bit(PORTH,PORTH1);					//set direction by pulling DIR low
		mes[2] =  ((255*(50-speed))/100)+10;		//calculate digital voltage value
	}
	
	else{mes[2] = 0;}								//no speed for joystick output between 48 and 52
		
	TWI_Start_Transceiver_With_Data(mes, 3);		//transmit over I2C
}

void motor_PIDcntrl(){

	uint8_t Kp = 1;
	double Ki = 0.3;
	double Kd = 1;
	
	int16_t wind_up = 5000;
	int16_t saturation = 5000;
	pos = motor_encoder_read();
	
	int32_t posError = reference-pos;
	sumError += posError;
	int32_t derivative = pos-last_pos;
	last_pos = pos;
	
	if(sumError>wind_up){sumError = wind_up;}
	if(sumError<-wind_up){sumError = -wind_up;}
	
	int32_t u = Kp*posError + Ki*sumError + Kd*derivative;
	
	if(u>saturation){u = saturation;}
	if(u<-saturation){u = -saturation;}
	
	motor_speed(((u/100)+50));
} 

void motor_set_reference(double ref){
	ref= ref/100;
	reference = ref*max;				//scales the reference to the encoder output;
}

void motor_encoder_enable(uint8_t enable){
	set_bit(DDRH,DDH5);							//sets data direction of OE
	if(enable){clear_bit(PORTH,PORTH5);}		//enables the decoder by pulling OE low
	else{set_bit(PORTH, PORTH5);}				//disables encoder by setting OE high
}
int16_t motor_encoder_calib(){
	motor_speed(95);
	_delay_ms(10);
	int16_t last_encoder = motor_encoder_read();
	printf("%i \n", last_encoder);
	while(motor_encoder_read() != last_encoder){
		_delay_ms(10);
		last_encoder = motor_encoder_read();
		printf("%i \n", last_encoder);
	}
	motor_encoder_reset();
	motor_speed(50);
	_delay_ms(200);
	motor_speed(5);
	_delay_ms(10);
	last_encoder = motor_encoder_read();
	printf("%i \n", last_encoder);
	while(motor_encoder_read() != last_encoder){				
		_delay_ms(10);
		last_encoder = motor_encoder_read();
		printf("%i \n", last_encoder);
	}
	max = -last_encoder;
	motor_encoder_reset();
	motor_speed(50);
	return max;
}
void motor_encoder_reset(){
	set_bit(DDRH,DDH6);				//sets data direction of RST
	clear_bit(PORTH,PORTH6);		//resets by pulling RST low
	_delay_us(20);
	set_bit(PORTH, PORTH6);			//sets RST high
}
int16_t motor_encoder_read(){
	motor_encoder_enable(1);		//enable encoder
	set_bit(DDRH, DDH3);			//sets data direction of SEL
	clear_bit(PORTH, PORTH3);		//pulls SEL low to get high bits
	_delay_us(20);					//wait 20 us
	int16_t data = (PINK<<8);		//loads high bits into data and left shifts 8 times
		
	set_bit(PORTH, PORTH3);			//sets SEL high to get low bits
	_delay_us(20);					//wait 20 us
	data += PINK;					//add the least significant byte
	motor_encoder_enable(0);		//Turns the encoder off
	
	return ((~data)+1);				//inverts the output
}
