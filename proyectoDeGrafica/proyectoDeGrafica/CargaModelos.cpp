// Biblioteca necesaria
#include "CargaModelos.h"

std::vector<Mesh*> meshList;
Model laboon;
Model sanji;
Model brook;
Model Robin;
Model Nami;
Model Usopp;
Model Vivi, Vivi_BR;
Model Carue, Carue_ft;
Model Zoro, Zoro_BR, Zoro_BL, Zoro_PR, Zoro_PL;
Model Franky, Franky_BR, Franky_BL, Franky_PR, Franky_PL;
Model Brogy, Brogy_BR, Brogy_BL, Brogy_PR, Brogy_PL;
Model Dorry, Dorry_BR, Dorry_BL, Dorry_PR, Dorry_PL;
Model thousandSunny;
Model thousandSunnyDestruido;
Model marina;
Model littleGarden;
Model reverseMountain;
Model metaKnight;

void cargaModelos() {
	// Laboon
	laboon = Model();
	laboon.LoadModel("Models/laboon.obj");

	// Sanji
	sanji = Model();
	sanji.LoadModel("Models/Sanji.obj");

	// Brook
	brook = Model();
	brook.LoadModel("Models/Brook.obj");

	// Nami
	Nami = Model();
	Nami.LoadModel("Models/Nami.obj");

	// Robin
	Robin = Model();
	Robin.LoadModel("Models/Robin.obj");

	// Usopp
	Usopp = Model();
	Usopp.LoadModel("Models/Usopp.obj");

	// Marina
	marina = Model();
	marina.LoadModel("Models/marina.obj");

	// Carue
	Carue = Model();
	Carue.LoadModel("Models/Carue_Body.obj");

	Carue_ft = Model();
	Carue_ft.LoadModel("Models/Carue_Feet.obj");

	// Vivi
	Vivi = Model();
	Vivi.LoadModel("Models/Vivi_Bo.obj");

	Vivi_BR = Model();
	Vivi_BR.LoadModel("Models/Vivi_BR.obj");


	// Zoro
	Zoro = Model();
	Zoro.LoadModel("Models/Zoro_Bo.obj");

	Zoro_BR = Model();
	Zoro_BR.LoadModel("Models/Zoro_BR.obj");

	Zoro_BL = Model();
	Zoro_BL.LoadModel("Models/Zoro_BL.obj");

	Zoro_PR = Model();
	Zoro_PR.LoadModel("Models/Zoro_PR.obj");

	Zoro_PL = Model();
	Zoro_PL.LoadModel("Models/Zoro_PL.obj");

	// Franky
	Franky = Model();
	Franky.LoadModel("Models/Franky_Bo.obj");

	Franky_BR = Model();
	Franky_BR.LoadModel("Models/Franky_BR.obj");

	Franky_BL = Model();
	Franky_BL.LoadModel("Models/Franky_BL.obj");

	Franky_PR = Model();
	Franky_PR.LoadModel("Models/Franky_PR.obj");

	Franky_PL = Model();
	Franky_PL.LoadModel("Models/Franky_PL.obj");

	// Brogy
	Brogy = Model();
	Brogy.LoadModel("Models/Brogy_Bo.obj");

	Brogy_BR = Model();
	Brogy_BR.LoadModel("Models/Brogy_BR.obj");

	Brogy_BL = Model();
	Brogy_BL.LoadModel("Models/Brogy_BL.obj");

	Brogy_PR = Model();
	Brogy_PR.LoadModel("Models/Brogy_PR.obj");

	Brogy_PL = Model();
	Brogy_PL.LoadModel("Models/Brogy_PL.obj");

	// Dorry
	Dorry = Model();
	Dorry.LoadModel("Models/Dorry_Bo.obj");

	Dorry_BR = Model();
	Dorry_BR.LoadModel("Models/Dorry_BR.obj");

	Dorry_BL = Model();
	Dorry_BL.LoadModel("Models/Dorry_BL.obj");

	Dorry_PR = Model();
	Dorry_PR.LoadModel("Models/Dorry_PR.obj");

	Dorry_PL = Model();
	Dorry_PL.LoadModel("Models/Dorry_PL.obj");

	// Thousand
	thousandSunny = Model();
	thousandSunny.LoadModel("Models/Thousand Sunny.obj");

	thousandSunnyDestruido = Model();
	thousandSunnyDestruido.LoadModel("Models/Thousand Sunny Destruido.obj");

	// Little Garden
	littleGarden = Model();
	littleGarden.LoadModel("Models/Little Garden.obj");

	// Reverse Mountain
	reverseMountain = Model();
	reverseMountain.LoadModel("Models/ReverseMountain.obj");

	// Meta Knight
	metaKnight = Model();
	metaKnight.LoadModel("Models/meta knight.obj");

}

void CreateFloor()
{
	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	0.0f, 0.8f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.8f, 0.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		0.8f, 0.8f,	0.0f, -1.0f, 0.0f
	};

	Mesh* floor = new Mesh();
	floor->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(floor);
}

void CreateChest()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};

	// average normals
	GLfloat cubo_vertices[] = {
		// front
		// x       y     z            S     T             NX           NY            NZ
		-0.5f, -0.5f,  0.5f,        0.5f, 0.0f,       0.0f,        0.0f,        -1.0f,        
		0.5f, -0.5f,  0.5f,         1.0f, 0.0f,        0.0f,        0.0f,        -1.0f,        
		0.5f,  0.5f,  0.5f,         1.0f, 0.5f,        0.0f,        0.0f,        -1.0f,        
		-0.5f,  0.5f,  0.5f,        0.5f, 0.5f,       0.0f,        0.0f,        -1.0f,        

		// right
		//x     y      z            S        T
		0.5f, -0.5f,  0.5f,         0.0f,  0.0f,		-1.0f,        0.0f,        0.0f,
		0.5f, -0.5f,  -0.5f,        0.5f,  0.0f,      -1.0f,        0.0f,        0.0f,
		0.5f,  0.5f,  -0.5f,        0.5f,  0.5f,      -1.0f,        0.0f,        0.0f,
		0.5f,  0.5f,  0.5f,         0.0f,  0.5f,		-1.0f,        0.0f,        0.0f,

		// back
		-0.5f, -0.5f, -0.5f,        0.0f,  0.5f,       0.0f,        0.0f,        1.0f,
		0.5f, -0.5f, -0.5f,         0.5f,  0.5f,      0.0f,        0.0f,        1.0f,
		0.5f,  0.5f, -0.5f,         0.5f,  1.0f,      0.0f,        0.0f,        1.0f,
		-0.5f,  0.5f, -0.5f,        0.0f,  1.0f,       0.0f,        0.0f,        1.0f,

		// left
		//x     y      z            S        T
		-0.5f, -0.5f,  -0.5f,       0.0f,  0.0f,       1.0f,        0.0f,        0.0f,
		-0.5f, -0.5f,  0.5f,        0.5f,  0.0f,      1.0f,        0.0f,        0.0f,
		-0.5f,  0.5f,  0.5f,        0.5f,  0.5f,      1.0f,        0.0f,        0.0f,
		-0.5f,  0.5f,  -0.5f,       0.0f,  0.5f,        1.0f,        0.0f,        0.0f,

		// bottom
		//x     y      z            S        T
		-0.5f, -0.5f,  0.5f,        0.0f,  0.5f,       0.0f,        1.0f,        0.0f,
		0.5f,  -0.5f,  0.5f,        0.5f,  0.5f,        0.0f,        1.0f,        0.0f,
		 0.5f,  -0.5f,  -0.5f,      0.5f,  1.0f,       0.0f,        1.0f,        0.0f,
		-0.5f, -0.5f,  -0.5f,       0.0f,  1.0f,      0.0f,        1.0f,        0.0f,

		// up
		//x     y      z            S        T
		 -0.5f, 0.5f,  0.5f,        0.5f,  0.5f,      0.0f,        -1.0f,        0.0f,
		 0.5f,  0.5f,  0.5f,        1.0f,  0.5f,       0.0f,        -1.0f,        0.0f,
		  0.5f, 0.5f,  -0.5f,       1.0f,  1.0f,        0.0f,        -1.0f,        0.0f,
		 -0.5f, 0.5f,  -0.5f,       0.5f,  1.0f,       0.0f,        -1.0f,        0.0f,
	};

	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(cubo);
}

