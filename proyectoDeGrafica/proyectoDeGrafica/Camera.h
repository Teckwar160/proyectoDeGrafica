#pragma once

// Bibliotecas necesarias
#include <glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <glfw3.h>

// Clase camera
class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	virtual void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	void setPosition(glm::vec3 pos);
	
	void setYaw(GLfloat yawn) { yaw = yawn; }
	void setPitch(GLfloat pitchn) { pitch = pitchn; }
	
	GLfloat getYaw() { return yaw; }
	GLfloat getPitch() { return pitch; }

	glm::vec3 getPosition();
	glm::mat4 calculateViewMatrix();
	void setType(int type) { cameraType = type; }

	~Camera();

protected:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	int cameraType;

	void update();
};

