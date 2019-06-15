#pragma once
//
 // "$Id$"
 //
 // Header file for Fl_Text_Buffer class.
 //
 // Copyright 2001-2016 by Bill Spitzak and others.
 // Original code Copyright Mark Edel.  Permission to distribute under
 // the LGPL for the FLTK library granted by Mark Edel.
 //
 // Please report all bugs and problems on the following page:
 //
 //     http://www.fltk.org/str.php
 //
 // Please report all bugs and problems on the following page:
 //
 //     http://www.fltk.org/str.php
 //

 /* \file
  Fl_Text_Buffer, Fl_Text_Selection widget . */

#ifndef FL_TEXT_BUFFER_H
#define FL_TEXT_BUFFER_H


#undef ASSERT_UTF8

#ifdef ASSERT_UTF8
# include <assert.h>
# define IS_UTF8_ALIGNED(a) if (a && *a) assert(fl_utf8len(*(a))>0);
# define IS_UTF8_ALIGNED2(a, b) if (b>=0 && b<a->length()) assert(fl_utf8len(a->byte_at(b))>0);
#else
# define IS_UTF8_ALIGNED(a)
# define IS_UTF8_ALIGNED2(a, b)
#endif


  /*
   "character size" is the size of a UTF-8 character in bytes
   "character width" is the width of a Unicode character in pixels
   "column" was orginally defined as a character offset from the left margin.
   It was identical to the byte offset. In UTF-8, we have neither a byte offset
   nor truly fixed width fonts (*). Column could be a pixel value multiplied with
   an average character width (which is a bearable approximation).

   * in Unicode, there are no fixed width fonts! Even if the ASCII characters may
	 happen to be all the same width in pixels, Chinese characters surely are not.
	 There are plenty of exceptions, like ligatures, that make special handling of
	 "fixed" character widths a nightmare. I decided to remove all references to
	 fixed fonts and see "columns" as a multiple of the average width of a
	 character in the main font.
	   - Matthias
   */


   /* Maximum length in characters of a tab or control character expansion
	  of a single buffer character */
#define FL_TEXT_MAX_EXP_CHAR_LEN 20

#include "Fl_Export.H"


class FL_EXPORT Fl_Text_Selection {
	friend class Fl_Text_Buffer;

public:

	void set(int start, int end);

	void update(int pos, int nDeleted, int nInserted);

	int start() const { return mStart; }

	int end() const { return mEnd; }

	bool selected() const { return mSelected; }

	void selected(bool b) { mSelected = b; }

	int includes(int pos) const;

	int position(int* start, int* end) const;

protected:

	int mStart;
	int mEnd;
	bool mSelected;
};


typedef void(*Fl_Text_Modify_Cb)(int pos, int nInserted, int nDeleted,
	int nRestyled, const char* deletedText,
	void* cbArg);


typedef void(*Fl_Text_Predelete_Cb)(int pos, int nDeleted, void* cbArg);


class FL_EXPORT Fl_Text_Buffer {
public:

	Fl_Text_Buffer(int requestedSize = 0, int preferredGapSize = 1024);

	~Fl_Text_Buffer();

	int length() const { return mLength; }

	char* text() const;

	void text(const char* text);

	char* text_range(int start, int end) const;

	unsigned int char_at(int pos) const;

	char byte_at(int pos) const;

	const char *address(int pos) const
	{
		return (pos < mGapStart) ? mBuf + pos : mBuf + pos + mGapEnd - mGapStart;
	}

	char *address(int pos)
	{
		return (pos < mGapStart) ? mBuf + pos : mBuf + pos + mGapEnd - mGapStart;
	}

	void insert(int pos, const char* text);

	void append(const char* t) { insert(length(), t); }

	void remove(int start, int end);

	void replace(int start, int end, const char *text);

	void copy(Fl_Text_Buffer* fromBuf, int fromStart, int fromEnd, int toPos);

	int undo(int *cp = 0);

	void canUndo(char flag = 1);

	int insertfile(const char *file, int pos, int buflen = 128 * 1024);

	int appendfile(const char *file, int buflen = 128 * 1024)
	{
		return insertfile(file, length(), buflen);
	}

	int loadfile(const char *file, int buflen = 128 * 1024)
	{
		select(0, length()); remove_selection(); return appendfile(file, buflen);
	}

	int outputfile(const char *file, int start, int end, int buflen = 128 * 1024);

