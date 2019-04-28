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


typedef struct Nodo*enlace;


Fl_Button *LineaALinea;
Fl_Button *Correr;
Fl_Button *Limpiar;
Fl_Button *Salir;
Fl_Input *entradaNum;




////////////////////////////////////////////////////////////////////////// Parte grafica //////////////////////////////////////////////////////////////////////////

class Direccion {//(x,y)
public:
	int dir;
};

//class EspacioV {
//public:
//	bool Lin1;
//	bool Lin2;
//	bool Lin3;
//	bool Lin4;
//};
//
//class EspacioH{
//public:
//	bool Lin1;
//	bool Lin2;
//	bool Lin3;
//	bool Lin4;
//	bool Lin5;
//	bool Lin6;
//	bool Lin7;
//};
//class EspacioVV { // Contiene las direcciones de salida de un nodo, 
//				//esto va a estar contenido en un vector donde estan 
//				//las posibles direcciones de salida de todos los nodos
//public:
//	Direccion D1;
//	Direccion D2;
//	Direccion D3;
//	Direccion D4;
//};
////const char * NumNodos[100] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19",
//							"20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39",
//							"40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59",
//							"60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79",
//							"80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99"};
////const char * Letras[26] = { "a","b","c","d","e","f","g","h","i","j","k","l","m",
//							"n","o","p","q","r","s","t","u","v","w","x","y","z" };
///Direcciones iniciales de todos los nodos
Direccion Direccionesx[31];
Direccion Niveles[28];


///Contiene las direcciones de salida de todos los nodos
//EspacioVV CorVerticales[28];

