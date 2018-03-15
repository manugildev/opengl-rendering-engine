#include "ParticleMaster.h"

ParticleMaster::ParticleMaster(glm::mat4 proj_mat) {
	renderer = new ParticleRenderer(proj_mat);
}


ParticleMaster::~ParticleMaster(){
}

void ParticleMaster::update(double delta_time){
	std::vector<Particle *>::iterator it;
	for (auto it = particles.begin(); it != particles.end();)	{
		Particle* p = *it;
		if (!p->update(delta_time)) { it = particles.erase(it); delete p; }
		else ++it;
	}
}

void ParticleMaster::render(Camera * camera){
	renderer->render(particles, camera);
}

void ParticleMaster::add_particle(Particle * p){
	particles.push_back(p);
}

void ParticleMaster::apply_force(glm::vec3 force){
	for (Particle* p : particles) {
		p->apply_force(force);		
	}
}
