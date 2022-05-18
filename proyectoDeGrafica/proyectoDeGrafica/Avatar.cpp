
#include "Avatar.h"

Avatar::Avatar()
{
}

Avatar::Avatar(glm::vec3 startPosition, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	yaw = 0.0f;
	rotation = 0.0f;
	pitch = 0.0f;
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Avatar::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
		rotation = yaw;

	}
	
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
		rotation = yaw + 180.0f;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
		rotation = yaw + 100.0f;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
		rotation = yaw - 100.0f;
	}

	if (keys[GLFW_KEY_W] and keys[GLFW_KEY_D]) {
		rotation = yaw - 45.0f;
	}

	if (keys[GLFW_KEY_W] and keys[GLFW_KEY_A]) {
		rotation = yaw + 45.0f;
	}

	if (keys[GLFW_KEY_S] and keys[GLFW_KEY_D]) {
		rotation = yaw - 135.0f;
	}

	if (keys[GLFW_KEY_S] and keys[GLFW_KEY_A]) {
		rotation = yaw + 135.0f;
	}
	
}

void Avatar::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw -= xChange;
	pitch += yChange;

	if (pitch > 0.0f)
	{
		pitch = 0.0f;
	}

	if (pitch < -30.0f)
	{
		pitch = -30.0f;
	}

	update();
}

glm::vec3 Avatar::getAvatarPosition()
{
	return position;
}


void Avatar::update()
{
	front.x = cos(glm::radians(yaw));
	front.y = 0.0f;
	front.z = -sin(glm::radians(yaw));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
}

Avatar::~Avatar() {};