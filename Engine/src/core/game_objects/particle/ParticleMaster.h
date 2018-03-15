#pragma once
#include "ParticleRenderer.h"
#include "ParticleSystem.h"

class ParticleMaster{
public:
	ParticleMaster(glm::mat4 proj_mat);
	~ParticleMaster();

	void update(double delta_time);
	void render(Camera* camera);
	void add_particle(Particle* p);
	void apply_force(glm::vec3 force);

private:
	std::vector<Particle* > particles;
	ParticleRenderer* renderer;
};

