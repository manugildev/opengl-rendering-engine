#include "GuiTexture.h"
#include "..\..\Application.h"

GuiTexture::GuiTexture(Application * app, ShaderProgram* shader_program, const std::string &file_name) : Texture(file_name), app(app), shader_program(shader_program) {
	this->quad = new Quad(shader_program);
	this->update_transformation_matrix();
}

GuiTexture::GuiTexture(Application * app, ShaderProgram * shader_program, Texture * texture): Texture(*texture), app(app), shader_program(shader_program) {
	this->quad = new Quad(shader_program);
	this->update_transformation_matrix();
}

void GuiTexture::update() {}

void GuiTexture::render() {
	GuiShader* gui_shader = dynamic_cast<GuiShader*>(shader_program);
	gui_shader->start();
	this->bind(0);
	if (gui_shader) gui_shader->set_transformation_matrix(transformation_matrix);
	this->quad->render();
	this->unbind();
	gui_shader->stop();
}

void GuiTexture::update_transformation_matrix() {
	this->transformation_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(this->scale, 1.0f));
	this->transformation_matrix[3][0] = this->position[0];
	this->transformation_matrix[3][1] = this->position[1];
}

void GuiTexture::update_window_size() {
	float aspect_ratio = app->get_window()->get_aspect_ratio();
	this->scale = glm::vec2(initial_scale.x / aspect_ratio, initial_scale.y);
	this->update_transformation_matrix();
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
	this->initial_scale = scale; // Not very elegant
	float aspect_ratio = app->get_window()->get_aspect_ratio();
	this->scale = glm::vec2(scale.x/ aspect_ratio, scale.y);
	this->update_transformation_matrix();
}

GuiTexture::~GuiTexture() {}