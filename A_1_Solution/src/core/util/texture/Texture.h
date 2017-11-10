#pragma once

#include <iostream>
#include <GLEW/glew.h>

class Texture {
public:
	Texture(const std::string &fileName);
	void bind(unsigned int unit);
	~Texture();

	bool is_empty = false;

private:
	GLuint texture_id;
};

