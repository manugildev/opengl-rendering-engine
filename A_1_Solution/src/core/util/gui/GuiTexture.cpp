#include "GuiTexture.h"
#include <glm\gtc\matrix_transform.hpp>

GuiTexture::GuiTexture(Texture* texture, GuiShader* shader_program, glm::vec2 position, glm::vec2 scale) : texture(texture), shader_program(shader_program), position(position), scale(scale) {
	this->quad = new Quad(shader_program);
	this->update_transformation_matrix();
}

void GuiTexture::update() {

}

void GuiTexture::render() {
	this->texture->bind(0);
	this->shader_program->set_transformation_matrix(transformation_matrix);
	this->quad->render();
	this->texture->unbind();
}

void GuiTexture::update_transformation_matrix() {
	this->transformation_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(this->scale, 1.0f));
	this->transformation_matrix[3][0] = this->position[0];
	this->transformation_matrix[3][1] = this->position[1];
}

glm::vec2 GuiTexture::get_position() {
	return this->position;
}

glm::vec2 GuiTexture::get_scale() {
	return this->scale;
}

void GuiTexture::set_position(glm::vec2 position) {
	this->position = position;
	this->update_transformation_matrix();
}

void GuiTexture::set_scale(glm::vec2 scale) {
	this->scale = scale;
	this->update_transformation_matrix();
}

GuiTexture::~GuiTexture() {}