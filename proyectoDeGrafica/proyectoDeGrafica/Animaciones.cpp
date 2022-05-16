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

// Variables Luffy
float anguloBrazoR = 0.0f;
float anguloBrazoL = 0.0f;
float anguloPiernaR = 0.0f;
float anguloPiernaL = 0.0f;
float escalaBrazo = 1.0f;
bool ataqueEspecial = false;
bool golpe = false;
bool comienzaAnimacionLuffy = false;
bool alto = false;
bool paso = false;
bool mediopaso = false;


//Funciones de clase personaje
void personaje::reset() {
	this->play = true;
	this->playIndex = 0;
	this->i_curr_steps = 0;
	this->bandera = false;
}

void personaje::set(float x, float y, float z, float giroX, float giroY, float giroZ) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->giroX = giroX;
	this->giroY = giroY;
	this->giroZ = giroZ;
}

//Personajes
personaje pMetaKnight;
personaje pDorry;
personaje pBrogy;
personaje pCarue;
personaje pVivi;
personaje pZoro;

int getCameraType() {
	return cameraType;
}

void resetElements(personaje* p)
{
	p-> x = p-> KeyFrame[0].x;
	p->y = p->KeyFrame[0].y;
	p-> z = p-> KeyFrame[0].z;
	p-> giroX = p-> KeyFrame[0].giroX;
	p->giroY = p->KeyFrame[0].giroY;
	p->giroZ = p->KeyFrame[0].giroZ;
	p->anguloBrazoDerecho = p->KeyFrame[0].anguloBrazoDerecho;
	p->anguloBrazoIzquierdo = p->KeyFrame[0].anguloBrazoIzquierdo;
	p->anguloPiernaDerecha = p->KeyFrame[0].anguloPiernaDerecha;
	p->anguloPiernaIzquierda = p->KeyFrame[0].anguloPiernaIzquierda;

}

void interpolation(personaje* p)
{
	p-> KeyFrame[p-> playIndex].incremento_x = (p-> KeyFrame[p-> playIndex + 1].x - p-> KeyFrame[p-> playIndex].x) / p-> i_max_steps;
	p->KeyFrame[p->playIndex].incremento_y = (p->KeyFrame[p->playIndex + 1].y - p->KeyFrame[p->playIndex].y) / p->i_max_steps;
	p-> KeyFrame[p-> playIndex].incremento_z = (p-> KeyFrame[p-> playIndex + 1].z - p-> KeyFrame[p-> playIndex].z) / p-> i_max_steps;
	p->KeyFrame[p->playIndex].incremento_giroX = (p->KeyFrame[p->playIndex + 1].giroX - p->KeyFrame[p->playIndex].giroX) / p->i_max_steps;
	p->KeyFrame[p->playIndex].incremento_giroY = (p->KeyFrame[p->playIndex + 1].giroY - p->KeyFrame[p->playIndex].giroY) / p->i_max_steps;
	p-> KeyFrame[p-> playIndex].incremento_giroZ = (p-> KeyFrame[p-> playIndex + 1].giroZ - p-> KeyFrame[p-> playIndex].giroZ) / p-> i_max_steps;
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
			p->y += p->KeyFrame[p->playIndex].incremento_y;
			p->z += p->KeyFrame[p -> playIndex].incremento_z;
			p->giroX += p->KeyFrame[ p-> playIndex].incremento_giroX;
			p->giroY += p->KeyFrame[p->playIndex].incremento_giroY;
			p->giroZ += p->KeyFrame[p->playIndex].incremento_giroZ;
			p->anguloBrazoDerecho += p->KeyFrame[p->playIndex].incremento_anguloBrazoDerecho;
			p->anguloBrazoIzquierdo += p->KeyFrame[p->playIndex].incremento_anguloBrazoIzquierdo;
			p->anguloPiernaDerecha += p->KeyFrame[p->playIndex].incremento_anguloPiernaDerecha;
			p->anguloPiernaIzquierda += p->KeyFrame[p->playIndex].incremento_anguloPiernaIzquierda;

			(p-> i_curr_steps)++;
		}
	}
}

