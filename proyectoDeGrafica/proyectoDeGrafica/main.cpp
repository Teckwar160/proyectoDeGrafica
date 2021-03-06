
// Para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

// Bibliotecas
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <glew.h>
#include "Animaciones.h"
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "Window.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Camera3th.h"
#include "CameraAerial.h"
#include "Texture.h"
#include "Sphere.h"
#include "CargaModelos.h"
#include "Skybox.h"

// Para iluminacion
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

// Avatar
#include "Avatar.h"

Window mainWindow;
std::vector<Shader> shaderList;

Avatar Luffy;

// Camaras
Camera* camera;
Camera cameraFree;
Camera3th camera3th;
CameraAerial cameraAerial;

// Texturas
Texture pisoTexture;
Texture treasureTexture;
Texture luffyTexture;
Texture transparentTexture;

// Skybox
Skybox skybox_day;
Skybox skybox_night;

// Materiales
Material Material_brillante;
Material Material_opaco;

// Para los FPS
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// Ciclo dia noche
GLfloat lastTimeSky = 0.0f;
bool day = true;

// Ciclo de erupción del Volcan
GLfloat lastTimeVolcano = 0.0f;

// luz direccional
DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


// Función para crear lso shaders
void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

// Movimiento de texturas
GLuint uniformTextureOffset = 0;
float toffsetu = 0.0f;
float toffsetv = 0.0f;

