/*
 * game.h
 *
 * Created: 20.11.2016 13:45:16
 *  Author: jeandres
 */ 


#ifndef GAME_H_
#define GAME_H_

typedef enum {ZERO, PRINTMENU, MAINMENU, GAME1, GAME2, LOST} State;

void game_statemachine();



#endif /* GAME_H_ */