void controlDeTeclas(bool* keys, GLfloat delta) {

	// Luffy
	comienzaAnimacionLuffy = keys[GLFW_KEY_W] and cameraType == 1;

	// Ataque de Luffy
	if (keys[GLFW_KEY_G]) ataqueEspecial = true;

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

	//Dorry && Brogy
	if (keys[GLFW_KEY_O]) {
		if (pDorry.bandera) {
			if (pDorry.play == false && pDorry.FrameIndex > 1) {
				resetElements(&pDorry);
				interpolation(&pDorry);
				pDorry.reset();
			}
		}

		if (pBrogy.bandera) {
			if (pBrogy.play == false && pBrogy.FrameIndex > 1) {
				resetElements(&pBrogy);
				interpolation(&pBrogy);
				pBrogy.reset();
			}
		}

	}

	if (keys[GLFW_KEY_Z]) {
		if (pZoro.bandera) {
			if (pZoro.play == false && pZoro.FrameIndex > 1) {
				resetElements(&pZoro);
				interpolation(&pZoro);
				pZoro.reset();
			}
		}
	}

	//Activador de animaciones por keyFrame
	if (keys[GLFW_KEY_K]) {
		pMetaKnight.bandera = true;
		pDorry.bandera = true;
		pBrogy.bandera = true;
		pCarue.bandera = true;
		pVivi.bandera = true;
		pZoro.bandera = true;
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

	//Control de animación de Thousand && Carue && Vivi
	if (keys[GLFW_KEY_T]) {

		comienzaAnimacionThousand = true;

		if (pCarue.bandera) {
			if (pCarue.play == false && pCarue.FrameIndex > 1) {
				resetElements(&pCarue);
				interpolation(&pCarue);
				pCarue.reset();
			}
		}

		if (pVivi.bandera) {
			if (pVivi.play == false && pVivi.FrameIndex > 1) {
				resetElements(&pVivi);
				interpolation(&pVivi);
				pVivi.reset();
			}
		}

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

void animaLuffy(GLfloat delta) {
	if (comienzaAnimacionLuffy or !alto) {
		if (!paso) {
			alto = false;
			if (!mediopaso) {
				if (anguloBrazoL < 45.0f) {
					anguloBrazoL++;
					anguloPiernaR++;
					anguloPiernaL--;
					if (!ataqueEspecial) anguloBrazoR = -anguloBrazoL;
				}
				else mediopaso = true;
			}
			else {
				if (anguloBrazoL > 0.0f) {
					anguloBrazoL--;
					anguloPiernaR--;
					anguloPiernaL++;
					if (!ataqueEspecial) anguloBrazoR = -anguloBrazoL;
				}
				else {
					mediopaso = false;
					paso = true;
					alto = true;
				}
			}
		}
		else {
			alto = false;
			if (!mediopaso) {
				if (anguloBrazoL > -45.0f) {
					anguloBrazoL--;
					anguloPiernaR--;
					anguloPiernaL++;
					if (!ataqueEspecial) anguloBrazoR = -anguloBrazoL;
				}
				else mediopaso = true;
			}
			else {
				if (anguloBrazoL < 0.0f) {
					anguloBrazoL++;
					anguloPiernaR++;
					anguloPiernaL--;
					if (!ataqueEspecial) anguloBrazoR = -anguloBrazoL;
				}
				else {
					mediopaso = false;
					paso = false;
					alto = true;
				}
			}
		}
	}
}

void animaAtaqueLuffy(GLfloat delta)
{
	if (ataqueEspecial)
	{
		if (!golpe) {
			if (anguloBrazoR > -90.0f) anguloBrazoR--;
			else if (escalaBrazo <= 40) escalaBrazo += 2.5 * delta;
			else golpe = true;
		}
		else {
			if (escalaBrazo > 1) escalaBrazo -= 2.5 * delta;
			else if (anguloBrazoR < 0.0f) anguloBrazoR++;
			else {
				ataqueEspecial = false;
				golpe = false;
			}
		}
	}
}

void keyFrameMetaKnight() {
	int i = 0;
	pMetaKnight.set(-60.0f, 61.8f, 240.0f, 0.0f, -90.0f, 0.0f);

	//Tramo de bajada
	pMetaKnight.KeyFrame[i].x = -60.0f;
	pMetaKnight.KeyFrame[i].y = 61.8f;
	pMetaKnight.KeyFrame[i].z = 240.0f;
	pMetaKnight.KeyFrame[i].giroX = 0.0f;
	pMetaKnight.KeyFrame[i].giroY = -90.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;

	pMetaKnight.KeyFrame[i].x = -115.0f;
	pMetaKnight.KeyFrame[i].y = 40.25f;
	pMetaKnight.KeyFrame[i].z = 240.0f;
	pMetaKnight.KeyFrame[i].giroX = 0.0f;
	pMetaKnight.KeyFrame[i].giroY = -90.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;

	pMetaKnight.KeyFrame[i].x = -170.0f;
	pMetaKnight.KeyFrame[i].y = 21.3f;
	pMetaKnight.KeyFrame[i].z = 240.0f;
	pMetaKnight.KeyFrame[i].giroX = 0.0f;
	pMetaKnight.KeyFrame[i].giroY = -90.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;

	//Voltea hacia el barco
	pMetaKnight.KeyFrame[i].x = -170.0f;
	pMetaKnight.KeyFrame[i].y = 21.03f;
	pMetaKnight.KeyFrame[i].z = 240.0f;
	pMetaKnight.KeyFrame[i].giroX = 0.0f;
	pMetaKnight.KeyFrame[i].giroY = -180.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;

	//Comienza ataque
	pMetaKnight.KeyFrame[i].x = -170.0f;
	pMetaKnight.KeyFrame[i].y = 21.3f;
	pMetaKnight.KeyFrame[i].z = 240.0f;
	pMetaKnight.KeyFrame[i].giroX = -90.0f;
	pMetaKnight.KeyFrame[i].giroY = -180.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;

	pMetaKnight.KeyFrame[i].x = -170.0f;
	pMetaKnight.KeyFrame[i].y = 21.3f;
	pMetaKnight.KeyFrame[i].z = 195.0f;
	pMetaKnight.KeyFrame[i].giroX = -90.0f;
	pMetaKnight.KeyFrame[i].giroY = -360.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;

	//Se acomoda en pose
	pMetaKnight.KeyFrame[i].x = -160.0f;
	pMetaKnight.KeyFrame[i].y = 21.3f;
	pMetaKnight.KeyFrame[i].z = 195.0f;
	pMetaKnight.KeyFrame[i].giroX = 0.0f;
	pMetaKnight.KeyFrame[i].giroY = -90.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;


	pMetaKnight.FrameIndex = i;
}

void keyFrameDorry() {
	int i = 0;
	pDorry.set(10.0f, 30.0f, 60.0f, 0.0f, 180.0f, 0.0f);

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 60.0f;
	pDorry.KeyFrame[i].giroY = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Caminar
	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 40.0f;
	pDorry.KeyFrame[i].giroY = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = -45.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 45.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = -45.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 45.0f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 20.0f;
	pDorry.KeyFrame[i].giroY = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = -45.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 45.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = -45.0f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 40.0f;
	pDorry.KeyFrame[i].z = 0.0f;
	pDorry.KeyFrame[i].giroY = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 90.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Ataque con espada
	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 0.0f;
	pDorry.KeyFrame[i].giroY = 225.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = -20.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = -45.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 45.0f;
	i++;

	//Defensa
	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 10.0f;
	pDorry.KeyFrame[i].giroY = 225.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 67.5f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 0.0f;
	pDorry.KeyFrame[i].giroY = 135.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = -20.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 60.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 22.5f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = -22.5f;
	i++;

	//Espera
	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 0.0f;
	pDorry.KeyFrame[i].giroY = 135.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = -20.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 60.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 0.0f;
	pDorry.KeyFrame[i].giroY = 135.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = -20.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 60.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Retirada
	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 0.0f;
	pDorry.KeyFrame[i].giroY = 135.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = -20.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 82.5f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 10.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = -22.5f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 20.0f;
	pDorry.KeyFrame[i].giroY = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Espera
	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 20.0f;
	pDorry.KeyFrame[i].giroY = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Saludo
	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 28.0f;
	pDorry.KeyFrame[i].z = 20.0f;
	pDorry.KeyFrame[i].giroX = 22.5f;
	pDorry.KeyFrame[i].giroY = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 22.5f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 22.5f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 20.0f;
	pDorry.KeyFrame[i].giroX = 0.0f;
	pDorry.KeyFrame[i].giroY = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Regreso
	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 20.0f;
	pDorry.KeyFrame[i].giroX = 0.0f;
	pDorry.KeyFrame[i].giroY = 90.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 45.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = -45.0f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 20.0f;
	pDorry.KeyFrame[i].giroX = 0.0f;
	pDorry.KeyFrame[i].giroY = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 40.0f;
	pDorry.KeyFrame[i].giroX = 0.0f;
	pDorry.KeyFrame[i].giroY = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = -45.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 45.0f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 60.0f;
	pDorry.KeyFrame[i].giroX = 0.0f;
	pDorry.KeyFrame[i].giroY = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 45.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = -45.0f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 60.0f;
	pDorry.KeyFrame[i].giroX = 0.0f;
	pDorry.KeyFrame[i].giroY = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 60.0f;
	pDorry.KeyFrame[i].giroX = 0.0f;
	pDorry.KeyFrame[i].giroY = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 45.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = -45.0f;
	i++;

	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 60.0f;
	pDorry.KeyFrame[i].giroX = 0.0f;
	pDorry.KeyFrame[i].giroY = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pDorry.FrameIndex = i;

}

void keyFrameBrogy() {
	int i = 0;

	pBrogy.set(0.0f, 30.0f, -100.0f, 0.0f, 0.0f, 0.0f); 

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -100.0f;
	pBrogy.KeyFrame[i].giroY = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Caminar
	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -80.0f;
	pBrogy.KeyFrame[i].giroY = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = -45.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 45.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = -45.0f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -60.0f;
	pBrogy.KeyFrame[i].giroY = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = -45.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 45.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = -45.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 45.0f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroY = -45.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = -20.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 90.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Espera
	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroY = -45.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = -20.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 90.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Contra ataque
	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroY = -45.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = -20.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 112.5f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 45.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = -45.0f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -50.0f;
	pBrogy.KeyFrame[i].giroY = 45.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 112.5f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = -45.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 45.0f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 40.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroY = 45.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 90.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = -20.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 45.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = -45.0f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroY = 45.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = -20.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Retirada
	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroY = 45.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 67.5f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = -20.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroY = 45.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 67.5f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = -20.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = -22.5f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 10.0f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroY = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Saludo
	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 28.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroX = 22.5f;
	pBrogy.KeyFrame[i].giroY = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 22.5f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 22.5f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroX = 0.0f;
	pBrogy.KeyFrame[i].giroY = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Regreso
	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroX = 0.0f;
	pBrogy.KeyFrame[i].giroY = 90.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = -45.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 45.0f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroX = 0.0f;
	pBrogy.KeyFrame[i].giroY = 180.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -60.0f;
	pBrogy.KeyFrame[i].giroX = 0.0f;
	pBrogy.KeyFrame[i].giroY = 180.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = -45.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 45.0f;
	i++;
	
	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -80.0f;
	pBrogy.KeyFrame[i].giroX = 0.0f;
	pBrogy.KeyFrame[i].giroY = 180.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 45.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = -45.0f;
	i++;
	
	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -100.0f;
	pBrogy.KeyFrame[i].giroX = 0.0f;
	pBrogy.KeyFrame[i].giroY = 180.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -100.0f;
	pBrogy.KeyFrame[i].giroX = 0.0f;
	pBrogy.KeyFrame[i].giroY = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 45.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = -45.0f;
	i++;

	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -100.0f;
	pBrogy.KeyFrame[i].giroX = 0.0f;
	pBrogy.KeyFrame[i].giroY = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;


	pBrogy.FrameIndex = i;
}

void keyFrameCarue() {
	int i = 0;

	pCarue.set(-148.0f, 6.9f, 5.0f, 0.0f, 0.0f, 0.0f);

	//Recorrido de carue
	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 5.0f;
	pCarue.KeyFrame[i].giroY = 0;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 0;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = 0;
	i++;

	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 25.0f;
	pCarue.KeyFrame[i].giroY = 0;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = -30.0f;
	i++;

	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 45.0f;
	pCarue.KeyFrame[i].giroY = 0;
	pCarue.KeyFrame[i].anguloPiernaDerecha = -30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = 30.0f;
	i++;

	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 65.0f;
	pCarue.KeyFrame[i].giroY = 0;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = -30.0f;
	i++;

	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 85.0f;
	pCarue.KeyFrame[i].giroY = 0;
	pCarue.KeyFrame[i].anguloPiernaDerecha = -30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = 30.0f;
	i++;

	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 85.0f;
	pCarue.KeyFrame[i].giroY = 0;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Espera
	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 85.0f;
	pCarue.KeyFrame[i].giroY = 0;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 85.0f;
	pCarue.KeyFrame[i].giroY = 0;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 85.0f;
	pCarue.KeyFrame[i].giroY = 0;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Regreso
	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 85.0f;
	pCarue.KeyFrame[i].giroY = -180;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = -30.0f;
	i++;

	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 65.0f;
	pCarue.KeyFrame[i].giroY = -180;
	pCarue.KeyFrame[i].anguloPiernaDerecha = -30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = 30.0f;
	i++;

	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 45.0f;
	pCarue.KeyFrame[i].giroY = -180;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = -30.0f;
	i++;

	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 25.0f;
	pCarue.KeyFrame[i].giroY = -180;
	pCarue.KeyFrame[i].anguloPiernaDerecha = -30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = 30.0f;
	i++;

	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 5.0f;
	pCarue.KeyFrame[i].giroY = -180;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = -30.0f;
	i++;

	//Entra al bosque
	pCarue.KeyFrame[i].x = -148.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 5.0f;
	pCarue.KeyFrame[i].giroY = -90;
	pCarue.KeyFrame[i].anguloPiernaDerecha = -30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = 30.0f;
	i++;

	pCarue.KeyFrame[i].x = -128.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 5.0f;
	pCarue.KeyFrame[i].giroY = -90;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = -30.0f;
	i++;

	pCarue.KeyFrame[i].x = -108.0f;
	pCarue.KeyFrame[i].y = 6.9f;
	pCarue.KeyFrame[i].z = 5.0f;
	pCarue.KeyFrame[i].giroY = -90;
	pCarue.KeyFrame[i].anguloPiernaDerecha = 30.0f;
	pCarue.KeyFrame[i].anguloPiernaIzquierda = -30.0f;
	i++;

	pCarue.FrameIndex = i;
}

void keyFrameVivi() {
	int i = 0;

	pVivi.set(0.0f, 0.8f, -0.5f, 0.0f, 0.0f, 0.0f);

	//Saludo de Vivi
	pVivi.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 90.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 90.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 90.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 90.0f;
	i++;

	//Despedida más alegre
	pVivi.KeyFrame[i].anguloBrazoDerecho = 135.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 135.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	i++;

	//Fin de saludo
	pVivi.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	i++;

	pVivi.FrameIndex = i;

}

void keyFrameZoro() {
	int i = 0;

	pZoro.set(-1.0f, 10.2f, -3.5f, -90.0f, 0.0f, 0.0f);

	//Acostado
	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 10.2f;
	pZoro.KeyFrame[i].z = -3.5f;
	pZoro.KeyFrame[i].giroX = -90.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Se levanta
	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 10.7f;
	pZoro.KeyFrame[i].z = -3.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 90.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 90.0f;
	i++;

	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 11.2f;
	pZoro.KeyFrame[i].z = -3.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Pasito hacia atras
	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 11.2f;
	pZoro.KeyFrame[i].z = -4.0f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 10.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = -22.5f;
	i++;

	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 11.2f;
	pZoro.KeyFrame[i].z = -4.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Brinco
	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 12.2f;
	pZoro.KeyFrame[i].z = -4.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 180.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 180.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 11.2f;
	pZoro.KeyFrame[i].z = -4.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Agachada
	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 10.7f;
	pZoro.KeyFrame[i].z = -4.3f;
	pZoro.KeyFrame[i].giroX = 90.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 90.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 90.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 90.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 90.0f;
	i++;

	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 11.2f;
	pZoro.KeyFrame[i].z = -4.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Brinco
	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 12.2f;
	pZoro.KeyFrame[i].z = -4.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 180.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 180.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 11.2f;
	pZoro.KeyFrame[i].z = -4.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Agachada
	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 10.7f;
	pZoro.KeyFrame[i].z = -4.3f;
	pZoro.KeyFrame[i].giroX = 90.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 90.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 90.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 90.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 90.0f;
	i++;

	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 11.2f;
	pZoro.KeyFrame[i].z = -4.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Pasito hacia enfrente
	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 11.2f;
	pZoro.KeyFrame[i].z = -4.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 22.5f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = -10.0f;
	i++;

	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 11.2f;
	pZoro.KeyFrame[i].z = -4.0f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	//Sentarse
	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 10.7f;
	pZoro.KeyFrame[i].z = -3.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 90.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 90.0f;
	i++;

	//Saludo a Luffy
	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 10.7f;
	pZoro.KeyFrame[i].z = -3.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 135.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 90.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 90.0f;
	i++;

	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 10.7f;
	pZoro.KeyFrame[i].z = -3.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 90.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 90.0f;
	i++;

	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 10.7f;
	pZoro.KeyFrame[i].z = -3.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 135.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 90.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 90.0f;
	i++;

	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 10.7f;
	pZoro.KeyFrame[i].z = -3.5f;
	pZoro.KeyFrame[i].giroX = 0.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 90.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 90.0f;
	i++;


	//Se acuesta
	pZoro.KeyFrame[i].x = -1.0f;
	pZoro.KeyFrame[i].y = 10.2f;
	pZoro.KeyFrame[i].z = -3.5f;
	pZoro.KeyFrame[i].giroX = -90.0f;
	pZoro.KeyFrame[i].giroY = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pZoro.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pZoro.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	pZoro.FrameIndex = i;
}