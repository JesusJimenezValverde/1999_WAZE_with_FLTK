#pragma once
#include <vector>
#include "Graph.h"
#include "Fl_Window.h"
#include "Fl_Multiline_Input.h"
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <string>
#include <stdio.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Progress.H>
#include <vector>
#include <iostream>
#include "ArbolRN.h"
#include "Permutacion.h"
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>
#include "Fl_Multiline_Output.H"
#include "Linea.h"
#include <string>
#include "BTree.h"
#include "DrawNodo.h"
#include <fstream>
#include <iostream>


using namespace std;

struct Nodo {
	int nNodo; //Numero de Nodo
	int x; //Coordenada X
	int y; //Coordenada Y
	int gradoEntrada = 0;
	int gradoSalida = 0;
	Nodo() { nNodo = 0;  x = 0; y = 0; gradoEntrada = 0; gradoSalida = 0; };
	Nodo(string num) { nNodo = atoi(num.c_str()); x = 0; y = 0; gradoEntrada = 0; gradoSalida = 0; };
	Nodo(string num, string x, string y) { nNodo = atoi(num.c_str()); this->x = atoi(x.c_str()); this->y = atoi(y.c_str()); };
};

struct Arco {
	int origen;
	int destino;
	int distancia;
	int vMaxima;
	int vPromedio;
	Arco() { origen = 0; destino = 0; distancia = 0; vMaxima = 0; vPromedio = 0; };
	Arco(string org, string dest, string dist, string vM, string vProm) {
		origen = atoi(org.c_str());
		destino = atoi(dest.c_str());
		distancia = atoi(dist.c_str());
		vMaxima = atoi(vM.c_str());
		vPromedio = atoi(vProm.c_str());
	}

};



