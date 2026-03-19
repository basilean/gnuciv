#include "app.h"
#include "event.h"
#include "draw.h"

SDL_AppResult app_new(void **state, int argc, char **argv) {
	app_t *app = SDL_calloc(1,sizeof(app_t));
	if (!app) {
		SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "Failed allocating memory.\n");
		return SDL_APP_FAILURE;
	}

	app->event = SDL_calloc(1,sizeof(event_t));
	app->frame = SDL_calloc(1,sizeof(frame_t));
	app->frame->bg = (SDL_Color){.r = 200, .g = 0, .b = 0, .a = 255};

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

	if (SDL_SetRenderVSync(app->render, 1)) {
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "VSync failed: %s.\n", SDL_GetError());
	}

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

void app_clean(app_t *app) {
	if (app) {
		if (app->render) SDL_DestroyRenderer(app->render);
		if (app->win) SDL_DestroyWindow(app->win);
		if (app->event) SDL_free(app->event);
		if (app->frame) SDL_free(app->frame);
		SDL_free(app);
	}
}