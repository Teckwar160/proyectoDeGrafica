#include "Animaciones.h"

//Control de camaras
int cameraType = 1;
bool cameraFlag = false;

//Control de Frames
#define MAX_FRAMES 200
int i_max_steps = 200;
FRAME KeyFrameThousand[MAX_FRAMES];
float reproduciranimacion, habilitaranimacion;
bool animacion = false;
int FrameIndex = 18;//5;
int i_curr_steps;//5;
bool play = false;
int playIndex = 0;

//Variables para thousand
float thousandX = -170;
float thousandZ = 200;
float giroThousand = 0;
char sentidoThousand = 'u';
float velocidadThousand = 0.5;
bool  comienzaAnimacionThousand = false;
int c1 = 0, c2 = 0;
bool banderaCentro = false;

int getCameraType() {
	return cameraType;
}


void resetElements(FRAME *KeyFrame, float *x, float *z, float *giro)
{
	*x = KeyFrame[0].x;
	*z = KeyFrame[0].z;
	*giro = KeyFrame[0].giro;
}

void interpolation(FRAME *KeyFrame)
{
	KeyFrame[playIndex].incremento_x = (KeyFrame[playIndex + 1].x - KeyFrame[playIndex].x) / i_max_steps;
	KeyFrame[playIndex].incremento_z = (KeyFrame[playIndex + 1].z - KeyFrame[playIndex].z) / i_max_steps;
	KeyFrame[playIndex].incremento_giro = (KeyFrame[playIndex + 1].giro - KeyFrame[playIndex].giro) / i_max_steps;

}


void animate(FRAME *KeyFrame, float *x, float *z, float *giro)
{
	//Movimiento del objeto
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation(KeyFrame);
			}
		}
		else
		{
			//Draw animation
			*x += KeyFrame[playIndex].incremento_x;
			*z += KeyFrame[playIndex].incremento_z;
			*giro += KeyFrame[playIndex].incremento_giro;
			i_curr_steps++;

		}

	}
}



void controlDeTeclas(bool* keys, GLfloat delta) {

	if (keys[GLFW_KEY_SPACE])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				//resetElements(KeyFrameThousand,&thousandX,&thousandZ,&giroThousand);
				//First Interpolation				
				interpolation(KeyFrameThousand);
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\nPresiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;
			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1)
		{
			reproduciranimacion = 0;
		}
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
	if (keys[GLFW_KEY_L]) {
		comienzaAnimacionThousand = true;
	}
	
}

/*
void animaThousand(GLfloat delta) {
	int i = 0;

	KeyFrameThousand[i].x = -170.0f;
	KeyFrameThousand[i].z = 200.0f;
	KeyFrameThousand[i].giro = 180.0f;
	i++;

	KeyFrameThousand[i].x = -170.0f;
	KeyFrameThousand[i].z = 250.0f;
	KeyFrameThousand[i].giro = 180.0f;
	i++;

	KeyFrameThousand[i].x = -170.0f;
	KeyFrameThousand[i].z =  300.0f;
	KeyFrameThousand[i].giro = 180.0f;
	i++;

	KeyFrameThousand[i].x = -170.0f;
	KeyFrameThousand[i].z = 360.0f;
	KeyFrameThousand[i].giro = 180.0f;
	i++;

	//Giro
	KeyFrameThousand[i].x = -170.0f;
	KeyFrameThousand[i].z = 390.0f;
	KeyFrameThousand[i].giro = 225.0f;
	i++;

	
	KeyFrameThousand[i].x = -85.0f;
	KeyFrameThousand[i].z = 420.0f;
	KeyFrameThousand[i].giro = 270.0f;
	i++;

	KeyFrameThousand[i].x = 0.0f;
	KeyFrameThousand[i].z = 420.0f;
	KeyFrameThousand[i].giro = 270.0f;
	i++;

	//Siguiente tramo
	KeyFrameThousand[i].x = 50.0f;
	KeyFrameThousand[i].z = 420.0f;
	KeyFrameThousand[i].giro = 270.0f;
	i++;

	KeyFrameThousand[i].x = 100.0f;
	KeyFrameThousand[i].z = 420.0f;
	KeyFrameThousand[i].giro = 270.0f;
	i++; //8

	KeyFrameThousand[i].x = 200.0f;
	KeyFrameThousand[i].z = 420.0f;
	KeyFrameThousand[i].giro = 270.0f;
	i++; //9

	//Giro
	KeyFrameThousand[i].x = 200.0f;
	KeyFrameThousand[i].z = 380.0f;
	KeyFrameThousand[i].giro = 360.0f;
	i++; //10

	//Siguiente tramo
	KeyFrameThousand[i].x = 200.0f;
	KeyFrameThousand[i].z = 250.0f;
	KeyFrameThousand[i].giro = 360.0f;
	i++; //11

	KeyFrameThousand[i].x = 200.0f;
	KeyFrameThousand[i].z = 100.0f;
	KeyFrameThousand[i].giro = 360.0f;
	i++; //12

	KeyFrameThousand[i].x = 200.0f;
	KeyFrameThousand[i].z = 0.0f;
	KeyFrameThousand[i].giro = 360.0f;
	i++; //13

	//Giro
	KeyFrameThousand[i].x = 50.0f;
	KeyFrameThousand[i].z = -50.0f;
	KeyFrameThousand[i].giro = 450.0f;
	i++; //14

	KeyFrameThousand[i].x = 0.0f;
	KeyFrameThousand[i].z = -50.0f;
	KeyFrameThousand[i].giro = 450.0f;
	i++; //15

	KeyFrameThousand[i].x = -50.0f;
	KeyFrameThousand[i].z = -50.0f;
	KeyFrameThousand[i].giro = 450.0f;
	i++; //16

	//Siguitnete tramo
	KeyFrameThousand[i].x = -170.0f;
	KeyFrameThousand[i].z = -50.0f;
	KeyFrameThousand[i].giro = 450.0f;
	i++; //17

	animate(KeyFrameThousand,&thousandX,&thousandZ,&giroThousand);
}
*/

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