#include "ParticleMaster.h"
#include <iostream>

ParticleMaster::ParticleMaster(glm::mat4 proj_mat) {
	renderer = new ParticlerRenderer(proj_mat);
}


ParticleMaster::~ParticleMaster(){
}

void ParticleMaster::update(float delta_time){
	std::vector<Particle *>::iterator it;
	for (auto it = particles.begin(); it != particles.end();)	{
		Particle* p = *it;
		if (!p->update(delta_time)) it = particles.erase(it);
		else ++it;
	}

}

void ParticleMaster::render(Camera * camera){
	renderer->render(particles, camera);
}

void ParticleMaster::add_particle(Particle * p){
	particles.push_back(p);
}
