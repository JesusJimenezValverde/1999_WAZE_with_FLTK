#pragma once
//
// "$Id$"
//
// Header file for Fl_Text_Display class.
//
// Copyright 2001-2016 by Bill Spitzak and others.
// Original code Copyright Mark Edel.  Permission to distribute under
// the LGPL for the FLTK library granted by Mark Edel.
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
 Fl_Text_Display widget . */

#ifndef FL_TEXT_DISPLAY_H
#define FL_TEXT_DISPLAY_H

#include "fl_draw.H"
#include "Fl_Group.H"
#include "Fl_Widget.H"
#include "Fl_Scrollbar.H"
#include "Fl_Text_Buffer.H"

class FL_EXPORT Fl_Text_Display : public Fl_Group {

public:

	enum {
		NORMAL_CURSOR,
		CARET_CURSOR,
		DIM_CURSOR,
		BLOCK_CURSOR,
		HEAVY_CURSOR,
		SIMPLE_CURSOR
	};

	enum {
		CURSOR_POS,
		CHARACTER_POS
	};

	enum {
		DRAG_NONE = -2,
		DRAG_START_DND = -1,
		DRAG_CHAR = 0,
		DRAG_WORD = 1,
		DRAG_LINE = 2
	};

	enum {
		WRAP_NONE,
		WRAP_AT_COLUMN,
		WRAP_AT_PIXEL,
		WRAP_AT_BOUNDS
	};

	friend void fl_text_drag_me(int pos, Fl_Text_Display* d);

	typedef void(*Unfinished_Style_Cb)(int, void *);

	struct Style_Table_Entry {
		Fl_Color    color;
		Fl_Font     font;
		Fl_Fontsize size;
		unsigned    attr;
	};

	Fl_Text_Display(int X, int Y, int W, int H, const char *l = 0);
	~Fl_Text_Display();

	virtual int handle(int e);

	void buffer(Fl_Text_Buffer* buf);

	void buffer(Fl_Text_Buffer& buf) { buffer(&buf); }

	Fl_Text_Buffer* buffer() const { return mBuffer; }

	void redisplay_range(int start, int end);
	void scroll(int topLineNum, int horizOffset);
	void insert(const char* text);
	void overstrike(const char* text);
	void insert_position(int newPos);

	int insert_position() const { return mCursorPos; }
	int position_to_xy(int pos, int* x, int* y) const;

	int in_selection(int x, int y) const;
	void show_insert_position();

	int move_right();
	int move_left();
	int move_up();
	int move_down();
	int count_lines(int start, int end, bool start_pos_is_line_start) const;
	int line_start(int pos) const;
	int line_end(int startPos, bool startPosIsLineStart) const;
	int skip_lines(int startPos, int nLines, bool startPosIsLineStart);
	int rewind_lines(int startPos, int nLines);
	void next_word(void);
	void previous_word(void);

	void show_cursor(int b = 1);

	void hide_cursor() { show_cursor(0); }

	void cursor_style(int style);

	Fl_Color cursor_color() const { return mCursor_color; }

	void cursor_color(Fl_Color n) { mCursor_color = n; }

	int scrollbar_width() const { return scrollbar_width_; }

	void scrollbar_width(int W) { scrollbar_width_ = W; }

	Fl_Align scrollbar_align() const { return scrollbar_align_; }

	void scrollbar_align(Fl_Align a) { scrollbar_align_ = a; }

	int word_start(int pos) const { return buffer()->word_start(pos); }

	int word_end(int pos) const { return buffer()->word_end(pos); }


	void highlight_data(Fl_Text_Buffer *styleBuffer,
		const Style_Table_Entry *styleTable,
		int nStyles, char unfinishedStyle,
		Unfinished_Style_Cb unfinishedHighlightCB,
		void *cbArg);

	int position_style(int lineStartPos, int lineLen, int lineIndex) const;

	int shortcut() const { return shortcut_; }

	void shortcut(int s) { shortcut_ = s; }

	Fl_Font textfont() const { return textfont_; }

	void textfont(Fl_Font s) { textfont_ = s; mColumnScale = 0; }

	Fl_Fontsize textsize() const { return textsize_; }

