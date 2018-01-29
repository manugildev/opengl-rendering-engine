#pragma once
#include "..\ShaderProgram.h"
#include "..\src\core\game_objects\lights\DirLight.h"
#include "..\src\core\game_objects\lights\PointLight.h"
#include <vector>

const std::string LAMP_VERTEX_FILE = "shaders/lighting_vertex_shader.glsl";
const std::string LAMP_FRAGMENT_FILE = "shaders/lighting_fragment_shader.glsl";

/* Structures for storing all the locations of the same light*/
struct DLight_Location {
	GLuint direction;
	GLuint light_color;
};

struct PLight_Location {
	GLuint position;
	GLuint light_color;
	GLuint constant;
	GLuint linear;
	GLuint quadratic;
};

struct Material_Location {
	GLuint ambient_color;
	GLuint diffuse_color;
	GLuint specular_color;
	GLuint shininess;
	GLuint shininess_strength;
};


// TODO: Material only shader??

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
	void set_view_pos(glm::vec3 view_pos);
	void set_object_color(glm::vec3 object_color);
	void set_light_pos(glm::vec3 light_pos);
	void set_light_color(glm::vec3 light_color);
	void set_ambient_strength(float value);
	void set_specular_strength(float value);
	void set_specular_power(int value);
	void set_texture(int value);
	void set_mix_power(float value);
	void set_cook_r(float value);
	void set_cook_k(float value);
	void set_cook_f(float value);
	void set_toon_shading(bool value);
	void set_cook_shading(bool value);

	void set_directional_light(DirLight* dir_light);
	void set_point_lights(std::vector<PointLight*> point_lights);
	void set_point_light(PointLight* dir_light, int index);
	void set_point_lights_size(int size);
	void set_material(Material material);

private:
	GLuint location_model_mat, location_view_mat, location_proj_mat, location_view_pos;
	GLuint location_object_color, location_light_pos, location_light_color;
	GLuint location_ambient_strength, location_specular_strength, location_specular_power;
	GLuint location_texture_0, location_mix_power, location_toon_shading, location_cook_shading;
	GLuint location_cook_r, location_cook_f, location_cook_k;
	GLuint location_point_lights_size;

	DLight_Location location_dir_light;
	Material_Location location_material;
	std::vector<PLight_Location> locations_point_lights;

};