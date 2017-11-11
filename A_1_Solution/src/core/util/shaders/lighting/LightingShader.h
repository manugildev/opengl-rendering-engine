#pragma once
#include "..\ShaderProgram.h"

const std::string VERTEX_FILE = "shaders/lighting_vertex_shader.glsl";
const std::string FRAGMENT_FILE = "shaders/lighting_fragment_shader.glsl";

class LightingShader : public ShaderProgram {
public:
	static LightingShader* create();

	LightingShader();
	~LightingShader();

	void bind_attributes() override;
	void get_all_uniform_locations() override;

	void set_view_matrix(glm::mat4 matrix);
	void set_model_matrix(glm::mat4 matrix);
	void set_proj_matrix(glm::mat4 matrix);
	void set_object_color(glm::vec3 object_color);
	void set_light_pos(glm::vec3 light_pos);
	void set_light_color(glm::vec3 light_color);
	void set_ambient_strength(float value);
	void set_specular_strength(float value); 
	void set_specular_power(int value);
	void set_texture(int value);

private:
	GLuint location_model_mat, location_view_mat, location_proj_mat;
	GLuint location_object_color, location_light_pos, location_light_color;
	GLuint location_ambient_strength, location_specular_strength, location_specular_power;
	GLuint location_texture_0;
};