//void ponerFalsos() {
//	for (int i = 0; i < 7; i++) {
//		Verticales[i].Lin1 = false;
//		Verticales[i].Lin2 = false;
//		Verticales[i].Lin3 = false;
//		Verticales[i].Lin4 = false;
//	}
//	for (int i = 0; i < 4; i++) {
//		Horizontales[i].Lin1 = false;
//		Horizontales[i].Lin2 = false;
//		Horizontales[i].Lin3 = false;
//		Horizontales[i].Lin4 = false;
//		Horizontales[i].Lin5 = false;
//		Horizontales[i].Lin6 = false;
//		Horizontales[i].Lin7 = false;
//	}
//	int cond = 0;
//	int y = 130;
//	int numero = 0;
//	while (cond < 4) {
//		int cond1 = 0;
//		int x = 60;
//		while (cond1 < 7) {
//			Direcciones[numero].x = x;
//			Direcciones[numero].y = y;
//			DireccionesSalida[numero].x = x + 70;
//			DireccionesSalida[numero].y = y + 50;
//			x += 140;
//			cond1++;
//			numero++;
//		}
//		y += 140;
//		cond++;
//	}
//}
/////							Funciones para la linea del puntero							///
//
/////Define por que carril se mueve, auxiliar Drawpun
//int definirx2(int x) {
//	if (x == 0 || x == 7 || x == 14 || x == 21) {
//		if (Verticales[0].Lin1 == false) {
//			Verticales[0].Lin1 = true;
//			return (Direcciones[x].x + 105);
//		}
//		else if (Verticales[0].Lin2 == false) {
//			Verticales[0].Lin2 = true;
//			return (Direcciones[x].x + 110);
//		}
//		else if (Verticales[0].Lin3 == false) {
//			Verticales[0].Lin3 = true;
//			return (Direcciones[x].x + 115);
//		}
//		else if (Verticales[0].Lin4 == false) {
//			Verticales[0].Lin4 = true;
//			return (Direcciones[x].x + 120);
//		}
//	}
//	else if (x == 1 || x == 8 || x == 15 || x == 22) {
//		if (Verticales[1].Lin1 == false) {
//			Verticales[1].Lin1 = true;
//			return (Direcciones[x].x + 105);
//		}
//		else if (Verticales[1].Lin2 == false) {
//			Verticales[1].Lin2 = true;
//			return (Direcciones[x].x + 110);
//		}
//		else if (Verticales[1].Lin3 == false) {
//			Verticales[1].Lin3 = true;
//			return (Direcciones[x].x + 115);
//		}
//		else if (Verticales[1].Lin4 == false) {
//			Verticales[1].Lin4 = true;
//			return (Direcciones[x].x + 120);
//		}
//	}
//	else if (x == 2 || x == 9 || x == 16 || x == 23) {
//		if (Verticales[2].Lin1 == false) {
//			Verticales[2].Lin1 = true;
//			return (Direcciones[x].x + 105);
//		}
//		else if (Verticales[2].Lin2 == false) {
//			Verticales[2].Lin2 = true;
//			return (Direcciones[x].x + 110);
//		}
//		else if (Verticales[2].Lin3 == false) {
//			Verticales[2].Lin3 = true;
//			return (Direcciones[x].x + 115);
//		}
//		else if (Verticales[2].Lin4 == false) {
//			Verticales[2].Lin4 = true;
//			return (Direcciones[x].x + 120);
//		}
//	}
//	else if (x == 3 || x == 10 || x == 17 || x == 24) {
//		if (Verticales[3].Lin1 == false) {
//			Verticales[3].Lin1 = true;
//			return (Direcciones[x].x + 105);
//		}
//		else if (Verticales[3].Lin2 == false) {
//			Verticales[3].Lin2 = true;
//			return (Direcciones[x].x + 110);
//		}
//		else if (Verticales[3].Lin3 == false) {
//			Verticales[3].Lin3 = true;
//			return (Direcciones[x].x + 115);
//		}
//		else if (Verticales[3].Lin4 == false) {
//			Verticales[3].Lin4 = true;
//			return (Direcciones[x].x + 120);
//		}
//	}
//	else if (x == 4 || x == 11 || x == 18 || x == 25) {
//		if (Verticales[4].Lin1 == false) {
//			Verticales[4].Lin1 = true;
//			return (Direcciones[x].x + 105);
//		}
//		else if (Verticales[4].Lin2 == false) {
//			Verticales[4].Lin2 = true;
//			return (Direcciones[x].x + 110);
//		}
//		else if (Verticales[4].Lin3 == false) {
//			Verticales[4].Lin3 = true;
//			return (Direcciones[x].x + 115);
//		}
//		else if (Verticales[4].Lin4 == false) {
//			Verticales[4].Lin4 = true;
//			return (Direcciones[x].x + 120);
//		}
//	}
//	else if (x == 5 || x == 12 || x == 19 || x == 26) {
//		if (Verticales[5].Lin1 == false) {
//			Verticales[5].Lin1 = true;
//			return (Direcciones[x].x + 105);
//		}
//		else if (Verticales[5].Lin2 == false) {
//			Verticales[5].Lin2 = true;
//			return (Direcciones[x].x + 110);
//		}
//		else if (Verticales[5].Lin3 == false) {
//			Verticales[5].Lin3 = true;
//			return (Direcciones[x].x + 115);
//		}
//		else if (Verticales[5].Lin4 == false) {
//			Verticales[5].Lin4 = true;
//			return (Direcciones[x].x + 120);
//		}
//	}
//	else if (x == 6 || x == 13 || x == 20 || x == 27) {
//		if (Verticales[6].Lin1 == false) {
//			Verticales[6].Lin1 = true;
//			return (Direcciones[x].x + 105);
//		}
//		else if (Verticales[6].Lin2 == false) {
//			Verticales[6].Lin2 = true;
//			return (Direcciones[x].x + 110);
//		}
//		else if (Verticales[6].Lin3 == false) {
//			Verticales[6].Lin3 = true;
//			return (Direcciones[x].x + 115);
//		}
//		else if (Verticales[6].Lin4 == false) {
//			Verticales[6].Lin4 = true;
//			return (Direcciones[x].x + 120);
//		}
//	}
//}
//
/////Define cuanto sube o baja la linea, ingresa el nodo hacia el que se dirige
//int definirSB(int x) {
//	if (x == 0 || x == 1 || x == 2 || x == 3 || x == 4 || x == 5 || x == 6) { 
//		if (Horizontales[0].Lin1 == false) {
//			Horizontales[0].Lin1 = true;
//			return (125);
//		}
//		else if (Horizontales[0].Lin2 == false) {
//			Horizontales[0].Lin2 = true;
//			return (120);
//		}
//		else if (Horizontales[0].Lin3 == false) {
//			Horizontales[0].Lin3 = true;
//			return (115);
//		}
//		else if (Horizontales[0].Lin4 == false) {
//			Horizontales[0].Lin4 = true;
//			return (110);
//		}
//		else if (Horizontales[0].Lin5 == false) {
//			Horizontales[0].Lin5 = true;
//			return (105);
//		}
//		else if (Horizontales[0].Lin6 == false) {
//			Horizontales[0].Lin6 = true;
//			return (100);
//		}
//		else if (Horizontales[0].Lin7 == false) {
//			Horizontales[0].Lin7 = true;
//			return (95);
//		}
//	}
//	else if (x == 7 || x == 8 || x == 9 || x == 10 || x == 11 || x == 12 || x == 13) {
//		if (Horizontales[1].Lin1 == false) {
//			Horizontales[1].Lin1 = true;
//			return (265);
//		}
//		else if (Horizontales[1].Lin2 == false) {
//			Horizontales[1].Lin2 = true;
//			return (260);
//		}
//		else if (Horizontales[1].Lin3 == false) {
//			Horizontales[1].Lin3 = true;
//			return (255);
//		}
//		else if (Horizontales[1].Lin4 == false) {
//			Horizontales[1].Lin4 = true;
//			return (250);
//		}
//		else if (Horizontales[1].Lin5 == false) {
//			Horizontales[1].Lin5 = true;
//			return (245);
//		}
//		else if (Horizontales[1].Lin6 == false) {
//			Horizontales[1].Lin6 = true;
//			return (240);
//		}
//		else if (Horizontales[1].Lin7 == false) {
//			Horizontales[1].Lin7 = true;
//			return (235);
//		}
//	}
//	else if (x == 14 || x == 15 || x == 16 || x == 17 || x == 18 || x == 19 || x == 20) {
//		if (Horizontales[2].Lin1 == false) {
//			Horizontales[2].Lin1 = true;
//			return (405);
//		}
//		else if (Horizontales[2].Lin2 == false) {
//			Horizontales[2].Lin2 = true;
//			return (400);
//		}
//		else if (Horizontales[2].Lin3 == false) {
//			Horizontales[2].Lin3 = true;
//			return (395);
//		}
//		else if (Horizontales[2].Lin4 == false) {
//			Horizontales[2].Lin4 = true;
//			return (390);
//		}
//		else if (Horizontales[2].Lin5 == false) {
//			Horizontales[2].Lin5 = true;
//			return (385);
//		}
//		else if (Horizontales[2].Lin6 == false) {
//			Horizontales[2].Lin6 = true;
//			return (380);
//		}
//		else if (Horizontales[2].Lin7 == false) {
//			Horizontales[2].Lin7 = true;
//			return (375);
//		}
//	}
//	else if (x == 21 || x == 22 || x == 23 || x == 24 || x == 25 || x == 26 || x == 27) {
//		if (Horizontales[3].Lin1 == false) {
//			Horizontales[3].Lin1 = true;
//			return (545);
//		}
//		else if (Horizontales[3].Lin2 == false) {
//			Horizontales[3].Lin2 = true;
//			return (540);
//		}
//		else if (Horizontales[3].Lin3 == false) {
//			Horizontales[3].Lin3 = true;
//			return (535);
//		}
//		else if (Horizontales[3].Lin4 == false) {
//			Horizontales[3].Lin4 = true;
//			return (530);
//		}
//		else if (Horizontales[3].Lin5 == false) {
//			Horizontales[3].Lin5 = true;
//			return (525);
//		}
//		else if (Horizontales[3].Lin6 == false) {
//			Horizontales[3].Lin6 = true;
//			return (520);
//		}
//		else if (Horizontales[3].Lin7 == false) {
//			Horizontales[3].Lin7 = true;
//			return (515);
//		}
//	}
//}
//
/////Define hasta donde llega la linea horizontalmente, ingresa el nodo al que se dirige
//int definirEntrada(int x) {
//	if (x == 0 || x == 7 || x == 14 || x == 21) {
//		return(DireccionesSalida[0].x);
//	}
//	else if (x == 1 || x == 8 || x == 15 || x == 22) {
//		return(DireccionesSalida[1].x);
//	}
//	else if (x == 2 || x == 9 || x == 16 || x == 23) {
//		return(DireccionesSalida[2].x);
//	}
//	else if (x == 3 || x == 10 || x == 17 || x == 24) {
//		return(DireccionesSalida[3].x);
//	}
//	else if (x == 4 || x == 11 || x == 18 || x == 25) {
//		return(DireccionesSalida[4].x);
//	}
//	else if (x == 5 || x == 12 || x == 19 || x == 26) {
//		return(DireccionesSalida[5].x);
//	}
//	else if (x == 6 || x == 13 || x == 20 || x == 27) {
//		return(DireccionesSalida[6 ].x);
//	}
//}
//
/////Define la posicion del final de la flecha
//int definirFlecha(int x) {
//	if (x == 0 || x == 1 || x == 2 || x == 3 || x == 4 || x == 5 || x == 6) {
//		return (155);
//	}
//	else if (x == 7 || x == 8 || x == 9 || x == 10 || x == 11 || x == 12 || x == 13) {
//		return(295);
//	}
//	else if (x == 14 || x == 15 || x == 16 || x == 17 || x == 18 || x == 19 || x == 20) {
//		return(435);
//	}
//	else if (x == 21 || x == 22 || x == 23 || x == 24 || x == 25 || x == 26 || x == 27) {
//		return(575);
//	}
//}
//
/////Encargada de dibujar el puntero de un punto a, al punto b. Auxiliar de dibujar puntero
////
//
//int definirletras(vector<string> letritas) {
//	if (letritas[0] == "a"){
//		return 0;
//	}
//	if (letritas[0] == "b") {
//		return 1;
//	}
//	if (letritas[0] == "c") {
//		return 2;
//	}
//	if (letritas[0] == "d") {
//		return 3;
//	}
//	if (letritas[0] == "e") {
//		return 4;
//	}
//	if (letritas[0] == "f") {
//		return 5;
//	}
//	if (letritas[0] == "g") {
//		return 6;
//	}
//	if (letritas[0] == "h") {
//		return 7;
//	}
//	if (letritas[0] == "i") {
//		return 8;
//	}
//	if (letritas[0] == "j") {
//		return 9;
//	}
//	if (letritas[0] == "k") {
//		return 10;
//	}
//	if (letritas[0] == "l") {
//		return 11;
//	}
//	if (letritas[0] == "m") {
//		return 12;
//	}
//	if (letritas[0] == "n") {
//		return 13;
//	}
//	if (letritas[0] == "o") {
//		return 14;
//	}
//	if (letritas[0] == "p") {
//		return 15;
//	}
//	if (letritas[0] == "q") {
//		return 16;
//	}
//	if (letritas[0] == "r") {
//		return 17;
//	}
//	if (letritas[0] == "s") {
//		return 18;
//	}
//	if (letritas[0] == "t") {
//		return 19;
//	}
//	if (letritas[0] == "u") {
//		return 20;
//	}
//	if (letritas[0] == "v") {
//		return 21;
//	}
//	if (letritas[0] == "w") {
//		return 22;
//	}
//	if (letritas[0] == "x") {
//		return 23;
//	}
//	if (letritas[0] == "y") {
//		return 24;
//	}
//	if (letritas[0] == "z") {
//		return 25;
//	}
//}

