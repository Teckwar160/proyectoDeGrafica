#include "Animaciones.h"

//Control de camaras
int cameraType = 1;
bool cameraFlag = false;

//Variables para thousand
float thousandX = -170.0f;
float thousandZ = 200.0f;
float giroThousand = 0;
char sentidoThousand = 'u';
float velocidadThousand = 0.5f;
bool  comienzaAnimacionThousand = false;
int c1 = 0, c2 = 0;
bool banderaCentro = false;

//Variables para Laboon
float laboonX = -300.0f;
float laboonZ = 80.0f;
float velocidadLaboon = 0.5f;
char sentidoLaboon = 'u';
float anguloLaboon = 0.0f;
bool comienzaAnimacionLaboon = false;


//Funciones de clase personaje
void personaje::reset() {
	this->play = true;
	this->playIndex = 0;
	this->i_curr_steps = 0;
	this->bandera = false;
}

void personaje::set(float x, float y, float z, float giro) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->giro = giro;
}

//Personajes
personaje pMetaKnight;
personaje pDorry;


int getCameraType() {
	return cameraType;
}

void resetElements(personaje* p)
{
	p-> x = p-> KeyFrame[0].x;
	p-> z = p-> KeyFrame[0].z;
	p-> giro = p-> KeyFrame[0].giro;
	p->anguloBrazoDerecho = p->KeyFrame[0].anguloBrazoDerecho;
	p->anguloBrazoIzquierdo = p->KeyFrame[0].anguloBrazoIzquierdo;
	p->anguloPiernaDerecha = p->KeyFrame[0].anguloPiernaDerecha;
	p->anguloPiernaIzquierda = p->KeyFrame[0].anguloPiernaIzquierda;

}

void interpolation(personaje* p)
{
	p-> KeyFrame[p-> playIndex].incremento_x = (p-> KeyFrame[p-> playIndex + 1].x - p-> KeyFrame[p-> playIndex].x) / p-> i_max_steps;
	p-> KeyFrame[p-> playIndex].incremento_z = (p-> KeyFrame[p-> playIndex + 1].z - p-> KeyFrame[p-> playIndex].z) / p-> i_max_steps;
	p-> KeyFrame[p-> playIndex].incremento_giro = (p-> KeyFrame[p-> playIndex + 1].giro - p-> KeyFrame[p-> playIndex].giro) / p-> i_max_steps;
	p->KeyFrame[p->playIndex].incremento_anguloBrazoDerecho = (p->KeyFrame[p->playIndex + 1].anguloBrazoDerecho - p->KeyFrame[p->playIndex].anguloBrazoDerecho) / p->i_max_steps;
	p->KeyFrame[p->playIndex].incremento_anguloBrazoIzquierdo = (p->KeyFrame[p->playIndex + 1].anguloBrazoIzquierdo - p->KeyFrame[p->playIndex].anguloBrazoIzquierdo) / p->i_max_steps;
	p->KeyFrame[p->playIndex].incremento_anguloPiernaDerecha = (p->KeyFrame[p->playIndex + 1].anguloPiernaDerecha - p->KeyFrame[p->playIndex].anguloPiernaDerecha) / p->i_max_steps;
	p->KeyFrame[p->playIndex].incremento_anguloPiernaIzquierda = (p->KeyFrame[p->playIndex + 1].anguloPiernaIzquierda - p->KeyFrame[p->playIndex].anguloPiernaIzquierda) / p->i_max_steps;

}

void animate(personaje *p) {
	if (p-> play) {
		if (p-> i_curr_steps >= p-> i_max_steps) {
			(p-> playIndex)++;

			if (p-> playIndex > p-> FrameIndex - 2) {
				p-> playIndex = 0;
				p-> play = false;
			}
			else {
				p-> i_curr_steps = 0;
				interpolation(p);
			}
		}
		else {
			p->x += p->KeyFrame[p-> playIndex].incremento_x;
			p->z += p->KeyFrame[p -> playIndex].incremento_z;
			p->giro += p->KeyFrame[ p-> playIndex].incremento_giro;
			p->anguloBrazoDerecho += p->KeyFrame[p->playIndex].incremento_anguloBrazoDerecho;
			p->anguloBrazoIzquierdo += p->KeyFrame[p->playIndex].incremento_anguloBrazoIzquierdo;
			p->anguloPiernaDerecha += p->KeyFrame[p->playIndex].incremento_anguloPiernaDerecha;
			p->anguloPiernaIzquierda += p->KeyFrame[p->playIndex].incremento_anguloPiernaIzquierda;

			(p-> i_curr_steps)++;
		}
	}
}

void controlDeTeclas(bool* keys, GLfloat delta) {
	//Meta Knight
	if (keys[GLFW_KEY_M]) {
		if (pMetaKnight.bandera) {
			if (pMetaKnight.play == false && pMetaKnight.FrameIndex > 1) {
				resetElements(&pMetaKnight);
				interpolation(&pMetaKnight);
				pMetaKnight.reset();
			}
		}

	}

	//Dorry
	if (keys[GLFW_KEY_O]) {
		if (pDorry.bandera) {
			if (pDorry.play == false && pDorry.FrameIndex > 1) {
				resetElements(&pDorry);
				interpolation(&pDorry);
				pDorry.reset();
			}
		}

	}

	//Activador de animaciones por keyFrame
	if (keys[GLFW_KEY_K]) {
		pMetaKnight.bandera = true;
		pDorry.bandera = true;
	}

	// Control de cámaras
	if (keys[GLFW_KEY_C] and cameraFlag)
	{
		cameraType++;
		if (cameraType > 3)	cameraType = 1;
		cameraFlag = false;
	}
	if (keys[GLFW_KEY_X]) {
		cameraFlag = true;
	}

	//Control de animación de Thousand
	if (keys[GLFW_KEY_T]) {
		comienzaAnimacionThousand = true;
	}

	//Control de animación de Laboon
	if (keys[GLFW_KEY_L]) {
		comienzaAnimacionLaboon = true;
	}
	
}