	void textsize(Fl_Fontsize s) { textsize_ = s; mColumnScale = 0; }

	Fl_Color textcolor() const { return textcolor_; }

	void textcolor(Fl_Color n) { textcolor_ = n; }

	int wrapped_column(int row, int column) const;
	int wrapped_row(int row) const;
	void wrap_mode(int wrap, int wrap_margin);

	virtual void resize(int X, int Y, int W, int H);

	double x_to_col(double x) const;

	double col_to_x(double col) const;

	void linenumber_width(int width);
	int linenumber_width() const;
	void linenumber_font(Fl_Font val);
	Fl_Font linenumber_font() const;
	void linenumber_size(Fl_Fontsize val);
	Fl_Fontsize linenumber_size() const;
	void linenumber_fgcolor(Fl_Color val);
	Fl_Color linenumber_fgcolor() const;
	void linenumber_bgcolor(Fl_Color val);
	Fl_Color linenumber_bgcolor() const;
	void linenumber_align(Fl_Align val);
	Fl_Align linenumber_align() const;
	void linenumber_format(const char* val);
	const char* linenumber_format() const;

protected:
	// Most (all?) of this stuff should only be called from resize() or
	// draw().
	// Anything with "vline" indicates thats it deals with currently
	// visible lines.

	virtual void draw();
	void draw_text(int X, int Y, int W, int H);
	void draw_range(int start, int end);
	void draw_cursor(int, int);

	void draw_string(int style, int x, int y, int toX, const char *string,
		int nChars) const;

	void draw_vline(int visLineNum, int leftClip, int rightClip,
		int leftCharIndex, int rightCharIndex);

	int find_x(const char *s, int len, int style, int x) const;

	enum {
		DRAW_LINE,
		FIND_INDEX,
		FIND_INDEX_FROM_ZERO,
		GET_WIDTH
	};

	int handle_vline(int mode,
		int lineStart, int lineLen, int leftChar, int rightChar,
		int topClip, int bottomClip,
		int leftClip, int rightClip) const;

	void draw_line_numbers(bool clearAll);

	void clear_rect(int style, int x, int y, int width, int height) const;
	void display_insert();

	void offset_line_starts(int newTopLineNum);

	void calc_line_starts(int startLine, int endLine);

	void update_line_starts(int pos, int charsInserted, int charsDeleted,
		int linesInserted, int linesDeleted, int *scrolled);

	void calc_last_char();

	int position_to_line(int pos, int* lineNum) const;
	double string_width(const char* string, int length, int style) const;

	static void scroll_timer_cb(void*);

	static void buffer_predelete_cb(int pos, int nDeleted, void* cbArg);
	static void buffer_modified_cb(int pos, int nInserted, int nDeleted,
		int nRestyled, const char* deletedText,
		void* cbArg);

	static void h_scrollbar_cb(Fl_Scrollbar* w, Fl_Text_Display* d);
	static void v_scrollbar_cb(Fl_Scrollbar* w, Fl_Text_Display* d);
	void update_v_scrollbar();
	void update_h_scrollbar();
	int measure_vline(int visLineNum) const;
	int longest_vline() const;
	int empty_vlines() const;
	int vline_length(int visLineNum) const;
	int xy_to_position(int x, int y, int PosType = CHARACTER_POS) const;

	void xy_to_rowcol(int x, int y, int* row, int* column,
		int PosType = CHARACTER_POS) const;
	void maintain_absolute_top_line_number(int state);
	int get_absolute_top_line_number() const;
	void absolute_top_line_number(int oldFirstChar);
	int maintaining_absolute_top_line_number() const;
	void reset_absolute_top_line_number();
	int position_to_linecol(int pos, int* lineNum, int* column) const;
	int scroll_(int topLineNum, int horizOffset);

	void extend_range_for_styles(int* start, int* end);

	void find_wrap_range(const char *deletedText, int pos, int nInserted,
		int nDeleted, int *modRangeStart, int *modRangeEnd,
		int *linesInserted, int *linesDeleted);
	void measure_deleted_lines(int pos, int nDeleted);
	void wrapped_line_counter(Fl_Text_Buffer *buf, int startPos, int maxPos,
		int maxLines, bool startPosIsLineStart,
		int styleBufOffset, int *retPos, int *retLines,
		int *retLineStart, int *retLineEnd,
		bool countLastLineMissingNewLine = true) const;
	void find_line_end(int pos, bool start_pos_is_line_start, int *lineEnd,
		int *nextLineStart) const;
	double measure_proportional_character(const char *s, int colNum, int pos) const;
	int wrap_uses_character(int lineEndPos) const;

