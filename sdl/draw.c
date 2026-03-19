#include "draw.h"
#include "app.h"
#include "event.h"

void draw_frame(app_t *app) {
	app->frame->size.x += app->event->mouse.wheel.y;
	app->frame->size.y += app->event->mouse.wheel.y;

	for(uint8_t i = 0; i < app->event->key.count; i++) {
		SDL_Log("K: %s (%d)",
			SDL_GetKeyName(app->event->key.code[i]),
			app->event->key.code[i]
		);
	}

	SDL_SetRenderDrawColor(
		app->render,
		app->frame->bg.r,
		app->frame->bg.g,
		app->frame->bg.b,
		app->frame->bg.a
	);
	SDL_RenderClear(app->render);

	SDL_FRect rect = {
		app->event->mouse.motion.x - (app->frame->size.y / 2),
		app->event->mouse.motion.y - (app->frame->size.y / 2),
		app->frame->size.x,
		app->frame->size.y
	};
	if(app->event->mouse.is_motion && app->event->mouse.state) {
		SDL_SetRenderDrawColor(
			app->render,
			0,
			0,
			200,
			255
		);
	}
	else {
		SDL_SetRenderDrawColor(
			app->render,
			0,
			200,
			0,
			255
		);
	}

	SDL_RenderFillRect(app->render, &rect);
	SDL_RenderPresent(app->render);
}