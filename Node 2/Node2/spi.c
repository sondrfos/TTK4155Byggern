/*
 * spi.c
 *
 * Created: 26.10.2016 10:19:14
 *  Author: sondrfos
 */ 

#include "bit.h"

#include <avr/io.h>

void spi_init(void){
	set_bit(DDRB, DDB0);	//SS = output
	set_bit(DDRB, DDB1);	//SCK = output
	set_bit(DDRB, DDB2);	//MOSI = output
	clear_bit(DDRB, DDB3);	//MISO = input
	set_bit(PORTB, PB3);	//MISO = pull-up
	set_bit(DDRB, DDB7);

	set_bit(SPCR, SPE);		//Enables SPI
	set_bit(SPCR, SPR0);	//clock rate fck/16
	set_bit(PORTB, PB0);	//set SS high
	set_bit(SPCR, MSTR);	//sets MCU as master
	
}

uint8_t spi_transmit(uint8_t cData){
	SPDR = cData;							//transmit data
	
	loop_until_bit_is_set(SPSR, SPIF);		//wait until transmit flag is set
	
	return SPDR;
}

void spi_select (){
	clear_bit(PORTB, PB7);	//SS low
}

void spi_deselect(){
	set_bit(PORTB, PB7);	//SS high
}

