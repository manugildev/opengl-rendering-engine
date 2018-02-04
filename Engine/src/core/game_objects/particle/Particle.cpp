#include "Particle.h"
#include <iostream>
Particle::Particle(){
}


Particle::Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, float life_length, float rotation, float scale) : position(position), velocity(velocity), acceleration(acceleration), life_length(life_length), rotation(rotation), scale(scale){
}

Particle::~Particle(){
}


bool Particle::update(float delta_time) {
	this->velocity += this->acceleration * delta_time;
	this->position += this->velocity * delta_time;
	this->elapsed_time += delta_time;
	return elapsed_time < life_length;
}

glm::vec3 Particle::get_position(){
	return this->position;
}

glm::vec3 Particle::get_velocity(){
	return this->velocity;
}

glm::vec3 Particle::get_acceleration() {
	return this->acceleration;
}

float Particle::get_rotation(){
	return this->rotation;
}

float Particle::get_scale(){
	return this->scale;
}
