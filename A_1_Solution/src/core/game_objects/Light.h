#pragma once

#include <glm\glm.hpp>
#include <GLEW\glew.h>
#include "..\util\shaders\lighting\LightingShader.h"
#include "..\Application.h"
#include "GameObject.h"

class Light : public GameObject {
public:
	Light(Application* app);
	~Light();

	void update(float delta_time);
	void render();
	void init();

private:
	glm::vec3 light_pos;
	glm::vec3 light_color;
	glm::mat4 model_mat;

	GLuint light_vao;
	Camera* camera;
};

