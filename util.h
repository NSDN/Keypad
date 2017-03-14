#include "STC15.h"
#include <intrins.h>

#ifndef __UTIL_H_
#define __UTIL_H_

#define uint8_t unsigned char
	
#define LED P55
static bit SHT_LCK = 0;
static bit ALT_LCK = 0;

static bit BUSY = 0;
static uint8_t DATA;

void portInit() {
	P1M0 = 0;	P1M1 = 0;
	P2M0 = 0;	P2M1 = 0;
	P5M0 = 0x20;P5M1 = 0;
	
	LED = 0;
}

void timerInit() {
	/*24MHz@1ms*/
	AUXR |= 0x80;
	TMOD &= 0xF0;
	TL0 = 0x40;	
	TH0 = 0xA2;
	TF0 = 0;
	TR0 = 1;
	ET0 = 1;
}

void serialInit() {
	/*24MHz@9600bps*/
	SCON = 0x50;
	T2L = 0x8F;
	T2H = 0xFD;
	AUXR = 0x14;
    AUXR |= 0x01;
    ES = 1;
}

void endInit() {
	EA = 1;
}

void serialInterrupt() interrupt 4 using 1 {
	if (RI) {
        RI = 0;
        DATA = SBUF;
    }
	if (TI) {
        TI = 0;
        BUSY = 0;
    }
}

static unsigned char _cnt = 0;
void timerInterrupt() interrupt 1 using 1 {
	if (ALT_LCK) {
		if (_cnt < 50) _cnt += 1;
		else {
			_cnt = 0;
			LED = !LED;
		}
	} else LED = SHT_LCK;
}

void send(uint8_t value) {
	while (BUSY);
	BUSY = 1;
	SBUF = value;
}

void write(char* str) {
	while (*str) send(*str++);
}

void delay(unsigned short time)
{
	unsigned char i, j;
	unsigned short t;
	i = 24;
	j = 85;
	t = time;
	do {
		do {
			while (--j) _nop_();
		} while (--i);
	} while (--t);
}

#endif