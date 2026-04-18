#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "bwt/app.h"
#include "game.h"

SDL_AppResult SDL_AppInit(void **app, int argc, char **argv)
{
	SDL_AppResult rc = app_new(app, argc, argv);
	game_init(*app); // <- Init all components for this game.
	return rc;
}

SDL_AppResult SDL_AppEvent(void *app, SDL_Event *event)
{
	return app_event(app, event);
}

SDL_AppResult SDL_AppIterate(void *app)
{
	app_input(app); // <- Do something with events according to layer/widget.
	game_logic(app); // <- Whatever game does.
	app_draw(app);
	return app_continue(app);
}

void SDL_AppQuit(void *app, SDL_AppResult result)
{
	app_quit(app);
}
