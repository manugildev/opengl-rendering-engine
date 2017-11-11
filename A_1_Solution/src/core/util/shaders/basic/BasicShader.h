#pragma once
#include "..\ShaderProgram.h"

const std::string BASIC_VERTEX_FILE = "shaders/basic_vertex_shader.glsl";
const std::string BASIC_FRAGMENT_FILE = "shaders/basic_fragment_shader.glsl";

class BasicShader : public ShaderProgram {
public:

	static BasicShader* create();

	BasicShader();
	~BasicShader();

	void bind_attributes() override;
	void get_all_uniform_locations() override;

	void set_model_matrix(glm::mat4 matrix);
	void set_view_matrix(glm::mat4 matrix);
	void set_proj_matrix(glm::mat4 matrix);

private:
	GLuint location_model_mat, location_view_mat, location_proj_mat;

};

