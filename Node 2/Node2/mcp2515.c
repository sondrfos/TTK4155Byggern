/*
 * mcp2515.c
 *
 * Created: 12.10.2016 17:31:09
 *  Author: sondrfos
 */ 
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include "spi.h"
#include "MCP2515_adresses.h"




uint8_t mcp2515_read(uint8_t adr){
	spi_select();
	spi_transmit(MCP_READ);
	spi_transmit(adr);
	uint8_t read_value = spi_transmit(0);
	spi_deselect();
	return read_value;
}
void mcp2515_write(uint8_t adr, uint8_t data){
	spi_select();
	spi_transmit(MCP_WRITE);
	spi_transmit(adr);
	spi_transmit(data);
	spi_deselect();
}
void mcp2515_request_to_send(uint8_t transmit_buffer){
	spi_select();
	spi_transmit(128+transmit_buffer);
	spi_deselect();
}
void mcp2515_reset(){
	spi_select();
	spi_transmit(MCP_RESET);
	spi_deselect();
	_delay_ms(1);
}
uint8_t mcp2515_read_status(){
	spi_select();
	spi_transmit(160);
	uint8_t status = spi_transmit(0);
	spi_deselect();
	return status;
}
void mcp2515_bit_modify(uint8_t adr, uint8_t mask, uint8_t data){
	spi_select();
	spi_transmit(MCP_BITMOD);
	spi_transmit(adr);
	spi_transmit(mask);
	spi_transmit(data);
	spi_deselect();
}