#include "header.h"

// struct entity {
// 	int x;
// 	int y;
// 	int width;
// 	int height;
// 	int on;
// };
//
// struct bullet {
// 	int x;
// 	int y;
// 	int dir;
// 	int on;
// };
//
// int updated = 0;

//
// struct entity make_spaceship (int x, int y, int width, int height) {
// 	struct entity temp;
// 	temp.x = x;
// 	temp.y = y;
// 	temp.width = width;
// 	temp.height = height;
// 	temp.on = 0;
// 	//TODO: add checks for validity
// 	return temp;
// }
//
// void toggle_entity (struct entity ent) {
// 	int i = ent.x - ent.width;
// 	int j = ent.y - ent.height;
//
// 	if (i >= 0 && (i + 2*ent.width) < 128 && j >= 0 && (j + 2*ent.height) < 32) {
// 		for (; i <= ent.x + ent.width; i++) {
// 			for (j = ent.y - ent.height; j <= ent.y + ent.width; j++) {
// 					toggle_pixel(&i, &j, ent.on);
// 			}
// 		}
// 	}
// 	updated = 1;
// }

void test() {

	// struct entity spaceship = make_spaceship(15, 16, 6, 8);
	// toggle_entity(spaceship);

	/*current testing routine*/
	int x, y, px, py;

	int pressed = 0;

	px = 60;
	py = 16;
	x = 60;
	y = 16;
	for(;;) {

		if (getbtn(1)) {
			x++;
			pressed = 1;
		}
		else if (getbtn(4)) {
			x--;
			pressed = 1;
		}

		if (getbtn(2)) {
			y++;
			pressed = 1;
		}
		else if (getbtn(3)) {
			y--;
			pressed = 1;
		}

		if (pressed) {
			toggle_pixel(&px, &py, 0);
			toggle_pixel(&x, &y, 1);
			px = x;
			py = y;

			display_update();
			pressed = 0;
		}
	}
}

int main() {
	setup();

	test();

	for(;;) ;
	return 0;
}
