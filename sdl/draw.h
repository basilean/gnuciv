#ifndef DRAW_H
#define DRAW_H
#include <SDL3/SDL.h>

typedef struct frame_t {
	SDL_Color bg;
	SDL_FPoint size;
} frame_t;

typedef struct app_t app_t;
void draw_frame(app_t *);
#endif