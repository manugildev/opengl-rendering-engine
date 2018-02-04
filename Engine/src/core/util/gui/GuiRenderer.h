#pragma once
#include <vector>
#include "GuiTexture.h"
#include "..\shaders\gui\GuiShader.h"

class Application;

class GuiRenderer {
public:
	GuiRenderer();
	~GuiRenderer();

	void update();
	void render();
	void update_window_size();
	void add_gui_texture(GuiTexture* texture);
	ShaderProgram* get_shader_program();


private:
	ShaderProgram* shader_program;
	std::vector<GuiTexture*> textures;

};

