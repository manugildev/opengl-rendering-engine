#pragma once
#include <glm\glm.hpp>

class Spline {
public:
	Spline();
	Spline(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	~Spline();
	glm::vec3 get_point_on_bezier_curve(float t);

	glm::vec3 p0; 
	glm::vec3 p1; 
	glm::vec3 p2; 
	glm::vec3 p3;
};

