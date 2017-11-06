#pragma once
#include <GLEW\glew.h>
#include <glm\glm.hpp>
#include "..\camera\Camera.h"
#include "..\src\core\util\BasicShader.h"

class Application;

class GameObject {
public:
	GameObject(Application *app);
	~GameObject();

	void update(float delta_time);
	void render();
	void init();

private:
	glm::mat4 model_mat;
	GLuint teapot_vao = 0;
	GLuint location_positions, location_normals;
	GLuint shader_program_id;
	int location_proj_mat, location_view_mat, location_model_mat;
	Camera* camera;
	BasicShader* shader_program;
};

