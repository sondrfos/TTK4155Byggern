/*
 * mcp2515.h
 *
 * Created: 12.10.2016 17:30:58
 *  Author: sondrfos
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_
#include <stdbool.h>
#include <stdint.h>

uint8_t mcp2515_read(uint8_t adr);
void mcp2515_write(uint8_t adr, uint8_t data);
void mcp2515_request_to_send(uint8_t transmit_buffer);
void mcp2515_bit_modify(uint8_t adr, uint8_t mask, uint8_t data);
void mcp2515_reset();
uint8_t mcp2515_read_status();



#endif /* MCP2515_H_ */