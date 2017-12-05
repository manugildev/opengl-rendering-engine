#pragma once
#include <GLEW\glew.h>
#include <glm\glm.hpp>
#include "Quad.h"
#include "..\texture\Texture.h"

class GuiTexture : public Texture {
public:
	GuiTexture(GuiShader* shader_program, const std::string &file_name = TEXTURE_WHITE_PIXEL);
	~GuiTexture();

	void update();
	void render();
	void update_transformation_matrix();

	glm::vec2 get_position();
	glm::vec2 get_scale();

	void set_position(glm::vec2 position);
	void set_scale(glm::vec2 scale);
private:

	GuiShader* shader_program;
	Quad* quad;
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 scale = glm::vec2(1.0f);
	glm::mat4 transformation_matrix;
};

