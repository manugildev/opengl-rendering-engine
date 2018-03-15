#include "ParticleSystem.h"
#include "Particle.h"
#include "core\Application.h"

ParticleSystem::ParticleSystem(Application * app, Texture* texture, float pps, float speed, float gravity_factor, float life_length, float scale) : app(app), texture(texture), pps(pps), speed(speed), gravity_factor(gravity_factor), life_length(life_length), scale(scale) {
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::generate_particles(double delta_time, glm::vec3 system_center) {
	double particles_to_create = pps * delta_time;
	int count = (int)glm::floor(particles_to_create);
	double partial_particle = std::fmod(particles_to_create, 1);
	for (int i = 0; i < count; i++) {
		emit_particle(system_center);
	}
	double r = ((double) rand() / (RAND_MAX));
	if (r < partial_particle) emit_particle(system_center);
}

void ParticleSystem::emit_particle(glm::vec3 center) {
	double r = ((double)rand() / (RAND_MAX));
	double dir_x = r * 1.0f - 0.5f;
	r = ((double)rand() / (RAND_MAX));
	double dir_z = r * 1.0f - 0.5f;

	glm::vec3 velocity = glm::vec3(dir_x, 1, dir_z);
	velocity = glm::normalize(velocity);
	velocity = velocity * (generate_value(speed, speed_error));
	float s = generate_value(scale, scale_error);
	float l = generate_value(life_length, life_error);
	//std::cout << generate_rotation() << std::endl;
	Particle* p = new Particle(texture, center, velocity, glm::vec3(0, -6.0f, 0), 1, l, generate_rotation(), s);
	p->set_object_color(object_color);
	app->particle_master->add_particle(p);
}

void ParticleSystem::set_speed_error(float value) {
	this->speed_error = value;
}

void ParticleSystem::set_life_error(float value) {
	this->life_error = value;
}

void ParticleSystem::set_scale_error(float value) {
	this->scale_error = value;
}

void ParticleSystem::set_random_rotation(bool value) {
	this->random_rotation = value;
}

void ParticleSystem::set_direction(glm::vec3 direction, float deviation) {
	this->direction = direction;
	this->direction_deviation = deviation * 3.141692f;
}

glm::vec3 ParticleSystem::generate_random_unit_vector(glm::vec3 direction, float deviation) {
	float cos_angle = glm::cos(deviation);
	float r = rand() / ((float)RAND_MAX);

	float theta = (float) r * 2.0f * 3.141692f;
	r = rand() / ((float) RAND_MAX);
	float z = cos_angle + (r * (1 - cos_angle));
	float root_one_minus = (float)glm::sqrt(1 - z * z);
	float x = (float)root_one_minus * glm::cos(theta);
	float y = (float)root_one_minus * glm::sin(theta);

	glm::vec3 d = glm::vec3(x, y, z);

	if (direction.x != 0 || direction.y != 0 || (direction.z != 1 && direction.z != -1)) {
		glm::vec3 rotate_axis = glm::cross(direction, glm::vec3(0, 0, 1));
		rotate_axis = glm::normalize(rotate_axis);
		float rotate_angle = (float)glm::acos(glm::dot(direction, glm::vec3(0,0,1)));
		glm::mat4 rotation_matrix = glm::mat4(1.0f);
		rotation_matrix = glm::rotate(rotation_matrix, rotate_angle, rotate_axis);
		rotation_matrix = glm::translate(rotation_matrix, d);
	}
	else if(direction.z == -1) {
		d.z *= -1;
	}

	return glm::vec3(direction);
}

float ParticleSystem::generate_value(float value1, float error) {
	float offset = ((rand() / (float)RAND_MAX) - 0.5f) * 2.0f * error;
	return value1 + offset;
}

float ParticleSystem::generate_rotation() {
	if (random_rotation) return ((rand() / (float)RAND_MAX) * 360.0f);
	else return 0;
}

void ParticleSystem::set_object_color(glm::vec3 object_color){
	this->object_color = object_color;
}
