#include "Car.h"
#include <glm\ext.hpp>
#include "..\GameObject.h"
#include "..\..\util\shaders\lighting\LightingShader.h"
#include "..\..\Application.h"

Car::Car(Application * app, Model* model, glm::vec3 object_color) : GameObject(app, model, object_color) {
	this->initial_position = this->get_pos();
}

void Car::update(float delta_time) {
	GameObject::update(delta_time);
	this->distance_traveled = glm::length(this->get_pos() - this->initial_position);
	if (this->distance_traveled > city_size - 5 && !animation_running) {
		start_turn_around_animation();
	}
	if (animation_running && std::abs(this->get_rotation()[1] - this->initial_rotation_y) > (180.0f)) {
		stop_turn_around_animation();
	}
}


void Car::set_initial_pos(glm::vec3 pos) {
	this->initial_position = pos;
	this->set_pos(pos);
}

void Car::start_turn_around_animation() {
	animation_running = true;
	initial_rotation_y = get_rotation()[1];
	initial_speed = get_speed();

	if (get_speed()[2] > 0)
		set_pos(glm::vec3(get_pos()[0], get_pos()[1], city_size - 4.999f));
	else if (get_speed()[2] < 0)
		set_pos(glm::vec3(get_pos()[0], get_pos()[1], -city_size + 4.999f));
	else if (get_speed()[0] > 0)
		set_pos(glm::vec3(city_size - 4.999f, get_pos()[1], get_pos()[2]));
	else if (get_speed()[0] < 0)
		set_pos(glm::vec3(-city_size + 4.999f, get_pos()[1], get_pos()[2]));

	previous_random_mutiplier = std::rand() < RAND_MAX / 2 ? 1.0f : -1.0f;
	set_speed(glm::vec3(0.0f));
	set_acceleration(glm::vec3(0.0f));
	set_rotation_acceleration(glm::vec3(0.0f, (std::rand() % 120 + 50) * previous_random_mutiplier, 0.0f));
}

void Car::stop_turn_around_animation() {
	set_rotation(glm::vec3(0, this->initial_rotation_y + (180 * previous_random_mutiplier), 0));
	initial_rotation_y = get_rotation()[1];
	set_rotation_speed(glm::vec3(0.0f));
	set_rotation_acceleration(glm::vec3(0.0f));
	set_speed(initial_speed * -1.0f);
	animation_running = false;
}

void Car::render() {
	this->shader_program->start();
	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();

	LightingShader* lighting_shader = dynamic_cast<LightingShader*>(shader_program);
	if (lighting_shader) {
		lighting_shader->set_view_matrix(view);
		lighting_shader->set_proj_matrix(perspective_proj);
		lighting_shader->set_model_matrix(model_mat);

		lighting_shader->set_object_color(this->object_color);
		lighting_shader->set_mix_power(this->get_mix_power());
	}

	this->model->materials[2].diffuse_color = object_color;
	if (this->app->is_debug()) { // TODO: Make this work again
		this->model->draw(nullptr, GL_LINES);
	}
	else this->model->draw(this->shader_program);
	this->shader_program->stop();
}


Car::~Car() {}
