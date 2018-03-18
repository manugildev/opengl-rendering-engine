#include "FrameBuffer.h"
#include "..\..\Application.h"

FrameBuffer::FrameBuffer(Application* app) : texture(texture), app(app) {
	// Create Frame Buffer
	this->fbo = create_frame_buffer();
	this->texture = create_texture_attachment(app->get_window()->get_width(), app->get_window()->get_height());
	this->depth_texture = create_depth_texture_attachment(app->get_window()->get_width(), app->get_window()->get_height());
	
	// Alternative: Depth Buffer. Faster but you can not render it into the texture
	//this->depth_buffer = create_depth_buffer_attachment(app->get_window()->get_width(), app->get_window()->get_height());
}

void FrameBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FrameBuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::resize() {
	texture->bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, app->get_window()->get_width(), app->get_window()->get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	depth_texture->bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, app->get_window()->get_width(), app->get_window()->get_height(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
}

GLuint FrameBuffer::create_frame_buffer(){
	GLuint new_fbo = 0;
	glGenFramebuffers(1, &new_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, new_fbo);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return new_fbo;
}

Texture* FrameBuffer::create_texture_attachment(int width, int height) {
	Texture* new_texture = new Texture();
	new_texture->bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, *new_texture->get_texture_id(), 0);
	return new_texture;
}

Texture* FrameBuffer::create_depth_texture_attachment(int width, int height) {
	Texture* new_texture = new Texture("textures/empty_pixel.png", GL_TEXTURE_2D, 20);
	new_texture->bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, *new_texture->get_texture_id(), 0);
	return new_texture;
}

GLuint FrameBuffer::create_depth_buffer_attachment(int widht, int height) {
	GLuint new_depth_buffer;
	glGenRenderbuffers(1, &new_depth_buffer);
	glBindRenderbuffer(GL_RENDERBUFFER, new_depth_buffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, widht, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, new_depth_buffer);
	return new_depth_buffer;
}

Texture * FrameBuffer::get_texture(){
	return texture;
}

Texture * FrameBuffer::get_depth_texture(){
	return depth_texture;
}

FrameBuffer::~FrameBuffer() {}