	int damage_range1_start, damage_range1_end;
	int damage_range2_start, damage_range2_end;
	int mCursorPos;
	int mCursorOn;
	int mCursorOldY;              /* Y pos. of cursor for blanking */
	int mCursorToHint;            /* Tells the buffer modified callback
								   where to move the cursor, to reduce
								   the number of redraw calls */
	int mCursorStyle;             /* One of enum cursorStyles above */
	int mCursorPreferredXPos;     /* Pixel position for vert. cursor movement */
	int mNVisibleLines;           /* # of visible (displayed) lines */
	int mNBufferLines;            /* # of newlines in the buffer */
	Fl_Text_Buffer* mBuffer;      /* Contains text to be displayed */
	Fl_Text_Buffer* mStyleBuffer; /* Optional parallel buffer containing
								   color and font information */
	int mFirstChar, mLastChar;    /* Buffer positions of first and last
								   displayed character (lastChar points
								   either to a newline or one character
								   beyond the end of the buffer) */
	int mContinuousWrap;          /* Wrap long lines when displaying */
	int mWrapMarginPix;           /* Margin in # of pixels for
								   wrapping in continuousWrap mode */
	int* mLineStarts;
	int mTopLineNum;              /* Line number of top displayed line
								   of file (first line of file is 1) */
	int mAbsTopLineNum;           /* In continuous wrap mode, the line
									number of the top line if the text
									were not wrapped (note that this is
									only maintained as needed). */
	int mNeedAbsTopLineNum;       /* Externally settable flag to continue
								   maintaining absTopLineNum even if
								   it isn't needed for line # display */
	int mHorizOffset;             /* Horizontal scroll pos. in pixels */
	int mTopLineNumHint;          /* Line number of top displayed line
								   of file (first line of file is 1) */
	int mHorizOffsetHint;         /* Horizontal scroll pos. in pixels */
	int mNStyles;                 /* Number of entries in styleTable */
	const Style_Table_Entry *mStyleTable; /* Table of fonts and colors for
										   coloring/syntax-highlighting */
	char mUnfinishedStyle;        /* Style buffer entry which triggers
								   on-the-fly reparsing of region */
	Unfinished_Style_Cb mUnfinishedHighlightCB; /* Callback to parse "unfinished" */
	/* regions */
	void* mHighlightCBArg;        /* Arg to unfinishedHighlightCB */

	int mMaxsize;

	int mSuppressResync;          /* Suppress resynchronization of line
								   starts during buffer updates */
	int mNLinesDeleted;           /* Number of lines deleted during
								   buffer modification (only used
								   when resynchronization is suppressed) */
	int mModifyingTabDistance;    /* Whether tab distance is being
								   modified */

	mutable double mColumnScale; /* Width in pixels of an average character. This
								   value is calculated as needed (lazy eval); it
								   needs to be mutable so that it can be calculated
								   within a method marked as "const" */

	Fl_Color mCursor_color;

	Fl_Scrollbar* mHScrollBar;
	Fl_Scrollbar* mVScrollBar;
	int scrollbar_width_;
	Fl_Align scrollbar_align_;
	int dragPos, dragType, dragging;
	int display_insert_position_hint;
	struct { int x, y, w, h; } text_area;

	int shortcut_;

	Fl_Font textfont_;
	Fl_Fontsize textsize_;
	Fl_Color textcolor_;

	// Line number margin and width
	int mLineNumLeft, mLineNumWidth;

	// Line number font/colors
#if FLTK_ABI_VERSION >= 10303
	Fl_Font     linenumber_font_;
	Fl_Fontsize linenumber_size_;
	Fl_Color    linenumber_fgcolor_;
	Fl_Color    linenumber_bgcolor_;
	Fl_Align    linenumber_align_;
	const char* linenumber_format_;
#endif
};

#endif

//
// End of "$Id$".
//