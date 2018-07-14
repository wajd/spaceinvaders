#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "header.h"

#define DELAY 100000

void setup() {
	/* Set up peripheral bus clock */
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;

	/* Clear SPIROV*/
	SPI2STATCLR &= ~0x40;
	/* Set CKP = 1, MSTEN = 1; */
				SPI2CON |= 0x60;

	/* Turn on SPI */
	SPI2CONSET = 0x8000;

	display_init();
	display_update(map);
}

int main() {
	setup();

	/*current testing routine*/
	int x, y, px, py;

	bool pressed = false;

	px = 60;
	py = 16;
	x = 60;
	y = 16;
	for(;;) {

		if (getbtn(1)) {
			x++;
			pressed = true;
		}
		else if (getbtn(4)) {
			x--;
			pressed = true;
		}

		if (getbtn(2)) {
		  y++;
			pressed = true;
		}
		else if (getbtn(3)) {
			y--;
			pressed = true;
		}

		if (pressed) {
			toggle_pixel(&px, &py, false);
			toggle_pixel(&x, &y, true);
			px = x;
			py = y;

			display_update(map);
			pressed = false;
		}
	}

	return 0;
}
