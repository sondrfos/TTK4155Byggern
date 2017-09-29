/*
 * mfcard.h
 *
 * Created: 19.09.2016 16:41:03
 *  Author: jeandres
 */ 



#pragma once

typedef struct{
	unsigned char x;
	unsigned char y;
}Joy_pos_store;
typedef struct{
	unsigned char left;
	unsigned char right;
	}Slider_pos_store;
typedef struct{
	char left;
	char right;
	}Button_press_store;
typedef enum Direction{NEUTRAL,UP,DOWN,LEFT,RIGHT,UNDEFINED} Direction;

void mfcard_interrupt_init(void);
void mfcard_init(void);
char mfcard_joy_button(void);
Joy_pos_store mfcard_joy_pos(void);
Direction mfcard_joy_dir(void);
Slider_pos_store mfcard_slider_pos(void);
char mfcard_button_press(void);

