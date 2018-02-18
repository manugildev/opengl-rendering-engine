#pragma once

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

#include "Window.h"
#include "game_objects\GameObject.h"
#include "camera\Camera.h"
#include "util\mesh\Mesh.h"
#include "util\gui\GuiRenderer.h"
#include "game_objects\lights\DirLight.h"
#include "game_objects\lights\PointLight.h"
#include "game_objects\cube_map\CubeMap.h"
#include "util\framebuffer\FrameBuffer.h"
#include "util\input\InputManager.h"
#include "game_objects\particle\ParticleMaster.h"

class Application {
public:
	Application(Camera* camera);
	~Application();
	
	int init();
	void runMainGameLoop();
	void update();
	void render();
	void bindAsRenderTarget();
	float calculate_delta_time();

	/* Getters */
	Camera* get_camera();
	Window* get_window();
	std::vector<GameObject*> get_game_objects();
	std::vector<PointLight*> get_point_lights();
	DirLight* get_dir_light();
	bool get_debug();
	GuiRenderer* get_gui_renderer();

	//TODO: Why this function is in here? This function si a Template function that should be somewhere else!!
	template<typename T>
	T* get_component(std::string name) {
		auto it = std::find_if(game_objects.begin(), game_objects.end(), [name](T* g) { return  g->get_name() == name; });
		return *it;
	};

	void key_callback(int key, int scancode, int action, int mode);
	void scroll_callback(double x_offset, double y_offset);
	void mouse_callback(double x_pos, double y_pos);
	void resize_callback(int width, int height);

	/* Setters */
	void set_game_objects(std::vector<GameObject*> game_objects); 
	void set_gui_renderer(GuiRenderer* gui_renderer);
	void set_directional_light(DirLight* dir_light);
	void set_point_lights(std::vector<PointLight*> point_lights);
	void set_shaders(std::vector<ShaderProgram*> shaders);
	void set_input_manager(InputManager* input_manager);
	void set_cube_map(CubeMap* cube_map);
	void set_frame_buffer(FrameBuffer* frame_buffer);
	void set_debug(bool debug);

	void update_lights();
	void check_shaders();
	bool is_debug();

	FrameBuffer* frame_buffer;
	float delta_time;

	ParticleMaster * particle_master;
	ParticleSystem* system;

private:
	Window * window;
	InputManager * input_manager;
	Camera* camera;
	CubeMap* cube_map;
	std::vector<GameObject*> game_objects;
	std::vector<PointLight*> point_lights;
	std::vector<ShaderProgram*> shaders;
	GuiRenderer* gui_renderer;
	DirLight* dir_light;

	float lastFrame = 0.0f;
	bool debug = false;

};
