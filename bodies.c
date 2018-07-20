#include "header.h"

/*barrier functions*/
void build_barriers() {
	uint8_t i;
	for (i=0;i<3;i++)
		toggle_body(BAR_X-BAR_H, i*(BAR_W+4), BAR_X, BAR_W + i*(BAR_W+4), 1);
}

/*entity functions*/

struct entity make_entity (uint8_t x, uint8_t y, uint8_t height, uint8_t width, int id) {
	struct entity temp;
	temp.x = x;
	temp.y = y;
	temp.height = height;
	temp.width = width;
	temp.id = id;
	temp.alive = 1;
	return temp;
}

void toggle_entity (struct entity *ent, int show) {
	toggle_body((*ent).x, (*ent).y, (*ent).x + (*ent).height, (*ent).y + (*ent).width, show);
}

void move_entity (struct entity *ent, int dir) {
	if ((*ent).alive) {
		uint8_t x, y;
		x = (*ent).x;
		y = (*ent).y;

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

		if (is_body_on((*ent).x, (*ent).y, (*ent).x + (*ent).height, (*ent).y + (*ent).width)) {
			(*ent).x = x;
			(*ent).y = y;
		}

		toggle_entity(ent, 1);
	}
}

/*bullet functions*/

struct bullet make_bullet(uint8_t x, uint8_t y, int dir, int id) {
	struct bullet temp;
	temp.x = x;
	temp.y = y;
	temp.dir = dir;
	temp.alive = 0;
	return temp;
}

void shoot(struct entity *ent) {
	if ((*ent).alive && !bullets[(*ent).id].alive) {
		bullets[(*ent).id].dir = ((*ent).id==ENE_CNT) ? 1 : 0;
		bullets[(*ent).id].x = (*ent).x + bullets[(*ent).id].dir*(*ent).height;
		bullets[(*ent).id].alive = 1;
		bullets[(*ent).id].y = (2*(*ent).y + (*ent).width)/2;
		//bullets[(*ent).id].other = 1;
	}
}

void kill(struct bullet *bul) {
	if (!(*bul).dir) {
		if(entities[ENE_CNT].alive) {
			if ((*bul).x <= entities[ENE_CNT].x+ entities[ENE_CNT].height && (*bul).x >= entities[ENE_CNT].x &&
					(*bul).y <= entities[ENE_CNT].y+ entities[ENE_CNT].width && (*bul).y >= entities[ENE_CNT].y) {
						(*bul).alive = 0;
						 lives--;
						 if (!lives) {
						 	entities[ENE_CNT].alive = 0;
							toggle_entity(&entities[ENE_CNT], 0);
						}
			}
			return;
		}
	} else {
		int i;
		for (i=0;i<ENE_CNT;i++) {
			if ((*bul).x <= entities[i].x+ entities[i].height && (*bul).x >= entities[i].x &&
					(*bul).y <= entities[i].y+ entities[i].width && (*bul).y >= entities[i].y) {
				if(entities[i].alive) {
					(*bul).alive = 0;
					entities[i].alive = 0;
					toggle_entity(&entities[i], 0);
				}
				return;
			}
		}
	}
}

void move_bullet(struct bullet *bul) {
  if ((*bul).alive) {
    toggle_pixel((*bul).x, (*bul).y, 0);

  	if ((*bul).dir)
  		(*bul).x++;
  	else
  		(*bul).x--;

		if(is_pixel_on((*bul).x, (*bul).y)) {
			kill(bul);
		}

		if ((*bul).x < 0 || (*bul).x > 127) {
			(*bul).alive = 0;
		} else {
			toggle_pixel((*bul).x, (*bul).y, (*bul).alive);
		}
  }
}
