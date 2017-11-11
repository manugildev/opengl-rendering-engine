#include "core\Application.h"
#include "core\camera\Camera.h"
#include "core\game_objects\GameObject.h"
#include "core\util\texture\Texture.h"
#include "core\util\shaders\lighting\LightingShader.h"
#include <iostream>

int main(void) {

	Camera camera(glm::vec3(0.0f, 0.0f, 90.0f));

	Application *app = new Application(&camera);

	Mesh* mesh = new Mesh("models/monkey3.obj");

	Texture texture1("textures/teapot.jpg");
	Texture texture2("textures/bricks.jpg");

	GameObject *teapot = new GameObject(app, mesh, glm::vec3(1.0f, 1.0f, 1.0f));
	GameObject *teapot1 = new GameObject(app, mesh, glm::vec3(1.0f, 1.0f, 1.0f), &texture1);
	GameObject *teapot2 = new GameObject(app, mesh, glm::vec3(1.0f, 1.0f, 1.0f), &texture2);

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
	PointLight* p_light_1 = new PointLight(app, glm::vec3(30.0f, 0.0f, 0.0f), glm::vec3(1.0f), 1.0f, 0.01f, 0.01f);
	PointLight* p_light_2 = new PointLight(app, glm::vec3(-30.0f, 0.0f, 0.0f), glm::vec3(1.0f,0.6f,0.6f), 1.0f, 0.01f, 0.01f);
	PointLight* p_light_3 = new PointLight(app, glm::vec3(0.0f, 0.0f, -30.0f), glm::vec3(0.6f, 1.0f, 0.6f), 1.0f, 0.01f, 0.01f);

	DirLight* d_light = new DirLight(app, glm::vec3(0.0f, -0.8f, -1.0f), glm::vec3(1.0f));

	p_light_1->set_shader_program(shader_program1);
	p_light_2->set_shader_program(shader_program1);
	p_light_3->set_shader_program(shader_program1);

	d_light->set_shader_program(shader_program1);

	std::vector<GameObject*> objects = {teapot, teapot1, teapot2};
	std::vector<PointLight*> point_lights = {p_light_1, p_light_2, p_light_3};

	app->set_game_objects(objects);
	app->set_directional_light(d_light);
	app->set_point_lights(point_lights);

	app->runMainGameLoop();
}