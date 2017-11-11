#include <iostream>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\detail\func_vector_relational.hpp>
#include <glm\ext.hpp>

#include "GameObject.h"
#include "..\Application.h"
#include "..\src\core\util\shaders\lighting\LightingShader.h"

GameObject::GameObject(Application *app, Mesh* mesh, glm::vec3 object_color, Texture* texture) : app(app), camera(app->get_camera()), mesh(mesh), object_color(object_color), texture(texture){
	this->model_mat = glm::mat4(1.0f);
	
}

void GameObject::set_shader_program(LightingShader* shader_program) {
	this->shader_program = shader_program;
	this->set_initial_shader_values();
}

void GameObject::set_initial_shader_values() {
	shader_program->start();
	shader_program->set_ambient_strength(0.05f);
	shader_program->set_specular_strength(0.8f);
	shader_program->set_specular_power(8);
	shader_program->stop();
}

void GameObject::update_lights() {
	// TODO: Only working for one light right now, implement shaders for multi lighting
	shader_program->start();
	shader_program->set_directional_light(app->get_dir_light());
	shader_program->set_point_lights(app->get_point_lights());
	shader_program->stop();
}


void GameObject::update(float delta_time) {
	//model_mat = glm::rotate(model_mat, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 new_speed = this->speed + (this->acceleration * delta_time);
	if (glm::all(glm::lessThan(new_speed, this->max_speed))) {
		this->speed = new_speed;
	}
	this->position += (this->speed * delta_time);
	this->set_pos(this->position);
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
	this->position = pos;
	model_mat[3][0] = pos.x;
	model_mat[3][1] = pos.y;
	model_mat[3][2] = pos.z;
}

void GameObject::set_acceleration(glm::vec3 acc) {
	this->acceleration = acc;
}

void GameObject::set_speed(glm::vec3 speed) {
	this->speed = speed;
}

void GameObject::set_max_speed(glm::vec3 max_speed) {
	this->max_speed = max_speed;
}


void GameObject::set_scale(glm::vec3 scale) {
	model_mat = glm::scale(model_mat, scale);
}

void GameObject::set_ambient_strength(float ambient_strength) {
	shader_program->start();
	shader_program->set_ambient_strength(ambient_strength);
	shader_program->stop();
}

void GameObject::set_specular_strength(float specular_strength) {
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
