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

typedef struct Nodo*enlace;

Fl_Button *LineaALinea;
Fl_Button *Correr;
Fl_Button *Limpiar;
Fl_Button *Salir;
Fl_Input *entradaNum;
Fl_Text_Buffer *buff;
Fl_Text_Display *disp; 

////////////////////////////////////////////////////////////////////////// Parte grafica //////////////////////////////////////////////////////////////////////////

class Direccion {//x
public:
	int dir;
};


//Direcciones para 50 nodos
Direccion Direccionesx50[50];

//Direcciones para 100 nodos
Direccion Direccionesx100[100];

//Direcciones para 150 nodos
Direccion Direccionesx150[150];

//Direcciones para 200 nodos
Direccion Direccionesx[200];

//Niveles generales
Direccion Niveles[200];



// Nodos
class DrawNodo : public Fl_Widget {
public:
	DrawNodo(int X, int Y, int W, int H, const char*L = 0) : Fl_Widget(X, Y, W, H, L) {
	}
	void draw() {
		cout << "Dibuje el primero" << endl;
		int par = x() - 1; // valor del nodo
		int x = par;
		par = y() - 1; //nivel actual
		int y = par;
		par = w(); //si es 1 es rojo, si es 2 es negro

		int tipo = h();
		if (tipo == 1) {// n<50
			if (par == 1) {
				fl_color(FL_RED);
				double cx = Direccionesx50[x].dir; //X
				double cy = Niveles[y].dir; //Y
				double cc = 4; // Radio
				while (cc > -0.5) {
					fl_circle(cx, cy, cc);
					cc = cc - 0.5;
				}
			}
			else {
				fl_color(FL_BLACK);
				double cx = Direccionesx50[x].dir; //X
				double cy = Niveles[y].dir; //Y
				double cc = 4; // Radio
				while (cc > -0.5) {
					fl_circle(cx, cy, cc);
					cc = cc - 0.5;
				}
			}
		}
		else if (tipo == 2) { // entre 50 y 100
			if (par == 1) {
				fl_color(FL_RED);
				double cx = Direccionesx100[x].dir; //X
				double cy = Niveles[y].dir; //Y
				double cc = 4; // Radio
				while (cc > -0.5) {
					fl_circle(cx, cy, cc);
					cc = cc - 0.5;
				}
			}
			else {
				fl_color(FL_BLACK);
				double cx = Direccionesx100[x].dir; //X
				double cy = Niveles[y].dir; //Y
				double cc = 4; // Radio
				while (cc > -0.5) {
					fl_circle(cx, cy, cc);
					cc = cc - 0.5;
				}
			}
		}
		else if (tipo == 3) { // entre 10 y 150
			if (par == 1) {
				fl_color(FL_RED);
				double cx = Direccionesx150[x].dir; //X
				double cy = Niveles[y].dir; //Y
				double cc = 3; // Radio
				while (cc > -0.5) {
					fl_circle(cx, cy, cc);
					cc = cc - 0.5;
				}
			}
			else {
				fl_color(FL_BLACK);
				double cx = Direccionesx150[x].dir; //X
				double cy = Niveles[y].dir; //Y
				double cc = 3; // Radio
				while (cc > -0.5) {
					fl_circle(cx, cy, cc);
					cc = cc - 0.5;
				}
			}
		}
		else {// de 150 a 200
			if (par == 1) {
				fl_color(FL_RED);
				double cx = Direccionesx[x].dir; //X
				double cy = Niveles[y].dir; //Y
				double cc = 2; // Radio
				while (cc > -0.5) {
					fl_circle(cx, cy, cc);
					cc = cc - 0.5;
				}
			}
			else {
				fl_color(FL_BLACK);
				double cx = Direccionesx[x].dir; //X
				double cy = Niveles[y].dir; //Y
				double cc = 2; // Radio
				while (cc > -0.5) {
					fl_circle(cx, cy, cc);
					cc = cc - 0.5;
				}
			}
		}


	}
};


