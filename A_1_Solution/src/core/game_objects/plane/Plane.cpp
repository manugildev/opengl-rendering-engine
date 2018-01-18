#include "Plane.h"
#include "../../Application.h"

Plane::Plane(Application * app, Model* model, Camera* camera) : GameObject(app, model) {
	camera = app->get_camera();
}

void Plane::update(float delta_time) {
	GameObject::update(delta_time);

	//camera->set_pos(this->get_pos());

	//this->set_rotation(glm::vec3(camera->pitch, 90-camera->yaw, 0));
	//this->model_mat[3][0] = camera->get_pos()[0] + camera->front[0];
	//this->model_mat[3][1] = camera->get_pos()[1] + camera->front[1];
	//this->model_mat[3][2] = camera->get_pos()[2] + camera->front[2];
}

Plane::~Plane() {
}
