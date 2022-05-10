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
//#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
//#include"Model.h"
#include "Carga modelos.h"
#include "Skybox.h"

//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
//std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture plainTexture;
Texture pisoTexture;
Texture treasureTexture;
Texture luffyTexture;

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



//c�lculo del promedio de las normales para sombreado de Phong
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



void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

//Movimiento de texturas
GLuint uniformTextureOffset = 0;
float toffsetu = 0.0f;
float toffsetv = 0.0f;


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateFloor();		// 0
	CreateChest();		// 1
	CreateLuffy();		// 2 - 10

	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();

	pisoTexture = Texture("Textures/mar.tga");
	pisoTexture.LoadTextureA();

	treasureTexture = Texture("Textures/treasure_chest.tga");
	treasureTexture.LoadTextureA();

	luffyTexture = Texture("Textures/LuffyA.tga");
	luffyTexture.LoadTextureA();

	//Cargamos los modelos
	cargaModelos();

	std::vector<std::string> skyboxFaces;

	skyboxFaces.push_back("Textures/Skybox/land_right.tga");
	skyboxFaces.push_back("Textures/Skybox/land_left.tga");
	skyboxFaces.push_back("Textures/Skybox/land_bottom.tga");
	skyboxFaces.push_back("Textures/Skybox/land_top.tga");
	skyboxFaces.push_back("Textures/Skybox/land_front.tga");
	skyboxFaces.push_back("Textures/Skybox/land_back.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	//luz direccional, s�lo 1 y siempre debe de existir
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

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 2000.0f);
	float ang = 0.0f;

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

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
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la c�mara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 aux(1.0);
		// Matrices auxiliares para Luffy
		glm::mat4 cabezaAux(1.0);
		glm::mat4 cuerpoAux(1.0);
		glm::mat4 brazoRAux(1.0);
		
		glm::mat4 frankyAux(1.0);
		glm::mat4 zoroAux(1.0);

		// Color base
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		//Movimiento de textura de mar
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);


		//Reinicio de movimiento de textura
		toffset = glm::vec2(0.0f, 0.0f);

		//Laboon
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		laboon.RenderModel();

		//Thousand Sunny
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -8.0f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		thousandSunny.RenderModel();

		//Thousand Sunny Destruido
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, -8.0f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		thousandSunnyDestruido.RenderModel();

		// Cofre del tesoro
		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.5f, 25.5f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		treasureTexture.UseTexture();
		meshList[1]->RenderMesh();

		//Sanji
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 25.0f, 8.0f));
		//model = glm::scale(model, glm::vec3(100.0f, 1.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sanji.RenderModel();

		//Brook
		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.5f, 25.0f, 8.0f));
		//model = glm::scale(model, glm::vec3(100.0f, 1.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		brook.RenderModel();

		// Cuerpo Luffy
		model = modelaux;
		model = glm::translate(model, glm::vec3(-4.5f, 26.25f, 8.0f));
		model = glm::scale(model, glm::vec3(2.4f, 2.4f, 2.4f));
		cuerpoAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		luffyTexture.UseTexture();
		meshList[2]->RenderMesh();

		// Cabeza Luffy
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(0.0f, 0.16f, 0.0f));
		cabezaAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//luffyTexture.UseTexture();
		meshList[3]->RenderMesh();

		// Sombrero Luffy
		model = cabezaAux;
		model = glm::translate(model, glm::vec3(0.0f, 0.24f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//luffyTexture.UseTexture();
		meshList[4]->RenderMesh();

		//ang < 180 ? ang += 0.1 : ang = 0;

		// Brazo L Luffy
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(0.18f, 0.1f, 0.0f));
		//model = glm::rotate(model, -ang * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//luffyTexture.UseTexture();
		meshList[5]->RenderMesh();

		// Brazo R1 Luffy
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(-0.18f, 0.1f, 0.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		brazoRAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//luffyTexture.UseTexture();
		meshList[8]->RenderMesh();

		//esc < 5.0f ? esc += 0.01f : esc = 1.0f;

		// Brazo R2 Luffy
		model = brazoRAux;
		model = glm::translate(model, glm::vec3(0.0f, -0.14f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, esc, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//luffyTexture.UseTexture();
		meshList[9]->RenderMesh();

		// Pierna L Luffy
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(0.08f, -0.2f, 0.0f));
		//model = glm::rotate(model, -ang * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//luffyTexture.UseTexture();
		meshList[6]->RenderMesh();

		// Pierna R Luffy
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(-0.08f, -0.2f, 0.0f));
		//model = glm::rotate(model, -ang * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//luffyTexture.UseTexture();
		meshList[7]->RenderMesh();

		// Entre pierna Luffy
		model = cuerpoAux;
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f));
		//model = glm::rotate(model, -ang * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//luffyTexture.UseTexture();
		meshList[10]->RenderMesh();

		// Nami
		model = modelaux;
		model = glm::translate(model, glm::vec3(-11.0f, 25.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Nami.RenderModel();

		// Robin
		model = modelaux;
		model = glm::translate(model, glm::vec3(-13.0f, 25.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Robin.RenderModel();

		// Franky
		model = modelaux;
		model = glm::translate(model, glm::vec3(-16.0f, 28.0f, 5.0f));
		model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
		frankyAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Franky.RenderModel();

		// Franky Brazo izq
		model = frankyAux;
		model = glm::translate(model, glm::vec3(0.7f, 0.6f, 0.0f));
		//model = glm::rotate(model, -glm::radians(ang), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Franky_BL.RenderModel();

		// Franky Brazo der
		model = frankyAux;
		model = glm::translate(model, glm::vec3(-0.6f, 0.6f, 0.0f));
		//model = glm::rotate(model, -glm::radians(ang), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Franky_BR.RenderModel();

		// Franky Pierna izq
		model = frankyAux;
		model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
		//model = glm::rotate(model, -glm::radians(ang), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Franky_PL.RenderModel();

		// Franky Pierna der
		model = frankyAux;
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
		//model = glm::rotate(model, -glm::radians(ang), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Franky_PR.RenderModel();

		// Zoro
		model = modelaux;
		model = glm::translate(model, glm::vec3(-19.0f, 28.0f, 5.0f));
		zoroAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zoro.RenderModel();

		// Zoro Brazo izq
		model = zoroAux;
		model = glm::translate(model, glm::vec3(0.5f, 0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(ang), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zoro_BL.RenderModel();

		// Zoro Brazo der
		model = zoroAux;
		model = glm::translate(model, glm::vec3(-0.4f, 0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(ang), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zoro_BR.RenderModel();

		// Zoro Pierna izq
		model = zoroAux;
		model = glm::translate(model, glm::vec3(0.2f, -0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(ang), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zoro_PL.RenderModel();

		// Zoro Pierna der
		model = zoroAux;
		model = glm::translate(model, glm::vec3(-0.1f, -0.4f, 0.0f));
		model = glm::rotate(model, -glm::radians(ang), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Zoro_PR.RenderModel();

		//Little Garden
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(400.0f, -2.0f, 200.0f));
		model = glm::scale(model, glm::vec3(70.0f, 70.0f, 70.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		littleGarden.RenderModel();

		// Reverse Mountain
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, -2.5f, -400.0f));
		model = glm::rotate(model, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		reverseMountain.RenderModel();


		toffsetu += 0.00005;
		if (toffsetu > 1.0) {
			toffsetu = 0.0f;
		}

		toffset = glm::vec2(toffsetu, toffsetv);

		// Piso
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(200.0f, 1.0f, 200.0f));
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
