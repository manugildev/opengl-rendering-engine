#include "Input.h"
#include "core\game_objects\GameObject.h"

Input::Input(Application* app) : InputManager(app) {}

Input::~Input() {}

void Input::key_callback(int key, int scancode, int action, int mode) {
	InputManager::key_callback(key, scancode, action, mode);
	this->process_camera_movement();
	if (keys[GLFW_KEY_U]) app->get_window()->set_full_screen(!app->get_window()->get_full_screen());
}

void Input::scroll_callback(double x_offset, double y_offset) {
	InputManager::scroll_callback(x_offset, y_offset);

}

void Input::mouse_callback(double x_pos, double y_pos) {
	InputManager::mouse_callback(x_pos, y_pos);
	app->get_camera()->process_mouse(x_offset, y_offset);
}

void Input::process_camera_movement() {
	if (keys[GLFW_KEY_W]) app->get_camera()->process_keyboard(FORWARD);
	if (keys[GLFW_KEY_S]) app->get_camera()->process_keyboard(BACKWARD);
	if (keys[GLFW_KEY_A]) app->get_camera()->process_keyboard(LEFT);
	if (keys[GLFW_KEY_D]) app->get_camera()->process_keyboard(RIGHT);


	if (keys[GLFW_KEY_E]) app->get_camera()->process_keyboard(ROLL_RIGHT);
	if (keys[GLFW_KEY_Q]) app->get_camera()->process_keyboard(ROLL_LEFT);

	if (!(keys[GLFW_KEY_W]) &&
		!(keys[GLFW_KEY_S]) &&
		!(keys[GLFW_KEY_A]) &&
		!(keys[GLFW_KEY_D])) app->get_camera()->process_keyboard(STOP);
}
