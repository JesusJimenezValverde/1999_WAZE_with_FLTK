#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "string.h" 

using namespace std;

//Define estructura de los registros
struct Persona {
	char nombre[50];
	int edad;
	Persona(string nombreP,
		int edadP) {
		strcpy(nombre, nombreP.c_str());
		edad = edadP;
	}
};

//Redefine el operador << para persona.
ostream& operator <<(ostream& os, const Persona &p) {
	return os << "[" << p.nombre << "] = " << p.edad << endl;
}

//Utilitarios.
template<class T>
char * as_bytes(T& p) {
	void * addr = &p;
	return static_cast<char*>(addr);
}

//metodo para escirbir un encabezado entero en un archivo
void escribeCabecera(int n, fstream &fs) {
	//se posiciona al inicio
	fs.seekp(0);
	fs.write(as_bytes<int>(n), sizeof(n));
}

//Define la clase archivo directo
template <class Registro>
class ArchivoDirecto {
private:
	string nArchivo;
	int nRegistros;
	fstream fs;
	bool abierto;

public:
	ArchivoDirecto(string nombre) {
		fs.open(nombre, ios_base::binary |
			ios_base::in |
			ios_base::out);
		if (!fs) {
			fs.open(nombre, ios_base::binary |
				ios_base::out);
			nRegistros = 0;
			escribeCabecera(nRegistros, fs);
			fs.close();
			fs.open(nombre, ios_base::binary |
				ios_base::in |
				ios_base::out);
		}
		else {
			fs.seekg(0);
			fs.read(as_bytes<int>(nRegistros), sizeof(nRegistros));
		};
		nArchivo = nombre;
		abierto = true;
	}

	string info() {
		if (abierto) {
			return "Archivo		: " + nArchivo +
				"\nRegistros : " + to_string(this->tam()) + "\n";
		}
		else return "***";
	}

	void cerrar() {
		fs.close();
		abierto = false;
	}

	int tam() {
		return(abierto ? nRegistros : 0);
	}

	void actualizar(int i, Registro& r) {
		if (abierto && i < nRegistros) {
			fs.seekp(sizeof(int) + i * sizeof(Registro));
			fs.write(as_bytes<Registro>(r), sizeof(Registro));
		}
	}

	void agregarFinal(Registro& r) {
		if (abierto) {
			fs.seekp(sizeof(int) + nRegistros * sizeof(Registro));
			fs.write(as_bytes<Registro>(r), sizeof(Registro));
			nRegistros++;
			escribeCabecera(nRegistros, fs);
		}
	}

	Registro leer(int i) {
		if (!abierto || i >= nRegistros)
			throw 1001;
		//Se posiciona al inicio del registro
		fs.seekp(sizeof(int) + i * sizeof(Registro));
		Registro r = Registro("", 0);
		fs.read(as_bytes<Registro>(r), sizeof(Registro));
		return r;
	}

	void limpiar() {
		if (abierto)
			fs.close();
		fs.open(nArchivo, ios_base::trunc | ios_base::in |
			ios_base::out | ios_base::binary);
		nRegistros = 0;
		escribeCabecera(nRegistros, fs);
	}
};