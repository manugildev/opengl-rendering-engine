#include "Engine.h"

#include "input\Input.h"
#include "game_objects\GoochObject.h"

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
	Model* car_model = new Model("models/volks.obj");

	/* GameObjects */
	GoochShader* shader_program = GoochShader::create();

	GoochObject * car1 = new GoochObject("car1", app, car_model, glm::vec3(0.90f, 0.29f, 0.23f));
	car1->set_shader_program(shader_program);
	car1->set_rotation_speed(glm::vec3(0, 0, 0));
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

	FrameBuffer* frame_buffer = new FrameBuffer(app);

	GuiShader* depth_shader_program = GuiShader::create("shaders/gui_vertex_shader.glsl", "shaders/gui_edge_fragment_shader.glsl");
	GuiTexture* frame_buffer_texture = new GuiTexture(app, depth_shader_program, frame_buffer->get_texture());
	
	float scale = 960.0f / 540.0f;
	
	frame_buffer_texture->set_scale(glm::vec2(scale, -1.0f));
	frame_buffer_texture->set_position(glm::vec2(0.0f, -0.0f));
	gui_renderer->add_gui_texture(frame_buffer_texture);

	std::vector<ShaderProgram*> shaders = { shader_program, shader_program_lamp, cube_map_shader, gui_renderer->get_shader_program(), depth_shader_program, app->basic_normal_shader};
	
	/* Setting up the Application */
	app->set_cube_map(cube_map);
	app->set_gui_renderer(gui_renderer);
	app->set_shaders(shaders);
	app->set_input_manager(input_manager);
	app->set_game_objects(objects);
	app->set_frame_buffer(frame_buffer);

	/* Run the loop */
	app->runMainGameLoop();
}