#include "GuiRenderer.h"

GuiRenderer::GuiRenderer() {
	shader_program = GuiShader::create();
}

void GuiRenderer::update() {}

void GuiRenderer::render() {
	shader_program->start();
	for (int i = 0; i < textures.size(); i++) {
		textures[i]->render();
	}
	shader_program->stop();
}

void GuiRenderer::add_gui_texture(GuiTexture* texture) {
	textures.push_back(texture);
}

GuiShader* GuiRenderer::get_shader_program() {
	return shader_program;
}

GuiRenderer::~GuiRenderer() {
	delete shader_program;
}