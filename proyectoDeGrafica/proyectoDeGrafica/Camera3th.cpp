#include "Camera3th.h"

Camera3th::Camera3th() : Camera()
{
	distFromAvatar = 10;
	distxAvatar = 0.0f;
	distyAvatar = 0.0f;
}

Camera3th::Camera3th(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) :
	Camera( startPosition, startUp, startYaw, startPitch, startMoveSpeed, startTurnSpeed)
{
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	distFromAvatar = 10;
	distxAvatar = 0.0f;
	distyAvatar = 0.0f;
}


void Camera3th::calculatePosition(glm::vec3 posAv, GLfloat yawA)
{
	distxAvatar = distFromAvatar * glm::cos(glm::radians(pitch));
	distyAvatar = distFromAvatar * glm::sin(glm::radians(pitch));

	float xoffset = distxAvatar * glm::cos(glm::radians(yawA));
	float zoffset = -distxAvatar * glm::sin(glm::radians(yawA));

	position.x = posAv.x - xoffset;
	position.y = posAv.y - distyAvatar;
	position.z = posAv.z - zoffset;

	update(posAv);

}

void Camera3th::calculatePosition(glm::vec3 posAv, GLfloat yawA, GLfloat pitchA)
{
	distxAvatar = distFromAvatar * glm::cos(glm::radians(pitchA));
	distyAvatar = distFromAvatar * glm::sin(glm::radians(pitchA));

	float xoffset = distxAvatar * glm::cos(glm::radians(yawA));
	float zoffset = -distxAvatar * glm::sin(glm::radians(yawA));

	position.x = posAv.x - xoffset;
	position.y = posAv.y - distyAvatar;
	position.z = posAv.z - zoffset;

	update(posAv);
}

void Camera3th::update(glm::vec3 posAv)
{
	front = posAv - position;
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera3th::~Camera3th()
{
}
