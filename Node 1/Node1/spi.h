/*
 * spi.h
 *
 * Created: 12.10.2016 13:24:05
 *  Author: sondrfos
 */ 


#ifndef SPI_H_
#define SPI_H_

uint8_t spi_transmit(uint8_t cData);
void spi_select();
void spi_deselect();
void spi_init();

#endif /* SPI_H_ */