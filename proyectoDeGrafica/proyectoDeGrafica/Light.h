#pragma once

#include <glew.h>
#include <glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, 
			GLfloat aIntensity, GLfloat dIntensity);
	void setIntensity(GLfloat aInt, GLfloat dInt) { ambientIntensity = aInt; diffuseIntensity = dInt; }
	void setColor(glm::vec3 col) { color = col; }
	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

