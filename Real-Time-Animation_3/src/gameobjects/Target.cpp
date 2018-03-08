#include "Target.h"
#include <glm\ext.hpp>
#include "../util/maths.h"

Target::Target(std::string name, Application * app, Model* model, glm::vec3 object_color) : GameObject(name, app, model, object_color) {
	interpolation_value = { 0,0,0 };
	end_vector = { 0,0,0 };
	myTween = tween::Tween::make();
	myTween.cancel();
}


Target::~Target()
{
}

void Target::update(float delta_time) {
	elapsed += delta_time;	
	tween::Tween::updateTweens(elapsed);
	
	GameObject::update(delta_time);

	if (maths::vector_to_vec3(end_vector) == maths::vector_to_vec3(interpolation_value)) {
		playing_animation = false;
	} else {
		set_pos(maths::vector_to_vec3(interpolation_value));
	}
}

void Target::add_keyframe_point(glm::vec3 point) {
	keyframes.push_back(point);
}
void Target::onComplete() {

}
void Target::start_keyframe_animation(int i) {
	if (i >= keyframes.size()) return;
	myTween.cancel();
	playing_animation = true;
	glm::vec3 start_point = get_pos();
	interpolation_value = maths::vec3_to_vector(start_point);
	end_vector = maths::vec3_to_vector(keyframes[i]);
	myTween = tween::Tween::make().to(interpolation_value, end_vector).seconds(1.0);
	myTween.start();
}

