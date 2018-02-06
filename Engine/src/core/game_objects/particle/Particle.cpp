#include "Particle.h"
#include <glm\ext.hpp>
#include <iostream>

Particle::Particle() {
}

Particle::Particle(Texture* texture, glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, float mass, float life_length, float rotation, float scale) : texture(texture), position(position), velocity(velocity), acceleration(acceleration), mass(mass), life_length(life_length), rotation(rotation), scale(scale) {
}

Particle::~Particle() {
}


bool Particle::update(float delta_time) {
	this->scale -= 0.05*(1 - (elapsed_time / life_length));
	if (get_position()[1] < -10) return false;
	if (glm::length(velocity) < 0.1) return false;

	this->force = (force + acceleration) / mass;
	this->penalty_force = (force + acceleration) * mass;

	if (false) {
		this->velocity += this->force * delta_time;
		this->position += this->velocity * delta_time;
	} else {
		this->position += (this->velocity + (0.5f * old_force)) * delta_time;
		this->velocity += (0.5f * (this->force + old_force)) * delta_time;
	}

	this->old_force = this->force;
	this->elapsed_time += delta_time;
	this->penalty_force = force;
	this->force = glm::vec3(0);
	float life_factor = elapsed_time / life_length;
	this->scale += 0.05*(1 - (elapsed_time / life_length));
	if (scale < 0) scale = 0;
	collision_handling();
	return elapsed_time < life_length;
}

glm::vec3 Particle::get_position() {
	return this->position;
}

glm::vec3 Particle::get_velocity() {
	return this->velocity;
}

glm::vec3 Particle::get_acceleration() {
	return this->acceleration;
}

float Particle::get_rotation() {
	return this->rotation;
}

float Particle::get_scale() {
	return this->scale;
}

void Particle::apply_force(glm::vec3 force) {
	this->force += force;
}

void Particle::collision_handling() {
	float distance_from_plane = glm::dot((get_position() - glm::vec3(0, 0, 0)), glm::vec3(0, 1, 0));
	float normal_speed = glm::dot(get_velocity(), glm::vec3(0, 1, 0));

	if (distance_from_plane - get_scale() < threshold && normal_speed < threshold) {
		glm::vec3 new_velocity = normal_speed * glm::vec3(0, 1, 0);
		velocity = get_velocity() - new_velocity - 0.2 * new_velocity;
		float correction_factor = scale /*Scale not working*/ + threshold - distance_from_plane;
		glm::vec3 positional_correction = correction_factor * glm::vec3(0, 1, 0);
		position += positional_correction;
		this->force -= 0.6 * velocity;
		this->rotation = 0;
	}
}


Texture * Particle::get_texture() {
	return texture;
}

void Particle::set_object_color(glm::vec3 object_color) {
	this->object_color = object_color;
}

glm::vec3 Particle::get_object_color() {
	return this->object_color;
}
