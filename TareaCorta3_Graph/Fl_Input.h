#pragma once
//
 // "$Id$"
 //
 // Input header file for the Fast Light Tool Kit (FLTK).
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
	Fl_Input widget . */

#ifndef Fl_Input_H
#define Fl_Input_H

#include "Fl_Input_.H"

class FL_EXPORT Fl_Input : public Fl_Input_ {
	int handle_key();
	int shift_position(int p);
	int shift_up_down_position(int p);
	void handle_mouse(int keepmark = 0);

	// Private keyboard functions
	int kf_lines_up(int repeat_num);
	int kf_lines_down(int repeat_num);
	int kf_page_up();
	int kf_page_down();
	int kf_insert_toggle();
	int kf_delete_word_right();
	int kf_delete_word_left();
	int kf_delete_sol();
	int kf_delete_eol();
	int kf_delete_char_right();
	int kf_delete_char_left();
	int kf_move_sol();
	int kf_move_eol();
	int kf_clear_eol();
	int kf_move_char_left();
	int kf_move_char_right();
	int kf_move_word_left();
	int kf_move_word_right();
	int kf_move_up_and_sol();
	int kf_move_down_and_eol();
	int kf_top();
	int kf_bottom();
	int kf_select_all();
	int kf_undo();
	int kf_redo();
	int kf_copy();
	int kf_paste();
	int kf_copy_cut();

protected:
	void draw();
public:
	int handle(int);
	Fl_Input(int, int, int, int, const char * = 0);
};

#endif 

//
// End of "$Id$".
//