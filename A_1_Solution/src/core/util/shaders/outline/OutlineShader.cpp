#include "OutlineShader.h"
#include <iostream>

OutlineShader * OutlineShader::create(std::string vertex_shader, std::string fragment_shader) {
	OutlineShader * p = new OutlineShader(vertex_shader, fragment_shader);
	p->init();
	return p;
}

OutlineShader::OutlineShader(std::string vertex_shader, std::string fragment_shader) : ShaderProgram(vertex_shader, fragment_shader) {}

OutlineShader::~OutlineShader() {}

void OutlineShader::bind_attributes() {
	ShaderProgram::bind_attribute(0, "vertex_positions");
	ShaderProgram::bind_attribute(2, "vertex_normals");
}

void OutlineShader::get_all_uniform_locations() {
	location_model_mat = get_uniform_location("model_mat");
	location_view_mat = get_uniform_location("view_mat");
	location_proj_mat = get_uniform_location("proj_mat");
}

void OutlineShader::set_model_matrix(glm::mat4 matrix) {
	modify_mat4(location_model_mat, matrix);
}
void OutlineShader::set_view_matrix(glm::mat4 matrix) { modify_mat4(location_view_mat, matrix); }

void OutlineShader::set_proj_matrix(glm::mat4 matrix) { modify_mat4(location_proj_mat, matrix); }