class DrawPun : public Fl_Widget {
public:
	DrawPun(int X, int Y, int W, int H, const char*L = 0) : Fl_Widget(X, Y, W, H, L) { // salida x, llegada x, nivel act, izq/der
	}
	void draw() {
		fl_color(FL_BLACK);
		int par = x() - 1; // valor del nodo
		int x = par;
		par = y() - 1; //nodo llegada
		int y = par; 
		par = w() - 1; //nivel actual
		int act = par;
		par = h();//si es 1 es izq, si es 2 es derecha

		const char* pereza = label();

		if (pereza == "1") {// n<50
			if (par == 1) {
				double cx = Direccionesx50[x].dir; //X
				double cy = Direccionesx50[y].dir; //X1

				double niv = Niveles[act].dir + 4;

				fl_line(cx, niv, cy, niv + 21);
			}
			else {
				double cx = Direccionesx50[x].dir; //X
				double cy = Direccionesx50[y].dir; //X1

				double niv = Niveles[act].dir + 4;

				fl_line(cx, niv, cy, niv + 21);
			}
		}
		else if (pereza == "2") { // entre 50 y 100
			if (par == 1) {
				double cx = Direccionesx100[x].dir; //X
				double cy = Direccionesx100[y].dir; //X1

				double niv = Niveles[act].dir + 4;

				fl_line(cx, niv, cy, niv + 21);
			}
			else {
				double cx = Direccionesx100[x].dir; //X
				double cy = Direccionesx100[y].dir; //X1

				double niv = Niveles[act].dir + 4;

				fl_line(cx, niv, cy, niv + 21);
			}
		}
		else if (pereza == "3") { // entre 100 y 150
			if (par == 1) {
				double cx = Direccionesx150[x].dir; //X
				double cy = Direccionesx150[y].dir; //X1

				double niv = Niveles[act].dir + 3;

				fl_line(cx, niv, cy, niv + 23);
			}
			else {
				double cx = Direccionesx150[x].dir; //X
				double cy = Direccionesx150[y].dir; //X1

				double niv = Niveles[act].dir + 3;

				fl_line(cx, niv, cy, niv + 23);
			}
		}
		else {// de 150 a 200
			if (par == 1) {
				double cx = Direccionesx[x].dir; //X
				double cy = Direccionesx[y].dir; //X1

				double niv = Niveles[act].dir + 2;

				fl_line(cx, niv, cy, niv + 25);
			}
			else {
				double cx = Direccionesx[x].dir; //X
				double cy = Direccionesx[y].dir; //X1

				double niv = Niveles[act].dir + 2;

				fl_line(cx, niv, cy, niv + 25);
			}
		}
	}
};

//Aqui se guardan los punteros a los nodos para saber si se pueden o se tienen que dibujar o borrar

DrawPun* Punteros[200];
bool Campos[200];
DrawNodo* NodosGraficos[200];


void llenarDirecciones() {
	//Direcciones para 200 nodos
	int cont = 0, x = 35, y = 65;
	while (cont < 200) {
		Direccionesx[cont].dir = x;
		Campos[cont] = false;
		cont++;
		x += 5;
	}
	//Direcciones de los niveles
	cont = 0;
	while (cont < 200) {
		Niveles[cont].dir = y;
		y += 30;
		cont++;
	}
	//Direcciones para n<50 nodos
	cont = 0, x = 35;
	while (cont < 50) {
		Direccionesx50[cont].dir = x;
		cont++;
		x += 20;
	}
	//Direcciones para 50<n<100 nodos
	cont = 0, x = 35;
	while (cont < 100) {
		Direccionesx100[cont].dir = x;
		cont++;
		x += 10;//Cambiarlo
	}
	//Direcciones para 100<n<150 nodos
	cont = 0, x = 35;
	while (cont < 150) {
		Direccionesx150[cont].dir = x;
		cont++;
		x += 6.999;//Cambiarlo
	}


}

int defNum() {
	int cont = 0;
	while (cont < 200) {
		if (Campos[cont] == false) {
			Campos[cont] = true;
			return cont;
		}
		cont++;
	}
}



