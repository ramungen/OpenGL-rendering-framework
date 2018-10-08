#include "cube.h"

Cube::Cube(Shader& shader, VertexArray* vArray, glm::vec3 pos) {
	this->shader = shader;
	this->vertexArray = vArray;
	this->position = pos;
}

Cube::~Cube() {

}

void Cube::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
	model = glm::translate(model, position);
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", model);

	// render the cube
	glBindVertexArray(vertexArray->ID());
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
