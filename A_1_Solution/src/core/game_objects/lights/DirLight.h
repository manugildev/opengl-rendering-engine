#pragma once
#include "Light.h"

const glm::vec3 DEFAULT_D_LIGHT_DIRECTION(0.0f);

class DirLight : public Light {
public:
	DirLight(Application* app, glm::vec3 direction = DEFAULT_D_LIGHT_DIRECTION, glm::vec3 light_color = DEFAULT_LIGHT_COLOR);
	~DirLight();

	glm::vec3 get_direction();

private:
	glm::vec3 direction;
};

