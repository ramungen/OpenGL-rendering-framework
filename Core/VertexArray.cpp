#include "VertexArray.h"



VertexArray::VertexArray(bool generate) : attribIndex(0), arrayID(0) {
	if (generate) {
		glGenVertexArrays(1, &this->arrayID);
	}
}


VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &this->arrayID);
}

void VertexArray::Bind() {
	attribIndex = 0;
	glBindVertexArray(this->arrayID);
}

void VertexArray::Unbind() {
	attribIndex = 0;
	glBindVertexArray(0);
}

void VertexArray::SetAndEnableVertexAttrib(int size, int stride, const void* startPos) {
	//GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer
	glVertexAttribPointer(attribIndex, size, GL_FLOAT, GL_FALSE, stride, startPos);
	++attribIndex;
}
