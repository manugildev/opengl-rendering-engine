#pragma once

#include <iostream>
#include <GLEW/glew.h>

const std::string TEXTURE_WHITE_PIXEL = "textures/empty_pixel.jpg";

class Texture {
public:
	Texture(const std::string &file_name=TEXTURE_WHITE_PIXEL, GLenum texture_target = GL_TEXTURE_2D, int num_of_textures=1);

	GLint load();
	GLuint* get_texture_id();
	void bind(int texture_unit = 0) const;
	void unbind();
	int get_unit();
	std::string get_file_name();
	~Texture();

	int get_width();
	int get_height();
	
private:
	int unit = 0;

	GLuint* texture_id;

	int width, height, num_of_components;
	int num_of_textures;
	GLenum texture_target;
	std::string file_name;
};

