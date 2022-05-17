
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
	stepFireworks = 0;
	intensidadFw = 10.f;
	ecuacionFw = glm::vec3(0.1f, 0.1f, 0.1f);
}

void Firework::updateLight() {
	pLight->setColor(color);
	pLight->setPosition(posicionCentral);
	pLight->setIntensity(intensidadFw, intensidadFw);
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
		if (posicionCentral.y < 500.0f) {
			posicionCentral.y++;
		}
		else if (fireworksOnce) {
			calculaPosiciones();
			fireworksOnce = false;
			intensidadFw = 45.f;
			ecuacionFw = glm::vec3(0.1f, 0.01f, 0.001f);
		}
		else if (stepFireworks < 500) {
			for (i = 0; i < numFireworks; i++) {
				posiciones[i] += (posicionesFinales[i] - posiciones[i]) / 500.0f;
			}
			//intensidadFw += (0.0 - intensidadFw) / 1000;
			stepFireworks++;

		}
		else if (stepFireworks < 800) {
			//ecuacionFw.y += (0.1 - ecuacionFw.y) / 800;
			ecuacionFw.z += (0.1 - ecuacionFw.z) / 800;
			intensidadFw += (0.1 - intensidadFw) / 800;
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