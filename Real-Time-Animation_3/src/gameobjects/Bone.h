#pragma once
#include "core\Application.h"

class Bone : public GameObject {
public:
	Bone(std::string name, Application * app, Model* model, glm::vec3 object_color);
	~Bone();

	void update(float delta_time) override;
	void update_quaternion(glm::quat quaternion);
};

