#ifndef WIDGET_BOX_H
#define WIDGET_BOX_H
#include <SDL3/SDL.h>

typedef struct widget_t widget_t;

typedef struct widget_box_t {
	SDL_Color color;
} widget_box_t;

widget_t * widget_box_new(SDL_Renderer *, SDL_FRect, SDL_Color);
void widget_box_destroy(widget_box_t *);
void widget_box_draw(SDL_Renderer *, widget_box_t *);
#endif