#pragma once
#include "Engine.h"

class Input : public InputManager {
public:
	Input(Application* app);
	~Input();

	void key_callback(int key, int scancode, int action, int mode) override;
	void scroll_callback(double x_offset, double y_offset) override;
	void mouse_callback(double x_pos, double y_pos) override;

private:
	void process_camera_movement();
};

