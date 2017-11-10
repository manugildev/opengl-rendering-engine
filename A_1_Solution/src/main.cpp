#include "core\Application.h"
#include "core\camera\Camera.h"
#include "core\game_objects\GameObject.h"
#include "core\game_objects\Light.h"
#include "core\util\texture\Texture.h"
#include <iostream>

int main(void) {

	Camera camera(glm::vec3(0.0f, 0.0f, 90.0f));

	Application *app = new Application(&camera);

	Texture texture("textures/teapot.jpg",0);
	Texture texture2("textures/bricks.jpg",1);
	GameObject *teapot = new GameObject(app, glm::vec3(1.0f, 0.3f, 0.0f), &texture);
	GameObject *teapot1 = new GameObject(app, glm::vec3(1.0f, 1.0f, 1.0f), &texture2);
	GameObject *teapot2 = new GameObject(app, glm::vec3(0.5f, 0.3f, 0.76f), &texture);

	LightingShader* shader_program = LightingShader::create();

	teapot->set_shader_program(shader_program);
	teapot1->set_shader_program(shader_program);
	teapot2->set_shader_program(shader_program);

	teapot->set_pos(glm::vec3(40.0f, 0.0f, 0.0f));
	teapot1->set_pos(glm::vec3(0.0f, 0.0f, -40.0f));
	teapot2->set_pos(glm::vec3(-40.0f, 0.0f, 0.0f));
	

	// TODO: Test if vectors would be a better option than arrays
	GameObject *objects[3] = {teapot, teapot1, teapot2 };
	app->runMainGameLoop(objects,3);
}