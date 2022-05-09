#pragma once

#include "Model.h"
#include "Mesh.h"


/**
* @brief Declaraci� nde modelos
*/
extern Model laboon;
extern Model sanji;
extern Model brook;
extern Model zoro_bo, zoro_l, zoro_r;
extern Model thousandSunny;
extern Model thousandSunnyDestruido;
extern Model littleGarden;
extern std::vector<Mesh*> meshList;
/**
* @brief Funci�n encargada de cargar los modelos
*/
void cargaModelos();
void CreateFloor();
void CreateChest();
void CreateLuffy();