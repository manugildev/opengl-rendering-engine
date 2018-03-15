#include "LampShader.h"

LampShader *LampShader::create() {
	LampShader *p = new LampShader();
	p->init();
	return p;
}

LampShader::LampShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}

LampShader::~LampShader() {}

void LampShader::bind_attributes() {
	ShaderProgram::bind_attribute(0, "vertex_positions");

}

void LampShader::get_all_uniform_locations() {
	location_model_mat = get_uniform_location("model_mat");
	location_view_mat = get_uniform_location("view_mat");
	location_proj_mat = get_uniform_location("proj_mat");
	location_object_color = get_uniform_location("object_color");
}

void LampShader::set_model_matrix(glm::mat4 matrix) {
	modify_mat4(location_model_mat, matrix);
}

void LampShader::set_view_matrix(glm::mat4 matrix) { modify_mat4(location_view_mat, matrix); }

void LampShader::set_proj_matrix(glm::mat4 matrix) { modify_mat4(location_proj_mat, matrix); }

void LampShader::set_object_color(glm::vec3 object_color) { modify_vec3(location_object_color, object_color); }
