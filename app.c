#include "app.h"
#include "event.h"
#include "layer/layer.h"

SDL_AppResult app_new(void **state, int argc, char **argv) {
	app_t *app = SDL_calloc(1, sizeof(app_t));
	if (!app) {
		SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Failed allocating memory.\n");
		return SDL_APP_FAILURE;
	}

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "Video target %s.\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if(SDL_Init(SDL_INIT_AUDIO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Audio %s.\n", SDL_GetError());
	}

//		if (TTF_Init() < 0) {
//			SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "%s.\n", SDL_GetError());
//			return SDL_APP_FAILURE;
//		}

	app->win = SDL_CreateWindow(
		"GNU Civ",
		320,
		240,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_VULKAN
	);

	app->render = SDL_CreateRenderer(
		app->win,
		NULL
	);

	if (SDL_SetRenderVSync(app->render, 1) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "VSync failed: %s.\n", SDL_GetError());
	}

	app->event = SDL_calloc(1, sizeof(event_t));

	*state = app;
  app_info();
	return SDL_APP_CONTINUE;
}

void app_info() {
	SDL_Log("CPU: %d", SDL_GetNumLogicalCPUCores());
	SDL_Log("RAM: %d", SDL_GetSystemRAM());
	SDL_Log("Video: %s", SDL_GetCurrentVideoDriver());
	SDL_Log("Audio: %s", SDL_GetCurrentAudioDriver());
}

static inline bool in_frect(const SDL_FPoint *p, const SDL_FRect *r) {
	return (p->x >= r->x) &&
		(p->x <  r->x + r->w) &&
		(p->y >= r->y) &&
		(p->y <  r->y + r->h);
}

void app_input(app_t *app) {
	if(app->event->mouse.is_event) {
		for(uint16_t i = app->layers->count; i > 0; i--) {
			if(!app->layers->layer[i - 1]->enable || !app->layers->layer[i - 1]->active) {
				continue;
			}
			SDL_Log("Check layer: %d", i - 1);
			switch(app->layers->layer[i - 1]->type) {
				case LAYER_GRID:
						uint16_t x = app->event->mouse.motion.x / app->layers->layer[i - 1]->grid->size;
						uint16_t y = app->event->mouse.motion.y / app->layers->layer[i - 1]->grid->size;
						uint16_t pos = (app->layers->layer[i - 1]->grid->w * y) + x;
						if(app->layers->layer[i - 1]->grid->cell[pos] != NULL) {
							SDL_Log("Cell with content: %d", pos);
							SDL_FPoint point = {app->event->mouse.motion.x, app->event->mouse.motion.y};
							for(uint16_t ii = app->layers->layer[i - 1]->grid->cell[pos]->count; ii > 0; ii--) {
//								if(!app->layers->layer[i - 1]->enable || !app->layers->layer[i - 1]->active) {
//									continue;
//								}
								if(in_frect(&point, &app->layers->layer[i - 1]->grid->cell[pos]->widget[ii - 1]->rect)) {
									SDL_Log("Widget: %d", ii - 1);
								}
							}
						}
						break;
			}
		}
	}
}

void app_resize(app_t *app) {
	if (!app->event->win.resize) {
		return;
	}
	for(uint16_t i = 0; i < app->layers->count; i++) {
		layer_resize(app->render, app->layers->layer[i]);
	}
	app->event->win.resize = 0;
}

void app_draw(app_t *app) {
	SDL_SetRenderDrawColor(app->render, 0, 0, 0, 0);
	SDL_RenderClear(app->render);
	for(uint16_t i = 0; i < app->layers->count; i++) {
		if (!app->layers->layer[i]->enable) continue;
		layer_draw(app->render, app->layers->layer[i]);
	}
	SDL_RenderPresent(app->render);
}

void app_clean(app_t *app) {
	if (app) {
		layer_list_destroy(app->layers);
		if (app->event) SDL_free(app->event);
		if (app->render) SDL_DestroyRenderer(app->render);
		if (app->win) SDL_DestroyWindow(app->win);
		SDL_free(app);
	}
}
