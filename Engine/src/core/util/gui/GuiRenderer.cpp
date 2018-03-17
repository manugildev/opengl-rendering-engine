#include "GuiRenderer.h"

GuiRenderer::GuiRenderer() {
	shader_program = GuiShader::create();
}

void GuiRenderer::update() {}

void GuiRenderer::render() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	for (GuiTexture* t : textures) {
		t->render();
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void GuiRenderer::update_window_size() {
	for (GuiTexture* t : textures) t->update_window_size();
}

void GuiRenderer::add_gui_texture(GuiTexture* texture) {
	textures.push_back(texture);
}

ShaderProgram* GuiRenderer::get_shader_program() {
	return shader_program;
}

GuiRenderer::~GuiRenderer() {
	delete shader_program;
}