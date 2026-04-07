#include "game.h"
#include "event.h"
#include "layer/widget_box.h"
#include "layer/layer.h"

#define COLOR_BLACK (SDL_Color){255, 255, 255, 255}
#define COLOR_GREEN (SDL_Color){0, 255, 0, 255}
#define COLOR_GRAY_50 (SDL_Color){127, 127, 127, 127}

void game_init(app_t *app) {
	app->layers = layer_list_new();

	layer_t *bg = layer_bg_new(app->render, COLOR_BLACK, "bg.png", 255);
	layer_list_add(app->layers, bg);
	bg->pos.anchor = FULL;

	layer_t *grid = layer_grid_new(app->render, 60, COLOR_GRAY_50);
	layer_list_add(app->layers, grid);
	grid->enable = false;
	grid->pos.min = (SDL_FRect){20, 20, 200, 200};
	grid->pos.max = (SDL_FRect){40, 40, 400, 400};
	widget_t *widget = widget_box_new(app->render, (SDL_FRect){20, 20, 100, 100}, COLOR_GREEN);
	layer_grid_add(grid->grid, widget);
	widget_t *widget2 = widget_box_new(app->render, (SDL_FRect){130, 130, 50, 50}, COLOR_BLACK);
	layer_grid_add(grid->grid, widget2);

	SDL_Log("Layers: %d", app->layers->count);
	SDL_Log("Widgets: %d", grid->grid->widgets);
}

void game_input(app_t *app) {
	for(uint8_t i = 0; i < app->event->key.count; i++) {
		SDL_Log("Key: %d", app->event->key.code[i]);
		switch(app->event->key.code[i]) {
			case 68:
				app->layers->layer[1]->enable ^= true;
				break;
		}
	}
}

void game_logic(app_t *app) {
}