#pragma once
#include "En.h"

class maths {
public:

	inline static std::vector<float> vec3_to_vector(glm::vec3 vec3) {
		std::vector<float> result = { vec3.x, vec3.y, vec3.z };
		return result;
	}

	inline static glm::vec3 vector_to_vec3(std::vector<float> vector) {
		return glm::vec3(vector[0], vector[1], vector[2]);
	}
};

