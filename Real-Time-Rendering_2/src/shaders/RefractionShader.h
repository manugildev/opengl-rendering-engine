#pragma once
#include "core\Application.h"
#include "core\util\shaders\lighting\LightingShader.h" // Get the DLightLocation


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
	void set_object_color(glm::vec3 color);
	void set_directional_light(DirLight* dir_light);
	void set_ambient_brightness(float ambient_brightness);
	void set_ior(float ior);
	void set_chormatic_offset(float offset);
	void set_fresnel(bool fresnel);
	void set_refractive_power(float refractive_power);
	void set_refractive_factor(float refractive_factor);
	void set_refractive_strength(float refractive_strength);
	void set_mix_power(float mix_power);

private:

	GLuint location_model_mat;
	GLuint location_view_mat; 
	GLuint location_proj_mat; 
	GLuint location_view_pos;
	GLuint location_environment_map;
	GLuint location_texture_0;
	GLuint location_object_color;
	DLight_Location location_dir_light;
	GLuint location_ambient_brightness;
	GLuint location_ior;
	GLuint location_chromatic_offset;
	GLuint location_fresnel;
	GLuint location_refractive_power;
	GLuint location_refractive_factor;
	GLuint location_refractive_strength;
	GLuint location_mix_power;

};

