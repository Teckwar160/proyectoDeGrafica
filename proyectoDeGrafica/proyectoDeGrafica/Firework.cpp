// Bibliotecas necesarias
#include "Firework.h"
#include <glm.hpp>


Firework::Firework() {};

Firework::Firework(int numFw, glm::vec3 colorFw, glm::vec3 posicionFw)
{
	numFireworks = numFw;
	color = colorFw;
	posicionOrigen = posicionFw;
	posicionCentral = posicionFw;
	comienzaAnimacionFireworks = false;

	posiciones = new glm::vec3 [numFireworks];
	posicionesFinales = new glm::vec3 [numFireworks];
};

void Firework::setPointLight(PointLight* light)
{
	pLight = light;
}


glm::vec3 * Firework::getPositions() {
	return posiciones;
}
glm::vec3 Firework::getCentralPos() {
	return posicionCentral;
}

bool Firework::isAnimating() {
	return comienzaAnimacionFireworks;
}

void Firework::start() {

	// Activación de animación
	fireworksOnce = true;
	comienzaAnimacionFireworks = true;
}

void Firework::reset() {

	// Reseteo de posiciones
	posicionCentral = posicionOrigen;

	for (i = 0; i < numFireworks; i++) {
		posiciones[i] = glm::vec3(0.0f, 0.0f, -400.0f);
	}
	x = 0;
	stepFireworks = 0;
	intensidadFw = 10.f;
	ecuacionFw = glm::vec3(0.2f, 0.3f, 0.3f);
}

void Firework::updateLight() {
	pLight->setColor(color);
	pLight->setIntensity(intensidadFw, intensidadFw);
	pLight->setPosition(posicionCentral);
	pLight->setEcuation(ecuacionFw);
}

// Función que calcula las posiciones finales de los fuegos artificiales
void Firework::calculaPosiciones() {
	int min = -200;
	int max = 200;
	int xr, yr, zr;

	for (i = 0; i < numFireworks; i++) {
		xr = min + rand() % (max + 1 - min);
		yr = min + rand() % (max + 1 - min);
		zr = min + rand() % (max + 1 - min);
		posiciones[i] = posicionCentral;
		posicionesFinales[i] = posicionCentral + glm::vec3(xr, yr, zr);
	}
}

void Firework::animate(GLfloat delta)
{
	if (comienzaAnimacionFireworks)
	{	
		// Color
		x < 768 ? x++ : x = 0;
		if (x <= 255) {
			color.x = 255 - x;
			color.y = x;
			color.z = 0;
		}
		else if (x <= 511) {
			color.x = 0;
			color.y = 255 - (x - 256);
			color.z = x - 256;
		}
		else {
			color.x = x - 512;
			color.y = 0;
			color.z = 255 - (x - 512);
		}
		// Posicion
		if (posicionCentral.y < 500.0f) {
			posicionCentral.y++;
		}
		else if (fireworksOnce) {
			calculaPosiciones();
			fireworksOnce = false;
			intensidadFw = 60.f;
		}
		else if (stepFireworks < 500) {
			for (i = 0; i < numFireworks; i++) {
				posiciones[i] += (posicionesFinales[i] - posiciones[i]) / 500.0f;
			}
			stepFireworks++;

		}
		else if (stepFireworks < 800) {
			stepFireworks++;
		}
		else
		{
			comienzaAnimacionFireworks = false;
			posicionCentral = posicionOrigen;
		}
	}
}


Firework::~Firework() {
	delete[] posiciones;
	delete[] posicionesFinales;
};