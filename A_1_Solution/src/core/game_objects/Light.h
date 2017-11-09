#pragma once

#include <glm\glm.hpp>
#include <GLEW\glew.h>
#include <..\src\core\util\shaders\LightingShader.h>
#include <..\src\core\Application.h>
#include "GameObject.h"

class Light {
public:
	Light(Camera* camera);
	~Light();

	void update(float delta_time);
	void render();
	void init();

private:
	glm::vec3 light_pos;
	glm::vec3 light_color;
	glm::mat4 model_mat;

	GLuint light_vao;
	LightingShader* shader_program;
	Camera* camera;
};

