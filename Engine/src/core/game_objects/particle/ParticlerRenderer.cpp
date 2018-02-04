#include "ParticlerRenderer.h"
#include "..\..\util\shaders\particle\ParticleShader.h"
#include <iostream>
#include <glm\ext.hpp>

ParticlerRenderer::ParticlerRenderer(glm::mat4 proj_mat): proj_mat(proj_mat)  {
	shader_program = ParticleShader::create();
	this->quad = new Quad(shader_program);
	shader_program->start();
	dynamic_cast<ParticleShader*> (shader_program)->set_proj_matrix(proj_mat);
	shader_program->stop();
}

ParticlerRenderer::~ParticlerRenderer() {
}

void ParticlerRenderer::render(std::vector<Particle*> particles, Camera* camera) {
	glm::mat4 view_matrix = camera->get_view_matrix();
	this->prepare();

	dynamic_cast<ParticleShader*> (shader_program)->set_proj_matrix(camera->get_persp_proj_matrix());
	for (unsigned int i = 0; i < particles.size(); i++) {
		Particle* p = particles[i];
		update_model_view_matrix(p->get_position(), p->get_rotation(), p->get_scale(), view_matrix);
		std::cout << particles.size() << std::endl;
		this->quad->render();
	}
	this->finish_rendering();
}

//TODO: Maybe this without the view matrix here
void ParticlerRenderer::update_model_view_matrix(glm::vec3 position, float rotation, float scale, glm::mat4 view_matrix) {
	glm::mat4 model_mat = glm::mat4(1.0f);
	model_mat[3][0] = position[0];
	model_mat[3][1] = position[1];
	model_mat[3][2] = position[2];

	model_mat[0][0] = view_matrix[0][0];
	model_mat[0][1] = view_matrix[1][0];
	model_mat[0][2] = view_matrix[2][0];
	model_mat[1][0] = view_matrix[0][1];
	model_mat[1][1] = view_matrix[1][1];
	model_mat[1][2] = view_matrix[2][1];
	model_mat[2][0] = view_matrix[0][2];
	model_mat[2][1] = view_matrix[1][2];
	model_mat[2][2] = view_matrix[2][2];

	model_mat = glm::scale(model_mat, glm::vec3(scale, scale, scale));
	model_mat = glm::rotate(model_mat, glm::radians(rotation), glm::vec3(0,0,1));

	shader_program->start();
	dynamic_cast<ParticleShader*> (shader_program)->set_view_matrix(view_matrix);
	dynamic_cast<ParticleShader*> (shader_program)->set_model_matrix(model_mat);
}

void ParticlerRenderer::prepare() {
	shader_program->start();
	glBindVertexArray(quad->get_vao());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(false);
}

void ParticlerRenderer::finish_rendering() {
	glDepthMask(true);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader_program->stop();
}
