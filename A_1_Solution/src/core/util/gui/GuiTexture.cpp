#include "GuiTexture.h"

GuiTexture::GuiTexture(GLuint texture_id, glm::vec2 position, glm::vec2 scale) : texture_id(texture_id), position(position), scale(scale) {}

GuiTexture::~GuiTexture() {}

glm::vec2 GuiTexture::get_position() {
	return this->position;
}

glm::vec2 GuiTexture::get_scale() {
	return this->scale;
}

void GuiTexture::set_position(glm::vec2 position) {
	this->position = position;
}

void GuiTexture::set_scale(glm::vec2 scale) { this->scale = scale; }
