#include "Engine.h"

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

	RefractionObject * pumba1 = new RefractionObject("pumba1", app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	pumba1->set_shader_program(shader_program);
	pumba1->set_pos(glm::vec3(0, 0, -16));
	pumba1->set_rotation_speed(glm::vec3(0, 20, 0));
	pumba1->set_mix_power(1.0f);
	pumba1->set_ambient_brightness(0.1f);
	pumba1->set_scale(glm::vec3(2.0f));

	RefractionObject * pumba2 = new RefractionObject("pumba2", app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	pumba2->set_shader_program(shader_program);
	pumba2->set_scale(glm::vec3(2.0f));
	pumba2->set_pos(glm::vec3(0, 0, -8));
	pumba2->set_rotation_speed(glm::vec3(0, 20, 0));
	pumba2->set_ior(0.8);
	pumba2->set_chromatic_offset(0.0f);
	pumba2->set_refractive_factor(1.0f);
	pumba2->set_mix_power(0.4f);

	RefractionObject * pumba3 = new RefractionObject("pumba3", app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	pumba3->set_shader_program(shader_program);
	pumba3->set_scale(glm::vec3(2.0f));
	pumba3->set_pos(glm::vec3(0, 0, 0));
	pumba3->set_rotation_speed(glm::vec3(0, 20, 0));
	pumba3->set_refractive_factor(0.0f);
	pumba3->set_mix_power(0.4f);

	RefractionObject * pumba4 = new RefractionObject("pumba4", app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	pumba4->set_shader_program(shader_program);
	pumba4->set_scale(glm::vec3(2.0f));
	pumba4->set_pos(glm::vec3(0, 0, 8));
	pumba4->set_rotation_speed(glm::vec3(0, 20, 0));
	pumba4->set_ior(0.9);
	pumba4->set_chromatic_offset(0.05f);
	pumba4->set_refractive_factor(1.0f);
	pumba4->set_mix_power(0.4f);
	
	RefractionObject * pumba5 = new RefractionObject("pumba5", app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	pumba5->set_shader_program(shader_program); 
	pumba5->set_scale(glm::vec3(2.0f));
	pumba5->set_pos(glm::vec3(0, 0, 16));
	pumba5->set_rotation_speed(glm::vec3(0, 20, 0));
	pumba5->set_ior(0.85f);
	pumba5->set_chromatic_offset(0.0f);
	pumba5->set_mix_power(0.1f);
	pumba5->set_fresnel(true);
	pumba5->set_refractive_power(2);

	RefractionObject * pumba6 = new RefractionObject("pumba6", app, pumba_model, glm::vec3(0.90f, 0.29f, 0.23f));
	pumba6->set_shader_program(shader_program); 
	pumba6->set_scale(glm::vec3(2.0f));
	pumba6->set_pos(glm::vec3(0, 0, 24));
	pumba6->set_rotation_speed(glm::vec3(0, 20, 0));
	pumba6->set_ior(0.85f);
	pumba6->set_chromatic_offset(0.05f);
	pumba6->set_mix_power(0.1f);
	pumba6->set_fresnel(true);
	pumba6->set_refractive_power(10);

	std::vector<GameObject*> objects = { pumba1, pumba2, pumba3, pumba4, pumba5, pumba6 };

	/* Lights */
	LampShader* shader_program_lamp = LampShader::create();
	DirLight* d_light = new DirLight(app, glm::vec3(1.0f, -1.0f, -0.0f), glm::vec3(1.0f));
	d_light->set_shader_program(shader_program_lamp);

	/* CubeMap */
	BasicShader* cube_map_shader = BasicShader::create("shaders/cube_vertex_shader.glsl", "shaders/cube_fragment_shader.glsl");

	CubeMap* cube_map = new CubeMap(1000, "cube_map/second/back.jpg", "cube_map/second/front.jpg", "cube_map/second/top.jpg", "cube_map/second/bot.jpg", "cube_map/second/left.jpg", "cube_map/second/right.jpg");
	cube_map->init(cube_map_shader);

	pumba1->set_environment_map_id(cube_map->get_cube_map_texture());
	pumba2->set_environment_map_id(cube_map->get_cube_map_texture());
	pumba3->set_environment_map_id(cube_map->get_cube_map_texture());
	pumba4->set_environment_map_id(cube_map->get_cube_map_texture());
	pumba5->set_environment_map_id(cube_map->get_cube_map_texture());
	pumba6->set_environment_map_id(cube_map->get_cube_map_texture());

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