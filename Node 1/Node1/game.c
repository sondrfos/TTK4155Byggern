/*
 * game.c
 *
 * Created: 20.11.2016 13:44:51
 *  Author: jeandres
 */ 

#include <util/delay.h>
#include "menu.h"
#include "mfcard.h"
#include "game.h"
#include "oled.h"
#include "MCP2515_adresses.h"
#include "CAN.h"
#include "test_functions.h"
#include <avr/interrupt.h>

#define F_CPU 4915200

volatile uint8_t mcp_intr = 0;


void game_statemachine(){
	uint8_t cursor = 0;
	uint8_t move_ready = 1;
	State state = PRINTMENU;
	uint8_t printing = 0;
	uint8_t score = 0;
	Menu mainMenu;
	Menu playGame;
	Menu game1;
	Menu game2;
	Menu game1info;
	Menu game2info;
	Menu* currentMenu = &mainMenu;
	menu_make(&mainMenu, &playGame, &game1info, &game2info, &game1, &game2);
	CAN_message recieved;
	while(1){
		switch (state) {
			case PRINTMENU:
				menu_print(*currentMenu, cursor);
				state = MAINMENU;
			case MAINMENU:
				if(mfcard_joy_dir() == NEUTRAL){
					move_ready = 1;
				}
				else if(mfcard_joy_dir() == UP && move_ready){
					if (cursor == 0){cursor = currentMenu->selectionLength-1;}
					else{cursor -= 1;}
					state = PRINTMENU;
					move_ready = 0;
				}
				else if(mfcard_joy_dir() == DOWN && move_ready){
					if (cursor == currentMenu->selectionLength-1){cursor = 0;}
					else{cursor += 1;}
					state = PRINTMENU;
					move_ready = 0;
				}
				if(mfcard_joy_button()){
					currentMenu = currentMenu->subMenu[cursor];
					if(currentMenu->state != ZERO){
						state = currentMenu->state;
					}
					else{
						cursor = 0;
						state = PRINTMENU;
						while(mfcard_joy_button()){}
					}
				}
				break;
			case GAME1:
				printing = oled_print_game(printing, state);
				CAN_sendgame(mfcard_joy_pos(), 0);
				if(mcp_intr&0b00000010){
					state = LOST;
					printing = 0;
				}
				break;
			case GAME2:
				printing = oled_print_game(printing, state);
				CAN_sendgame(mfcard_joy_pos(), 1);
				if(mcp_intr&0b00000010){
					state = LOST;
					printing = 0;
				}
				break;
			case LOST:
				printing = oled_lost(printing);
				if(mfcard_joy_button()){
					while(mfcard_joy_button()){}
						CAN_sendgame(mfcard_joy_pos(), 0);
						currentMenu = &mainMenu;
						state = PRINTMENU;
						printing = 0;
				}
				break;
			default:
				break;
		}
	}
	
}

ISR(INT1_vect){
	mcp_intr = mcp2515_read(MCP_CANINTF);						//reads interrupt register into global variable mcp_intr to determine what's going on
	mcp2515_bit_modify(MCP_CANINTF, 0b11111111, 0b00000000);	//clears interrupt flags
}