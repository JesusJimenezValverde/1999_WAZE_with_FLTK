#pragma once
//
// "$Id$"
//
// Image header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Image_H
#  define Fl_Image_H

#  include "Enumerations.H"
#include <stdlib.h>

class Fl_Widget;
class Fl_Pixmap;
struct Fl_Menu_Item;
struct Fl_Label;


enum Fl_RGB_Scaling {
	FL_RGB_SCALING_NEAREST = 0,
	FL_RGB_SCALING_BILINEAR
};


class FL_EXPORT Fl_Image {

public:
	static const int ERR_NO_IMAGE = -1;
	static const int ERR_FILE_ACCESS = -2;
	static const int ERR_FORMAT = -3;

private:
	int w_, h_, d_, ld_, count_;
	const char * const *data_;
	static Fl_RGB_Scaling RGB_scaling_;

	// Forbid use of copy constructor and assign operator
	Fl_Image & operator=(const Fl_Image &);
	Fl_Image(const Fl_Image &);

protected:

	void w(int W) { w_ = W; }
	void h(int H) { h_ = H; }
	void d(int D) { d_ = D; }
	void ld(int LD) { ld_ = LD; }
	void data(const char * const *p, int c) { data_ = p; count_ = c; }
	void draw_empty(int X, int Y);

	static void labeltype(const Fl_Label *lo, int lx, int ly, int lw, int lh, Fl_Align la);
	static void measure(const Fl_Label *lo, int &lw, int &lh);

public:

	int w() const { return w_; }
	int h() const { return h_; }
	int d() const { return d_; }
	int ld() const { return ld_; }
	int count() const { return count_; }
	const char * const *data() const { return data_; }
	int fail();
	Fl_Image(int W, int H, int D);
	virtual ~Fl_Image();
	virtual Fl_Image *copy(int W, int H);
	Fl_Image *copy() { return copy(w(), h()); }
	virtual void color_average(Fl_Color c, float i);
	void inactive() { color_average(FL_GRAY, .33f); }
	virtual void desaturate();
	virtual void label(Fl_Widget*w);
	virtual void label(Fl_Menu_Item*m);
	virtual void draw(int X, int Y, int W, int H, int cx = 0, int cy = 0); // platform dependent
	void draw(int X, int Y) { draw(X, Y, w(), h(), 0, 0); } // platform dependent
	virtual void uncache();

	// set RGB image scaling method
	static void RGB_scaling(Fl_RGB_Scaling);

	// get RGB image scaling method
	static Fl_RGB_Scaling RGB_scaling();
};


class FL_EXPORT Fl_RGB_Image : public Fl_Image {
	friend class Fl_Quartz_Graphics_Driver;
	friend class Fl_GDI_Graphics_Driver;
	friend class Fl_GDI_Printer_Graphics_Driver;
	friend class Fl_Xlib_Graphics_Driver;
	static size_t max_size_;
public:

	const uchar *array;
	int alloc_array;

private:

#if defined(__APPLE__) || defined(WIN32)
	void *id_; // for internal use
	void *mask_; // for internal use (mask bitmap)
#else
	unsigned id_; // for internal use
	unsigned mask_; // for internal use (mask bitmap)
#endif // __APPLE__ || WIN32

public:

	Fl_RGB_Image(const uchar *bits, int W, int H, int D = 3, int LD = 0);
	Fl_RGB_Image(const Fl_Pixmap *pxm, Fl_Color bg = FL_GRAY);
	virtual ~Fl_RGB_Image();
	virtual Fl_Image *copy(int W, int H);
	Fl_Image *copy() { return copy(w(), h()); }
	virtual void color_average(Fl_Color c, float i);
	virtual void desaturate();
	virtual void draw(int X, int Y, int W, int H, int cx = 0, int cy = 0);
	void draw(int X, int Y) { draw(X, Y, w(), h(), 0, 0); }
	virtual void label(Fl_Widget*w);
	virtual void label(Fl_Menu_Item*m);
	virtual void uncache();
	static void max_size(size_t size) { max_size_ = size; }
	static size_t max_size() { return max_size_; }
};

#endif // !Fl_Image_H

//
// End of "$Id$".
//