#pragma once

#include <GLEW\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT, STOP, ROLL_LEFT, ROLL_RIGHT};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 0.0f;
const GLfloat SENSITIVITY = 0.10f;
const GLfloat FIELD_OF_VIEW = 45.0f;

class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, -90.0f),
		   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		   GLfloat yaw = YAW, GLfloat pitch = PITCH,
		   glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
		   GLfloat movement_speed = SPEED,
		   GLfloat mouse_sensitiviy = SENSITIVITY,
		   GLfloat field_of_view = FIELD_OF_VIEW);
	~Camera();

	void update(float delta_time);

	void process_keyboard(Camera_Movement direction);
	void process_mouse(GLfloat x_offset, GLfloat y_offset, bool constrain_pitch = true);
	void process_mouse_scroll(GLfloat y_offset);

	void update_camera_vectors();

	GLfloat get_field_of_view();
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
	GLfloat yaw = 0;
	GLfloat pitch = 0;
	GLfloat roll = 0;
	GLfloat field_of_view;

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
	GLfloat movement_speed;
	GLfloat acceleration = 3.0f;
	GLfloat max_velocity = 0.6f;
	GLfloat mouse_sensitivity;
	Camera_Movement direction;
	
	glm::mat4 parent_model_mat;
	float aspect_ratio;

};

