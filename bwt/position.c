#include "config.h"
#include "position.h"

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
		case TOP_LEFT:
			pos->size.x = 0;
			pos->size.y = 0;
			break;
		case TOP_CENTER:
			pos->size.x = (sw - pos->size.w) * 0.5f;
			pos->size.y = 0;
			break;
		case TOP_RIGHT:
			pos->size.x = sw - pos->size.w;
			pos->size.y = 0;
			break;
		case MIDDLE_LEFT:
			pos->size.x = 0;
			pos->size.y = (sh - pos->size.h) * 0.5f;
			break;
		case MIDDLE_CENTER:
			pos->size.x = (sw - pos->size.w) * 0.5f;
			pos->size.y = (sh - pos->size.h) * 0.5f;
			break;
		case MIDDLE_RIGHT:
			pos->size.x = sw - pos->size.w;
			pos->size.y = (sh - pos->size.h) * 0.5f;
			break;
		case BOTTOM_LEFT:
			pos->size.x = 0;
			pos->size.y = sh - pos->size.h;
			break;
		case BOTTOM_CENTER:
			pos->size.x = (sw - pos->size.w) * 0.5f;
			pos->size.y = sh - pos->size.h;
			break;
		case BOTTOM_RIGHT:
			pos->size.x = sw - pos->size.w;
			pos->size.y = sh - pos->size.h;
			break;
	}
}