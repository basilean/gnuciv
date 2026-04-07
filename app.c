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

void app_input(app_t *app) {

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
