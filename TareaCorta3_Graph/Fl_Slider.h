#pragma once
//
 // "$Id$"
 //
 // Slider header file for the Fast Light Tool Kit (FLTK).
 //
 // Copyright 1998-2010 by Bill Spitzak and others.
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
	Fl_Slider widget . */

#ifndef Fl_Slider_H
#define Fl_Slider_H

#ifndef Fl_Valuator_H
#include "Fl_Valuator.H"
#endif

	// values for type(), lowest bit indicate horizontal:
#define FL_VERT_SLIDER          0
#define FL_HOR_SLIDER           1
#define FL_VERT_FILL_SLIDER     2
#define FL_HOR_FILL_SLIDER      3
#define FL_VERT_NICE_SLIDER     4
#define FL_HOR_NICE_SLIDER      5

class FL_EXPORT Fl_Slider : public Fl_Valuator {

	float slider_size_;
	uchar slider_;
	void _Fl_Slider();
	void draw_bg(int, int, int, int);

protected:

	// these allow subclasses to put the slider in a smaller area:
	void draw(int, int, int, int);
	int handle(int, int, int, int, int);
	void draw();

public:

	int handle(int);
	Fl_Slider(int X, int Y, int W, int H, const char *L = 0);
	Fl_Slider(uchar t, int X, int Y, int W, int H, const char *L);

	int scrollvalue(int pos, int size, int first, int total);
	void bounds(double a, double b);

	float slider_size() const { return slider_size_; }

	void slider_size(double v);

	Fl_Boxtype slider() const { return (Fl_Boxtype)slider_; }

	void slider(Fl_Boxtype c) { slider_ = c; }
};

#endif

//
// End of "$Id$".
//