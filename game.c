#include "bwt/config.h"
#include "bwt/event.h"
#include "bwt/widget/box.h"
#include "bwt/layer/layer.h"
#include "game.h"

void game_hello() {
	SDL_Log("Hello World!");
}

void game_init(app_t *app) {
	app->layers = layers_new();

	layer_t *bg = layer_bg_new(app->render, COLOR_BLACK, "bg.png", 255);
	layers_add(app->layers, bg);
	bg->pos.anchor = FULL;

	layer_t *grid = layer_grid_new(app, 60, COLOR_GRAY_20);
//	grid->enable = false;
	grid->pos.min = (SDL_FRect){20, 20, 200, 200};
	grid->pos.max = (SDL_FRect){40, 40, 400, 400};
	grid->pos.anchor = MIDDLE_CENTER;
	layers_add(app->layers, grid);

	widget_t *widget = widget_box_new(app->render, (SDL_FRect){20, 20, 100, 100}, COLOR_GREEN);
	widget->click = game_hello;
	layer_grid_add(grid->grid, widget);

	widget_t *widget2 = widget_box_new(app->render, (SDL_FRect){130, 130, 50, 50}, COLOR_BLACK);
	layer_grid_add(grid->grid, widget2);

	SDL_Log("Layers: %d", app->layers->count);
	SDL_Log("Widgets: %d", grid->grid->widgets);
//	app->event->win.resize = true;
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
	game_input(app); // <- Events for this specific game.
}