// Función principal
int main()
{
	mainWindow = Window(1366, 768);
	mainWindow.Initialise();

	// Se crean las texturas
	CreateFloor();		
	CreateChest();		
	CreateLuffy();		
	CreateShaders();

	// Creación del avatar
	Luffy = Avatar(glm::vec3(-149.0f, 17.5f, 194.0f),0.3f, 0.3f);  //-174.0f, 18.8f, 204.0f

	// Creación de la camara en tercera persona
	camera3th = Camera3th(Luffy.getAvatarPosition(), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -15.0f, 0.5f, 0.5f);
	camera3th.setType(1);

	// Creación de camara aerea
	cameraAerial = CameraAerial(glm::vec3(-170.0f, 100.0f, 200.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);
	cameraAerial.setType(2);

	// Creación de camara aerea
	cameraFree = Camera(glm::vec3(-170.0f, 20.0f, 200.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);
	cameraFree.setType(3);

	// Carga de textura del mar
	pisoTexture = Texture("Textures/mar.tga");
	pisoTexture.LoadTextureA();

	// Carga de textura de cofre
	treasureTexture = Texture("Textures/treasure_chest.tga");
	treasureTexture.LoadTextureA();

	// Carga de trextura de Luffy
	luffyTexture = Texture("Textures/LuffyA.tga");
	luffyTexture.LoadTextureA();

	// Carga de textura de transparencia
	transparentTexture = Texture("Textures/transparente.tga");
	transparentTexture.LoadTextureA();

	// Cargamos los modelos
	cargaModelos();

	// Caras de los skybox
	std::vector<std::string> skyboxFaces_day;
	std::vector<std::string> skyboxFaces_night;

	// Cargamos las caras del skybox de día
	skyboxFaces_day.push_back("Textures/Skybox/heaven_right.tga");
	skyboxFaces_day.push_back("Textures/Skybox/heaven_left.tga");
	skyboxFaces_day.push_back("Textures/Skybox/heaven_bottom.tga");
	skyboxFaces_day.push_back("Textures/Skybox/heaven_top.tga");
	skyboxFaces_day.push_back("Textures/Skybox/heaven_front.tga");
	skyboxFaces_day.push_back("Textures/Skybox/heaven_back.tga");
	

	// Cargamos las caras del skybox de noche
	skyboxFaces_night.push_back("Textures/Skybox/heaven_night_right.tga");
	skyboxFaces_night.push_back("Textures/Skybox/heaven_night_left.tga");
	skyboxFaces_night.push_back("Textures/Skybox/heaven_night_bottom.tga");
	skyboxFaces_night.push_back("Textures/Skybox/heaven_night_top.tga");
	skyboxFaces_night.push_back("Textures/Skybox/heaven_night_front.tga");
	skyboxFaces_night.push_back("Textures/Skybox/heaven_night_back.tga");

	// Creamos los skybox
	skybox_day = Skybox(skyboxFaces_day);
	skybox_night = Skybox(skyboxFaces_night);

	// Creamos los materiales
	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	// Luz direccional
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, -1.0f, 0.0f);

	// Contador de luces puntuales
	unsigned int pointLightCount = 0;
	unsigned int spotLightCount = 0;

	// Luces del Volcan
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,					
		20.0f, 20.0f,												
		posicionOrigenV.x, posicionOrigenV.y, posicionOrigenV.z,	
		0.9f, 0.5f, 0.5f);											
	pointLightCount++;

	pointLights[1] = PointLight(1.0f, 0.0f, 0.0f,								
		30.0f, 30.0f,										
		posicionesVolcan[0].x, posicionesVolcan[0].y, posicionesVolcan[0].z,	
		0.9f, 0.5f, 0.5f);									
	pointLightCount++;

	pointLights[2] = PointLight(1.0f, 0.0f, 0.0f,			
		30.0f, 30.0f,										
		posicionesVolcan[1].x, posicionesVolcan[1].y, posicionesVolcan[1].z,	
		0.9f, 0.5f, 0.5f);									
	pointLightCount++;

	pointLights[3] = PointLight(1.0f, 0.0f, 0.0f,			
		30.0f, 30.0f,										
		posicionesVolcan[2].x, posicionesVolcan[2].y, posicionesVolcan[2].z,	
		0.9f, 0.5f, 0.5f);									
	pointLightCount++;

	// Luces fireworks
	pointLights[4] = PointLight(1.0f, 0.0f, 0.0f,			
		10.0f, 10.0f,										
		0.0f, 0.0f, 0.0f,	
		0.1f, 0.1f, 0.1f);																
	pointLightCount++;

	//Luz de barco de marina 1
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 20.0f,
		-300.0f, 20.0f, -135.0f,
		1.0f, 0.0f, 0.2f,
		1.0f, 0.0f, 0.0f,
		10.0f);
	spotLightCount++;

	//Luz de barco de marina 2
	spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 20.0f,
		-300.0f, 20.0f, -65.0f,
		1.0f, 0.0f, -0.2f,
		1.0f, 0.0f, 0.0f,
		10.0f);
	spotLightCount++;

	// Definimos nuestras variables uniformes
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
	uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;

	// Definimos la proyección
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.5f, 1000.0f);
	float ang = 0.0f;

	// Animaciones por Keyframe
	keyFrameMetaKnight();
	keyFrameDorry();
	keyFrameBrogy();
	keyFrameCarue();
	keyFrameVivi();
	keyFrameZoro();
	keyFrameFranky();
	
	// Posicionamos la luz del fuego artificial
	fireworkRed.setPointLight(&pointLights[4]);

	//Audio ambiental
	audioAmbiental->play2D("audio/One Piece We Are.wav", true);
	audioAmbiental->setSoundVolume(0.1);

	while (!mainWindow.getShouldClose())
	{
		// Para limitar los FPS
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		// Tiempo de control del ciclo dia noche
		if ((now - lastTimeSky) >= 50) {
			day = !day;
			lastTimeSky = now;
		}

		// Tiempo de control de erupción del volcan
		if ((now - lastTimeVolcano) >= 30) {
			iniciaErupcionVolcan = !iniciaErupcionVolcan;
			lastTimeVolcano = now;
		}

		// Recibir eventos del usuario
		glfwPollEvents();

		// Definimos el recorrido del video
		animaRecorrido(&cameraFree, deltaTime);

		// Cambio de camara
		switch (getCameraType())
		{
		case 2:
			camera = &cameraFree;
			camera->keyControl(mainWindow.getsKeys(), deltaTime);
			camera->mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
			break;

		case 3:
			camera = &cameraAerial;
			camera->keyControl(mainWindow.getsKeys(), deltaTime);
			camera->mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
			break;

		default:
			Luffy.keyControl(mainWindow.getsKeys(), deltaTime);
			Luffy.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
			camera3th.calculatePosition(Luffy.getAvatarPosition(), Luffy.getYaw(), Luffy.getPitch());
			cameraFree.setPosition(camera3th.getPosition());
			camera = &camera3th;
			break;
		}


		// Control de eventos de animación
		controlDeTeclas(mainWindow.getsKeys());

		// Limpiamos la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Cambio de skybox
		if (day) {
			mainLight.setIntensity(0.5f, 0.5f);
			skybox_day.DrawSkybox(camera->calculateViewMatrix(), projection);
		}
		else {
			mainLight.setIntensity(0.3f, 0.3f);
			skybox_night.DrawSkybox(camera->calculateViewMatrix(), projection);
		}

		// Fuegos artificiales
		iniciaShow(day);

		// Obtención de las variables uniformes
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		// Información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);

		// Información al shader de fuentes de iluminaci�n

		shaderList[0].SetDirectionalLight(&mainLight);
		

		if (lucesMarina) {
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}
		else {
			shaderList[0].SetSpotLights(spotLights, spotLightCount-2);
		}

		// Actualización de posición de luces
		pointLights[1].setPosition(posicionesVolcan[0]);
		pointLights[2].setPosition(posicionesVolcan[1]);
		pointLights[3].setPosition(posicionesVolcan[2]);
		
		if (fireworkRed.isAnimating()) {
			fireworkRed.updateLight();
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}
		else {
			shaderList[0].SetPointLights(pointLights, pointLightCount-1);
		}

		// Matrices auxiliares
		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 aux(1.0);

		// Matrices auxiliares para Luffy
		glm::mat4 cabezaAux(1.0);
		glm::mat4 cuerpoAux(1.0);
		glm::mat4 brazoRAux(1.0);

		glm::mat4 frankyAux(1.0);
		glm::mat4 zoroAux(1.0);
		glm::mat4 brogyAux(1.0);
		glm::mat4 dorryAux(1.0);
		glm::mat4 viviAux(1.0);
		glm::mat4 carueAux(1.0);

		// Color base
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		// Movimiento de textura de mar
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);


		// Reinicio de movimiento de textura
		toffset = glm::vec2(0.0f, 0.0f);


		// Thousand Sunny

		// Animación
		animaThousand(deltaTime);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(thousandX, 5.0f, thousandZ));
		model = glm::rotate(model, glm::radians(-giroThousand), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		// Cambio de modelo
		if (velaRota) {
			thousandSunnyDestruido.RenderModel();
		}
		else {
			thousandSunny.RenderModel();
		}
		

		// Barco 1 de la marina
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, 5.0f, -125.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		marina.RenderModel();

		// Barco 2 de la marina
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, 5.0f, -75.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		marina.RenderModel();

		// Cofre del tesoro
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.5f, 13.98f, -7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		treasureTexture.UseTexture();
		meshList[1]->RenderMesh();

		// Meta Knight
		animate(&pMetaKnight);

		// Ruptura de vela
		if (pMetaKnight.z < 205 && pMetaKnight.x < -160.0f) {
			velaRota = true;
		}

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(pMetaKnight.x, pMetaKnight.y, pMetaKnight.z));
		model = glm::rotate(model, glm::radians(pMetaKnight.giroX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pMetaKnight.giroY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pMetaKnight.giroZ), glm::vec3(0.0f, 0.0f, 1.0f));
		zoroAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		metaKnight.RenderModel();

		// Sanji
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.0f, 13.5f, -7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sanji.RenderModel();

		// Brook
		model = modelaux;
		model = glm::translate(model, glm::vec3(-6.0f, 12.5f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		brook.RenderModel();

		// Nami
		model = modelaux;
		model = glm::translate(model, glm::vec3(-4.0f, 8.8f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Nami.RenderModel();

		// Robin
		model = modelaux;
		model = glm::translate(model, glm::vec3(-5.5f, 12.3f, -6.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Robin.RenderModel();

		// Usopp
		model = modelaux;
		model = glm::translate(model, glm::vec3(-4.2f, 29.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Usopp.RenderModel();
		
		// Luffy
		animaLuffy(deltaTime);

		// Cuerpo Luffy
		model = glm::mat4(1.0);
		model = glm::translate(model, Luffy.getAvatarPosition());
		model = glm::scale(model, glm::vec3(2.4f, 2.4f, 2.4f));
		model = glm::rotate(model, glm::radians(Luffy.getRotation() + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		cuerpoAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		luffyTexture.UseTexture();
		meshList[2]->RenderMesh();

		// Cabeza Luffy
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(0.0f, 0.16f, 0.0f));
		cabezaAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[3]->RenderMesh();

		// Sombrero Luffy
		model = cabezaAux;
		model = glm::translate(model, glm::vec3(0.0f, 0.24f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[4]->RenderMesh();

		// Brazo L Luffy
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(0.18f, 0.1f, 0.0f));
		model = glm::rotate(model, glm::radians(anguloBrazoL), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[5]->RenderMesh();

		// Brazo R1 Luffy
		verificaAtaque();
		animaAtaqueLuffy(deltaTime);
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(-0.18f, 0.1f, 0.0f));
		model = glm::rotate(model, glm::radians(anguloBrazoR), glm::vec3(1.0f, 0.0f, 0.0f));
		brazoRAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[8]->RenderMesh();

		// Brazo R2 Luffy
		model = brazoRAux;
		model = glm::translate(model, glm::vec3(0.0f, -0.14f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, escalaBrazo, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[9]->RenderMesh();

		// Pierna L Luffy
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(0.08f, -0.2f, 0.0f));
		model = glm::rotate(model, glm::radians(anguloPiernaL), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[6]->RenderMesh();

		// Pierna R Luffy
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(-0.08f, -0.2f, 0.0f));
		model = glm::rotate(model, glm::radians(anguloPiernaR), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[7]->RenderMesh();

		// Entre pierna Luffy
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[10]->RenderMesh();

		// Franky
		animate(&pFranky);
		model = modelaux;
		model = glm::translate(model, glm::vec3(pFranky.x, pFranky.y, pFranky.z));
		model = glm::rotate(model, glm::radians(pFranky.giroY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
		frankyAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Franky.RenderModel();

		// Franky Brazo izq
		model = frankyAux;
		model = glm::translate(model, glm::vec3(0.7f, 0.6f, 0.0f));
		model = glm::rotate(model, -glm::radians(pFranky.anguloBrazoIzquierdo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Franky_BL.RenderModel();

		// Franky Brazo der

		// Reparación de vela
		if (pFranky.anguloBrazoDerecho > 135.0f && pFranky.anguloBrazoDerecho < 180.0f && pFranky.x <= -1.5f && pFranky.y >= 16.7f) {
			velaRota = false;
		}

		model = frankyAux;
		model = glm::translate(model, glm::vec3(-0.6f, 0.6f, 0.0f));
		model = glm::rotate(model, -glm::radians(pFranky.anguloBrazoDerecho), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Franky_BR.RenderModel();

		// Franky Pierna izq
		model = frankyAux;
		model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
		model = glm::rotate(model, -glm::radians(pFranky.anguloPiernaIzquierda), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Franky_PL.RenderModel();

		// Franky Pierna der
		model = frankyAux;
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
		model = glm::rotate(model, -glm::radians(pFranky.anguloPiernaDerecha), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Franky_PR.RenderModel();

		// Zoro
		animate(&pZoro);
		model = modelaux;
		model = glm::translate(model, glm::vec3(pZoro.x, pZoro.y, pZoro.z));
		model = glm::rotate(model, glm::radians(pZoro.giroY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pZoro.giroX), glm::vec3(1.0f, 0.0f, 0.0f));
		zoroAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zoro.RenderModel();

		// Zoro Brazo izq
		model = zoroAux;
		model = glm::translate(model, glm::vec3(0.5f, 0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pZoro.anguloBrazoIzquierdo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zoro_BL.RenderModel();

		// Zoro Brazo der
		model = zoroAux;
		model = glm::translate(model, glm::vec3(-0.4f, 0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pZoro.anguloBrazoDerecho), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zoro_BR.RenderModel();

		// Zoro Pierna izq
		model = zoroAux;
		model = glm::translate(model, glm::vec3(0.2f, -0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pZoro.anguloPiernaIzquierda), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zoro_PL.RenderModel();

		// Zoro Pierna der
		model = zoroAux;
		model = glm::translate(model, glm::vec3(-0.1f, -0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pZoro.anguloPiernaDerecha), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zoro_PR.RenderModel();

		// Little Garden
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 200.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		littleGarden.RenderModel();

		// Brogy
		iniciaPelea();
		animate(&pBrogy);
		model = modelaux;
		model = glm::translate(model, glm::vec3(pBrogy.x, pBrogy.y, pBrogy.z));
		model = glm::rotate(model, glm::radians(pBrogy.giroY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pBrogy.giroX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		brogyAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Brogy.RenderModel();

		// Brogy Brazo izq
		model = brogyAux;
		model = glm::translate(model, glm::vec3(0.5f, 0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pBrogy.anguloBrazoIzquierdo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Brogy_BL.RenderModel();

		// Brogy Brazo der
		model = brogyAux;
		model = glm::translate(model, glm::vec3(-0.4f, 0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pBrogy.anguloBrazoDerecho), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Brogy_BR.RenderModel();

		// Brogy Pierna izq
		model = brogyAux;
		model = glm::translate(model, glm::vec3(0.2f, -0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pBrogy.anguloPiernaIzquierda), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Brogy_PL.RenderModel();

		// Brogy Pierna der
		model = brogyAux;
		model = glm::translate(model, glm::vec3(-0.1f, -0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pBrogy.anguloPiernaDerecha), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Brogy_PR.RenderModel();

		// Dorry
		animate(&pDorry);
		model = modelaux;
		model = glm::translate(model, glm::vec3(pDorry.x, pDorry.y, pDorry.z));
		model = glm::rotate(model, glm::radians(pDorry.giroY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pDorry.giroX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		dorryAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dorry.RenderModel();

		// Dorry Brazo izq
		model = dorryAux;
		model = glm::translate(model, glm::vec3(0.5f, 0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pDorry.anguloBrazoIzquierdo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dorry_BL.RenderModel();

		// Dorry Brazo der
		model = dorryAux;
		model = glm::translate(model, glm::vec3(-0.4f, 0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pDorry.anguloBrazoDerecho), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dorry_BR.RenderModel();

		// Dorry Pierna izq
		model = dorryAux;
		model = glm::translate(model, glm::vec3(0.2f, -0.5f, 0.0f));
		model = glm::rotate(model, -glm::radians(pDorry.anguloPiernaIzquierda), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dorry_PL.RenderModel();

		// Dorry Pierna der
		model = dorryAux;
		model = glm::translate(model, glm::vec3(-0.1f, -0.5f, 0.0f));
		model = glm::rotate(model, -glm::radians(pDorry.anguloPiernaDerecha), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dorry_PR.RenderModel();

		// Carue
		animate(&pCarue);
		model = modelaux;
		model = glm::translate(model, glm::vec3(pCarue.x, pCarue.y, pCarue.z));
		model = glm::rotate(model, -glm::radians(pCarue.giroY), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		carueAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Carue.RenderModel();

		// Carue pie derecho
		model = carueAux;
		model = glm::translate(model, glm::vec3(-0.3f, -0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pCarue.anguloPiernaDerecha), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Carue_ft.RenderModel();

		// Carue pie izquierdo
		model = carueAux;
		model = glm::translate(model, glm::vec3(0.3f, -0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(pCarue.anguloPiernaIzquierda), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Carue_ft.RenderModel();

		// Vivi
		animate(&pVivi);
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, -0.5));
		viviAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Vivi.RenderModel();

		// Vivi brazo derecho
		model = viviAux;
		model = glm::translate(model, glm::vec3(-0.4f, 0.6f, 0.0f));
		model = glm::rotate(model, -glm::radians(pVivi.anguloBrazoDerecho), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Vivi_BR.RenderModel();

		// Reverse Mountain
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -11.0f, -400.0f));
		modelaux = model;
		model = glm::rotate(model, -glm::radians(90.0f) , glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		reverseMountain.RenderModel();

		// Laboon
		animaLaboon(deltaTime);
		model = modelaux;
		model = glm::translate(model, glm::vec3(laboonX, -8.0f, laboonZ));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(anguloLaboon), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(40.0f, 40.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		laboon.RenderModel();

		//Animación de la lava
		animaLava(deltaTime);
		for (glm::vec3 posVolcan : posicionesVolcan) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, posVolcan);
			model = glm::rotate(model, glm::radians(rotacionLava), glm::vec3(0.0f, 1.0f, 1.0f));
			model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			transparentTexture.UseTexture();
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[1]->RenderMesh();
			glDisable(GL_BLEND);
		}
		
		// Fireworks
		fireworkRed.animate(deltaTime);

		// Firework red
		model = glm::mat4(1.0f);
		model = glm::translate(model, fireworkRed.getCentralPos());
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		transparentTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();
		glDisable(GL_BLEND);

		if (fireworkRed.isAnimating()) {
			glm::vec3* p = fireworkRed.getPositions();

			for (int i = 0; i < fireworkRed.getSize();i++) {
				model = glm::mat4(1.0f);
				model = glm::translate(model,p[i]);
				model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				glUniform3fv(uniformColor, 1, glm::value_ptr(color));
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				transparentTexture.UseTexture();
				Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
				meshList[1]->RenderMesh();
				glDisable(GL_BLEND);
			}
		}

		toffsetu += 0.00005;
		if (toffsetu > 1.0) {
			toffsetu = 0.0f;
		}

		toffset = glm::vec2(toffsetu, toffsetv);

		// Mar
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 10.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f, 1.0f, 100.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}

