#include "LightingShader.h"
#include <iostream>

LightingShader * LightingShader::create() {
	LightingShader * p = new LightingShader();
	p->init();
	return p;
}

LightingShader::LightingShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE) {}

LightingShader::~LightingShader() {}

void LightingShader::bind_attributes() {
	ShaderProgram::bind_attribute(0, "vertex_positions");
	ShaderProgram::bind_attribute(1, "vertex_normals");
}

void LightingShader::get_all_uniform_locations() {
	location_model_mat = get_uniform_location("model_mat");
	location_view_mat = get_uniform_location("view_mat");
	location_proj_mat = get_uniform_location("proj_mat");
	location_object_color = get_uniform_location("object_color");
	location_light_pos = get_uniform_location("light_pos");
	location_light_color = get_uniform_location("light_color");
	location_ambient_strength = get_uniform_location("ambient_strength");
	location_specular_strength = get_uniform_location("specular_strength");
	location_texture_0 = get_uniform_location("texture_0");
}

void LightingShader::set_object_color(glm::vec3 object_color) { modify_vec3(location_object_color, object_color); }

void LightingShader::set_light_pos(glm::vec3 light_pos) { modify_vec3(location_light_pos, light_pos); }

void LightingShader::set_light_color(glm::vec3 light_color) { modify_vec3(location_light_color, light_color); }

void LightingShader::set_model_matrix(glm::mat4 matrix) { modify_mat4(location_model_mat, matrix); }

void LightingShader::set_view_matrix(glm::mat4 matrix) { modify_mat4(location_view_mat, matrix); }

void LightingShader::set_proj_matrix(glm::mat4 matrix) { modify_mat4(location_proj_mat, matrix); }

void LightingShader::set_ambient_strength(float value) { modify_float(location_ambient_strength, value); }

void LightingShader::set_specular_strength(float value) { modify_float(location_specular_strength , value); }

void LightingShader::set_texture(int number) { modify_texture(location_texture_0, number); }