void CreateLuffy() {
	
	float n = 1.0 / 32;
	int i = 0;

	// Sombrero
	int const x = 3 * 22;				
	unsigned int sombrero_indices[x];
	
	for (i = 0; i < x; i++) { sombrero_indices[i] = i; }

	GLfloat sombrero_vertices[] = {
		// x	  y		  z		 u		  v		  nx	 ny		 nz
		-0.14f,	0.0f,	0.1f,	0.625f,	1.0f,	0.0f,	0.0f,	-1.0f, // 0
		0.14f,	0.0f,	0.1f,	0.406f,	1.0f,	0.0f,	0.0f,	-1.0f, // 1
		0.14f,	0.08f,	0.1f,	0.406f,	0.937f,	0.0f,	0.0f,	-1.0f, // 5

		0.14f,	0.08f,	0.1f,	0.406f,	0.937f,	0.0f,	0.0f,	-1.0f, // 5
		-0.14f,	0.08f,	0.1f,	0.625f,	0.937f,	0.0f,	0.0f,	-1.0f, // 4
		-0.14f,	0.0f,	0.1f,	0.625f,	1.0f,	0.0f,	0.0f,	-1.0f, // 0
		//
		0.14f,	0.0f,	0.1f,	0.406f,	1.0f,	-1.0f,	0.0f,	0.0f, // 1
		0.14f,	0.0f,	-0.1f,	0.25f,	1.0f,	-1.0f,	0.0f,	0.0f, // 2
		0.14f,	0.08f,	-0.1f,	0.25f,	0.937f,	-1.0f,	0.0f,	0.0f, // 6

		0.14f,	0.08f,	-0.1f,	0.25f,	0.937f,	-1.0f,	0.0f,	0.0f, // 6
		0.14f,	0.08f,	0.1f,	0.406f,	0.937f,	-1.0f,	0.0f,	0.0f, // 5
		0.14f,	0.0f,	0.1f,	0.406f,	1.0f,	-1.0f,	0.0f,	0.0f, // 1
		//
		0.14f,	0.0f,	-0.1f,	0.25f,	1.0f,	0.0f,	0.0f,	1.0f, // 2
		-0.14f,	0.0f,	-0.1f,	0.031f,	1.0f,	0.0f,	0.0f,	1.0f, // 3
		-0.14f,	0.08f,	-0.1f,	0.031f,	0.937f,	0.0f,	0.0f,	1.0f, // 7

		-0.14f,	0.08f,	-0.1f,	0.031f,	0.937f,	0.0f,	0.0f,	1.0f, // 7
		0.14f,	0.08f,	-0.1f,	0.25f,	0.937f,	0.0f,	0.0f,	1.0f, // 6
		0.14f,	0.0f,	-0.1f,	0.25f,	1.0f,	0.0f,	0.0f,	1.0f, // 2
		//
		-0.14f,	0.0f,	-0.1f,	0.781f,	1.0f,	1.0f,	0.0f,	0.0f, // 3
		-0.14f,	0.0f,	0.1f,	0.625f,	1.0f,	1.0f,	0.0f,	0.0f, // 0
		-0.14f,	0.08f,	0.1f,	0.625f,	0.937f,	1.0f,	0.0f,	0.0f, // 4

		-0.14f,	0.08f,	0.1f,	0.625f,	0.937f,	1.0f,	0.0f,	0.0f, // 4
		-0.14f,	0.08f,	-0.1f,	0.781f,	0.937f,	1.0f,	0.0f,	0.0f, // 7
		-0.14f,	0.0f,	-0.1f,	0.781f,	1.0f,	1.0f,	0.0f,	0.0f, // 3
		//
		-0.14f,	0.08f,	0.1f,	0.625f,	0.937f,	0.0f,	-1.0f,	0.0f, // 4
		0.14f,	0.08f,	0.1f,	0.406f,	0.937f,	0.0f,	-1.0f,	0.0f, // 5
		0.14f,	0.08f,	-0.1f,	0.406f,	0.781f,	0.0f,	-1.0f,	0.0f, // 6

		0.14f,	0.08f,	-0.1f,	0.406f,	0.781f,	0.0f,	-1.0f,	0.0f, // 6
		-0.14f,	0.08f,	-0.1f,	0.625f,	0.781f,	0.0f,	-1.0f,	0.0f, // 7
		-0.14f,	0.08f,	0.1f,	0.625f,	0.937f,	0.0f,	-1.0f,	0.0f, // 4
		//
		-0.18f,	-0.04f,	0.14f,	22*n,	12*n,	0.0f,	0.0f,	-1.0f, // 8
		0.18f,	-0.04f,	0.14f,	22*n,	3*n,	0.0f,	0.0f,	-1.0f, // 9
		0.18f,	0.0f,	0.14f,	23*n,	3*n,	0.0f,	0.0f,	-1.0f, // 13

		0.18f,	0.0f,	0.14f,	23*n,	3*n,	0.0f,	0.0f,	-1.0f, // 13
		-0.18f,	0.0f,	0.14f,	23*n,	12*n,	0.0f,	0.0f,	-1.0f, // 12
		-0.18f,	-0.04f,	0.14f,	22*n,	12*n,	0.0f,	0.0f,	-1.0f, // 8
		//
		0.18f,	-0.04f,	0.14f,	23*n,	2*n,	-1.0f,	0.0f,	0.0f, // 9
		0.18f,	-0.04f,	-0.14f,	30*n,	2*n,	-1.0f,	0.0f,	0.0f, // 10
		0.18f,	0.0f,	-0.14f,	30*n,	3*n,	-1.0f,	0.0f,	0.0f, // 14

		0.18f,	0.0f,	-0.14f,	30*n,	3*n,	-1.0f,	0.0f,	0.0f, // 14
		0.18f,	0.0f,	0.14f,	23*n,	3*n,	-1.0f,	0.0f,	0.0f, // 13
		0.18f,	-0.04f,	0.14f,	23*n,	2*n,	-1.0f,	0.0f,	0.0f, // 9
		//
		0.18f,	-0.04f,	-0.14f,	31*n,	3*n,	0.0f,	0.0f,	1.0f, // 10
		-0.18f,	-0.04f,	-0.14f,	31*n,	12*n,	0.0f,	0.0f,	1.0f, // 11
		-0.18f,	0.0f,	-0.14f,	30*n,	12*n,	0.0f,	0.0f,	1.0f, // 15

		-0.18f,	0.0f,	-0.14f,	30*n,	12*n,	0.0f,	0.0f,	1.0f, // 15
		0.18f,	0.0f,	-0.14f,	30*n,	3*n,	0.0f,	0.0f,	1.0f, // 14
		0.18f,	-0.04f,	-0.14f,	31*n,	3*n,	0.0f,	0.0f,	1.0f, // 10
		//
		-0.18f,	-0.04f,	-0.14f,	30*n,	13*n,	1.0f,	0.0f,	0.0f, // 11
		-0.18f,	-0.04f,	0.14f,	23*n,	13*n,	1.0f,	0.0f,	0.0f, // 8
		-0.18f,	0.0f,	0.14f,	23*n,	12*n,	1.0f,	0.0f,	0.0f, // 12

		-0.18f,	0.0f,	0.14f,	23*n,	12*n,	1.0f,	0.0f,	0.0f, // 12
		-0.18f,	0.0f,	-0.14f,	30*n,	12*n,	1.0f,	0.0f,	0.0f, // 15
		-0.18f,	-0.04f,	-0.14f,	30*n,	13*n,	1.0f,	0.0f,	0.0f, // 11
		//
		-0.18f,	0.0f,	0.14f,	23*n,	12*n,	0.0f,	-1.0f,	0.0f, // 12
		0.18f,	0.0f,	0.14f,	23*n,	3*n,	0.0f,	-1.0f,	0.0f, // 13
		0.18f,	0.0f,	-0.14f,	30*n,	3*n,	0.0f,	-1.0f,	0.0f, // 14

		0.18f,	0.0f,	-0.14f,	30*n,	3*n,	0.0f,	-1.0f,	0.0f, // 14
		-0.18f,	0.0f,	-0.14f,	30*n,	12*n,	0.0f,	-1.0f,	0.0f, // 15
		-0.18f,	0.0f,	0.14f,	23*n,	12*n,	0.0f,	-1.0f,	0.0f, // 12
		//
		0.18f,	-0.04f,	0.14f,	23*n,	3*n,	0.0f,	1.0f,	0.0f, // 9
		-0.18f,	-0.04f,	0.14f,	23*n,	12*n,	0.0f,	1.0f,	0.0f, // 8
		-0.18f,	-0.04f,	-0.14f,	30*n,	12*n,	0.0f,	1.0f,	0.0f, // 11
		
		-0.18f,	-0.04f,	-0.14f,	30*n,	12*n,	0.0f,	1.0f,	0.0f, // 11
		0.18f,	-0.04f,	-0.14f,	30*n,	3*n,	0.0f,	1.0f,	0.0f, // 10
		0.18f,	-0.04f,	0.14f,	23*n,	3*n,	0.0f,	1.0f,	0.0f, // 9
	};
	
	// Prisma rectangular
	int const c = 3 * 12;				
	unsigned int prisma_indices[c];		

	for (i = 0; i < c; i++) { prisma_indices[i] = i; }

	// Cabeza
	GLfloat cabeza_vertices[] = {
		// x	  y		  z		 u		  v		  nx	 ny		 nz
		// front
		-0.14f,	0.0f,	0.1f,	5*n,	19*n,	0.0f,	0.0f,	-1.0f, // 0
		0.14f,	0.0f,	0.1f,	12*n,	19*n,	0.0f,	0.0f,	-1.0f, // 1
		0.14f,	0.2f,	0.1f,	12*n,	24*n,	0.0f,	0.0f,	-1.0f, // 5

		0.14f,	0.2f,	0.1f,	12*n,	24*n,	0.0f,	0.0f,	-1.0f, // 5
		-0.14f,	0.2f,	0.1f,	5*n,	24*n,	0.0f,	0.0f,	-1.0f, // 4
		-0.14f,	0.0f,	0.1f,	5*n,	19*n,	0.0f,	0.0f,	-1.0f, // 0

		// rigth
		0.14f,	0.0f,	0.1f,	12*n,	19*n,	-1.0f,	0.0f,	0.0f, // 1
		0.14f,	0.0f,	-0.1f,	18*n,	19*n,	-1.0f,	0.0f,	0.0f, // 2
		0.14f,	0.2f,	-0.1f,	18*n,	24*n,	-1.0f,	0.0f,	0.0f, // 6

		0.14f,	0.2f,	-0.1f,	18*n,	24*n,	-1.0f,	0.0f,	0.0f, // 6
		0.14f,	0.2f,	0.1f,	12*n,	24*n,	-1.0f,	0.0f,	0.0f, // 5
		0.14f,	0.0f,	0.1f,	12*n,	19*n,	-1.0f,	0.0f,	0.0f, // 1

		// back
		0.14f,	0.0f,	-0.1f,	18*n,	19*n,	0.0f,	0.0f,	1.0f, // 2
		-0.14f,	0.0f,	-0.1f,	24*n,	19*n,	0.0f,	0.0f,	1.0f, // 3
		-0.14f,	0.2f,	-0.1f,	24*n,	24*n,	0.0f,	0.0f,	1.0f, // 7

		-0.14f,	0.2f,	-0.1f,	24*n,	24*n,	0.0f,	0.0f,	1.0f, // 7
		0.14f,	0.2f,	-0.1f,	18*n,	24*n,	0.0f,	0.0f,	1.0f, // 6
		0.14f,	0.0f,	-0.1f,	18*n,	19*n,	0.0f,	0.0f,	1.0f, // 2

		// left
		-0.14f,	0.0f,	-0.1f,	0.0f,	19*n,	1.0f,	0.0f,	0.0f, // 3
		-0.14f,	0.0f,	0.1f,	5*n,	19*n,	1.0f,	0.0f,	0.0f, // 0
		-0.14f,	0.2f,	0.1f,	5*n,	24*n,	1.0f,	0.0f,	0.0f, // 4

		-0.14f,	0.2f,	0.1f,	5*n,	24*n,	1.0f,	0.0f,	0.0f, // 4
		-0.14f,	0.2f,	-0.1f,	0.0f,	24*n,	1.0f,	0.0f,	0.0f, // 7
		-0.14f,	0.0f,	-0.1f,	0.0f,	19*n,	1.0f,	0.0f,	0.0f, // 3

		// top
		-0.14f,	0.2f,	0.1f,	5*n,	24*n,	0.0f,	-1.0f,	0.0f, // 4
		0.14f,	0.2f,	0.1f,	12*n,	24*n,	0.0f,	-1.0f,	0.0f, // 5
		0.14f,	0.2f,	-0.1f,	12*n,	29*n,	0.0f,	-1.0f,	0.0f, // 6

		0.14f,	0.2f,	-0.1f,	12*n,	29*n,	0.0f,	-1.0f,	0.0f, // 6
		-0.14f,	0.2f,	-0.1f,	5*n,	29*n,	0.0f,	-1.0f,	0.0f, // 7
		-0.14f,	0.2f,	0.1f,	5*n,	24*n,	0.0f,	-1.0f,	0.0f, // 4

		// bottom
		0.14f,	0.0f,	0.1f,	12*n,	19*n,	0.0f,	1.0f,	0.0f, // 1
		-0.14f,	0.0f,	0.1f,	5*n,	19*n,	0.0f,	1.0f,	0.0f, // 0
		-0.14f,	0.0f,	-0.1f,	5*n,	14*n,	0.0f,	1.0f,	0.0f, // 3

		-0.14f,	0.0f,	-0.1f,	5*n,	14*n,	0.0f,	1.0f,	0.0f, // 3
		0.14f,	0.0f,	-0.1f,	12*n,	14*n,	0.0f,	1.0f,	0.0f, // 2
		0.14f,	0.0f,	0.1f,	12*n,	19*n,	0.0f,	1.0f,	0.0f, // 1

	};

	// Cuerpo
	GLfloat cuerpo_vertices[] = {
		// x	  y		  z		 u		  v		  nx	 ny		 nz
		// front
		-0.14f,	-0.16f,	0.06f,	4*n,	2*n,	0.0f,	0.0f,	-1.0f, // 0
		0.14f,	-0.16f,	0.06f,	11*n,	2*n,	0.0f,	0.0f,	-1.0f, // 1
		0.14f,	0.16f,	0.06f,	11*n,	10*n,	0.0f,	0.0f,	-1.0f, // 5

		0.14f,	0.16f,	0.06f,	11*n,	10*n,	0.0f,	0.0f,	-1.0f, // 5
		-0.14f,	0.16f,	0.06f,	4*n,	10*n,	0.0f,	0.0f,	-1.0f, // 4
		-0.14f,	-0.16f,	0.06f,	4*n,	2*n,	0.0f,	0.0f,	-1.0f, // 0

		// right
		0.14f,	-0.16f,	0.06f,	11*n,	2*n,	-1.0f,	0.0f,	0.0f, // 1
		0.14f,	-0.16f,	-0.06f,	14*n,	2*n,	-1.0f,	0.0f,	0.0f, // 2
		0.14f,	0.16f,	-0.06f,	14*n,	10*n,	-1.0f,	0.0f,	0.0f, // 6

		0.14f,	0.16f,	-0.06f,	14*n,	10*n,	-1.0f,	0.0f,	0.0f, // 6
		0.14f,	0.16f,	0.06f,	11*n,	10*n,	-1.0f,	0.0f,	0.0f, // 5
		0.14f,	-0.16f,	0.06f,	11*n,	2*n,	-1.0f,	0.0f,	0.0f, // 1

		// back
		0.14f,	-0.16f,	-0.06f,	14*n,	2*n,	0.0f,	0.0f,	1.0f, // 2
		-0.14f,	-0.16f,	-0.06f,	21*n,	2*n,	0.0f,	0.0f,	1.0f, // 3
		-0.14f,	0.16f,	-0.06f,	21*n,	10*n,	0.0f,	0.0f,	1.0f, // 7

		-0.14f,	0.16f,	-0.06f,	21*n,	10*n,	0.0f,	0.0f,	1.0f, // 7
		0.14f,	0.16f,	-0.06f,	14*n,	10*n,	0.0f,	0.0f,	1.0f, // 6
		0.14f,	-0.16f,	-0.06f,	14*n,	2*n,	0.0f,	0.0f,	1.0f, // 2

		// left
		-0.14f,	-0.16f,	-0.06f,	1*n,	2*n,	1.0f,	0.0f,	0.0f, // 3
		-0.14f,	-0.16f,	0.06f,	4*n,	2*n,	1.0f,	0.0f,	0.0f, // 0
		-0.14f,	0.16f,	0.06f,	4*n,	10*n,	1.0f,	0.0f,	0.0f, // 4
		
		-0.14f,	0.16f,	0.06f,	4*n,	10*n,	1.0f,	0.0f,	0.0f, // 4
		-0.14f,	0.16f,	-0.06f,	1*n,	10*n,	1.0f,	0.0f,	0.0f, // 7
		-0.14f,	-0.16f,	-0.06f,	1*n,	2*n,	1.0f,	0.0f,	0.0f, // 3

		// top
		-0.14f,	0.16f,	0.06f,	21*n,	13*n,	0.0f,	-1.0f,	0.0f, // 4
		0.14f,	0.16f,	0.06f,	14*n,	13*n,	0.0f,	-1.0f,	0.0f, // 5
		0.14f,	0.16f,	-0.06f,	14*n,	10*n,	0.0f,	-1.0f,	0.0f, // 6

		0.14f,	0.16f,	-0.06f,	14*n,	10*n,	0.0f,	-1.0f,	0.0f, // 6
		-0.14f,	0.16f,	-0.06f,	21*n,	10*n,	0.0f,	-1.0f,	0.0f, // 7
		-0.14f,	0.16f,	0.06f,	21*n,	13*n,	0.0f,	-1.0f,	0.0f, // 4

		// bottom
		0.14f,	-0.16f,	0.06f,	14*n,	13*n,	0.0f,	1.0f,	0.0f, // 1
		-0.14f,	-0.16f,	0.06f,	21*n,	13*n,	0.0f,	1.0f,	0.0f, // 0
		-0.14f,	-0.16f,	-0.06f,	21*n,	10*n,	0.0f,	1.0f,	0.0f, // 3

		-0.14f,	-0.16f,	-0.06f,	21*n,	10*n,	0.0f,	1.0f,	0.0f, // 3
		0.14f,	-0.16f,	-0.06f,	14*n,	10*n,	0.0f,	1.0f,	0.0f, // 2
		0.14f,	-0.16f,	0.06f,	14*n,	13*n,	0.0f,	1.0f,	0.0f, // 1

	};
	
	// Brazo izquierdo
	GLfloat brazoL_vertices[] = {
		// x	  y		  z		 u		  v		  nx	 ny		 nz
		
		// front
		-0.04f,	-0.26f,	0.06f,	22*n,	15*n,	0.0f,	0.0f,	-1.0f, // 0
		0.04f,	-0.26f,	0.06f,	22*n,	18*n,	0.0f,	0.0f,	-1.0f, // 1
		0.04f,	0.06f,	0.06f,	14*n,	18*n,	0.0f,	0.0f,	-1.0f, // 5
		
		0.04f,	0.06f,	0.06f,	14*n,	18*n,	0.0f,	0.0f,	-1.0f, // 5
		-0.04f,	0.06f,	0.06f,	14*n,	15*n,	0.0f,	0.0f,	-1.0f, // 4
		-0.04f,	-0.26f,	0.06f,	22*n,	15*n,	0.0f,	0.0f,	-1.0f, // 0

		// right
		0.04f,	-0.26f,	0.06f,	22*n,	15*n,	-1.0f,	0.0f,	0.0f, // 1
		0.04f,	-0.26f,	-0.06f,	22*n,	18*n,	-1.0f,	0.0f,	0.0f, // 2
		0.04f,	0.06f,	-0.06f,	14*n,	18*n,	-1.0f,	0.0f,	0.0f, // 6
		
		0.04f,	0.06f,	-0.06f,	14*n,	18*n,	-1.0f,	0.0f,	0.0f, // 6
		0.04f,	0.06f,	0.06f,	14*n,	15*n,	-1.0f,	0.0f,	0.0f, // 5
		0.04f,	-0.26f,	0.06f,	22*n,	15*n,	-1.0f,	0.0f,	0.0f, // 1

		// back
		0.04f,	-0.26f,	-0.06f,	22*n,	15*n,	0.0f,	0.0f,	1.0f, // 2
		-0.04f,	-0.26f,	-0.06f,	22*n,	18*n,	0.0f,	0.0f,	1.0f, // 3
		-0.04f,	0.06f,	-0.06f,	14*n,	18*n,	0.0f,	0.0f,	1.0f, // 7
		
		-0.04f,	0.06f,	-0.06f,	14*n,	18*n,	0.0f,	0.0f,	1.0f, // 7
		0.04f,	0.06f,	-0.06f,	14*n,	15*n,	0.0f,	0.0f,	1.0f, // 6
		0.04f,	-0.26f,	-0.06f,	22*n,	15*n,	0.0f,	0.0f,	1.0f, // 2

		// left
		-0.04f,	-0.26f,	-0.06f,	22*n,	15*n,	1.0f,	0.0f,	0.0f, // 3
		-0.04f,	-0.26f,	0.06f,	22*n,	18*n,	1.0f,	0.0f,	0.0f, // 0
		-0.04f,	0.06f,	0.06f,	14*n,	18*n,	1.0f,	0.0f,	0.0f, // 4
		
		-0.04f,	0.06f,	0.06f,	14*n,	18*n,	1.0f,	0.0f,	0.0f, // 4
		-0.04f,	0.06f,	-0.06f,	14*n,	15*n,	1.0f,	0.0f,	0.0f, // 7
		-0.04f,	-0.26f,	-0.06f,	22*n,	15*n,	1.0f,	0.0f,	0.0f, // 3

		// top
		-0.04f,	0.06f,	0.06f,	14*n,	15*n,	0.0f,	-1.0f,	0.0f, // 4
		0.04f,	0.06f,	0.06f,	14*n,	18*n,	0.0f,	-1.0f,	0.0f, // 5
		0.04f,	0.06f,	-0.06f,	17*n,	18*n,	0.0f,	-1.0f,	0.0f, // 6
		
		0.04f,	0.06f,	-0.06f,	17*n,	18*n,	0.0f,	-1.0f,	0.0f, // 6
		-0.04f,	0.06f,	-0.06f,	17*n,	15*n,	0.0f,	-1.0f,	0.0f, // 7
		-0.04f,	0.06f,	0.06f,	14*n,	15*n,	0.0f,	-1.0f,	0.0f, // 4

		// bottom
		0.04f,	-0.26f,	0.06f,	22*n,	18*n,	0.0f,	1.0f,	0.0f, // 1
		-0.04f,	-0.26f,	0.06f,	22*n,	15*n,	0.0f,	1.0f,	0.0f, // 0
		-0.04f,	-0.26f,	-0.06f,	19*n,	15*n,	0.0f,	1.0f,	0.0f, // 3
	
		-0.04f,	-0.26f,	-0.06f,	19*n,	15*n,	0.0f,	1.0f,	0.0f, // 3
		0.04f,	-0.26f,	-0.06f,	19*n,	18*n,	0.0f,	1.0f,	0.0f, // 2
		0.04f,	-0.26f,	0.06f,	22*n,	18*n,	0.0f,	1.0f,	0.0f, // 1
	};
	
	// Pierna izquierda
	GLfloat piernaL_vertices[] = {
		// x	  y		  z		 u		  v		  nx	 ny		 nz
		// 
		// top
		-0.06f,	-0.32f,	0.06f,	25*n,	20*n,	0.0f,	0.0f,	-1.0f, // 0
		0.06f,	-0.32f,	0.06f,	28*n,	20*n,	0.0f,	0.0f,	-1.0f, // 1
		0.06f,	0.04f,	0.06f,	28*n,	29*n,	0.0f,	0.0f,	-1.0f, // 5

		0.06f,	0.04f,	0.06f,	28*n,	29*n,	0.0f,	0.0f,	-1.0f, // 5
		-0.06f,	0.04f,	0.06f,	25*n,	29*n,	0.0f,	0.0f,	-1.0f, // 4
		-0.06f,	-0.32f,	0.06f,	25*n,	20*n,	0.0f,	0.0f,	-1.0f, // 0

		// right
		0.06f,	-0.32f,	0.06f,	27*n,	20*n,	-1.0f,	0.0f,	0.0f, // 1
		0.06f,	-0.32f,	-0.06f,	30*n,	20*n,	-1.0f,	0.0f,	0.0f, // 2
		0.06f,	0.04f,	-0.06f,	30*n,	29*n,	-1.0f,	0.0f,	0.0f, // 6

		0.06f,	0.04f,	-0.06f,	30*n,	29*n,	-1.0f,	0.0f,	0.0f, // 6
		0.06f,	0.04f,	0.06f,	27*n,	29*n,	-1.0f,	0.0f,	0.0f, // 5
		0.06f,	-0.32f,	0.06f,	27*n,	20*n,	-1.0f,	0.0f,	0.0f, // 1

		// back
		0.06f,	-0.32f,	-0.06f,	28*n,	20*n,	0.0f,	0.0f,	1.0f, // 2
		-0.06f,	-0.32f,	-0.06f,	31*n,	20*n,	0.0f,	0.0f,	1.0f, // 3
		-0.06f,	0.04f,	-0.06f,	31*n,	29*n,	0.0f,	0.0f,	1.0f, // 7

		-0.06f,	0.04f,	-0.06f,	31*n,	29*n,	0.0f,	0.0f,	1.0f, // 7
		0.06f,	0.04f,	-0.06f,	28*n,	29*n,	0.0f,	0.0f,	1.0f, // 6
		0.06f,	-0.32f,	-0.06f,	28*n,	20*n,	0.0f,	0.0f,	1.0f, // 2

		// left
		-0.06f,	-0.32f,	-0.06f,	28*n,	20*n,	1.0f,	0.0f,	0.0f, // 3
		-0.06f,	-0.32f,	0.06f,	31*n,	20*n,	1.0f,	0.0f,	0.0f, // 0
		-0.06f,	0.04f,	0.06f,	31*n,	29*n,	1.0f,	0.0f,	0.0f, // 4

		-0.06f,	0.04f,	0.06f,	31*n,	29*n,	1.0f,	0.0f,	0.0f, // 4
		-0.06f,	0.04f,	-0.06f,	28*n,	29*n,	1.0f,	0.0f,	0.0f, // 7
		-0.06f,	-0.32f,	-0.06f,	28*n,	20*n,	1.0f,	0.0f,	0.0f, // 3

		// top 
		-0.06f,	0.04f,	0.06f,	31*n,	29*n,	0.0f,	-1.0f,	0.0f, // 4
		0.06f,	0.04f,	0.06f,	28*n,	29*n,	0.0f,	-1.0f,	0.0f, // 5
		0.06f,	0.04f,	-0.06f,	28*n,	25*n,	0.0f,	-1.0f,	0.0f, // 6

		0.06f,	0.04f,	-0.06f,	28*n,	25*n,	0.0f,	-1.0f,	0.0f, // 6
		-0.06f,	0.04f,	-0.06f,	31*n,	25*n,	0.0f,	-1.0f,	0.0f, // 7
		-0.06f,	0.04f,	0.06f,	31*n,	29*n,	0.0f,	-1.0f,	0.0f, // 4

		// bottom 
		0.06f,	-0.32f,	0.06f,	28*n,	20*n,	0.0f,	1.0f,	0.0f, // 1
		-0.06f,	-0.32f,	0.06f,	25*n,	20*n,	0.0f,	1.0f,	0.0f, // 0
		-0.06f,	-0.32f,	-0.06f,	25*n,	23*n,	0.0f,	1.0f,	0.0f, // 3

		-0.06f,	-0.32f,	-0.06f,	25*n,	23*n,	0.0f,	1.0f,	0.0f, // 3
		0.06f,	-0.32f,	-0.06f,	28*n,	23*n,	0.0f,	1.0f,	0.0f, // 2
		0.06f,	-0.32f,	0.06f,	28*n,	20*n,	0.0f,	1.0f,	0.0f, // 1
	};

	// Pierna derecha
	GLfloat piernaR_vertices[] = {
		// x	  y		  z		 u		  v		  nx	 ny		 nz
		// 
		// front
		-0.06f,	-0.32f,	0.06f,	28*n,	20*n,	0.0f,	0.0f,	-1.0f, // 0
		0.06f,	-0.32f,	0.06f,	31*n,	20*n,	0.0f,	0.0f,	-1.0f, // 1
		0.06f,	0.04f,	0.06f,	31*n,	29*n,	0.0f,	0.0f,	-1.0f, // 5

		0.06f,	0.04f,	0.06f,	31*n,	29*n,	0.0f,	0.0f,	-1.0f, // 5
		-0.06f,	0.04f,	0.06f,	28*n,	29*n,	0.0f,	0.0f,	-1.0f, // 4
		-0.06f,	-0.32f,	0.06f,	28*n,	20*n,	0.0f,	0.0f,	-1.0f, // 0

		// right
		0.06f,	-0.32f,	0.06f,	28*n,	20*n,	-1.0f,	0.0f,	0.0f, // 1
		0.06f,	-0.32f,	-0.06f,	31*n,	20*n,	-1.0f,	0.0f,	0.0f, // 2
		0.06f,	0.04f,	-0.06f,	31*n,	29*n,	-1.0f,	0.0f,	0.0f, // 6

		0.06f,	0.04f,	-0.06f,	31*n,	29*n,	-1.0f,	0.0f,	0.0f, // 6
		0.06f,	0.04f,	0.06f,	28*n,	29*n,	-1.0f,	0.0f,	0.0f, // 5
		0.06f,	-0.32f,	0.06f,	28*n,	20*n,	-1.0f,	0.0f,	0.0f, // 1

		// back
		0.06f,	-0.32f,	-0.06f,	28*n,	20*n,	0.0f,	0.0f,	1.0f, // 2
		-0.06f,	-0.32f,	-0.06f,	31*n,	20*n,	0.0f,	0.0f,	1.0f, // 3
		-0.06f,	0.04f,	-0.06f,	31*n,	29*n,	0.0f,	0.0f,	1.0f, // 7

		-0.06f,	0.04f,	-0.06f,	31*n,	29*n,	0.0f,	0.0f,	1.0f, // 7
		0.06f,	0.04f,	-0.06f,	28*n,	29*n,	0.0f,	0.0f,	1.0f, // 6
		0.06f,	-0.32f,	-0.06f,	28*n,	20*n,	0.0f,	0.0f,	1.0f, // 2

		// left
		-0.06f,	-0.32f,	-0.06f,	28*n,	20*n,	1.0f,	0.0f,	0.0f, // 3
		-0.06f,	-0.32f,	0.06f,	31*n,	20*n,	1.0f,	0.0f,	0.0f, // 0
		-0.06f,	0.04f,	0.06f,	31*n,	29*n,	1.0f,	0.0f,	0.0f, // 4

		-0.06f,	0.04f,	0.06f,	31*n,	29*n,	1.0f,	0.0f,	0.0f, // 4
		-0.06f,	0.04f,	-0.06f,	28*n,	29*n,	1.0f,	0.0f,	0.0f, // 7
		-0.06f,	-0.32f,	-0.06f,	28*n,	20*n,	1.0f,	0.0f,	0.0f, // 3

		// top
		-0.06f,	0.04f,	0.06f,	31*n,	29*n,	0.0f,	-1.0f,	0.0f, // 4
		0.06f,	0.04f,	0.06f,	28*n,	29*n,	0.0f,	-1.0f,	0.0f, // 5
		0.06f,	0.04f,	-0.06f,	28*n,	25*n,	0.0f,	-1.0f,	0.0f, // 6

		0.06f,	0.04f,	-0.06f,	28*n,	25*n,	0.0f,	-1.0f,	0.0f, // 6
		-0.06f,	0.04f,	-0.06f,	31*n,	25*n,	0.0f,	-1.0f,	0.0f, // 7
		-0.06f,	0.04f,	0.06f,	31*n,	29*n,	0.0f,	-1.0f,	0.0f, // 4

		// bottom
		0.06f,	-0.32f,	0.06f,	28*n,	20*n,	0.0f,	1.0f,	0.0f, // 1
		-0.06f,	-0.32f,	0.06f,	25*n,	20*n,	0.0f,	1.0f,	0.0f, // 0
		-0.06f,	-0.32f,	-0.06f,	25*n,	23*n,	0.0f,	1.0f,	0.0f, // 3

		-0.06f,	-0.32f,	-0.06f,	25*n,	23*n,	0.0f,	1.0f,	0.0f, // 3
		0.06f,	-0.32f,	-0.06f,	28*n,	23*n,	0.0f,	1.0f,	0.0f, // 2
		0.06f,	-0.32f,	0.06f,	28*n,	20*n,	0.0f,	1.0f,	0.0f, // 1
	};

	// Entre pierna
	GLfloat entrePierna_vertices[] = {
		// x	  y		  z		 u		  v		  nx	 ny		 nz
		// front
		-0.02f,	-0.04f,	0.06f,	31 * n,	29 * n,	0.0f,	0.0f,	-1.0f, // 0
		0.02f,	-0.04f,	0.06f,	28 * n,	29 * n,	0.0f,	0.0f,	-1.0f, // 1
		0.02f,	0.04f,	0.06f,	28 * n,	25 * n,	0.0f,	0.0f,	-1.0f, // 5

		0.02f,	0.04f,	0.06f,	28 * n,	25 * n,	0.0f,	0.0f,	-1.0f, // 5
		-0.02f,	0.04f,	0.06f,	31 * n,	25 * n,	0.0f,	0.0f,	-1.0f, // 4
		-0.02f,	-0.04f,	0.06f,	31 * n,	29 * n,	0.0f,	0.0f,	-1.0f, // 0

		// right
		0.02f,	-0.04f,	0.06f,	31 * n,	29 * n,	-1.0f,	0.0f,	0.0f, // 1
		0.02f,	-0.04f,	-0.06f,	28 * n,	29 * n,	-1.0f,	0.0f,	0.0f, // 2
		0.02f,	0.04f,	-0.06f,	28 * n,	25 * n,	-1.0f,	0.0f,	0.0f, // 6

		0.02f,	0.04f,	-0.06f,	28 * n,	25 * n,	-1.0f,	0.0f,	0.0f, // 6
		0.02f,	0.04f,	0.06f,	31 * n,	25 * n, -1.0f,	0.0f,	0.0f, // 5
		0.02f,	-0.04f,	0.06f,	31 * n,	29 * n,	-1.0f,	0.0f,	0.0f, // 1

		// back
		0.02f,	-0.04f,	-0.06f,	31 * n,	29 * n,	0.0f,	0.0f,	1.0f, // 2
		-0.02f,	-0.04f,	-0.06f,	28 * n,	29 * n,	0.0f,	0.0f,	1.0f, // 3
		-0.02f,	0.04f,	-0.06f,	28 * n,	25 * n,	0.0f,	0.0f,	1.0f, // 7

		-0.02f,	0.04f,	-0.06f,	28 * n,	25 * n,	0.0f,	0.0f,	1.0f, // 7
		0.02f,	0.04f,	-0.06f,	31 * n,	25 * n,	0.0f,	0.0f,	1.0f, // 6
		0.02f,	-0.04f,	-0.06f,	31 * n,	29 * n,	0.0f,	0.0f,	1.0f, // 2

		// left
		-0.02f,	-0.04f,	-0.06f,	31 * n,	29 * n, 1.0f,	0.0f,	0.0f, // 3
		-0.02f,	-0.04f,	0.06f,	28 * n,	29 * n,	1.0f,	0.0f,	0.0f, // 0
		-0.02f,	0.04f,	0.06f,	28 * n,	25 * n,	1.0f,	0.0f,	0.0f, // 4

		-0.06f,	0.04f,	0.06f,	28 * n,	25 * n,	1.0f,	0.0f,	0.0f, // 4
		-0.06f,	0.04f,	-0.06f,	31 * n,	25 * n,	1.0f,	0.0f,	0.0f, // 7
		-0.06f,	-0.04f,	-0.06f,	31 * n,	29 * n,	1.0f,	0.0f,	0.0f, // 3

		// top
		-0.02f,	0.04f,	0.06f,	31 * n,	29 * n,	0.0f,	-1.0f,	0.0f, // 4
		0.02f,	0.04f,	0.06f,	28 * n,	29 * n,	0.0f,	-1.0f,	0.0f, // 5
		0.02f,	0.04f,	-0.06f,	28 * n,	25 * n,	0.0f,	-1.0f,	0.0f, // 6

		0.02f,	0.04f,	-0.06f,	28 * n,	25 * n,	0.0f,	-1.0f,	0.0f, // 6
		-0.02f,	0.04f,	-0.06f,	31 * n,	25 * n,	0.0f,	-1.0f,	0.0f, // 7
		-0.02f,	0.04f,	0.06f,	31 * n,	29 * n,	0.0f,	-1.0f,	0.0f, // 4

		// bottom
		0.02f,	-0.04f,	0.06f,	31 * n,	29 * n,	0.0f,	1.0f,	0.0f, // 1
		-0.02f,	-0.04f,	0.06f,	28 * n,	29 * n,	0.0f,	1.0f,	0.0f, // 0
		-0.02f,	-0.04f,	-0.06f,	28 * n,	25 * n,	0.0f,	1.0f,	0.0f, // 3

		-0.02f,	-0.04f,	-0.06f,	28 * n,	25 * n,	0.0f,	1.0f,	0.0f, // 3
		0.02f,	-0.04f,	-0.06f,	31 * n,	25 * n,	0.0f,	1.0f,	0.0f, // 2
		0.02f,	-0.04f,	0.06f,	31 * n,	29 * n,	0.0f,	1.0f,	0.0f, // 1
	};

	// Hombro derecho
	GLfloat brazoR1_vertices[] = {
		// x	  y		  z		 u		  v		  nx	 ny		 nz
		// front
		-0.04f,	-0.14f,	0.06f,	19*n,	15*n,	0.0f,	0.0f,	-1.0f, // 0
		0.04f,	-0.14f,	0.06f,	19*n,	18*n,	0.0f,	0.0f,	-1.0f, // 1
		0.04f,	0.06f,	0.06f,	14*n,	18*n,	0.0f,	0.0f,	-1.0f, // 5

		0.04f,	0.06f,	0.06f,	14*n,	18*n,	0.0f,	0.0f,	-1.0f, // 5
		-0.04f,	0.06f,	0.06f,	14*n,	15*n,	0.0f,	0.0f,	-1.0f, // 4
		-0.04f,	-0.14f,	0.06f,	19*n,	15*n,	0.0f,	0.0f,	-1.0f, // 0

		// right
		0.04f,	-0.14f,	0.06f,	19*n,	15*n,	-1.0f,	0.0f,	0.0f, // 1
		0.04f,	-0.14f,	-0.06f,	19*n,	18*n,	-1.0f,	0.0f,	0.0f, // 2
		0.04f,	0.06f,	-0.06f,	14*n,	18*n,	-1.0f,	0.0f,	0.0f, // 6

		0.04f,	0.06f,	-0.06f,	14*n,	18*n,	-1.0f,	0.0f,	0.0f, // 6
		0.04f,	0.06f,	0.06f,	14*n,	15*n,	-1.0f,	0.0f,	0.0f, // 5
		0.04f,	-0.14f,	0.06f,	19*n,	15*n,	-1.0f,	0.0f,	0.0f, // 1

		// back
		0.04f,	-0.14f,	-0.06f,	19*n,	15*n,	0.0f,	0.0f,	1.0f, // 2
		-0.04f,	-0.14f,	-0.06f,	19*n,	18*n,	0.0f,	0.0f,	1.0f, // 3
		-0.04f,	0.06f,	-0.06f,	14*n,	18*n,	0.0f,	0.0f,	1.0f, // 7

		-0.04f,	0.06f,	-0.06f,	14*n,	18*n,	0.0f,	0.0f,	1.0f, // 7
		0.04f,	0.06f,	-0.06f,	14*n,	15*n,	0.0f,	0.0f,	1.0f, // 6
		0.04f,	-0.14f,	-0.06f,	19*n,	15*n,	0.0f,	0.0f,	1.0f, // 2

		// left
		-0.04f,	-0.14f,	-0.06f,	19*n,	15*n,	1.0f,	0.0f,	0.0f, // 3
		-0.04f,	-0.14f,	0.06f,	19*n,	18*n,	1.0f,	0.0f,	0.0f, // 0
		-0.04f,	0.06f,	0.06f,	14*n,	18*n,	1.0f,	0.0f,	0.0f, // 4

		-0.04f,	0.06f,	0.06f,	14*n,	18*n,	1.0f,	0.0f,	0.0f, // 4
		-0.04f,	0.06f,	-0.06f,	14*n,	15*n,	1.0f,	0.0f,	0.0f, // 7
		-0.04f,	-0.14f,	-0.06f,	19*n,	15*n,	1.0f,	0.0f,	0.0f, // 3

		// top
		-0.04f,	0.06f,	0.06f,	19*n,	15*n,	0.0f,	-1.0f,	0.0f, // 4
		0.04f,	0.06f,	0.06f,	19*n,	18*n,	0.0f,	-1.0f,	0.0f, // 5
		0.04f,	0.06f,	-0.06f,	14*n,	18*n,	0.0f,	-1.0f,	0.0f, // 6

		0.04f,	0.06f,	-0.06f,	14*n,	18*n,	0.0f,	-1.0f,	0.0f, // 6
		-0.04f,	0.06f,	-0.06f,	14*n,	15*n,	0.0f,	-1.0f,	0.0f, // 7
		-0.04f,	0.06f,	0.06f,	19*n,	15*n,	0.0f,	-1.0f,	0.0f, // 4

		// bottom
		0.04f,	-0.14f,	0.06f,	22*n,	18*n,	0.0f,	1.0f,	0.0f, // 1
		-0.04f,	-0.14f,	0.06f,	22*n,	15*n,	0.0f,	1.0f,	0.0f, // 0
		-0.04f,	-0.14f,	-0.06f,	19*n,	15*n,	0.0f,	1.0f,	0.0f, // 3

		-0.04f,	-0.14f,	-0.06f,	19*n,	15*n,	0.0f,	1.0f,	0.0f, // 3
		0.04f,	-0.14f,	-0.06f,	19*n,	18*n,	0.0f,	1.0f,	0.0f, // 2
		0.04f,	-0.14f,	0.06f,	22*n,	18*n,	0.0f,	1.0f,	0.0f, // 1
	};
	
	// Brazo derecho
	GLfloat brazoR2_vertices[] = {
		// x	  y		  z		 u		  v		  nx	 ny		 nz
		// front
		-0.04f,	-0.12f,	0.06f,	22*n,	18*n,	0.0f,	0.0f,	-1.0f, // 0
		0.04f,	-0.12f,	0.06f,	22*n,	15*n,	0.0f,	0.0f,	-1.0f, // 1
		0.04f,	0.0f,	0.06f,	19*n,	15*n,	0.0f,	0.0f,	-1.0f, // 5

		0.04f,	0.0f,	0.06f,	19*n,	15*n,	0.0f,	0.0f,	-1.0f, // 5
		-0.04f,	0.0f,	0.06f,	19*n,	18*n,	0.0f,	0.0f,	-1.0f, // 4
		-0.04f,	-0.12f,	0.06f,	22*n,	18*n,	0.0f,	0.0f,	-1.0f, // 0

		// right
		0.04f,	-0.12f,	0.06f,	22*n,	18*n,	-1.0f,	0.0f,	0.0f, // 1
		0.04f,	-0.12f,	-0.06f,	22*n,	15*n,	-1.0f,	0.0f,	0.0f, // 2
		0.04f,	0.0f,	-0.06f,	19*n,	15*n,	-1.0f,	0.0f,	0.0f, // 6

		0.04f,	0.0f,	-0.06f,	19*n,	15*n,	-1.0f,	0.0f,	0.0f, // 6
		0.04f,	0.0f,	0.06f,	19*n,	18*n,	-1.0f,	0.0f,	0.0f, // 5
		0.04f,	-0.12f,	0.06f,	22*n,	18*n,	-1.0f,	0.0f,	0.0f, // 1

		// back
		0.04f,	-0.12f,	-0.06f,	22*n,	18*n,	0.0f,	0.0f,	1.0f, // 2
		-0.04f,	-0.12f,	-0.06f,	22*n,	15*n,	0.0f,	0.0f,	1.0f, // 3
		-0.04f,	0.0f,	-0.06f,	19*n,	15*n,	0.0f,	0.0f,	1.0f, // 7

		-0.04f,	0.0f,	-0.06f,	19*n,	15*n,	0.0f,	0.0f,	1.0f, // 7
		0.04f,	0.0f,	-0.06f,	19*n,	18*n,	0.0f,	0.0f,	1.0f, // 6
		0.04f,	-0.12f,	-0.06f,	22*n,	18*n,	0.0f,	0.0f,	1.0f, // 2

		// left
		-0.04f,	-0.12f,	-0.06f,	22*n,	18*n,	1.0f,	0.0f,	0.0f, // 3
		-0.04f,	-0.12f,	0.06f,	22*n,	15*n,	1.0f,	0.0f,	0.0f, // 0
		-0.04f,	0.0f,	0.06f,	19*n,	15*n,	1.0f,	0.0f,	0.0f, // 4

		-0.04f,	0.0f,	0.06f,	19*n,	15*n,	1.0f,	0.0f,	0.0f, // 4
		-0.04f,	0.0f,	-0.06f,	19*n,	18*n,	1.0f,	0.0f,	0.0f, // 7
		-0.04f,	-0.12f,	-0.06f,	22*n,	18*n,	1.0f,	0.0f,	0.0f, // 3

		// top
		-0.04f,	0.0f,	0.06f,	22*n,	18*n,	0.0f,	-1.0f,	0.0f, // 4
		0.04f,	0.0f,	0.06f,	22*n,	15*n,	0.0f,	-1.0f,	0.0f, // 5
		0.04f,	0.0f,	-0.06f,	19*n,	15*n,	0.0f,	-1.0f,	0.0f, // 6

		0.04f,	0.0f,	-0.06f,	19*n,	15*n,	0.0f,	-1.0f,	0.0f, // 6
		-0.04f,	0.0f,	-0.06f,	19*n,	18*n,	0.0f,	-1.0f,	0.0f, // 7
		-0.04f,	0.0f,	0.06f,	22*n,	18*n,	0.0f,	-1.0f,	0.0f, // 4

		// bottom
		0.04f,	-0.12f,	0.06f,	22*n,	18*n,	0.0f,	1.0f,	0.0f, // 1
		-0.04f,	-0.12f,	0.06f,	22*n,	15*n,	0.0f,	1.0f,	0.0f, // 0
		-0.04f,	-0.12f,	-0.06f,	19*n,	15*n,	0.0f,	1.0f,	0.0f, // 3

		-0.04f,	-0.12f,	-0.06f,	19*n,	15*n,	0.0f,	1.0f,	0.0f, // 3
		0.04f,	-0.12f,	-0.06f,	19*n,	18*n,	0.0f,	1.0f,	0.0f, // 2
		0.04f,	-0.12f,	0.06f,	22*n,	18*n,	0.0f,	1.0f,	0.0f, // 1
	};

	Mesh* cuerpo = new Mesh(); //2
	cuerpo->CreateMesh(cuerpo_vertices, prisma_indices, 8 * c, c);
	meshList.push_back(cuerpo);

	Mesh* cabeza = new Mesh(); //3
	cabeza->CreateMesh(cabeza_vertices, prisma_indices, 8 * c, c);
	meshList.push_back(cabeza);

	Mesh* sombrero = new Mesh(); //4
	sombrero->CreateMesh(sombrero_vertices, sombrero_indices, 8 * x, x);
	meshList.push_back(sombrero);

	Mesh* brazoL = new Mesh(); //5
	brazoL->CreateMesh(brazoL_vertices, prisma_indices, 8 * c, c);
	meshList.push_back(brazoL);

	Mesh* piernaL = new Mesh(); //6
	piernaL->CreateMesh(piernaL_vertices, prisma_indices, 8 * c, c);
	meshList.push_back(piernaL);

	Mesh* piernaR = new Mesh(); //7
	piernaR->CreateMesh(piernaR_vertices, prisma_indices, 8 * c, c);
	meshList.push_back(piernaR);

	Mesh* brazoR1 = new Mesh(); //8
	brazoR1->CreateMesh(brazoR1_vertices, prisma_indices, 8 * c, c);
	meshList.push_back(brazoR1);

	Mesh* brazoR2 = new Mesh(); //9
	brazoR2->CreateMesh(brazoR2_vertices, prisma_indices, 8 * c, c);
	meshList.push_back(brazoR2);

	Mesh* entrePierna = new Mesh(); //10
	entrePierna->CreateMesh(entrePierna_vertices, prisma_indices, 8 * c, c);
	meshList.push_back(entrePierna);
}