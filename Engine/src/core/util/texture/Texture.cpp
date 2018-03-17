#include "Texture.h"

#include <std_image\stb_image.h>

#include "..\Logger.h"

Texture::Texture(const std::string & file_name, GLenum texture_target, int num_of_textures) : texture_target(texture_target), file_name(file_name), num_of_textures(num_of_textures) {
	//LOG_MESSAGE("Importing: " + file_name);
	this->texture_id = new GLuint[num_of_textures];
	this->load();
}

Texture::Texture(Texture & texture) : texture_target(texture.texture_target), file_name(texture.file_name), num_of_textures(texture.num_of_textures) {
	this->texture_id = new GLuint[texture.num_of_textures];
	texture_id = texture.get_texture_id();
}

GLint Texture::load() {
	unsigned char* image_data = stbi_load(file_name.c_str(), &width, &height, &num_of_components, STBI_rgb_alpha);

	if (image_data == nullptr) { std::cout << "Texture loading failed: " << file_name.c_str() << std::endl; return -1; };

	glGenTextures(num_of_textures, texture_id);
	for (int i = 0; i < num_of_textures; i++) {
		glBindTexture(texture_target, texture_id[i]);

		if (num_of_textures == 1) {
			glTexParameterf(texture_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(texture_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		else {
			glTexParameterf(texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			glTexParameterf(texture_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		glTexImage2D(texture_target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

		glGenerateMipmap(texture_target);
		GLfloat maxAnisotropy;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
		glTexParameterf(texture_target, GL_TEXTURE_MAX_ANISOTROPY_EXT, std::clamp(0.0f, 8.0f, maxAnisotropy));


		glTexImage2D(texture_target, i, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

		this->unbind();
	}
	stbi_image_free(image_data);
	return 1;
}

GLuint* Texture::get_texture_id() {
	return this->texture_id;
}

void Texture::bind(int texture_unit, unsigned texture_num) const {
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(texture_target, texture_id[texture_num]);
}

void Texture::unbind() {
	glBindTexture(texture_target, 0);
	glDisable(texture_target);
}
int Texture::get_unit() {
	return this->unit;
}
void Texture::set_texture_type(TextureType texture_type) {
	this->texture_type = texture_type;
}
std::string Texture::get_file_name() {
	return this->file_name;
}

Texture::~Texture() {
	if (*texture_id) glDeleteTextures(num_of_textures, texture_id);
	delete texture_id;
}

int Texture::get_width() {
	return this->width;
}

int Texture::get_height() {
	return this->height;
}
