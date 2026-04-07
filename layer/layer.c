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
		w, h
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
	SDL_RenderTexture(render, layer->cache, NULL, NULL);
}
