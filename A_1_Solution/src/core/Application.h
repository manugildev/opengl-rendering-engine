#pragma once

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include "game_objects\GameObject.h"

class Application {
public:
	Application();
	~Application();

	void _update_fps_counter(GLFWwindow* window);

	int init();
	void runMainGameLoop(GameObject * objects[], int lenght);
	int window_width, window_height;


private:
	GLFWwindow* window = 0;
	double previous_seconds;
	int frame_count;
};
