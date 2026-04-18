#include "event.h"
#include "app.h"
#include "widget.h"

int is_click(SDL_FPoint *event, SDL_FPoint *down) {
	// TODO: Add optional pixel toleration.
	if (event->x == down->x && event->y == down->y) {
		return 1;
	}
	return 0;
}

SDL_AppResult event_call(app_t *app, SDL_Event *event) {
	SDL_Keycode code;
	switch (event->type)
	{
		case SDL_EVENT_QUIT:
			SDL_Log("Quit event received");
			return SDL_APP_SUCCESS;

		case SDL_EVENT_WINDOW_RESIZED:
			app->event->win.resize = 1;
			SDL_Log("Window resized: %d x %d", event->window.data1, event->window.data2);
			break;

//		case SDL_EVENT_WINDOW_MOVED:
//			SDL_Log("Window moved: %d, %d", event->window.data1, event->window.data2);
//			break;

		case SDL_EVENT_KEY_DOWN:
//			code = SDL_GetKeyFromScancode(event->key.scancode, event->key.mod, true);
			app->event->key.code[app->event->key.count] = event->key.scancode;
//			SDL_Log("Key: %d", app->event->key.code[app->event->key.count]);
			app->event->key.count++;
			break;

//		case SDL_EVENT_KEY_UP:
//			code = SDL_GetKeyFromScancode(event->key.scancode, event->key.mod, true);
//			SDL_Log("Key up: %s (scancode %d)", SDL_GetKeyName(code), event->key.scancode);
//			break;

		case SDL_EVENT_MOUSE_MOTION:
			int state = SDL_GetMouseState(&app->event->mouse.motion.x, &app->event->mouse.motion.y);
			if (state >= SDL_BUTTON_RMASK) {
				app->event->mouse.right.status = MOUSE_DRAG;
				state -= SDL_BUTTON_RMASK;
			}
			if (state >= SDL_BUTTON_MMASK) {
				app->event->mouse.middle.status = MOUSE_DRAG;
				state -= SDL_BUTTON_MMASK;
			}
			if (state >= SDL_BUTTON_LMASK) {
				app->event->mouse.left.status = MOUSE_DRAG;
				state -= SDL_BUTTON_LMASK;
			}
			if (state < 1) {
				app->event->mouse.is_motion = 1;
			}
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			app->event->mouse.state = SDL_GetMouseState(&app->event->mouse.motion.x, &app->event->mouse.motion.y);
			switch (event->button.button) {
				case SDL_BUTTON_LEFT:
					app->event->mouse.left.status = MOUSE_DOWN;
					app->event->mouse.left.down = app->event->mouse.motion;
					break;
				case SDL_BUTTON_MIDDLE:
					app->event->mouse.middle.status = MOUSE_DOWN;
					app->event->mouse.middle.down = app->event->mouse.motion;
					break;
				case SDL_BUTTON_RIGHT:
					app->event->mouse.right.status = MOUSE_DOWN;
					app->event->mouse.right.down = app->event->mouse.motion;
					break;
			}
			break;

		case SDL_EVENT_MOUSE_BUTTON_UP:
			app->event->mouse.state = SDL_GetMouseState(&app->event->mouse.motion.x, &app->event->mouse.motion.y);
			switch (event->button.button) {
				case SDL_BUTTON_LEFT:
					if (is_click(&app->event->mouse.motion, &app->event->mouse.left.down)) {
						app->event->mouse.left.status = MOUSE_CLICK;
					}
					else {
						app->event->mouse.left.status = MOUSE_DROP;
					}
					break;
				case SDL_BUTTON_MIDDLE:
					if (is_click(&app->event->mouse.motion, &app->event->mouse.middle.down)) {
						app->event->mouse.middle.status = MOUSE_CLICK;
					}
					else {
						app->event->mouse.middle.status = MOUSE_DROP;
					}
					break;
				case SDL_BUTTON_RIGHT:
					if (is_click(&app->event->mouse.motion, &app->event->mouse.right.down)) {
						app->event->mouse.right.status = MOUSE_CLICK;
					}
					else {
						app->event->mouse.right.status = MOUSE_DROP;
					}
					break;
			}
			app->event->is_event = true;
			break;

		case SDL_EVENT_MOUSE_WHEEL:
			app->event->mouse.wheel.x = event->wheel.x;
			app->event->mouse.wheel.y = event->wheel.y;
			app->event->mouse.is_wheel = 1;
			break;

//		default:
//			SDL_Log("Other event: %u", event->type);
//			break;
	}

	return SDL_APP_CONTINUE;
}

void event_clean(app_t *app) {
	app->event->is_event = false;

	app->event->mouse.is_wheel = 0;
	app->event->mouse.wheel.x = 0;
	app->event->mouse.wheel.y = 0;
	app->event->mouse.is_motion = 0;
	app->event->key.count = 0;
	app->event->win.resize = 0;
	// IF diff of none or down.
	if (app->event->mouse.left.status > 1) {
		app->event->mouse.left.status = 0;
	}
	if (app->event->mouse.middle.status > 1) {
		app->event->mouse.middle.status = 0;
	}
	if (app->event->mouse.right.status > 1) {
		app->event->mouse.right.status = 0;
	}

//	app->event->mouse.state = 0;
//	app->event->mouse.motion.x = 0;
//	app->event->mouse.motion.y = 0;
}