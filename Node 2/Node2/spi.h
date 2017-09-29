/*
 * spi.h
 *
 * Created: 26.10.2016 10:19:23
 *  Author: sondrfos
 */ 


#ifndef SPI_H_
#define SPI_H_

uint8_t spi_transmit(uint8_t cData);
void spi_select();
void spi_deselect();
void spi_init();

#endif /* SPI_H_ */