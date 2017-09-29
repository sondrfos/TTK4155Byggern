/*
 * display.h
 *
 * Created: 21.09.2016 10:36:20
 *  Author: sondrfos
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_
#include<stdio.h>
#pragma once

void write_c(uint8_t adr);
void write_d(uint8_t b);

uint8_t oled_print_game(uint8_t printing, uint8_t state);
uint8_t oled_lost(uint8_t printing);
void oled_reset();
void oled_home(); 
void oled_goto_line(unsigned char line);
void oled_goto_column(unsigned char column);
void oled_clear_line(unsigned char line); 
void oled_pos(unsigned char line, unsigned char column);
void oled_print4x6(char letter);
void oled_print8x8(char letter);
void oled_init();

int oled_print8x8_stream(char letter,FILE *stream);

static FILE oled_stream_font8 = FDEV_SETUP_STREAM(oled_print8x8_stream,NULL,_FDEV_SETUP_WRITE);
#define FONT8 (&oled_stream_font8)



#endif /* DISPLAY_H_ */
