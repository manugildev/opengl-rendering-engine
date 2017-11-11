#pragma once
#include "Light.h"

const float DEFAULT_P_LIGHT_CONSTANT(1.0f);
const float DEFAULT_P_LIGHT_LINEAR(0.09f);
const float DEFAULT_P_LIGHT_QUADRATIC(0.032f);

class PointLight :	public Light {
public:
	PointLight(Application* app, glm::vec3 position = DEFAULT_LIGHT_POS, glm::vec3 light_color = DEFAULT_LIGHT_COLOR, 
			   float constant = DEFAULT_P_LIGHT_CONSTANT, float linear= DEFAULT_P_LIGHT_LINEAR, float quadratic = DEFAULT_P_LIGHT_QUADRATIC);
	~PointLight();

	float get_constant();
	float get_linear();
	float get_quadratic();

private:
	float constant, linear, quadratic;
};

