#pragma once

#include <glfw3.h>
#include <glm.hpp>

//Definición de Frame
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

#define MAX_FRAMES 200

//Variables que se usaran en el main

//Thousand
extern float thousandX;
extern float thousandZ;
extern float giroThousand;

//Laboon
extern float laboonX;
extern float laboonZ;
extern float anguloLaboon;

//Meta Knight
extern FRAME KeyFrameMetaKnight[MAX_FRAMES];
extern float metaKnightX;
extern float metaKnightZ;
extern float giroMetaKnight;
extern int iCSMetaKnight;
extern int fIMetaKnight;// = 18;//5;
extern int iMSMetaKnight;
extern int pIMetaKnight;
extern bool comienzaAnimacionMetaKnight;
extern bool banderaMetaKnight;


void controlDeTeclas(bool* keys, GLfloat delta);

//Animación de Thousand
void animaThousand(GLfloat delta);

//Animación de Laboon
void animaLaboon(GLfloat delta);

void keyFrameMetaKnight();

void animate(FRAME* KeyFrame, float* x, float* z, float* giro, int* i_curr_steps, int i_max_steps, int* playIndex, int FrameIndex, bool* play);

int getCameraType();