///							Auxiliares							///

//Nodos 150<n<200
void dibujarArbol(link& p, int nivel) {

	int x5 = p->v + 1, x6 = nivel + 1;

	if (p->nColor == 0) { //0=rojo   1=negro
		NodosGraficos[p->v] = new DrawNodo(x5, x6, 1, 4);
	}
	else {
		NodosGraficos[p->v] = new DrawNodo(x5, x6, 2, 4);
	}
	
	//Punteros

	if (p->izq) {
		dibujarArbol(p->izq, nivel + 1);
		Punteros[defNum()] = new DrawPun(x5, p->izq->v+1, x6, 1, "4");
	}
	if (p->der) {
		dibujarArbol(p->der, nivel + 1);
		Punteros[defNum()] = new DrawPun(x5, p->der->v+1, x6, 2, "4");
	}
}

//Nodos 100<n<150
void dibujarArbol1(link& p, int nivel) {

	int x5 = p->v + 1, x6 = nivel + 1;

	if (p->nColor == 0) { //0=rojo   1=negro
		NodosGraficos[p->v] = new DrawNodo(x5, x6, 1, 3);
	}
	else {
		NodosGraficos[p->v] = new DrawNodo(x5, x6, 2, 3);
	}

	//Nota estoy metiendo dos punteros en una misma direccion.... entonces la solucion sería que se llene el arreglo de punteros en forma ascendente.


	if (p->izq) {
		dibujarArbol1(p->izq, nivel + 1);
		Punteros[defNum()] = new DrawPun(x5, p->izq->v + 1, x6, 1, "3");
	}
	if (p->der) {
		dibujarArbol1(p->der, nivel + 1);
		Punteros[defNum()] = new DrawPun(x5, p->der->v + 1, x6, 2, "3");
	}
}

//Nodos 50<n<100
void dibujarArbol2(link& p, int nivel) {

	int x5 = p->v + 1, x6 = nivel + 1;

	if (p->nColor == 0) { //0=rojo   1=negro
		NodosGraficos[p->v] = new DrawNodo(x5, x6, 1, 2);
	}
	else {
		NodosGraficos[p->v] = new DrawNodo(x5, x6, 2, 2);
	}

	//Nota estoy metiendo dos punteros en una misma direccion.... entonces la solucion sería que se llene el arreglo de punteros en forma ascendente.


	if (p->izq) {
		dibujarArbol2(p->izq, nivel + 1);
		Punteros[defNum()] = new DrawPun(x5, p->izq->v + 1, x6, 1, "2");
	}
	if (p->der) {
		dibujarArbol2(p->der, nivel + 1);
		Punteros[defNum()] = new DrawPun(x5, p->der->v + 1, x6, 2, "2");
	}
}
//Nodos n<50
void dibujarArbol3(link& p, int nivel) {

	int x5 = p->v + 1, x6 = nivel + 1;

	if (p->nColor == 0) { //0=rojo   1=negro
		NodosGraficos[p->v] = new DrawNodo(x5, x6, 1, 1);
	}
	else {
		NodosGraficos[p->v] = new DrawNodo(x5, x6, 2, 1);
	}
	//Punteros
	if (p->izq) {
		dibujarArbol3(p->izq, nivel + 1);
		Punteros[defNum()] = new DrawPun(x5, p->izq->v + 1, x6, 1, "1");
	}
	if (p->der) {
		dibujarArbol3(p->der, nivel + 1);
		Punteros[defNum()] = new DrawPun(x5, p->der->v + 1, x6, 2, "1");
	}
}


///						Call backs						///

