#include "CCDSolver.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "../gameobjects/Skeleton.h"
#include <algorithm>
#include "glm\glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/ext.hpp"

CCDSolver::CCDSolver(){
}


CCDSolver::~CCDSolver(){
}

glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest) {
	start = normalize(start);
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.000001f) {
		// special case when vectors in opposite directions :
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		// This implementation favors a rotation around the Up axis,
		// since it's often what you want to do.
		rotationAxis = cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return angleAxis(glm::radians(180.0f), rotationAxis);
	}

	// Implementation from Stan Melax's Game Programming Gems 1 article
	rotationAxis = cross(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);
}

void CCDSolver::update(float delta_time, Skeleton* skeleton, GameObject* target) {
	Bone* first_bone = skeleton->get_bones().front();
	Bone* last_bone = skeleton->get_bones().back();
	float distance = glm::distance(last_bone->get_pos(), target->get_pos());

	float threshold = 0.001;
	int max_iterations = 10;
	int iterations = 0;

	while (distance > threshold) {
		iterations++;
		for (unsigned i = skeleton->get_bones().size(); i-- > 0;){	
			if (skeleton->get_bones()[i] == last_bone) continue;

			glm::vec3 current_skeleton_pos = skeleton->get_bones()[i]->get_pos();
			glm::vec3 target_vector = target->get_pos() - current_skeleton_pos;
			glm::vec3 end_efector_vector = last_bone->get_pos() - current_skeleton_pos;

			glm::quat new_rotation = RotationBetweenVectors(end_efector_vector, target_vector);
			skeleton->get_bones()[i]->set_quaternion(new_rotation);
			skeleton->get_bones()[i]->update_model_mat();
		}
		
		distance = glm::distance(last_bone->get_pos(), target->get_pos());

		if (iterations > max_iterations) return;

	}	
}
