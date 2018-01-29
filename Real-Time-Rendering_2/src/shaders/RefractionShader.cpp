#include "RefractionShader.h"

RefractionShader * RefractionShader::create(std::string vertex_shader, std::string fragment_shader) {
	RefractionShader * p = new RefractionShader(vertex_shader, fragment_shader);
	p->init();
	return p;
}

RefractionShader::RefractionShader(std::string vertex_shader, std::string fragment_shader) : ShaderProgram(vertex_shader, fragment_shader) {}

RefractionShader::~RefractionShader() {}

void RefractionShader::bind_attributes() {
	ShaderProgram::bind_attribute(0, "vertex_positions");
	ShaderProgram::bind_attribute(1, "vertex_tex_coords");
	ShaderProgram::bind_attribute(2, "vertex_normals");
}

void RefractionShader::get_all_uniform_locations() {
	location_model_mat = get_uniform_location("model_mat");
	location_view_mat = get_uniform_location("view_mat");
	location_proj_mat = get_uniform_location("proj_mat");
	location_view_pos = get_uniform_location("view_pos");
	location_texture_0 = get_uniform_location("texture_0");
	location_environment_map = get_uniform_location("environment_map");
	location_object_color = get_uniform_location("object_color");

	/* Locations for Lights */
	// Directional Lights
	location_dir_light.direction = get_uniform_location("dir_light.direction");
	location_dir_light.light_color = get_uniform_location("dir_light.light_color");
}

void RefractionShader::set_model_matrix(glm::mat4 matrix) {
	modify_mat4(location_model_mat, matrix);
}
void RefractionShader::set_view_pos(glm::vec3 view_pos) { modify_vec3(location_view_pos, view_pos); }

void RefractionShader::set_view_matrix(glm::mat4 matrix) { modify_mat4(location_view_mat, matrix); }

void RefractionShader::set_proj_matrix(glm::mat4 matrix) { modify_mat4(location_proj_mat, matrix); }

void RefractionShader::set_texture_0(int number) { modify_texture(location_texture_0, number); }

void RefractionShader::set_environment_map(int number) { modify_texture(location_environment_map, number); }

void RefractionShader::set_object_color(glm::vec3 color){ modify_vec3(location_object_color, color);}

void RefractionShader::set_directional_light(DirLight* dir_light) {
	modify_vec3(location_dir_light.direction, dir_light->get_direction());
	modify_vec3(location_dir_light.light_color, dir_light->get_light_color());
}