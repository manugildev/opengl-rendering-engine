#include "Light.h"
#include <glm\gtc\type_ptr.hpp>

Light::Light(Application* app, glm::vec3 position, glm::vec3 light_color) : GameObject(app, new Mesh("models/sphere.obj")), position(position), light_color(light_color) {
	this->model_mat = glm::translate(glm::mat4(1.0f), position);
}

void Light::set_shader_program(LampShader* shader_program) {
	this->shader_program = shader_program;
	this->set_initial_shader_values();
}

void Light::set_initial_shader_values() {
	this->shader_program->start();
	this->shader_program->stop();
}


void Light::update(float delta_time) {}

void Light::render() {
	shader_program->start();

	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();

	shader_program->set_object_color(light_color);
	shader_program->set_view_matrix(view);
	shader_program->set_proj_matrix(perspective_proj);
	shader_program->set_model_matrix(model_mat);

	mesh->draw();

	shader_program->stop();
}

glm::vec3 Light::get_position() {
	return this->position;
}

glm::vec3 Light::get_light_color() {
	return this->light_color;
}

Light::~Light() {}