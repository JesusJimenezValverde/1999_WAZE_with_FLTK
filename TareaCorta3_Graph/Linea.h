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
	int iluminado;

	Linea(int X, int Y, int W, int H, int P, const char*L = 0) : Fl_Box(X, Y, W, H, L) { // salida x, llegada x, nivel act, izq/der
		iluminado = P;
	}
	/*
	En x se va a guardar el numero de nodo
	En y al nodo a donde llega

	En w 1 / 2 prendido o apagado

	*/
	void draw() {
		int color = w();
		int cx = x()+12;// /Centro x,y del nodo de salida
		int cy = y()+12; //Centro y del nodo de salida
		int llx = w()+12; // Centro x del nodo de llegada
		int lly = h()+12; // Centro y del nodo de llegada
		if (iluminado == 1) { //Arco normal
			fl_color(FL_BLACK);
			fl_line_style(FL_SOLID, 2);
			//----------------Alineados--------------------
			if (cy == lly && cx < llx) {
				fl_line(cx, cy, llx-12, lly);
				fl_line(llx-12, lly, llx - 16, lly - 4);
				fl_line(llx-12, lly, llx - 16, lly + 4);
			}
			else if(cy == lly && cx > llx) {
				fl_line(cx, cy, llx + 12, lly);
				fl_line(llx + 12, lly, llx + 16, lly - 4);
				fl_line(llx + 12, lly, llx + 16, lly + 4);
			}
			else if (cy < lly && cx == llx) {
				fl_line(cx, cy, llx, lly-12);
				fl_line(llx, lly - 12, llx - 4, lly - 16);
				fl_line(llx, lly - 12, llx + 4, lly - 16);
			}
			else if (cy > lly && cx == llx) {
				fl_line(cx, cy, llx, lly + 12);
				fl_line(llx, lly + 12, llx + 4, lly + 16);
				fl_line(llx, lly + 12 , llx - 4, lly + 16);
			}
			//Superior cubriendo LISTO
			else if ((cx > llx - 12 && cx < llx) && cy < lly - 12) { // izq
				fl_line(cx, cy, llx - 6, lly - 9);
				fl_line(llx - 6, lly - 9, llx - 13, lly - 17);
				fl_line(llx - 6, lly - 9, llx + 1, lly - 17);
			}
			else if ((cx < llx + 12 && cx > llx) && cy < lly - 12) { // der
				fl_line(cx, cy, llx + 6, lly - 9);
				fl_line(llx + 6, lly - 9, llx + 13, lly - 17);
				fl_line(llx + 6, lly - 9, llx - 1, lly - 17);
			}
			//Inferior Cubriendo lISTO
			else if ((cx > llx - 12 && cx < llx) && cy > lly + 12) { // izq
				fl_line(cx, cy, llx - 6, lly + 9);
				fl_line(llx - 6, lly + 9, llx - 13, lly + 17);
				fl_line(llx - 6, lly + 9, llx + 1, lly + 17);
			}
			else if ((cx < llx + 12 && cx > llx) && cy > lly + 12) { // der
				fl_line(cx, cy, llx + 6, lly + 9);
				fl_line(llx + 6, lly + 9, llx + 13, lly + 17);
				fl_line(llx + 6, lly + 9, llx - 1, lly + 17);
			}
			//Derecha
			else if ((cy > lly - 12 && cy < lly) && cx > llx + 12) { // arriba
				cout << "Derecha arriba" << endl;
				fl_line(cx, cy, llx + 9, lly - 6);
				fl_line(llx + 9, lly - 6, llx + 17, lly - 13);
				fl_line(llx + 9, lly - 6, llx + 17, lly + 1);
			}
			else if ((cy < lly + 12 && cy > lly) && cx > llx + 12) { // abajo
				cout << "Derecha abajo" << endl;
				fl_line(cx, cy, llx + 9, lly + 6);
				fl_line(llx + 9, lly + 6, llx + 17, lly - 1);
				fl_line(llx + 9, lly + 6, llx + 17, lly + 13);
			}
			//Izquierda
			else if ((cy > lly - 12 && cy < lly) && cx < llx - 12) { // arriba
				fl_line(cx, cy, llx - 9, lly - 6);
				fl_line(llx - 9, lly - 6, llx - 17, lly - 13);
				fl_line(llx - 9, lly - 6, llx - 17, lly + 1);
			}
			else if ((cy < lly + 12 && cy > lly) && cx < llx - 12) { // abajo
				fl_line(cx, cy, llx - 9, lly + 6);
				fl_line(llx - 9, lly + 6, llx - 17, lly + 13);
				fl_line(llx - 9, lly + 6, llx - 17, lly - 1);
			}
			//------------------ Angulo de 45 ------------------
			else if (cx > llx + 12 && cy > lly + 12) { // lista
				fl_line(cx, cy, llx + 10, lly + 10);
				fl_line(llx + 10, lly + 10, llx + 18, lly + 6);
				fl_line(llx + 10, lly + 10, llx + 6, lly + 18);
			}
			else if (cx < llx - 12 && cy > lly - 12) { // lista
				fl_line(cx, cy, llx - 10, lly + 10);
				fl_line(llx - 10, lly + 10, llx - 18, lly + 6);
				fl_line(llx - 10, lly + 10, llx - 6, lly + 18);
			}
			else if (cx < llx - 12 && cy < lly - 12) { // lista
				fl_line(cx, cy, llx - 10, lly - 10);
				fl_line(llx - 10, lly - 10, llx - 18, lly - 6);
				fl_line(llx - 10, lly - 10, llx - 6, lly - 18);
			}
			else if (cx > llx + 12 && cy < lly - 12) { // lista
				fl_line(cx, cy, llx + 10, lly - 10);
				fl_line(llx + 10, lly - 10, llx + 18, lly - 6);
				fl_line(llx + 10, lly - 10, llx + 6, lly - 18);
			}
			else {
				fl_line(cx, cy, llx, lly);
			}
		}
		else if (iluminado == 2) { //Arco iluminado
			fl_color(FL_YELLOW);
			fl_line_style(FL_SOLID, 3);
			//----------------Alineados--------------------
			if (cy == lly && cx < llx) {
				fl_line(cx, cy, llx - 12, lly);
				fl_line(llx - 12, lly, llx - 16, lly - 4);
				fl_line(llx - 12, lly, llx - 16, lly + 4);
			}
			else if (cy == lly && cx > llx) {
				fl_line(cx, cy, llx + 12, lly);
				fl_line(llx + 12, lly, llx + 16, lly - 4);
				fl_line(llx + 12, lly, llx + 16, lly + 4);
			}
			else if (cy < lly && cx == llx) {
				fl_line(cx, cy, llx, lly - 12);
				fl_line(llx, lly - 12, llx - 4, lly - 16);
				fl_line(llx, lly - 12, llx + 4, lly - 16);
			}
			else if (cy > lly && cx == llx) {
				fl_line(cx, cy, llx, lly + 12);
				fl_line(llx, lly + 12, llx + 4, lly + 16);
				fl_line(llx, lly + 12, llx - 4, lly + 16);
			}
			//Superior cubriendo LISTO
			else if ((cx > llx - 12 && cx < llx) && cy < lly - 12) { // izq
				fl_line(cx, cy, llx - 6, lly - 9);
				fl_line(llx - 6, lly - 9, llx - 13, lly - 17);
				fl_line(llx - 6, lly - 9, llx + 1, lly - 17);
			}
			else if ((cx < llx + 12 && cx > llx) && cy < lly - 12) { // der
				fl_line(cx, cy, llx + 6, lly - 9);
				fl_line(llx + 6, lly - 9, llx + 13, lly - 17);
				fl_line(llx + 6, lly - 9, llx - 1, lly - 17);
			}
			//Inferior Cubriendo lISTO
			else if ((cx > llx - 12 && cx < llx) && cy > lly + 12) { // izq
				fl_line(cx, cy, llx - 6, lly + 9);
				fl_line(llx - 6, lly + 9, llx - 13, lly + 17);
				fl_line(llx - 6, lly + 9, llx + 1, lly + 17);
			}
			else if ((cx < llx + 12 && cx > llx) && cy > lly + 12) { // der
				fl_line(cx, cy, llx + 6, lly + 9);
				fl_line(llx + 6, lly + 9, llx + 13, lly + 17);
				fl_line(llx + 6, lly + 9, llx - 1, lly + 17);
			}
			//Derecha
			else if ((cy > lly - 12 && cy < lly) && cx > llx + 12) { // arriba
				cout << "Derecha arriba" << endl;
				fl_line(cx, cy, llx + 9, lly - 6);
				fl_line(llx + 9, lly - 6, llx + 17, lly - 13);
				fl_line(llx + 9, lly - 6, llx + 17, lly + 1);
			}
			else if ((cy < lly + 12 && cy > lly) && cx > llx + 12) { // abajo
				cout << "Derecha abajo" << endl;
				fl_line(cx, cy, llx + 9, lly + 6);
				fl_line(llx + 9, lly + 6, llx + 17, lly - 1);
				fl_line(llx + 9, lly + 6, llx + 17, lly + 13);
			}
			//Izquierda
			else if ((cy > lly - 12 && cy < lly) && cx < llx - 12) { // arriba
				fl_line(cx, cy, llx - 9, lly - 6);
				fl_line(llx - 9, lly - 6, llx - 17, lly - 13);
				fl_line(llx - 9, lly - 6, llx - 17, lly + 1);
			}
			else if ((cy < lly + 12 && cy > lly) && cx < llx - 12) { // abajo
				fl_line(cx, cy, llx - 9, lly + 6);
				fl_line(llx - 9, lly + 6, llx - 17, lly + 13);
				fl_line(llx - 9, lly + 6, llx - 17, lly - 1);
			}
			//------------------ Angulo de 45 ------------------
			else if (cx > llx + 12 && cy > lly + 12) { // lista
				fl_line(cx, cy, llx + 10, lly + 10);
				fl_line(llx + 10, lly + 10, llx + 18, lly + 6);
				fl_line(llx + 10, lly + 10, llx + 6, lly + 18);
			}
			else if (cx < llx - 12 && cy > lly - 12) { // lista
				fl_line(cx, cy, llx - 10, lly + 10);
				fl_line(llx - 10, lly + 10, llx - 18, lly + 6);
				fl_line(llx - 10, lly + 10, llx - 6, lly + 18);
			}
			else if (cx < llx - 12 && cy < lly - 12) { // lista
				fl_line(cx, cy, llx - 10, lly - 10);
				fl_line(llx - 10, lly - 10, llx - 18, lly - 6);
				fl_line(llx - 10, lly - 10, llx - 6, lly - 18);
			}
			else if (cx > llx + 12 && cy < lly - 12) { // lista
				fl_line(cx, cy, llx + 10, lly - 10);
				fl_line(llx + 10, lly - 10, llx + 18, lly - 6);
				fl_line(llx + 10, lly - 10, llx + 6, lly - 18);
			}
			else {
				fl_line(cx, cy, llx, lly);
			}
		}

	}
};