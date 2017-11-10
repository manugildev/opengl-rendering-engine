#pragma once
#include <GLEW\glew.h>
#include <glm\glm.hpp>
#include "..\camera\Camera.h"
#include "..\util\shaders\lighting\LightingShader.h"
#include "..\util\texture\Texture.h"

class Application;

const glm::vec3 DEFAULT_OBJ_COLOR(1.0f); 

class GameObject {
public:
	GameObject(Application *app, glm::vec3 object_color=DEFAULT_OBJ_COLOR, Texture* texture=new Texture("",0));
	~GameObject();

	void update(float delta_time);
	void render();
	void init();

	void set_initial_shader_values();

	void set_pos(glm::vec3 pos);
	void set_scale(glm::vec3 scale);
	void set_shader_program(LightingShader* shader_program);
	LightingShader* shader_program;


protected:
	GLuint teapot_vao = 0;
	GLuint location_positions, location_normals;
	Camera* camera;
	bool is_light = false;

private:
	glm::mat4 model_mat;
	glm::vec3 object_color;
	Texture* texture;

};

