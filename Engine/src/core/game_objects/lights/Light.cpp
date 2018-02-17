#include "Light.h"
#include "..\..\Application.h"
#include <glm\gtc\type_ptr.hpp>
#include <glm\ext.hpp>

Light::Light(Application* app, glm::vec3 light_position, glm::vec3 light_color) : GameObject("Light", app, new Model("models/sphere.obj")), light_position(light_position), light_color(light_color) {
	this->set_model_mat(glm::translate(glm::mat4(1.0f), light_position));
	this->set_pos(light_position);
	this->set_scale(glm::vec3(0.3f));
}

void Light::set_shader_program(LampShader* shader_program) {
	this->shader_program = shader_program;
	this->set_initial_shader_values();
}

void Light::set_initial_shader_values() {
	this->shader_program->start();
	this->shader_program->stop();
}

void Light::render() {
	if (!shader_program) return;

	shader_program->start();
	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();

	shader_program->set_object_color(light_color);
	shader_program->set_view_matrix(view);
	shader_program->set_proj_matrix(perspective_proj);
	shader_program->set_model_matrix(get_model_mat());

	if (app->is_debug()) {
		model->draw(nullptr, GL_LINES);
	} else model->draw();
	shader_program->stop();
}

void Light::update(float delta_time) {
	GameObject::update(delta_time);
	app->update_lights();
}

glm::vec3 Light::get_light_position() {
	return glm::vec3(get_model_mat()[3][0], get_model_mat()[3][1], get_model_mat()[3][2]);
}

glm::vec3 Light::get_light_color() {
	return this->light_color;
}

Light::~Light() {}