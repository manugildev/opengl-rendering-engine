#include "Texture.h"
#include <assert.h>
#include "..\Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <std_image\stb_image.h>

Texture::Texture(const std::string & file_name) {
	if (file_name == "") { is_empty = true; return;}

	int width, height, num_of_components;
	unsigned char* image_data = stbi_load(file_name.c_str(), &width, &height, &num_of_components, STBI_rgb_alpha);

	if (image_data == nullptr) {
		std::cout << "Texture loading failed: " << file_name.c_str() << std::endl;
	}

	glGenTextures(1, &texture_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image_data);
}

void Texture::bind() {
	if (is_empty) { unbind(); return; } 

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

Texture::~Texture() {
	glDeleteTextures(1, &texture_id);
}

int Texture::get_unit() {
	return this->unit;
}
