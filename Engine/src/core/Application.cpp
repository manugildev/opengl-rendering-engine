#include "Application.h"
#include "game_objects/plane/Plane.h"
#include "util\Logger.h"

#include <iostream>
#include "util\texture\Texture.h"
#include <glm\glm.hpp>
#include "util\gui\Quad.h"


Application::Application(Camera* camera) : camera(camera) {
	this->init();
}

int Application::init() {

	/* Initialize the library */
	if (!glfwInit()) { LOG_MESSAGE("GLFW not initialized."); return -1; }
	/* Create a windowed mode window and its OpenGL context */
	window = new Window(this, 960, 540, "A_1");

	get_camera()->set_aspect_ratio(window->get_aspect_ratio());

	glewExperimental = GL_TRUE;
	glewInit();

	/* Get GL version information */
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	char tmp[150];
	sprintf_s(tmp, "Renderer: %s - OpenGL Version: %s", renderer, version);
	LOG_MESSAGE(tmp);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Set viewport to windows size */
	glViewport(0, 0, window->get_width(), window->get_height());

	// TODO: Temporal Particle Master

	particle_master = new ParticleMaster(camera->get_persp_proj_matrix());

	return 1;
}

// TODO: Abstract this to run it outside
void Application::runMainGameLoop() {
	while (!glfwWindowShouldClose(window->window_obj) && glfwGetKey(window->window_obj, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		this->check_shaders();

		/* Update */
		this->update();

		/* Render */
		if (this->frame_buffer) {
			this->frame_buffer->bind();
			glViewport(0, 0, window->get_width(), window->get_height());
			//this->render();
			this->frame_buffer->unbind();
		}

		glViewport(0, 0, window->get_width(), window->get_height());
		this->render();
		this->gui_renderer->render();

		/* Start second viewport */
		//glViewport(0, window->get_height() - window->get_width() / 4, window->get_width() / 4, window->get_width() / 4);

		/* Update Camera for second viewport */
		//this->camera->update_view_matrix_second_viewport(glm::vec3(0.0f, -1.0f, 0.0f));
		//this->camera->set_persp_proj_matrix(glm::ortho(-window->get_width() / 50.f, window->get_width() / 50.0f, -window->get_width() /50.0f, window->get_width() / 50.0f, 0.1f, 10000.f));

		/* Render second viewport */
		//for (int i = 0; i < game_objects.size(); i++) game_objects[i]->render();
		//for (int i = 0; i < point_lights.size(); i++) point_lights[i]->render();
		//this->dir_light->render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window->window_obj);
	}
}

// TODO: Abstract this to run it outside
void Application::update() {
	this->delta_time = calculate_delta_time();
	this->particle_master->update(delta_time);

	/* Poll for and process events */
	glfwPollEvents();
	for (int i = 0; i < game_objects.size(); i++) game_objects[i]->update(delta_time);

	/* Updating the camera aftwerwards because of the FPV*/
	this->camera->update(delta_time);
	this->camera->update_view_matrix();
	this->camera->set_persp_proj_matrix(glm::perspective(glm::radians(camera->get_field_of_view()), camera->get_aspect_ratio(), 0.1f, 10000.0f));

	for (int i = 0; i < point_lights.size(); i++) point_lights[i]->update(delta_time);
	this->dir_light->update(delta_time);
}

// TODO: Abstract this to run it outside
void Application::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	cube_map->render(camera->get_view_matrix(), camera->get_persp_proj_matrix());
	for (int i = 0; i < game_objects.size(); i++) game_objects[i]->render();
	for (int i = 0; i < point_lights.size(); i++) point_lights[i]->render();
	dir_light->render();
	this->particle_master->render(camera);
}

//TODO: This is probably need to be in the window thing
void Application::bindAsRenderTarget() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glViewport(0, 0, window->get_width(), window->get_height());
}

void Application::update_lights() {
	for (int i = 0; i < game_objects.size(); i++) game_objects[i]->update_lights();
}

float Application::calculate_delta_time() {
	float currentFrame = glfwGetTime();
	delta_time = currentFrame - lastFrame;
	lastFrame = currentFrame;
	return delta_time;
}


#pragma region INPUT_FUNCTIONS
void Application::key_callback(int key, int scancode, int action, int mode) {
	if (this->input_manager) this->input_manager->key_callback(key, scancode, action, mode);
}

void Application::resize_callback(int width, int height) {
	if (frame_buffer) frame_buffer->resize();
	if (gui_renderer) gui_renderer->update_window_size();
}

void Application::scroll_callback(double x_offset, double y_offset) {
	if (this->input_manager) this->input_manager->scroll_callback(x_offset, y_offset);
	camera->process_mouse_scroll(y_offset);
}

void Application::mouse_callback(double x_pos, double y_pos) {
	if (this->input_manager) this->input_manager->mouse_callback(x_pos, y_pos);
}
#pragma endregion

void Application::check_shaders() {
	for (int i = 0; i < shaders.size(); i++) {
		shaders[i]->check_if_modified();
	}
}

void Application::set_game_objects(std::vector<GameObject*> game_objects) {
	this->game_objects = game_objects;
}

void Application::set_gui_renderer(GuiRenderer* gui_renderer) {
	this->gui_renderer = gui_renderer;
}

void Application::set_directional_light(DirLight* dir_light) {
	this->dir_light = dir_light;
}
void Application::set_point_lights(std::vector<PointLight*> point_lights) {
	this->point_lights = point_lights;
	this->update_lights();
}

void Application::set_shaders(std::vector<ShaderProgram*> shaders) {
	this->shaders = shaders;
}

void Application::set_input_manager(InputManager * input_manager) {
	this->input_manager = input_manager;
}

std::vector<GameObject*> Application::get_game_objects() {
	return this->game_objects;
}

DirLight* Application::get_dir_light() {
	return this->dir_light;
}

bool Application::get_debug() {
	return debug;
}

GuiRenderer * Application::get_gui_renderer() {
	return this->gui_renderer;
}

std::vector<PointLight*> Application::get_point_lights() {
	return this->point_lights;
}

void Application::set_cube_map(CubeMap * cube_map) {
	this->cube_map = cube_map;
}

void Application::set_frame_buffer(FrameBuffer* frame_buffer) {
	this->frame_buffer = frame_buffer;
}

void Application::set_debug(bool debug) {
	this->debug = debug;
}

Camera* Application::get_camera() {
	return this->camera;
}

Window* Application::get_window() {
	return this->window;
}
bool Application::is_debug() {
	return this->debug;
}

Application::~Application() {
	delete window;
	for (int i = 0; i < game_objects.size(); i++) { delete game_objects[i]; game_objects[i] = NULL; }
	for (int i = 0; i < point_lights.size(); i++) { delete point_lights[i]; point_lights[i] = NULL; }
	window = NULL;
	glfwTerminate();
}