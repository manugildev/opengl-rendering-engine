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

	GoochObject * car1 = new GoochObject("car1", app, car_model, glm::vec3(1.0f));
	car1->set_shader_program(shader_program);
	car1->set_rotation_speed(glm::vec3(0, 0, 0));
	car1->set_pos(glm::vec3(0, 0, 0));
	car1->set_scale(glm::vec3(1.0f));
	car1->set_specular_strength(0);
	car1->set_specular_power(1);

	GoochObject * car2 = new GoochObject("car2", app, car_model, glm::vec3(1.0f));
	car2->set_shader_program(shader_program);
	car2->set_rotation_speed(glm::vec3(0, 0, 0));
	car2->set_pos(glm::vec3(0, 0, 0));
	car2->set_scale(glm::vec3(1.0f));
	car2->set_specular_strength(0);
	car2->set_specular_power(1);
	car2->use_phong = true;

	std::vector<GameObject*> objects = { car1, car2 };
	
	/* CubeMap */
	BasicShader* cube_map_shader = BasicShader::create("shaders/cube_vertex_shader.glsl", "shaders/cube_fragment_shader.glsl");

	CubeMap* cube_map = new CubeMap(1000);
	cube_map->init(cube_map_shader);

	/* GUI */
	GuiRenderer* gui_renderer = new GuiRenderer();

	GuiTexture* first_gui = new GuiTexture(app, gui_renderer->get_shader_program(), "textures/logo.png");
	first_gui->set_initial_scale(glm::vec2(0.03f, 0.03f));
	first_gui->set_initial_position(glm::vec2(0.0f, -0.0f));
	gui_renderer->add_gui_texture(first_gui);

	FrameBuffer* frame_buffer1 = new FrameBuffer(app);
	FrameBuffer* frame_buffer2 = new FrameBuffer(app);
	FrameBuffer* frame_buffer3 = new FrameBuffer(app);
	FrameBuffer* frame_buffer4 = new FrameBuffer(app);
	FrameBuffer* frame_buffer5 = new FrameBuffer(app);
	FrameBuffer* frame_buffer6 = new FrameBuffer(app);
	FrameBuffer* frame_buffer7 = new FrameBuffer(app);


	std::vector<FrameBuffer*> frame_buffers = { frame_buffer1, frame_buffer2, frame_buffer3, frame_buffer4, frame_buffer5, frame_buffer6, frame_buffer7 };

	GuiShader* edge_shader_program = GuiShader::create("shaders/gui_vertex_shader.glsl", "shaders/gui_edge_fragment_shader.glsl");
	GuiShader* depth_shader_program = GuiShader::create("shaders/gui_vertex_shader.glsl", "shaders/gui_depth_fragment_shader.glsl");
	GuiShader* color_shader_program = GuiShader::create("shaders/gui_vertex_shader.glsl", "shaders/gui_fragment_shader.glsl");
	GuiShader* edge_color_shader_program = GuiShader::create("shaders/gui_vertex_shader.glsl", "shaders/gui_edge_color_fragment_shader.glsl");

	GuiTexture* frame_buffer1_texture = new GuiTexture(app, edge_shader_program, frame_buffer1->get_texture());
	GuiTexture* frame_buffer2_texture = new GuiTexture(app, depth_shader_program, frame_buffer2->get_texture());
	GuiTexture* frame_buffer3_texture = new GuiTexture(app, color_shader_program, frame_buffer3->get_texture());
	GuiTexture* frame_buffer4_texture = new GuiTexture(app, color_shader_program, frame_buffer4->get_texture());
	GuiTexture* frame_buffer5_texture = new GuiTexture(app, edge_color_shader_program, frame_buffer5->get_texture());
	GuiTexture* frame_buffer6_texture = new GuiTexture(app, color_shader_program, frame_buffer6->get_texture());
	GuiTexture* frame_buffer7_texture = new GuiTexture(app, color_shader_program, frame_buffer7->get_texture());
	
	float scale = 960.0f / 540.0f;
	
	frame_buffer1_texture->set_initial_scale(glm::vec2(scale, -1.0f));
	frame_buffer1_texture->set_initial_position(glm::vec2(0.0f, -0.0f));

	frame_buffer2_texture->set_initial_scale(glm::vec2(scale / 5, -1.0f / 5));
	frame_buffer2_texture->set_initial_position(glm::vec2(-0.79f, -0.80f + (0.01f * scale)));
	
	frame_buffer3_texture->set_initial_scale(glm::vec2(scale / 5, -1.0f / 5));
	frame_buffer3_texture->set_initial_position(glm::vec2(-0.38f, -0.80f + (0.01f * scale)));
	
	frame_buffer4_texture->set_initial_scale(glm::vec2(scale / 5, -1.0f / 5));
	frame_buffer4_texture->set_initial_position(glm::vec2(0.03f, -0.80f + (0.01f * scale)));

	frame_buffer5_texture->set_initial_scale(glm::vec2(scale / 5, -1.0f / 5));
	frame_buffer5_texture->set_initial_position(glm::vec2(0.44f, -0.80f + (0.01f * scale)));

	frame_buffer6_texture->set_initial_scale(glm::vec2(scale / 5, -1.0f / 5));
	frame_buffer6_texture->set_initial_position(glm::vec2(-0.79f, 0.80f - (0.01f * scale)));

	frame_buffer7_texture->set_initial_scale(glm::vec2(scale / 5, -1.0f / 5));
	frame_buffer7_texture->set_initial_position(glm::vec2(-0.38f, 0.80f - (0.01f * scale)));
	
	gui_renderer->add_gui_texture(frame_buffer1_texture);
	gui_renderer->add_gui_texture(frame_buffer2_texture);
	gui_renderer->add_gui_texture(frame_buffer3_texture);
	gui_renderer->add_gui_texture(frame_buffer4_texture);
	gui_renderer->add_gui_texture(frame_buffer5_texture);
	gui_renderer->add_gui_texture(frame_buffer6_texture);
	gui_renderer->add_gui_texture(frame_buffer7_texture);

	std::vector<ShaderProgram*> shaders = { shader_program, shader_program_lamp, cube_map_shader, gui_renderer->get_shader_program(), depth_shader_program,edge_shader_program, edge_color_shader_program,app->basic_normal_shader, app->basic_depth_shader, app->basic_normal_shader_no_alpha };
	
	/* Setting up the Application */
	app->set_cube_map(cube_map);
	app->set_gui_renderer(gui_renderer);
	app->set_shaders(shaders);
	app->set_input_manager(input_manager);
	app->set_game_objects(objects);
	app->set_frame_buffers(frame_buffers);

	/* Run the loop */
	app->runMainGameLoop();
}