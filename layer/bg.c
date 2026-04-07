#include <SDL3_image/SDL_image.h>
#include "layer.h"
//#include "bg.h"

layer_t * layer_bg_new(SDL_Renderer *render, SDL_Color color, const char *file, uint8_t alpha) {
	layer_t *layer = layer_new(render);
	layer->type = LAYER_BG;
	layer->bg = SDL_calloc(1, sizeof(layer_bg_t));
	layer->bg->color = color;
	layer->bg->alpha = alpha;
	layer->bg->image = IMG_Load(file);
	if(!layer->bg->image) {
		SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Failed loading background.\n");
	}
	return layer;
}

void layer_bg_destroy(layer_bg_t *bg) {
	SDL_DestroySurface(bg->image);
	SDL_free(bg);
}

void layer_bg_draw(SDL_Renderer *render, layer_bg_t *bg) {
	SDL_SetRenderDrawColor(render, bg->color.r, bg->color.g, bg->color.b, bg->color.a);
	SDL_RenderClear(render);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, bg->image);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, bg->alpha);
	SDL_RenderTexture(render, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
}