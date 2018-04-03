#pragma once
#include "Engine.h"

class GoochShader : public ShaderProgram {
public:

	static GoochShader* create(std::string vertex_shader = VERTEX_FILE, std::string fragment_shader = FRAGMENT_FILE);

	GoochShader(std::string vertex_shader = VERTEX_FILE, std::string fragment_shader = FRAGMENT_FILE);
	~GoochShader();

	void bind_attributes() override;
	void get_all_uniform_locations() override;
	void set_material(Material material);

	static const std::string VERTEX_FILE;
	static const std::string FRAGMENT_FILE;

	static const std::string PROJECTION_MATRIX;
	static const std::string MODEL_MATRIX;
	static const std::string VIEW_MATRIX;

	GLuint location_model_mat;
	GLuint location_view_mat;
	GLuint location_proj_mat;
	GLuint location_texture_0;
	GLuint location_object_color;
	GLuint location_view_position;
	GLuint location_use_object_color;
	GLuint location_use_phong;
	DLight_Location location_dir_light;
	Material_Location location_material;
};

