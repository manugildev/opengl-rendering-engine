#include "Camera.h"
#include <iostream>
#include <glm\ext.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, glm::vec3 front,
	GLfloat movement_speed, GLfloat mouse_sensitivity, GLfloat zoom) {
	this->position = position;
	this->world_up = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->front = front;
	this->movement_speed = movement_speed;
	this->mouse_sensitivity = mouse_sensitivity;
	this->field_of_view = zoom;
	this->update_camera_vectors();
}

void Camera::process_keyboard(Camera_Movement direction) {
	this->direction = direction;
}

void Camera::process_mouse(GLfloat x_offset, GLfloat y_offset, bool constrain_pitch) {
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
	if (this->field_of_view >= 1.0f && this->field_of_view <= 85.0f) this->field_of_view -= y_offset;
	if (this->field_of_view <= 1.0f) this->field_of_view = 1.0f;
	if (this->field_of_view >= 85.0f) this->field_of_view = 85.0f;
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
	return this->view_matrix;
}

glm::mat4 Camera::get_persp_proj_matrix() {
	return this->persp_proj_matrix;
}

glm::vec3 Camera::get_pos() {
	return this->position;
}

void Camera::set_pos(glm::vec3 position) {
	this->position = position;
}

void Camera::set_persp_proj_matrix(glm::mat4 perspective) {
	this->persp_proj_matrix = perspective;
}

void Camera::set_view_matrix(glm::mat4 view_matrix) {
	this->view_matrix = view_matrix;
}

void Camera::update_view_matrix() {
	this->update_camera_vectors();
	glm::mat4 model_mat = glm::mat4(1.0f);
	model_mat = glm::rotate(model_mat, glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));

	this->field_of_view = 60;
	if (this->first_person) {
		glm::vec3 scale;
		glm::vec3 translation;
		glm::quat rotation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(parent_model_mat, scale, rotation, translation, skew, perspective);
		glm::vec3 euler_angles = glm::eulerAngles(rotation);

		glm::mat4 rotation_mat = glm::toMat4(rotation);
		model_mat = rotation_mat * glm::mat4(1.0f);

		roll = 0;
		yaw = -90;
		pitch = 0;

		this->update_camera_vectors();
		glm::mat4 new_mat = parent_model_mat * glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.9, -1.55));
		glm::decompose(new_mat, scale, rotation, translation, skew, perspective);
		this->position = translation;

		this->field_of_view = 85;
	}

	this->view_matrix = glm::lookAt(this->position, this->position + (this->front*glm::vec3(1, 1, 1)), this->up);
	this->view_matrix = model_mat * view_matrix;
}

void Camera::update_view_matrix_second_viewport(glm::vec3 front) {
	glm::vec3 second_camera_position(position[0], 210.0f, position[2]);
	this->view_matrix = glm::lookAt(second_camera_position, second_camera_position + front, glm::vec3(0, 0, -1));
}

void Camera::update_persp_proj_matrix() {
	this->persp_proj_matrix = glm::perspective(glm::radians(this->get_field_of_view()), this->aspect_ratio, 0.1f, 1000.0f);
}

float Camera::get_aspect_ratio() {
	return this->aspect_ratio;
}

GLfloat Camera::get_field_of_view() {
	return this->field_of_view;
}

void Camera::set_aspect_ratio(float aspect_ratio) {
	this->aspect_ratio = aspect_ratio;
}

void Camera::set_parent_model_mat(glm::mat4  parent_model_mat) {
	this->parent_model_mat = parent_model_mat;
}

void Camera::update(float delta_time) {
	movement_speed += (this->acceleration * delta_time);
	if (movement_speed >= max_velocity) movement_speed = max_velocity;

	if (this->direction == FORWARD) this->position += this->front * movement_speed;
	if (this->direction == BACKWARD) this->position -= this->front * movement_speed;
	if (this->direction == LEFT) this->position -= this->right * movement_speed;
	if (this->direction == RIGHT) this->position += this->right * movement_speed;
	if (this->direction == STOP) this->movement_speed = 0.0f;
	if (this->direction == ROLL_LEFT) this->roll -= 1;
	if (this->direction == ROLL_RIGHT) this->roll += 1;

	this->update_persp_proj_matrix();
	this->update_view_matrix();
}

Camera::~Camera() {}