void correrCb(Fl_Widget* butt, void * data) {
	butt->deactivate();
	Fl::check();
	Fl_Window *w = (Fl_Window*)data;
	w->begin();
	//Funcion-->

	//Limpia el espacio de entrada
	const char* numerito = entradaNum->value();
	int numeroM;
	stringstream s(numerito);
	s >> numeroM;
	cout << "Numero de nodos: " << numeroM << endl;
	entradaNum->replace(0, entradaNum->size(), NULL, 0);

	//Limpia toda la pantalla ... por hacer ☼ ...
	for (int i = 0; i < 200; i++) {
		//cout << "Borrando " << i << endl;
		w->remove(Punteros[i]);
		w->remove(NodosGraficos[i]);
		Punteros[i] = nullptr;
		NodosGraficos[i] = nullptr;
		Campos[i] = false;
	}


	//Generando el arbol
	int * numeros = genere(numeroM);
	link arbol = nullptr;
	string tira = "";
	for (int i = 0; i < numeroM; i++) {
		RBinsert(arbol, numeros[i]);
		//cout << numeros[i] << endl;
		tira += to_string(numeros[i]);
		tira += ",";
	}
	
	tira = tira.substr(0,tira.size()-1);
	//cout << tira << endl;
	const char * tirita = tira.c_str();
	//Verifica entre que numeros se encuentra la cantidad de nodos solicitada y crea el arbol
	//segun las direcciones dadas para esa cantidad

	if (numeroM >= 0 && numeroM < 51) {
		dibujarArbol3(arbol, 0);
		buff->text(tirita);
		//Se puede hacer un print del arreglo que se inserto al arbol
	}
	else if (numeroM > 50 && numeroM < 101) {
		dibujarArbol2(arbol, 0);
		buff->text(tirita);
		//Se puede hacer un print del arreglo que se inserto al arbol
	}
	else if (numeroM > 100 && numeroM < 151) {
		dibujarArbol1(arbol, 0);
		buff->text(tirita);
		//Se puede hacer un print del arreglo que se inserto al arbol
	}
	else if (numeroM > 150 && numeroM < 201) {
		dibujarArbol(arbol, 0); 
		buff->text(tirita);
		//Se puede hacer un print del arreglo que se inserto al arbol
	}
	else {
		cout << "Ha superado el limite de 200 nodos"<<endl;
		buff->text("Ha superado el limite de 200 nodos");
		// Se puede hacer un print de lo anterior
	}

	//<--Funcion
	w->redraw();
	w->end();
	butt->activate();
}


void close_cb(Fl_Widget* obj, void*)
{
		exit(0);
}


int main(int argc, char **argv) {

	using namespace Graph_lib; 
	using namespace std; 

	llenarDirecciones();

	Fl_Window window(0, 0, 1300, 700, "Dibujando Bosques");

	//------------------------- Caja del control ----------------------------- //
	Fl_Box *box = new Fl_Box(1120, 15, 150, 40, "Control");
	box->box(_FL_PLASTIC_THIN_DOWN_BOX);
	box->labelfont(FL_BOLD + FL_ITALIC);
	box->labelsize(32);
	
	//------------------------- Caja que indica donde se dibuja ----------------------------- //
	Fl_Box *box1 = new Fl_Box(30, 15, 1000, 40, "Dibujo");
	box1->box(_FL_PLASTIC_THIN_DOWN_BOX);
	box1->labelfont(FL_BOLD + FL_ITALIC);
	box1->labelsize(32);
	//------------------------- Texto ----------------------------- //
	Fl_Box *texto = new Fl_Box(1192, 90, 0, 0,"Indique el numero\nmaximo de nodos");
	texto->labelfont(FL_HELVETICA_ITALIC);
	texto->labelsize(17);

	//Entrada de Numero maximo 
	entradaNum = new Fl_Input(1135, 120, 120, 30);

	//Salida del arreglo
	buff = new Fl_Text_Buffer();
	disp = new Fl_Text_Display(30, 600, 1000, 50, "Arreglo introducido");
	disp->buffer(buff);

	// ------------------------- Botones ----------------------------- //
	Fl_Button Correr(1135, 170, 120, 50, "Dibujar");
	Salir = new Fl_Button(1165, 240, 60, 40, "Salir");
	Correr.color(FL_GREEN);
	Salir->color(FL_RED);
	//Funciones//
	Salir->callback((Fl_Callback*)close_cb);
	Correr.callback(correrCb,&window);//////////////////////////////




	window.show();
	return Fl::run();
}
