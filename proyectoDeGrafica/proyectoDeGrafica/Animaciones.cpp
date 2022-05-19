// Biblioteca
#include "Animaciones.h"

// Control de camaras
int cameraType = 1;

// Variables para el Thousand Sunny
float thousandX = -170.0f;
float thousandZ = 200.0f;
float giroThousand = 0;
char sentidoThousand = 'u';
float velocidadThousand = 0.5f;
bool  comienzaAnimacionThousand = false;
int c1 = 0, c2 = 0;
bool banderaCentro = false;

// Variables para Laboon
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

// Luces del volcan
glm::vec3 posicionesVolcan[3];
glm::vec3 posicionOrigenV = glm::vec3(-48.0f, 45.0f, 14.0f);
float radio = 10.0f;
glm::vec3 centros[3];
bool iniciaErupcionVolcan = false;
float anguloLava = 0.0f;
float rotacionLava = 0.0f; // x
bool volcanActivo = false;

// Fuegos artificiales
Firework fireworkRed = Firework(200, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 250.0f, -400.0f));
bool fireworkActivo = false;

// Bandera de activación del recorrido
bool comienzaRecorrido = false;
int steps = 0;
int rcam = 1;
GLfloat yawFinal, pitchFinal;
glm::vec3 posFinal;

// Ruptura de vela del barco
bool velaRota = false;

// Bandera para evitar el reseteo de la pelea de los gigantes
bool peleaActiva = false;

// Luces de la marina
bool lucesMarina = false;


// Función encargada de calcular la posición del volcán
void calculaPosicionesVolcan() {
	for (int i = 0; i < 3; i++) {
		posicionesVolcan[i] = posicionOrigenV;
	}
	centros[0] = glm::vec3(-48.0f, 45.0f, 14.0f + radio);
	centros[1] = glm::vec3(-48.0f + radio, 45.0f, 14.0f);
	centros[2] = glm::vec3(-48.0f - radio, 45.0f, 14.0f);

}

// Funciones de clase personaje
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

// Personajes
personaje pMetaKnight;
personaje pDorry;
personaje pBrogy;
personaje pCarue;
personaje pVivi;
personaje pZoro;
personaje pFranky;

// Función de camara
int getCameraType() {
	return cameraType;
}

// Funciones de KeyFrames
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

// Control de eventos con teclas
void controlDeTeclas(bool* keys) {

	// Luffy
	comienzaAnimacionLuffy = ((keys[GLFW_KEY_W] or keys[GLFW_KEY_A] or keys[GLFW_KEY_D] or keys[GLFW_KEY_S]) and cameraType == 1);

	// Ataque de Luffy
	if (keys[GLFW_KEY_G]) {
		ataqueEspecial = true;
		keyFrameMetaKnightFight();

		if (pMetaKnight.play == false && pMetaKnight.FrameIndex > 1) {
			resetElements(&pMetaKnight);
			interpolation(&pMetaKnight);
			pMetaKnight.reset();
		}

	} 

	// MetaKnight
	if (keys[GLFW_KEY_M]) {
		if (pMetaKnight.bandera) {
			if (pMetaKnight.play == false && pMetaKnight.FrameIndex > 1) {
				resetElements(&pMetaKnight);
				interpolation(&pMetaKnight);
				pMetaKnight.reset();
			}
		}

	}

	// Franky
	if (keys[GLFW_KEY_F]) {
		if (pFranky.bandera) {
			if (pFranky.play == false && pFranky.FrameIndex > 1) {
				resetElements(&pFranky);
				interpolation(&pFranky);
				pFranky.reset();
			}
		}

	}

	// Zoro
	if (keys[GLFW_KEY_Z]) {
		if (pZoro.bandera) {
			if (pZoro.play == false && pZoro.FrameIndex > 1) {
				resetElements(&pZoro);
				interpolation(&pZoro);
				pZoro.reset();
			}
		}
	}

	// Activador de animaciones por keyFrame
	if (keys[GLFW_KEY_K]) {
		pMetaKnight.bandera = true;
		pCarue.bandera = true;
		pVivi.bandera = true;
		pZoro.bandera = true;
		pFranky.bandera = true;
	}

	// Control de cámaras
	if (keys[GLFW_KEY_1]) { cameraType = 1; }
	if (keys[GLFW_KEY_2]) { cameraType = 2; }
	if (keys[GLFW_KEY_3]) { cameraType = 3; }

	// Control de animación de Thousand && Carue && Vivi
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

	// Control de animación de Laboon
	if (keys[GLFW_KEY_L]) {
		comienzaAnimacionLaboon = true;
	}

	// Activación del recorrido
	if (keys[GLFW_KEY_R]) {
		comienzaRecorrido = true;
	}

	// Control de luces
	if (keys[GLFW_KEY_4]) {
		lucesMarina = true;
	}

	if (keys[GLFW_KEY_5]) {
		lucesMarina = false;
	}

	
}

