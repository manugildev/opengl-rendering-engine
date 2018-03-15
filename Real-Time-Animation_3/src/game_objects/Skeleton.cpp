#include "Skeleton.h"

Skeleton::Skeleton(std::string name, Application * app, GameObject* target) : GameObject(name, app, nullptr, glm::vec3()), target(target) {
	solver = new CCDSolver();
	bone_model = new Model("models/bone.obj");
	hand_model = new Model("models/hand.obj");
}


Skeleton::~Skeleton() {
}

void Skeleton::update(double delta_time) {
	solver->update(delta_time, this, target);
	for (Bone* bone : bones) bone->update(delta_time);
}

void Skeleton::render() {
	for (Bone* bone : bones) bone->render();
}

void Skeleton::add(Bone* bone) {
	bones.push_back(bone);
	for (int i = 1; i < bones.size(); i++) bones[i]->set_parent(bones[i - 1]);
	for (int i = 0; i < bones.size() - 1; i++) bones[i]->set_children(bones[i + 1]);

	for (int i = 0; i < bones.size(); i++) bones[i]->set_model(bone_model);
	if(bones.size() > 3) bones[bones.size() -2]->set_model(hand_model);

}

std::vector<Bone*> Skeleton::get_bones() {
	return bones;
}

void Skeleton::add_new_bone() {
	if (bones.size() == 20) return;

	double c1 = (rand() / (double)(RAND_MAX + 1));
	double c2 = (rand() / (double)(RAND_MAX + 1));
	double c3 = (rand() / (double)(RAND_MAX + 1));
	
	Bone* bone = new Bone("bone" + bones.size(), app, bones[0]->get_model(), glm::vec3(c1, c2, c3), 0.6);
	bone->set_shader_program(bones[0]->get_shader_program());
	bone->set_mix_power(0.9);

	bones.insert(bones.end() - 1, bone);	

	for (int i = 1; i < bones.size(); i++) bones[i]->set_parent(bones[i - 1]);
	for (int i = 0; i < bones.size() - 1; i++) bones[i]->set_children(bones[i + 1]);
	for (int i = 0; i < bones.size(); i++) bones[i]->set_model(bone_model);
	if (bones.size() > 2) bones[bones.size() - 2]->set_model(hand_model);
}


void Skeleton::remove_bone() {
	if (bones.size() == 3) return;

	bones.erase(bones.end() -2);

	for (int i = 1; i < bones.size(); i++) bones[i]->set_parent(bones[i - 1]);
	for (int i = 0; i < bones.size() - 1; i++) bones[i]->set_children(bones[i + 1]);
	for (int i = 0; i < bones.size(); i++) bones[i]->set_model(bone_model);
	if (bones.size() > 2) bones[bones.size() - 2]->set_model(hand_model);
}
