#pragma once

#include <glm.hpp>
#include <glad/glad.h>

class VertexBuffer {
private:
	unsigned int bufferID;

public:

	VertexBuffer() : bufferID(0) {}
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	unsigned int ID() { return bufferID; }

	void Bind();
	void Unbind();
};

