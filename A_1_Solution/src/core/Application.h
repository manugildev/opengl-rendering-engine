#pragma once

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include "Window.h"
#include "game_objects\GameObject.h"
#include "camera\Camera.h"

class Application {
public:
	Application(Camera* camera);
	~Application();

	float calculate_delta_time();

	int init();
	void runMainGameLoop(GameObject * objects[], int lenght);
	int window_width, window_height;

	void do_movement();

	Camera* get_camera();
	Window* get_window();

	void key_callback(int key, int scancode, int action, int mode); 
	void scroll_callback(double x_offset, double y_offset); 
	void mouse_callback(double x_pos, double y_pos);

private:
	Window* window;
	Camera* camera;

	bool keys[1024];
	bool first_mouse = true;

	float delta_time;
	float lastFrame = 0.0f;
	float last_x = 0, last_y = 0;
	float x_offset = 0, y_offset = 0;
	
};
