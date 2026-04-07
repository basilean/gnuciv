#ifndef GRID_H
#define GRID_H
#include <SDL3/SDL.h>
#include "../app.h"

typedef struct widget_t widget_t;
typedef struct layer_t layer_t;

typedef struct cell_t {
	widget_t **widget;
	uint8_t count;
} cell_t;

typedef struct layer_grid_t {
	SDL_Color color;
	uint16_t size;
	uint16_t w;
	uint16_t h;
	uint16_t count;
	uint16_t widgets;
	widget_t **widget;
	cell_t **cell;
} layer_grid_t;

layer_t* layer_grid_new(app_t *, uint16_t size, SDL_Color);
void layer_grid_index(layer_grid_t *, widget_t *);
void layer_grid_resize(app_t *, layer_t *);
void layer_grid_draw(SDL_Renderer *, layer_grid_t *);
void layer_grid_add(layer_grid_t *, widget_t *);
void layer_grid_del(layer_grid_t *, widget_t *);
void layer_grid_destroy(layer_grid_t *);
#endif