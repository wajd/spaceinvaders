#include "header.h"

struct entity {
	int x;
	int y;
	int on;
	int height;
	int width;
};

struct bullet {
	int x;
	int y;
	int on;
	int dir;
};

// int updated = 0;


struct entity make_entity (int x, int y, int height, int width) {
	struct entity temp;
	temp.x = x;
	temp.y = y;
	temp.height = height;
	temp.width = width;
	temp.on = 1;
	//TODO: add checks for validity
	return temp;
}

void toggle_entity (struct entity *ent) {
	int i, j, x, y;
	x = (*ent).x - (*ent).width;
	y = (*ent).y - (*ent).height;

	if (x >= 0 && (x + 2*(*ent).height) < 128 && y >= 0 && (y + 2*(*ent).width) < 32) {
		for (j = (*ent).y - (*ent).width; j <= (*ent).y + (*ent).width; j++) {
			for (i = (*ent).x - (*ent).height; i <= (*ent).x + (*ent).height; i++) {
				x = i;
				y = j;
				toggle_pixel(&x, &y, (*ent).on);
			}
		}
	}
}

//void move_entity (struct entity ent) {}

void test() {

	struct entity spaceship = make_entity(15, 16, 3, 2);

	// int x, y, px, py;
	//
	// int pressed = 0;
	//
	// px = 60;
	// py = 16;
	// x = 60;
	// y = 16;
	//int i, j, x, y;

	for(;;) {
		if (getbtn(4)) {
			toggle_entity(&spaceship);
			display_update();
		}
		// if (getbtn(1)) {
		// 	for (j = spaceship.y - spaceship.width; j <= spaceship.y + spaceship.width; j++) {
		// 		for (i = spaceship.x - spaceship.height; i <= spaceship.x + spaceship.height; i++) {
		// 			// x = i;
		// 			// y = j;
		// 			toggle_pixel(&i, &j, spaceship.on);
		// 		}
		// 	}
		// 	display_update();
		// }
		// if (getbtn(1)) {
		// 	x++;
		// 	pressed = 1;
		// }
		// else if (getbtn(4)) {
		// 	x--;
		// 	pressed = 1;
		// }
		//
		// if (getbtn(2)) {
		// 	y++;
		// 	pressed = 1;
		// }
		// else if (getbtn(3)) {
		// 	y--;
		// 	pressed = 1;
		// }
		//
		// if (pressed) {
		// 	toggle_pixel(&px, &py, 0);
		// 	toggle_pixel(&x, &y, 1);
		// 	px = x;
		// 	py = y;
		//
		// 	display_update();
		// 	pressed = 0;
		// }
	}
}

int main() {
	setup();

	/*current testing routine*/
	test();

	for(;;) ;
	return 0;
}
