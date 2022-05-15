#pragma once

#include <glfw3.h>
#include <glm.hpp>

//Definición de Frame
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float x;
	float incremento_x;
	float y;
	float incremento_y;
	float z;
	float incremento_z;
	float giro;
	float incremento_giro;

}FRAME;

#define MAX_FRAMES 200

class personaje {
	public:
		//Atributos para key frames
		FRAME KeyFrame[MAX_FRAMES];
		int i_curr_steps = 0; 
		int i_max_steps = 200; 
		int playIndex = 0;
		int FrameIndex = 0; 
		bool play = false;
		bool bandera = true;

		//Atributos de posición
		float x = 0;
		float z = 0;
		float y = 0;
		float giro = 0;

		//Atributos para cuerpos complejos

		//Método encargada de resetear atributos para repetir la animación
		void reset();

		//Método encargado de definir el estado inicial del personaje
		void set(float x, float y, float z, float giro);
};

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
extern personaje pMetaKnight;

//Función encargada de controlar las teclas para las animaciones
void controlDeTeclas(bool* keys, GLfloat delta);

//Animación de Thousand
void animaThousand(GLfloat delta);

//Animación de Laboon
void animaLaboon(GLfloat delta);

//Función encargada de definir la aniamción de MetaKnight
void keyFrameMetaKnight();

//Función encargada de ejecutar la animación por KeyFrames de un personaje
void animate(personaje *p);

int getCameraType();