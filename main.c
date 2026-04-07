#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "app.h"
#include "event.h"
#include "game.h"

SDL_AppResult SDL_AppInit(void **app, int argc, char **argv)
{
	SDL_AppResult rc = app_new(app, argc, argv);
	game_init(*app);// <- Init all components for this game.
	return rc;
}

SDL_AppResult SDL_AppEvent(void *app, SDL_Event *event)
{
	return event_call(app, event);
}

SDL_AppResult SDL_AppIterate(void *app)
{
	app_input(app); // <- Do something with events according to layer/widget.
	game_input(app); // <- events for this specific game.
	game_logic(app);// <- Whatever game does.
	app_resize(app);
	app_draw(app);
	event_clean(app);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *app, SDL_AppResult result)
{
	app_clean(app);
	SDL_Quit();
}
