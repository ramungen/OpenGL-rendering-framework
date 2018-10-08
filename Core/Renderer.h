#pragma once

#include <glad\glad.h>
#include <glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "stb_image.h"
#include "OpenGLObject.h"

#include "constants.h"
#include <string>


class Renderer {
private:

public:

	Renderer() {

	}

	void Draw(OpenGLObject* object, glm::mat4 model, glm::mat4 view, glm::mat4 projection, unsigned int renderMode, int start, int end) {
		model = glm::translate(model, object->Position());

		Shader currentShader = object->GetShader();
		currentShader.setMat4("projection", projection);
		currentShader.setMat4("view", view);
		currentShader.setMat4("model", model);

		// render the cube
		glBindVertexArray(object->ArrayID());
		glDrawArrays(renderMode, start, end);
	}


	void Clear(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
		// clear the whole screen with a color
		glClearColor(red, green, blue, alpha);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void enableProperty(int property) {
		glEnable(property);
	}

};
