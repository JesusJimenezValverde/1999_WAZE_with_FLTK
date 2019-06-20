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
#include <queue>
#include "Carrito.h"
#include "Fl_Tooltip.h"
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>

#define MAX 10000
#define Arco2 pair< int , float >
#define INF 10000

using namespace std;

vector<Carrito*> allRect;

void winUpdate(void *data)
{
	static unsigned i = 0;
	Fl_Window *o = (Fl_Window*)data;
	if (i < allRect.size()) {
		o->add(allRect[i]);
		if (i >= 1) o->remove(allRect[i - 1]);
		o->redraw();
		Fl::add_timeout(0.1, winUpdate, data);
		++i;
	}
}

struct Nodo {
	int nNodo; //Numero de Nodo
	int x;	   //Coordenada X
	int y;     //Coordenada Y
	int gradoEntrada = 0;
	int gradoSalida = 0;
	Nodo() { nNodo = 0;  x = 0; y = 0; gradoEntrada = 0; gradoSalida = 0; };
	Nodo(string num) { nNodo = atoi(num.c_str()); x = 0; y = 0; gradoEntrada = 0; gradoSalida = 0; };
	Nodo(string num, string x, string y) { nNodo = atoi(num.c_str()); this->x = atoi(x.c_str()); this->y = atoi(y.c_str()); };
};

struct Arco {
	int origen;
	int destino;
	float distancia;
	int vMaxima;
	float vPromedio;
	float peso;
	Arco() { origen = 0; destino = 0; distancia = 0; vMaxima = 0; vPromedio = 0; peso = 0; };
	Arco(string org, string dest, string dist, string vM, string vProm) {
		origen = atoi(org.c_str());
		destino = atoi(dest.c_str());
		distancia = atoi(dist.c_str());
		vMaxima = atoi(vM.c_str());
		vPromedio = atoi(vProm.c_str());
		peso = (distancia/vPromedio);
		//cout << "peso : " << peso << "  distancia : " << distancia << "  promedio : " << vPromedio << endl;
	}

};


//Prueba
struct cmp {
	bool operator() (const Arco2 &a, const Arco2 &b) {
		return a.second > b.second;
	}
};
//

