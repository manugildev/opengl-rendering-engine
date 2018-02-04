#pragma once
#include "ParticlerRenderer.h"

class ParticleMaster{
public:
	ParticleMaster(glm::mat4 proj_mat);
	~ParticleMaster();

	void update(float delta_time);
	void render(Camera* camera);
	void add_particle(Particle* p);

private:
	std::vector<Particle* > particles;
	ParticlerRenderer* renderer;
};

