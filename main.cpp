#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>
#include "stb_image.h"

#include "shader.h"
#include "cube.h"
#include "ShaderHelpers.h"

#include "vertices.h"
#include "constants.h"
#include "Core/Camera.h"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), -90.0f, 0.0f, false);
// used for stabilising the framerate
float deltaTime = 0.0f;
float lastFrame = 0.0f;


#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/EventHandler.h"
#include "Core/Texture.h"


#include "VertexBuffer.h"
#include "VertexArray.h"


int main() {

	// configure window
	Window* window = new Window();
	window->InitWindow(SCR_WIDTH, SCR_HEIGHT);
	
	// set callbacks
	EventHandler eventHandler;
	eventHandler.EnableAllCallbacks(window);

	window->MakeCurrent();
	// capture the mouse
	window->SetOpenGLInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// if any of the opengl functions failed loading
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	Renderer* renderer = new Renderer();
	renderer->enableProperty(GL_DEPTH_TEST);
	

	Shader lightingShader("vertex.vs", "fragment.fs");
	Shader lampShader("lightVertex.vs", "lightFragment.fs");

	// configure VBO and cubeVAO
	VertexBuffer VBO(vertices, sizeof(vertices));
	VertexArray cubeVAO;
	cubeVAO.Bind();
	cubeVAO.SetAndEnableVertexAttrib(3, 8 * sizeof(float), (void*)(0));
	cubeVAO.SetAndEnableVertexAttrib(3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	cubeVAO.SetAndEnableVertexAttrib(2, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// configure light VAO
	VertexArray lightVAO;
	lightVAO.Bind();
	VBO.Bind();
	lightVAO.SetAndEnableVertexAttrib(3, 8 * sizeof(float), (void*)(0));
	

	auto specularMap = std::make_unique<Texture2D>("container2_specular.png");
	specularMap->Bind();
	auto diffuseMap = std::make_unique<Texture2D>("container2.png");
	diffuseMap->Bind();


	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);

	std::vector <OpenGLObject*> objects;
	glm::vec3 lightPos(4.0f, 0.0f, 0.0f);

	while (!window->ShouldClose()) {

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// handle input
		eventHandler.handle_input(window->GetRawWindow(), objects, lightingShader, &cubeVAO);
		renderer->Clear(0.1f, 0.1f, 0.1f, 1.0f);
	
		// be sure to activate shader when setting uniforms/drawing objects
		lightingShader.use();

		ConfigureLighting(lightingShader, lightPos, camera);

		glm::mat4 model;
		glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();
		
		Cube objectCube(lightingShader, &cubeVAO, glm::vec3(0.0f, 0.0f, 0.0f));

		for (auto& object : objects) {
			renderer->Draw(object, model, view, projection, GL_TRIANGLES, 0, 36);
		}
			 
		// also draw the lamp object
	
		lampShader.use();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(lightPos));
		model = glm::scale(model, glm::vec3(1.0f));

		Cube lampCube(lampShader, &lightVAO, lightPos);
		renderer->Draw(&lampCube, model, view, projection, GL_TRIANGLES, 0, 36);
		
		window->SwapBuffers();
		window->ProcessEvents();
	}

	return 0;
}


