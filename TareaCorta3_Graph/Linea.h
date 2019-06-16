#pragma once
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

class Linea : public Fl_Box {
public:


	Linea(int X, int Y, int W, int H, const char*L = 0) : Fl_Box(X, Y, W, H, L) { // salida x, llegada x, nivel act, izq/der
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
		else if (color == 2) { //Arco iluminado
			fl_color(FL_RED);
			fl_line_style(FL_SOLID, 2);
			fl_line(400, 40, 800, 40 + 21);
			fl_line(800, 61, 800 - 5, 61 - 4);
			fl_line(800, 61, 800 - 5, 61 + 4);
		}

	}
};