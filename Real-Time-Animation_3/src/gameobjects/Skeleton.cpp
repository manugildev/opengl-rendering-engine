#include "Skeleton.h"

Skeleton::Skeleton(std::string name, Application * app, GameObject* target) : GameObject(name, app, nullptr, glm::vec3()), target(target) {
	solver = new CCDSolver();
}


Skeleton::~Skeleton(){
}

void Skeleton::update(float delta_time){
	solver->update(delta_time, this, target);
	for (unsigned i = bones.size(); i-- > 0;) bones[i]->update(delta_time);
}

void Skeleton::render(){
	for (Bone* bone : bones) bone->render();
}

void Skeleton::add(Bone* bone){
	bones.push_back(bone);
}

std::vector<Bone*> Skeleton::get_bones(){
	return bones;
}
