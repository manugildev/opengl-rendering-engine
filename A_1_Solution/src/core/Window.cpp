#include "Window.h"

#include "util\Logger.h"
#include "Application.h"

Window::Window(Application* app, int width, int height, std::string title) {
	this->app = app;

	glfwWindowHint(GLFW_SAMPLES, 16);
		
	// Move window to the upper left corner.
	window_obj = glfwCreateWindow(940, 540, "A_1", NULL, NULL);

	/* Activate this for FullScreen */
	//GLFWmonitor* primary = glfwGetPrimaryMonitor();
	//const GLFWvidmode* mode = glfwGetVideoMode(primary);
	//glfwSetWindowSize(window_obj, mode->width, mode->height);

	LOG_MESSAGE("Creating window");
	if (!window_obj) {
		LOG_MESSAGE("Window not created.");
		glfwTerminate();
	}

	glfwSetWindowUserPointer(window_obj, this);
	glfwGetWindowSize(window_obj, &this->window_width, &this->window_height);
	glfwSetCursorPos(window_obj, window_width / 2, window_height / 2);
	glfwSetWindowSizeCallback(window_obj, window_size_callback);
	glfwSetInputMode(window_obj, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetWindowPos(window_obj, 400, 300);
	glfwSetWindowAspectRatio(window_obj, 16, 9);

	glfwMakeContextCurrent(window_obj);
	glfwSetKeyCallback(window_obj, key_callback);
	glfwSetCursorPosCallback(window_obj, mouse_callback);
	glfwSetScrollCallback(window_obj, scroll_callback);
}

#pragma region CALLBACK_FUNCTIONS
void Window::window_size_callback(GLFWwindow * window, int width, int height) {
	Window* w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
	glfwGetWindowSize(window, &w->window_width, &w->window_height);
	glViewport(0, 0, w->window_width, w->window_height);
	w->app->get_camera()->set_aspect_ratio((float) width / (float) height);

	char temp[128];
	sprintf_s(temp, "Window resize: %dx%d", width, height);
	LOG_MESSAGE(temp);

}

void Window::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode) {
	Window* w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
	w->app->key_callback(key, scancode, action, mode);
}

void Window::scroll_callback(GLFWwindow * window, double x_offset, double y_offset) {
	Window* w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
	w->app->scroll_callback(x_offset, y_offset);
}

void Window::mouse_callback(GLFWwindow * window, double x_pos, double y_pos) {
	Window* w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
	w->app->mouse_callback(x_pos, y_pos);
}

#pragma endregion 

int Window::get_width() {
	return this->window_width;
}

int Window::get_height() {
	return this->window_height;
}

float Window::get_aspect_ratio() {
	return (float) this->window_width / (float) this->window_height;
}

Window::~Window() {
	glfwDestroyWindow(window_obj);
	delete window_obj;
	window_obj = NULL;
}