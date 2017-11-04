#pragma once
#include <GLFW/glfw3.h>

class Application {
public:
	Application();
	~Application();

	int init();
	void runMainGameLoop();

private:
	GLFWwindow* window = 0;
};

