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
//Fl_Button *LineaALinea;
//Fl_Button *Correr;
//Fl_Button *Limpiar;
//Fl_Button *Salir;








class DrawNodo : public Fl_Box {
public:
	DrawNodo(int X, int Y, int W, int H, const char*L = 0) : Fl_Box(X, Y, W, H, L) {
	}
	void draw() {
		//int cx = x();
		//int cy = y();
		//int cc = 10;
		//while (cc > -0.5) {
		//	fl_circle(cx, cy, cc);
		//	cc = cc - 0.5;
		//}

		fl_color(FL_BLUE);
		fl_pie(500, 200, 20 - 1, 20 - 1, 0, 360);
		//fl_color(color);	// reset color


		fl_color(FL_RED);
		fl_arc(500, 200, 20, 20, 0, 360);
		//fl_circle(cx, cy, cc);
	}
	
};

class linea : public Fl_Box {
public:


	linea(int X, int Y, int W, int H, const char*L = 0) : Fl_Box(X, Y, W, H, L) { // salida x, llegada x, nivel act, izq/der
	}
	
	void draw() {
		int color = x();
		if (color == 1) { //Arco normal
			fl_color(FL_BLACK);
			fl_line_style(FL_SOLID, 2);
			fl_line(400, 40, 800, 40 + 21);
			fl_line(800, 61, 800 - 5, 61 - 4);
			fl_line(800, 61, 800 - 5, 61 + 4);

		}
		else if (color == 2){ //Arco iluminado
			fl_color(FL_RED);
			fl_line_style(FL_SOLID, 2);
			fl_line(400, 40, 800, 40 + 21);
			fl_line(800, 61, 800 - 5, 61 - 4);
			fl_line(800, 61, 800 - 5, 61 + 4);
		}

	}
};

///// Variables Globales ////
Fl_Text_Display *salidas;
Fl_Text_Buffer *tbuff;
Fl_Window *window;
Fl_Box *CAJITAS[1001];
linea *LINEAS[1001];


///							Auxiliares							///

void nRedraw() {
	window->redraw();
}

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
		//for (int i = 0; i < 1000; i++) {
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
				cout << "Llego un node " << endl;

				string nNodo = instruccion.substr(5, instruccion.size());
				int number = std::atoi(nNodo.c_str());
				
				CAJITAS[number]->color(FL_RED);
				nRedraw();
				
				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				////*********************************************************************//
			}
			else if (sinstruccion5 == "arcs ") {
				cout << "LLego un arcs " << endl;

				string nArcs = instruccion.substr(5, instruccion.size());

				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				////*********************************************************************//
			}
			else if (sinstruccion5 == "open ") {
				/*cout << "Llego un open" << endl;*/

				string nombArchivo = instruccion.substr(5, instruccion.size());

				////**** Esto despues de hacer la instruccion si y solo si es valida ****//
				instruccion = instruccion + "\n";
				const char * inst = instruccion.data();
				tbuff->append(inst);
				salidas->buffer(tbuff);
				////*********************************************************************//
			}
			else if (sinstruccion7 == "import ") {
				/*cout << "LLego un import " << endl;*/

				string nombArchivo = instruccion.substr(7, instruccion.size());
				//cout << "El archivo a leer es :" + sinstruccion7 + "." << endl;




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

	//llenarDirecciones();

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


	// *** Esta es una cajita *** //
	int cont = 0;
	for (int j = 0; j < 100; j++) {
		for (int i = 0; i < 100; i++) {
			CAJITAS[cont] = new Fl_Box(305 + ((i*9.94)), 5 + (j*6.9), 4, 4, "");
			CAJITAS[cont]->color(FL_BLUE);
			CAJITAS[cont]->box(FL_FLAT_BOX);
			cont++;
		}
	}

	
	

	DrawNodo* nodoR = new DrawNodo(500, 10, 0, 0);

	linea * linea1 = new linea(2, 1, 1, 1); 
	linea1->color(FL_BLUE);
	/*nodoR->SET()*/

	//Entrada de Numero maximo 
	MyInput *entradaNum = new MyInput(2, 668, 296, 30);
	
	
	//------------------------- Caja de salida de instrucciones ----------------------------- //
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





