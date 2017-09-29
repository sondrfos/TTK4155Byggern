/*
 * menu.c
 *
 * Created: 05.10.2016 13:19:43
 *  Author: jeandres
 */ 
#include "mfcard.h"
#include "oled.h"
#include "menu.h"
#include "game.h"
#include <stdint.h>
#include <avr/interrupt.h>

void menu_make(Menu* mainMenu, Menu* playGame, Menu* game1info, Menu* game2info, Menu* game1, Menu* game2){
	
	mainMenu->length = 2;
	mainMenu->selectionLength = 2;
	mainMenu->names[0] = "Play game!";
	mainMenu->names[1] = "Exit";

	
	
	playGame->length = 3;
	playGame->selectionLength = 3;
	playGame->names[0] = "Mode 1";
	playGame->names[1] = "Mode 2";
	playGame->names[2] = "Exit";
	mainMenu->subMenu[0] = playGame;

	
	playGame->subMenu[0] = game1info;
	playGame->subMenu[1] = game2info;
	playGame->subMenu[2] = mainMenu;
	
	game1info->length = 6;
	game1info->selectionLength = 2;
	game1info->names[0] = "Play game!";
	game1info->names[1] = "Exit";
	game1info->names[2] = " ";
	game1info->names[3] = "About: Control";
	game1info->names[4] = "the position";
	game1info->names[5] = "of the shooter";
	
	game1info->subMenu[2] = game1info;
	game1info->subMenu[3] = game1info;
	game1info->subMenu[4] = game1info;
	game1info->subMenu[0] = game1;
	game1info->subMenu[1] = playGame;
	
	game2info->length = 6;
	game2info->selectionLength = 2;
	game2info->names[0] = "Play game!";
	game2info->names[1] = "Exit";
	game2info->names[2] = " ";
	game2info->names[3] = "About: Control";
	game2info->names[4] = "the speed of";
	game2info->names[5] = "the shooter";
		
	game2info->subMenu[2] = game2info;
	game2info->subMenu[3] = game2info;
	game2info->subMenu[4] = game2info;
	game2info->subMenu[0] = game2;
	game2info->subMenu[1] = playGame;
	
	
	mainMenu->state = ZERO;
	playGame->state = ZERO;
	game1info->state = ZERO;
	game2info->state = ZERO;
	game1->state = GAME1;
	game2->state = GAME2;
	
}

uint8_t menu_move_cursor(Direction dir, uint8_t pos){
	if(dir == NEUTRAL || dir == UNDEFINED){
		return pos;
	}
	if(dir == DOWN){
		if (pos == 7){
			pos=0;
		}
		else{
			pos++;
		}
	}
	else if(dir == UP){
		if (pos == 0){
			pos=7;
		}
		else{
			pos--;
		}
	}
	menu_draw_cursor(pos);
	return pos;
}

void menu_draw_cursor(uint8_t line){
	for(uint8_t i = 0;i<8;i++){
		oled_pos(i,0);
		for(uint8_t k = 0;k<4;k++){
			write_d(0b0);
		}
	}
	oled_pos(line,0);
	write_d(0b01111100);
	write_d(0b00111000);
	write_d(0b00010000);	
}

void menu_print(Menu menu, uint8_t cursor_pos){
	oled_reset();
	for(int i = 0; i<menu.length; i++){
		oled_goto_line(i);
		oled_goto_column(5);
		fprintf(FONT8, menu.names[i]);
	}
	for(int i = menu.length; i<8; i++){
		oled_goto_line(i);
		oled_goto_column(5);
		fprintf(FONT8, " ");
	}
	menu_draw_cursor(cursor_pos);
}

