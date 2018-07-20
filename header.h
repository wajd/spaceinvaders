#include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>

/*display definitions*/
#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9

#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

/*CONSTANTS*/
#define DELAY 100000
#define ENE_CNT 18
#define BAR_X 15
#define BAR_W 7
#define BAR_H 2

enum Direction {Forward, Right, Backwards, Left};

struct entity {
	uint8_t x;
	uint8_t y;
	uint8_t height;
	uint8_t width;
	int id;
	int alive;
};

struct bullet {
	uint8_t x;
	uint8_t y;
	int dir;
	int alive;
};

/*VARIABLES*/
uint8_t pixels[512];
struct entity entities[ENE_CNT+1];
struct bullet bullets[ENE_CNT+1];
int lives;
int play;

/*Declare base & setup functions*/
void delay(int cyc);
uint8_t spi_send_recv(uint8_t data);
void display_init();
void display_update();
void setup();

/*Declare graphic functions*/
void toggle_pixel(uint8_t x, uint8_t y, int on);
int is_pixel_on(uint8_t x, uint8_t y);
void toggle_body(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, int on);
int is_body_on(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

/*Declare input functions*/
int getbtn(int x);
int getsw(int x);

/*Declare game control functions*/
struct entity make_entity (uint8_t x, uint8_t y, uint8_t height, uint8_t width, int id);
void toggle_entity (struct entity *ent, int show);
void move_entity (struct entity *ent, int dir);
struct bullet make_bullet(uint8_t x, uint8_t y, int dir, int id);
void move_bullet(struct bullet *bul);
void shoot(struct entity *ent);
void build_barriers();
