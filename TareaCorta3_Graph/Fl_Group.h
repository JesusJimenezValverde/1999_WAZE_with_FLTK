#pragma once
//
// "$Id$"
//
// Group header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Group, Fl_End classes . */

#ifndef Fl_Group_H
#define Fl_Group_H

#ifndef Fl_Widget_H
#include "Fl_Widget.H"
#endif

class FL_EXPORT Fl_Group : public Fl_Widget {

	Fl_Widget** array_;
	Fl_Widget* savedfocus_;
	Fl_Widget* resizable_;
	int children_;
	int *sizes_; // remembered initial sizes of children

	int navigation(int);
	static Fl_Group *current_;

	// unimplemented copy ctor and assignment operator
	Fl_Group(const Fl_Group&);
	Fl_Group& operator=(const Fl_Group&);

protected:
	void draw();
	void draw_child(Fl_Widget& widget) const;
	void draw_children();
	void draw_outside_label(const Fl_Widget& widget) const;
	void update_child(Fl_Widget& widget) const;
	int  *sizes();

public:

	int handle(int);
	void begin();
	void end();
	static Fl_Group *current();
	static void current(Fl_Group *g);

	int children() const { return children_; }
	Fl_Widget* child(int n) const { return array()[n]; }
	int find(const Fl_Widget*) const;
	int find(const Fl_Widget& o) const { return find(&o); }
	Fl_Widget* const* array() const;

	void resize(int, int, int, int);
	Fl_Group(int, int, int, int, const char * = 0);
	virtual ~Fl_Group();
	void add(Fl_Widget&);
	void add(Fl_Widget* o) { add(*o); }
	void insert(Fl_Widget&, int i);
	void insert(Fl_Widget& o, Fl_Widget* before) { insert(o, find(before)); }
	void remove(int index);
	void remove(Fl_Widget&);
	void remove(Fl_Widget* o) { remove(*o); }
	void clear();

	void resizable(Fl_Widget& o) { resizable_ = &o; }
	void resizable(Fl_Widget* o) { resizable_ = o; }
	Fl_Widget* resizable() const { return resizable_; }
	void add_resizable(Fl_Widget& o) { resizable_ = &o; add(o); }
	void init_sizes();

	void clip_children(int c) { if (c) set_flag(CLIP_CHILDREN); else clear_flag(CLIP_CHILDREN); }
	unsigned int clip_children() { return (flags() & CLIP_CHILDREN) != 0; }

	// Note: Doxygen docs in Fl_Widget.H to avoid redundancy.
	virtual Fl_Group* as_group() { return this; }

	// back compatibility functions:

	void focus(Fl_Widget* W) { W->take_focus(); }

	Fl_Widget* & _ddfdesign_kludge() { return resizable_; }

	void forms_end();
};

// dummy class used to end child groups in constructors for complex
// subclasses of Fl_Group:
class FL_EXPORT Fl_End {
public:
	Fl_End() { Fl_Group::current()->end(); }
};

#endif

//
// End of "$Id$".
//