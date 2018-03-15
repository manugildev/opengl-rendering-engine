#pragma once
#include "Engine.h"
#include <tween\tween.h>
#include "Spline.h"

class Target :	public GameObject{
public:
	Target(std::string name, Application * app, Model* model, glm::vec3 object_color);
	~Target();

	void update(double delta_time) override;

	void add_keyframe_point(glm::vec3 point);
	void add_spline(Spline spline);
	void start_keyframe_animation(unsigned int i);
	void start_spline_animation(unsigned int i);
	void prepare_spline_animation(unsigned int i);

private:
	std::vector<glm::vec3> keyframes;
	std::vector<Spline> splines;
	Spline current_spline;

	bool playing_animation = false;
	bool playing_spline = false;
	bool spiral_curve = false;

	std::vector<float> interpolation_value;
	std::vector<float> end_vector;
	double elapsed;
	tween::Tween tween;
	
	float spline_interpolator = 0;


};

