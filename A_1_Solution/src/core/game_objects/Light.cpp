#include "Light.h"
#include <glm\gtc\type_ptr.hpp>

Light::Light(Camera* camera) : camera(camera), light_pos(5.0f, 4.0f, 0.0f), light_color(0.5f, 0.3f, 0.5f) {
	this->init();
}

void Light::init() {

	/* Define VAO */
	glGenVertexArrays(1, &light_vao);
	glBindVertexArray(light_vao);

	/* Generate Object VBO */
	GLuint vp_vbo = 0;
	glGenBuffers(1, &vp_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), &light_pos, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(0);

	this->shader_program = LightingShader::create();
}

Light::~Light() {}

void Light::update(float delta_time) {
	this->model_mat = glm::translate(glm::mat4(1.0f), light_pos);
}

void Light::render() {
	shader_program->start();
	glBindVertexArray(light_vao);


	glm::mat4 view = this->camera->get_view_matrix();
	glm::mat4 perspective_proj = this->camera->get_persp_proj_matrix();

	shader_program->set_view_matrix(view);
	shader_program->set_proj_matrix(perspective_proj);
	shader_program->set_model_matrix(model_mat);

	shader_program->set_light_pos(this->light_pos);
	shader_program->set_object_color(this->light_color);

	glDrawArrays(GL_POINT, 0, 3);

	shader_program->stop();
}
