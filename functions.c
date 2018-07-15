#include "header.h"

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

/*input*/

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

/*setup for code, called first thing in main()*/
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
