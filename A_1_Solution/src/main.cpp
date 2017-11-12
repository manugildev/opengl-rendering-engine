#include "core\Application.h"
#include "core\camera\Camera.h"
#include "core\game_objects\GameObject.h"
#include "core\util\texture\Texture.h"
#include "core\util\shaders\lighting\LightingShader.h"
#include <iostream>
#include <assimp/Importer.hpp>

int main(void) {

	Camera camera(glm::vec3(0.0f, 0.0f, 90.0f));

	Application *app = new Application(&camera);

	Model* mesh = new Model("models/monkey3.obj");

	Texture texture1("textures/UMP45Texture.png");
	Texture texture2("textures/teapot.jpg");

	GameObject *teapot = new GameObject(app, mesh, glm::vec3(1.0f, 0.0f, 1.0f));
	GameObject *teapot1 = new GameObject(app, mesh, glm::vec3(1.0f, 0.0f, 1.0f), &texture2);
	GameObject *teapot2 = new GameObject(app, mesh, glm::vec3(1.0f, 0.0f, 1.0f));

	LightingShader* shader_program = LightingShader::create();

	teapot->set_shader_program(shader_program);
	teapot1->set_shader_program(shader_program);
	teapot2->set_shader_program(shader_program);

	teapot->set_pos(glm::vec3(40.0f, 0.0f, 0.0f));
	teapot1->set_pos(glm::vec3(-40.0f, 0.0f, 0.0f));
	teapot2->set_pos(glm::vec3(0.0f, 0.0f, -40.0f));

	teapot->set_scale(glm::vec3(10.0f));
	teapot->set_rotation_speed(glm::vec3(0.0f, 30.0f, 0.0f));

	LampShader* shader_program1 = LampShader::create();
	PointLight* p_light_1 = new PointLight(app, glm::vec3(40.0f, 1.0f, 4.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.001f);
	PointLight* p_light_2 = new PointLight(app, glm::vec3(-40.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.01f);
	PointLight* p_light_3 = new PointLight(app, glm::vec3(0.0f, 0.0f, -30.0f), glm::vec3(0.4f, 0.0f, 1.0f), 1.0f, 0.001f, 0.01f);

	DirLight* d_light = new DirLight(app, glm::vec3(0.0f, -0.8f, -1.0f), glm::vec3(1.0f));

	p_light_1->set_shader_program(shader_program1);
	p_light_2->set_shader_program(shader_program1);
	p_light_3->set_shader_program(shader_program1);

	d_light->set_shader_program(shader_program1);

	std::vector<GameObject*> objects = {teapot, teapot2, teapot1};
	std::vector<PointLight*> point_lights = {p_light_1, p_light_2, p_light_3};

	app->set_game_objects(objects);
	app->set_directional_light(d_light);
	app->set_point_lights(point_lights);

	app->runMainGameLoop();
}