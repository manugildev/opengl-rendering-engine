#include "CCDSolver.h"
#include "../game_objects/Skeleton.h"
#include "maths.h"

CCDSolver::CCDSolver() {}


CCDSolver::~CCDSolver() {}


void CCDSolver::update(float delta_time, Skeleton* skeleton, GameObject* target) {
	Bone* first_bone = skeleton->get_bones().front();
	Bone* last_bone = skeleton->get_bones().back();
	float distance = glm::distance(last_bone->get_pos(), target->get_pos());

	float threshold = 0.001f;
	int max_iterations = 1000;
	int iterations = 0;

	while (distance > threshold) {
		iterations++;
		for (unsigned i = skeleton->get_bones().size(); i-- > 0;) {
			Bone* current_bone = skeleton->get_bones()[i];
			glm::vec3 current_end = current_bone->end_pos; // Should be always the same
			glm::vec3 current_origin = current_bone->origin_pos;

			glm::vec3 target_vector = target->get_pos() - current_origin;
			glm::vec3 end_efector_vector = last_bone->origin_pos - current_origin;

			glm::quat new_rotation = maths::rotation_between_vectors(end_efector_vector, target_vector);

			// Update the ortientation of the current_end_efector to match the rotation
			current_bone->end_pos = maths::rotate_around_point(current_end, current_origin, new_rotation);
			// Update its childrens
			current_bone->update_childrens(current_origin, new_rotation);
		}

		distance = glm::distance(last_bone->end_pos, target->get_pos());

		if (iterations > max_iterations) return;

	}
}
