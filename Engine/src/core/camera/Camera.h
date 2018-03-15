#pragma once
#include "En.h"

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT, STOP, ROLL_LEFT, ROLL_RIGHT};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 0.0f;
const float SENSITIVITY = 0.10f;
const float FIELD_OF_VIEW = 45.0f;

class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, -90.0f),
		   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		   float yaw = YAW, float pitch = PITCH,
		   glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
			float movement_speed = SPEED,
			float mouse_sensitiviy = SENSITIVITY,
			float field_of_view = FIELD_OF_VIEW);
	~Camera();

	void update(double delta_time);

	void process_keyboard(Camera_Movement direction);
	void process_mouse(double x_offset, double y_offset, bool constrain_pitch = true);
	void process_mouse_scroll(double y_offset);

	void update_camera_vectors();

	float get_field_of_view();
	glm::mat4 get_view_matrix();
	glm::mat4 get_persp_proj_matrix();
	glm::vec3 get_pos();

	float get_aspect_ratio();
	void set_pos(glm::vec3 position);
	void set_persp_proj_matrix(glm::mat4 perspective);
	void set_view_matrix(glm::mat4 view_matrix);
	void update_view_matrix();
	void update_view_matrix_second_viewport(glm::vec3 front);
	void update_persp_proj_matrix();
	void set_aspect_ratio(float aspect_ratio);
	void set_parent_model_mat(glm::mat4 parent_model_mat);
	
	/* Euler Angles */
	float yaw = 0;
	float pitch = 0;
	float roll = 0;
	float field_of_view;

	bool first_person = false;

	glm::vec3 front;
	glm::vec3 position;
	glm::vec3 world_up;
	glm::vec3 right;
	glm::vec3 up;

private:
	glm::mat4 persp_proj_matrix;
	glm::mat4 view_matrix;
	/* Camera Options */
	float movement_speed;
	float acceleration = 0.4f;
	float max_velocity = 0.6f;
	float mouse_sensitivity;
	Camera_Movement direction;
	
	glm::mat4 parent_model_mat;
	float aspect_ratio;

};

