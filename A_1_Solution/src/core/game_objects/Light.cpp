#include "Light.h"
#include <glm\gtc\type_ptr.hpp>

Light::Light(Application* app) : GameObject(app, new Mesh("models/sphere.obj")), light_pos(0.0f, 0.0f, 0.0f), light_color(0.5f, 0.3f, 0.5f) {
	this->model_mat = glm::translate(glm::mat4(1.0f), light_pos);
}

Light::~Light() {}

void Light::set_shader_program(LampShader* shader_program) {
	this->shader_program = shader_program;
	this->set_initial_shader_values();
}

void Light::set_initial_shader_values() {
}


void Light::update(float delta_time) {}

void Light::render() {
	shader_program->start();

	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();

	shader_program->set_view_matrix(view);
	shader_program->set_proj_matrix(perspective_proj);
	shader_program->set_model_matrix(model_mat);

	mesh->draw();

	shader_program->stop();

}