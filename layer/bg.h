#ifndef BG_H
#define BG_H

typedef struct layer_t layer_t;

typedef struct layer_bg_t {
	SDL_Color color;
	SDL_Surface *image;
	uint8_t alpha;
} layer_bg_t;

layer_t * layer_bg_new(SDL_Renderer *, SDL_Color, const char *, uint8_t);
void layer_bg_destroy(layer_bg_t *);
void layer_bg_draw(SDL_Renderer *, layer_bg_t *);
#endif