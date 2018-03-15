#pragma once
#include "..\texture\Texture.h"

class Application;

class FrameBuffer {
public:
	FrameBuffer(Application* app, Texture* texture);
	~FrameBuffer();

	void bind();
	void unbind();
	void resize();

private:
	GLuint fbo = 0; 
	Texture* texture;
	Application* app;
};

