#include "Engine.h"

#include "input\Input.h"
#include "game_objects\GoochObject.h"
#include "shaders\GoochShader.h"

int main(void) {

	/* Camera */
	Camera camera(glm::vec3(0.0f, 7.0f, 10.0f));

	/* Application */
	Application *app = new Application(&camera);

	/* Lights */
	LampShader* shader_program_lamp = LampShader::create();
	DirLight* d_light = new DirLight(app, glm::vec3(1.0f, -1.0f, -0.0f), glm::vec3(1.0f));
	d_light->set_shader_program(shader_program_lamp);
	app->set_directional_light(d_light);

	/* InputManager */
	InputManager* input_manager = new Input(app);

	/* Models */
	Model* floor_no_mipmap = new Model("models/floor.obj", 1);
	Model* car_model = new Model("models/teapot.obj");

	/* GameObjects */
	GoochShader* shader_program = GoochShader::create();

	GameObject * floor1 = new GameObject("floor1", app, floor_no_mipmap, glm::vec3(0.90f, 0.29f, 0.23f));
	floor1->set_shader_program(shader_program);
	floor1->set_pos(glm::vec3(0, 0, 0));
	floor1->set_scale(glm::vec3(5.0f));
	floor1->set_specular_strength(0);
	floor1->set_specular_power(1);
	floor1->set_mix_power(0.5);

	GoochObject * car1 = new GoochObject("car1", app, car_model, glm::vec3(0.90f, 0.29f, 0.23f));
	car1->set_shader_program(shader_program);
	car1->set_rotation_speed(glm::vec3(0, 30, 0));
	car1->set_pos(glm::vec3(0, 0, 0));
	car1->set_scale(glm::vec3(1.0f));
	car1->set_specular_strength(0);
	car1->set_specular_power(1);

	std::vector<GameObject*> objects = { car1 };
	
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
	app->set_cube_map(cube_map);
	app->set_gui_renderer(gui_renderer);
	app->set_shaders(shaders);
	app->set_input_manager(input_manager);

	/* Run the loop */
	app->runMainGameLoop();
}