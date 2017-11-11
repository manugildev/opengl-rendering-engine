#pragma once
#include "..\ShaderProgram.h"
#include "..\src\core\game_objects\lights\DirLight.h"
#include "..\src\core\game_objects\lights\PointLight.h"
#include <vector>

const std::string LAMP_VERTEX_FILE = "shaders/lighting_vertex_shader.glsl";
const std::string LAMP_FRAGMENT_FILE = "shaders/lighting_fragment_shader.glsl";
const int MAX_LIGHTS = 3;

/* Structures for storing all the locations of the same light*/
struct DLight {
	GLuint direction;
	GLuint light_color;
};

struct PLight {
	GLuint position;
	GLuint light_color;
	GLuint constant;
	GLuint linear;
	GLuint quadratic;
};

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

	void set_directional_light(DirLight* dir_light);
	void set_point_lights(std::vector<PointLight*> point_lights);
	void set_point_light(PointLight* dir_light, int index);

private:
	GLuint location_model_mat, location_view_mat, location_proj_mat;
	GLuint location_object_color, location_light_pos, location_light_color;
	GLuint location_ambient_strength, location_specular_strength, location_specular_power;
	GLuint location_texture_0;

	DLight location_dir_light;
	PLight location_point_light[MAX_LIGHTS];

};