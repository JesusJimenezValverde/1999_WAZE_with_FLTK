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
//#include "bits/stdc++.h"

int main(int argc, char **argv) {

	using namespace Graph_lib; 
	using namespace std; 
	Fl_Window * ventana = new Fl_Window(20, 40, 1302, 700, "MIWA");
	Procesar p(2, 668, 296, 30,ventana);

	ventana->show();
	return Fl::run();

	//ArchivoDirecto<BTreePage>arch = { "tec.ARC" };
	//for (int i = 0; i < 5; i++) {
	//	cout << "Pagina " << i + 1 << "\n\n";
	//	BTreePage a =arch.leer(i);
	//	a.showKeys();
	//}
	
	return 0;
}






//fuck my life//





