/*
Semestre 2022-2
Animación Simple 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movCocheX;
float movCocheZ;
float movHelicopteroX;
float movHelicopteroZ;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;

Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model Dado_M;

//Modelos de carro
Model cuerpoDeCarro;
Model llanta;

//Modelo de circuito de carreras
Model circuitoDeCarreras;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";



//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/k_rueda.3ds");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Camino_M = Model();
	Camino_M.LoadModel("Models/railroad track.obj");

	//Carga de modelos de carro
	cuerpoDeCarro = Model();
	cuerpoDeCarro.LoadModel("Models/cuerpoDeCarro.obj");
	llanta = Model();
	llanta.LoadModel("Models/llanta.obj");

	//Carga de modelo de circuito de carreras
	circuitoDeCarreras = Model();
	circuitoDeCarreras.LoadModel("Models/circuitoDeCarreras.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);

	//contador de luces puntuales
	unsigned int pointLightCount = 0;

	unsigned int spotLightCount = 0;

	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz del carro delantera
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;

	//Luz de helicoptero
	spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,
		0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;

	//Luz del carro trasera
	spotLights[3] = SpotLight(0.0f, 0.0f, 1.0f,
		0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	
	//Variables de movimiento de coche
	movCocheX = 10.0f;
	movCocheZ = 14.0f;

	//Variables de movimiento de helicoptero
	movHelicopteroX = 110.0f;
	movHelicopteroZ = 100.0f;

	//Variables de control
	movOffset = 0.15f;
	rotllanta = 0.0f;
	rotllantaOffset = 10.0f;

	char direccion = 'l';
	char direccionHelicoptero = 'u';
	
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Control de dirección de coche
		if (direccion == 'l') {
			//Izquierda
			movCocheX += movOffset * deltaTime;
		}
		else if(direccion == 'u') {
			//Arriba
			movCocheZ += movOffset * deltaTime;
		}
		else if (direccion == 'r') {
			//Derecha
			movCocheX -= movOffset * deltaTime;
		}
		else if (direccion == 'd') {
			//Abajo
			movCocheZ -= movOffset * deltaTime;
		}

		//Control de sentidos de coche
		if (movCocheX > 79.0f && direccion == 'l') {
			direccion = 'u';
		}
		else if (movCocheX < -62.0f && direccion == 'r') {
			direccion = 'd';
		}
		else if (movCocheX > -4.0f && movCocheX < -3.0f && direccion == 'l') {
			direccion = 'u';
		}
		if (movCocheZ > 108 && direccion == 'u') {
			direccion = 'r';
		}
		else if (movCocheZ < -60.0f && direccion == 'd') {
			direccion = 'l';
		}
		else if (movCocheZ > 14.0f && movCocheX > -4.0f && movCocheX < -3.0f && direccion == 'u') {
			direccion = 'l';
		}

		rotllanta += rotllantaOffset * deltaTime;

		if (rotllanta >= 360.0f) {
			rotllanta = 0.0f;
		}

		//Control de dirección del helicoptero
		if (direccionHelicoptero == 'l') {
			//Izquierda
			movHelicopteroX += movOffset * deltaTime;
		}
		else if (direccionHelicoptero == 'u') {
			//Arriba
			movHelicopteroZ += movOffset * deltaTime;
		}
		else if (direccionHelicoptero == 'r') {
			//Derecha
			movHelicopteroX -= movOffset * deltaTime;
		}
		else if (direccionHelicoptero == 'd') {
			//Abajo
			movHelicopteroZ -= movOffset * deltaTime;
		}

		//Control de sentido del helicoptero
		if (movHelicopteroX > 110.0f && direccionHelicoptero == 'l') {
			direccionHelicoptero = 'u';
		}
		else if (movHelicopteroX < -90.0f && direccionHelicoptero == 'r') {
			direccionHelicoptero = 'd';
		}
		if (movHelicopteroZ > 140 && direccionHelicoptero == 'u') {
			direccionHelicoptero = 'r';
		}
		else if (movHelicopteroZ < -90.0f && direccionHelicoptero == 'd') {
			direccionHelicoptero = 'l';
		}

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);

		//Apagamos la luz trasera del carro
		shaderList[0].SetSpotLights(spotLights, spotLightCount-1);

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//Carro propio
		model = glm::mat4(1.0f);
		glm::vec3 posicionCarro(movCocheX, 2.1f, movCocheZ); 
		model = glm::translate(model, posicionCarro);

		//Ajustes para recorrer el circuito
		if (movCocheX > 75.0f && movCocheX < 79.0f && direccion == 'l') {
			//Giro para cambiar de dirección de izquierda hacia arriba
			model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f,1.0f,0.0f));
		}

		if (movCocheZ > 105.0f && movCocheZ < 108.0f && direccion == 'u') {
			//Giro para cambiar de dirección de arriba hacia derecha
			model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if (movCocheX < -58.0f && movCocheX > -62.0f && direccion == 'r') {
			//Giro para cambiar de dirección de derecha hacia abajo
			model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if (movCocheZ < -57.0f && movCocheZ > -60.0f && direccion == 'd') {
			//Giro para cambiar de dirección de abajo hacia izquierda
			model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if (movCocheX > -6.0 && movCocheX < -3.0f && direccion == 'l') {
			//Giro para cambiar de dirección de izquierda hacia arriba
			model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if (movCocheZ > 11.0f && movCocheZ < 14.0f && direccion == 'u') {
			//Giro para cambiar de dirección de arriba hacia izquierda
			model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if(direccion == 'u')
		{
			//Giro para mover el carro y quede viendo hacia arriba
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

			//Luz delantera
			spotLights[1].SetFlash(posicionCarro, glm::vec3(0.0f, 0.0f, 1.0f));

			//Luz trasera
			spotLights[3].SetFlash(posicionCarro, glm::vec3(0.0f, 0.0f, -1.0f));

		}
		else if (direccion == 'r') {
			//Giro para mover el carro y quede viendo hacia la derecha
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

			//Luz delantera
			spotLights[1].SetFlash(posicionCarro, glm::vec3(-1.0f, 0.0f, 0.0f));

			//Luz trasera
			spotLights[3].SetFlash(posicionCarro, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (direccion == 'd') {
			//Giro para mover el carro y quede viendo hacia abajo
			model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

			//Luz delantera
			spotLights[1].SetFlash(posicionCarro, glm::vec3(0.0f, 0.0f, -1.0f));

			//Luz trasera
			spotLights[3].SetFlash(posicionCarro, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		else if (direccion == 'l') {
			//Luz delantera
			spotLights[1].SetFlash(posicionCarro, glm::vec3(1.0f, 0.0f, 0.0f));

			//Luz trasera
			spotLights[3].SetFlash(posicionCarro, glm::vec3(-1.0f, 0.0f, 0.0f));
		}

		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuerpoDeCarro.RenderModel();

		//Llanta superior derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.3f, 0.25f, -1.25f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta.RenderModel();

		//Llanta superior izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.3f, 0.25f, 0.65f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta.RenderModel();

		//Llanta inferior derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(1.5f, 0.25f, -1.25f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta.RenderModel();

		//Llanta Inferior izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(1.5f, 0.25f, 0.65f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta.RenderModel();


		//Circuito de carreras
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		circuitoDeCarreras.RenderModel();


		//Helicoptero
		model = glm::mat4(1.0);
		glm::vec3 posicionHelicoptero(movHelicopteroX, 50.0f, movHelicopteroZ);
		model = glm::translate(model, posicionHelicoptero);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

		if (direccionHelicoptero == 'u')
		{
			//Giro para mover el helicoptero y quede viendo hacia arriba
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		}
		else if (direccionHelicoptero == 'r') {
			//Giro para mover el helicoptero y quede viendo hacia la derecha
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		else if (direccionHelicoptero == 'l') {
			//Giro para mover el helicoptero y quede viendo hacia abajo
			model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		}

		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);

		//Luz del helicoptero
		posicionHelicoptero.y -= 0.3f;
		posicionHelicoptero.z -= 1.0f;
		spotLights[2].SetFlash(posicionHelicoptero, glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
