// Biblioteca necesaria
#include "CameraAerial.h"

CameraAerial::CameraAerial() : Camera() {}

CameraAerial::CameraAerial(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) :
	Camera( startPosition, startUp, startYaw, startPitch, startMoveSpeed, startTurnSpeed) {}

void CameraAerial::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position.x += front.x * velocity;
		position.z += front.z * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position.x -= front.x * velocity;
		position.z -= front.z * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

CameraAerial::~CameraAerial()
{
}
