#ifndef POSITION_H
#define POSITION_H
#include <SDL3/SDL.h>

typedef enum {
	NONE = 0,
	FULL,
	TOP_LEFT,
	TOP_CENTER,
	TOP_RIGHT,
	MIDDLE_LEFT,
	MIDDLE_CENTER,
	MIDDLE_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT
} anchor_type;

typedef struct position_t {
	anchor_type anchor;
	SDL_FRect min;
	SDL_FRect max;
	SDL_FRect size;
} position_t;

void position_set(SDL_FRect *, position_t *);
#endif