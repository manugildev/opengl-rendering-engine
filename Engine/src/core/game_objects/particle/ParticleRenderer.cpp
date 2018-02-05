#include "ParticleRenderer.h"
#include "..\..\util\shaders\particle\ParticleShader.h"
#include <iostream>
#include <glm\ext.hpp>

#define MAX_INSTANCES 10000
#define INSTANCE_DATA_LENGTH 16

ParticleRenderer::ParticleRenderer(glm::mat4 proj_mat) : proj_mat(proj_mat) {
	shader_program = ParticleShader::create();
	this->quad = new Quad(shader_program);
	shader_program->start();
	dynamic_cast<ParticleShader*> (shader_program)->set_proj_matrix(proj_mat);
	shader_program->stop();

	this->vbo = create_empty_vbo(INSTANCE_DATA_LENGTH * MAX_INSTANCES);
	add_instanced_attribute(quad->get_vao(), vbo, 1, 4, INSTANCE_DATA_LENGTH, 0);
	add_instanced_attribute(quad->get_vao(), vbo, 2, 4, INSTANCE_DATA_LENGTH, 4);
	add_instanced_attribute(quad->get_vao(), vbo, 3, 4, INSTANCE_DATA_LENGTH, 8);
	add_instanced_attribute(quad->get_vao(), vbo, 4, 4, INSTANCE_DATA_LENGTH, 12);

	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, MAX_INSTANCES * INSTANCE_DATA_LENGTH * sizeof(GLfloat), NULL, GL_STREAM_DRAW);


}

ParticleRenderer::~ParticleRenderer() {
}

void ParticleRenderer::render(std::vector<Particle*> particles, Camera* camera) {
	this->prepare();

	dynamic_cast<ParticleShader*> (shader_program)->set_proj_matrix(camera->get_persp_proj_matrix());
	dynamic_cast<ParticleShader*> (shader_program)->set_view_matrix(camera->get_view_matrix());
	//dynamic_cast<ParticleShader*> (shader_program)->set_number_of_rows(1);

	const int p_size = particles.size();
	std::vector<float>* vbo_data = new std::vector<float>;

	particles[0]->get_texture()->bind(0);
	for (unsigned int i = 0; i < particles.size(); i++) {
		Particle* p = particles[i];
		update_model_view_matrix(p->get_position(), p->get_rotation(), p->get_scale(), camera->get_view_matrix(), vbo_data);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	particles[0]->get_texture()->unbind();
	std::cout << "Particles: " << particles.size() << std::endl;
	//udpate_vbo(particles.size(), vbo, *vbo_data, particles_position_buffer);
	//glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, quad->get_vertex_count(), particles.size());
	this->finish_rendering();
	delete vbo_data;
}

//TODO: Maybe this without the view matrix here
void ParticleRenderer::update_model_view_matrix(glm::vec3 position, float rotation, float scale, glm::mat4 view_matrix, std::vector<float>* vbo_data) {
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
	model_mat = glm::rotate(model_mat, glm::radians(rotation), glm::vec3(0, 0, 1));

	//store_matrix_data(model_mat, vbo_data);
	dynamic_cast<ParticleShader*> (shader_program)->set_model_matrix(model_mat);
}

void ParticleRenderer::store_matrix_data(glm::mat4 model_mat, std::vector<float>* vbo_data) {
	vbo_data->push_back(model_mat[0][0]);
	vbo_data->push_back(model_mat[0][1]);
	vbo_data->push_back(model_mat[0][2]);
	vbo_data->push_back(model_mat[0][3]);
	vbo_data->push_back(model_mat[1][0]);
	vbo_data->push_back(model_mat[1][1]);
	vbo_data->push_back(model_mat[1][2]);
	vbo_data->push_back(model_mat[1][3]);
	vbo_data->push_back(model_mat[2][0]);
	vbo_data->push_back(model_mat[2][1]);
	vbo_data->push_back(model_mat[2][2]);
	vbo_data->push_back(model_mat[2][3]);
	vbo_data->push_back(model_mat[3][0]);
	vbo_data->push_back(model_mat[3][1]);
	vbo_data->push_back(model_mat[3][2]);
	vbo_data->push_back(model_mat[3][3]);

}

void ParticleRenderer::prepare() {
	shader_program->start();
	glBindVertexArray(quad->get_vao());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(false);
}

void ParticleRenderer::finish_rendering() {
	glDepthMask(true);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0); 
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glBindVertexArray(0);
	shader_program->stop();
}

int ParticleRenderer::create_empty_vbo(int float_count) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, float_count * 4, NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vbo;
}

void ParticleRenderer::add_instanced_attribute(GLuint vao, GLuint vbo, GLuint attribute, GLuint data_size, GLuint instanced_data_length, GLuint offset) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glVertexAttribPointer(attribute, data_size, GL_FLOAT, false, instanced_data_length * 4, (void*)(offset * 4));
	glVertexAttribDivisor(attribute, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ParticleRenderer::udpate_vbo(int particles_size, int vbo, std::vector<float> data, GLuint particles_position_buffer) {
	float *p = &data[0];
	//std::cout << p[2] << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, MAX_INSTANCES * INSTANCE_DATA_LENGTH, NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particles_size * INSTANCE_DATA_LENGTH, p);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}