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
private:
	std::vector<Bone*> bones;
	CCDSolver* solver;
	GameObject* target;
	
};

