#include "Bone.h"
#include <glm\ext.hpp>

Bone::Bone(std::string name, Application * app, Model* model, glm::vec3 object_color) : GameObject(name, app, model, object_color){
}


Bone::~Bone(){
}

void Bone::update(float delta_time){
	this->model_mat = glm::scale(glm::mat4(1.0f), this->scale);
	glm::mat4 rotation_mat = glm::toMat4(quaternion);
	this->model_mat = rotation_mat * model_mat;
	this->model_mat[3][0] = this->get_pos()[0];
	this->model_mat[3][1] = this->get_pos()[1];
	this->model_mat[3][2] = this->get_pos()[2];

	this->global_model_mat = this->model_mat;

	if (parent != nullptr) this->model_mat = parent->get_model_mat() * this->model_mat;
}

void Bone::update_quaternion(glm::quat quaternion) {
	this->quaternion = quaternion * this->quaternion;
}