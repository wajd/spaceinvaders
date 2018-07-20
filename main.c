#include "header.h"

void test() {
	int i, j;

	entities[ENE_CNT] = make_entity(10, 3, 2, 1, ENE_CNT);
	toggle_entity(&entities[ENE_CNT], 1);

	for (i= 0; i< ENE_CNT/3; i++) {
		entities[i] = make_entity(100, (2 + i * 5), 1, 1, i);
		toggle_entity(&entities[i], 1);
		entities[i+6] = make_entity(110, (2 + i * 5), 1, 1, i+6);
		toggle_entity(&entities[i+6], 1);
		entities[i+12] = make_entity(120, (2 + i * 5), 1, 1, i+12);
		toggle_entity(&entities[i+12], 1);
	}

	for (i=0; i<ENE_CNT;i++) {
		bullets[i] = make_bullet(0,0,0,i);
	}

	for (i=0; i<BUL_LIM;i++) {
		herbuls[i] = make_bullet(0,0,1,i);
	}

	build_barriers();

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
			move_entity(&entities[ENE_CNT], Forward);

		}
		if (getbtn(2)) {
			move_entity(&entities[ENE_CNT], Right);

		}
		if (getbtn(3)) {
			move_entity(&entities[ENE_CNT], Left);

		}
		if (getbtn(4)) {
			move_entity(&entities[ENE_CNT], Backwards);

		}

		for (i=0; i<ENE_CNT;i++) {
			if (getsw(1)) {
				shoot(&entities[i]);
			}
			move_bullet(&bullets[i]);
		}

		if (getsw(2+i)) {
			shoot(&entities[ENE_CNT]);
		}

		for (i=0;i<BUL_LIM; i++) {
			move_bullet(&herbuls[i]);
		}

		if (disp) {
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
