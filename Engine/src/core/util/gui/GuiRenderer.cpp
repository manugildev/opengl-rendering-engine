#include "GuiRenderer.h"

GuiRenderer::GuiRenderer() {
	shader_program = GuiShader::create();
}

void GuiRenderer::update() {}

void GuiRenderer::render() {
	shader_program->start();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < textures.size(); i++) {
		textures[i]->render();
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	shader_program->stop();
}

void GuiRenderer::update_window_size() {
	for (int i = 0; i < textures.size(); i++) textures[i]->update_window_size();
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