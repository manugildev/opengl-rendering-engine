#pragma once
#include <GLEW\glew.h>
#include <glm\glm.hpp>
#include "Quad.h"
#include "..\texture\Texture.h"

class GuiTexture {
public:
	GuiTexture(Texture* texture, GuiShader* shader_program, glm::vec2 position = glm::vec2(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	~GuiTexture();

	void update();
	void render();
	void update_transformation_matrix();

	glm::vec2 get_position();
	glm::vec2 get_scale();

	void set_position(glm::vec2 position);
	void set_scale(glm::vec2 scale);
private:
	Texture* texture;
	GuiShader* shader_program;
	Quad* quad;
	GLuint texture_id;
	glm::vec2 position;
	glm::vec2 scale;
	glm::mat4 transformation_matrix;
};

