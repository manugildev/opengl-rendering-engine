#pragma once

#include <iostream>
#include <GLEW/glew.h>

const std::string TEXTURE_WHITE_PIXEL = "textures/empty_pixel.jpg";

class Texture {
public:
	Texture(GLenum texture_target=GL_TEXTURE_2D, const std::string &file_name=TEXTURE_WHITE_PIXEL, int num_of_textures=1);

	GLint load();
	void init(unsigned char** data, GLfloat* filter);
	void bind(int texture_unit) const;
	void unbind();
	int get_unit();
	std::string get_file_name();
	~Texture();

	void bindAsRenderTarget();

private:
	int unit = 0;

	GLuint* texture_id;

	int width, height, num_of_components;
	unsigned char* image_data;
	int num_of_textures;
	GLenum texture_target;
	std::string file_name;
};

