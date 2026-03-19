#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include "sdl/app.h"
#include "sdl/event.h"
#include "sdl/draw.h"

SDL_AppResult SDL_AppInit(void **app, int argc, char **argv)
{
	return app_new(app, argc, argv);
}

SDL_AppResult SDL_AppEvent(void *app, SDL_Event *event)
{
	return event_call(app, event);
}

SDL_AppResult SDL_AppIterate(void *app)
{
	draw_frame(app);
	event_clean(app);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *app, SDL_AppResult result)
{
	app_clean(app);
	SDL_Quit();
}
