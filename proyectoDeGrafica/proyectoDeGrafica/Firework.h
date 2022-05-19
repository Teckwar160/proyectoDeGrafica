#pragma once

// Biblioteca necesaria
#include "PointLight.h"


class Firework
{
public:
	Firework();
	Firework( int numFw, glm::vec3 colorFw, glm::vec3 posicionFw );
	
	glm::vec3* getPositions();
	
	// Define la posición de la luz
	void setPointLight(PointLight* light);
	
	// Función que nos dice si esta la animación corriendo
	bool isAnimating();
	glm::vec3 getCentralPos();

	// Función encargada de ejecutar los fuegos artificiales
	void animate(GLfloat delta);

	// Función encarga de devovler el número de cubos
	int getSize() { return numFireworks; }

	// Función encargada de resetear el objeto
	void reset();

	// Función encargada comenzar la animación
	void start();

	// Función encargada de actualizar la luz
	void updateLight();

	// Función encargada de devolver el valro de comienzaAnimacionFireworks
	bool getComienzaAnimacionFirework() { return comienzaAnimacionFireworks; }

	~Firework();

private:

	// Fireworks
	int i, x;
	int numFireworks;
	int stepFireworks;
	
	float intensidadFw;

	PointLight* pLight;

	glm::vec3 color;
	glm::vec3 ecuacionFw;
	
	glm::vec3 posicionOrigen;
	glm::vec3 posicionCentral;
	glm::vec3* posiciones;
	glm::vec3* posicionesFinales;

	bool fireworksOnce;
	bool comienzaAnimacionFireworks;

	// Función encargada de calcular la posición
	void calculaPosiciones();

	
};
