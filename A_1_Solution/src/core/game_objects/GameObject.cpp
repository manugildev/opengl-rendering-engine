#include <iostream>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\ext.hpp>

#include "GameObject.h"
#include "..\Application.h"

GameObject::GameObject(Application *app, Mesh* mesh, glm::vec3 object_color, Texture* texture) : app(app), camera(app->get_camera()), mesh(mesh), object_color(object_color), texture(texture){
	this->model_mat = glm::mat4(1.0f);
}

void GameObject::set_shader_program(LightingShader* shader_program) {
	this->shader_program = shader_program;
	this->set_initial_shader_values();
}

void GameObject::set_initial_shader_values() {
	shader_program->start();
	shader_program->set_ambient_strength(0.1f);
	shader_program->set_specular_strength(1.0f);
	shader_program->set_specular_power(256);
	shader_program->stop();
}

void GameObject::update_lights() {
	// TODO: Only working for one light right now, implement shaders for multilighting
	shader_program->start();
	shader_program->set_light_color(app->get_lights()[0]->get_light_color());
	shader_program->set_light_pos(app->get_lights()[0]->get_light_position());
	shader_program->stop();
}


void GameObject::update(float delta_time) {
	model_mat = glm::rotate(model_mat, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void GameObject::render() {
	shader_program->start();
	
	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();

	texture->bind();
	shader_program->set_texture(texture->get_unit());

	shader_program->set_view_matrix(view);
	shader_program->set_proj_matrix(perspective_proj);
	shader_program->set_model_matrix(model_mat);
	shader_program->set_object_color(object_color);
	
	mesh->draw();
	
	/* Draw Debug CubeMesh */
	if (app->is_debug()) {
		glm::mat4 cube_mat = glm::scale(model_mat, mesh->get_size());
		shader_program->set_model_matrix(cube_mat);
		cube_mesh.draw();
	}

	texture->unbind();
	shader_program->stop();
}

#pragma region PROPERTIES_SETTERS
void GameObject::set_pos(glm::vec3 pos) {
	model_mat = glm::translate(model_mat, pos);
}

void GameObject::set_scale(glm::vec3 scale) {
	model_mat = glm::scale(model_mat, scale);
}

void GameObject::set_ambient_strength(float ambient_strength) {
	shader_program->start();
	shader_program->set_ambient_strength(ambient_strength);
	shader_program->stop();
}

void GameObject::set_specular_strength(int specular_strength) {
	shader_program->start();
	shader_program->set_specular_strength(specular_strength);
	shader_program->stop();
}

void GameObject::set_specular_power(int specular_power) {
	shader_program->start();
	shader_program->set_specular_power(specular_power);
	shader_program->stop();

}

#pragma endregion

GameObject::~GameObject() {
	delete camera;
	delete shader_program;
	delete mesh;
	mesh = NULL;
	camera = NULL;
	shader_program = NULL;
}
