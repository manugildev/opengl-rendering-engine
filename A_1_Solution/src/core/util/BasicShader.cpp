#include "BasicShader.h"
#include <iostream>

BasicShader * BasicShader::create() {
	BasicShader * p = new BasicShader();
	p->init();
	return p;
}

BasicShader::BasicShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}

BasicShader::~BasicShader() {}

void BasicShader::bind_attributes() {
	ShaderProgram::bind_attribute(0, "vertex_positions");
	ShaderProgram::bind_attribute(1, "vertex_normals");
}

void BasicShader::get_all_uniform_locations() {
	location_model_mat = get_uniform_location("model_mat");
	location_view_mat = get_uniform_location("view_mat");
	location_proj_mat = get_uniform_location("proj_mat");
}

void BasicShader::set_model_matrix(glm::mat4 matrix) {
	modify_mat4(location_model_mat, matrix);
}

void BasicShader::set_view_matrix(glm::mat4 matrix) { modify_mat4(location_view_mat, matrix); }

void BasicShader::set_proj_matrix(glm::mat4 matrix) { modify_mat4(location_proj_mat, matrix); }
