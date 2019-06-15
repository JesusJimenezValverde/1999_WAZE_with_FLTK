#pragma once
//
// "$Id$"
//
// Valuator header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2016 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

/* \file
   Fl_Valuator widget . */

#ifndef Fl_Valuator_H
#define Fl_Valuator_H

#ifndef Fl_Widget_H
#include "Fl_Widget.H"
#endif

   // shared type() values for classes that work in both directions:
#define FL_VERTICAL             0 
#define FL_HORIZONTAL           1 


class FL_EXPORT Fl_Valuator : public Fl_Widget {

	double value_;
	double previous_value_;
	double min, max; // truncates to this range *after* rounding
	double A; int B; // rounds to multiples of A/B, or no rounding if A is zero

protected:
	int horizontal() const { return type()& FL_HORIZONTAL; }
	Fl_Valuator(int X, int Y, int W, int H, const char* L);

	double previous_value() const { return previous_value_; }
	void handle_push() { previous_value_ = value_; }
	double softclamp(double);
	void handle_drag(double newvalue);
	void handle_release(); // use drag() value
	virtual void value_damage(); // cause damage() due to value() changing
	void set_value(double v) { value_ = v; }

public:

	void bounds(double a, double b) { min = a; max = b; }
	double minimum() const { return min; }
	void minimum(double a) { min = a; }
	double maximum() const { return max; }
	void maximum(double a) { max = a; }
	void range(double a, double b) { min = a; max = b; }
	void step(int a) { A = a; B = 1; }
	void step(double a, int b) { A = a; B = b; }
	void step(double s);
	double step() const { return A / B; }
	void precision(int digits);

	double value() const { return value_; }
	int value(double);

	virtual int format(char*);
	double round(double); // round to nearest multiple of step
	double clamp(double); // keep in range
	double increment(double, int); // add n*step to value
};

#endif

//
// End of "$Id$".
//