#ifndef LAYERS_H
#define LAYERS_H
#include <SDL3/SDL.h>

typedef struct layer_t layer_t;

typedef struct layers_t {
	uint16_t count;
	layer_t	**layer;
} layers_t;

layers_t * layers_new();
void layers_destroy(layers_t *);
void layers_add(layers_t *, layer_t *);
void layers_del(layers_t *, layer_t *);
#endif