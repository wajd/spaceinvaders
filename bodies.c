#include "header.h"

struct entity;
struct bullet;

struct entity make_entity (int x, int y, int height, int width, int enemy) {
	struct entity temp;
	temp.x = x;
	temp.y = y;
	temp.height = height;
	temp.width = width;
	temp.on = 1;
  temp.enemy = enemy;
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
