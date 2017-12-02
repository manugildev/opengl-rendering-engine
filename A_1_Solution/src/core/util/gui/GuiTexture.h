#pragma once
#include <GLEW\glew.h>
#include <glm\glm.hpp>
#include "Quad.h"

class GuiTexture {
public:
	GuiTexture(GLuint texture_id, glm::vec2 position = glm::vec2(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	~GuiTexture();

	void update();
	void render();

	glm::vec2 get_position();
	glm::vec2 get_scale();

	void set_position(glm::vec2 position);
	void set_scale(glm::vec2 scale);
private:
	GLuint texture_id;
	glm::vec2 position;
	glm::vec2 scale;
};

