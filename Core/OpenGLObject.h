#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "shader.h"
#include <memory>

class OpenGLObject {

protected:
	Shader shader;
	VertexArray* vertexArray;
	VertexBuffer* vertexBuffer;
	glm::vec3 position;

public:
	virtual Shader GetShader() { return shader; }
	virtual unsigned int ArrayID() { return vertexArray->ID(); }
	virtual unsigned int BufferID() { return vertexBuffer->ID(); }
	virtual glm::vec3 Position() { return position; }
	virtual ~OpenGLObject() {}
};
