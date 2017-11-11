#include "Light.h"
#include <glm\gtc\type_ptr.hpp>

Light::Light(Application* app, Mesh* mesh) : GameObject(app, mesh), light_pos(5.0f, 4.0f, 0.0f), light_color(0.5f, 0.3f, 0.5f) {
	this->model_mat = glm::translate(glm::mat4(1.0f), light_pos);
}

void Light::init() {
}

Light::~Light() {}

void Light::update(float delta_time) {
}

void Light::render() {
	//shader_program->start();
	glBindVertexArray(light_vao);

	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();

	//shader_program->set_view_matrix(view);
	//shader_program->set_proj_matrix(perspective_proj);
	//shader_program->set_model_matrix(model_mat);
	
	glDrawArrays(GL_POINT, 0, 1);

	//shader_program->stop();
}
