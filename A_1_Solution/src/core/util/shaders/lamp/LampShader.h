#pragma once
#include "..\ShaderProgram.h"


class LampShader : public ShaderProgram {
public:
	const std::string VERTEX_FILE = "shaders/lamp_vertex_shader.glsl";
	const std::string FRAGMENT_FILE = "shaders/lamp_fragment_shader.glsl";

	static LampShader* create();

	LampShader();
	~LampShader();

	void bind_attributes() override;
	void get_all_uniform_locations() override;

	void set_model_matrix(glm::mat4 matrix);
	void set_view_matrix(glm::mat4 matrix);
	void set_proj_matrix(glm::mat4 matrix);

private:
	GLuint location_model_mat, location_view_mat, location_proj_mat;

};

