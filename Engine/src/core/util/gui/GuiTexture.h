#pragma once
#include "Quad.h"
#include "..\texture\Texture.h"
#include <tween\tween.h>

class Application;

class GuiTexture : public Texture {
public:
	GuiTexture(Application* app, ShaderProgram* shader_program, const std::string &file_name = TEXTURE_WHITE_PIXEL);
	GuiTexture(Application* app, ShaderProgram* shader_program, Texture* texture);
	~GuiTexture();

	void update(double delta_time);
	void render();
	void update_transformation_matrix();
	void update_window_size();

	glm::vec2 get_position();
	glm::vec2 get_scale();
	glm::vec2 get_value(float percent, glm::vec2 min, glm::vec2 max);
	void go_to_center_animation();
	void go_to_initial_animation();
	void trigger_scaling_animation();

	void set_position(glm::vec2 position);
	void set_scale(glm::vec2 scale);
	void set_initial_position(glm::vec2 position);
	void set_initial_scale(glm::vec2 scale);


protected:
	Application * app;

private:
	ShaderProgram* shader_program;
	Quad* quad;
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 initial_position = glm::vec2(0);
	glm::vec2 initial_scale = glm::vec2(1.0f);
	glm::vec2 scale = glm::vec2(1.0f);
	glm::mat4 transformation_matrix;

	float end_value = 1;
	bool going_up = false;
	double elapsed;
	tween::Tween tween;
	float interpolation_value = 0;
};