///Dibuja los nodos
class DrawNodo : public Fl_Widget { 
public:
	DrawNodo(int X, int Y, int W, int H, const char*L = 0) : Fl_Widget(X, Y, W, H, L) {
	}
	void draw() {

		fl_color(216);
		//Rectangulo azul
		int par = x()-1;
		int x = 35; //Direcciones[par].x; // Sacar del arreglo direcciones x
		//cout << x << endl;/////////////////////////////////////////////////////////
		int y = 65; //Direcciones[par].y; // Sacar del arreglo niveles
		int contaaaar = 0;
		while (contaaaar < 31) {
			fl_color(FL_BLACK);
			double cx = x;
			double cy = y;
			double cc = 4;
			while (cc > -0.5){
				fl_circle(cx, cy, cc);
				cc = cc - 0.5;
			}

			//fl_color(FL_RED);
			//cx = x + 15;
			//cy = y;
			// cc = 4;
			//while (cc > -0.5) {
			//	fl_circle(cx, cy, cc);
			//	cc = cc - 0.5;
			//}
			contaaaar++;
			x += 33;

		}
		//Circulo azul

	}
};
class DrawPun : public Fl_Widget {
public:
	DrawPun(int X, int Y, int W, int H, const char*L = 0) : Fl_Widget(X, Y, W, H, L) {
	}
	void draw() {
		
		// Por hacer ... ☼ ... dibuja una linea de direccion del nodo actual y el nivel
							 //hasta la direccion del nodo izq o der y nivel+1
		
		
		
		////W y H se van a usar para identificar hacia donde va el puntero 
		//fl_color(255);
		//int p = x() - 1;//Direccion del nodo de inicio
		//int u = y() - 1;//Direccion del ultimo nodo
		////Aqui inicia la linea
		//int x1 = DireccionesSalida[p].x;
		//int y1 = DireccionesSalida[p].y;
		////cout << "Guarda " << y1 << endl;
		////Estas definen cuanto sale a la derecha
		//int y2 = y1;
		//int x2 = definirx2(p);
		////cout << "x2 definido -> " << x2 << endl;
		//fl_line(x1,y1,x2,y2);
		////Linea vertical
		//int y3 = definirSB(u);
		//fl_line(x2, y2, x2, y3); ///El  que tengo que averiguar con definirSB es el ultimo de esta
		////Linea horizontal
		//int x3 = definirEntrada(u) - 20;
		//fl_line(x2, y3, x3, y3);
		////Flecha de entrada
		//int y4 = definirFlecha(u);
		////std::cout << y4 << endl;
		//fl_line(x3, y3, x3, y4);
		////punta de la flecha
		//fl_line(x3, y4, x3 + 4, y4-4);
		//fl_line(x3, y4, x3 - 4, y4-4);
		////cout << y4 << endl;
	}
};

