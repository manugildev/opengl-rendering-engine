#pragma once

#include <GLEW\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 30.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(0.0f,0.0f,-90.0f),
		   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		   GLfloat yaw = YAW, GLfloat pitch = PITCH,
		   glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
		   GLfloat movement_speed = SPEED,
		   GLfloat mouse_sensitiviy = SENSITIVITY,
		   GLfloat zoom = ZOOM);
	~Camera();

	void process_keyboard(Camera_Movement direction, GLfloat delta_time);
	void process_mouse(GLfloat x_offset, GLfloat y_offset, GLboolean constrain_pitch = true);
	void process_mouse_scroll(GLfloat y_offset);

	void update_camera_vectors();

	GLfloat get_zoom();
	glm::mat4 get_view_matrix();

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
	GLfloat zoom;
};

