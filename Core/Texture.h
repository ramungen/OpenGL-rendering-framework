#pragma once

#include <glad/glad.h>

class Texture2D {
private:
	unsigned int textureID;
	static unsigned int textureCount;

public:
	unsigned int ID() { return textureID; }

	Texture2D() : textureID(0) {}

	Texture2D(const char* path) : textureID(0) {
		this->Load(path);
	}

	~Texture2D();

	void Load(const char*path);

	void Bind();

};


