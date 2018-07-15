#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "header.h"

struct entity {
	int x;
	int y;
	int width;
	int height;
	bool on;
};

struct bullet {
	int x;
	int y;
	bool dir;
	bool on;
};

bool updated = false;

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
	display_update();
}

struct entity make_spaceship (int x, int y, int width, int height) {
	struct entity temp;
	temp.x = x;
	temp.y = y;
	temp.width = width;
	temp.height = height;
	temp.on = false;
	//TODO: add checks for validity
	return temp;
}

void toggle_entity (struct entity ent) {
	int i = ent.x - ent.width;
	int j = ent.y - ent.height;

	if (i >= 0 && (i + 2*ent.width) < 128 && j >= 0 && (j + 2*ent.height) < 32) {
		for (; i <= ent.x + ent.width; i++) {
			for (j = ent.y - ent.height; j <= ent.y + ent.width; j++) {
					toggle_pixel(&i, &j, ent.on);
			}
		}
	}
	updated = true;
}

int main() {
	setup();

	struct entity spaceship = make_spaceship(15, 16, 6, 8);
	toggle_entity(spaceship);

	// /*current testing routine*/
	// int x, y, px, py;
	//
	// bool pressed = false;
	//
	// px = 60;
	// py = 16;
	// x = 60;
	// y = 16;
	// for(;;) {
	//
	// 	if (getbtn(1)) {
	// 		x++;
	// 		pressed = true;
	// 	}
	// 	else if (getbtn(4)) {
	// 		x--;
	// 		pressed = true;
	// 	}
	//
	// 	if (getbtn(2)) {
	// 	  y++;
	// 		pressed = true;
	// 	}
	// 	else if (getbtn(3)) {
	// 		y--;
	// 		pressed = true;
	// 	}
	//
	// 	if (pressed) {
	// 		toggle_pixel(&px, &py, false);
	// 		toggle_pixel(&x, &y, true);
	// 		px = x;
	// 		py = y;
	//
	// 		display_update(map);
	// 		pressed = false;
	// 	}
	// }
	for(;;) {
		if (updated)
			display_update();
			updated = false;
	}

	return 0;
}
