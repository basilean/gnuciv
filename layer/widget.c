#include "widget.h"

widget_t * widget_new(SDL_FRect rect) {
	widget_t *widget = SDL_calloc(1, sizeof(widget_t));
	*widget = (widget_t){
		WIDGET_BOX,
		(SDL_FPoint){0, 0},
		(SDL_Color){100, 100, 100, 255},
		rect
	};
	return widget;
}