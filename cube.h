
#ifndef CUBE_H
#define CUBE_H

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include "Core/OpenGLObject.h"
#include "shader.h"
#include "constants.h"

class Cube : public OpenGLObject {
public:
	Cube(Shader& shader, VertexArray* vertexArray, glm::vec3 pos);

	void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	~Cube();

private:


};
#endif
