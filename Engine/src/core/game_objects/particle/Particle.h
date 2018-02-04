#pragma once
#include <glm\glm.hpp>

class Particle {
public:
	Particle();
	Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, float life_length, float rotation, float scale);
	~Particle();

	glm::vec3 get_position();
	glm::vec3 get_velocity();
	glm::vec3 get_acceleration();
	float get_rotation();
	float get_scale();
	bool update(float delta_time);

protected:

private:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float life_length;
	float rotation;
	float scale;

	float elapsed_time = 0;
};