// Función encargada de calcular el centro sobre el cual rotara el Thousand
void calculaCentro(){

	// Calculamos el centro dependiendo de en donde esta el barco
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

		// Evitamos que se vuelva a calcular
		banderaCentro = false;
	}

}

void animaThousand(GLfloat delta) {

	// Condicional para evitar que la animación se active antes de tiempo
	if (comienzaAnimacionThousand) {

		// Control de movimiento
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

		// Control de giro
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

		// Paramos el barco
		if (thousandX < -200.0f && sentidoThousand == 'r') {
			sentidoThousand = '4';
		}

		// Calculamos el centro
		calculaCentro();

	}


}

void animaLaboon(GLfloat delta) {

	// Condicional para evitar que la animación empiece antes de tiempo
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

	// Condicional para evitar que la animación empiece antes de tiempo
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
	// Condicional para evitar que la animación comience antes de tiempo
	if (ataqueEspecial)
	{
		if (!golpe) {
			if (anguloBrazoR > -90.0f) anguloBrazoR -= 6.0 * delta;
			else if (escalaBrazo <= 40) escalaBrazo += 3.0 * delta;
			else golpe = true;
		}
		else {
			if (escalaBrazo > 1) escalaBrazo -= 3.0 * delta;
			else if (anguloBrazoR < 0.0f) {
				anguloBrazoR += 6.0 * delta;
				escalaBrazo = 1.0f;
			}
			else {
				ataqueEspecial = false;
				golpe = false;
			}
		}
	}
}

void animaLava(GLfloat delta) {

	// Condicional de control de la erupción del volcán
	if (iniciaErupcionVolcan or volcanActivo) {
		rotacionLava < 359 ? rotacionLava += 1.5 * delta : rotacionLava = 0.0f;

		if (anguloLava < 180.0) {
			posicionesVolcan[0].z = centros[0].z - radio * glm::cos(glm::radians(anguloLava));
			posicionesVolcan[0].y = centros[0].y + radio * glm::sin(glm::radians(anguloLava));

			posicionesVolcan[1].x = centros[1].x - radio * glm::cos(glm::radians(anguloLava));
			posicionesVolcan[1].y = centros[2].y + radio * glm::sin(glm::radians(anguloLava));

			posicionesVolcan[2].x = centros[2].x + radio * glm::cos(glm::radians(anguloLava));
			posicionesVolcan[2].y = centros[2].y + radio * glm::sin(glm::radians(anguloLava));

			anguloLava += 2.0 * delta;
		}
		else if (posicionesVolcan[0].y > 35.0) {
			posicionesVolcan[0].y -= 0.3 * delta;
			posicionesVolcan[1].y -= 0.3 * delta;
			posicionesVolcan[2].y -= 0.3 * delta;
			volcanActivo = true;

		}
		else if (posicionesVolcan[0].y > 20.0) {
			posicionesVolcan[0].y -= 0.08 * delta;
			posicionesVolcan[0].z += 0.08 * delta;

			posicionesVolcan[1].y -= 0.08 * delta;
			posicionesVolcan[1].x += 0.08 * delta;

			posicionesVolcan[2].y -= 0.08 * delta;
			posicionesVolcan[2].x -= 0.08 * delta;
		}
		else if (anguloLava < 300.0f) {	
			anguloLava += 2.0 * delta;
			rotacionLava -= 1.5 * delta;
		}
		else {
			volcanActivo = false;
			calculaPosicionesVolcan();
			anguloLava = 0.0f;
			rotacionLava = 0.0f;
		}
	}
}

