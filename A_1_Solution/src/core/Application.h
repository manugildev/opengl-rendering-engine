#pragma once

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include "Window.h"
#include "game_objects\GameObject.h"
#include "camera\Camera.h"
#include "util\mesh\Mesh.h"
#include "util\gui\GuiRenderer.h"
#include "game_objects\lights\DirLight.h"
#include "game_objects\lights\PointLight.h"
#include "game_objects\cube_map\CubeMap.h"
#include "util\framebuffer\FrameBuffer.h"

#include <vector>


class Application {
public:
	Application(Camera* camera);
	~Application();

	float calculate_delta_time();

	int init();
	void runMainGameLoop();
	void update();
	void render();
	void bindAsRenderTarget();
	int window_width, window_height;

	Camera* get_camera();
	Window* get_window();

	void key_callback(int key, int scancode, int action, int mode); 
	void scroll_callback(double x_offset, double y_offset); 
	void mouse_callback(double x_pos, double y_pos);
	void resize_callback(int width, int height);

	void set_game_objects(std::vector<GameObject*> game_objects);
	void set_gui_renderer(GuiRenderer* gui_renderer);
	void set_directional_light(DirLight* dir_light);
	void set_point_lights(std::vector<PointLight*> point_lights);
	std::vector<GameObject*> get_game_objects();
	DirLight* get_dir_light();
	std::vector<PointLight*> get_point_lights();
	void set_cube_map(CubeMap* cube_map);
	void set_frame_buffer(FrameBuffer* frame_buffer);

	void update_lights();
	void do_movement();
	bool is_debug();

	FrameBuffer* frame_buffer;
private:
	Window* window;
	Camera* camera; 
	CubeMap* cube_map;
	std::vector<GameObject*> game_objects;
	GuiRenderer* gui_renderer;
	std::vector<PointLight*> point_lights;
	DirLight* dir_light;
	
	bool keys[1024];
	bool first_mouse = true;

	float delta_time;
	float lastFrame = 0.0f;
	float last_x = 0, last_y = 0;
	float x_offset = 0, y_offset = 0;
	float debug = false;

			
};
