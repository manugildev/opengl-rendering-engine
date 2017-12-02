#pragma once
#include "..\ShaderProgram.h"

const std::string GUI_VERTEX_FILE = "shaders/gui_vertex_shader.glsl";
const std::string GUI_FRAGMENT_FILE = "shaders/gui_fragment_shader.glsl";
class GuiShader :
	public ShaderProgram {
public:
	static GuiShader* create(std::string vertex_shader = GUI_VERTEX_FILE, std::string fragment_shader = GUI_FRAGMENT_FILE);

	GuiShader(std::string vertex_shader = GUI_VERTEX_FILE, std::string fragment_shader = GUI_FRAGMENT_FILE);
	~GuiShader();

	void bind_attributes() override;
	void get_all_uniform_locations() override;

	void set_transformation_matrix(glm::mat4 transformation_matrix);

private:
	GLuint location_transformation_matrix;
};

