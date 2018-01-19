#include "Plane.h"
#include "../../Application.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>



Plane::Plane(Application * app, Model* model, Camera* camera) : GameObject(app, model) {
	camera = app->get_camera();

	this->attach_propeller(app);
	this->attach_wheels(app);
	this->attach_arrows(app);
}

void Plane::attach_wheels(Application * app) {
	Model* wheels_model = new Model("models/plane/wheels.obj");
	wheels = new GameObject(app, wheels_model);
	wheels->set_pos(glm::vec3(0.0f, -1.02f, 1.7f));
	wheels->set_parent(this);
	wheels->set_scale(glm::vec3(1.0f, 1.1f, 1.1f));
	wheels->set_rotation_speed(glm::vec3(300.0f, 00.0f, 0.0f));
}

void Plane::attach_propeller(Application * app) {
	Model* propeller_model = new Model("models/plane/propeller.obj");
	propeller = new GameObject(app, propeller_model);
	propeller->set_pos(glm::vec3(0.0f, -0.0f, 3.19f));
	propeller->set_parent(this);
	propeller->set_scale(glm::vec3(1.1f, 1.1f, 1.1f));
	propeller->set_rotation_speed(glm::vec3(0.0f, 0.0f, 900.0f));
}

void Plane::attach_arrows(Application * app) {
	Model* green_arrow_model = new Model("models/green_arrow.obj");
	Model* blue_arrow_model = new Model("models/blue_arrow.obj");
	Model* red_arrow_model = new Model("models/red_arrow.obj");

	green_arrow = new GameObject(app, green_arrow_model, glm::vec3(0.0f, 1.0f, 0.0f));
	green_arrow->set_pos(glm::vec3(0.0f, 0.0f, 0.0f));
	green_arrow->set_scale(glm::vec3(3.45f, 3.45f, 3.45f));
	green_arrow->set_rotation(glm::vec3(0, 0, 0));

	blue_arrow = new GameObject(app, green_arrow_model, glm::vec3(0.0f, 0.0f, 1.0f));
	blue_arrow->set_pos(glm::vec3(0.0f, 0.0f, 0.0f));
	blue_arrow->set_parent(green_arrow);
	blue_arrow->set_scale(glm::vec3(0.90f, 0.90f, 0.90f));
	blue_arrow->set_rotation(glm::vec3(0, -90, 0));

	red_arrow = new GameObject(app, green_arrow_model, glm::vec3(1.0f, 0.0f, 0.0f));
	red_arrow->set_pos(glm::vec3(0.0f, 0.0f, 0.0f));
	red_arrow->set_parent(blue_arrow);
	red_arrow->set_scale(glm::vec3(0.90f, 0.90f, 0.90f));
	red_arrow->set_rotation(glm::vec3(-90, 90, 0));
}

void Plane::update(float delta_time) {
	this->set_parent(red_arrow);
	green_arrow->set_pos(glm::vec3(0, 25, 0));
	set_pos(glm::vec3(0, 0, 0));

	if (app->get_camera()->first_person) {
		green_arrow->set_pos(app->get_camera()->get_pos() + glm::vec3(0, -2.0f, .0f));
		set_pos(glm::vec3(-0.6f,0,0));		
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;

		glm::decompose(camera->get_view_matrix(), scale, rotation, translation, skew, perspective);
		glm::vec3 angles = glm::degrees(glm::eulerAngles(rotation));

		std::cout << glm::to_string(angles) << std::endl;
		
		green_arrow->set_rotation(glm::vec3(0,- camera->yaw-90, 0));
		app->get_camera()->field_of_view = 45.0f;
	}
	
	/* Update Following the Hierarchy that we have decided*/
	green_arrow->update(delta_time);
	blue_arrow->update(delta_time);
	red_arrow->update(delta_time);
	GameObject::update(delta_time);
	wheels->update(delta_time);
	propeller->update(delta_time);


}

void Plane::render() {
	GameObject::render();
	wheels->render();
	propeller->render();

	if (show_debug) {
		green_arrow->render();
		blue_arrow->render();
		red_arrow->render();
	}
}

void Plane::set_shader_program(LightingShader * shader_program) {
	GameObject::set_shader_program(shader_program);
	this->wheels->set_shader_program(shader_program);
	this->propeller->set_shader_program(shader_program);
	this->green_arrow->set_shader_program(shader_program);
	this->green_arrow->set_mix_power(1.0f);
	this->blue_arrow->set_shader_program(shader_program);
	this->blue_arrow->set_mix_power(1.0f);
	this->red_arrow->set_shader_program(shader_program);
	this->red_arrow->set_mix_power(1.0f);
}

GameObject* Plane::get_green_arrow() {
	return this->green_arrow;
}
GameObject* Plane::get_blue_arrow() {
	return this->blue_arrow;
}
GameObject* Plane::get_red_arrow() {
	return this->red_arrow;
}


Plane::~Plane() {
}
