#ifndef LAYER_H
#define LAYER_H
#include <SDL3/SDL.h>
#include "layer_list.h"
#include "grid.h"
#include "widget.h"
#include "bg.h"
#include "position.h"
#include "event.h"
#include "app.h"

typedef enum {
	LAYER_COMMON = 0,
	LAYER_BG,
	LAYER_GRID,
	LAYER_MAP
} layer_type;

typedef struct layer_t {
	layer_type type;
	SDL_Texture *cache;
	position_t pos;
	SDL_FRect rect;
	bool enable;
	bool active;
	bool refresh;
	union {
		layer_grid_t *grid;
		layer_bg_t *bg;
	};
} layer_t;

layer_t * layer_new(SDL_Renderer *);
void layer_destroy(layer_t *);
void layer_resize(app_t *, layer_t *);
void layer_draw(SDL_Renderer *, layer_t *);
bool layer_input(event_t *, layer_t *);
#endif