#pragma once
#include "En.h"

class Application;

class Window {
public:
	Window(Application* app, int width, int height, std::string title);
	~Window();

	GLFWwindow *window_obj = nullptr;

	int get_width();
	int get_height();
	float get_aspect_ratio();
	void set_full_screen(bool fullscreen);
	bool get_full_screen();
	void set_aspect_ratio(float aspect_ratio);

private:
	Application* app;

	int window_width;
	int window_height;
	float aspect_ratio;
	bool full_screen = false;

	static void window_size_callback(GLFWwindow * window, int width, int height);
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static void scroll_callback(GLFWwindow *window, double x_offset, double y_offset);
	static void mouse_callback(GLFWwindow *window, double x_pos, double y_pos);
};

