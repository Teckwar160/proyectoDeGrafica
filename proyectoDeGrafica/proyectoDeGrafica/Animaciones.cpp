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

//Variables para Meta Knight
FRAME KeyFrameMetaKnight[MAX_FRAMES];
float metaKnightX = -170;
float metaKnightZ = 200;
float giroMetaKnight = 0;
int iCSMetaKnight = 0;
int fIMetaKnight = 0;// = 18;//5;
int iMSMetaKnight = 200;
int pIMetaKnight = 0;
bool comienzaAnimacionMetaKnight = false;
bool banderaMetaKnight = true;


int getCameraType() {
	return cameraType;
}


void resetElements(FRAME *KeyFrame, float *x, float* z, float* giro)
{
	*x = KeyFrame[0].x;
	*z = KeyFrame[0].z;
	*giro = KeyFrame[0].giro;
}

void interpolation(FRAME *KeyFrame, int i_max_steps, int playIndex)
{
	KeyFrame[playIndex].incremento_x = (KeyFrame[playIndex + 1].x - KeyFrame[playIndex].x) / i_max_steps;
	KeyFrame[playIndex].incremento_z = (KeyFrame[playIndex + 1].z - KeyFrame[playIndex].z) / i_max_steps;
	KeyFrame[playIndex].incremento_giro = (KeyFrame[playIndex + 1].giro - KeyFrame[playIndex].giro) / i_max_steps;

}


void animate(FRAME* KeyFrame, float* x, float* z, float* giro, int* i_curr_steps, int i_max_steps, int *playIndex, int FrameIndex, bool *play) {
	if (*play) {
		if (*i_curr_steps >= i_max_steps) {
			(*playIndex)++;

			if (*playIndex > FrameIndex - 2) {
				*playIndex = 0;
				*play = false;
			}
			else {
				*i_curr_steps = 0;
				interpolation(KeyFrame, i_max_steps, *playIndex);
			}
		}
		else {
			*x += KeyFrame[*playIndex].incremento_x;
			*z += KeyFrame[*playIndex].incremento_z;
			*giro += KeyFrame[*playIndex].incremento_giro;
			(*i_curr_steps)++;
		}
	}
}

void controlDeTeclas(bool* keys, GLfloat delta) {
	//Meta Knight
	if (keys[GLFW_KEY_M]) {
		if (banderaMetaKnight) {
			if (comienzaAnimacionMetaKnight == false && fIMetaKnight > 1) {
				resetElements(KeyFrameMetaKnight, &metaKnightX, &metaKnightZ, &giroMetaKnight);

				interpolation(KeyFrameMetaKnight, iMSMetaKnight, pIMetaKnight);
				comienzaAnimacionMetaKnight = true;
				pIMetaKnight = 0;
				iCSMetaKnight = 0;
				banderaMetaKnight = false;
			}
		}

	}

	if (keys[GLFW_KEY_K]) {
		banderaMetaKnight = true;
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
			c1 = thousandX + 100; //x
			c2 = thousandZ;	 //y
			//sentidoThousand = '1';
		}

		if (sentidoThousand == '2') {
			c1 = thousandX; //x
			c2 = thousandZ - 100;	 //y
		}

		if (sentidoThousand == '3') {
			c1 = thousandX -100; //x
			c2 = thousandZ;	 //y
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

	//0
	KeyFrameMetaKnight[0].x = -170.0f;
	KeyFrameMetaKnight[0].z = 200.0f;
	KeyFrameMetaKnight[0].giro = 0.0f;
	i++;

	//1
	KeyFrameMetaKnight[i].x = -170.0f;
	KeyFrameMetaKnight[i].z = 220.0f;
	KeyFrameMetaKnight[i].giro = 0.0f;
	i++;

	//2
	KeyFrameMetaKnight[i].x = -170.0f;
	KeyFrameMetaKnight[i].z = 300.0f;
	KeyFrameMetaKnight[i].giro = 45.0f;
	i++;

	fIMetaKnight = i;
}