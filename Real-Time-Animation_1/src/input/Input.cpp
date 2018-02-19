#include "Input.h"
#include "core\game_objects\plane\Plane.h"

Input::Input(Application* app) : InputManager(app) {
}


Input::~Input() {
}

void Input::key_callback(int key, int scancode, int action, int mode) {
	InputManager::key_callback(key, scancode, action, mode);
	this->process_camera_movement();

	/* City Rotation */
	if (keys[GLFW_KEY_J]) app->get_component<GameObject>("city")->set_rotation_speed(glm::vec3(0.0f, -30.0f, 0.0f));
	if (keys[GLFW_KEY_L]) app->get_component<GameObject>("city")->set_rotation_speed(glm::vec3(0.0f, 30.0f, 0.0f));
	if (!keys[GLFW_KEY_L] && !keys[GLFW_KEY_J]) {
		app->get_component<GameObject>("city")->set_rotation_acceleration(glm::vec3(0.0f));
		app->get_component<GameObject>("city")->set_rotation_speed(glm::vec3(0.0f));
	}

	/* Plane Rotation */ //Todo: Get direction instead of pointer
	Plane* plane = app->get_component<Plane>("plane");
	if (keys[GLFW_KEY_Z]) {
		plane->set_speed_y(-60.0f);

		if (!plane->with_quaternions) plane->get_green_arrow()->set_rotation_speed(glm::vec3(0, -60.0f, 0.0f));
	}
	if (keys[GLFW_KEY_X]) {
		plane->set_speed_y(60.0f);
		if (!plane->with_quaternions) plane->get_green_arrow()->set_rotation_speed(glm::vec3(0, 60.0f, 0.0f));
	}
	if (!keys[GLFW_KEY_Z] && !keys[GLFW_KEY_X]) {
		plane->set_speed_y(0);
		if (!plane->with_quaternions) plane->get_green_arrow()->set_rotation_speed(glm::vec3(0, 0.0f, 0.0f));
	}

	if (keys[GLFW_KEY_C]) {
		plane->set_speed_z(60.0f);
		if (!plane->with_quaternions) plane->get_blue_arrow()->set_rotation_speed(glm::vec3(0, 0.0f, -60.0f));
	}
	if (keys[GLFW_KEY_V]) {
		plane->set_speed_z(-60.0f);
		if (!plane->with_quaternions) plane->get_blue_arrow()->set_rotation_speed(glm::vec3(0, 0.0f, 60.0f));
	}
	if (!keys[GLFW_KEY_C] && !keys[GLFW_KEY_V]) {
		plane->set_speed_z(0);
		if (!plane->with_quaternions) plane->get_blue_arrow()->set_rotation_speed(glm::vec3(0, 0.0f, 0.0f));
	}

	if (keys[GLFW_KEY_B]) {
		plane->set_speed_x(-60.0f);
		if (!plane->with_quaternions) plane->get_red_arrow()->set_rotation_speed(glm::vec3(0, 0.0f, -60.0f));
	}
	if (keys[GLFW_KEY_N]) {
		plane->set_speed_x(60.0f);
		if (!plane->with_quaternions) plane->get_red_arrow()->set_rotation_speed(glm::vec3(0.0f, 0.0f, 60.0f));
	}
	if (!keys[GLFW_KEY_B] && !keys[GLFW_KEY_N]) {
		plane->set_speed_x(0);
		if (!plane->with_quaternions) plane->get_red_arrow()->set_rotation_speed(glm::vec3(0, 0.0f, 0.0f));
	}

	if (keys[GLFW_KEY_R]) {
		app->get_camera()->first_person = !app->get_camera()->first_person;
	}

	if (keys[GLFW_KEY_M]) {
		plane->with_quaternions = !plane->with_quaternions;
		plane->show_debug = !plane->show_debug;
		plane->transform = glm::angleAxis(glm::radians(-90.0f), glm::vec3(0, 0, 1)); // We init the transform quaternion to 0.0f in the forward vector
		plane->transform = plane->transform * glm::angleAxis(glm::radians(90.0f), glm::vec3(-1, 0, 0));
	}

	if (keys[GLFW_KEY_P]) {
		app->set_debug(!app->get_debug());
	}

	if (keys[GLFW_KEY_U]) {
		app->get_window()->set_full_screen(!app->get_window()->get_full_screen());
	}
}

void Input::scroll_callback(double x_offset, double y_offset) {
	InputManager::scroll_callback(x_offset, y_offset);
	if (keys[GLFW_KEY_1] || keys[GLFW_KEY_2] || keys[GLFW_KEY_3]) {
		if (keys[GLFW_KEY_1]) {
			float cook_r = app->get_component<GameObject>("teapot3")->get_cook_r() + ((float) y_offset / 10);
			app->get_component<GameObject>("teapot3")->set_cook_r(cook_r);
		}

		if (keys[GLFW_KEY_2]) {
			float cook_f0 = app->get_component<GameObject>("teapot3")->get_cook_f0() + ((float) y_offset / 10);
			app->get_component<GameObject>("teapot3")->set_cook_f0(cook_f0);
		}

		if (keys[GLFW_KEY_3]) {
			float cook_k = app->get_component<GameObject>("teapot3")->get_cook_k() + ((float) y_offset / 10);
			app->get_component<GameObject>("teapot3")->set_cook_k(cook_k);
		}
		return;
	}

	if (!keys[GLFW_KEY_SPACE]) {
		float specular_power;
		if (keys[GLFW_KEY_4]) {
			specular_power = app->get_component<GameObject>("teapot2")->get_specular_power() + (float) y_offset;
			app->get_component<GameObject>("teapot2")->set_specular_power(specular_power);
		}
		else {
			specular_power = app->get_component<GameObject>("teapot2")->get_specular_power() + (float) y_offset;
			app->get_component<GameObject>("teapot2")->set_specular_power(specular_power);
		}
	}
	else {
		float specular_strength;
		if (keys[GLFW_KEY_4]) {
			specular_strength = app->get_component<GameObject>("teapot3")->get_specular_strength() + ((float)y_offset / 10);
			app->get_component<GameObject>("teapot3")->set_specular_strength(specular_strength);
		}
		else {
			specular_strength = app->get_component<GameObject>("teapot3")->get_specular_strength() + ((float)y_offset / 10);
			app->get_component<GameObject>("teapot3")->set_specular_strength(specular_strength);
		}
	}
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
