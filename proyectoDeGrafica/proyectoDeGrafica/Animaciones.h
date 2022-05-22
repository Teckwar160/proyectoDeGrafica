#pragma once

// Bibliotecas
#include "Firework.h"
#include "Camera.h"
#include <glfw3.h>
#include <irrKlang.h>
using namespace irrklang;

// Definición de Frame
typedef struct _frame
{
	// Variables para cuerpos sencillos
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

	// Variables para cuerpos complejos
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
		// Atributos para key frames
		FRAME KeyFrame[MAX_FRAMES];
		int i_curr_steps = 0; 
		int i_max_steps = 200; 
		int playIndex = 0;
		int FrameIndex = 0; 
		bool play = false;
		bool bandera = true;

		// Atributos de posición
		float x = 0;
		float z = 0;
		float y = 0;
		float giroX = 0;
		float giroY = 0;
		float giroZ = 0;

		// Atributos para cuerpos complejos
		float anguloBrazoDerecho = 0;
		float anguloBrazoIzquierdo = 0;
		float anguloPiernaDerecha = 0;
		float anguloPiernaIzquierda = 0;


		// Método encargado de resetear atributos para repetir la animación
		void reset();

		// Método encargado de definir el estado inicial del personaje
		void set(float x, float y, float z, float giroX, float giroY, float giroZ);
};

// Variables que se usarán en el main

// Thousand
extern float thousandX;
extern float thousandZ;
extern float giroThousand;

// Laboon
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

// Luces de la marina
extern bool lucesMarina;

// Ruptura de vela de bardo
extern bool velaRota;

// Personajes
extern personaje pMetaKnight;
extern personaje pDorry;
extern personaje pBrogy;
extern personaje pCarue;
extern personaje pVivi;
extern personaje pZoro;
extern personaje pFranky;

// Audio
extern ISoundEngine* audioAmbiental;
extern ISoundEngine* audioAtaque;

// Fuegos artificiales
extern Firework fireworkRed;

//Función encargada de controlar las teclas para las animaciones
void controlDeTeclas(bool* keys);

// Animación de Thousand
void animaThousand(GLfloat delta);

// Animación de Laboon
void animaLaboon(GLfloat delta);

// Función encargada de definir la animación de Luffy
void animaLuffy(GLfloat delta);

// Función encargada de ejecutar el golpe de Luffy
void animaAtaqueLuffy(GLfloat delta);

// Función encargada de guiar las cámaras para el recorrido
void animaRecorrido(Camera* cam, GLfloat delta);

// Función encargada de definir la animación de Meta Knight
void keyFrameMetaKnight();

// Función encargada de animar cuando Meta Knight es golpeado
void keyFrameMetaKnightFight();

// Función encargada de definir la animación de Dorry
void keyFrameDorry();

// Función encargada de definir la animación de Brogy
void keyFrameBrogy();

// Función encargada de empezar la pelea de los gigantes
void iniciaPelea();

// Función encargada de definir la animación de Carue
void keyFrameCarue();

// Función encargada de definir la animación de Vivi
void keyFrameVivi();

// Función encargada de definir la animación de Zoro
void keyFrameZoro();

// Función encargada de definir la animación de Franky
void keyFrameFranky();

// Función encargada de ejecutar la erupción del volcan.
void animaLava(GLfloat delta);

// Función encargada de ejecutar la animación por KeyFrames de un personaje
void animate(personaje *p);

// Funcion que devuelve el tipo de camara actual
int getCameraType();

// Función encargada de ejecutar los fuegos artificiales
void iniciaShow(bool day);
