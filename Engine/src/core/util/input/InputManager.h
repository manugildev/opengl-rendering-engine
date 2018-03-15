#pragma once

class Application;

class InputManager {
public:
	InputManager(Application* app);
	~InputManager();

	virtual void key_callback(int key, int scancode, int action, int mode);
	virtual void scroll_callback(double x_offset, double y_offset);
	virtual void mouse_callback(double x_pos, double y_pos);

protected:
	Application * app;

	bool keys[1024];
	bool first_mouse = true;

	float lastFrame = 0.0f;
	double last_x = 0, last_y = 0;
	double x_offset = 0, y_offset = 0;
};

