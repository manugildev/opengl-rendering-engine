#include "Target.h"
#include "..\util\maths.h"

Target::Target(std::string name, Application * app, Model* model, glm::vec3 object_color) : GameObject(name, app, model, object_color) {
	interpolation_value = { 0,0,0 };
	end_vector = { 0,0,0 };
	tween = tween::Tween::make();
	tween.cancel();
}


Target::~Target() {
}

void Target::update(double delta_time) {
	elapsed += delta_time;
	tween::Tween::updateTweens(elapsed);

	GameObject::update(delta_time);

	if (maths::vector_to_vec3(end_vector) == maths::vector_to_vec3(interpolation_value)) {
		playing_animation = false;
		spiral_curve = false;
	}

	if (playing_animation) {
		if (spiral_curve) {
			set_pos(+glm::vec3(get_pos().x, maths::vector_to_vec3(interpolation_value).y, get_pos().z));
		}
		else { set_pos(maths::vector_to_vec3(interpolation_value)); }
	}
	else if (playing_spline) set_pos(current_spline.get_point_on_bezier_curve(spline_interpolator));
}

void Target::add_keyframe_point(glm::vec3 point) {
	keyframes.push_back(point);
}
void Target::add_spline(Spline spline) {
	splines.push_back(spline);

}
void Target::start_keyframe_animation(unsigned int i) {
	playing_animation = true;
	playing_spline = false;
	tween.cancel();
	glm::vec3 start_point = get_pos();
	if (i == 9) {
		spiral_curve = true;
		interpolation_value = maths::vec3_to_vector(start_point);
		end_vector = maths::vec3_to_vector(start_point + glm::vec3(0, get_pos().y > 0 ? -6 : 6, 0));
		tween = tween::Tween::make().to(interpolation_value, end_vector).seconds(10.0);
		tween.start();
	}

	if (i >= keyframes.size()) return;
	interpolation_value = maths::vec3_to_vector(start_point);
	end_vector = maths::vec3_to_vector(keyframes[i]);
	tween = tween::Tween::make().to(interpolation_value, end_vector).seconds(1.0);
	tween.start();


}

void Target::start_spline_animation(unsigned int i) {
	if (i >= keyframes.size()) return;
	tween.cancel();
	playing_spline = true;
	playing_animation = false;
	spline_interpolator = 0;
	tween = tween::Tween::make().to(spline_interpolator, 1.0f).seconds(3.0);
	tween.start();
	current_spline = splines[i];
}

void Target::prepare_spline_animation(unsigned int i) {
	if (i >= keyframes.size()) return;
	tween.cancel();
	playing_animation = true;
	playing_spline = false;
	glm::vec3 start_point = get_pos();
	interpolation_value = maths::vec3_to_vector(start_point);
	end_vector = maths::vec3_to_vector(splines[i].p0);
	tween = tween::Tween::make().to(interpolation_value, end_vector).seconds(1.0);
	tween.start();
}


