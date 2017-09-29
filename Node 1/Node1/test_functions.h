/*
 * test.h
 *
 * Created: 06.09.2016 13:48:15
 *  Author: sondrfos
 */ 
#include <util/delay.h>

#ifndef TEST_H_
#define TEST_H_



void sram_init(void);

void SRAM_test(void);

void test_GAL(void);

void test_adc(void);

void our_delay(int time);


#endif /* TEST_H_ */