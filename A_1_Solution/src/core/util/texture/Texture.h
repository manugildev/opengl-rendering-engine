#pragma once

#include <iostream>
#include <GLEW/glew.h>

class Texture {
public:
	Texture(const std::string &fileName, int unit);
	void bind();
	void unbind();
	~Texture();

	bool is_empty = false;
	int get_unit();

private:
	GLuint texture_id;
	int unit = 0;
};

