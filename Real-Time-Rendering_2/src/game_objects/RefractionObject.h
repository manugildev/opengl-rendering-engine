#pragma once
#include "core\Application.h"

class RefractionObject : public GameObject {
public:
	RefractionObject(Application * app, Model * model, glm::vec3 color);
	~RefractionObject();

	virtual void update(float delta_time);
	virtual void render();
	virtual void set_shader_program(ShaderProgram* shader_program);

	void set_environment_map_id(GLuint environment_map_id);

private:
	GLuint environment_map_id = 0;
};

