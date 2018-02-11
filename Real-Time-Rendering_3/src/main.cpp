#include "core\Application.h"
#include "core\util\texture\Texture.h"
#include "core\util\shaders\lighting\LightingShader.h"
#include <iostream>
#include <assimp\Importer.hpp>
#include "core\game_objects\cube_map\CubeMap.h"
#include "core\util\gui\GuiRenderer.h"
#include "input\Input.h"

#include <tweakbar\AntTweakBar.h>

int main(void) {
	
	/* Camera */
	Camera camera(glm::vec3(0.0f, 7.0f, 10.0f));

	/* Application */
	Application *app = new Application(&camera);

	/* InputManager */
	InputManager* input_manager = new Input(app);

	/* Models */
	Model* barrel_model = new Model("models/r_3/barrel.obj");
	Model* rock_model = new Model("models/r_3/Rock.obj");

	/* GameObjects */
	LightingShader* shader_program = LightingShader::create();

	GameObject * teapot = new GameObject(app, barrel_model, glm::vec3(0.90f, 0.29f, 0.23f));
	teapot->set_shader_program(shader_program);
	teapot->set_pos(glm::vec3(0, 0, 4));
	teapot->set_rotation_speed(glm::vec3(0, 20, 0));
	teapot->set_scale(glm::vec3(.5f));
	teapot->set_specular_strength(1);
	teapot->set_specular_power(1);

	GameObject * teapot1 = new GameObject(app, rock_model, glm::vec3(0.90f, 0.29f, 0.23f));
	teapot1->set_shader_program(shader_program);
	teapot1->set_scale(glm::vec3(.5f));
	teapot1->set_pos(glm::vec3(0, 0, -4));
	teapot1->set_rotation_speed(glm::vec3(0, 20, 0));
	teapot1->set_specular_power(0.2);

	std::vector<GameObject*> objects = { teapot, teapot1};

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

	std::vector<PointLight*> point_lights = {p_light_7, p_light_9, p_light_8, p_light_10 };
	for (unsigned int i = 0; i < point_lights.size(); i++) point_lights[i]->set_shader_program(shader_program_lamp);
	for (unsigned int i = 0; i < point_lights.size(); i++) point_lights[i]->set_scale(glm::vec3(0.1,0.1,0.1));

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
	app->set_point_lights(point_lights);
	app->set_cube_map(cube_map);
	app->set_gui_renderer(gui_renderer);
	app->set_shaders(shaders);
	app->set_input_manager(input_manager);



	/* Run the loop */
	app->runMainGameLoop();
}