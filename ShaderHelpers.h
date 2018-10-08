#pragma once

#include "shader.h"
#include "Core/Camera.h"

void ConfigureLighting(Shader& lightingShader, glm::vec3& lightPos, const Camera& camera) {

	lightingShader.setVec3("light.position", lightPos);
	lightingShader.setVec3("viewPos", camera.getPosition());

	lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	// material properties
	lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	lightingShader.setFloat("material.shininess", 64.0f);

	lightingShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

}