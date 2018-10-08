#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const void * data, unsigned int size) : bufferID(0) {
	glGenBuffers(1, &this->bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &this->bufferID);
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->bufferID);
}

void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
