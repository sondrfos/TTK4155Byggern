/*
 * spi.c
 *
 * Created: 12.10.2016 13:23:55
 *  Author: sondrfos
 */ 
#include <avr/io.h>
#include "bit.h"

void spi_init(void){
	set_bit(DDRB, DDB4);	//SS = output
	set_bit(DDRB, DDB5);	//MOSI = output
	clear_bit(DDRB, DDB6);	//MISO = input
	set_bit(PORTB, PORTB6);	//MISO = pull-up
	set_bit(DDRB, DDB7);	//SCK = output

	set_bit(SPCR, SPE);		//Enables SPI	
	set_bit(SPCR, SPR0);	//clock rate fck/16
	set_bit(PORTB, PB4);	//set SS high
	set_bit(SPCR, MSTR);	//sets MCU as master
	
}

uint8_t spi_transmit(uint8_t cData){
	SPDR = cData;							//transmit data
	
	loop_until_bit_is_set( SPSR, SPIF );	//wait until transmit flag is set
	
	return SPDR;
}

void spi_select (){
	clear_bit(PORTB, PB4);
}

void spi_deselect(){
	set_bit(PORTB, PB4);
}

