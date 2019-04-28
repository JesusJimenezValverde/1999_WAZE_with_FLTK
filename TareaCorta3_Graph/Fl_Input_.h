#pragma once
//
 // "$Id$"
 //
 // Input base class header file for the Fast Light Tool Kit (FLTK).
 //
 // Copyright 1998-2015 by Bill Spitzak and others.
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
	Fl_Input_ widget . */

#ifndef Fl_Input__H
#define Fl_Input__H

#ifndef Fl_Widget_H
#include "Fl_Widget.H"
#endif

#define FL_NORMAL_INPUT         0
#define FL_FLOAT_INPUT          1
#define FL_INT_INPUT            2
#define FL_HIDDEN_INPUT         3
#define FL_MULTILINE_INPUT      4
#define FL_SECRET_INPUT         5
#define FL_INPUT_TYPE           7
#define FL_INPUT_READONLY       8
#define FL_NORMAL_OUTPUT        (FL_NORMAL_INPUT | FL_INPUT_READONLY)
#define FL_MULTILINE_OUTPUT     (FL_MULTILINE_INPUT | FL_INPUT_READONLY)
#define FL_INPUT_WRAP           16
#define FL_MULTILINE_INPUT_WRAP (FL_MULTILINE_INPUT | FL_INPUT_WRAP)
#define FL_MULTILINE_OUTPUT_WRAP (FL_MULTILINE_INPUT | FL_INPUT_READONLY | FL_INPUT_WRAP)

class FL_EXPORT Fl_Input_ : public Fl_Widget {

	const char* value_;

	char* buffer;

	int size_;

	int bufsize;

	int position_;

	int mark_;

	int tab_nav_;

	int xscroll_, yscroll_;

	int mu_p;

	int maximum_size_;

	int shortcut_;

	uchar erase_cursor_only;

	Fl_Font textfont_;

	Fl_Fontsize textsize_;

	Fl_Color textcolor_;

	Fl_Color cursor_color_;

	static double up_down_pos;

	static int was_up_down;

	/* Convert a given text segment into the text that will be rendered on screen. */
	const char* expand(const char*, char*) const;

	/* Calculates the width in pixels of part of a text buffer. */
	double expandpos(const char*, const char*, const char*, int*) const;

	/* Mark a range of characters for update. */
	void minimal_update(int, int);

	/* Mark a range of characters for update. */
	void minimal_update(int p);

	/* Copy the value from a possibly static entry into the internal buffer. */
	void put_in_buffer(int newsize);

	/* Set the current font and font size. */
	void setfont() const;

protected:

	/* Find the start of a word. */
	int word_start(int i) const;

	/* Find the end of a word. */
	int word_end(int i) const;

	/* Find the start of a line. */
	int line_start(int i) const;

	/* Find the end of a line. */
	int line_end(int i) const;

	/* Draw the text in the passed bounding box. */
	void drawtext(int, int, int, int);

	/* Move the cursor to the column given by up_down_pos. */
	int up_down_position(int, int keepmark = 0);

	/* Handle mouse clicks and mouse moves. */
	void handle_mouse(int, int, int, int, int keepmark = 0);

	/* Handle all kinds of text field related events. */
	int handletext(int e, int, int, int, int);

	/* Check the when() field and do a callback if indicated. */
	void maybe_do_callback();

	int xscroll() const { return xscroll_; }

	int yscroll() const { return yscroll_; }
	void yscroll(int yOffset) { yscroll_ = yOffset; damage(FL_DAMAGE_EXPOSE); }

	/* Return the number of lines displayed on a single page.  */
	int linesPerPage();

public:

	/* Change the size of the widget. */
	void resize(int, int, int, int);

	/* Constructor */
	Fl_Input_(int, int, int, int, const char* = 0);

	/* Destructor */
	~Fl_Input_();

	/* Changes the widget text. */
	int value(const char*);

	/* Changes the widget text. */
	int value(const char*, int);

	/* Changes the widget text. */
	int static_value(const char*);

	/* Changes the widget text. */
	int static_value(const char*, int);

	const char* value() const { return value_; }

	/* Returns the character at index \p i. */
	Fl_Char index(int i) const;

	int size() const { return size_; }

	void size(int W, int H) { Fl_Widget::size(W, H); }

	int maximum_size() const { return maximum_size_; }

	void maximum_size(int m) { maximum_size_ = m; }

	int position() const { return position_; }

	int mark() const { return mark_; }

	/* Sets the index for the cursor and mark. */
	int position(int p, int m);

	int position(int p) { return position(p, p); }

	int mark(int m) { return position(position(), m); }

	/* Deletes text from \p b to \p e and inserts the new string \p text. */
	int replace(int b, int e, const char *text, int ilen = 0);

	int cut() { return replace(position(), mark(), 0); }

	int cut(int n) { return replace(position(), position() + n, 0); }

	int cut(int a, int b) { return replace(a, b, 0); }

	int insert(const char* t, int l = 0) { return replace(position_, mark_, t, l); }

	/* Put the current selection into the clipboard. */
	int copy(int clipboard);

	/* Undo previous changes to the text buffer. */
	int undo();

	/* Copy the yank buffer to the clipboard. */
	int copy_cuts();

	int shortcut() const { return shortcut_; }

	void shortcut(int s) { shortcut_ = s; }

	Fl_Font textfont() const { return textfont_; }

	void textfont(Fl_Font s) { textfont_ = s; }

	Fl_Fontsize textsize() const { return textsize_; }

	void textsize(Fl_Fontsize s) { textsize_ = s; }

	Fl_Color textcolor() const { return textcolor_; }

	void textcolor(Fl_Color n) { textcolor_ = n; }

	Fl_Color cursor_color() const { return cursor_color_; }

	void cursor_color(Fl_Color n) { cursor_color_ = n; }

	int input_type() const { return type() & FL_INPUT_TYPE; }

	void input_type(int t) { type((uchar)(t | readonly())); }

	int readonly() const { return type() & FL_INPUT_READONLY; }

	void readonly(int b) {
		if (b) type((uchar)(type() | FL_INPUT_READONLY));
		else type((uchar)(type() & ~FL_INPUT_READONLY));
	}

	int wrap() const { return type() & FL_INPUT_WRAP; }

	void wrap(int b) {
		if (b) type((uchar)(type() | FL_INPUT_WRAP));
		else type((uchar)(type() & ~FL_INPUT_WRAP));
	}

	void tab_nav(int val) {
		tab_nav_ = val;
	}

	int tab_nav() const {
		return tab_nav_;
	}
};

#endif 

//
// End of "$Id$".
//