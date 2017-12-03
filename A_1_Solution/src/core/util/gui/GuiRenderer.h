#pragma once
#include <vector>
#include "GuiTexture.h"
#include "..\shaders\gui\GuiShader.h"

class GuiRenderer {
public:
	GuiRenderer();
	~GuiRenderer();

	void update();
	void render();
	void add_gui_texture(GuiTexture* texture);
	GuiShader* get_shader_program();


private:
	GuiShader* shader_program;
	std::vector<GuiTexture*> textures;

};

