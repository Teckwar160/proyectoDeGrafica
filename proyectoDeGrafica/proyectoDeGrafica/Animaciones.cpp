#include "Animaciones.h"




#define MAX_FRAMES 200
int i_max_steps = 200;
int i_curr_steps = 4;

float thousandX = 0;
float thousandZ = 0;
float giroThousand = 180;
FRAME KeyFrameThousand[MAX_FRAMES];
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;


bool animacion = false;



//NEW// Keyframes

int i = 0;




int FrameIndex = 4;			//introducir datos
bool play = false;
int playIndex = 0;

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
				resetElements(KeyFrameThousand,&thousandX,&thousandZ,&giroThousand);
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
}



void animaThousand(GLfloat delta) {

	KeyFrameThousand[0].z = -300.0f;
	KeyFrameThousand[0].x = 0.0f;
	KeyFrameThousand[0].giro = 180.0f;

	KeyFrameThousand[1].z = 600.0f;
	KeyFrameThousand[1].x = 0.0f;
	KeyFrameThousand[1].giro = 180.0f;

	KeyFrameThousand[2].z = 600.0f;
	KeyFrameThousand[2].x = 0.0f;
	KeyFrameThousand[2].giro = 270.0f;

	KeyFrameThousand[3].z = 600.0f;
	KeyFrameThousand[3].x = -600.0f;
	KeyFrameThousand[3].giro = 270.0f;

	animate(KeyFrameThousand,&thousandX,&thousandZ,&giroThousand);
}