void animaRecorrido(Camera* cam, GLfloat delta) {

	//Condicional para evitar que la animación comience antes de tiempo
	if (comienzaRecorrido) {
		cameraType = 2;

		switch (rcam)
		{
		case 1:
			posFinal = glm::vec3(-162.87, 19.85, 202.25);
			yawFinal = -162.0;
			pitchFinal = -8.0;
			break;

		case 2:
			posFinal = glm::vec3(-190.17, 29.92, 234.30);
			yawFinal = -24.50;
			pitchFinal = -9.50;
			break;

		case 3:
			posFinal = glm::vec3(-143.00, 151.54, -25.16);
			yawFinal = 45.0;
			pitchFinal = -41.0;
			break;

		case 4:

			posFinal = glm::vec3(-380.63, 92.45, 211.69);
			yawFinal = -64.0;
			pitchFinal = 11.0;
			break;

		default:
			rcam = 1;
			cameraType = 1;
			break;
		}

		if (steps < 1800) {
			cam->setYaw(cam->getYaw() + (yawFinal - cam->getYaw()) / 500.0f);
			cam->setPitch(cam->getPitch() + (pitchFinal - cam->getPitch()) / 500.0f);
			cam->setPosition(cam->getPosition() + (posFinal - cam->getPosition()) / 500.0f);
			steps++;
		}
		else {
			comienzaRecorrido = false;
			steps = 0;
			rcam++;
		}
	}
}

void keyFrameMetaKnight() {
	int i = 0;
	pMetaKnight.set(-60.0f, 61.8f, 240.0f, 0.0f, -90.0f, 0.0f);

	// Tramo de bajada
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
	pMetaKnight.KeyFrame[i].giroZ = 180.0f;
	i++;

	pMetaKnight.KeyFrame[i].x = -170.0f;
	pMetaKnight.KeyFrame[i].y = 21.3f;
	pMetaKnight.KeyFrame[i].z = 240.0f;
	pMetaKnight.KeyFrame[i].giroX = 0.0f;
	pMetaKnight.KeyFrame[i].giroY = -90.0f;
	pMetaKnight.KeyFrame[i].giroZ = 360.0f;
	i++;

	// Voltea hacia el barco
	pMetaKnight.KeyFrame[i].x = -170.0f;
	pMetaKnight.KeyFrame[i].y = 21.03f;
	pMetaKnight.KeyFrame[i].z = 240.0f;
	pMetaKnight.KeyFrame[i].giroX = 0.0f;
	pMetaKnight.KeyFrame[i].giroY = -180.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;

	// Comienza ataque
	pMetaKnight.KeyFrame[i].x = -170.0f;
	pMetaKnight.KeyFrame[i].y = 21.3f;
	pMetaKnight.KeyFrame[i].z = 240.0f;
	pMetaKnight.KeyFrame[i].giroX = -90.0f;
	pMetaKnight.KeyFrame[i].giroY = -540.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;

	pMetaKnight.KeyFrame[i].x = -170.0f;
	pMetaKnight.KeyFrame[i].y = 21.3f;
	pMetaKnight.KeyFrame[i].z = 195.0f;
	pMetaKnight.KeyFrame[i].giroX = -90.0f;
	pMetaKnight.KeyFrame[i].giroY = -900.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;

	// Se acomoda en pose
	pMetaKnight.KeyFrame[i].x = -160.0f;
	pMetaKnight.KeyFrame[i].y = 21.3f;
	pMetaKnight.KeyFrame[i].z = 195.0f;
	pMetaKnight.KeyFrame[i].giroX = 0.0f;
	pMetaKnight.KeyFrame[i].giroY = -810.0f;
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

	// Caminar
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

	// Ataque con espada
	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 0.0f;
	pDorry.KeyFrame[i].giroY = 225.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = -20.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = -45.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 45.0f;
	i++;

	// Defensa
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

	// Espera
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

	// Retirada
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

	// Espera
	pDorry.KeyFrame[i].x = 10.0f;
	pDorry.KeyFrame[i].y = 30.0f;
	pDorry.KeyFrame[i].z = 20.0f;
	pDorry.KeyFrame[i].giroY = 180.0f;
	pDorry.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pDorry.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pDorry.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	// Saludo
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

	// Regreso
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

	// Caminar
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

	// Espera
	pBrogy.KeyFrame[i].x = 0.0f;
	pBrogy.KeyFrame[i].y = 30.0f;
	pBrogy.KeyFrame[i].z = -40.0f;
	pBrogy.KeyFrame[i].giroY = -45.0f;
	pBrogy.KeyFrame[i].anguloBrazoDerecho = -20.0f;
	pBrogy.KeyFrame[i].anguloBrazoIzquierdo = 90.0f;
	pBrogy.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pBrogy.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	// Contra ataque
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

	// Retirada
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

	// Saludo
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

	// Regreso
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

	// Recorrido de carue
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

	// Espera
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

	// Regreso
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

	// Entra al bosque
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

	// Saludo de Vivi
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

	// Despedida más alegre
	pVivi.KeyFrame[i].anguloBrazoDerecho = 135.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 135.0f;
	i++;

	pVivi.KeyFrame[i].anguloBrazoDerecho = 45.0f;
	i++;

	// Fin de saludo
	pVivi.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	i++;

	pVivi.FrameIndex = i;
}

