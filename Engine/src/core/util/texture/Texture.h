#pragma once

#include <iostream>
#include <GLEW/glew.h>

const std::string TEXTURE_WHITE_PIXEL = "textures/empty_pixel.jpg";
const std::string DEFAULT_NORMAL_MAP = "textures/default_normal_map.jpg";

enum TextureType {
	DIFFUSE_TEXTURE, NORMAL_TEXTURE
};

class Texture {
public:
	Texture(const std::string &file_name=TEXTURE_WHITE_PIXEL, GLenum texture_target = GL_TEXTURE_2D, int num_of_textures=1);

	GLint load();
	GLuint* get_texture_id();
	void bind(int texture_unit = 0) const;
	void unbind();
	int get_unit();
	void set_texture_type(TextureType texture_type);
	std::string get_file_name();
	~Texture();

	int get_width();
	int get_height();
	TextureType texture_type = DIFFUSE_TEXTURE;
	
private:
	int unit = 0;
	GLuint* texture_id;

	int width, height, num_of_components;
	int num_of_textures;
	GLenum texture_target;
	std::string file_name;
};

