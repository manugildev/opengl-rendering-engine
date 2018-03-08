#pragma once
#include "..\GameObject.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <tween\tween.h>

class Application;

class Plane : public GameObject {
public:
	Plane(std::string name, Application* app, Model* model, Camera* camera);
	void attach_wheels(Application * app);
	void attach_propeller(Application * app);
	void attach_arrows(Application* app);
	void update(float delta_time) override;
	void render() override;
	void set_shader_program(ShaderProgram* shader_program) override;
	void set_toon_shading(bool toon_shading) override;

	GameObject* get_red_arrow();
	GameObject* get_blue_arrow();
	GameObject* get_green_arrow();

	bool show_debug = false;

	~Plane();

	glm::vec3 normal = glm::vec3(0, 1, 0);			//inital vectors of the plane, defines coordinate space for plane
	glm::vec3 forwardVector = glm::vec3(0, 0, -1);
	glm::vec3 barrel = glm::vec3(-1, 0, 0);
	glm::quat transform;							//transofmration quaternion
	glm::vec3 axis_z;								//forwardVector axis quaterion
	glm::vec3 axis_x;								//horizaontal axis quaternion
	glm::vec3 axis_y;								//top axis quaternion

	bool with_quaternions = true;

	void start_roll();
	void start_yaw();

	float start_time = 0.0f;
	float elapsed = 0.0f;
	float finish_time = 1.0f;
	float from = 0.0f;
	float to = 1.0f;
	float interpolation_value = 0.0f; 
	bool animation_start = false;

	glm::quat new_transform;

	void set_speed_x(float speed);
	void set_speed_y(float speed);
	void set_speed_z(float speed);

private:
	GameObject * propeller;
	GameObject * wheels;
	GameObject * green_arrow;
	GameObject * blue_arrow;
	GameObject * red_arrow;

	glm::vec3 quaternion_speed;
	void update_quaternion_axis(glm::quat transform);
	void update_quaternion_speed(float delta_time);
};

