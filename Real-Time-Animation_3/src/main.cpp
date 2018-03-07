#include "core\Application.h"
#include "core\util\texture\Texture.h"
#include "core\util\shaders\lighting\LightingShader.h"
#include <iostream>
#include <assimp\Importer.hpp>
#include "core\game_objects\cube_map\CubeMap.h"
#include "core\util\gui\GuiRenderer.h"
#include "input\Input.h"
#include "gameobjects\Bone.h"
#include "gameobjects\Skeleton.h"
#include <glm\ext.hpp>


int main(void) {

	/* Camera */
	Camera camera(glm::vec3(0.0f, 7.0f, 10.0f));

	/* Application */
	Application *app = new Application(&camera);

	/* InputManager */
	InputManager* input_manager = new Input(app);

	Model* floor_mipmap = new Model("models/floor.obj", 20);
	Model* bone_model = new Model("models/bone.obj");
	Model* sphere_model = new Model("models/sphere.obj");

	/* GameObjects */
	LightingShader* shader_program = LightingShader::create();

	GameObject * floor1 = new GameObject("floor", app, floor_mipmap, glm::vec3(0.90f, 0.29f, 0.23f));
	floor_mipmap->textures[1].diffuse_texture = new Texture();
	floor1->set_shader_program(shader_program);
	floor1->set_pos(glm::vec3(0, 0, 0));
	floor1->set_scale(glm::vec3(1.0f));
	floor1->set_specular_strength(0);
	floor1->set_specular_power(1);
	floor1->set_mix_power(0.1);
	
	GameObject * target = new GameObject("target", app, sphere_model, glm::vec3(0.90f, 0.50f, 0.23f));
	target->set_shader_program(shader_program);
	target->set_pos(glm::vec3(0, 2.52, 0));
	target->set_scale(glm::vec3(0.07));
	target->set_mix_power(0.9);

	Skeleton* skeleton = new Skeleton("skeleton", app, target);
	skeleton->set_shader_program(shader_program);
	
	Bone* bone1 = new Bone("bone1", app, bone_model, glm::vec3(0.90f, 0.29f, 0.23f));
	bone1->set_shader_program(shader_program);
	bone1->set_pos(glm::vec3(0, 0, 0));
	bone1->set_scale(glm::vec3(1));
	bone1->set_mix_power(1);
	bone1->set_specular_strength(0);
	bone1->set_specular_power(1);
	bone1->set_mix_power(0.9);

	Bone* bone2 = new Bone("bone2", app, bone_model, glm::vec3(0.29f, 0.90f, 0.23f));
	bone2->set_parent(bone1);
	bone2->set_shader_program(shader_program);
	bone2->set_pos(glm::vec3(0, 1.275, 0));
	bone2->set_scale(glm::vec3(0.75));
	bone2->set_mix_power(0.9);

	Bone* bone3 = new Bone("efector", app, sphere_model, glm::vec3(0.29f, 0.23f, 0.90f));
	bone3->set_parent(bone2);
	bone3->set_shader_program(shader_program);
	bone3->set_pos(glm::vec3(0, 1.32, 0));
	bone3->set_scale(glm::vec3(0.03));
	bone3->set_mix_power(0.9);

	skeleton->add(bone1);
	skeleton->add(bone2);
	skeleton->add(bone3);
	
	std::vector<GameObject*> objects = { skeleton, target };

	/* Lights */
	LampShader* shader_program_lamp = LampShader::create();

	PointLight* p_light_7 = new PointLight(app, glm::vec3(0, 0, 4), glm::vec3(1.0f, .0f, 0.0f), 0.0f, 1.0f, 0.0f);
	PointLight* p_light_8 = new PointLight(app, glm::vec3(0, 0, 4), glm::vec3(0.0f, .0f, 1.0f), .3f, 0.8f, 0.1f);
	PointLight* p_light_9 = new PointLight(app, glm::vec3(0, 0, -4), glm::vec3(0.0f, 1.0f, 0), .3f, 0.8f, 0.1f);
	PointLight* p_light_10 = new PointLight(app, glm::vec3(0, 0, -4), glm::vec3(1.0f), .3f, 0.8f, 0.1f);

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