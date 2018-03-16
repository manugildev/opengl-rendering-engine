#pragma once
#include "..\GameObject.h"
#include "..\..\util\shaders\lamp\LampShader.h"
#include "..\..\util\mesh\Mesh.h"

class Application;

const glm::vec3 DEFAULT_LIGHT_POS(0.0f);
const glm::vec3 DEFAULT_LIGHT_COLOR(1.0f);

class Light : public GameObject {
public:
	Light(Application* app, glm::vec3 light_position = DEFAULT_LIGHT_POS, glm::vec3 light_color = DEFAULT_LIGHT_COLOR);
	~Light();

	void render() override;
	void update(double delta_time) override;
	void set_initial_shader_values() override;
	void set_shader_program(ShaderProgram* shader_program);

	glm::vec3 get_light_position();
	glm::vec3 get_light_color();
protected:
	glm::vec3 light_position;
	glm::vec3 light_color;

private:
	ShaderProgram * shader_program;
};

