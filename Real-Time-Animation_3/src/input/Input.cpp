#include "Input.h"
#include "core\game_objects\GameObject.h"
#include "..\gameobjects\Skeleton.h"
#include "..\gameobjects\Target.h"
#include <glm\ext.hpp>

Input::Input(Application* app) : InputManager(app) {}

Input::~Input() {}

void Input::key_callback(int key, int scancode, int action, int mode) {
	InputManager::key_callback(key, scancode, action, mode);
	this->process_camera_movement();
	if (keys[GLFW_KEY_F]) app->get_window()->set_full_screen(!app->get_window()->get_full_screen());
	if (keys[GLFW_KEY_P]) app->set_debug(!app->get_debug());

	GameObject* target = app->get_component<GameObject>("target");
	glm::vec3 velocity = target->get_speed();

	if (keys[GLFW_KEY_I]) target->set_speed(glm::vec3(velocity.x, 3, velocity.z));
	else if (keys[GLFW_KEY_K]) target->set_speed(glm::vec3(velocity.x, -3, velocity.z));


	if (keys[GLFW_KEY_L]) target->set_speed(glm::vec3(3,velocity.y, velocity.z));
	else if (keys[GLFW_KEY_J]) target->set_speed(glm::vec3(-3, velocity.y , velocity.z));

	if (keys[GLFW_KEY_O]) target->set_speed(glm::vec3(velocity.x, velocity.y, 3));
	else if (keys[GLFW_KEY_U]) target->set_speed(glm::vec3(velocity.y , velocity.y, -3));

	if(!keys[GLFW_KEY_I] &&! keys[GLFW_KEY_K]&& !keys[GLFW_KEY_J]&& !keys[GLFW_KEY_L] && !keys[GLFW_KEY_O] && !keys[GLFW_KEY_U])target->set_speed(glm::vec3(0));
	
	if (keys[GLFW_KEY_T]) app->get_component<Skeleton>("skeleton")->add_new_bone();
	
	if (keys[GLFW_KEY_Y]) app->get_component<Skeleton>("skeleton")->remove_bone();

	if (keys[GLFW_KEY_M]) std::cout << glm::to_string(app->get_component<GameObject>("target")->get_pos()) << std::endl;

	if (!keys[GLFW_KEY_SPACE]) {
		if (keys[GLFW_KEY_1]) app->get_component<Target>("target")->start_keyframe_animation(0);
		if (keys[GLFW_KEY_2]) app->get_component<Target>("target")->start_keyframe_animation(1);
		if (keys[GLFW_KEY_3]) app->get_component<Target>("target")->start_keyframe_animation(2);
		if (keys[GLFW_KEY_4]) app->get_component<Target>("target")->start_keyframe_animation(3);
		if (keys[GLFW_KEY_5]) app->get_component<Target>("target")->start_keyframe_animation(4);
		if (keys[GLFW_KEY_6]) app->get_component<Target>("target")->start_keyframe_animation(5);
		if (keys[GLFW_KEY_7]) app->get_component<Target>("target")->start_keyframe_animation(6);
		if (keys[GLFW_KEY_8]) app->get_component<Target>("target")->start_keyframe_animation(7);
		if (keys[GLFW_KEY_9]) app->get_component<Target>("target")->start_keyframe_animation(8);
		if (keys[GLFW_KEY_0]) app->get_component<Target>("target")->start_keyframe_animation(9);

		if (keys[GLFW_KEY_Z]) {
			if (keys[GLFW_KEY_1]) app->get_component<Target>("target")->prepare_spline_animation(0);
			if (keys[GLFW_KEY_2]) app->get_component<Target>("target")->prepare_spline_animation(1);
			if (keys[GLFW_KEY_3]) app->get_component<Target>("target")->prepare_spline_animation(2);
		}
	} else if (keys[GLFW_KEY_SPACE]){
		if (keys[GLFW_KEY_1]) app->get_component<Target>("target")->start_spline_animation(0);
		if (keys[GLFW_KEY_2]) app->get_component<Target>("target")->start_spline_animation(1);
		if (keys[GLFW_KEY_3]) app->get_component<Target>("target")->start_spline_animation(2);
	} 

	if (keys[GLFW_KEY_V]) { 
		app->get_component<Target>("target")->set_circular_speed(glm::vec2(0, 200));
		app->get_component<Target>("target")->set_distance_from_center(1);
	}	else {
		app->get_component<Target>("target")->set_circular_speed(glm::vec2(0, 200));
		app->get_component<Target>("target")->set_distance_from_center(0);
	}
	

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
