#include "core\Application.h"
#include "core\camera\Camera.h"
#include "core\game_objects\GameObject.h"
#include "core\game_objects\car\Car.h"
#include "core\util\texture\Texture.h"
#include "core\util\shaders\lighting\LightingShader.h"
#include <iostream>
#include <assimp\Importer.hpp>
#include "core\game_objects\cube_map\CubeMap.h"

int main(void) {
	/* Camera */
	Camera camera(glm::vec3(0.0f, 0.0f, 90.0f));

	/* Application */
	Application *app = new Application(&camera);

	/* Models */
	Model* city_model = new Model("models/street/street.obj");
	Model* car_model = new Model("models/volks.obj");

	/* Textures */
	Texture city_texture(GL_TEXTURE_2D, "textures/marble.jpg");

	/* GameObjects */
	LightingShader* shader_program = LightingShader::create();
	GameObject *teapot = new GameObject(app, city_model, glm::vec3(1.0f));
	teapot->set_scale(glm::vec3(1.0f));
	teapot->set_rotation_speed(glm::vec3(0.0f, 0.0f, 0.0f));
	teapot->set_pos(glm::vec3(0.0f, 0.0f, 0.0f));
	teapot->set_shader_program(shader_program);

	Car *car1 = new Car(app, car_model, glm::vec3(0.18f, 0.80f, 0.44f));
	car1->set_parent(teapot);
	car1->set_initial_pos(glm::vec3(0.0f, 1.0f, -10.0f));
	car1->set_rotation(glm::vec3(0.0f, 270.0f, 0.0f));
	car1->set_shader_program(shader_program);
	car1->set_mix_power(0.8f);
	car1->set_acceleration(glm::vec3(Util::random_range(0.5f, 2.0f), 0.0f, 0.0f));

	Car *car5 = new Car(app, car_model, glm::vec3(0.20f, 0.59f, 0.84f));
	car5->set_parent(teapot);
	car5->set_initial_pos(glm::vec3(0.0f, 1.0f, -5.0f));
	car5->set_rotation(glm::vec3(0.0f, 270.0f, 0.0f));
	car5->set_shader_program(shader_program);
	car5->set_mix_power(0.8f);
	car5->set_acceleration(glm::vec3(Util::random_range(0.5f, 2.0f), 0.0f, 0.0f));

	Car *car2 = new Car(app, car_model, glm::vec3(0.90f, 0.29f, 0.23f));
	car2->set_parent(teapot);
	car2->set_initial_pos(glm::vec3(0.0f, 1.0f, 0.0f));
	car2->set_rotation(glm::vec3(0.0f, -270.0f, 0.0f));
	car2->set_shader_program(shader_program);
	car2->set_mix_power(0.8f);
	car2->set_acceleration(glm::vec3(-Util::random_range(0.5f, 2.0f), 0.0f, 0.0f));

	Car *car6 = new Car(app, car_model, glm::vec3(0.94f, 0.76f, 0.05f));
	car6->set_parent(teapot);
	car6->set_initial_pos(glm::vec3(0.0f, 1.0f, 5.0f));
	car6->set_rotation(glm::vec3(0.0f, -270.0f, 0.0f));
	car6->set_shader_program(shader_program);
	car6->set_mix_power(0.8f);
	car6->set_acceleration(glm::vec3(-Util::random_range(0.5f, 2.0f), 0.0f, 0.0f));
	
	Car *car3 = new Car(app, car_model, glm::vec3(0.10f, 0.73f, 0.61f));
	car3->set_parent(teapot);
	car3->set_initial_pos(glm::vec3(0.0f, 1.0f, 0.0f));
	car3->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
	car3->set_shader_program(shader_program);
	car3->set_mix_power(0.8f);
	car3->set_acceleration(glm::vec3(0.0f, 0.0f, -Util::random_range(0.5f, 2.0f)));

	Car *car7 = new Car(app, car_model, glm::vec3(0.6f, 0.34f, 0.71f));
	car7->set_parent(teapot);
	car7->set_initial_pos(glm::vec3(5.0f, 1.0f, 0.0f));
	car7->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
	car7->set_shader_program(shader_program);
	car7->set_mix_power(0.8f);
	car7->set_acceleration(glm::vec3(0.0f, 0.0f, -Util::random_range(0.5f, 2.0f)));

	Car *car4 = new Car(app, car_model, glm::vec3(0.9f, 0.49f, 0.13f));
	car4->set_parent(teapot);
	car4->set_initial_pos(glm::vec3(-5.0f, 1.0f, 0.0f));
	car4->set_rotation(glm::vec3(0.0f, -180.0f, 0.0f));
	car4->set_shader_program(shader_program);
	car4->set_mix_power(0.8f);
	car4->set_acceleration(glm::vec3(0.0f, 0.0f, Util::random_range(0.5f, 2.0f)));

	Car *car8 = new Car(app, car_model, glm::vec3(0.97f, 0.42f, 0.56f));
	car8->set_parent(teapot);
	car8->set_initial_pos(glm::vec3(-10.0f, 1.0f, 0.0f));
	car8->set_rotation(glm::vec3(0.0f, -180.0f, 0.0f));
	car8->set_shader_program(shader_program);
	car8->set_mix_power(0.8f);
	car8->set_acceleration(glm::vec3(0.0f, 0.0f, Util::random_range(0.5f, 2.0f)));

	std::vector<GameObject*> objects = {teapot, car1, car2, car3, car4, car5, car6, car7, car8};

	/* Lights */
	LampShader* shader_program1 = LampShader::create();
	PointLight* p_light_1 = new PointLight(app, glm::vec3(40.0f, 2.0f, 8.0f), glm::vec3(1.0f, 0.0f, 1.0f), 1.0f, 0.5f, 0.001f);
	PointLight* p_light_2 = new PointLight(app, glm::vec3(-40.0f, 2.0f, -13.0f), glm::vec3(1.0f, 1.0f, 0.0f), 1.0f, 0.5f, 0.001f);
	PointLight* p_light_3 = new PointLight(app, glm::vec3(8.0f, 2.0f, -40.0f), glm::vec3(1.0f, .0f, 0.0f), 1.0f, 0.5f, 0.001f);
	PointLight* p_light_4 = new PointLight(app, glm::vec3(-13.0f, 2.0f, 40.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.5f, 0.001f);
	PointLight* p_light_5 = new PointLight(app, glm::vec3(40.0f, 2.0f, -13.0f), glm::vec3(1.0f, 0.0f, 1.0f), 1.0f, 0.5f, 0.001f);
	PointLight* p_light_6 = new PointLight(app, glm::vec3(-40.0f, 2.0f, 8.0f), glm::vec3(1.0f, 1.0f, 0.0f), 1.0f, 0.5f, 0.001f);
	PointLight* p_light_7 = new PointLight(app, glm::vec3(-13.0f, 2.0f, -40.0f), glm::vec3(1.0f, .0f, 0.0f), 1.0f, 0.5f, 0.001f);
	PointLight* p_light_8 = new PointLight(app, glm::vec3(8.0f, 2.0f, 40.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.5f, 0.001f);
	PointLight* p_light_9 = new PointLight(app, glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f), 1.0f, 0.05f, 0.001f);

	std::vector<PointLight*> point_lights = {p_light_1, p_light_2, p_light_3, p_light_4, p_light_5, p_light_6, p_light_7, p_light_8, p_light_9};
	for (int i = 0; i < point_lights.size(); i++) point_lights[i]->set_parent(teapot);
	for (int i = 0; i < point_lights.size(); i++) point_lights[i]->set_shader_program(shader_program1);

	DirLight* d_light = new DirLight(app, glm::vec3(0.0f, -0.8f, -1.0f), glm::vec3(1.0f));
	d_light->set_shader_program(shader_program1);


	BasicShader* cube_map_shader = BasicShader::create("shaders/cube_vertex_shader.glsl", "shaders/cube_fragment_shader.glsl");
	/* CubeMap */
	CubeMap* cube_map = new CubeMap();
	cube_map->init(cube_map_shader);

	/* Setting up the Application */
	app->set_game_objects(objects);
	app->set_directional_light(d_light);
	app->set_point_lights(point_lights);
	app->set_cube_map(cube_map);

	app->runMainGameLoop();
}