#include "Application.h"
#include "util\Logger.h"

Application::Application() { init(); }

int Application::init() {

	/* Initialize the library */
	if (!glfwInit()) { LOG_MESSAGE("GLFW not initialized."); return -1; }

	/* Create a windowed mode window and its OpenGL context */
	// TODO: Move window to another class? new Window(height, width, fullscreen, title, some more data)
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	LOG_MESSAGE("Creating window");
	if (!window) {
		LOG_MESSAGE("Window not created.");
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	return 1;
}

void Application::runMainGameLoop() {
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

}

Application::~Application() {
	delete window;
	glfwTerminate();
}
