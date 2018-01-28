#pragma once
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

class Application;

class Window {
public:
	Window(Application* app, int width, int height, std::string title);
	~Window();

	GLFWwindow *window_obj = 0;

	int get_width();
	int get_height();
	float get_aspect_ratio();

private:
	Application * app;

	int window_width;
	int window_height;

	static void window_size_callback(GLFWwindow * window, int width, int height);
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static void scroll_callback(GLFWwindow *window, double x_offset, double y_offset);
	static void mouse_callback(GLFWwindow *window, double x_pos, double y_pos);
};

