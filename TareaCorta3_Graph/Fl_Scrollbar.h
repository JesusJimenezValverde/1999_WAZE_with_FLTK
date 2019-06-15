#pragma once
//
 // "$Id$"
 //
 // Scroll bar header file for the Fast Light Tool Kit (FLTK).
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
	Fl_Scrollbar widget . */

#ifndef Fl_Scrollbar_H
#define Fl_Scrollbar_H

#include "Fl_Slider.H"

class FL_EXPORT Fl_Scrollbar : public Fl_Slider {

	int linesize_;
	int pushed_;
	static void timeout_cb(void*);
	void increment_cb();
protected:
	void draw();

public:

	Fl_Scrollbar(int X, int Y, int W, int H, const char *L = 0);
	~Fl_Scrollbar();
	int handle(int);

	int value() const { return int(Fl_Slider::value()); }

	int value(int p) { return int(Fl_Slider::value((double)p)); }

	int value(int pos, int windowSize, int first, int total) {
		return scrollvalue(pos, windowSize, first, total);
	}

	int linesize() const { return linesize_; }

	void linesize(int i) { linesize_ = i; }

};

#endif

//
// End of "$Id$".
//