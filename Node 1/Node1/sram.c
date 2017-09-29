/*
 * sram.c
 *
 * Created: 20.10.2016 13:44:56
 *  Author: sondrfos
 */ 

#include <avr/io.h>
#include "bit.h"


void sram_init(void){
	set_bit(SFIOR,XMM2);
	clear_bit(SFIOR,XMM1);
	clear_bit(SFIOR,XMM0);
	set_bit(MCUCR,SRE);
}