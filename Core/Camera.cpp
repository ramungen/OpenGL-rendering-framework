#include "Camera.h"

#include <iostream>

Camera::Camera(bool trueFps) : yaw(-90.0f), pitch(0.0f), mouseSensitivity(0.1f), zoom(45.0f), movementSpeed(2.5f) {
	this->trueFps = trueFps;
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	updateCameraVectors();
}

Camera::Camera(glm::vec3 position,float yaw, float pitch, bool trueFps) : mouseSensitivity(0.1f), zoom(45.0f), movementSpeed(2.5f) {
	
	this->yaw = yaw;
	this->pitch = pitch;
	this->trueFps = trueFps;
	this->position = position;
	updateCameraVectors();
}

Camera::~Camera() {
}

void Camera::updateCameraVectors() {

	
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);
	// Also re-calculate the Right and Up vector
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::normalize(glm::cross(direction, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, direction));
}


glm::mat4 Camera::getViewMatrix() { 
	return glm::lookAt(position, direction + position, up);
}

void Camera::processKeyboard(cameraMovement dir, float deltaTime) {
	float velocity = movementSpeed * deltaTime;
	
	switch (dir) {
	case FORWARD:
		position += direction * velocity;
		break;
	case BACKWARD:
		position -= direction * velocity;
		break;
	case LEFT:
		position -= right * velocity;
		break;
	case RIGHT:
		position += right * velocity;
		break;
	}

	if (trueFps) {
		position.y = 0;
	}
}
void Camera::processMouseMovement(float xoffset, float yoffset) {
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;
	yaw += xoffset;
	pitch += yoffset;

	// prevent gimbal lock
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
	if (zoom >= 1.0f && zoom <= 45.f) {
		zoom -= yoffset;
	}
	if (zoom <= 1.0f) {
		zoom = 1.0f;
	}
	if (zoom >= 45.0f) {
		zoom = 45.0f;
	}
}

