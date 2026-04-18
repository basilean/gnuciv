#ifndef APP_H
#define APP_H
#include <SDL3/SDL.h>

typedef struct event_t event_t;
typedef struct layers_t layers_t;

typedef struct app_t {
	SDL_Window* win;
	SDL_Renderer* render;
	event_t *event;
	layers_t *layers;
	SDL_FRect screen;
} app_t;

SDL_AppResult app_new(void **, int, char **);
void app_quit(app_t *);
void app_input(app_t *);
void app_draw(app_t *);
void app_resize(app_t *);
void app_info();
SDL_AppResult app_event(app_t *, SDL_Event *);
SDL_AppResult app_continue(app_t *);
#endif