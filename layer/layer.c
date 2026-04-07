#include "layer.h"

layer_t * layer_new(SDL_Renderer *render) {
	int w, h;
	SDL_GetCurrentRenderOutputSize(render, &w, &h);
	layer_t *layer = SDL_calloc(1, sizeof(layer_t));
	layer->cache = SDL_CreateTexture(
		render,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		w, h
	);
	layer->refresh = true;
	layer->enable = true;
	return layer;
}

void layer_destroy(layer_t *layer) {
	switch(layer->type) {
		case LAYER_BG:
				layer_bg_destroy(layer->bg);
				break;
		case LAYER_GRID:
				layer_grid_destroy(layer->grid);
				break;
	}
	SDL_DestroyTexture(layer->cache);
	SDL_free(layer);
}

void layer_resize(SDL_Renderer *render, layer_t *layer) {
	int w, h;
	SDL_GetCurrentRenderOutputSize(render, &w, &h);
	SDL_DestroyTexture(layer->cache);
	
	layer->cache = SDL_CreateTexture(
		render,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		layer->pos.size.w, layer->pos.size.h
	);
	switch(layer->type) {
		case LAYER_BG:
				//layer_bg_draw(render, layer->bg);
				break;
		case LAYER_GRID:
				layer_grid_resize(render, layer->grid);
				break;
	}
	layer->refresh = true;
}

void layer_draw(SDL_Renderer *render, layer_t *layer) {
	if (layer->refresh) {
		SDL_SetRenderTarget(render, layer->cache);
		switch(layer->type) {
			case LAYER_BG:
					layer_bg_draw(render, layer->bg);
					break;
			case LAYER_GRID:
					layer_grid_draw(render, layer->grid);
					break;
		}
		SDL_SetRenderTarget(render, NULL);
		layer->refresh = false;
	}
	SDL_RenderTexture(render, layer->cache, NULL, &layer->pos.size);
}

static inline bool in_frect(const SDL_FPoint *p, const SDL_FRect *r) {
	return (p->x >= r->x) &&
		(p->x <  r->x + r->w) &&
		(p->y >= r->y) &&
		(p->y <  r->y + r->h);
}

bool layer_input(event_t *event, layer_t *layer) {
	if(!layer->enable || !layer->active) {
		return false;
	}
	switch(layer->type) {
		case LAYER_GRID:
				uint16_t x = event->mouse.motion.x / layer->grid->size;
				uint16_t y = event->mouse.motion.y / layer->grid->size;
				uint16_t pos = (layer->grid->w * y) + x;
				if(layer->grid->cell[pos] != NULL) {
					SDL_FPoint point = {event->mouse.motion.x, event->mouse.motion.y};
					for(uint16_t i = layer->grid->cell[pos]->count; i > 0; i--) {
						uint16_t w = i - 1;
						if(in_frect(&point, &layer->grid->cell[pos]->widget[w]->rect)) {
							SDL_Log("Widget: %d", w);
							if(layer->grid->cell[pos]->widget[w]->click != NULL) {
								layer->grid->cell[pos]->widget[w]->click();
							}
							return true;
						}
					}
				}
				break;
	}
}