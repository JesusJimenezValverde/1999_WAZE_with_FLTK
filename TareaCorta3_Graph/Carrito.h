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

class Carrito : public Fl_Box {
public:
	Carrito(int X, int Y, int W, int H, const char*L = 0) : Fl_Box(X, Y, W, H, L) {
	}
	void draw() {
		int cx = x();
		int cy = y();
		fl_color(FL_GREEN);
		fl_circle(cx, cy, 12);

	}

};