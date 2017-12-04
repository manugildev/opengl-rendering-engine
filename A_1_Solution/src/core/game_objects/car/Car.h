#pragma once
#include "..\GameObject.h"

class Application;

class Car : public GameObject {

public:
	Car(Application *, Model* model, glm::vec3 object_color);
	void update(float delta_time) override;
	~Car();
	void set_initial_pos(glm::vec3 pos);

	void start_turn_around_animation();
	void stop_turn_around_animation();


private:
	float city_size = 50;
	glm::vec3 initial_position;
	glm::vec3 initial_speed;
	float initial_rotation_y;
	float distance_traveled;

	bool animation_running = false;
	float previous_random_mutiplier = 0;

};

