#include "Light.h"
#include <glm\gtc\type_ptr.hpp>

Light::Light(Application* app) : GameObject(app), light_pos(5.0f, 4.0f, 0.0f), light_color(0.5f, 0.3f, 0.5f) {
	//this->init();
	this->model_mat = glm::translate(glm::mat4(1.0f), light_pos);
}

void Light::init() {

	/* Define VAO */
	glGenVertexArrays(1, &light_vao);
	glBindVertexArray(light_vao);

	/* Generate Object VBO */
	GLuint vp_vbo = 0;
	glGenBuffers(1, &vp_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(light_pos), &light_pos, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	//this->shader_program = LightingShader::create();
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
