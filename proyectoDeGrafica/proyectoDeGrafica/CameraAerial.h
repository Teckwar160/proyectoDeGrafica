#pragma once

// Biblioteca necesaria
#include "Camera.h"


class CameraAerial : public Camera
{
public:
	CameraAerial();
	CameraAerial(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	
	virtual void keyControl(bool* keys, GLfloat deltaTime);

	~CameraAerial();
};

