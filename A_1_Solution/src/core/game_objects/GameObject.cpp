#include <iostream>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\ext.hpp>

#include "GameObject.h"
#include "..\res\teapot.h"
#include "..\Application.h"

GameObject::GameObject(Application *app) : camera(app->get_camera()) {
	this->model_mat = glm::mat4(1.0f);
	init();
}

void GameObject::init() {

	/* Generate Object VBO */
	GLuint vp_vbo = 0;
	glGenBuffers(1, &vp_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * teapot_vertex_count * sizeof(float), teapot_vertex_points, GL_STATIC_DRAW);
	GLuint vn_vbo = 0;
	glGenBuffers(1, &vn_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * teapot_vertex_count * sizeof(float), teapot_normals, GL_STATIC_DRAW);

	/* Define VAO */
	glGenVertexArrays(1, &teapot_vao);
	glBindVertexArray(teapot_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, vn_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	this->shader_program = BasicShader::create();

	location_model_mat = glGetUniformLocation(shader_program->program_id, "model_mat");
	location_view_mat = glGetUniformLocation(shader_program->program_id, "view_mat");
	location_proj_mat = glGetUniformLocation(shader_program->program_id, "proj_mat");
}

GameObject::~GameObject() {
	delete camera;
	delete shader_program;
	camera = NULL;
	shader_program = NULL;
}

void GameObject::update() {
	model_mat = glm::rotate(model_mat, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void GameObject::render() {
	shader_program->start();
	glBindVertexArray(teapot_vao);

	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();

	shader_program->set_view_matrix(view);
	shader_program->set_proj_matrix(perspective_proj);
	shader_program->set_model_matrix(model_mat);

	glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);

	shader_program->stop();
}
