#pragma once
#include "..\shaders\ShaderProgram.h"

class Quad {
public:
	Quad(ShaderProgram* shader_program);
	~Quad();

	GLuint get_vao();
	GLuint get_vertex_count();
	void render();

private:
	GLuint vao;
	ShaderProgram* shader_program;
};

