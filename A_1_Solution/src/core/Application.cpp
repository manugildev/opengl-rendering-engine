#include "Application.h"
#include "util\Logger.h"


// TODO: MOVE THIS KEYS TO OTHER PLACE
bool keys[1024];
bool first_mouse = true;

GLfloat delta_time;
GLfloat lastFrame = 0.0f;


Application::Application(Camera* camera) : camera(camera) {
	init();
}

int Application::init() {

	/* Initialize the library */
	if (!glfwInit()) { LOG_MESSAGE("GLFW not initialized."); return -1; }

	/* Create a windowed mode window and its OpenGL context */
	// TODO: Move window to another class? new Window(height, width, fullscreen, title, some more data)
	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
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

void Application::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode) {
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) keys[key] = true;
		else if (action == GLFW_RELEASE) keys[key] = false;
	}
}

void Application::scroll_callback(GLFWwindow * window, double x_offset, double y_offset) {}

void Application::mouse_callback(GLFWwindow * window, double x_pos, double y_pos) {}

void Application::do_movement() {
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) this->camera->process_keyboard(FORWARD, delta_time);
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) this->camera->process_keyboard(BACKWARD, delta_time);
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])this->camera->process_keyboard(LEFT, delta_time);
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) this->camera->process_keyboard(RIGHT, delta_time);
}

Camera* Application::get_camera() {
	return this->camera;
}


void Application::calculate_delta_time() {
	GLfloat currentFrame = glfwGetTime();
	delta_time = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

Application::~Application() {
	glfwDestroyWindow(window);
	glfwTerminate();
}
