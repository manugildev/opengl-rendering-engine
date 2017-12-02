#include "Texture.h"
#include <assert.h>
#include "..\Logger.h"

#include <std_image\stb_image.h>

Texture::Texture(GLenum texture_target, const std::string & file_name, int num_of_textures) : texture_target(texture_target), file_name(file_name), num_of_textures(num_of_textures) {
	texture_id = new GLuint[num_of_textures];	
}

GLint Texture::load() {
	image_data = stbi_load(file_name.c_str(), &width, &height, &num_of_components, STBI_rgb_alpha);

	if (image_data == nullptr) {
		std::cout << "Texture loading failed: " << file_name.c_str() << std::endl;
	}
	glGenTextures(num_of_textures, texture_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(texture_target, *texture_id);

	glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameterf(texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(texture_target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	glBindTexture(texture_target, 0);

	stbi_image_free(image_data);
	return 1;
}

void Texture::init(unsigned char** data, GLfloat* filter) {
	glGenTextures(num_of_textures, texture_id);
	for (int i = 0; i < num_of_textures; i++) {

		glBindTexture(texture_target, texture_id[i]);

		glTexParameterf(texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(texture_target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	}
}

void Texture::bind(int texture_unit) const {
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(texture_target, *texture_id);
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

void Texture::bindAsRenderTarget() {

}

Texture::~Texture() {
	if (*texture_id) glDeleteTextures(num_of_textures, texture_id);
	if (texture_id) delete texture_id;
}