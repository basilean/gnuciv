#include "layer.h"

layer_list_t * layer_list_new() {
	layer_list_t *list = SDL_calloc(1, sizeof(layer_list_t));
	list->layer = NULL;
	list->count = 0;
	return list;
}

void layer_list_destroy(layer_list_t *list) {
	for(uint16_t i = 0; i < list->count; i++) {
		if(list->layer[i]) layer_destroy(list->layer[i]);
	}
	if (list->layer) SDL_free(list->layer);
	if (list) SDL_free(list);
}

void layer_list_add(layer_list_t *list, layer_t *layer) {
	list->layer = SDL_realloc(list->layer, (list->count + 1) * sizeof(layer_t *));
	if(list->layer == NULL) {
		SDL_Log("SEGFAULT REALLOC");
	}
	list->layer[list->count] = layer;
	list->count++;
}

void layer_list_del(layer_list_t *list, layer_t *layer) {
	uint16_t t = 0;
	for(uint16_t i = 0; i < list->count; i++) {
		if (list->layer[i] == layer) {
			layer_destroy(layer);
			continue;		
		}
		list->layer[t] = list->layer[i];
		t++;
	}
	list->count = t;
	if (list->count == 0) {
		SDL_free(list->layer);
		list->layer = NULL;
	}
	else {
		list->layer = SDL_realloc(list->layer, list->count * sizeof(layer_t *));
	}
}