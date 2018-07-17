#include "header.h"
enum Direction {Forward, Right, Backwards, Left};

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

void toggle_entity (struct entity *ent, int on) {
	int i, j, x, y;
	x = (*ent).x - (*ent).height;
	y = (*ent).y - (*ent).width;

	if (x >= 0 && (x + 2*(*ent).height) < 128 && y >= 0 && (y + 2*(*ent).width) < 32) {
		for (j = (*ent).y - (*ent).width; j <= (*ent).y + (*ent).width; j++) {
			for (i = (*ent).x - (*ent).height; i <= (*ent).x + (*ent).height; i++) {
				x = i;
				y = j;
				toggle_pixel(&x, &y, on);
			}
		}
	}
}

void move_entity (struct entity *ent, int dir) {
	toggle_entity(ent, 0);

	switch(dir) {
		case Forward :
			(*ent).x++;
			break;
		case Right :
			(*ent).y++;
			break;
		case Backwards :
			(*ent).x--;
			break;
		case Left :
			(*ent).y--;
			break;
	}

	toggle_entity(ent, 1);
}

void test() {

	struct entity spaceship = make_entity(15, 16, 3, 2);
	toggle_entity(&spaceship, 1);
	display_update();

	int disp = 0;
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
		if (getbtn(1)) {
			move_entity(&spaceship, Forward);
			disp = 1;
		}
		if (getbtn(2)) {
			move_entity(&spaceship, Left);
			disp = 1;
		}
		if (getbtn(3)) {
			move_entity(&spaceship, Right);
			disp = 1;
		}
		if (getbtn(4)) {
			move_entity(&spaceship, Backwards);
			disp = 1;
		}

		if (disp) {
			display_update();
			disp = 0;
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