//Aqui se guardan los punteros a los nodos para saber si se pueden o se tienen que dibujar o borrar

DrawPun* Punteros[28];
DrawNodo* NodosGraficos[28];




///						Call backs						///

void dibujarfinal(void * data) {
	Fl::check();
	Fl_Window *w = (Fl_Window*)data;
	w->begin();

	//string loco = multilinea->value();

	//realizarlinea(loco);


	//ponerFalsos();
	////int i = 0;
	////while(i<)
	//for (int i = 0; i < 27; i++) {
	//	//cout << "Valor de I ; " << i << endl;
	//	w->remove(NodosGraficos[vnodos[i]->campo]);
	//	w->remove(Punteros[vnodos[i]->campo]);
	//	//w->remove(LetrasGraf[vnodos[i]->campo]);
	//	if (vnodos[i]->v != -1) { //&& vnodos[i]->cambio == false) { // Verifica si el nodo valor -1
	//		if (vnodos[i]->dibujadoN == false) {
	//			cout << "DIBUJADO" << endl;
	//			cout << "nodosgraficos[i]->campo ; " << vnodos[i]->campo + 1 << endl;
	//			cout << "vnodos[i] ; " << vnodos[i]->v << endl;
	//			cout << "NumNodos[x] ; " << NumNodos[vnodos[i]->v] << endl;
	//			NodosGraficos[vnodos[i]->campo] = new DrawNodo((vnodos[i]->campo+1), 8, 0, 0, NumNodos[vnodos[i]->v]);
	//			//vnodos[i]->dibujadoN = true;
	//			if (vnodos[i]->sig != nullptr) {
	//				vnodos[i]->siguienteN = vnodos[i]->sig->campo;
	//				cout << "Yo soy el siguiente" << vnodos[i]->siguienteN << endl;
	//				Punteros[vnodos[i]->campo] = new DrawPun(vnodos[i]->campo+1, vnodos[i]->siguienteN+1, 0, 0);
	//				//vnodos[i]->dibujadoP = true;
	//			}
	//			//LetrasGraf[vnodos[i]->campo] = new DrawL((vnodos[i]->campo + 1), 8, 0, 0, Letras[definirletras(vnodos[i]->letras)]);
	//		}
	//	}
	//}
	//cout << "---------------------------------------------" << endl;
	w->redraw();
	w->end();
}


void correrCb(Fl_Widget* butt, void * data) {
	butt->deactivate();
	Fl::check();
	Fl_Window *w = (Fl_Window*)data;
	w->begin();
	//Funcion-->

	//Limpia el espacio de entrada
	entradaNum->replace(0, entradaNum->size(), NULL, 0);

	//Limpia toda la pantalla ... por hacer ☼
	//for (int i = 0; i < 28; i++) {
	//	w->remove(NodosGraficos[i]);
	//	//delete(NodosGraficos[i]);
	//	w->remove(Punteros[i]);
	//	//delete(Punteros[i]);
	//}

	//Llamar a funcion que recorre el arbol y crea los nodos de la siguiente manera
	DrawNodo * nodo2 = new DrawNodo(8, 55, 0, 0); //Pasa el nodo actual + 1
	
	//Por hacer...☼... funcion que recorra el arbol por niveles 
	//Por hacer...☼... funcion que verifique si tiene izq y der, en caso de tenerlos, dibuje los punteros
					 //luego de esto baje y haga lo mismo con los otros nodos

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

	//Entrada de Numero maximo 32
	entradaNum = new Fl_Input(1135, 120, 120, 30);

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
