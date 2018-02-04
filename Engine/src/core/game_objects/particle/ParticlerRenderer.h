#pragma once
#include <vector>
#include "..\..\camera\Camera.h"
#include "..\..\util\shaders\ShaderProgram.h"
#include "..\..\util\gui\Quad.h"
#include "Particle.h"

class ParticlerRenderer {
public:
	ParticlerRenderer(glm::mat4 proj_mat);
	~ParticlerRenderer();

	void render(std::vector<Particle*> particles, Camera* camera);
	void update_model_view_matrix(glm::vec3 position, float rotation, float scale, glm::mat4 view_matrix);
	void prepare();
	void finish_rendering();

private:
	GLfloat vertices[6] = {-.5f, .5f, -.5f, -.5f, .5f, .5f};
	ShaderProgram* shader_program;
	Quad* quad;

	glm::mat4 proj_mat;
};

