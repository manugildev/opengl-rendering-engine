#include "core\Application.h"
#include "core\util\texture\Texture.h"
#include "core\util\shaders\lighting\LightingShader.h"
#include <iostream>
#include <assimp\Importer.hpp>
#include "core\game_objects\cube_map\CubeMap.h"
#include "core\util\gui\GuiRenderer.h"
#include "input\Input.h"
#include "core\game_objects\car\Car.h"


int main(void) {

	/* Camera */
	Camera camera(glm::vec3(0.0f, 7.0f, 10.0f));

	/* Application */
	Application *app = new Application(&camera);

	/* InputManager */
	InputManager* input_manager = new Input(app);

	/* Models */
	Model* floor_no_mipmap = new Model("models/floor.obj", 1);
	Model* floor_mipmap = new Model("models/floor.obj", 20);
	Model* car_model = new Model("models/volks.obj");

	/* GameObjects */
	LightingShader* shader_program = LightingShader::create();

	GameObject * floor1 = new GameObject("floor1", app, floor_no_mipmap, glm::vec3(0.90f, 0.29f, 0.23f));
	floor1->set_shader_program(shader_program);
	floor1->set_pos(glm::vec3(-50, 0.50001, 0));
	floor1->set_scale(glm::vec3(5.0f));
	floor1->set_specular_strength(0);
	floor1->set_specular_power(1);
	floor1->set_mix_power(0.5);
	//teapot->set_rotation_speed(glm::vec3(0,20,0));

	GameObject * floor2 = new GameObject("floor2", app, floor_mipmap, glm::vec3(0.29f, 0.90f, 0.23f));
	floor2->set_shader_program(shader_program);
	floor2->set_pos(glm::vec3(50.05, 0.5, 0));
	floor2->set_scale(glm::vec3(5.0f));
	floor2->set_specular_strength(0);
	floor2->set_specular_power(1);
	floor2->set_mix_power(0.5);
	//teapot1->set_rotation_speed(glm::vec3(0, 20, 0));


	Car *car1 = new Car("car1", app, car_model, glm::vec3(0.18f, 0.80f, 0.44f));
	car1->set_initial_pos(glm::vec3(0.0f, 1.0f, -10.0f));
	car1->set_rotation(glm::vec3(0.0f, 270.0f, 0.0f));
	car1->set_shader_program(shader_program);
	car1->set_scale(glm::vec3(0.5f));
	car1->set_acceleration(glm::vec3(Util::random_range(0.5f, 2.0f), 0.0f, 0.0f));

	Car *car5 = new Car("car5", app, car_model, glm::vec3(0.20f, 0.59f, 0.84f));
	car5->set_initial_pos(glm::vec3(0.0f, 1.0f, -5.0f));
	car5->set_rotation(glm::vec3(0.0f, 270.0f, 0.0f));
	car5->set_shader_program(shader_program);
	car5->set_acceleration(glm::vec3(Util::random_range(0.5f, 2.0f), 0.0f, 0.0f));
	car5->set_scale(glm::vec3(0.5f));

	Car *car2 = new Car("car2", app, car_model, glm::vec3(0.90f, 0.29f, 0.23f));
	car2->set_initial_pos(glm::vec3(0.0f, 1.0f, 0.0f));
	car2->set_rotation(glm::vec3(0.0f, -270.0f, 0.0f));
	car2->set_shader_program(shader_program);
	car2->set_acceleration(glm::vec3(-Util::random_range(0.5f, 2.0f), 0.0f, 0.0f));
	car2->set_scale(glm::vec3(0.5f));

	Car *car6 = new Car("car6", app, car_model, glm::vec3(0.94f, 0.76f, 0.05f));
	car6->set_initial_pos(glm::vec3(0.0f, 1.0f, 5.0f));
	car6->set_rotation(glm::vec3(0.0f, -270.0f, 0.0f));
	car6->set_shader_program(shader_program);
	car6->set_acceleration(glm::vec3(-Util::random_range(0.5f, 2.0f), 0.0f, 0.0f));
	car6->set_scale(glm::vec3(0.5f));

	Car *car3 = new Car("car3", app, car_model, glm::vec3(0.10f, 0.73f, 0.61f));
	car3->set_initial_pos(glm::vec3(0.0f, 1.0f, 0.0f));
	car3->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
	car3->set_shader_program(shader_program);
	car3->set_acceleration(glm::vec3(0.0f, 0.0f, -Util::random_range(0.5f, 2.0f))); 
	car3->set_scale(glm::vec3(0.5f));

	Car *car7 = new Car("car7", app, car_model, glm::vec3(0.6f, 0.34f, 0.71f));
	car7->set_initial_pos(glm::vec3(5.0f, 1.0f, 0.0f));
	car7->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
	car7->set_shader_program(shader_program);
	car7->set_acceleration(glm::vec3(0.0f, 0.0f, -Util::random_range(0.5f, 2.0f))); 
	car7->set_scale(glm::vec3(0.5f));

	Car *car4 = new Car("car4", app, car_model, glm::vec3(0.9f, 0.49f, 0.13f));
	car4->set_initial_pos(glm::vec3(-5.0f, 1.0f, 0.0f));
	car4->set_rotation(glm::vec3(0.0f, -180.0f, 0.0f));
	car4->set_shader_program(shader_program);
	car4->set_acceleration(glm::vec3(0.0f, 0.0f, Util::random_range(0.5f, 2.0f)));
	car4->set_scale(glm::vec3(0.5f));

	Car *car8 = new Car("car8", app, car_model, glm::vec3(0.97f, 0.42f, 0.56f));
	car8->set_initial_pos(glm::vec3(-10.0f, 1.0f, 0.0f));
	car8->set_rotation(glm::vec3(0.0f, -180.0f, 0.0f));
	car8->set_shader_program(shader_program);
	car8->set_acceleration(glm::vec3(0.0f, 0.0f, Util::random_range(0.5f, 2.0f))); 
	car8->set_scale(glm::vec3(0.5f));

	std::vector<GameObject*> objects = { floor1, floor2, car1, car2, car3 ,car4, car5, car6, car7, car8 };

	/* Lights */
	LampShader* shader_program_lamp = LampShader::create();

	PointLight* p_light_7 = new PointLight(app, glm::vec3(0, 0, 4), glm::vec3(1.0f, .0f, 0.0f), 0.0f, 1.0f, 0.0f);
	PointLight* p_light_8 = new PointLight(app, glm::vec3(0, 0, 4), glm::vec3(0.0f, .0f, 1.0f), .3f, 0.8f, 0.1f);
	PointLight* p_light_9 = new PointLight(app, glm::vec3(0, 0, -4), glm::vec3(0.0f, 1.0f, 0), .3f, 0.8f, 0.1f);
	PointLight* p_light_10 = new PointLight(app, glm::vec3(0, 0, -4), glm::vec3(1.0f), .3f, 0.8f, 0.1f);

	p_light_7->set_circular_speed(glm::vec2(0, 40));
	p_light_7->set_distance_from_center(5);
	p_light_8->set_circular_speed(glm::vec2(0, 40));
	p_light_8->set_circular_angle(glm::vec3(0, 180, 0));
	p_light_8->set_distance_from_center(5);
	p_light_9->set_circular_speed(glm::vec2(0, 40));
	p_light_9->set_distance_from_center(5);
	p_light_10->set_circular_speed(glm::vec2(0, 40));
	p_light_10->set_circular_angle(glm::vec3(0, 180, 0));
	p_light_10->set_distance_from_center(5);

	//std::vector<PointLight*> point_lights = {p_light_7, p_light_9, p_light_8, p_light_10 };
	//for (unsigned int i = 0; i < point_lights.size(); i++) point_lights[i]->set_shader_program(shader_program_lamp);
	//for (unsigned int i = 0; i < point_lights.size(); i++) point_lights[i]->set_scale(glm::vec3(0.1,0.1,0.1));

	DirLight* d_light = new DirLight(app, glm::vec3(1.0f, -1.0f, -0.0f), glm::vec3(1.0f));
	d_light->set_shader_program(shader_program_lamp);

	/* CubeMap */
	BasicShader* cube_map_shader = BasicShader::create("shaders/cube_vertex_shader.glsl", "shaders/cube_fragment_shader.glsl");

	CubeMap* cube_map = new CubeMap(1000);
	cube_map->init(cube_map_shader);

	/* GUI */
	GuiRenderer* gui_renderer = new GuiRenderer();

	GuiTexture* first_gui = new GuiTexture(app, gui_renderer->get_shader_program(), "textures/logo.png");
	first_gui->set_scale(glm::vec2(0.03f, 0.03f));
	first_gui->set_position(glm::vec2(0.0f, -0.0f));
	gui_renderer->add_gui_texture(first_gui);

	std::vector<ShaderProgram*> shaders = { shader_program, shader_program_lamp, cube_map_shader };

	/* Setting up the Application */
	app->set_game_objects(objects);
	app->set_directional_light(d_light);
	//app->set_point_lights(point_lights);
	app->set_cube_map(cube_map);
	app->set_gui_renderer(gui_renderer);
	app->set_shaders(shaders);
	app->set_input_manager(input_manager);



	/* Run the loop */
	app->runMainGameLoop();
}