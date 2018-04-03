#include "GuiTexture.h"
#include <core\Application.h>
#include "..\shaders\gui\GuiShader.h"

GuiTexture::GuiTexture(Application * app, ShaderProgram* shader_program, const std::string &file_name) : Texture(file_name), app(app), shader_program(shader_program) {
	this->quad = new Quad(shader_program);
	this->update_transformation_matrix();
	interpolation_value = 1;
	end_value = 1;
	tween = tween::Tween::make();
	tween.cancel();
}

GuiTexture::GuiTexture(Application * app, ShaderProgram * shader_program, Texture * texture) : Texture(*texture), app(app), shader_program(shader_program) {
	this->quad = new Quad(shader_program);
	this->update_transformation_matrix();
	interpolation_value = 1;
	end_value = 1;
	tween = tween::Tween::make();
	tween.cancel();
}

void GuiTexture::update(double delta_time) {
	elapsed += delta_time;
	tween::Tween::updateTweens(elapsed);

	if (going_up) {
		set_position(get_value(interpolation_value, initial_position, glm::vec2(0)));
		set_scale(get_value(interpolation_value, initial_scale, glm::vec2(app->get_window()->get_aspect_ratio(), -1.0f)));
	} else {
		set_position(get_value(interpolation_value, glm::vec2(0), initial_position));
		set_scale(get_value(interpolation_value, glm::vec2(app->get_window()->get_aspect_ratio(), -1.0f), initial_scale));
	}
}

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

void GuiTexture::set_initial_position(glm::vec2 position) {
	this->initial_position = position;
	this->position = position;
	this->update_transformation_matrix();
}

void GuiTexture::set_scale(glm::vec2 scale) {
	float aspect_ratio = app->get_window()->get_aspect_ratio();
	this->scale = glm::vec2(scale.x / aspect_ratio, scale.y);
	this->update_transformation_matrix();
}

void GuiTexture::set_initial_scale(glm::vec2 scale) {
	this->initial_scale = scale;
	float aspect_ratio = app->get_window()->get_aspect_ratio();
	this->scale = glm::vec2(scale.x / aspect_ratio, scale.y);
	this->update_transformation_matrix();
}

glm::vec2 GuiTexture::get_value(float percent, glm::vec2 min, glm::vec2 max) {
	// Calculate the distance
	float distance = glm::distance(min, max);
	if (distance == 0) return min;

	// Scale the distance
	distance = distance * percent;

	// Calculate the difference vector
	glm::vec2 difference = max - min;

	// Normalize and scale the difference vector
	difference = glm::normalize(difference) * distance;

	// Translate the vector back to A
	return (min + difference);
}

void GuiTexture::go_to_center_animation() {
	interpolation_value = 0;
	going_up = true;
	tween.cancel();
	tween = tween::Tween::make().to(interpolation_value, 1).seconds(0.5);
	tween.start();
}

void GuiTexture::go_to_initial_animation() {
	interpolation_value = 0;
	going_up = false;
	tween.cancel();
	tween = tween::Tween::make().to(interpolation_value, 1).seconds(0.5);
	tween.start();
}

void GuiTexture::trigger_scaling_animation() {
	if (going_up) go_to_initial_animation();
	else go_to_center_animation();
}

GuiTexture::~GuiTexture() {}