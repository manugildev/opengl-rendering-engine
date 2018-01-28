#include "GuiShader.h"

const std::string BASIC_VERTEX_FILE = "shaders/gui_vertex_shader.glsl";
const std::string BASIC_FRAGMENT_FILE = "shaders/gui_fragment_shader.glsl";

GuiShader * GuiShader::create(std::string vertex_shader, std::string fragment_shader) {
	GuiShader * p = new GuiShader(vertex_shader, fragment_shader);
	p->init();
	return p;
}

GuiShader::GuiShader(std::string vertex_shader, std::string fragment_shader) : ShaderProgram(vertex_shader, fragment_shader) {}

GuiShader::~GuiShader() {}

void GuiShader::bind_attributes() {
	ShaderProgram::bind_attribute(0, "vertex_positions");
}

void GuiShader::get_all_uniform_locations() {
	location_transformation_matrix = get_uniform_location("transformation_matrix");
	location_gui_texture = get_uniform_location("gui_texture");
}

void GuiShader::set_transformation_matrix(glm::mat4 transformation_matrix) {
	modify_mat4(location_transformation_matrix, transformation_matrix);
}


void GuiShader::set_texture(int number) { modify_texture(location_gui_texture, number); }