#include "event.h"
#include "app.h"

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

		case SDL_EVENT_WINDOW_MOVED:
			SDL_Log("Window moved: %d, %d", event->window.data1, event->window.data2);
			break;

		case SDL_EVENT_KEY_DOWN:
			code = SDL_GetKeyFromScancode(event->key.scancode, event->key.mod, true);
			app->event->key.code[app->event->key.count] = code;
			app->event->key.count++;
//			SDL_Log("Key down: %s (scancode %d)", SDL_GetKeyName(code), event->key.scancode);
			break;

//		case SDL_EVENT_KEY_UP:
//			code = SDL_GetKeyFromScancode(event->key.scancode, event->key.mod, true);
//			SDL_Log("Key up: %s (scancode %d)", SDL_GetKeyName(code), event->key.scancode);
//			break;

		case SDL_EVENT_MOUSE_MOTION:
			app->event->mouse.state = SDL_GetMouseState(&app->event->mouse.motion.x, &app->event->mouse.motion.y);
			app->event->mouse.is_motion = 1;
//			SDL_Log("Mouse moved: %f, %f | %d", app->event.mouse.motion.x, app->event.mouse.motion.y, mstate);
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
//			SDL_Log("Mouse button down: %d", event->button.button);
			app->event->mouse.state = SDL_GetMouseState(&app->event->mouse.motion.x, &app->event->mouse.motion.y);
//			app->event->mouse.is_motion = 1;
//			app->event->mouse.motion = (SDL_FPoint){evt.motion.x, evt.motion.y};
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
			SDL_Log("L: %d | M: %d | R: %d", app->event->mouse.left.status, app->event->mouse.middle.status, app->event->mouse.right.status);
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
			SDL_Log("L: %d | M: %d | R: %d", app->event->mouse.left.status, app->event->mouse.middle.status, app->event->mouse.right.status);
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
	app->event->mouse.is_wheel = 0;
	app->event->mouse.wheel.x = 0;
	app->event->mouse.wheel.y = 0;
	app->event->mouse.is_motion = 0;
	app->event->key.count = 0;
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