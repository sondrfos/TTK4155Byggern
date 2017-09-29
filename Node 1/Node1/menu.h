/*
 * menu.h
 *
 * Created: 05.10.2016 13:19:57
 *  Author: jeandres
 */ 


#ifndef MENU_H_
#define MENU_H_
#include <stdint.h>
#include "game.h"


typedef struct{
	char* names[8];
	struct Menu* subMenu[8];
	uint8_t length;
	uint8_t selectionLength; 
	State state;
}Menu;

void menu_make(Menu* mainMenu, Menu* playGame, Menu* game1info, Menu* game2info, Menu* game1, Menu* game2);

uint8_t menu_move_cursor(uint8_t dir, uint8_t pos);
void menu_print(Menu menu, uint8_t cursor_pos);
void menu_draw_cursor(uint8_t line);
void menu_run(uint8_t *cursor, uint8_t *move_ready);





#endif /* MENU_H_ */