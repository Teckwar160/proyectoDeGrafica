#pragma once
#include "Firework.h"
#include "Camera.h"
#include <glfw3.h>
//#include <glm.hpp>

//Definici�n de Frame
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float x;
	float incremento_x;
	float y;
	float incremento_y;
	float z;
	float incremento_z;
	float giroX;
	float incremento_giroX;
	float giroY;
	float incremento_giroY;
	float giroZ;
	float incremento_giroZ;

	//Variables para cuerpos complejos
	float anguloBrazoDerecho;
	float incremento_anguloBrazoDerecho;
	float anguloBrazoIzquierdo;
	float incremento_anguloBrazoIzquierdo;
	float anguloPiernaDerecha;
	float incremento_anguloPiernaDerecha;
	float anguloPiernaIzquierda;
	float incremento_anguloPiernaIzquierda;


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

		//Atributos de posici�n
		float x = 0;
		float z = 0;
		float y = 0;
		float giroX = 0;
		float giroY = 0;
		float giroZ = 0;

		//Atributos para cuerpos complejos
		float anguloBrazoDerecho = 0;
		float anguloBrazoIzquierdo = 0;
		float anguloPiernaDerecha = 0;
		float anguloPiernaIzquierda = 0;


		//M�todo encargada de resetear atributos para repetir la animaci�n
		void reset();

		//M�todo encargado de definir el estado inicial del personaje
		void set(float x, float y, float z, float giroX, float giroY, float giroZ);
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

// Luffy
extern float anguloBrazoR;
extern float anguloBrazoL;
extern float anguloPiernaR;
extern float anguloPiernaL;
extern float escalaBrazo;

// Luces del volcan
extern glm::vec3 posicionesVolcan[3];
extern glm::vec3 posicionOrigenV;
extern float rotacionLava; // x
extern bool iniciaErupcionVolcan;

// Ruptura de vela de bardo
extern bool velaRota;

//Personajes
extern personaje pMetaKnight;
extern personaje pDorry;
extern personaje pBrogy;
extern personaje pCarue;
extern personaje pVivi;
extern personaje pZoro;
extern personaje pFranky;

// Fuegos artificiales
extern Firework fireworkRed;

//Funci�n encargada de controlar las teclas para las animaciones
void controlDeTeclas(bool* keys);

//Animaci�n de Thousand
void animaThousand(GLfloat delta);

//Animaci�n de Laboon
void animaLaboon(GLfloat delta);

//Funci�n encargada de definir la animaci�n de Luffy
void animaLuffy(GLfloat delta);

// Funci�n encargada de ejecutar el golpe de Luffy
void animaAtaqueLuffy(GLfloat delta);

// Funci�n encargada de guiar las c�maras para el recorrido
void animaRecorrido(Camera* cam, GLfloat delta);

//Funci�n encargada de definir la animaci�n de MetaKnight
void keyFrameMetaKnight();

//Funci�n encargada de definir la animaci�n de Dorry
void keyFrameDorry();

//Funci�n encargada de definir la animaci�n de Brogy
void keyFrameBrogy();

//Funci�n encargada de emepzar la pelea de lso gigantes
void iniciaPelea();

//Funci�n encargada de definir la animaci�n de Carue
void keyFrameCarue();

//Funci�n encargada de definir la animaci�n de Vivi
void keyFrameVivi();

//Funci�n encargada de definir la animaci�n de Zoro
void keyFrameZoro();

//Funci�n encargada de definir la animaci�n de Franky
void keyFrameFranky();

// Funci�n encargada de ejecutar la erupci�n del volcan.
void animaLava(GLfloat delta);

//Funci�n encargada de ejecutar la animaci�n por KeyFrames de un personaje
void animate(personaje *p);

// Funcion que devuelve el tipo de camara actual
int getCameraType();
