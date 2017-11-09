#pragma once
#include <GLEW\glew.h>
#include <glm\glm.hpp>
#include "..\camera\Camera.h"
#include "..\src\core\util\shaders\LightingShader.h"

class Application;

const glm::vec3 DEFAULT_OBJ_COLOR(1.0f);

class GameObject {
public:
	GameObject(Application *app, glm::vec3 object_color=DEFAULT_OBJ_COLOR);
	~GameObject();

	void update(float delta_time);
	void render();
	void init();

private:
	glm::mat4 model_mat;
	glm::vec3 object_color;
	GLuint teapot_vao = 0;
	GLuint location_positions, location_normals;

	Camera* camera;
	LightingShader* shader_program;
};

