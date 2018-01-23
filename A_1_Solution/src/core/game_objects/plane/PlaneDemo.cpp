#include "PlaneDemo.h"
#include "../../Application.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <tween\tween.h>

PlaneDemo::PlaneDemo(Application * app, Model* model, Camera* camera) : GameObject(app, model) {
	camera = app->get_camera();

	this->attach_propeller(app);
	this->attach_wheels(app);
}

void PlaneDemo::attach_wheels(Application * app) {
	Model* wheels_model = new Model("models/plane/wheels.obj");
	wheels = new GameObject(app, wheels_model);
	wheels->set_pos(glm::vec3(0.0f, -1.02f, -1.7f));
	wheels->set_parent(this);
	wheels->set_scale(glm::vec3(1.0f, 1.1f, 1.1f));
	wheels->set_rotation_speed(glm::vec3(-300.0f, 00.0f, 0.0f));
}

void PlaneDemo::attach_propeller(Application * app) {
	Model* propeller_model = new Model("models/plane/propeller_1.obj");
	propeller = new GameObject(app, propeller_model);
	propeller->set_pos(glm::vec3(0.0f, -0.0f, -3.19f));
	propeller->set_parent(this);
	propeller->set_scale(glm::vec3(1.1f, 1.1f, 1.1f));
	//propeller->set_rotation_speed(glm::vec3(0.0f, 0.0f, -900.0f));
}


void PlaneDemo::update(float delta_time) {
	GameObject::update(delta_time);
	wheels->update(delta_time);
	propeller->update(delta_time);
}

void PlaneDemo::render() {
	GameObject::render();
	wheels->render();
	propeller->render();

}

void PlaneDemo::set_shader_program(LightingShader * shader_program) {
	GameObject::set_shader_program(shader_program);
	this->wheels->set_shader_program(shader_program);
	this->propeller->set_shader_program(shader_program);
}


PlaneDemo::~PlaneDemo() {

}
