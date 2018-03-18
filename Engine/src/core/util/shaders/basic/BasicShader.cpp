#include "BasicShader.h"

BasicShader * BasicShader::create(std::string vertex_shader, std::string fragment_shader) {
	BasicShader * p = new BasicShader(vertex_shader, fragment_shader);
	p->init();
	return p;
}

BasicShader::BasicShader(std::string vertex_shader, std::string fragment_shader) : ShaderProgram(vertex_shader, fragment_shader) {}

BasicShader::~BasicShader() {}

void BasicShader::bind_attributes() {
	ShaderProgram::bind_attribute(0, "vertex_position");
	ShaderProgram::bind_attribute(1, "vertex_tex_coord");
	ShaderProgram::bind_attribute(2, "vertex_normal");
	ShaderProgram::bind_attribute(3, "vertex_tangent");
	ShaderProgram::bind_attribute(4, "vertex_bitangent");
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
