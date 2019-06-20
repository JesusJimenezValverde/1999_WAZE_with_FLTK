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
		fl_draw_box(FL_SHADOW_BOX,cx,cy,43,25,FL_YELLOW);
		fl_draw_box(FL_FLAT_BOX, cx+17, cy+7, 9, 9, FL_CYAN);
		fl_line_style(FL_SOLID, 4);
		fl_color(FL_BLACK);
		fl_pie(cx, cy+20, 13, 13, 0, 360);
		fl_pie(cx+25, cy + 20, 13, 13, 0, 360);
		//fl_circle(cx, cy, 12);


	}

};