class Procesar :Fl_Input
{
public:
	int k; //Cantidad de Vertices en el Grafo
	vector<Nodo> nodos;
	vector<Arco> arcos;
	vector<DrawNodo*>dibujosN;
	vector<Linea*>dibujosA;
	ArchivoDirecto<Nodo>archivoVRT;
	ArchivoDirecto<BTreePage>archivoARC;
	string nArchivo;
	Fl_Box *box;
	Fl_Box *box1;
	Fl_Text_Display *salidas;
	Fl_Text_Buffer *tbuff;
	Fl_Window *window;
	bool ejecutado;
	Fl_Window * ventana;
	//Procesar() {}
	void importarArchivo(string nombre);
	void contarArcos(int N, int K);
	void crearVRT(string nombre);
	void crearARC(string nombre);
	void mostrar();
	void abrir();
	void mostrarArcos();
	void leerTexto() {
		//Limpia el espacio de entrada
		string instruccion = this->value();
		cout << "Instruccion a realizar: '" << instruccion << "'" << endl;
		//Intrucciones
		if (instruccion == "clear") {
			//limpiar todos los iluminadosde nodos y arcos esto es en dinamica
			//borra y reescribe toda la memoria en pantalla

			//Limpia toda la pantalla ... por hacer ☼ ...
			for (int i = 0; i < dibujosN.size(); i++) {
				cout << "Borrando " << i << endl;
				ventana->remove(dibujosN[i]);
			}
			for (int i = 0; i < dibujosA.size(); i++) {
				ventana->remove(dibujosA[i]);
			}
			if (dibujosN.size() > 0) {
				for (int i = dibujosN.size() - 1; i > 0; i--) {
					dibujosN.pop_back();
				}
				dibujosN.pop_back();
			}
			if (dibujosA.size() > 0) {
				for (int i = dibujosA.size() - 1; i > 0; i--) {
					dibujosA.pop_back();
				}
				dibujosA.pop_back();
			}

			dibujaGrafo();
			ventana->redraw();
		}
		else if (instruccion == "close") {
			if (dibujosN.size() > 0 && nodos.size() > 0) {
				for (int i = dibujosN.size() - 1; i > 0; i--) {
					//cout << "Borrando " << i << endl;
					ventana->remove(dibujosN[i]);
					dibujosN.pop_back();
					nodos.pop_back();
				}
				ventana->remove(dibujosN[0]);
				dibujosN.pop_back();
				nodos.pop_back();
				if (dibujosA.size() > 0 && arcos.size() > 0) {
					for (int i = dibujosA.size() - 1; i > 0; i--) {
						//cout << "Borrando " << i << endl;
						ventana->remove(dibujosA[i]);
						dibujosA.pop_back();
						arcos.pop_back();
					}
					ventana->remove(dibujosA[0]);
					dibujosA.pop_back();
					arcos.pop_back();
				}
				tbuff->text("--- Red Cerrada ---\n");
				salidas->buffer(tbuff);

				ventana->redraw();
			}
			else {
				////*** Esto despues de hacer la instruccion si y solo si es valida ***//
				instruccion = "No hay red que cerrar!!! \n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				////*********************************************************************//

			}
		}
		else if (instruccion == "cleart") { //Limpiar la cinta
			tbuff->text("");
			salidas->buffer(tbuff);
		}
		else {
			string sinstruccion = instruccion.substr(0, 3);
			string sinstruccion4 = instruccion.substr(0, 4);
			string sinstruccion5 = instruccion.substr(0, 5);
			string sinstruccion7 = instruccion.substr(0, 7);

			if (sinstruccion == "to ") {
				cout << "LLego un to" << endl;

				string rInstruccion = instruccion.substr(3, instruccion.size());

				//**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);

				//*********************************************************************//

			}
			else if (sinstruccion4 == "spt ") {
				cout << "LLego un spt " << endl;

				string rInstruccion = instruccion.substr(4, instruccion.size());

				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				////*********************************************************************//
			}
			else if (sinstruccion5 == "node ") {
				string nNodo = instruccion.substr(5, instruccion.size());
				int number = std::atoi(nNodo.c_str());

				if (number < dibujosN.size()) {
					ventana->remove(dibujosN[number]);
					dibujosN[number] = new DrawNodo(nodos[number].x + 300, nodos[number].y, 2, 1);
					ventana->add(dibujosN[number]);
					ventana->redraw();

					////*** Esto despues de hacer la instruccion si y solo si es valida ***//
					instruccion = instruccion + "\n";
					const char * inst = instruccion.data();
					tbuff->append(inst);
					string info = "Nodo: " + to_string(number) + "\n" +
						"Coordenada x: " + to_string(nodos[number].x) + "\n" +
						"Coordenada y: " + to_string(nodos[number].y) + "\n" +
						"Grado entrada: " + to_string(nodos[number].gradoEntrada) + "\n" +
						"Grado salida: " + to_string(nodos[number].gradoSalida) + "\n";
					const char * cool = info.data();
					tbuff->append(cool);
					salidas->buffer(tbuff);
					////*********************************************************************//
				}
				else {
					////*** Esto despues de hacer la instruccion si y solo si es valida ***//
					instruccion = "El nodo no existe!!! \n";
					const char * inst = instruccion.data();
					tbuff->append(inst);
					salidas->buffer(tbuff);
					////*********************************************************************//
				}

			}
			else if (sinstruccion5 == "arcs ") {
				cout << "LLego un arcs " << endl;

				string nArcs = instruccion.substr(5, instruccion.size());
				int nprincipal = atoi(nArcs.c_str());
				if (nprincipal < dibujosN.size()) {

					for (int i = 0; i < arcos.size(); i++) {
						ventana->remove(dibujosA[i]);
						if (arcos[i].origen == nprincipal) {
							dibujosA[i] = new Linea(nodos[arcos[i].origen].x + 300, nodos[arcos[i].origen].y,
								nodos[arcos[i].destino].x + 300, nodos[arcos[i].destino].y, 2);
							ventana->add(dibujosA[i]);
						}
						else {
							dibujosA[i] = new Linea(nodos[arcos[i].origen].x + 300, nodos[arcos[i].origen].y,
								nodos[arcos[i].destino].x + 300, nodos[arcos[i].destino].y, 1);
							ventana->add(dibujosA[i]);
						}
					}
					ventana->redraw();
					////*** Esto despues de hacer la instruccion si y solo si es valida ***//
					instruccion = instruccion + "\n";
					const char * inst = instruccion.data();
					tbuff->append(inst);
					salidas->buffer(tbuff);
					////*********************************************************************//
				}
				else {
					////** Esto despues de hacer la instruccion si y solo si es valida **//
					instruccion = "El nodo no existe!!! \n";
					const char * inst = instruccion.data();
					tbuff->append(inst);
					salidas->buffer(tbuff);
					////*********************************************************************//
				}


			}
			else if (sinstruccion5 == "open ") {
				/*cout << "Llego un open" << endl;*/
				string nombArchivo = instruccion.substr(6);
				nombArchivo = nombArchivo.substr(0, nombArchivo.size() - 1);
				cout << "Open: " << nombArchivo<<endl;
				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				ifstream archivo, archivo2;
				archivo.open(nombArchivo+".VRT",ios::in);
				archivo2.open(nombArchivo +".ARC", ios::in);
				string mensaje;
				
				if (archivo.fail() || archivo2.fail()) {
					mensaje = "El archivo .VRT o .ARC no se pudieron abrir \n o no existen.\n";
					tbuff->append(mensaje.data());
					salidas->buffer(tbuff);
					cout << "FALLO LA APERTURA";
				}
				else {
					archivo.close();
					archivo2.close();
					mensaje = "Los archivos .VRT y .ARC se abrieron exitosamente.\n";
					tbuff->append(mensaje.data());
					salidas->buffer(tbuff);
					archivoVRT = { nombArchivo+".VRT" };
					for (int i = 0; i < archivoVRT.tam(); i++) {
						nodos.push_back(archivoVRT.leer(i));
					}
					archivoARC = { nombArchivo + ".ARC" };
					vector<BTreePage>paginas;
					for (int i = 0; i < archivoARC.tam(); i++) {
						paginas.push_back(archivoARC.leer(i));
					}
					//OPERACIONES MODULARES
					int origen, destino;
					for (int i = 0; i < paginas.size(); i++) {
						for (int j = 0; j < 5; j++) {
							if (paginas[i].key[j].valor != 0) {
								TKey aux = paginas[i].key[j];
								origen = (aux.valor / 1000) % 1000;
								destino = aux.valor % 1000;
								arcos.push_back(Arco(to_string(origen), to_string(destino), to_string(aux.distancia), to_string(aux.vMaxima), to_string(aux.vPromedio)));
							}
						}
					}
					this->dibujaGrafo();
				}
			}
			else if (sinstruccion7 == "import ") {
				//Import
				string nombArchivo = instruccion.substr(8);
				nombArchivo = nombArchivo.substr(0,nombArchivo.size()-1);
				this->importarArchivo(nombArchivo);
				nombArchivo = nombArchivo.substr(0, nombArchivo.size() - 4);
				cout << nombArchivo << endl;
				this->crearVRT(nombArchivo);
				this->crearARC(nombArchivo);
				dibujaGrafo();
				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				string aux = "Informacion Leida:\nVertices: " + to_string(nodos.size()) + "\nArcos: " + to_string(arcos.size())+"\n";
				tbuff->append(aux.data());
				salidas->buffer(tbuff);

				////*********************************************************************//
			}
			else {
				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = "Instruccion invalida \n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				////*********************************************************************//
			}
		}
		//Poner en la lista de instrucciones lo que tengo en numeroM******Falta****

		//Reemplaza lo que hay en el cuadro de entrada de texto
		this->replace(0, this->size(), NULL, 0);
	}
	int handle(int e) {
		switch (e) {
		case FL_KEYUP:
			int key = Fl::event_key();
			if (key == FL_Enter) {
				leerTexto();
				//Llamar aqui a la funcion --Leer instruccion--
				return(1);
			}
			break;
		}
		return(Fl_Input::handle(e));    // let Fl_Input handle all other events
	}
	Procesar(int X, int Y, int W, int H, Fl_Window *v,const char*L = 0) :Fl_Input(X, Y, W, H, L) {
		this->ventana = v;
		this->iniciar(); }
	void iniciar(){
	box = new Fl_Box(1, 1, 298, 666, "");
	box->color(FL_WHITE);
	box->box(_FL_PLASTIC_THIN_DOWN_BOX);
	box->labelfont(FL_BOLD + FL_ITALIC);
	box->labelsize(32);
	box1 = new Fl_Box(300, 1, 1000, 698, "");
	box1->color(FL_WHITE);
	box1->box(FL_EMBOSSED_BOX);
	box1->labelfont(FL_BOLD + FL_ITALIC);
	box1->labelsize(32);
	salidas = new Fl_Text_Display(1, 1, 296, 666);
	salidas->textcolor(FL_WHITE);
	salidas->color(FL_DARK_CYAN);
	tbuff = new Fl_Text_Buffer();
	salidas->buffer(tbuff);
	}
	void nRedraw() {
		ventana->redraw();
	}
	void dibujaGrafo() {
		cout <<"Cant de nodos: "<< nodos.size() << endl;

		if (dibujosN.size() > 0 && nodos.size() > 0) {
			for (int i = dibujosN.size() - 1; i > 0; i--) {
				ventana->remove(dibujosN[i]);
				dibujosN.pop_back();
			}
			ventana->remove(dibujosN[0]);
			dibujosN.pop_back();
		}
		for (int i = 0; i < nodos.size(); i++) {
			dibujosN.push_back(new DrawNodo(nodos[i].x + 300, nodos[i].y,1,1));
			ventana->add(dibujosN[i]);
		}
		cout << arcos.size() << endl;
		for (int i = 0; i < arcos.size(); i++) {
			dibujosA.push_back(new Linea(nodos[arcos[i].origen].x+300,nodos[arcos[i].origen].y, 
				nodos[arcos[i].destino].x + 300, nodos[arcos[i].destino].y,1));
			ventana->add(dibujosA[i]);
		}
		ventana->redraw();
	}
};

