#pragma once

#include "Model.h"
#include "Mesh.h"



/**
* @brief Declaraci� nde modelos
*/
extern Model laboon;
extern Model sanji;
extern Model brook;
extern Model Robin;
extern Model Nami;
extern Model Usopp;
extern Model Zoro, Zoro_BR, Zoro_BL, Zoro_PR, Zoro_PL;
extern Model Franky, Franky_BR, Franky_BL, Franky_PR, Franky_PL;
extern Model thousandSunny;
extern Model thousandSunnyDestruido;
extern Model littleGarden;
extern Model reverseMountain;
extern Model metaKnight;


extern std::vector<Mesh*> meshList;
/**
* @brief Funci�n encargada de cargar los modelos
*/
void cargaModelos();
void CreateFloor();
void CreateChest();
void CreateLuffy();