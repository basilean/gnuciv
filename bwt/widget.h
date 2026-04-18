#ifndef WIDGET_H
#define WIDGET_H
#include <SDL3/SDL.h>
#include "widget_box.h"

typedef enum {
	WIDGET_COMMON = 0,
	WIDGET_BOX,
} widget_type;

typedef struct widget_t {
	widget_type type;
	SDL_FRect rect;
	SDL_Texture *cache;
	bool refresh;
	bool enable;
	uint8_t x; // min
	uint8_t X; // max
	uint8_t y;
	uint8_t Y;
	void (*click)();
	union {
		widget_box_t *box;
	};
} widget_t;

widget_t * widget_new(SDL_Renderer *, widget_type, SDL_FRect);
void widget_destroy(widget_t *);
void widget_draw(SDL_Renderer *, widget_t *);
void widget_resize(SDL_Renderer *, widget_t *);
#endif