void Procesar::importarArchivo(string nombre) //Carga los vertices y arcos del .txt
{
	ifstream archivo;
	this->nArchivo = nombre;
	string naux, x, y, vM, vP, red, nom;
	string origen, dest, dist, vMax, vProm, newN, newOrigen, newMax, newX;
	archivo.open(nombre);
	int n = 0;
	int c = 0;
	int f = 0;
	k = 0;
	while (archivo.good()) {
		if (c == 0) { //Carga encabezado
			getline(archivo, red, ',');
			getline(archivo, naux, '\n');
			n = atoi(naux.c_str());
			cout << "La red: " << red << " con nodos: " << n << endl;
			cout << "\n" << "N: " << n << endl;
		}
		else if (c > 0 && c <= n) { //Carga nodos
			getline(archivo, naux, ',');
			getline(archivo, x, ',');
			getline(archivo, y, '\n');
			Nodo n(naux, x, y);
			nodos.push_back(n);
			cout << "Nodo: " << naux << " X: " << x << " Y: " << y << endl;
		}
		else { //Carga arcos

			getline(archivo, origen, ',');
			getline(archivo, dest, ',');
			getline(archivo, dist, ',');
			getline(archivo, vMax, ',');
			getline(archivo, vProm, '\n');
			Arco a(origen, dest, dist, vMax, vProm);
			arcos.push_back(a);
			//k++; CUIDADO
			cout << "Arco " << k++ << " origen: " << origen << " destino: " << dest << " distancia: " << dist << " velocidad Max: " << vMax << " promedio: " << vProm << endl;
		}
		c++;
	}

	contarArcos(arcos.size(), nodos.size());
}
void Procesar::contarArcos(int N, int K) //Calcula grado de entrada y salida
{
	for (int j = 0; j < arcos.size(); j++) {
		cout << arcos[j].origen << endl;
	}
	for (int i = 0; i < nodos.size(); i++) {
		for (int j = 0; j < arcos.size(); j++) {
			if (nodos[i].nNodo == arcos[j].origen) { //Detecta  origen
				nodos[i].gradoSalida += 1;
			}
			if (nodos[i].nNodo == arcos[j].destino) {
				nodos[i].gradoEntrada += 1;
			}
		}
	}

	for (int i = 0; i < K; i++) {
		cout << "Nodo: " << i << " Entrada: " << nodos[i].gradoEntrada << " Salida: " << nodos[i].gradoSalida << endl;
	}
	cout << "** Nodos cargados y leidos **"<<endl;
	cout << arcos.size()<<endl;
}
void Procesar::crearVRT(string nombre) 
{
	archivoVRT = {nombre+".VRT"};
	if (archivoVRT.tam() == 0) {
		for (int i = 0; i < nodos.size(); i++) {
			archivoVRT.agregarFinal(nodos[i], nodos.size());
		}
	}
}
inline void Procesar::crearARC(string nombre)
{
	archivoARC = { nombre + ".ARC" };
	BTreePage pagina;
	for (int i = 0; i < arcos.size(); i++) {
		if (pagina.lleno == false) {
			TKey nueva{arcos[i].origen,arcos[i].destino,(double)arcos[i].distancia,(double)arcos[i].vMaxima,(double)arcos[i].vPromedio};
			pagina.insertarLlave(nueva);
			cout << "vMaxima : " << arcos[i].vMaxima << endl;
		}
		else {
			archivoARC.agregarFinal(pagina, pagina.t);
			cout << "Meti una pagina"<<endl;
			BTreePage pagina{};
		}
	}
	if (!pagina.vacia()) {
		archivoARC.agregarFinal(pagina, pagina.t);
	}

	archivoARC.cerrar();
}
inline void Procesar::mostrar()
{
	cout << "Mostrando"<<endl;
	cout << archivoVRT.tam()<<endl;
	for (int i = 0; i < archivoVRT.tam(); i++) {
		cout << archivoVRT.leer(i).nNodo<<" "<< archivoVRT.leer(i).gradoEntrada<<" "<<archivoVRT.leer(i).gradoSalida<<endl;
	}
	archivoVRT.cerrar();
}
inline void Procesar::abrir()
{
	archivoVRT.abrir(nArchivo);
	cout << archivoVRT.tam()<<endl;
	for (int i = 0; i < archivoVRT.tam(); i++) {
		cout << archivoVRT.leer(i).nNodo << " " << archivoVRT.leer(i).gradoEntrada << " " << archivoVRT.leer(i).gradoSalida << endl;
	}
}
inline void Procesar::mostrarArcos()
{
	archivoARC.abrir("ciudad.ARC");
	for (int i = 0; i < archivoARC.tam(); i++) {
		archivoARC.leer(i).showKeys();
		cout << endl;
	}
}