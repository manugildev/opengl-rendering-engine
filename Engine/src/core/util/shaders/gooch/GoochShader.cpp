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
	/* Locations for Material*/
	location_material.ambient_color = get_uniform_location("material.ambient_color");
	location_material.diffuse_color = get_uniform_location("material.diffuse_color");
	location_material.specular_color = get_uniform_location("material.specular_color");
	location_material.shininess = get_uniform_location("material.shininess");
	location_material.shininess_strength = get_uniform_location("material.shininess_strength");

	location_use_object_color = get_uniform_location("use_object_color");
	location_use_phong = get_uniform_location("use_phong");

	for (int i = 0; i < 128; i++) {
		std::string index = std::to_string(i);
		PLight_Location p_light_location;
		p_light_location.position = get_uniform_location("point_lights[" + index + "].position");
		p_light_location.light_color = get_uniform_location("point_lights[" + index + "].light_color");
		p_light_location.constant = get_uniform_location("point_lights[" + index + "].constant");
		p_light_location.linear = get_uniform_location("point_lights[" + index + "].linear");
		p_light_location.quadratic = get_uniform_location("point_lights[" + index + "].quadratic");
		locations_point_lights.push_back(p_light_location);
	}

}

void GoochShader::set_material(Material material) {
	this->modify_vec3(location_material.ambient_color, material.ambient_color);
	this->modify_vec3(location_material.diffuse_color, material.diffuse_color);
	this->modify_vec3(location_material.specular_color, material.specular_color);
	this->modify_float(location_material.shininess, material.shininess);
}

void GoochShader::set_point_lights(std::vector<PointLight*> point_lights) {
	// Point Lights
	for (unsigned int i = 0; i < point_lights.size(); i++) {
		this->set_point_light(point_lights[i], i);
	}
	this->set_point_lights_size(point_lights.size());
}

void GoochShader::set_point_light(PointLight* point_light, int index) {
	modify_vec3(locations_point_lights[index].position, point_light->get_light_position());
	modify_vec3(locations_point_lights[index].light_color, point_light->get_light_color());
	modify_float(locations_point_lights[index].constant, point_light->get_constant());
	modify_float(locations_point_lights[index].linear, point_light->get_linear());
	modify_float(locations_point_lights[index].quadratic, point_light->get_quadratic());
}

void GoochShader::set_point_lights_size(int size) {
	modify_int(location_point_lights_size, size);
}
