#pragma once

#include <GLEW\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 60.0f;
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

	void process_keyboard(Camera_Movement direction, GLfloat delta_time);
	void process_mouse(GLfloat x_offset, GLfloat y_offset, GLboolean constrain_pitch = true);
	void process_mouse_scroll(GLfloat y_offset);

	void update_camera_vectors();

	GLfloat get_field_of_view();
	glm::mat4 get_view_matrix();
	glm::mat4 get_persp_proj_matrix();
	void set_aspect_ratio(float aspect_ratio);

private:
	glm::vec3 position;
	glm::vec3 world_up;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	/* Euler Angles */
	GLfloat yaw;
	GLfloat pitch;

	/* Camera Options */
	GLfloat movement_speed;
	GLfloat mouse_sensitivity;
	GLfloat field_of_view;

	float aspect_ratio;
};

