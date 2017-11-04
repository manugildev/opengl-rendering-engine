#include "Application.h"
#include "util\Logger.h"

Application::Application() { init(); }

int Application::init() {

	/* Initialize the library */
	if (!glfwInit()) { LOG_MESSAGE("GLFW not initialized."); return -1; }

	/* Create a windowed mode window and its OpenGL context */
	// TODO: Move window to another class? new Window(height, width, fullscreen, title, some more data)
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	glfwGetWindowSize(window, &window_width, &window_height);
	LOG_MESSAGE("Creating window");
	if (!window) {
		LOG_MESSAGE("Window not created.");
		glfwTerminate();
		return -1;
	}

	// TODO: Window Size Callback

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	glfwWindowHint(GLFW_SAMPLES, 4);

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
		_update_fps_counter(window);
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

		for (int i = 0; i < length; i++) objects[i]->update();
		for (int i = 0; i < length; i++) objects[i]->render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}


void Application::_update_fps_counter(GLFWwindow* window) {
	double current_seconds;
	double elapsed_seconds;
	current_seconds = glfwGetTime();
	elapsed_seconds = current_seconds - previous_seconds;

	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		char tmp[128];
		double fps = (double) frame_count / elapsed_seconds;
		sprintf_s(tmp, "opengl @ fps: %.2f", fps);
		glfwSetWindowTitle(window, tmp);
		frame_count = 0;
	}
	frame_count++;
}

Application::~Application() {
	glfwDestroyWindow(window);
	glfwTerminate();
}
