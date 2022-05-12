#pragma once

#include <glfw3.h>
#include <glm.hpp>
extern float thousandX;
extern float thousandZ;
extern float giroThousand;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float x;
	float incremento_x;
	float z;
	float incremento_z;
	float giro;
	float incremento_giro;

}FRAME;

void controlDeTeclas(bool* keys, GLfloat delta);

//Animación de Thousand
void animaThousand(GLfloat delta);
