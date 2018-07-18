#include "header.h"

void test() {

	spaceship = make_entity(10, 15, 2, 1, 0);
	toggle_entity(&spaceship, 1);
	struct bullet ssbul;
	int ssbtrav = 0;

	int i;
	for (i= 0; i< ENE_CNT; i++) {
		enemies[i] = make_entity(100, (3 + i * 5), 1, 1, 1);
		toggle_entity(&enemies[i], 1);
		bultrav[i] = 0;
	}

	display_update();

	int disp = 0;

	//int i, j, x, y;

	// uint8_t x, y, px, py;
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

		if(ssbtrav && ssbul.on) {
			move_bullet(&ssbul);
			bullet_kill(&ssbul);
			disp = 1;
		} else {
			ssbtrav = 0;
		}

		if(getsw(1) && !ssbtrav) {
			ssbul = shoot(&spaceship);
			ssbtrav = 1;
		}

		for (i=0; i<ENE_CNT; i++) {
			if(bultrav[i] && enebuls[i].on) {
				move_bullet(&enebuls[i]);
				bullet_kill(&enebuls[i]);
				disp = 1;
			} else {
				bultrav[i] = 0;
			}

			if(getsw(2) && !bultrav[i]) {
				enebuls[i] = shoot(&enemies[i]);
				bultrav[i] = 1;
			}
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
