#include "FrameBuffer.h"
#include "..\..\Application.h"

FrameBuffer::FrameBuffer(Application* app, Texture* texture) : texture(texture), app(app) {
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	
	texture->bind();

	/* ======================================================================================= */
	/* Create Texture Attachment */
	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, app->get_window()->get_width(), app->get_window()->get_height() , 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 940, 540, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, *texture->get_texture_id(), 0);
	/* ======================================================================================= */

	/* ======================================================================================= */
	/* Depth Buffer Attachment - Not texture */
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, app->get_window()->get_width(), app->get_window()->get_height());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);


	// Set the list of draw buffers.
	GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};
	glDrawBuffers(1, DrawBuffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) std::cout << "Error with the framebuffer" << std::endl;
}

void FrameBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FrameBuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::resize() {
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, app->get_window()->get_width(), app->get_window()->get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
}

FrameBuffer::~FrameBuffer() {}
