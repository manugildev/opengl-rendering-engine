#pragma once
#include "Bone.h"
#include "vector"
#include "core\Application.h"
#include "../util/CCDSolver.h"

class Skeleton : public GameObject {
public:
	Skeleton(std::string name, Application * app, GameObject* target);
	~Skeleton();

	void update(float delta_time) override;
	void render() override;

	void add(Bone* bone);
	std::vector<Bone*> get_bones();
	void add_new_bone();
	void remove_bone();
private:
	std::vector<Bone*> bones;
	CCDSolver* solver;
	GameObject* target;
	Model* bone_model;
	Model* hand_model;
	
};

