#include "Carga modelos.h"

Model laboon;
Model sanji;
Model brook;
Model zoro_bo, zoro_l, zoro_r;
Model thousandSunny;
Model thousandSunnyDestruido;

void cargaModelos() {
	laboon = Model();
	laboon.LoadModel("Models/laboon.obj");

	sanji = Model();
	sanji.LoadModel("Models/Sanji.obj");

	brook = Model();
	brook.LoadModel("Models/Brook.obj");

	zoro_bo = Model();
	zoro_bo.LoadModel("Models/Zoro_bo.obj");

	zoro_l = Model();
	zoro_l.LoadModel("Models/Zoro_L.obj");

	zoro_r = Model();
	zoro_r.LoadModel("Models/Zoro_R.obj");

	thousandSunny = Model();
	thousandSunny.LoadModel("Models/Thousand Sunny.obj");

	thousandSunnyDestruido = Model();
	thousandSunnyDestruido.LoadModel("Models/Thousand Sunny Destruido.obj");
}