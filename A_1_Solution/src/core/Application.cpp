#include "Application.h"
#include "util\Logger.h"

#include <iostream>


Application::Application(Camera* camera) : camera(camera) {
	init();
}

int Application::init() {

	/* Initialize the library */
	if (!glfwInit()) { LOG_MESSAGE("GLFW not initialized."); return -1; }

	/* Create a windowed mode window and its OpenGL context */
	// TODO: Move window to another class? new Window(height, width, fullscreen, title, some more data)
	window = glfwCreateWindow(960, 540, "A_1", NULL, NULL);
	glfwGetWindowSize(window, &window_width, &window_height);
	get_camera()->set_aspect_ratio((float) window_width / (float) window_height);
	last_x = window_width / 2.0f;
	last_y = window_height / 2.0f;

	LOG_MESSAGE("Creating window");
	if (!window) {
		LOG_MESSAGE("Window not created.");
		glfwTerminate();
		return -1;
	}


	/* Make the window's context current */
	glfwSetWindowUserPointer(window, this);
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	glewInit();
	glfwWindowHint(GLFW_SAMPLES, 16);

	/* Get GL version information */
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	char tmp[150];
	sprintf_s(tmp, "Renderer: %s - OpenGL Version: %s", renderer, version);
	LOG_MESSAGE(tmp);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Set viewport to windows size */
	glViewport(0, 0, window_width, window_height);
	return 1;
}


void Application::runMainGameLoop(GameObject* objects[], int length) {
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

		calculate_delta_time();

		/* Poll for and process events */
		glfwPollEvents();
		do_movement();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

		for (int i = 0; i < length; i++) objects[i]->update();
		for (int i = 0; i < length; i++) objects[i]->render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

	}
}

void Application::calculate_delta_time() {
	GLfloat currentFrame = glfwGetTime();
	delta_time = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void Application::window_size_callback(GLFWwindow * window, int width, int height) {
	Application* app = reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
	glfwGetWindowSize(window, &app->window_width, &app->window_height);
	glViewport(0, 0, app->window_width, app->window_height);
	app->get_camera()->set_aspect_ratio((float) width / (float) height);

	char temp[128];
	sprintf_s(temp, "Window resize: %dx%d", width, height);
	LOG_MESSAGE(temp);
}

#pragma region INPUT_CALLBACKS
void Application::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode) {
	Application* app = reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) app->keys[key] = true;
		else if (action == GLFW_RELEASE) app->keys[key] = false;
	}
}

void Application::scroll_callback(GLFWwindow * window, double x_offset, double y_offset) {
	Application* app = reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
	app->get_camera()->process_mouse_scroll(y_offset);
}

void Application::mouse_callback(GLFWwindow * window, double x_pos, double y_pos) {
	Application* app = reinterpret_cast<Application *>(glfwGetWindowUserPointer(window));
	if (app->first_mouse) {
		app->last_x = x_pos;
		app->last_y = y_pos;
		app->first_mouse = false;
	}

	app->x_offset = x_pos - app->last_x;
	app->y_offset = app->last_y - y_pos;

	app->last_x = x_pos;
	app->last_y = y_pos;

	app->get_camera()->process_mouse(app->x_offset, app->y_offset);
}
#pragma endregion

void Application::do_movement() {
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) this->camera->process_keyboard(FORWARD, delta_time);
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) this->camera->process_keyboard(BACKWARD, delta_time);
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])this->camera->process_keyboard(LEFT, delta_time);
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) this->camera->process_keyboard(RIGHT, delta_time);
}

Camera* Application::get_camera() {
	return this->camera;
}

Application::~Application() {
	glfwDestroyWindow(window);
	glfwTerminate();
}