	int savefile(const char *file, int buflen = 128 * 1024)
	{
		return outputfile(file, 0, length(), buflen);
	}

	int tab_distance() const { return mTabDist; }

	void tab_distance(int tabDist);

	void select(int start, int end);

	int selected() const { return mPrimary.selected(); }

	void unselect();

	int selection_position(int* start, int* end);

	char* selection_text();

	void remove_selection();

	void replace_selection(const char* text);

	void secondary_select(int start, int end);

	int secondary_selected() { return mSecondary.selected(); }

	void secondary_unselect();

	int secondary_selection_position(int* start, int* end);

	char* secondary_selection_text();

	void remove_secondary_selection();

	void replace_secondary_selection(const char* text);

	void highlight(int start, int end);

	int highlight() { return mHighlight.selected(); }

	void unhighlight();

	int highlight_position(int* start, int* end);

	char* highlight_text();

	void add_modify_callback(Fl_Text_Modify_Cb bufModifiedCB, void* cbArg);

	void remove_modify_callback(Fl_Text_Modify_Cb bufModifiedCB, void* cbArg);

	void call_modify_callbacks() { call_modify_callbacks(0, 0, 0, 0, 0); }

	void add_predelete_callback(Fl_Text_Predelete_Cb bufPredelCB, void* cbArg);

	void remove_predelete_callback(Fl_Text_Predelete_Cb predelCB, void* cbArg);

	void call_predelete_callbacks() { call_predelete_callbacks(0, 0); }

	char* line_text(int pos) const;

	int line_start(int pos) const;

	int line_end(int pos) const;

	int word_start(int pos) const;

	int word_end(int pos) const;

	int count_displayed_characters(int lineStartPos, int targetPos) const;

	int skip_displayed_characters(int lineStartPos, int nChars);

	int count_lines(int startPos, int endPos) const;

	int skip_lines(int startPos, int nLines);

	int rewind_lines(int startPos, int nLines);

	int findchar_forward(int startPos, unsigned searchChar, int* foundPos) const;

	int findchar_backward(int startPos, unsigned int searchChar, int* foundPos) const;

	int search_forward(int startPos, const char* searchString, int* foundPos,
		int matchCase = 0) const;

	int search_backward(int startPos, const char* searchString, int* foundPos,
		int matchCase = 0) const;

	const Fl_Text_Selection* primary_selection() const { return &mPrimary; }

	Fl_Text_Selection* primary_selection() { return &mPrimary; }

	const Fl_Text_Selection* secondary_selection() const { return &mSecondary; }

	const Fl_Text_Selection* highlight_selection() const { return &mHighlight; }

	int prev_char(int ix) const;
	int prev_char_clipped(int ix) const;

	int next_char(int ix) const;
	int next_char_clipped(int ix) const;

	int utf8_align(int) const;

	int input_file_was_transcoded;

	static const char* file_encoding_warning_message;

	void(*transcoding_warning_action)(Fl_Text_Buffer*);

protected:

	void call_modify_callbacks(int pos, int nDeleted, int nInserted,
		int nRestyled, const char* deletedText) const;

	void call_predelete_callbacks(int pos, int nDeleted) const;

	int insert_(int pos, const char* text);

	void remove_(int start, int end);

	void redisplay_selection(Fl_Text_Selection* oldSelection,
		Fl_Text_Selection* newSelection) const;

	void move_gap(int pos);

	void reallocate_with_gap(int newGapStart, int newGapLen);

	char* selection_text_(Fl_Text_Selection* sel) const;

	void remove_selection_(Fl_Text_Selection* sel);

	void replace_selection_(Fl_Text_Selection* sel, const char* text);

	void update_selections(int pos, int nDeleted, int nInserted);

	Fl_Text_Selection mPrimary;
	Fl_Text_Selection mSecondary;
	Fl_Text_Selection mHighlight;
	int mLength;
	char* mBuf;
	int mGapStart;
	int mGapEnd;
	// The hardware tab distance used by all displays for this buffer,
	// and used in computing offsets for rectangular selection operations.
	int mTabDist;
	int mNModifyProcs;
	Fl_Text_Modify_Cb *mModifyProcs;
	void** mCbArgs;
	int mNPredeleteProcs;
	Fl_Text_Predelete_Cb *mPredeleteProcs;
	void **mPredeleteCbArgs;
	int mCursorPosHint;
	char mCanUndo;
	int mPreferredGapSize;
};

#endif

//
// End of "$Id$".
//