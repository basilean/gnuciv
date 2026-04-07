#ifndef EVENT_H
#define EVENT_H
#include <SDL3/SDL.h>

#define KEY_MAX 8
typedef struct widget_t widget_t;

typedef struct {
	int count;
	SDL_Scancode code[KEY_MAX];	
} event_key_t;

typedef enum {
	MOUSE_NONE = 0,
	MOUSE_DOWN,
	MOUSE_CLICK,
	MOUSE_DRAG,
	MOUSE_DROP,
} event_mouse_status_t;

typedef struct {
	event_mouse_status_t status;
	SDL_FPoint down;
	SDL_FPoint off;
	widget_t *widget;
} event_mouse_button_t;

typedef struct {
	uint8_t is_motion;
	SDL_FPoint motion;
	SDL_MouseButtonFlags state;
	uint8_t is_wheel;
	SDL_FPoint wheel;

	event_mouse_button_t left;
	event_mouse_button_t middle;
	event_mouse_button_t right;
} event_mouse_t;

typedef union {
	struct {
		uint8_t resize : 1;
		uint8_t notused : 6;
		uint8_t quit : 1;
	};
	uint8_t all;
} event_win_t;

typedef struct event_t {
	event_win_t win;
	event_key_t key;
	event_mouse_t mouse;
} event_t;

typedef struct app_t app_t;
typedef struct event_t event_t;

SDL_AppResult event_call(app_t *, SDL_Event *);
void event_clean(app_t *);
#endif