#pragma once
#include <GLEW\glew.h>
#include "..\texture\Texture.h"

class FrameBuffer {
public:
	FrameBuffer(Texture* texture);
	~FrameBuffer();

	void bind();
	void unbind();

private:
	GLuint fbo = 0; 
	Texture* texture;
};

