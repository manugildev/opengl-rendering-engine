#include "core\Application.h"
#include "core\camera\Camera.h"
#include "core\game_objects\GameObject.h"
#include "core\game_objects\Light.h"
#include "core\util\texture\Texture.h"
#include <iostream>

int main(void) {

	Camera camera(glm::vec3(0.0f, 0.0f, 90.0f));
	
	Application *app = new Application(&camera);

	Mesh* mesh = new Mesh("models/monkey3.obj");

	Texture texture1("textures/teapot.jpg");
	Texture texture2("textures/bricks.jpg");

	GameObject *teapot = new GameObject(app, mesh, glm::vec3(1.0f, 0.3f, 0.0f));
	GameObject *teapot1 = new GameObject(app, mesh, glm::vec3(1.0f, 1.0f, 1.0f), &texture1);
	GameObject *teapot2 = new GameObject(app, mesh, glm::vec3(0.5f, 0.3f, 0.76f), &texture2);

	LightingShader* shader_program = LightingShader::create();

	teapot->set_shader_program(shader_program);
	teapot1->set_shader_program(shader_program);
	teapot2->set_shader_program(shader_program);

	teapot->set_pos(glm::vec3(40.0f, 0.0f, 0.0f));
	teapot1->set_pos(glm::vec3(0.0f, 0.0f, -40.0f));
	teapot2->set_pos(glm::vec3(-40.0f, 0.0f, 0.0f));

	teapot->set_scale(glm::vec3(10.0f, 10.0f, 10.0f));
	teapot1->set_scale(glm::vec3(10.0f, 10.0f, 10.0f));
	teapot2->set_scale(glm::vec3(10.0f, 10.0f, 10.0f));

	LampShader* shader_program1 = LampShader::create();
	Light* light = new Light(app);
	light->set_shader_program(shader_program1);

	std::vector<GameObject*> objects = {teapot, teapot1, teapot2, dynamic_cast<GameObject*>(light)};
	app->set_game_objects(objects);

	app->runMainGameLoop();
}