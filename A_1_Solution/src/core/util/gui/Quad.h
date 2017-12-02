#pragma once
#include <GLEW/glew.h>
#include "..\shaders\gui\GuiShader.h"

class Quad {
public:
	Quad();
	~Quad();

	GLuint get_vao();
	void render();

private:
	GLuint vao; 
	GuiShader* shader_program;
};

