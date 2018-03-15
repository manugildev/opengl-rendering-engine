#include "Engine.h"
#include "game_objects\car\Car.h"
#include "input\Input.h"

int main(void) {
	/* Camera */
	Camera camera(glm::vec3(0.0f, 7.0f, 10.0f));

	/* Application */
	Application *app = new Application(&camera);

	/* Input Manager */
	InputManager* input_manager = new Input(app);

	/* Models */
	Model* city_model = new Model("models/street/street.obj");
	Model* car_model = new Model("models/volks.obj");

	/* GameObjects */
	LightingShader* shader_program = LightingShader::create();
	GameObject *city = new GameObject("city", app, city_model, glm::vec3(1.0f));
	city->set_scale(glm::vec3(1.0f));
	city->set_rotation_speed(glm::vec3(0.0f, 0.0f, 0.0f));
	city->set_pos(glm::vec3(0.0f, 0.0f, 0.0f));
	city->set_shader_program(shader_program);

	Car *car1 = new Car("car1", app, car_model, glm::vec3(0.18f, 0.80f, 0.44f));
	car1->set_parent(city);
	car1->set_initial_pos(glm::vec3(0.0f, 1.0f, -10.0f));
	car1->set_rotation(glm::vec3(0.0f, 270.0f, 0.0f));
	car1->set_shader_program(shader_program);
	car1->set_acceleration(glm::vec3(Util::random_range(3.0f, 7.0f), 0.0f, 0.0f));

	Car *car5 = new Car("car5", app, car_model, glm::vec3(0.20f, 0.59f, 0.84f));
	car5->set_parent(city);
	car5->set_initial_pos(glm::vec3(0.0f, 1.0f, -5.0f));
	car5->set_rotation(glm::vec3(0.0f, 270.0f, 0.0f));
	car5->set_shader_program(shader_program);
	car5->set_acceleration(glm::vec3(Util::random_range(3.0f, 7.0f), 0.0f, 0.0f));

	Car *car2 = new Car("car2", app, car_model, glm::vec3(0.90f, 0.29f, 0.23f));
	car2->set_parent(city);
	car2->set_initial_pos(glm::vec3(0.0f, 1.0f, 0.0f));
	car2->set_rotation(glm::vec3(0.0f, -270.0f, 0.0f));
	car2->set_shader_program(shader_program);
	car2->set_acceleration(glm::vec3(-Util::random_range(3.0f, 7.0f), 0.0f, 0.0f));

	Car *car6 = new Car("car6", app, car_model, glm::vec3(0.94f, 0.76f, 0.05f));
	car6->set_parent(city);
	car6->set_initial_pos(glm::vec3(0.0f, 1.0f, 5.0f));
	car6->set_rotation(glm::vec3(0.0f, -270.0f, 0.0f));
	car6->set_shader_program(shader_program);
	car6->set_acceleration(glm::vec3(-Util::random_range(3.0f, 7.0f), 0.0f, 0.0f));

	Car *car3 = new Car("car3", app, car_model, glm::vec3(0.10f, 0.73f, 0.61f));
	car3->set_parent(city);
	car3->set_initial_pos(glm::vec3(0.0f, 1.0f, 0.0f));
	car3->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
	car3->set_shader_program(shader_program);
	car3->set_acceleration(glm::vec3(0.0f, 0.0f, -Util::random_range(3.0f, 7.0f)));

	Car *car7 = new Car("car7", app, car_model, glm::vec3(0.6f, 0.34f, 0.71f));
	car7->set_parent(city);
	car7->set_initial_pos(glm::vec3(5.0f, 1.0f, 0.0f));
	car7->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
	car7->set_shader_program(shader_program);
	car7->set_acceleration(glm::vec3(0.0f, 0.0f, -Util::random_range(3.0f, 7.0f)));

	Car *car4 = new Car("car4", app, car_model, glm::vec3(0.9f, 0.49f, 0.13f));
	car4->set_parent(city);
	car4->set_initial_pos(glm::vec3(-5.0f, 1.0f, 0.0f));
	car4->set_rotation(glm::vec3(0.0f, -180.0f, 0.0f));
	car4->set_shader_program(shader_program);
	car4->set_acceleration(glm::vec3(0.0f, 0.0f, Util::random_range(3.0f, 7.0f)));

	Car *car8 = new Car("car8", app, car_model, glm::vec3(0.97f, 0.42f, 0.56f));
	car8->set_parent(city);
	car8->set_initial_pos(glm::vec3(-10.0f, 1.0f, 0.0f));
	car8->set_rotation(glm::vec3(0.0f, -180.0f, 0.0f));
	car8->set_shader_program(shader_program);
	car8->set_acceleration(glm::vec3(0.0f, 0.0f, Util::random_range(3.0f, 7.0f)));

	std::vector<GameObject*> objects = { city, car1, car2, car3, car4, car5, car6, car7, car8 };

	/* Lights */
	LampShader* shader_program1 = LampShader::create();
	PointLight* p_light_1 = new PointLight(app, glm::vec3(40.0f, 2.0f, 8.0f), glm::vec3(1.0f, 0.0f, 1.0f), .3f, 0.8f, 0.1f);
	PointLight* p_light_2 = new PointLight(app, glm::vec3(-40.0f, 2.0f, -13.0f), glm::vec3(1.0f, 1.0f, 0.0f), .3f, 0.8f, 0.1f);
	PointLight* p_light_3 = new PointLight(app, glm::vec3(8.0f, 2.0f, -40.0f), glm::vec3(1.0f, .0f, 0.0f), .3f, 0.8f, 0.1f);
	PointLight* p_light_4 = new PointLight(app, glm::vec3(-13.0f, 2.0f, 40.0f), glm::vec3(0.0f, 1.0f, 0.0f), .3f, 0.8f, 0.1f);
	PointLight* p_light_5 = new PointLight(app, glm::vec3(40.0f, 2.0f, -13.0f), glm::vec3(1.0f, 0.0f, 1.0f), .3f, 0.8f, 0.1f);
	PointLight* p_light_6 = new PointLight(app, glm::vec3(-40.0f, 2.0f, 8.0f), glm::vec3(1.0f, 1.0f, 0.0f), .3f, 0.8f, 0.1f);

	std::vector<PointLight*> point_lights = { p_light_1, p_light_2, p_light_3, p_light_4, p_light_5, p_light_6 };
	for (unsigned int i = 0; i < point_lights.size(); i++) point_lights[i]->set_parent(city);
	for (unsigned int i = 0; i < point_lights.size(); i++) point_lights[i]->set_shader_program(shader_program1);

	DirLight* d_light = new DirLight(app, glm::vec3(1.0f, -1.0f, -0.0f), glm::vec3(1.0f));
	d_light->set_shader_program(shader_program1);

	/* CubeMap */
	BasicShader* cube_map_shader = BasicShader::create("shaders/cube_vertex_shader.glsl", "shaders/cube_fragment_shader.glsl");
	CubeMap* cube_map = new CubeMap();
	cube_map->init(cube_map_shader);

	/* GUI */
	GuiRenderer* gui_renderer = new GuiRenderer();

	GuiTexture* first_gui = new GuiTexture(app, gui_renderer->get_shader_program());
	first_gui->set_scale(glm::vec2(0.2f, 0.2f));
	first_gui->set_position(glm::vec2(0.80f, 0.80f));

	GuiTexture* second_gui = new GuiTexture(app, gui_renderer->get_shader_program(), "textures/logo.png");
	second_gui->set_scale(glm::vec2(0.03f, 0.03f));
	second_gui->set_position(glm::vec2(0.0f, -0.0f));

	//gui_renderer->add_gui_texture(first_gui);
	gui_renderer->add_gui_texture(second_gui);

	std::vector<ShaderProgram*> shaders = { shader_program, shader_program1, cube_map_shader };
		
	/* Setting up the Application */
	app->set_input_manager(input_manager);
	app->set_game_objects(objects);
	app->set_directional_light(d_light);
	app->set_point_lights(point_lights);
	app->set_cube_map(cube_map);
	app->set_gui_renderer(gui_renderer);
	app->set_shaders(shaders);

	/* Run the loop */
	app->runMainGameLoop();
}