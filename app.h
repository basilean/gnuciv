#ifndef APP_H
#define APP_H
#include <SDL3/SDL.h>

typedef struct event_t event_t;
typedef struct layer_list_t layer_list_t;

typedef struct app_t {
	SDL_Window* win;
	SDL_Renderer* render;
	event_t *event;
	layer_list_t *layers;
} app_t;

SDL_AppResult app_new(void **, int, char **);
void app_clean(app_t *);
void app_input(app_t *);
void app_draw(app_t *);
void app_resize(app_t *);
void app_info();
#endif