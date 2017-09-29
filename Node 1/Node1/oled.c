/*
 * display.c
 *
 * Created: 21.09.2016 10:36:07
 *  Author: sondrfos
 */ 
#include "font.h"
#include "bit.h"
#include "oled.h"
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>


void write_c(uint8_t adr){
	volatile char *ext_oled = (char *) 0x1000;
	ext_oled[0] = adr;
}
void write_d(uint8_t adr){
	volatile char *ext_oled = (char *) 0x1200;
	
	ext_oled[0] = adr;
}

uint8_t oled_print_game(uint8_t printing, uint8_t state){
	if (!printing && state == 3 ){
		oled_reset();
		oled_goto_line(0);
		oled_goto_column(5);
		fprintf(FONT8, "Game 1 running!");
	}
	if (!printing && state == 4){
		oled_reset();
		oled_goto_line(0);
		oled_goto_column(5);
		fprintf(FONT8, "Game 2 running!");
	}
	return 1;
	
}

uint8_t oled_lost(uint8_t printing){
	if (!printing){
		oled_reset();
		oled_goto_line(4);
		oled_goto_column(30);
		fprintf(FONT8, "You lost");
	}
	return 1;	
}

void oled_reset(){
	for (uint8_t i = 0; i<8;i++){
		oled_clear_line(i);
	}
	oled_home();
	
}

void oled_home(){
	oled_pos(0,0);
}

void oled_goto_line(uint8_t line){
	current_line = line;
	write_c(0xb0+line);
}

void oled_goto_column(uint8_t column){
	current_column = column;
	write_c(0x00+column%16);
	write_c(0x10+column/16);
}

void oled_clear_line(uint8_t line){
	oled_goto_line(line);
	for(uint8_t i = 0; i<128;i++){
		write_d(0x0);
	}
}

void oled_pos(uint8_t line, uint8_t column){
	current_column = column;
	current_line = line;
	oled_goto_line(line);
	oled_goto_column(column);
}

void oled_print4x6(char letter){
	letter = letter-32;
	
	for(uint8_t i = 3; i>=0;i--){
		write_d(pgm_read_byte(&font4x6[letter][i]));
	}
}

void oled_print8x8(char letter){
	letter = letter-32;
	
	for(uint8_t i = 0; i<8;i++){
		write_d(pgm_read_byte(&font8x8[letter][i]));
		if (current_column >127){
			current_column = 0;
		}
		else{
			current_column = current_column+1;
		}
	}
}

int oled_print8x8_stream(char letter,FILE *stream){
	letter = letter-32;
	
	for(uint8_t i = 0; i<8;i++){
		write_d(pgm_read_byte(&font8x8[letter][i]));
		if (current_column >127){
			current_column = 0;
		}
		else{
			current_column = current_column+1;
		}
	}
	return 0;
}

void oled_init(){
	write_c(0xae); // display off
	write_c(0xa1); //segment remap
	write_c(0xda); //common pads hardware: alternative
	write_c(0x12);
	write_c(0xc8); //common output scan direction:com63~com0
	write_c(0xa8); //multiplex ration mode:63
	write_c(0x3f);
	write_c(0xd5); //display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81); //contrast control
	write_c(0x50);
	write_c(0xd9); //set pre-charge period
	write_c(0x21);
	write_c(0x20); //Set Memory Addressing Mode
	write_c(0x02);
	write_c(0xdb); //VCOM deselect level mode
	write_c(0x30);
	write_c(0xad); //master configuration
	write_c(0x00);
	write_c(0xa4); //out follows RAM content
	write_c(0xa6); //set normal display
	write_c(0xaf); // display on
	
	oled_home();
	oled_reset();
}

