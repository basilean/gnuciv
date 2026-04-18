#include "widget.h"

widget_t * widget_new(SDL_Renderer *render, widget_type type, SDL_FRect rect) {
	widget_t *widget = SDL_calloc(1, sizeof(widget_t));
	*widget = (widget_t){
		type,
		rect
	};
	widget->cache = SDL_CreateTexture(
		render,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		rect.w,
		rect.h
	);
	widget->refresh = true;
	return widget;
}

void widget_destroy(widget_t *widget) {
	SDL_free(widget);
}

void widget_draw(SDL_Renderer *render, widget_t *widget) {
	SDL_Texture* last = SDL_GetRenderTarget(render);
	if (widget->refresh) {
		SDL_SetRenderTarget(render, widget->cache);
		switch(widget->type) {
			case WIDGET_BOX:
					SDL_Log("Widget draw");
					widget_box_draw(render, widget->box);
					break;
		}
		SDL_SetRenderTarget(render, last);
		widget->refresh = false;
	}
	SDL_RenderTexture(render, widget->cache, NULL, &widget->rect);
}

void widget_resize(SDL_Renderer *render, widget_t *widget) {
	SDL_Log("Widget resize");
	widget->refresh = true;
}