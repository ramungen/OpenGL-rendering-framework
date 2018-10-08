#pragma once

#include <glad\glad.h>
#include <glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "stb_image.h"

#include "constants.h"


class Window {
private:

	GLFWwindow* window;
	//EventHandler eventHandler;

public:

	Window(bool capture = false) {
	}

	void MakeCurrent() {
		glfwMakeContextCurrent(window);
	}

	GLFWwindow* GetRawWindow() { return window; }

	void Close() {
		glfwSetWindowShouldClose(window, true);
	}

	void InitWindow(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		// uncomment this statement to fix compilation on OS X
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
#endif

// glfw window creation
		this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == nullptr) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			throw std::exception("Failed to create GLFW window");
		}
	}

	void SetOpenGLInputMode(unsigned int mode, unsigned int value) {
		if (window != nullptr) {
			glfwSetInputMode(window, mode, value);
		}
	}

	bool ShouldClose() {
		return glfwWindowShouldClose(window);
	}

	void SwapBuffers() {
		glfwSwapBuffers(this->window);
	}

	void ProcessEvents() {
		glfwPollEvents();
	}

};
