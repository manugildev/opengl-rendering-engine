#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, glm::vec3 front,
			   GLfloat movement_speed, GLfloat mouse_sensitivity, GLfloat zoom) {
	this->position = position;
	this->world_up = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->front = front;
	this->movement_speed = movement_speed;
	this->mouse_sensitivity = mouse_sensitivity;
	this->zoom = zoom;
	this->update_camera_vectors();
}

void Camera::process_keyboard(Camera_Movement direction, GLfloat delta_time) {
	GLfloat velocity = this->movement_speed * delta_time;
	if (direction == FORWARD) this->position += this->front * velocity;
	if (direction == BACKWARD) this->position -= this->front * velocity;
	if (direction == LEFT) this->position -= this->right * velocity;
	if (direction == RIGHT) this->position += this->right * velocity;
}

void Camera::process_mouse(GLfloat x_offset, GLfloat y_offset, GLboolean constrain_pitch) {
	x_offset *= this->mouse_sensitivity;
	y_offset *= this->mouse_sensitivity;

	this->yaw += x_offset;
	this->pitch += y_offset;

	if (constrain_pitch) {
		if (this->pitch > 89.0f) this->pitch = 89.0f;
		if (this->pitch < -89.0f) this->pitch = -89.0f;
	}
	this->update_camera_vectors();
}

void Camera::process_mouse_scroll(GLfloat y_offset) {
	if (this->zoom >= 1.0f && this->zoom <= 65.0f) this->zoom -= y_offset;
	if (this->zoom <= 1.0f) this->zoom = 1.0f;
	if (this->zoom >= 65.0f) this->zoom = 65.0f;
}

void Camera::update_camera_vectors() {
	/* Calculate the new front vectors */
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(front);


	/* Recalculate the new Right and Up Vector */
	this->right = glm::normalize(glm::cross(this->front, this->world_up));
	this->up = glm::normalize(glm::cross(this->right, this->front));

}

glm::mat4 Camera::get_view_matrix() {
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

glm::mat4 Camera::get_persp_proj_matrix() {
	return glm::perspective(glm::radians(this->get_zoom()), this->aspect_ratio, 0.1f, 1000.0f);;
}

GLfloat Camera::get_zoom() {
	return this->zoom;
}

void Camera::set_aspect_ratio(float aspect_ratio) {
	this->aspect_ratio = aspect_ratio;
}

Camera::~Camera() {}