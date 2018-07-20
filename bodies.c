#include "header.h"

/*barrier functions*/
void build_barriers() {
	uint8_t i;
	for (i=0;i<3;i++)
		toggle_body(BAR_X-BAR_H, i*BAR_W, BAR_X, BAR_W + i*(BAR_W+3), 1);
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

		if (is_body_on((*ent).x, (*ent).y, (*ent).x + (*ent).height, (*ent).y + (*ent).width))
			pxl[(*ent).id] = 1;

		toggle_entity(ent, 1);
	}
}

/*bullet functions*/

struct bullet make_bullet(uint8_t x, uint8_t y, int dir, int id) {
	struct bullet temp;
	temp.x = x;
	temp.y = y;
	temp.dir = dir;
	temp.id = id;
	temp.alive = 0;
	return temp;
}

void move_bullet(struct bullet *bul) {
  if ((*bul).alive) {
    toggle_pixel((*bul).x, (*bul).y, 0);

  	if ((*bul).dir)
  		(*bul).x++;
  	else
  		(*bul).x--;

		if(is_pixel_on((*bul).x, (*bul).y))
			pxl[ENE_CNT + 1 + (*bul).dir * ENE_CNT + (*bul).id];

		if ((*bul).x < 0 || (*bul).x > 127) {
			(*bul).alive = 0;
		} else {
			toggle_pixel((*bul).x, (*bul).y, 1);
		}
  }
}

void shoot(struct entity *ent) {
	if ((*ent).id != ENE_CNT && !bullets[(*ent).id].alive) {
		bullets[(*ent).id].alive = 1;
		bullets[(*ent).id].dir = 0;
		bullets[(*ent).id].x = (*ent).x;
		bullets[(*ent).id].y = (2*(*ent).y + (*ent).width)/2;
		//bullets[(*ent).id].other = 1;
	} else if ((*ent).id == ENE_CNT) {
		int i;
		for(i=0;i<BUL_LIM;i++) {
			if (!herbuls[i].alive) {
				break;
			}
			if (i= BUL_LIM-1)
				return;
		}
		herbuls[i].alive = 1;
		herbuls[i].dir = 1;
		herbuls[i].x = (*ent).x + (*ent).height;
		herbuls[i].y = (2*(*ent).y + (*ent).width)/2;
		//herbuls[i].other = 1;
	}
}

// int murder() {
// 	int i;
// 	for (i=0; i< 2*ENE_CNT+BUL_LIM+1; i++) {
// 		if (pxl[i]) {
// 			if (i < ENE_CNT+1) {
// 				x = entities[i].x;
// 				h = entities[i].height;
// 				y = entities[i].y;
// 				w = entities[i].width;
// 				for (j=i+1; j< 2*ENE_CNT+BUL_LIM+1; j++) {
// 					if (pxl[j]) {
// 						if ()
// 					}
// 				}
// 			} else if (i > ENE_CNT+1) {
// 				if (i < 2*ENE_CNT+1) {
// 					x = bullets[i-ENE_CNT-1].x;
// 					y = bullets[i-ENE_CNT-1].y;
// 				} else {
// 					x = herbuls[i-2*ENE_CNT-1].x;
// 					y = herbuls[i-2*ENE_CNT-1].y;
// 				}
// 			}
// 		}
// 	}
// }
