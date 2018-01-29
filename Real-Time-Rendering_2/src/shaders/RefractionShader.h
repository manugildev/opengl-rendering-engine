#pragma once
#include "core\Application.h"


const std::string REFRACTION_VERTEX_FILE = "shaders/refraction/refraction_vertex_shader.glsl";
const std::string REFRACTION_FRAGMENT_FILE = "shaders/refraction/refraction_fragment_shader.glsl";

class RefractionShader : public ShaderProgram {
public:

	static RefractionShader* create(std::string vertex_shader = REFRACTION_VERTEX_FILE, std::string fragment_shader = REFRACTION_FRAGMENT_FILE);

	RefractionShader(std::string vertex_shader = REFRACTION_VERTEX_FILE, std::string fragment_shader = REFRACTION_FRAGMENT_FILE);
	~RefractionShader();

	void bind_attributes() override;
	void get_all_uniform_locations() override;

	void set_model_matrix(glm::mat4 matrix);
	void set_view_matrix(glm::mat4 matrix);
	void set_proj_matrix(glm::mat4 matrix);
	void set_view_pos(glm::vec3 view_pos);
	void set_texture_0(int number);
	void set_environment_map(int number);

private:
	GLuint location_model_mat, location_view_mat, location_proj_mat, location_view_pos;
	GLuint location_environment_map;
	GLuint location_texture_0;
};

