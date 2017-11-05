#pragma once

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include "game_objects\GameObject.h"
#include "camera\Camera.h"

class Application {
public:
	Application(Camera* camera);
	~Application();

	void calculate_delta_time();

	int init();
	void runMainGameLoop(GameObject * objects[], int lenght);
	int window_width, window_height;

	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
	static void scroll_callback(GLFWwindow *window, double x_offset, double y_offset);
	static void mouse_callback(GLFWwindow *window, double x_pos, double y_pos);
	static void Application::window_size_callback(GLFWwindow * window, int width, int height);

	void do_movement();

	Camera* get_camera();

private:
	GLFWwindow* window = 0;
	Camera* camera;

	bool keys[1024];
	bool first_mouse = true;

	GLfloat delta_time;
	GLfloat lastFrame = 0.0f;
	GLfloat last_x = 0, last_y = 0;
	GLfloat x_offset = 0, y_offset = 0;

};
