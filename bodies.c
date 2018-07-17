#include "header.h"

struct entity;
struct bullet;

/*entity functions*/

struct entity make_entity (uint8_t x, uint8_t y, uint8_t height, uint8_t width, int enemy) {
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
	uint8_t i, j;

  for (j=(*ent).y - (*ent).width; j < (*ent).y + (*ent).width + 1; j++) {
    for (i=(*ent).x - (*ent).height; i < (*ent).x + (*ent).height + 1; i++) {
      toggle_pixel(i, j, on);
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
  temp.y = (*ent).y;

	if (temp.dir) {
		temp.x = (*ent).x - (*ent).height - 1;
    if (temp.x <= 0) {
      temp.on = 0;
      return temp;
    }
	} else {
	  temp.x = (*ent).x + (*ent).height + 1;
    if (temp.x >= 127) {
      temp.on = 0;
      return temp;
    }
	}

  temp.on = 1;
	toggle_pixel(temp.x, temp.y, temp.on);
	return temp;
}

void move_bullet(struct bullet *bul) {
  if ((*bul).on) {
    toggle_pixel((*bul).x, (*bul).y, 0);

  	if ((*bul).dir) {
  		(*bul).x--;
  	} else {
  		(*bul).x++;
  	}

  	if ((*bul).x < 0 || (*bul).x > 127 || is_pixel_on((*bul).x, (*bul).y))
  		(*bul).on = 0;
  	else
  		toggle_pixel((*bul).x, (*bul).y, 1);
  }
}
