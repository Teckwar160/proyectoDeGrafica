#pragma once

// Biblioteca necesaria
#include "Camera.h"


class Camera3th : public Camera
{
public:
	Camera3th();
	Camera3th(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	
	void calculatePosition(glm::vec3 posAv, GLfloat yaw);
	void calculatePosition(glm::vec3 posAv, GLfloat yaw, GLfloat pitchA);

	~Camera3th();

private:
	GLfloat distFromAvatar;
	GLfloat distxAvatar;
	GLfloat distyAvatar;

	void update(glm::vec3 posAv);

};

