#include "widget.h"

widget_t * widget_box_new(SDL_Renderer *render, SDL_FRect rect, SDL_Color color) {
	widget_t *widget = widget_new(render, WIDGET_BOX, rect);
	widget->box = SDL_calloc(1, sizeof(widget_box_t));
	widget->box->color = color;
	return widget;
}

void widget_box_draw(SDL_Renderer *render, widget_box_t *box) {
	SDL_SetRenderDrawColor(render, box->color.r, box->color.g, box->color.b, box->color.a);
	SDL_RenderClear(render);
}