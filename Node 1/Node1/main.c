/*
 * Hovedoppgave.c
 *
 * Created: 31.08.2016 14:30:56
 *  Author: eiriaha
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "uart.h"
#include "sram.h"
#include "mfcard.h"
#include "bit.h"
#include "menu.h"
#include "mcp2515.h"
#include "CAN.h"
#include "MCP2515_adresses.h"



#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#define SIZEOF(a) (sizeof(a)/sizeof((a)[0]))


volatile uint8_t button_pressed = 0;
//volatile uint8_t mcp_intr = 0;


int main(void){
	uart_init(MYUBRR);
	sram_init();
	oled_init();
	mfcard_init();
	mfcard_interrupt_init();
	spi_init();
	CAN_init();
	solenoid_init();
	while(1){
		game_statemachine();
	}
	
	/*while(1){
		CAN_joystick(mfcard_joy_pos());
		printf("I'm sending some shit niggah  \n");
		BUTTON_PRESSED = 0;
	}
	
	CAN_message duta = {128, 7, {3, 2, 3, 7, 6, 3, 8}};
	while(1){	
		if (MCP_INTR){
			CAN_message received;
			CAN_receive(MCP_RXB1D0, &received);
			printf("Data:");
			for(int i = 0; i<received.length; i++){
				printf(" %i", received.data[i]);
			}
			printf("\nLength: %i    ID: %i\n \n", received.length, received.ID);
			MCP_INTR = 0;
		}
		//CAN_joystick(mfcard_joy_pos());
		CAN_send(duta);
		our_delay(1000);
	}*/
	/*our_delay(1000);
	CAN_message received = CAN_receive(MCP_RXB0D0);
	for(int i = 0; i<received.length; i++){
	printf("%i ", received.data[i]);
	}
	printf("Length: %i    ID: %i    \n", received.length, received.ID);


	CAN_send(duta2);
	our_delay(1000);
	CAN_message received2 = CAN_receive(MCP_RXB0D0);
	for(int i = 0; i<received2.length; i++){
	printf("%i ", received2.data[i]);
	}
	printf("Length: %i    ID: %i    \n", received2.length, received2.ID);
	printf("\n\nStartup complete\n\n");
	mcp2515_write(0b00101001, 0b01010101);
	while(1){
		
		uint8_t test = mcp2515_read(0b00101001);
		printf("%i \n \n", test);
		our_delay(1000);
		mcp2515_bit_modify(0b00101001, 0b10101010, 0b10101010);
		
	}
	Menu meny;
	meny.line_0="This is a call";
	meny.line_1="For the here";
	meny.line_2="And the now";
	meny.line_3="noe";
	meny.line_4="noe annet";
	meny.line_5="noe tredje";
	meny.line_6="yeah boi";
	meny.line_7="";
	
	char cursor_pos = 0;
	char just_moved = 0;
	char last_click = -1;
	menu_print(meny, cursor_pos);
	BUTTON_PRESSED = 0;

	while(1){
		if (BUTTON_PRESSED){
			meny.line_5=("Hval");
			menu_print(meny, cursor_pos);
			BUTTON_PRESSED = 0;
			last_click = cursor_pos;
			printf("%d",last_click);
		}
		Direction dir = mfcard_joy_dir();
		if (just_moved){
			if(dir == NEUTRAL){
				just_moved = 0;
			}
		}
		else if (!just_moved){
			char pos = menu_move_cursor(dir, cursor_pos);
			if(pos!=cursor_pos){
				cursor_pos = pos;
				just_moved=1;
			}
		}
	}*/	
}

ISR(INT2_vect){
	button_pressed = 1;
}

