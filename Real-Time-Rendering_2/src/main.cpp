#include "core\Application.h"
#include "core\util\texture\Texture.h"
#include "core\util\shaders\lighting\LightingShader.h"
#include <iostream>
#include <assimp\Importer.hpp>
#include "core\game_objects\cube_map\CubeMap.h"
#include "core\util\gui\GuiRenderer.h"
#include "input\Input.h"
#include "game_objects\RefractionObject.h"
#include "shaders\RefractionShader.h"

int main(void) {
	/* Camera */
	Camera camera(glm::vec3(0.0f, 7.0f, 10.0f));

	/* Application */
	Application *app = new Application(&camera);

	/* InputManager */
	InputManager* input_manager = new Input(app);

	/* Models */
	Model* teapot_model = new Model("models/teapot.obj");
	Model* pumba_model = new Model("models/pumba/pumba.obj");

	/* GameObjects */
	RefractionShader* shader_program = RefractionShader::create();

	RefractionObject * teapot = new RefractionObject(app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	teapot->set_shader_program(shader_program);
	teapot->set_pos(glm::vec3(0, 0, -16));
	teapot->set_rotation_speed(glm::vec3(0, 20, 0));
	teapot->set_mix_power(1.0f);
	teapot->set_ambient_brightness(0.1f);
	teapot->set_scale(glm::vec3(2.0f));

	RefractionObject * teapot1 = new RefractionObject(app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	teapot1->set_shader_program(shader_program);
	teapot1->set_scale(glm::vec3(2.0f));
	teapot1->set_pos(glm::vec3(0, 0, -8));
	teapot1->set_rotation_speed(glm::vec3(0, 20, 0));
	teapot1->set_ior(0.8);
	teapot1->set_chromatic_offset(0.0f);
	teapot1->set_refractive_factor(1.0f);
	teapot1->set_mix_power(0.4f);

	RefractionObject * teapot2 = new RefractionObject(app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	teapot2->set_shader_program(shader_program);
	teapot2->set_scale(glm::vec3(2.0f));
	teapot2->set_pos(glm::vec3(0, 0, 0));
	teapot2->set_rotation_speed(glm::vec3(0, 20, 0));
	teapot2->set_refractive_factor(0.0f);
	teapot2->set_mix_power(0.4f);

	RefractionObject * teapot3 = new RefractionObject(app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	teapot3->set_shader_program(shader_program);
	teapot3->set_scale(glm::vec3(2.0f));
	teapot3->set_pos(glm::vec3(0, 0, 8));
	teapot3->set_rotation_speed(glm::vec3(0, 20, 0));
	teapot3->set_ior(0.9);
	teapot3->set_chromatic_offset(0.05f);
	teapot3->set_refractive_factor(1.0f);
	teapot3->set_mix_power(0.4f);
	
	RefractionObject * teapot4 = new RefractionObject(app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	teapot4->set_shader_program(shader_program); 
	teapot4->set_scale(glm::vec3(2.0f));
	teapot4->set_pos(glm::vec3(0, 0, 16));
	teapot4->set_rotation_speed(glm::vec3(0, 20, 0));
	teapot4->set_ior(0.85f);
	teapot4->set_chromatic_offset(0.0f);
	teapot4->set_mix_power(0.1f);
	teapot4->set_fresnel(true);
	teapot4->set_refractive_power(2);

	RefractionObject * teapot5 = new RefractionObject(app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	teapot5->set_shader_program(shader_program); 
	teapot5->set_scale(glm::vec3(2.0f));
	teapot5->set_pos(glm::vec3(0, 0, 24));
	teapot5->set_rotation_speed(glm::vec3(0, 20, 0));
	teapot5->set_ior(0.85f);
	teapot5->set_chromatic_offset(0.05f);
	teapot5->set_mix_power(0.1f);
	teapot5->set_fresnel(true);
	teapot5->set_refractive_power(10);

	std::vector<GameObject*> objects = { teapot, teapot1, teapot2, teapot3, teapot4, teapot5 };

	/* Lights */
	LampShader* shader_program_lamp = LampShader::create();
	DirLight* d_light = new DirLight(app, glm::vec3(1.0f, -1.0f, -0.0f), glm::vec3(1.0f));
	d_light->set_shader_program(shader_program_lamp);

	/* CubeMap */
	BasicShader* cube_map_shader = BasicShader::create("shaders/cube_vertex_shader.glsl", "shaders/cube_fragment_shader.glsl");

	CubeMap* cube_map = new CubeMap(1000, "cube_map/second/back.jpg", "cube_map/second/front.jpg", "cube_map/second/top.jpg", "cube_map/second/bot.jpg", "cube_map/second/left.jpg", "cube_map/second/right.jpg");
	cube_map->init(cube_map_shader);

	teapot->set_environment_map_id(cube_map->get_cube_map_texture());
	teapot1->set_environment_map_id(cube_map->get_cube_map_texture());
	teapot2->set_environment_map_id(cube_map->get_cube_map_texture());
	teapot3->set_environment_map_id(cube_map->get_cube_map_texture());
	teapot4->set_environment_map_id(cube_map->get_cube_map_texture());
	teapot5->set_environment_map_id(cube_map->get_cube_map_texture());

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
	app->set_cube_map(cube_map);
	app->set_gui_renderer(gui_renderer);
	app->set_shaders(shaders);
	app->set_input_manager(input_manager);

	/* Run the loop */
	app->runMainGameLoop();
}