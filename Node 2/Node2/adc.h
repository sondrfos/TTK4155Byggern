/*
 * adc.h
 *
 * Created: 13.11.2016 10:59:34
 *  Author: sondrfos
 */ 


#ifndef ADC_H_
#define ADC_H_


void adc_init();
uint8_t adc_read();
uint8_t adc_score(uint8_t last_read_IR);


#endif /* ADC_H_ */