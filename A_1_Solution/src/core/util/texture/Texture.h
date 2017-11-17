#pragma once

#include <iostream>
#include <GLEW/glew.h>

const std::string TEXTURE_WHITE_PIXEL = "textures/empty_pixel.jpg";

class Texture {
public:
	Texture(GLenum texture_target=GL_TEXTURE_2D, const std::string &file_name=TEXTURE_WHITE_PIXEL);

	GLint load();
	void bind(int texture_unit);
	void unbind();
	int get_unit();
	std::string get_file_name();
	~Texture();

private:
	int unit = 0;

	GLuint texture_id;
	GLenum texture_target;
	std::string file_name;
};

