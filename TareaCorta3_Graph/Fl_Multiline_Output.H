#pragma once
//
 // "$Id$"
 //
 // Multi line output header file for the Fast Light Tool Kit (FLTK).
 //
 // Copyright 1998-2011 by Bill Spitzak and others.
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
	Fl_Multiline_Output widget . */

#ifndef Fl_Multiline_Output_H
#define Fl_Multiline_Output_H

#include "Fl_Output.H"

class FL_EXPORT Fl_Multiline_Output : public Fl_Output {
public:

	Fl_Multiline_Output(int X, int Y, int W, int H, const char *l = 0);
};

#endif

//
// End of "$Id$".
//
