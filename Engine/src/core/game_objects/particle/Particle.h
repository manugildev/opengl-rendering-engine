#pragma once
#include <glm\glm.hpp>
#include "..\..\util\texture\Texture.h"

class Particle {
public:
	Particle();
	Particle(Texture* texture, glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, float mass, float life_length, float rotation, float scale);
	~Particle();

	glm::vec3 get_position();
	glm::vec3 get_velocity();
	glm::vec3 get_acceleration();
	float get_rotation();
	float get_scale();
	bool update(double delta_time);
	void apply_force(glm::vec3 force);
	void collision_handling();
	Texture* get_texture();
	void set_object_color(glm::vec3 object_color);
	glm::vec3 get_object_color();

protected:

private:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 force = glm::vec3(0.0f);
	glm::vec3 old_force = glm::vec3(0.0f);
	glm::vec3 penalty_force;
	float threshold = 0.06f;
	float mass;
	double life_length;
	float rotation;
	float scale;
	Texture* texture;
	glm::vec3 object_color = glm::vec3(1);
	double elapsed_time = 0;
};

