#pragma once

#include <glm\glm.hpp>
#include <GLEW\glew.h>
#include "..\util\shaders\lamp\LampShader.h"
#include "GameObject.h"
#include "..\util\mesh\Mesh.h"

class Application;

class Light : public GameObject {
public:
	Light(Application* app);
	~Light();

	void render() override;
	void update(float delta_time) override;
	void set_initial_shader_values() override;
	void set_shader_program(LampShader* shader_program);

private:
	glm::vec3 light_pos;
	glm::vec3 light_color;
	LampShader* shader_program;
};