void calculaCentro(){
	//Calculamos el centro
	if (banderaCentro) {
		if (sentidoThousand == '1') {
			c1 = thousandX + 100; 
			c2 = thousandZ;	 
		}

		if (sentidoThousand == '2') {
			c1 = thousandX; 
			c2 = thousandZ - 100;	 
		}

		if (sentidoThousand == '3') {
			c1 = thousandX -100; 
			c2 = thousandZ;	 
		}

		//Evitamos que se vuelva a calcular
		banderaCentro = false;
	}
}


void animaThousand(GLfloat delta) {

	if (comienzaAnimacionThousand) {
		//Control de movimiento
		switch (sentidoThousand) {
		case 'u':
			thousandZ += velocidadThousand * delta;
			break;
		case 'd':
			thousandZ -= velocidadThousand * delta;
			break;
		case 'l':
			thousandX += velocidadThousand * delta;
			break;
		case 'r':
			thousandX -= velocidadThousand * delta;
			break;
		case '1':
			thousandX = c1 + 100 * glm::cos(glm::radians(giroThousand+180));
			thousandZ = c2 + 100 * glm::sin(glm::radians(giroThousand+180));
			giroThousand -= 0.3 * delta;

			if (giroThousand < -90.0 && sentidoThousand == '1') {
				sentidoThousand = 'l';
			}

			break;
		case '2':
			thousandX = c1 + 100 * glm::cos(glm::radians(giroThousand + 180));
			thousandZ = c2 + 100 * glm::sin(glm::radians(giroThousand + 180));
			giroThousand -= 0.3 * delta;

			if (giroThousand < -180.0 && sentidoThousand == '2') {
				sentidoThousand = 'd';
			}
			break;

		case '3':
			thousandX = c1 + 100 * glm::cos(glm::radians(giroThousand + 180));
			thousandZ = c2 + 100 * glm::sin(glm::radians(giroThousand + 180));
			giroThousand -= 0.3 * delta;

			if (giroThousand < -270.0 && sentidoThousand == '3') {
				sentidoThousand = 'r';
			}
			break;
		}

		//Control de giro
		if (thousandZ > 330.0f && sentidoThousand == 'u') {
			banderaCentro = true;
			sentidoThousand = '1';
		}

		if (thousandX > 100.0f && sentidoThousand == 'l') {
			banderaCentro = true;
			sentidoThousand = '2';
		}

		if (thousandZ < 0.0f && sentidoThousand == 'd') {
			banderaCentro = true;
			sentidoThousand = '3';
		}

		//Paramos el barco
		if (thousandX < -200.0f && sentidoThousand == 'r') {
			sentidoThousand = '4';
		}

		//Calculamos el centro
		calculaCentro();

	}


}

void animaLaboon(GLfloat delta) {

	if (comienzaAnimacionLaboon) {
		switch (sentidoLaboon) {
		case 'u':
			laboonX += velocidadLaboon * delta;

			if (anguloLaboon < 0.0f) {
				anguloLaboon += 0.1 * delta;
			}

			break;
		case 'd':
			laboonX -= velocidadLaboon * delta;

			if (anguloLaboon > -45.0f) {
				anguloLaboon -= 0.1 * delta;
			}

			break;
		}

		if (laboonX > -220.0f) {
			sentidoLaboon = 'd';
		}

		if (laboonX < -300.0f) {
			sentidoLaboon = 'u';
		}
	}
}

void keyFrameMetaKnight() {
	int i = 0;
	pMetaKnight.set(-170.0f, 20.0f, 200.0f, 0.0f);

	pMetaKnight.KeyFrame[i].x = -170.0f;
	pMetaKnight.KeyFrame[i].z = 200.0f;
	pMetaKnight.KeyFrame[i].giro = 0.0f;
	i++;

	pMetaKnight.KeyFrame[i].x = -170.0f;
	pMetaKnight.KeyFrame[i].z = 220.0f;
	pMetaKnight.KeyFrame[i].giro = 0.0f;
	i++;

	pMetaKnight.KeyFrame[i].x = -170.0f;
	pMetaKnight.KeyFrame[i].z = 300.0f;
	pMetaKnight.KeyFrame[i].giro = 45.0f;
	i++;

	pMetaKnight.FrameIndex = i;
}

void keyFrameDorry() {
	int i = 0;
	pDorry.set(40.0f, -2.0f, 0.0f, 180.0f);

	pDorry.KeyFrame[i].x = 40.0f;
	pDorry.KeyFrame[i].y = -2.0f;
	pDorry.KeyFrame[i].z = 0.0f;
	pDorry.KeyFrame[i].giro = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pDorry.KeyFrame[i].x = 40.0f;
	pDorry.KeyFrame[i].y = -2.0f;
	pDorry.KeyFrame[i].z = 0.0f;
	pDorry.KeyFrame[i].giro = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = -45.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 45.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = -45.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = -20.0f;

	i++;

	pDorry.FrameIndex = i;

}