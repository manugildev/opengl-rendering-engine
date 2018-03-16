#include "GoochShader.h"

const std::string GoochShader::VERTEX_FILE = "shaders/npr/gooch_vertex_shader.glsl";
const std::string GoochShader::FRAGMENT_FILE = "shaders/npr/gooch_fragment_shader.glsl";

GoochShader::GoochShader(std::string vertex_shader, std::string fragment_shader) : ShaderProgram(vertex_shader, fragment_shader) {

}

GoochShader * GoochShader::create(std::string vertex_shader, std::string fragment_shader){
	GoochShader * p = new GoochShader(vertex_shader, fragment_shader);
	p->init();
	return p;
}

GoochShader::~GoochShader(){
}

void GoochShader::bind_attributes() {
	ShaderProgram::bind_attribute(0, "vertex_positions");
	ShaderProgram::bind_attribute(1, "vertex_tex_coords");
	ShaderProgram::bind_attribute(2, "vertex_normals");

}

void GoochShader::get_all_uniform_locations() {
	location_model_mat = get_uniform_location("model_mat");
	location_view_mat = get_uniform_location("view_mat");
	location_proj_mat = get_uniform_location("proj_mat");
	location_texture_0 = get_uniform_location("texture_0");
	location_object_color = get_uniform_location("object_color");
	location_view_position = get_uniform_location("view_pos");
	/* Locations for Lights */
	// Directional Lights
	location_dir_light.direction = get_uniform_location("dir_light.direction");
	location_dir_light.light_color = get_uniform_location("dir_light.light_color");
}
