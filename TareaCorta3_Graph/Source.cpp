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
//
//typedef struct Nodo*enlace;
//
Fl_Button *LineaALinea;
Fl_Button *Correr;
Fl_Button *Limpiar;
Fl_Button *Salir;
Fl_Text_Display *salidas;
Fl_Text_Buffer *tbuff;
Fl_Text_Display *disp; 
Fl_Window *window;
//
//////////////////////////////////////////////////////////////////////////// Parte grafica //////////////////////////////////////////////////////////////////////////

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

class MyInput : public Fl_Input {
	//Si hay que meter funciones es bueno hacerlo aqui
	//No he solucionado como modificar la ventana... pienso que sería bueno ponerla como
	 // parametro global
public:

	

	void leerTexto() {
		cout << "Aqui toy" << endl;
		//Limpia el espacio de entrada
		string instruccion = this->value();

		cout << "Instruccion a realizar: '" << instruccion <<"'" << endl;

		//Intrucciones
		if (instruccion == "clear") {


			//limpiar todos los iluminadosde nodos y arcos esto es en dinamica
			//borra y reescribe toda la memoria en pantalla

		//Limpia toda la pantalla ... por hacer ☼ ...
		//for (int i = 0; i < 200; i++) {
		//	//cout << "Borrando " << i << endl;
		//	window->remove(Punteros[i]);
		//	window->remove(NodosGraficos[i]);
		//	Punteros[i] = nullptr;
		//	NodosGraficos[i] = nullptr;
		//	Campos[i] = false;
		//}

		}
		else if (instruccion == "close") {
			//Cerrar grafo actual y limpiar areas de despliegue y cinta
			// limpia los iluminados


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

				//**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);

				//*********************************************************************//

			}
			else if (sinstruccion4 == "spt ") {
				cout << "LLego un spt " << endl;

				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				////*********************************************************************//
			}
			else if (sinstruccion5 == "node ") {
				cout << "Llego un node " << endl;

				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				////*********************************************************************//
			}
			else if (sinstruccion5 == "arcs ") {
				cout << "LLego un arcs " << endl;

				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				////*********************************************************************//
			}
			else if (sinstruccion5 == "open ") {
				cout << "Llego un open" << endl;


				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				////*********************************************************************//
			}
			else if (sinstruccion7 == "import ") {
				cout << "LLego un import " << endl;


				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
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
	MyInput(int X, int Y, int W, int H, const char*L = 0) :Fl_Input(X, Y, W, H, L) {
	}
};






int main(int argc, char **argv) {

	using namespace Graph_lib; 
	using namespace std; 

	llenarDirecciones();

	window = new Fl_Window(20, 40, 1302, 700, "MIWA");
	
	////------------------------- Caja de instrucciones ----------------------------- //
	Fl_Box *box = new Fl_Box(1, 1, 298, 698, "");
	box->color(FL_BLUE);
	box->box(_FL_PLASTIC_THIN_DOWN_BOX);
	box->labelfont(FL_BOLD + FL_ITALIC);
	box->labelsize(32);
	
	////------------------------- Caja de dibujo del grafo ----------------------------- //
	Fl_Box *box1 = new Fl_Box(300, 1, 1000, 698, "");
	box1->color(FL_GRAY);
	box1->box(FL_EMBOSSED_BOX);
	box1->labelfont(FL_BOLD + FL_ITALIC);
	box1->labelsize(32);

	Fl_Box *box2 = new Fl_Box(305, 5, 5, 5, "");
	box2->color(FL_BLUE);
	box2->box(FL_FLAT_BOX);

	//Entrada de Numero maximo 
	MyInput *entradaNum = new MyInput(2, 668, 296, 30);
	
	

	salidas = new Fl_Text_Display (1, 1, 296, 666);
	salidas->textcolor(FL_WHITE);
	salidas->color(FL_BLUE);
	tbuff = new Fl_Text_Buffer();
	salidas->buffer(tbuff);

	////Salida del arreglo
	//buff = new Fl_Text_Buffer();
	//disp = new Fl_Text_Display(30, 600, 1000, 50, "Arreglo introducido");
	//disp->buffer(buff);

	
	window->show();
	return Fl::run();
}

//fuck my life//





