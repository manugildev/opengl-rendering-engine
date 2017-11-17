#include "Texture.h"
#include <assert.h>
#include "..\Logger.h"

#include <std_image\stb_image.h>

Texture::Texture(GLenum texture_target, const std::string & file_name) : texture_target(texture_target), file_name(file_name){
	texture_id = load();
}

GLint Texture::load() {
	int width, height, num_of_components;
	unsigned char* image_data = stbi_load(file_name.c_str(), &width, &height, &num_of_components, STBI_rgb_alpha);

	if (image_data == nullptr) {
		std::cout << "Texture loading failed: " << file_name.c_str() << std::endl;
		return -1;
	}
	GLuint id;
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(texture_target, id);

	glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameterf(texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(texture_target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	glBindTexture(texture_target, 0);

	stbi_image_free(image_data);
	return id;
}

void Texture::bind(int texture_unit) {
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(texture_target, texture_id);
}

void Texture::unbind() {
	glBindTexture(texture_target, 0);
	glDisable(texture_target);
}
int Texture::get_unit() {
	return this->unit;
}
std::string Texture::get_file_name() {
	return this->file_name;
}
Texture::~Texture() {
	glDeleteTextures(1, &texture_id);
}