struct par {
	int salida;
	int llegada;
	par(int xsalida, int xllegada) {
		salida = xsalida;
		llegada = xllegada;
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
	vector<Arco2> ady[MAX]; 
	float distancia[MAX];      
	bool visitado[MAX]; 
	float previo[1000];
	priority_queue< Arco2, vector<Arco2>, cmp > Q;
	vector<int> padres;
	vector<par> aIluminarSpt;
	Carrito *carrito;
	bool archAbierto = false;
	int inicial = -1;
	string nArchivo;
	Fl_Box *box;
	Fl_Box *box1;
	Fl_Text_Display *salidas;
	Fl_Text_Buffer *tbuff;
	Fl_Window *window;
	bool ejecutado;
	Fl_Window * ventana;
	void importarArchivo(string nombre);
	void contarArcos(int N, int K);
	void crearVRT(string nombre);
	void crearARC(string nombre);
	void mostrar();
	void abrir();
	void mostrarArcos();
	//función de inicialización
	void init() {
		for (int i = 0; i <= nodos.size(); ++i) {
			distancia[i] = INF;  //inicializamos todas las distancias con valor infinito
			visitado[i] = false; //inicializamos todos los vértices como no visitados
			      //inicializamos el previo del vertice i con -1
		}
		for (int i = 0; i < 1000; i++) {
			previo[i] = -1;
		}
	}
	//Paso de relajacion
	void relajacion(int actual, int adyacente, float peso) {
		//Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
		if (distancia[actual] + peso < distancia[adyacente]) {
			distancia[adyacente] = distancia[actual] + peso;  //relajamos el vertice actualizando la distancia
			previo[adyacente] = actual;                         //a su vez actualizamos el vertice previo
			Q.push(Arco2(adyacente, distancia[adyacente])); //agregamos adyacente a la cola de prioridad
			//cout << "------------------------------------" << endl;
			//cout << "Meto " << actual << " , " << adyacente << endl;
			//aIluminarSpt.push_back(par(actual, adyacente)); //Agregandolo a los arcos que se tienen que iluminar cuando se ilumina spt
		}
	}
	//Impresion del camino mas corto desde el vertice inicial y final ingresados
	void arrPadres(int destino) {
		if (previo[destino] != -1)    //si aun poseo un vertice previo
			arrPadres(previo[destino]);  //recursivamente sigo explorando
		//printf("%d ", destino);        //terminada la recursion imprimo los vertices recorridos
		cout << "destino vale --> " << destino << endl;
		bool entra = true;
		for (int i = 0; i < padres.size(); i++) {
			if (destino == padres[i]) {
				entra = false;
			}
		}
		if (entra == true) {
			padres.push_back(destino);
		}
	}
	void fSpt() {
		if (aIluminarSpt.size() > 0) {
			for (int i = 0; i < aIluminarSpt.size(); i++) {
				aIluminarSpt.pop_back();
			}
			//aIluminarSpt.pop_back();
		}
		for (int i = 0; i < 1000; i++) {
			if (previo[i] != -1) {
				aIluminarSpt.push_back(par(previo[i], i));
				cout << "Meti a iluminar : " << previo[i] << " , " << i << endl;
			}
		}
	}
	void mSPT(int inicial) {
		init(); //inicializamos nuestros arreglos
		Q.push(Arco2(inicial, 0)); //Insertamos el vértice inicial en la Cola de Prioridad
		//aIluminarSpt.push_back(par(inicial, 0));
		distancia[inicial] = 0;      //Este paso es importante, inicializamos la distancia del inicial como 0
		int actual, adyacente;
		float peso;
		while (!Q.empty()) {  
			actual = Q.top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial
			Q.pop();     //Sacamos el elemento de la cola
			//aIluminarSpt.pop_back();
			if (visitado[actual]) continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola
			visitado[actual] = true;         //Marco como visitado el vértice actual

			for (int i = 0; i < ady[actual].size(); ++i) { //reviso sus adyacentes del vertice actual
				adyacente = ady[actual][i].first;   //id del vertice adyacente
				peso = ady[actual][i].second;        //peso de la arista que une actual con adyacente ( actual , adyacente )
				if (!visitado[adyacente]) {        //si el vertice adyacente no fue visitado
					relajacion(actual, adyacente, peso); //realizamos el paso de relajacion
				}
			}
		}
		//printf("Distancias mas cortas iniciando en vertice %d\n", inicial);
		//for (int i = 0; i < nodos.size(); ++i) {
		//	if (distancia[i] != 10000) {
		//		printf("Vertice %d , distancia mas corta = %f\n", i, distancia[i]);
		//	}
		//	else {
		//		cout << "Nodo " << i << " inalcanzable." << endl;
		//	}
		//}
	}
	

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

			if (allRect.size() > 0) {
				ventana->remove(allRect[allRect.size() - 1]);
				for (int i = 0; i < allRect.size(); i++) {
					allRect.pop_back();
				}
				//allRect.pop_back();
				ventana->redraw();
			}

			dibujaGrafo();
			ventana->redraw();
			
		}
		else if (instruccion == "close") {
			inicial = -1;
			archAbierto = false;
			if (allRect.size() > 0) {
				ventana->remove(allRect[allRect.size() - 1]);
				for (int i = 0; i < allRect.size(); i++) {
					allRect.pop_back();
				}
				//allRect.pop_back();
				ventana->redraw();
			}
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
			
			if (sinstruccion == "to ") {//-----------------------------------------------------------------------------**********************to********************--//

				string rInstruccion = instruccion.substr(3, instruccion.size());
				int destino = std::atoi(rInstruccion.c_str());
				if (archAbierto == true) {
					if (inicial != -1 && inicial != destino) {

						if (allRect.size() > 0) {
							ventana->remove(allRect[allRect.size() - 1]);
							for (int i = 0; i < allRect.size(); i++) {
								allRect.pop_back();
							}
							//allRect.pop_back();
							ventana->redraw();
						}

						if (padres.size() > 0) {
							for (int i = 0; i < padres.size(); i++) {
								padres.pop_back();
							}
							padres.pop_back();
						}

						arrPadres(destino);//Esta llena un vector en orden que se llama padres del nodo inicial al final
						if (padres.size() > 1) {
							if (aIluminarSpt.size() > 0) {
								for (int i = aIluminarSpt.size(); i > 0; i--) {
									aIluminarSpt.pop_back();
								}
							}

							//Limpiar padres antes de eso//

							for (int i = 1; i < padres.size(); i++) {
								aIluminarSpt.push_back(par(padres[i - 1], padres[i]));
							}


							//Iluminando el Inicial del Spt///
							for (int i = 0; i < nodos.size(); i++) {
								ventana->remove(dibujosN[i]);
								delete(dibujosN[i]);
								if (nodos[i].nNodo == inicial || nodos[i].nNodo == destino) {
									dibujosN[i] = new DrawNodo(nodos[i].x + 300, nodos[i].y, 2, 1);
								}
								else {
									dibujosN[i] = new DrawNodo(nodos[i].x + 300, nodos[i].y, 1, 1);
								}
								ventana->add(dibujosN[i]);
							}

							//Iluminando los arcos correspondientes al la ruta correspondiente///

							int valorDistancia = 0;
							for (int i = 0; i < arcos.size(); i++) {
								for (int j = 0; j < aIluminarSpt.size(); j++) {
									if (arcos[i].origen == aIluminarSpt[j].salida && arcos[i].destino == aIluminarSpt[j].llegada) {
										ventana->remove(dibujosA[i]);
										delete(dibujosA[i]);
										dibujosA[i] = new Linea(nodos[arcos[i].origen].x + 300, nodos[arcos[i].origen].y,
											nodos[arcos[i].destino].x + 300, nodos[arcos[i].destino].y, 2);
										ventana->add(dibujosA[i]);
										valorDistancia += arcos[i].peso;
										break;
									}
									else {
										ventana->remove(dibujosA[i]);
										delete(dibujosA[i]);
										dibujosA[i] = new Linea(nodos[arcos[i].origen].x + 300, nodos[arcos[i].origen].y,
											nodos[arcos[i].destino].x + 300, nodos[arcos[i].destino].y, 1);
										ventana->add(dibujosA[i]);
									}
								}
							}
							ventana->redraw();

							//**** Esto despues de hacer la instruccion si y solo si es valida ****//
							instruccion = "--> " + instruccion + "\n";
							const char * inst = instruccion.data();
							tbuff->append(inst);
							instruccion = "";
							for (int i = 0; i < padres.size(); i++) {
								if (i < padres.size() - 1) {
									instruccion = instruccion + to_string(padres[i]) + " --> ";
								}
								else {
									instruccion = instruccion + to_string(padres[i]) + "\n";
								}
							}
							instruccion = instruccion +" -> Peso: " + to_string(valorDistancia) + "\n";
							inst = instruccion.data();
							tbuff->append(inst);

							salidas->buffer(tbuff);
							//*********************************************************************//
						}
						else {
							//**** Notificacion inválida ****//
							instruccion = "--> " + instruccion + "\n";
							const char * inst = instruccion.data();
							tbuff->append(inst);
							instruccion = " -- Nodo Inalcanzable -- \n";

							inst = instruccion.data();
							tbuff->append(inst);
							salidas->buffer(tbuff);
						}
					}
					else {
						//**** Esto despues de hacer la instruccion si y solo si es valida ****//
						instruccion = "-- No se ha ejecutado el spt -- \n";
						const char * inst = instruccion.data();
						tbuff->append(inst);
						salidas->buffer(tbuff);

						//*********************************************************************//
					}
				}
				else {
					////****  Notificacion de salida    ****//
					instruccion = "-- No se ha abierto \n   ningun archivo \n";
					const char * inst = instruccion.data();
					tbuff->append(inst);
					salidas->buffer(tbuff);
					////*********************************************************************//
				}
			}
			else if (sinstruccion4 == "toa ") {//-----------------------------------------------------------------------------**********************toa********************--//
				string rInstruccion = instruccion.substr(3, instruccion.size());
				int destino = std::atoi(rInstruccion.c_str());
				if (archAbierto == true) {
					if (inicial != -1 && inicial != destino) {

						if (allRect.size() > 0) {
							ventana->remove(allRect[allRect.size() - 1]);
							//for (int i = 0; i < allRect.size(); i++) {
							//	allRect.pop_back();
							//}
							//allRect.pop_back();
							ventana->redraw();
						}
						if (padres.size() > 0) {
							for (int i = 0; i < padres.size(); i++) {
								padres.pop_back();
							}
							padres.pop_back();
						}

						arrPadres(destino);//Esta llena un vector en orden que se llama padres del nodo inicial al final
						if (padres.size() > 1) {
							if (aIluminarSpt.size() > 0) {
								for (int i = aIluminarSpt.size(); i > 0; i--) {
									aIluminarSpt.pop_back();
								}
							}

							//Limpiar padres antes de eso//

							for (int i = 1; i < padres.size(); i++) {
								aIluminarSpt.push_back(par(padres[i - 1], padres[i]));
							}


							//Iluminando el Inicial del Spt///
							for (int i = 0; i < nodos.size(); i++) {
								ventana->remove(dibujosN[i]);
								delete(dibujosN[i]);
								if (nodos[i].nNodo == inicial || nodos[i].nNodo == destino) {
									dibujosN[i] = new DrawNodo(nodos[i].x + 300, nodos[i].y, 2, 1);
								}
								else {
									dibujosN[i] = new DrawNodo(nodos[i].x + 300, nodos[i].y, 1, 1);
								}
								ventana->add(dibujosN[i]);
							}

							//Iluminando los arcos correspondientes al la ruta correspondiente///

							int valorDistancia = 0;
							for (int i = 0; i < arcos.size(); i++) {
								for (int j = 0; j < aIluminarSpt.size(); j++) {
									if (arcos[i].origen == aIluminarSpt[j].salida && arcos[i].destino == aIluminarSpt[j].llegada) {
										ventana->remove(dibujosA[i]);
										delete(dibujosA[i]);
										dibujosA[i] = new Linea(nodos[arcos[i].origen].x + 300, nodos[arcos[i].origen].y,
											nodos[arcos[i].destino].x + 300, nodos[arcos[i].destino].y, 2);
										ventana->add(dibujosA[i]);
										valorDistancia += arcos[i].peso;
										break;
									}
									else {
										ventana->remove(dibujosA[i]);
										delete(dibujosA[i]);
										dibujosA[i] = new Linea(nodos[arcos[i].origen].x + 300, nodos[arcos[i].origen].y,
											nodos[arcos[i].destino].x + 300, nodos[arcos[i].destino].y, 1);
										ventana->add(dibujosA[i]);
									}
								}
							}
							ventana->redraw();

							//------------Funcion que hace que se mueva-------------//
							
							for (int i = 0; i < aIluminarSpt.size(); i++) {
								cout << "Salida: " << aIluminarSpt[i].salida << "Llegada: " << aIluminarSpt[i].llegada << endl;
								//xy entrada y salida----------------//
								int xsalida = 0;
								int ysalida = 0;
								int xllegada = 0;
								int yllegada = 0;
								for (int j = 0; j < nodos.size(); j++) {
									if (nodos[j].nNodo == aIluminarSpt[i].salida) {
										xsalida = nodos[j].x + 300;
										ysalida = nodos[j].y;
									}
									if (nodos[j].nNodo == aIluminarSpt[i].llegada) {
										xllegada = nodos[j].x+300;
										yllegada = nodos[j].y;
									}
								}
								//xy entrada y salida----------------//
								int cantNodos = (abs(xllegada - xsalida) + abs(yllegada - ysalida))/6;
								cantNodos += 2;
								float constantex = ((abs(xllegada - xsalida)) / ((abs(xllegada - xsalida) + abs(yllegada - ysalida)) / 6));
								float constantey = ((abs(yllegada - ysalida)) / ((abs(xllegada - xsalida) + abs(yllegada - ysalida)) / 6));
								//y iguales
								if ((xllegada < xsalida) && ysalida == yllegada) {
									for (int i = 0; i < cantNodos; ++i) {
										allRect.push_back(new Carrito(xsalida-(i*constantex),ysalida,0,0));
									}
								}
								if ((xllegada > xsalida) && ysalida == yllegada) {
									for (int i = 0; i < cantNodos; ++i) {
										allRect.push_back(new Carrito(xsalida + (i*constantex), ysalida, 0, 0));
									}
								}
								//x iguales
								if ((xllegada == xsalida) && (ysalida < yllegada)) {
									for (int i = 0; i < cantNodos; ++i) {
										allRect.push_back(new Carrito(xsalida, ysalida + (i*constantey), 0, 0));
									}
								}
								if ((xllegada == xsalida) && (ysalida > yllegada)) {
									for (int i = 0; i < cantNodos; ++i) {
										allRect.push_back(new Carrito(xsalida, ysalida - (i*constantey), 0, 0));
									}
								}
								//arriba
								if ((xllegada > xsalida) && (ysalida > yllegada)) {
									for (int i = 0; i < cantNodos; ++i) {
										allRect.push_back(new Carrito(xsalida + (i*constantex), ysalida - (i*constantey), 0, 0));
									}
								}
								if ((xllegada < xsalida) && (ysalida > yllegada)) {
									for (int i = 0; i < cantNodos; ++i) {
										allRect.push_back(new Carrito(xsalida - (i*constantex), ysalida - (i*constantey), 0, 0));
									}
								}
								//abajo
								if ((xllegada > xsalida) && (ysalida < yllegada)) {
									for (int i = 0; i < cantNodos; ++i) {
										allRect.push_back(new Carrito(xsalida + (i*constantex), ysalida + (i*constantey), 0, 0));
									}
								}
								if ((xllegada < xsalida) && (ysalida < yllegada)) {
									for (int i = 0; i < cantNodos; ++i) {
										allRect.push_back(new Carrito(xsalida - (i*constantex), ysalida + (i*constantey), 0, 0));
									}
								}
								Fl::add_timeout(2, winUpdate, ventana);
							}

							//**** Esto despues de hacer la instruccion si y solo si es valida ****//
							instruccion = "--> " + instruccion + "\n";
							const char * inst = instruccion.data();
							tbuff->append(inst);
							instruccion = "";
							for (int i = 0; i < padres.size(); i++) {
								if (i < padres.size() - 1) {
									instruccion = instruccion + to_string(padres[i]) + " --> ";
								}
								else {
									instruccion = instruccion + to_string(padres[i]) + "\n";
								}
							}
							instruccion = instruccion + " -> Peso: " + to_string(valorDistancia) + "\n";
							inst = instruccion.data();
							tbuff->append(inst);

							salidas->buffer(tbuff);
							//*********************************************************************//
						}
						else {
							//**** Notificacion inválida ****//
							instruccion = "--> " + instruccion + "\n";
							const char * inst = instruccion.data();
							tbuff->append(inst);
							instruccion = " -- Nodo Inalcanzable -- \n";

							inst = instruccion.data();
							tbuff->append(inst);
							salidas->buffer(tbuff);
						}
					}
					else {
						//**** Esto despues de hacer la instruccion si y solo si es valida ****//
						instruccion = "-- No se ha ejecutado el spt -- \n";
						const char * inst = instruccion.data();
						tbuff->append(inst);
						salidas->buffer(tbuff);

						//*********************************************************************//
					}
				}
				else {
					////****  Notificacion de salida    ****//
					instruccion = "-- No se ha abierto \n   ningun archivo \n";
					const char * inst = instruccion.data();
					tbuff->append(inst);
					salidas->buffer(tbuff);
					////*********************************************************************//
				}

			}
			
			else if (sinstruccion4 == "spt ") {//-----------------------------------------------------------------------------**********************spt********************--//
				string rInstruccion = instruccion.substr(4, instruccion.size());
				inicial = std::atoi(rInstruccion.c_str());
				if (archAbierto == true) {
				//--------------Limpiar a iluminar ---------------//
					
					//if (allRect.size() > 0) {
					//	ventana->remove(allRect[allRect.size() - 1]);
					//	for (int i = 0; i < allRect.size(); i++) {
					//		allRect.pop_back();
					//	}
					//	//allRect.pop_back();
					//	ventana->redraw();
					//}

					if (aIluminarSpt.size() > 0) {
						for (int i = 0; i < aIluminarSpt.size(); i++) {
							aIluminarSpt.pop_back();
						}
						aIluminarSpt.pop_back();
					}

					if (ady->size() > 0) {
						for (int i = 0; i < ady->size(); i++) {
							ady->pop_back();
						}
					}
					//----------Aqui termina-------------------//

					for (int i = 0; i < arcos.size(); i++) {
						ady[arcos[i].origen].push_back(Arco2(arcos[i].destino, arcos[i].peso));
					}

					mSPT(inicial);

					fSpt();

					//Iluminando el Inicial del Spt///
					for (int i = 0; i < nodos.size(); i++) {
						ventana->remove(dibujosN[i]);
						delete(dibujosN[i]);
						if (nodos[i].nNodo == inicial) {
							dibujosN[i] = new DrawNodo(nodos[i].x + 300, nodos[i].y, 2, 1);
						}
						else {
							dibujosN[i] = new DrawNodo(nodos[i].x + 300, nodos[i].y, 1, 1);
						}
						ventana->add(dibujosN[i]);
					}

					//Iluminando los arcos correspondientes al spt///


					for (int i = 0; i < arcos.size(); i++) {
						for (int j = 0; j < aIluminarSpt.size(); j++) {
							if (arcos[i].origen == aIluminarSpt[j].salida && arcos[i].destino == aIluminarSpt[j].llegada) {
								ventana->remove(dibujosA[i]);
								delete(dibujosA[i]);
								dibujosA[i] = new Linea(nodos[arcos[i].origen].x + 300, nodos[arcos[i].origen].y,
									nodos[arcos[i].destino].x + 300, nodos[arcos[i].destino].y, 2);
								ventana->add(dibujosA[i]);
								break;
							}
							else {
								ventana->remove(dibujosA[i]);
								delete(dibujosA[i]);
								dibujosA[i] = new Linea(nodos[arcos[i].origen].x + 300, nodos[arcos[i].origen].y,
									nodos[arcos[i].destino].x + 300, nodos[arcos[i].destino].y, 1);
								ventana->add(dibujosA[i]);
							}
						}
					}
					ventana->redraw();

					////**** Esto despues de hacer la instruccion si y solo si es valida ****//
					instruccion = instruccion + "\n";
					const char * inst = instruccion.data();
					tbuff->append(inst);
					salidas->buffer(tbuff);
					////*********************************************************************//
				}
				else {
					////****  Notificacion de salida    ****//
					instruccion = "-- No se ha abierto \n   ningun archivo \n";
					const char * inst = instruccion.data();
					tbuff->append(inst);
					salidas->buffer(tbuff);
					////*********************************************************************//
				}
				
			}
			else if (sinstruccion5 == "node ") {
				string nNodo = instruccion.substr(5, instruccion.size());
				int number = std::atoi(nNodo.c_str());

				if (allRect.size() > 0) {
					ventana->remove(allRect[allRect.size() - 1]);
					for (int i = 0; i < allRect.size(); i++) {
						allRect.pop_back();
					}
					//allRect.pop_back();
					ventana->redraw();
				}

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

				inicial = -1;

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
					archAbierto = true;
					tbuff->append(mensaje.data());
					salidas->buffer(tbuff);

					archivo.open(nombArchivo+".txt",ios::in);
					int c = 0, cantNodos, cantArc = 0;
					string ax;
					while (archivo.good()) {
						if (c == 0) { //Carga encabezado
							getline(archivo, ax, ',');
							getline(archivo, ax, '\n');
							cantNodos = atoi(ax.c_str());
							cout << "La red con nodos: " << cantNodos << endl;
						}
						else if (c > 0 && c <= cantNodos) { //Carga nodos
							getline(archivo, ax ,',');
							getline(archivo, ax, ',');
							getline(archivo, ax, '\n');
						}
						else { //Carga arcos
							getline(archivo, ax, ',');
							getline(archivo, ax, ',');
							getline(archivo, ax, ',');
							getline(archivo, ax, ',');
							getline(archivo, ax, '\n');
							cantArc++;
						}
						c++;
					}
					archivo.close();
					int cantPaginas = 0;
					if (cantArc > 9 && cantArc % 9 == 0) {
						cantPaginas = cantArc / 9;
					}
					else if (cantArc < 9) {
						cantPaginas = 1;
					}
					else {
						cantPaginas = cantArc / 9;
						cantPaginas++;
					}
					cout << "HAY " << cantPaginas << " PAGINAS";
					//********************WAIT************************
					archivoVRT = { nombArchivo+".VRT" };
					for (int i = 0; i < archivoVRT.tam(); i++) {
						nodos.push_back(archivoVRT.leer(i));
					}
					archivoARC = { nombArchivo + ".ARC" };
					vector<BTreePage>paginas;
					for (int i = 0; i < cantPaginas; i++) {
						paginas.push_back(archivoARC.leer(i));
					}
					//OPERACIONES MODULARES
					int origen, destino;
					for (int i = 0; i < paginas.size(); i++) {
						for (int j = 0; j < 9; j++) {
							if (paginas[i].key[j].valor != 0) {
								TKey aux = paginas[i].key[j];
								origen = (aux.valor / 1000) % 1000;
								destino = aux.valor % 1000;
								arcos.push_back(Arco(to_string(origen), to_string(destino), to_string(aux.distancia), to_string(aux.vMaxima), to_string(aux.vPromedio)));
								cout << "\n\n " << paginas[i].key[j].valor << endl;
							}
						}
					}
					this->dibujaGrafo();
				}
			}
			else if (sinstruccion7 == "import ") {
				//Import
				inicial = -1;
				string auxa = instruccion.substr(7);
				string val =  to_string(auxa[0]);
				ifstream prueba;
				if (auxa != "" && auxa[0]=='"') {
					string nombArchivo = instruccion.substr(8);
					nombArchivo = nombArchivo.substr(0, nombArchivo.size() - 1);
					prueba.open(nombArchivo,ios::binary);
					if (!prueba.fail()) {
						prueba.close();
						this->importarArchivo(nombArchivo);
						nombArchivo = nombArchivo.substr(0, nombArchivo.size() - 4);
						cout << "Se ha abierto la ciudad: '" << nombArchivo << "'" << endl;
						this->crearVRT(nombArchivo);
						this->crearARC(nombArchivo);
						dibujaGrafo();
						////**** Esto despues de hacer la instruccion si y solo si es valida ****//
						archAbierto = true;
						instruccion = instruccion + "\n";
						const char * inst = instruccion.data();
						tbuff->append(inst);
						salidas->buffer(tbuff);
						string aux = "Informacion Leida:\nVertices: " + to_string(nodos.size()) + "\nArcos: " + to_string(arcos.size()) + "\n";
						tbuff->append(aux.data());
						salidas->buffer(tbuff);
					}
					else {
						string aux = "El archivo indicado no existe\n";
						tbuff->append(aux.data());
						salidas->buffer(tbuff);
					}
				}
				else {
					auxa = "Instrucción Inválida\n";
					tbuff->append(auxa.data());
					salidas->buffer(tbuff);
				}
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

		if (dibujosN.size() > 0 && nodos.size() > 0) {
			for (int i = dibujosN.size() - 1; i > 0; i--) {
				ventana->remove(dibujosN[i]);
				dibujosN.pop_back();
			}
			ventana->remove(dibujosN[0]);
			dibujosN.pop_back();
		}
		cout << "\n\n PEPEPE " << nodos.size() << endl;
		for (int i = 0; i < nodos.size(); i++) {
			dibujosN.push_back(new DrawNodo(nodos[i].x + 300, nodos[i].y,1,1));
			ventana->add(dibujosN[i]);
		}
		cout <<"\n\n BLA BLA "<< arcos.size() << endl;
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
			a.peso = a.distancia / a.vPromedio;
			arcos.push_back(a);
			//k++; CUIDADO

			cout << "Arco " << k++ << " origen: " << origen << " destino: " << dest << " distancia: " << dist << " velocidad Max: " << vMax << " promedio: " << vProm << " peso : " << a.peso << endl;
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
	int i = 0;
	int pag = 0;
	while (i < arcos.size()) {
		if (pag < 9) {
			TKey nueva{ arcos[i].origen,arcos[i].destino,(double)arcos[i].distancia,(double)arcos[i].vMaxima,(double)arcos[i].vPromedio };
			pagina.insertarLlave(nueva);
			pag++;
			i++;
		}
		else {
			archivoARC.agregarFinal(pagina, pagina.t);
			pagina.limpiar();
			pag = 0;
		}

	}

	//for (int i = 0; i < arcos.size(); i++) {
	//	if (pagina.lleno == false) {
	//		TKey nueva{arcos[i].origen,arcos[i].destino,(double)arcos[i].distancia,(double)arcos[i].vMaxima,(double)arcos[i].vPromedio};
	//		pagina.insertarLlave(nueva);
	//		cout << "Showkeys1" << endl;
	//		pagina.showKeys();
	//		cout << "vMaxima : " << arcos[i].vMaxima << endl;
	//		if ((((cont*8)+i) % 8) == 0 && (i != 0)) {
	//			pagina.lleno = true;
	//			cont++;
	//			
	//		}
	//		//if (i == 8)
	//		//	pagina.lleno = true;
	//	}
	//	else {
	//		archivoARC.agregarFinal(pagina, pagina.t);
	//		cout << "Meti una pagina"<<endl;
	//		pagina.limpiar();
	//		TKey nueva{ arcos[i].origen,arcos[i].destino,(double)arcos[i].distancia,(double)arcos[i].vMaxima,(double)arcos[i].vPromedio };
	//		pagina.insertarLlave(nueva);
	//		cout << "Showkeys" << endl;
	//		pagina.showKeys();
	//	}
	//}
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
