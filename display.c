#include "header.h"

/*switch specific pixel on/off*/
void toggle_pixel(uint8_t x, uint8_t y, int on) {
	if(on)
		pixels[(x % 128) + 128 * (((y - (y % 8))/8)%4)] |= (0x1 << (y % 8));
	else
		pixels[(x % 128) + 128 * (((y - (y % 8))/8)%4)] &= ~(0x1 << (y % 8));
}

/*ckeck specific pixel is on/off*/
int is_pixel_on(uint8_t x, uint8_t y) {
	return (pixels[(x % 128) + 128 * (((y - (y % 8))/8)%4)] & (0x1 << (y % 8)));
}

/*pixel array*/
uint8_t pixels[512];

/*functions to communication with screen hardware*/

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void display_init() {
	DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
	delay(10);
	DISPLAY_VDD_PORT &= ~DISPLAY_VDD_MASK;
	delay(1000000);

	spi_send_recv(0xAE);
	DISPLAY_RESET_PORT &= ~DISPLAY_RESET_MASK;
	delay(10);
	DISPLAY_RESET_PORT |= DISPLAY_RESET_MASK;
	delay(10);

	spi_send_recv(0x8D);
	spi_send_recv(0x14);

	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

	DISPLAY_VBATT_PORT &= ~DISPLAY_VBATT_MASK;
	delay(10000000);

	spi_send_recv(0xA1);
	spi_send_recv(0xC8);

	spi_send_recv(0xDA);
	spi_send_recv(0x20);

	spi_send_recv(0xAF);
}

void display_update() {
	 int i, j;

	 for(i = 0; i < 4; i++) {
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(0);
		spi_send_recv(0x10);

		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;

		for(j = 0; j < 128; j++)
			spi_send_recv(pixels[i*128 + j]);
	 }

	 delay(DELAY);
}
