#pragma once

#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	//virtual void calculatePosition(glm::vec3 avPos);
	virtual void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	void setPosition(glm::vec3 pos);
	//void setCameraDirection(glm::vec3 dir);
	
	void setYaw(GLfloat yawn) { yaw = yawn; }
	void setPitch(GLfloat pitchn) { pitch = pitchn; }
	
	GLfloat getYaw() { return yaw; }
	GLfloat getPitch() { return pitch; }

	glm::vec3 getPosition();
	//glm::vec3 getCameraDirection();
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

