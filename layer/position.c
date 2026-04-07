#include "position.h"

#define SCREEN_MIN_W 320
#define SCREEN_MAX_W 1920
#define SCREEN_MIN_H 240
#define SCREEN_MAX_H 1080

float clamp(float v, float min, float max) {
	if (v < min) return min;
	if (v > max) return max;
	return v;
}

float prop_w(float screen, float min, float max) {
	return min + (screen - SCREEN_MIN_W) * (max - min) / (float)(SCREEN_MAX_W - SCREEN_MIN_W);
}

float prop_h(float screen, float min, float max) {
	return min + (screen - SCREEN_MIN_H) * (max - min) / (float)(SCREEN_MAX_H - SCREEN_MIN_H);
}

void position_set(SDL_FRect *screen, position_t *pos) {
	float sw = clamp(screen->w, SCREEN_MIN_W, SCREEN_MAX_W);
	float sh = clamp(screen->h, SCREEN_MIN_H, SCREEN_MAX_H);
	pos->size.w = prop_w(sw, pos->min.w, pos->max.w);
	pos->size.h = prop_h(sh, pos->min.h, pos->max.h);
	switch(pos->anchor) {
		case NONE:
			pos->size.x = prop_w(sw, pos->min.x, pos->max.x);
			pos->size.y = prop_h(sh, pos->min.y, pos->max.y);
			break;
		case FULL:
			pos->size.w = sw;
			pos->size.h = sh;
			pos->size.x = 0;
			pos->size.y = 0;
			break;
	}
}