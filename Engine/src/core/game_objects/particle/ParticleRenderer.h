#pragma once
#include "En.h"
#include "Particle.h"

#include "..\..\camera\Camera.h"
#include "..\..\util\shaders\ShaderProgram.h"
#include "..\..\util\gui\Quad.h"

class ParticleRenderer {
public:
	ParticleRenderer(glm::mat4 proj_mat);
	~ParticleRenderer();

	void render(std::vector<Particle*> particles, Camera* camera);
	void update_model_view_matrix(glm::vec3 position, float rotation, float scale, glm::mat4 view_matrix, std::vector<float>* vbo_data);
	void prepare();
	void finish_rendering();
	int create_empty_vbo(int float_count); 
	void add_instanced_attribute(GLuint vao, GLuint vbo, GLuint attribute, GLuint data_size, GLuint instanced_data_length, GLuint offset);
	void udpate_vbo(int particles_size, int vbo, std::vector<float> data, GLuint particles_position_buffer);
	void store_matrix_data(glm::mat4 model_mat, std::vector<float>* vbo_data);



private:
	GLfloat vertices[6] = {-.5f, .5f, -.5f, -.5f, .5f, .5f};
	ShaderProgram* shader_program;
	Quad* quad;

	glm::mat4 proj_mat;
	GLuint vbo;
	GLuint particles_position_buffer;
	int pointer = 0;
};

