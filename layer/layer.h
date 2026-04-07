#ifndef LAYER_H
#define LAYER_H
#include <SDL3/SDL.h>
#include "layer_list.h"
#include "grid.h"
#include "widget.h"
#include "bg.h"

typedef enum {
	LAYER_COMMON = 0,
	LAYER_BG,
	LAYER_GRID,
	LAYER_MAP
} layer_type;

typedef struct layer_t {
	layer_type type;
	SDL_Texture *cache;
	bool refresh;
	bool enable;
	union {
		layer_grid_t *grid;
		layer_bg_t *bg;
	};
} layer_t;

layer_t * layer_new(SDL_Renderer *);
void layer_destroy(layer_t *);
void layer_resize(SDL_Renderer *, layer_t *);
void layer_draw(SDL_Renderer *, layer_t *);
#endif