#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "header.h"

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

int getbtn(int x) {
	volatile int buttons = ((PORTD >> 4) & 0xe) | ((PORTF >> 1) & 0x1);

	if (!x || x > 4)
		return buttons;

	return (buttons >> (x-1)) & 0x1;
}

int getsw(int x) {
	volatile int sw = ((PORTD >> 8) & 0xf);

	if (!x || x>4)
		return sw;

	return (sw >> (x-1)) & 0x1;
}
