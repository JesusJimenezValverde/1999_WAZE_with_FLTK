#include <iostream>
#include <string>

using namespace std;

typedef long int pIndex;
const int MaxT = 300;

struct TKey {
	//Mantiene el valor de una llave y un puntero al numero de registro
	// en el archivo directo que contiene esa llave
	int valor; //Llave
	double distancia;
	double vMaxima;
	double vPromedio;
	//pIndex pRegistro; //Puntero al registro en el archivo directo

	TKey(int origen, int destino,double dist,double vMax,double vProm) {
		valor = 1000 * (1000 + origen) + destino;
		distancia = dist;
		vMaxima = vMax;
		vPromedio = vProm;
	}
	TKey() {
		valor = 0;
		distancia = 0.0;
		vMaxima = 0.0;
		vPromedio = 0.0;
	}
};