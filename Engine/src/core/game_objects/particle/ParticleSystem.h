#pragma once
#include <glm\glm.hpp>
#include "..\..\util\texture\Texture.h"
class Application;
class ParticleSystem {
public:
	ParticleSystem(Application * app, Texture* texture, float pps, float speed, float gravity_factor, float life_length, float scale);
	~ParticleSystem();

	void generate_particles(float delta_time, glm::vec3 system_center);
	void emit_particle(glm::vec3 center);

	void set_speed_error(float value);
	void set_life_error(float value);
	void set_scale_error(float value);
	void set_random_rotation(bool value);
	void set_direction(glm::vec3 direction, float deviation);
	glm::vec3 generate_random_unit_vector(glm::vec3 direction, float deviation);
	float generate_value(float value1, float error);
	float generate_rotation();
	void set_object_color(glm::vec3 object_color);

private:
	float pps;
	float speed;
	float gravity_factor;
	float life_length;
	Application * app;
	Texture* texture;
	float scale = 0.05f;
	glm::vec3 object_color = glm::vec3(1.0f);

	float speed_error, life_error, scale_error;
	bool random_rotation = true;
	glm::vec3 direction = glm::vec3(0,0,0);
	float direction_deviation = 0;
};

