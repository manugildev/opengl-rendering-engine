#include "Spline.h"

Spline::Spline(){
}

Spline::Spline(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) : p0(p0), p1(p1), p2(p2), p3(p3) {
}


Spline::~Spline() {
}

glm::vec3 Spline::get_point_on_bezier_curve(float t) {

	glm::vec3 a = glm::mix(p0, p1, t);
	glm::vec3 b = glm::mix(p1, p2, t);
	glm::vec3 c = glm::mix(p2, p3, t);
	glm::vec3 d = glm::mix(a, b, t);
	glm::vec3 e = glm::mix(b, c, t);
	glm::vec3 pointOnCurve = glm::mix(d, e, t);

	return pointOnCurve;
}