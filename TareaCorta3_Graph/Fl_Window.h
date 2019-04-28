#pragma once
//
// "$Id$"
//
// Window header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2012 by Bill Spitzak and others.
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

#ifndef Fl_Window_H
#define Fl_Window_H

#ifdef WIN32
#include <windows.h>
#endif

#include "Fl_Group.H"
#include "Fl_Bitmap.H"
#include <stdlib.h>

#define FL_WINDOW 0xF0          
#define FL_DOUBLE_WINDOW 0xF1   

class Fl_X;
class Fl_RGB_Image;


class FL_EXPORT Fl_Window : public Fl_Group {

	static char *default_xclass_;
	// Note: we must use separate statements for each of the following 8 variables,
	// with the static attribute, otherwise MS VC++ 2008/2010 complains :-(
	// AlbrechtS 04/2012
#if FLTK_ABI_VERSION < 10301
	static // when these members are static, ABI compatibility with 1.3.0 is respected
#endif
		int no_fullscreen_x;
#if FLTK_ABI_VERSION < 10301
	static // when these members are static, ABI compatibility with 1.3.0 is respected
#endif
		int no_fullscreen_y;
#if FLTK_ABI_VERSION < 10301
	static // when these members are static, ABI compatibility with 1.3.0 is respected
#endif
		int no_fullscreen_w;
#if FLTK_ABI_VERSION < 10301
	static // when these members are static, ABI compatibility with 1.3.0 is respected
#endif
		int no_fullscreen_h;
#if FLTK_ABI_VERSION < 10303
	static // when these members are static, ABI compatibility with 1.3.0 is respected
#endif
		int fullscreen_screen_top;
#if FLTK_ABI_VERSION < 10303
	static // when these members are static, ABI compatibility with 1.3.0 is respected
#endif
		int fullscreen_screen_bottom;
#if FLTK_ABI_VERSION < 10303
	static // when these members are static, ABI compatibility with 1.3.0 is respected
#endif
		int fullscreen_screen_left;
#if FLTK_ABI_VERSION < 10303
	static // when these members are static, ABI compatibility with 1.3.0 is respected
#endif
		int fullscreen_screen_right;

	friend class Fl_X;
	Fl_X *i; // points at the system-specific stuff

	struct icon_data {
		const void *legacy_icon;
		Fl_RGB_Image **icons;
		int count;
#ifdef WIN32
		HICON big_icon;
		HICON small_icon;
#endif
	};

	const char* iconlabel_;
	char* xclass_;
	struct icon_data *icon_;
	// size_range stuff:
	int minw, minh, maxw, maxh;
	int dw, dh, aspect;
	uchar size_range_set;
	// cursor stuff
	Fl_Cursor cursor_default;
#if FLTK_ABI_VERSION < 10303
	// legacy, not used
	Fl_Color cursor_fg, cursor_bg;
#endif

protected:
	struct shape_data_type {
		int lw_;
		int lh_;
		Fl_Image* shape_;
#if defined(__APPLE__)
		typedef struct CGImage* CGImageRef;
		CGImageRef mask;
#endif
		Fl_Bitmap *todelete_;
	};

#if FLTK_ABI_VERSION < 10303 && !defined(FL_DOXYGEN)
	static
#endif
		shape_data_type *shape_data_;
private:
	void shape_bitmap_(Fl_Image* b);
	void shape_alpha_(Fl_Image* img, int offset);
	void shape_pixmap_(Fl_Image* pixmap);
public:
	void shape(const Fl_Image* img);
	inline void shape(const Fl_Image& b) { shape(&b); }
#if ! (defined(WIN32) || defined(__APPLE__) || defined(FL_DOXYGEN))
	void combine_mask(void);
#endif
private:


	void size_range_();
	void _Fl_Window(); // constructor innards
	void fullscreen_x(); // platform-specific part of sending a window to full screen
	void fullscreen_off_x(int X, int Y, int W, int H);// platform-specific part of leaving full screen

	// unimplemented copy ctor and assignment operator
	Fl_Window(const Fl_Window&);
	Fl_Window& operator=(const Fl_Window&);

protected:

	static Fl_Window *current_;
	virtual void draw();
	virtual void flush();

