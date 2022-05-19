#pragma once

// Biblioteca necesaria
#include "PointLight.h"


class Firework
{
public:
	Firework();
	Firework( int numFw, glm::vec3 colorFw, glm::vec3 posicionFw );
	
	glm::vec3* getPositions();
	
	// Define la posici�n de la luz
	void setPointLight(PointLight* light);
	
	// Funci�n que nos dice si esta la animaci�n corriendo
	bool isAnimating();
	glm::vec3 getCentralPos();

	// Funci�n encargada de ejecutar los fuegos artificiales
	void animate(GLfloat delta);

	// Funci�n encarga de devovler el n�mero de cubos
	int getSize() { return numFireworks; }

	// Funci�n encargada de resetear el objeto
	void reset();

	// Funci�n encargada comenzar la animaci�n
	void start();

	// Funci�n encargada de actualizar la luz
	void updateLight();

	// Funci�n encargada de devolver el valro de comienzaAnimacionFireworks
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

	// Funci�n encargada de calcular la posici�n
	void calculaPosiciones();

	
};
