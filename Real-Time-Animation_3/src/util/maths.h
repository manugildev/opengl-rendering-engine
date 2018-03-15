#pragma once
#include "En.h"

class maths {
public:
	inline static glm::quat rotation_between_vectors(glm::vec3 start, glm::vec3 dest) {
		start = normalize(start);
		dest = normalize(dest);

		float cosTheta = dot(start, dest);
		glm::vec3 rotationAxis;

		if (cosTheta < -1 + 0.000001f) {
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

		return glm::quat(s * 0.5f, rotationAxis.x * invs, rotationAxis.y * invs, rotationAxis.z * invs
		);
	}

	inline static glm::vec3 rotate_around_point(glm::vec3 input, glm::vec3 origin, glm::quat quaternion) {
		return origin + quaternion * (input - origin);
	}

	inline static std::vector<float> vec3_to_vector(glm::vec3 vec3) {
		std::vector<float> result = { vec3.x, vec3.y, vec3.z };
		return result;
	}

	inline static glm::vec3 vector_to_vec3(std::vector<float> vector) {
		return glm::vec3(vector[0], vector[1], vector[2]);
	}
};