	void force_position(int force) {
		if (force) set_flag(FORCE_POSITION);
		else clear_flag(FORCE_POSITION);
	}
	int force_position() const { return ((flags() & FORCE_POSITION) ? 1 : 0); }

	void free_icons();

public:

	Fl_Window(int w, int h, const char* title = 0);
	Fl_Window(int x, int y, int w, int h, const char* title = 0);
	virtual ~Fl_Window();

	virtual int handle(int);

	virtual void resize(int X, int Y, int W, int H);
	void border(int b);
	void clear_border() { set_flag(NOBORDER); }
	unsigned int border() const { return !(flags() & NOBORDER); }
	void set_override() { set_flag(NOBORDER | OVERRIDE); }
	unsigned int override() const { return flags()&OVERRIDE; }
	void set_modal() { set_flag(MODAL); }
	unsigned int modal() const { return flags() & MODAL; }
	void set_non_modal() { set_flag(NON_MODAL); }
	unsigned int non_modal() const { return flags() & (NON_MODAL | MODAL); }

	void clear_modal_states() { clear_flag(NON_MODAL | MODAL); }

	void set_menu_window() { set_flag(MENU_WINDOW); }

	unsigned int menu_window() const { return flags() & MENU_WINDOW; }

	void set_tooltip_window() {
		set_flag(TOOLTIP_WINDOW);
		clear_flag(MENU_WINDOW);
	}
	unsigned int tooltip_window() const { return flags() & TOOLTIP_WINDOW; }

	void hotspot(int x, int y, int offscreen = 0);
	void hotspot(const Fl_Widget*, int offscreen = 0);
	void hotspot(const Fl_Widget& p, int offscreen = 0) { hotspot(&p, offscreen); }

	void free_position() { clear_flag(FORCE_POSITION); }
	void size_range(int minw, int minh, int maxw = 0, int maxh = 0, int dw = 0, int dh = 0, int aspect = 0) {
		this->minw = minw;
		this->minh = minh;
		this->maxw = maxw;
		this->maxh = maxh;
		this->dw = dw;
		this->dh = dh;
		this->aspect = aspect;
		size_range_();
	}

	const char* label() const { return Fl_Widget::label(); }
	const char* iconlabel() const { return iconlabel_; }
	void label(const char*);
	void iconlabel(const char*);
	void label(const char* label, const char* iconlabel); // platform dependent
	void copy_label(const char* a);

	static void default_xclass(const char*);
	static const char *default_xclass();
	const char* xclass() const;
	void xclass(const char* c);

	static void default_icon(const Fl_RGB_Image*);
	static void default_icons(const Fl_RGB_Image*[], int);
	void icon(const Fl_RGB_Image*);
	void icons(const Fl_RGB_Image*[], int);

#ifdef WIN32
	static void default_icons(HICON big_icon, HICON small_icon);
	void icons(HICON big_icon, HICON small_icon);
#endif

	/* for legacy compatibility */
	const void* icon() const;
	void icon(const void * ic);

	int shown() { return i != 0; }
	virtual void show();
	virtual void hide();
	void show(int argc, char **argv);

	// Enables synchronous show(), docs in Fl_Window.cxx
	void wait_for_expose();

	void fullscreen();
	void fullscreen_off();
	void fullscreen_off(int X, int Y, int W, int H);
	unsigned int fullscreen_active() const { return flags() & FULLSCREEN; }
	void fullscreen_screens(int top, int bottom, int left, int right);
	void iconize();

	int x_root() const;
	int y_root() const;

	static Fl_Window *current();
	void make_current();

	// Note: Doxygen docs in Fl_Widget.H to avoid redundancy.
	virtual Fl_Window* as_window() { return this; }

	void cursor(Fl_Cursor);
	void cursor(const Fl_RGB_Image*, int, int);
	void default_cursor(Fl_Cursor);

	/* for legacy compatibility */
	void cursor(Fl_Cursor c, Fl_Color, Fl_Color = FL_WHITE);
	void default_cursor(Fl_Cursor c, Fl_Color, Fl_Color = FL_WHITE);

	static void default_callback(Fl_Window*, void* v);

	int decorated_w();
	int decorated_h();

};

#endif

//
// End of "$Id$".
//