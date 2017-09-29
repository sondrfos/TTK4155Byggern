/*
 * mfcard.c
 *
 * Created: 19.09.2016 16:33:58
 *  Author: jeandres
 */ 

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "mfcard.h"
#include "bit.h"

void mfcard_interrupt_init(void){
	cli();
	clear_bit(GICR, INT2); 
	clear_bit(EMCUCR,ISC2);		//Falling edge activates interrupt on INT2
	clear_bit(GIFR,INTF2);		//Makes the MCU jump to corresponding interrupt vector
	set_bit(MCUCR,ISC11);
	clear_bit(MCUCR,ISC10);		//Falling edge activates interrupt on INT1
	clear_bit(GIFR,INTF1);
	set_bit(MCUCR,ISC00);
	set_bit(MCUCR,ISC01);
	set_bit(GICR, INT2);		//INT2 enabled as interrupt
	set_bit(GICR, INT1);
	sei();
	//set_sleep_mode(SLEEP_MODE_PWR_SAVE);
}

void mfcard_init(void){
	clear_bit(DDRE, DDE0);		//sets joystick button pin to input
	set_bit(PORTE, PORTE0);		//enables pull up resistor
	clear_bit(DDRD, DDD2);
	
}
char mfcard_joy_button(void){
	return !test_bit(PINE, 0);
}	
Joy_pos_store mfcard_joy_pos(void){
	Joy_pos_store pos;
	volatile char *ext_ram = (char *) 0x1400;
	
	ext_ram[0] = 5;
	_delay_us(40);
	double x = (100*ext_ram[0])/255;
	pos.x = x;
	
	
	ext_ram[0] = 4;
	_delay_us(40);
	double y = (100*ext_ram[0])/255;
	pos.y = y;
	
	
	return pos;
}
Direction mfcard_joy_dir(void){
	Joy_pos_store pos=mfcard_joy_pos();
	
	int delta_x=pos.x-50;
	int delta_y=pos.y-50;
	
	if((abs(delta_x)<40)&&(abs(delta_y)<40)){
		return NEUTRAL;
	}
	
	if((abs(delta_x)<12)&&(abs(delta_y)<12)){
		return UNDEFINED;
	}
	
	if (abs(delta_x)>(abs(delta_y))){
		if(delta_x>0){
			return RIGHT;
		}
		else{
			return LEFT;
		}
	}
	else{
		if(delta_y>0){
			return UP;
		}
		else{
			return DOWN;
		}
	}

	
}
Slider_pos_store mfcard_slider_pos(void){
		Slider_pos_store pos;
		volatile char *ext_ram = (char *) 0x1400;
		
		ext_ram[0] = 6;
		_delay_us(40);
		double left = (100*ext_ram[0])/255;
		pos.left = left;
		
		
		ext_ram[0] = 7;
		_delay_us(40);
		double right = (100*ext_ram[0])/255;
		pos.right = right;
		
		return pos;
}
char mfcard_button_press(void){
	Button_press_store button;
	
	button.left = test_bit(PIND, PIND2);
	//button.right = 0;//test_bit(PIND, PIND2);
	
	return button.left;
}
