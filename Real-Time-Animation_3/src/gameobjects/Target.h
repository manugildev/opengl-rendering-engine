#pragma once
#include "core\game_objects\GameObject.h"
#include <tween\tween.h>

class Target :	public GameObject{
public:
	Target(std::string name, Application * app, Model* model, glm::vec3 object_color);
	~Target();

	void update(float delta_time) override;

	void add_keyframe_point(glm::vec3 point);
	void start_keyframe_animation(int i);

	void onComplete();

private:
	std::vector<glm::vec3> keyframes;
	bool playing_animation = false;

	std::vector<float> interpolation_value;
	std::vector<float> end_vector;
	float elapsed;
	tween::Tween myTween;
	

};

