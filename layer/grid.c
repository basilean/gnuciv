#include "layer.h"
#include "widget.h"
#include "position.h"

layer_t * layer_grid_new(app_t *app, uint16_t size, SDL_Color color) {
	layer_t *layer = layer_new(app->render);
	layer->type = LAYER_GRID;
	layer->active = true;
	layer->grid = SDL_calloc(1, sizeof(layer_grid_t));
	layer->grid->color = color;
	layer->grid->count = 0;
	layer->grid->size = size;
	layer->grid->widgets = 0;
	layer->pos.min = (SDL_FRect){20, 20, 300, 300};
	layer->pos.max = (SDL_FRect){40, 40, 500, 500};
	layer_grid_resize(app, layer);
	return layer;
}

void layer_grid_resize(app_t *app, layer_t *layer) {
	int w, h;
	SDL_GetCurrentRenderOutputSize(app->render, &w, &h);
	if (layer->grid->cell) {
		for(uint16_t i = 0; i < layer->grid->count; i++) {
			if(layer->grid->cell[i] == NULL) continue;
			if(layer->grid->cell[i]->widget != NULL) SDL_free(layer->grid->cell[i]->widget);
			SDL_free(layer->grid->cell[i]);
		}
		SDL_free(layer->grid->cell);
	}
	position_set(&app->screen, &layer->pos);
	layer->grid->w = layer->pos.size.w / layer->grid->size;
	layer->grid->h = layer->pos.size.h / layer->grid->size;
	layer->grid->count = layer->grid->w * layer->grid->h;
	layer->grid->cell = SDL_calloc(layer->grid->count, sizeof(cell_t *));
	SDL_Log("Grid resized: %dx%d %fx%f", layer->grid->w, layer->grid->h, layer->pos.size.w, layer->pos.size.h);
	for(uint16_t i = 0; i < layer->grid->widgets; i++) {
		widget_resize(app->render, layer->grid->widget[i]);
		layer_grid_index(layer->grid, layer->grid->widget[i]);
	}
}

void layer_grid_destroy(layer_grid_t *grid) {
	if (grid->cell) SDL_free(grid->cell);
	if (grid) SDL_free(grid);
}

void layer_grid_draw(SDL_Renderer *render, layer_grid_t *grid) {
	SDL_SetRenderDrawColor(render, grid->color.r, grid->color.g, grid->color.b, grid->color.a);
	SDL_RenderClear(render);
	for(uint16_t i = 0; i < grid->widgets; i++) {
		widget_draw(render, grid->widget[i]);
	}
}

void layer_grid_index(layer_grid_t *grid, widget_t *widget) {
	for (uint16_t y = widget->y; y <= widget->Y; y++) {
		for (uint16_t x = widget->x; x <= widget->X; x++) {
			uint16_t pos = (grid->w * y) + x;
			if (grid->cell[pos] == NULL) grid->cell[pos] = SDL_calloc(1, sizeof(cell_t));
			grid->cell[pos]->widget = SDL_realloc(grid->cell[pos]->widget, (grid->cell[pos]->count + 1) * sizeof(widget_t *));
			grid->cell[pos]->widget[grid->cell[pos]->count] = widget;
			grid->cell[pos]->count++;
		}
	}
}

void layer_grid_add(layer_grid_t *grid, widget_t *widget) {
	widget->x = widget->rect.x / grid->size;
	widget->y = widget->rect.y / grid->size;
	widget->X = (widget->rect.x + widget->rect.w) / grid->size;
	widget->Y = (widget->rect.y + widget->rect.h) / grid->size;
	grid->widget = SDL_realloc(grid->widget, (grid->widgets + 1) * sizeof(widget_t *));
	grid->widget[grid->widgets] = widget;
	grid->widgets++;
	layer_grid_index(grid, widget);
}

void layer_grid_del(layer_grid_t *grid, widget_t *widget) {
	for (uint16_t y = widget->y; y <= widget->Y; y++) {
		for (uint16_t x = widget->x; x <= widget->X; x++) {
			uint16_t pos = (grid->w * y) + x;
			uint16_t t = 0;
			for(uint16_t i = 0; i < grid->cell[pos]->count; i++) {
				if (grid->cell[pos]->widget[i] == widget) {
					continue;
				}
				grid->cell[pos]->widget[t] = grid->cell[pos]->widget[i];
				t++;
			}
			grid->cell[pos]->count = t;
			grid->cell[pos]->widget = SDL_realloc(grid->cell[pos]->widget, grid->cell[pos]->count * sizeof(widget_t *));
			if(grid->cell[pos]->count == 0) {
				if(grid->cell[pos]->widget != NULL) SDL_free(grid->cell[pos]->widget);
				if(grid->cell[pos] != NULL) {
					SDL_free(grid->cell[pos]);
					grid->cell[pos] = NULL;
				}
			}
		}
	}
	uint16_t t = 0;
	for(uint16_t i = 0; i < grid->widgets; i++) {
		if(grid->widget[i] == widget) {
			widget_destroy(grid->widget[i]); // Should I destroyed it here?
			continue;
		}
		grid->widget[t] = grid->widget[i];
		t++;
	}
	grid->widgets = t;
	SDL_realloc(grid->widget, grid->widgets * sizeof(widget_t *));
}