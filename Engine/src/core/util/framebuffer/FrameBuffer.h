#pragma once
#include "..\texture\Texture.h"

class Application;

class FrameBuffer {
public:
	FrameBuffer(Application* app);
	~FrameBuffer();

	void bind();
	void unbind();
	void resize();
	GLuint create_frame_buffer();
	Texture* create_texture_attachment(int width, int height);
	Texture* create_depth_texture_attachment(int width, int height);
	GLuint create_depth_buffer_attachment(int widht, int height);

	Texture* get_texture();
	Texture* get_depth_texture();

private:
	GLuint fbo = 0; 
	GLuint depth_buffer = 0;
	Texture* texture;
	Texture* depth_texture;
	Application* app;
};

