#pragma once
#include <GLEW\glew.h>
#include <glm\glm.hpp>
#include "..\camera\Camera.h"

class Application;

class GameObject {
public:
	GameObject(Application *app);
	~GameObject();

	void update();
	void render();
	void init();

	static void GameObject::AddShader(GLuint shader_program, const char * shader_text, GLenum shader_type);
	GLuint GameObject::compile_shaders();

private:
	glm::mat4 model_mat;
	GLuint teapot_vao = 0;
	GLuint location_positions, location_normals;
	GLuint shader_program_id;
	int location_proj_mat, location_view_mat, location_model_mat;
	Camera* camera;
};

