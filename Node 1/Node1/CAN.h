/*
 * CAN.h
 *
 * Created: 19.10.2016 11:40:46
 *  Author: jeandres
 */ 
#include "mfcard.h"

#ifndef CAN_H_
#define CAN_H_



typedef struct {
	uint16_t ID;
	uint8_t length;
	uint8_t data[8];
}CAN_message;


void CAN_init();
void CAN_send(CAN_message message);
void CAN_receive(uint8_t adr, CAN_message* received);
void CAN_sendgame(Joy_pos_store joystick, uint8_t gametype);


#endif /* CAN_H_ */