#pragma once
#include "GuiTexture.h"
#include "..\shaders\gui\GuiShader.h"

class Application;

class GuiRenderer {
public:
	GuiRenderer();
	~GuiRenderer();

	void update(double delta_time);
	void render();
	void update_window_size();

	void add_gui_texture(GuiTexture* texture);
	ShaderProgram* get_shader_program();


	std::vector<GuiTexture*> get_textures();


private:
	ShaderProgram* shader_program;
	std::vector<GuiTexture*> textures;

};

