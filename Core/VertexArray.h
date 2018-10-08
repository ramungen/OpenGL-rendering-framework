#pragma once

#include <glad/glad.h>

class VertexArray {
private:
	unsigned int arrayID;
	unsigned int attribIndex;

public:
	VertexArray(bool generate = false);
	~VertexArray();

	unsigned int ID() { return this->arrayID; }

	void Bind();
	void Unbind();

	void SetAndEnableVertexAttrib(int size, int stride, const void* startPos);

};

