#include "Texture.h"
#include "stb_image.h"
#include <string>
#include <exception>

Texture2D::~Texture2D() {}

void Texture2D::Load(const char* path) {

	glGenTextures(1, &this->textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		switch (nrComponents) {
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		}

		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
	}

	else {
		stbi_image_free(data);
		std::string error = "texture failed to load at path: " + std::string(path);
		throw std::exception(error.c_str());

	}
}


void Texture2D::Bind() {

	glActiveTexture(textureCount++);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}


unsigned int Texture2D::textureCount = 0;