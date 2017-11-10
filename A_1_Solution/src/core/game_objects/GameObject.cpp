#include <iostream>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\ext.hpp>

#include "GameObject.h"
#include "..\res\teapot.h"
#include "..\Application.h"

GameObject::GameObject(Application *app, glm::vec3 object_color, Texture* texture) : camera(app->get_camera()), object_color(object_color), texture(texture){
	this->model_mat = glm::mat4(1.0f);
	init();
}

void GameObject::init() {
	/* Generate Object VBO */
	GLuint vp_vbo = 0;
	glGenBuffers(1, &vp_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * teapot_vertex_count * sizeof(float), teapot_vertex_points, GL_STATIC_DRAW);

	GLuint vt_vbo = 0;
	glGenBuffers(1, &vt_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vt_vbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * teapot_vertex_count * sizeof(float), teapot_tex_coords, GL_STATIC_DRAW);

	GLuint vn_vbo = 0;
	glGenBuffers(1, &vn_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * teapot_vertex_count * sizeof(float), teapot_normals, GL_STATIC_DRAW);
	
	/* Define VAO */
	glGenVertexArrays(1, &teapot_vao);
	glBindVertexArray(teapot_vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vt_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

}

void GameObject::set_shader_program(LightingShader* shader_program) {
	this->shader_program = shader_program;
	this->set_initial_shader_values();
}

void GameObject::set_initial_shader_values() {
	shader_program->start();
	shader_program->set_light_color(glm::vec3(1.0f, 1.0f, 1.0f));
	shader_program->set_light_pos(glm::vec3(0.0f, 200.0f, 200.0f));
	shader_program->set_ambient_strength(0.1f);
	shader_program->set_specular_strength(1.0f);
	shader_program->stop();
}

void GameObject::update(float delta_time) {
	model_mat = glm::rotate(model_mat, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void GameObject::render() {
	shader_program->start();
	glBindVertexArray(teapot_vao);

	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();

	texture->bind();
	shader_program->set_texture(texture->get_unit());

	shader_program->set_view_matrix(view);
	shader_program->set_proj_matrix(perspective_proj);
	shader_program->set_model_matrix(model_mat);
	shader_program->set_object_color(object_color);

	glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);

	glBindVertexArray(0);
	//texture->unbind();
	//shader_program->stop();
}

void GameObject::set_pos(glm::vec3 pos) {
	model_mat = glm::translate(model_mat, pos);
}

void GameObject::set_scale(glm::vec3 scale) {
	model_mat = glm::scale(model_mat, scale);
}

GameObject::~GameObject() {
	delete camera;
	delete shader_program;
	camera = NULL;
	shader_program = NULL;
}
