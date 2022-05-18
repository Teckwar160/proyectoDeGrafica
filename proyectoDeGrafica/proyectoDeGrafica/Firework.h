#pragma once

#include "PointLight.h"


class Firework
{
public:
	Firework();
	Firework( int numFw, glm::vec3 colorFw, glm::vec3 posicionFw );
	
	glm::vec3* getPositions();
	
	void setPointLight(PointLight* light);
	
	bool isAnimating();
	glm::vec3 getCentralPos();
	// Función encargada de ejecutar los fuegos artificiales
	void animate(GLfloat delta);
	int getSize() { return numFireworks; }
	void reset();

	void start();

	void updateLight();

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

	void calculaPosiciones();
};