void keyFrameZoro() {
	int i = 0;

	pZoro.set(-1.0f, 10.2f, -3.5f, -90.0f, 0.0f, 0.0f);

	// Acostado
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

	// Se levanta
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

	// Pasito hacia atras
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

	// Brinco
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

	// Agachada
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

	// Brinco
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

	// Agachada
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

	// Pasito hacia enfrente
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

	// Sentarse
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

	// Saludo a Luffy
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


	// Se acuesta
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

void iniciaPelea() {
	if (volcanActivo && !peleaActiva) {
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

		pDorry.bandera = true;
		pBrogy.bandera = true;
		peleaActiva = true;

	}
	else if(!volcanActivo) {
		peleaActiva = false;
	}
}

void keyFrameFranky() {
	int i = 0;

	pFranky.set(-1.5f, 13.7f, 5.0f, 0.0f, 0.0f, 0.0f);

	pFranky.KeyFrame[i].x = -1.5f;
	pFranky.KeyFrame[i].y = 13.7f;
	pFranky.KeyFrame[i].z = 5.0f;
	pFranky.KeyFrame[i].giroY = 0.0f;
	pFranky.KeyFrame[i].anguloBrazoDerecho = 0.0f;
	pFranky.KeyFrame[i].anguloBrazoIzquierdo = 0.0f;
	pFranky.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pFranky.KeyFrame[i].anguloPiernaIzquierda = 0.0f;
	i++;

	// Giro
	pFranky.KeyFrame[i].x = -1.5f;
	pFranky.KeyFrame[i].y = 13.7f;
	pFranky.KeyFrame[i].z = 5.0f;
	pFranky.KeyFrame[i].giroY = 180.0f;
	pFranky.KeyFrame[i].anguloBrazoDerecho = 0;
	pFranky.KeyFrame[i].anguloBrazoIzquierdo = 0;
	pFranky.KeyFrame[i].anguloPiernaDerecha = 45.0f;
	pFranky.KeyFrame[i].anguloPiernaIzquierda = -45.0f;
	i++;

	// Brinco
	pFranky.KeyFrame[i].x = -1.5f;
	pFranky.KeyFrame[i].y = 15.7f;
	pFranky.KeyFrame[i].z = 5.0f;
	pFranky.KeyFrame[i].giroY = 180.0f;
	pFranky.KeyFrame[i].anguloBrazoDerecho = 180;
	pFranky.KeyFrame[i].anguloBrazoIzquierdo = 0;
	pFranky.KeyFrame[i].anguloPiernaDerecha = 0;
	pFranky.KeyFrame[i].anguloPiernaIzquierda = 0;
	i++;

	pFranky.KeyFrame[i].x = -1.5f;
	pFranky.KeyFrame[i].y = 17.7f;
	pFranky.KeyFrame[i].z = 5.0f;
	pFranky.KeyFrame[i].giroY = 180.0f;
	pFranky.KeyFrame[i].anguloBrazoDerecho = 135;
	pFranky.KeyFrame[i].anguloBrazoIzquierdo = 0;
	pFranky.KeyFrame[i].anguloPiernaDerecha = 0;
	pFranky.KeyFrame[i].anguloPiernaIzquierda = 0;
	i++;

	pFranky.KeyFrame[i].x = -1.5f;
	pFranky.KeyFrame[i].y = 15.7f;
	pFranky.KeyFrame[i].z = 5.0f;
	pFranky.KeyFrame[i].giroY = 180.0f;
	pFranky.KeyFrame[i].anguloBrazoDerecho = 90;
	pFranky.KeyFrame[i].anguloBrazoIzquierdo = 0;
	pFranky.KeyFrame[i].anguloPiernaDerecha = 0;
	pFranky.KeyFrame[i].anguloPiernaIzquierda = 0;
	i++;

	pFranky.KeyFrame[i].x = -1.5f;
	pFranky.KeyFrame[i].y = 13.7f;
	pFranky.KeyFrame[i].z = 5.0f;
	pFranky.KeyFrame[i].giroY = 180.0f;
	pFranky.KeyFrame[i].anguloBrazoDerecho = 0;
	pFranky.KeyFrame[i].anguloBrazoIzquierdo = 0;
	pFranky.KeyFrame[i].anguloPiernaDerecha = 0;
	pFranky.KeyFrame[i].anguloPiernaIzquierda = 0;
	i++;

	// Giro
	pFranky.KeyFrame[i].x = -1.5f;
	pFranky.KeyFrame[i].y = 13.7f;
	pFranky.KeyFrame[i].z = 5.0f;
	pFranky.KeyFrame[i].giroY = 180.0f;
	pFranky.KeyFrame[i].anguloBrazoDerecho = 0;
	pFranky.KeyFrame[i].anguloBrazoIzquierdo = 0;
	pFranky.KeyFrame[i].anguloPiernaDerecha = -45.0f;
	pFranky.KeyFrame[i].anguloPiernaIzquierda = 45.0f;
	i++;

	pFranky.KeyFrame[i].x = -1.5f;
	pFranky.KeyFrame[i].y = 13.7f;
	pFranky.KeyFrame[i].z = 5.0f;
	pFranky.KeyFrame[i].giroY = 0.0f;
	pFranky.KeyFrame[i].anguloBrazoDerecho = 0;
	pFranky.KeyFrame[i].anguloBrazoIzquierdo = 0;
	pFranky.KeyFrame[i].anguloPiernaDerecha = 0.0f;
	pFranky.KeyFrame[i].anguloPiernaIzquierda = .0f;
	i++;

	pFranky.FrameIndex = i;
}

void keyFrameMetaKnightFight() {
	int i = 0;

	pMetaKnight.KeyFrame[i].x = -160.0f;
	pMetaKnight.KeyFrame[i].y = 21.3f;
	pMetaKnight.KeyFrame[i].z = 195.0f;
	pMetaKnight.KeyFrame[i].giroX = 0.0f;
	pMetaKnight.KeyFrame[i].giroY = -810.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;

	pMetaKnight.KeyFrame[i].x = -60.0f;
	pMetaKnight.KeyFrame[i].y = 40.0f;
	pMetaKnight.KeyFrame[i].z = 150.0f;
	pMetaKnight.KeyFrame[i].giroX = 360.0f;
	pMetaKnight.KeyFrame[i].giroY = -810.0f;
	pMetaKnight.KeyFrame[i].giroZ = 0.0f;
	i++;

	pMetaKnight.FrameIndex = i;

}

void iniciaShow(bool day) {
	if (!day && !fireworkRed.getComienzaAnimacionFirework()) {
		fireworkRed.reset();
		fireworkRed.start();
	}
}