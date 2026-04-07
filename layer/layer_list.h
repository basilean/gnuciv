#ifndef LAYER_LIST_H
#define LAYER_LIST_H
#include <SDL3/SDL.h>

typedef struct layer_t layer_t;

typedef struct layer_list_t {
	uint16_t count;
	layer_t	**layer;
} layer_list_t;

layer_list_t * layer_list_new();
void layer_list_destroy(layer_list_t *);
void layer_list_add(layer_list_t *, layer_t *);
void layer_list_del(layer_list_t *, layer_t *);
#endif