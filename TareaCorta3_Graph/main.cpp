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
#include <iostream>
#include <fstream>
#include "Persona.h"
#include "ArchivoDirecto.h"
#include <string>
#include "Procesar.h"
#include "string.h" 


int main(int argc, char **argv) {

	using namespace Graph_lib; 
	using namespace std; 
	Fl_Window * ventana = new Fl_Window(20, 40, 1302, 700, "MIWA");
	Procesar p(2, 668, 296, 30,ventana);

	/*int cont = 0;
	for (int j = 0; j < 25; j++) {
		for (int i = 0; i < 40; i++) {
			p.CAJITAS[cont] = new Fl_Box(305 + ((i*25)), 5 + (j*28), 4, 4, "");
			p.CAJITAS[cont]->color(FL_BLUE);
			p.CAJITAS[cont]->box(FL_FLAT_BOX);
			cont++;
		}
	}*/

	//Linea * linea1 = new Linea(2, 1, 1, 1); 
	//linea1->color(FL_BLUE);
	
	//p.importarArchivo("ciudad.txt");
	//p.crearVRT("ciudad");
	//p.mostrar();
	ventana->show();
	return Fl::run();
}

//fuck my life//





