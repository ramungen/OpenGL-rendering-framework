#pragma once
#include <cmath>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

enum cameraMovement {
	FORWARD, 
	BACKWARD,
	LEFT,
	RIGHT
};
class Camera {

public:
	Camera(bool trueFps);
	Camera(glm::vec3 position, float yaw, float pitch, bool trueFps);
	~Camera();
	glm::mat4 getViewMatrix();
	void processKeyboard(cameraMovement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset);
	void processMouseScroll(float yoffset);

public:
	glm::vec3 getDirection() const { return direction; }
	float getDirectionX() const { return direction.y; }
	float getDirectionY() const { return direction.z; }
	float getDirectionZ() const { return direction.x; }

	glm::vec3 getPosition() const { return position; }
	float getPositionX() const { return position.y; }
	float getPositionY() const { return position.y; }
	float getPositionZ() const { return position.z; }

	float getZoom() { return zoom; }

private:

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;

	bool trueFps = false;

	// euler angles
	float pitch;
	float yaw;

	// camera options
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

private:
	void updateCameraVectors();
};

