#include "InputManager.h"
#include "core\Application.h"

InputManager::InputManager(Application * app) : app(app) {
	// TODO: This will be helpful when you start without the mouse
	last_x = app->get_window()->get_width() / 2.0f;
	last_y = app->get_window()->get_height() / 2.0f;
}


InputManager::~InputManager(){
}

void InputManager::key_callback(int key, int scancode, int action, int mode){
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) keys[key] = true;
		else if (action == GLFW_RELEASE) keys[key] = false;
	}
}

void InputManager::scroll_callback(double x_offset, double y_offset){
}

void InputManager::mouse_callback(double x_pos, double y_pos){
	if (first_mouse) {
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = false;
	}

	x_offset = x_pos - last_x;
	y_offset = last_y - y_pos;

	last_x = x_pos;
	last_y = y_pos;
}
