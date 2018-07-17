#include "header.h"

struct entity;
struct bullet;

void test() {

	struct entity spaceship = make_entity(15, 16, 3, 2, 0);
	struct bullet bul;
	toggle_entity(&spaceship, 1);
	display_update();

	int disp = 0;
	int shooting = 0;

	//int i, j, x, y;

	// int x, y, px, py;
	//
	// int pressed = 0;
	//
	// px = 60;
	// py = 16;
	// x = 60;
	// y = 16;

	for(;;) {

		if (getbtn(1)) {
			move_entity(&spaceship, Forward);
			disp = 1;
		}
		if (getbtn(2)) {
			move_entity(&spaceship, Right);
			disp = 1;
		}
		if (getbtn(3)) {
			move_entity(&spaceship, Left);
			disp = 1;
		}
		if (getbtn(4)) {
			move_entity(&spaceship, Backwards);
			disp = 1;
		}

		if(shooting && bul.on) {
			move_bullet(&bul);
			disp = 1;
		} else {
			shooting = 0;
		}

		if(getsw(1) && !shooting) {
			bul = shoot(&spaceship);
			shooting = 1;
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
