#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void escribeCabezera(int n, fstream &fs);
template<class T>
char * as_bytes(T& p);

//Metodo para escribir un encabezado entero en un archivo
void escribeCabezera(int n, fstream &fs) {
	//Se posiciona al inicio
	fs.seekp(0);
	fs.write(as_bytes<int>(n), sizeof(n));
}

template<class T>
char * as_bytes(T& p) {
	void * addr = &p;
	return static_cast<char*>(addr);
}

template<class Registro>
class ArchivoDirecto {
private:
	string nArchivo;
	int nRegistros;
	fstream fs;
	bool abierto;
public:
	ArchivoDirecto(){}
	ArchivoDirecto(string nombre) {
		//Verifica si el archivo existe
		fs.open(nombre, ios_base::binary |
			ios_base::in |
			ios_base::out);
		if (!fs) {
			//Crea el archivo
			fs.open(nombre, ios_base::binary | ios_base::out);
			nRegistros = 0;
			escribeCabezera(nRegistros, fs);
			fs.close();
			//Reabre el archivo
			fs.open(nombre, ios_base::binary | ios_base::in | ios_base::out);
		}
		else {
			//El archivo existe
			//Lee la cantidad de registros
			fs.seekg(0);
			fs.read(as_bytes<int>(nRegistros), sizeof(nRegistros));
		};
		nArchivo = nombre;
		abierto = true;
	}
	string info() {
		//Retorna la informacion del archivo
		if (abierto)
			return "Archivo : " + nArchivo + "\nRegistros : " + to_string(this->tam()) + "\n";
		else return "***";
	}
	void abrir(string nArchivo1) {
		fs.open(nArchivo1, ios_base::binary | ios_base::in | ios_base::out);
		abierto = true;
	}
	void cerrar() {
		//Cierra el archivo
		fs.close();
		abierto = false;
	}
	int tam() {
		//Retorna el # de registros en el archivo
		return (abierto ? nRegistros : 0);
	}
	void actualizar(int i, Registro &r) {
		//Actualiza el registro en posicion u
		//Asume que los registros se numeran a partir de a pos 0
		if (abierto && i < nRegistros) {
			fs.seekp(sizeof(int) + i * sizeof(Registro));
			//Escribe el registro
			fs.write(as_bytes<Registro>(r), sizeof(Registro));
		}
	}
	void agregarFinal(Registro &r, int k) {
		//Agrega un registro al final 
		if (abierto) {
			fs.seekp(sizeof(int) + nRegistros * sizeof(Registro));
			fs.write(as_bytes<Registro>(r), sizeof(Registro));
			nRegistros++;
			escribeCabezera(k, fs);
		}
	}
	Registro leer(int i) {
		if (!abierto || i >= nRegistros)
			throw 1001;
		//Se posiciona al inicio del registro
		fs.seekp(sizeof(int) + i * sizeof(Registro));
		Registro r = Registro();
		fs.read(as_bytes<Registro>(r), sizeof(Registro));
		return r;
	}
	void limpiar() {
		if (abierto)
			fs.close();
		fs.open(nArchivo, ios__base::truct | ios__base::in | ios__base::out | ios__base::binary);
		nRegistros = 0;
		escribeCabezera(nRegistros, fs);
	}
};
