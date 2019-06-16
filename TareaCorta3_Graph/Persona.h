#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

//Define la estructura de los registros
struct Persona {
	char nombre[50];
	int edad;
	Persona() {
	}
	Persona(string nombreP, int edadP) {
		strcpy(nombre, nombreP.c_str());
		edad = edadP;
	}

//Redefine el operando << para Persona
};
ostream & operator <<(ostream& os, const Persona &p) {
	return os << "[" << p.nombre << "]=" << p.edad << endl;
}
