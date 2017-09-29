/*
 * CAN.c
 *
 * Created: 19.10.2016 11:40:33
 *  Author: jeandres
 */ 
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "bit.h"
#include "CAN.h"
#include "mcp2515.h"
#include "MCP2515_adresses.h"

void CAN_init(){
	cli();														//global disable interrupt
	mcp2515_reset();
	mcp2515_bit_modify(MCP_CANCTRL, 0b11110000, 0b00000000);	//cancrl set normal
	mcp2515_bit_modify(MCP_CANINTE, 0b10011111, 0b10011111);	//sets interrupts
													
	clear_bit(EIMSK, INT2);										//disable interrupt in pin 2
	clear_bit(EICRA, ISC21);									//
	clear_bit(EICRA, ISC20);									//interrupt on falling edge
	set_bit(EIMSK, INT2);										//enable interrupt on pin 2
	sei();														//global enable interrupt
}

void CAN_send(CAN_message message){
	for (uint8_t i = 0; i<message.length; i++){
		mcp2515_write(MCP_TXB0D0 + i, message.data[i]);			//writes data to transmit buffers
	}
	mcp2515_write(MCP_TXB0DLC, message.length);					//writes length to DLC register
	mcp2515_write(MCP_TXB0SIDH, message.ID >> 3);				//shifts ID 3 to right and writes to IDhigh
	mcp2515_write(MCP_TXB0SIDL, message.ID << 5);				// shifts ID 5 to left and writes to IDlow

	mcp2515_bit_modify(MCP_TXB0CTRL, 0b00001000, 0b00001000);	//request sending
}

void CAN_receive(uint8_t adr, CAN_message* received){
	received->length = 0b00001111 & mcp2515_read(adr-1);		//reads length from adr-1 and bitwise AND with value to mask out insignificant bits
	for (uint8_t i = 0; i<received->length; i++){
		received->data[i] = mcp2515_read(adr+i);				//reads data from dataregisters
	}
	uint16_t ID_low = ((mcp2515_read(adr-4)>>5) & 0b00000111);	//finds low bits by right-shifting register 5 places and bitwise AND to mask out insignificant bits
	uint16_t ID_high = mcp2515_read(adr-5)*8;					//reads high ID bits and left-shifts 3 places
	received->ID = ID_low+ID_high; 
	
}

void CAN_lost(){
	CAN_message msg;
	msg.ID = 2;
	msg.length = 1;
	msg.data[0] = 0;
	CAN_send(msg);	
};
