#pragma once

#include <glad\glad.h>
#include <glfw3.h>
#include <string>
#include <glm.hpp>
#include <vector>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "stb_image.h"

#include "constants.h"
#include "Window.h"
#include <cube.h>
/*
TODO: change default_processInput to something better
*/
namespace {
	void default_framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void default_mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void default_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void default_processInput(GLFWwindow *window, std::vector <OpenGLObject*>& cubes, Shader shader, VertexArray* cubeVAO);
}

enum class callback {
	MOUSE = 0,
	FRAMEBUFFER_SIZE = 1,
	SCROLL = 2,
};


struct EventHandler {

	EventHandler() {
		mouse_callback = default_mouse_callback;
		framebuffer_size_callback = default_framebuffer_size_callback;
		mouse_callback = default_mouse_callback;
		scroll_callback = default_scroll_callback;
		handle_input = default_processInput;
	}
	
	void(*mouse_callback) (GLFWwindow*, double, double);
	void (*framebuffer_size_callback) (GLFWwindow*, int, int);
	void(*scroll_callback)(GLFWwindow*, double, double);
	void (*handle_input)(GLFWwindow*, std::vector <OpenGLObject*>&, Shader, VertexArray*);


	void EnableAllCallbacks(Window* window) {
			glfwSetFramebufferSizeCallback(window->GetRawWindow(), framebuffer_size_callback);
			glfwSetCursorPosCallback(window->GetRawWindow(), mouse_callback);
			glfwSetScrollCallback(window->GetRawWindow(), scroll_callback);

	}

	void enableCallback(callback callbackType, Window* window) {
		switch (callbackType) {
		case callback::FRAMEBUFFER_SIZE:
			glfwSetFramebufferSizeCallback(window->GetRawWindow(), framebuffer_size_callback);
			break;
		case callback::MOUSE:
			glfwSetCursorPosCallback(window->GetRawWindow(), mouse_callback);
			break;
		case callback::SCROLL:
			glfwSetScrollCallback(window->GetRawWindow(), scroll_callback);
			break;
		default:
			std::cout << "unkown callback type\n";
			break;
		}
	}

};


namespace {
	bool godMode = false;
	bool drawAnotherObject = false;

	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;


	void default_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}


	void default_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		camera.processMouseMovement(xoffset, yoffset);
	}


	void default_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		camera.processMouseScroll(yoffset);
	}

	void default_processInput(GLFWwindow *window, std::vector <OpenGLObject*>& objects, Shader shader, VertexArray* cubeVAO) {

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			camera.processKeyboard(FORWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camera.processKeyboard(BACKWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camera.processKeyboard(LEFT, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera.processKeyboard(RIGHT, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
			drawAnotherObject = true;
		}

		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE) {
			if (drawAnotherObject) {
				// the constant regulates how far the added cube appears from camera
				glm::vec3 position = 1.7f * camera.getDirection() + camera.getPosition();
				Cube* newCube = new Cube(shader, cubeVAO, position);
				objects.push_back(newCube);
				drawAnotherObject = false;
			}

		}
	}
}


