#include "header.h"

struct entity;
struct bullet;

/*entity functions*/

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
      if((*ent).height + (*ent).x + 1 < 128)
			   (*ent).x++;
			break;
		case Right :
      if((*ent).width + (*ent).y + 1 < 32)
			   (*ent).y++;
			break;
		case Backwards :
      if(-(*ent).height + (*ent).x - 1 >= 0)
			   (*ent).x--;
			break;
		case Left :
      if(-(*ent).width + (*ent).y - 1 >= 0)
        (*ent).y--;
			break;
	}

	toggle_entity(ent, 1);
}

/*bullet functions*/

struct bullet shoot(struct entity *ent) {
	struct bullet temp;
	temp.dir = (*ent).enemy;
	if (temp.dir) {
		temp.x = (*ent).x - (*ent).height - 1;
	} else {
		temp.x = (*ent).x + (*ent).height + 1;
	}
	temp.y = (*ent).y;
	temp.on = 1;

	toggle_pixel(&temp.x, &temp.y, temp.on);
	return temp;
}

void move_bullet(struct bullet *bul) {
	toggle_pixel(&(*bul).x, &(*bul).y, 0);
	if ((*bul).dir) {
		(*bul).x--;
	} else {
		(*bul).x++;
	}

	if ((*bul).x < 2 || (*bul).x > 126 || is_pixel_on((*bul).x, (*bul).y))
		(*bul).on = 0;
	else
		toggle_pixel(&(*bul).x, &(*bul).y, (*bul).on);
}
