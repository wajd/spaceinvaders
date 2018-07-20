#include "header.h"

int i;

void game_setup() {

	lives = 4;
	play = 1;

	entities[ENE_CNT] = make_entity(8, 15, 3, 2, ENE_CNT);
	toggle_entity(&entities[ENE_CNT], 1);

	for (i= 0; i< ENE_CNT/3; i++) {
		entities[i] = make_entity(100, (2 + i * 5), 2, 2, i);
		toggle_entity(&entities[i], 1);
		entities[i+6] = make_entity(110, (2 + i * 5), 2, 2, i+6);
		toggle_entity(&entities[i+6], 1);
		entities[i+12] = make_entity(120, (2 + i * 5), 2, 2, i+12);
		toggle_entity(&entities[i+12], 1);
	}
	for (i=0; i<ENE_CNT;i++) {
		bullets[i] = make_bullet(0,0,0,i);
	}
	bullets[ENE_CNT] = make_bullet(0,0,1,ENE_CNT);
	build_barriers();

	display_update();
}

void game() {

	while(play) {

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

		if (getsw(2)) {
			shoot(&entities[ENE_CNT]);
		}
		move_bullet(&bullets[ENE_CNT]);

		if(lives && entities[ENE_CNT].alive) {
			toggle_entity(&entities[ENE_CNT], 1);
		} else {
			play = 0;
		}

		for(i=0;i<ENE_CNT;i++) {
			if (entities[i].alive) {
				toggle_entity(&entities[i], 1);
			}
		}

		display_update();
	}
}

int main() {
	setup();
	game_setup();
	game();

	for(;;) ;
	return 0;
}
