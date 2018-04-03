#pragma once
#include "En.h"

#include "Window.h"
#include "game_objects\GameObject.h"
#include "game_objects\lights\DirLight.h"
#include "game_objects\lights\PointLight.h"
#include "game_objects\cube_map\CubeMap.h"
#include "game_objects\particle\ParticleMaster.h"
#include "camera\Camera.h"
#include "util\mesh\Mesh.h"
#include "util\gui\GuiRenderer.h"
#include "util\input\InputManager.h"
#include "util\framebuffer\FrameBuffer.h"

class Application {
public:
	Application(Camera* camera);
	~Application();
	
	int init();
	void runMainGameLoop();
	void update();
	void render();
	void bindAsRenderTarget();
	double calculate_delta_time();

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
		auto it = std::find_if(game_objects.begin(), game_objects.end(), [name](GameObject* g) { return  g->get_name() == name; });
		return dynamic_cast<T*>(*it);
	};

	void key_callback(int key, int scancode, int action, int mode);
	void scroll_callback(double x_offset, double y_offset);
	void mouse_callback(double x_pos, double y_pos);
	void resize_callback(int width, int height);

	/* Setters */
	void set_game_objects(std::vector<GameObject*> game_objects);
	void set_frame_buffers(std::vector<FrameBuffer*> frame_buffers);
	void set_gui_renderer(GuiRenderer* gui_renderer);
	void set_directional_light(DirLight* dir_light);
	void set_point_lights(std::vector<PointLight*> point_lights);
	void set_shaders(std::vector<ShaderProgram*> shaders);
	void set_input_manager(InputManager* input_manager);
	void set_cube_map(CubeMap* cube_map);
	void set_debug(bool debug);

	void update_lights();
	void check_shaders();
	bool is_debug();

	std::vector<FrameBuffer*> frame_buffers;
	ParticleMaster * particle_master;
	ShaderProgram* basic_normal_shader;
	ShaderProgram* basic_depth_shader;
	ShaderProgram* basic_normal_shader_no_alpha;

	double delta_time;

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

	double lastFrame = 0.0f;
	bool debug = false;

	std::thread* shader_check_thread;
	bool stop_thread;
};
