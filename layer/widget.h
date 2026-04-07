#ifndef WIDGET_H
#define WIDGET_H
#include <SDL3/SDL.h>

typedef enum {
	WIDGET_COMMON = 0,
	WIDGET_BOX,
} widget_type;

typedef struct widget_t {
	widget_type type;
	SDL_FPoint off;
	SDL_Color color;
	SDL_FRect rect;
	uint8_t x; // min
	uint8_t X; // max
	uint8_t y;
	uint8_t Y;
} widget_t;

widget_t * widget_new(SDL_FRect);
#endif