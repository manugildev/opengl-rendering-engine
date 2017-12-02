#pragma once
#include <GLEW/glew.h>

class Quad {
public:
	Quad(float positions[]);
	~Quad();

	void render();
	void update();

private:
	GLuint mesh_vao;
};

