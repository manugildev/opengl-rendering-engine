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
	Model* sphere_model = new Model("models/sphere.obj");

	/* GameObjects */
	RefractionShader* shader_program = RefractionShader::create();

	RefractionObject * teapot = new RefractionObject(app, teapot_model, glm::vec3(0.90f, 0.29f, 0.23f));
	teapot->set_shader_program(shader_program);
	teapot->set_scale(glm::vec3(1.0f));
	teapot->set_pos(glm::vec3(0, 0, -8));
	teapot->set_rotation_speed(glm::vec3(0, 20, 0));
	teapot->set_ambient_brightness(0.3f);
	teapot->set_fresnel(true);
	teapot->set_ior(0.8f);
	teapot->set_ambient_brightness(0.9f);
	teapot->set_refractive_factor(0.0f);

	RefractionObject * teapot1 = new RefractionObject(app, sphere_model, glm::vec3(0.90f, 0.29f, 0.23f));
	teapot1->set_shader_program(shader_program);
	teapot1->set_scale(glm::vec3(1.0f));
	teapot1->set_pos(glm::vec3(0, 0, 0));
	teapot1->set_rotation_speed(glm::vec3(0, 20, 0));
	teapot1->set_toon_shading(true);

	RefractionObject * teapot2 = new RefractionObject(app, sphere_model, glm::vec3(0.90f, 0.29f, 0.23f));
	teapot2->set_shader_program(shader_program);
	teapot2->set_scale(glm::vec3(1.0f));
	teapot2->set_scale(glm::vec3(1.0f));
	teapot2->set_pos(glm::vec3(0, 0, 8));
	teapot2->set_rotation_speed(glm::vec3(0, 20, 0));
	teapot2->set_cook_shading(true);

	std::vector<GameObject*> objects = { teapot1, teapot, teapot2 };

	/* Lights */
	LampShader* shader_program_lamp = LampShader::create();
	DirLight* d_light = new DirLight(app, glm::vec3(1.0f, -1.0f, -0.0f), glm::vec3(1.0f));
	d_light->set_shader_program(shader_program_lamp);

	/* CubeMap */
	BasicShader* cube_map_shader = BasicShader::create("shaders/cube_vertex_shader.glsl", "shaders/cube_fragment_shader.glsl");

	CubeMap* cube_map = new CubeMap(1000, "cube_map/dallas/back.jpg", "cube_map/dallas/front.jpg", "cube_map/dallas/top.jpg", "cube_map/dallas/bot.jpg", "cube_map/dallas/left.jpg", "cube_map/dallas/right.jpg");
	cube_map->init(cube_map_shader);

	teapot->set_environment_map_id(cube_map->get_cube_map_texture());
	teapot1->set_environment_map_id(cube_map->get_cube_map_texture());
	teapot2->set_environment_map_id(cube_map->get_cube_map_texture());

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