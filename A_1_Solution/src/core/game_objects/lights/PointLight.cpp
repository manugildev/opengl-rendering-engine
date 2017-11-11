#include "PointLight.h"

PointLight::PointLight(Application * app, glm::vec3 position, glm::vec3 light_color, float constant, float linear, float quadratic) : Light(app, position, light_color), constant(constant), linear(linear), quadratic(quadratic) {}

float PointLight::get_constant() {
	return this->constant;
}

float PointLight::get_linear() {
	return this->linear;
}

float PointLight::get_quadratic() {
	return this->quadratic;
}

PointLight::~PointLight() {}