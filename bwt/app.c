#include <SDL3_ttf/SDL_ttf.h>
#include "config.h"
#include "app.h"
#include "event.h"
#include "layer/layer.h"
#include "position.h"

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

	if (TTF_Init() < 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "%s.\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	app->screen = (SDL_FRect){0, 0, SCREEN_MIN_W, SCREEN_MIN_H};

	app->win = SDL_CreateWindow(
		WINDOW_TITLE,
		app->screen.w,
		app->screen.h,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_VULKAN
	);

	SDL_SetWindowMinimumSize(app->win, SCREEN_MIN_W, SCREEN_MIN_H);
	SDL_SetWindowMaximumSize(app->win, SCREEN_MAX_W, SCREEN_MAX_H);

	app->render = SDL_CreateRenderer(
		app->win,
		NULL
	);

	if (SDL_SetRenderVSync(app->render, 1) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "VSync failed: %s.\n", SDL_GetError());
	}

	app->event = SDL_calloc(1, sizeof(event_t));
	app->event->win.resize = true;
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
	if(!app->event->is_event) {
		return;
	}
	for(uint16_t i = app->layers->count; i > 0; i--) {
//		SDL_Log("LAYER INPUT: %d", i - 1);
		if(layer_input(app->event, app->layers->layer[i - 1])) {
			// Finish loop when someone takes care of event.
			return;
		}
	}
}

void app_resize(app_t *app) {
	if (!app->event->win.resize) {
		return;
	}
	int w, h;
	SDL_GetCurrentRenderOutputSize(app->render, &w, &h);
	app->screen.w = w;
	app->screen.h = h;
	for(uint16_t i = 0; i < app->layers->count; i++) {
		position_set(&app->screen, &app->layers->layer[i]->pos);
		layer_resize(app, app->layers->layer[i]);
	}
}

void app_draw(app_t *app) {
	app_resize(app);
	SDL_SetRenderDrawColor(app->render, 0, 0, 0, 0);
	SDL_RenderClear(app->render);
	for(uint16_t i = 0; i < app->layers->count; i++) {
		if (!app->layers->layer[i]->enable) continue;
		layer_draw(app->render, app->layers->layer[i]);
	}
	SDL_RenderPresent(app->render);
}

void app_quit(app_t *app) {
	if (!app) {
		SDL_Quit();
	}
	layers_destroy(app->layers);
	if (app->event) SDL_free(app->event);
	if (app->render) SDL_DestroyRenderer(app->render);
	if (app->win) SDL_DestroyWindow(app->win);
	SDL_free(app);
	SDL_Quit();
}

SDL_AppResult app_event(app_t *app, SDL_Event *event) {
	return event_call(app, event);
}

SDL_AppResult app_continue(app_t *app) {
	event_clean(app);
	return SDL_APP_CONTINUE;
}