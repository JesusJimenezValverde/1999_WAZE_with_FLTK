#pragma once
 //
 // "$Id$"
 //
 // Enumerations for the Fast Light Tool Kit (FLTK).
 //
 // Copyright 1998-2017 by Bill Spitzak and others.
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

#ifndef Fl_Enumerations_H
#define Fl_Enumerations_H

/*
 ******************************************************************************
 * Notes on FL_ABI_VERSION and deprecated (obsolete) FLTK_ABI_VERSION:
 *
 * (1)  FLTK_ABI_VERSION is deprecated, but still defined below.
 *      Do NOT define FLTK_ABI_VERSION here - it would be overwritten later.
 *
 * (2)  FL_ABI_VERSION is now (as of FLTK 1.3.4) defined by configure
 *      or CMake. Do NOT define it here. Its definition will be included
 *      below by "#include <FL/abi-version.h>".
 *
 * (3)  If you use the provided IDE files (Windows VC++ or Xcode) you should
 *      edit the definition in the provided file abi-version.ide. The correct
 *      file is `/path/to/fltk/abi-version.ide' .
 *
 ******************************************************************************
 * For more informations on FL_ABI_VERSION see README.abi-version.txt.
 ******************************************************************************
 */

#include <FL/abi-version.h>

#  include "Fl_Export.H"
#  include "fl_types.h"


#define FL_MAJOR_VERSION        1

#define FL_MINOR_VERSION        3

#define FL_PATCH_VERSION        5

#define FL_VERSION      ( (double)FL_MAJOR_VERSION + \
                           (double)FL_MINOR_VERSION * 0.01 + \
                           (double)FL_PATCH_VERSION * 0.0001 )

#define FL_API_VERSION (FL_MAJOR_VERSION*10000 + FL_MINOR_VERSION*100 + FL_PATCH_VERSION)

#ifndef FL_ABI_VERSION
#define FL_ABI_VERSION (FL_MAJOR_VERSION*10000 + FL_MINOR_VERSION*100)
#endif

 /*
   Check if FL_ABI_VERSION is out of allowed range; redefine if necessary.

   This is done to prevent users from defining an illegal ABI version.

   Rule: FL_MAJOR_VERSION * 10000 + FL_MINOR_VERSION * 100
		   <= FL_ABI_VERSION <= FL_API_VERSION.

   Example (FLTK 1.3.4):

	 10300 <= FL_ABI_VERSION <= 10304

   Note: configure + CMake can be used to define FL_ABI_VERSION, but they
   do not check validity. This is done here.
 */

#if FL_ABI_VERSION < FL_MAJOR_VERSION*10000 + FL_MINOR_VERSION*100

# undef FL_ABI_VERSION
# define FL_ABI_VERSION (FL_MAJOR_VERSION*10000 + FL_MINOR_VERSION*100)

#elif FL_ABI_VERSION > FL_API_VERSION

# undef FL_ABI_VERSION
# define FL_ABI_VERSION FL_API_VERSION

#endif

 /*
   FLTK_ABI_VERSION is deprecated (replaced by FL_ABI_VERSION).

   This deprecated constant will be removed in FLTK 1.4.0 and later.
   Please use FL_ABI_VERSION when FLTK 1.4.0 has been released.
 */

#ifdef FLTK_ABI_VERSION
#undef FLTK_ABI_VERSION
#endif

#define FLTK_ABI_VERSION FL_ABI_VERSION
 // group: Version Numbers

// DEV NOTE: Keep this list in sync with FL/names.H
enum Fl_Event { // events
	FL_NO_EVENT = 0,

	FL_PUSH = 1,

	FL_RELEASE = 2,

	FL_ENTER = 3,

	FL_LEAVE = 4,

	FL_DRAG = 5,

	FL_FOCUS = 6,

	FL_UNFOCUS = 7,

	FL_KEYDOWN = 8,

	FL_KEYBOARD = 8,

	FL_KEYUP = 9,

	FL_CLOSE = 10,

	FL_MOVE = 11,

	FL_SHORTCUT = 12,

	FL_DEACTIVATE = 13,

	FL_ACTIVATE = 14,

	FL_HIDE = 15,

	FL_SHOW = 16,

	FL_PASTE = 17,

	FL_SELECTIONCLEAR = 18,

	FL_MOUSEWHEEL = 19,

	FL_DND_ENTER = 20,

	FL_DND_DRAG = 21,

	FL_DND_LEAVE = 22,

	FL_DND_RELEASE = 23,
	FL_SCREEN_CONFIGURATION_CHANGED = 24,
	FL_FULLSCREEN = 25,
	FL_ZOOM_GESTURE = 26
};

enum Fl_When { // Fl_Widget::when():
	FL_WHEN_NEVER = 0,
	FL_WHEN_CHANGED = 1,
	FL_WHEN_NOT_CHANGED = 2,
	FL_WHEN_RELEASE = 4,
	FL_WHEN_RELEASE_ALWAYS = 6,
	FL_WHEN_ENTER_KEY = 8,
	FL_WHEN_ENTER_KEY_ALWAYS = 10,
	FL_WHEN_ENTER_KEY_CHANGED = 11
};
// group: When Conditions


// FIXME: These codes collide with valid Unicode keys

#define FL_Button       0xfee8  
#define FL_BackSpace    0xff08  
#define FL_Tab          0xff09  
#define FL_Iso_Key      0xff0c  
#define FL_Enter        0xff0d  
#define FL_Pause        0xff13  
#define FL_Scroll_Lock  0xff14  
#define FL_Escape       0xff1b  
#define FL_Kana         0xff2e  
#define FL_Eisu         0xff2f  
#define FL_Yen          0xff30  
#define FL_JIS_Underscore 0xff31 
#define FL_Home         0xff50  
#define FL_Left         0xff51  
#define FL_Up           0xff52  
#define FL_Right        0xff53  
#define FL_Down         0xff54  
#define FL_Page_Up      0xff55  
#define FL_Page_Down    0xff56  
#define FL_End          0xff57  
#define FL_Print        0xff61  
#define FL_Insert       0xff63  
#define FL_Menu         0xff67  
#define FL_Help         0xff68  
#define FL_Num_Lock     0xff7f  
#define FL_KP           0xff80  
#define FL_KP_Enter     0xff8d  
#define FL_KP_Last      0xffbd  
#define FL_F            0xffbd  
#define FL_F_Last       0xffe0  
#define FL_Shift_L      0xffe1  
#define FL_Shift_R      0xffe2  
#define FL_Control_L    0xffe3  
#define FL_Control_R    0xffe4  
#define FL_Caps_Lock    0xffe5  
#define FL_Meta_L       0xffe7  
#define FL_Meta_R       0xffe8  
#define FL_Alt_L        0xffe9  
#define FL_Alt_R        0xffea  
#define FL_Delete       0xffff  

// These use the Private Use Area (PUA) of the Basic Multilingual Plane
// of Unicode. Guaranteed not to conflict with a proper Unicode character.

// These primarily map to the XFree86 keysym range
#define FL_Volume_Down  0xEF11   /* Volume control down        */
#define FL_Volume_Mute  0xEF12   /* Mute sound from the system */
#define FL_Volume_Up    0xEF13   /* Volume control up          */
#define FL_Media_Play   0xEF14   /* Start playing of audio     */
#define FL_Media_Stop   0xEF15   /* Stop playing audio         */
#define FL_Media_Prev   0xEF16   /* Previous track             */
#define FL_Media_Next   0xEF17   /* Next track                 */
#define FL_Home_Page    0xEF18   /* Display user's home page   */
#define FL_Mail         0xEF19   /* Invoke user's mail program */
#define FL_Search       0xEF1B   /* Search                     */
#define FL_Back         0xEF26   /* Like back on a browser     */
#define FL_Forward      0xEF27   /* Like forward on a browser  */
#define FL_Stop         0xEF28   /* Stop current operation     */
#define FL_Refresh      0xEF29   /* Refresh the page           */
#define FL_Sleep        0xEF2F   /* Put system to sleep        */
#define FL_Favorites    0xEF30   /* Show favorite locations    */
		// group: Mouse and Keyboard Events


#define FL_LEFT_MOUSE   1       
#define FL_MIDDLE_MOUSE 2       
#define FL_RIGHT_MOUSE  3       

				// group: Mouse Buttons


				// group: Event States

// FIXME: it would be nice to have the modifiers in the upper 8 bit so that
//        a unicode ke (24bit) can be sent as an unsigned with the modifiers.

#define FL_SHIFT        0x00010000      
#define FL_CAPS_LOCK    0x00020000      
#define FL_CTRL         0x00040000      
#define FL_ALT          0x00080000      
#define FL_NUM_LOCK     0x00100000      
										// most X servers do this?
#define FL_META         0x00400000      
										// correct for XFree86
#define FL_SCROLL_LOCK  0x00800000      
										// correct for XFree86
#define FL_BUTTON1      0x01000000      
#define FL_BUTTON2      0x02000000      
#define FL_BUTTON3      0x04000000      
#define FL_BUTTONS      0x7f000000      
#define FL_BUTTON(n)    (0x00800000<<(n)) 

#define FL_KEY_MASK 0x0000ffff          
										//   FIXME: Unicode needs 24 bits!

#ifdef __APPLE__
#  define FL_COMMAND    FL_META         
#  define FL_CONTROL    FL_CTRL         
#else
#  define FL_COMMAND    FL_CTRL         
#  define FL_CONTROL    FL_META         
#endif // __APPLE__
				// group: Event States

enum Fl_Boxtype { // boxtypes (if you change these you must fix fl_boxtype.cxx):

	FL_NO_BOX = 0,
	FL_FLAT_BOX,
	FL_UP_BOX,
	FL_DOWN_BOX,
	FL_UP_FRAME,
	FL_DOWN_FRAME,
	FL_THIN_UP_BOX,
	FL_THIN_DOWN_BOX,
	FL_THIN_UP_FRAME,
	FL_THIN_DOWN_FRAME,
	FL_ENGRAVED_BOX,
	FL_EMBOSSED_BOX,
	FL_ENGRAVED_FRAME,
	FL_EMBOSSED_FRAME,
	FL_BORDER_BOX,
	_FL_SHADOW_BOX,
	FL_BORDER_FRAME,
	_FL_SHADOW_FRAME,
	_FL_ROUNDED_BOX,
	_FL_RSHADOW_BOX,
	_FL_ROUNDED_FRAME,
	_FL_RFLAT_BOX,
	_FL_ROUND_UP_BOX,
	_FL_ROUND_DOWN_BOX,
	_FL_DIAMOND_UP_BOX,
	_FL_DIAMOND_DOWN_BOX,
	_FL_OVAL_BOX,
	_FL_OSHADOW_BOX,
	_FL_OVAL_FRAME,
	_FL_OFLAT_BOX,
	_FL_PLASTIC_UP_BOX,
	_FL_PLASTIC_DOWN_BOX,
	_FL_PLASTIC_UP_FRAME,
	_FL_PLASTIC_DOWN_FRAME,
	_FL_PLASTIC_THIN_UP_BOX,
	_FL_PLASTIC_THIN_DOWN_BOX,
	_FL_PLASTIC_ROUND_UP_BOX,
	_FL_PLASTIC_ROUND_DOWN_BOX,
	_FL_GTK_UP_BOX,
	_FL_GTK_DOWN_BOX,
	_FL_GTK_UP_FRAME,
	_FL_GTK_DOWN_FRAME,
	_FL_GTK_THIN_UP_BOX,
	_FL_GTK_THIN_DOWN_BOX,
	_FL_GTK_THIN_UP_FRAME,
	_FL_GTK_THIN_DOWN_FRAME,
	_FL_GTK_ROUND_UP_BOX,
	_FL_GTK_ROUND_DOWN_BOX,
	_FL_GLEAM_UP_BOX,
	_FL_GLEAM_DOWN_BOX,
	_FL_GLEAM_UP_FRAME,
	_FL_GLEAM_DOWN_FRAME,
	_FL_GLEAM_THIN_UP_BOX,
	_FL_GLEAM_THIN_DOWN_BOX,
	_FL_GLEAM_ROUND_UP_BOX,
	_FL_GLEAM_ROUND_DOWN_BOX,
	FL_FREE_BOXTYPE
};
extern FL_EXPORT Fl_Boxtype fl_define_FL_ROUND_UP_BOX();
#define FL_ROUND_UP_BOX fl_define_FL_ROUND_UP_BOX()
#define FL_ROUND_DOWN_BOX (Fl_Boxtype)(fl_define_FL_ROUND_UP_BOX()+1)
extern FL_EXPORT Fl_Boxtype fl_define_FL_SHADOW_BOX();
#define FL_SHADOW_BOX fl_define_FL_SHADOW_BOX()
#define FL_SHADOW_FRAME (Fl_Boxtype)(fl_define_FL_SHADOW_BOX()+2)
extern FL_EXPORT Fl_Boxtype fl_define_FL_ROUNDED_BOX();
#define FL_ROUNDED_BOX fl_define_FL_ROUNDED_BOX()
#define FL_ROUNDED_FRAME (Fl_Boxtype)(fl_define_FL_ROUNDED_BOX()+2)
extern FL_EXPORT Fl_Boxtype fl_define_FL_RFLAT_BOX();
#define FL_RFLAT_BOX fl_define_FL_RFLAT_BOX()
extern FL_EXPORT Fl_Boxtype fl_define_FL_RSHADOW_BOX();
#define FL_RSHADOW_BOX fl_define_FL_RSHADOW_BOX()
extern FL_EXPORT Fl_Boxtype fl_define_FL_DIAMOND_BOX();
#define FL_DIAMOND_UP_BOX fl_define_FL_DIAMOND_BOX()
#define FL_DIAMOND_DOWN_BOX (Fl_Boxtype)(fl_define_FL_DIAMOND_BOX()+1)
extern FL_EXPORT Fl_Boxtype fl_define_FL_OVAL_BOX();
#define FL_OVAL_BOX fl_define_FL_OVAL_BOX()
#define FL_OSHADOW_BOX (Fl_Boxtype)(fl_define_FL_OVAL_BOX()+1)
#define FL_OVAL_FRAME (Fl_Boxtype)(fl_define_FL_OVAL_BOX()+2)
#define FL_OFLAT_BOX (Fl_Boxtype)(fl_define_FL_OVAL_BOX()+3)

extern FL_EXPORT Fl_Boxtype fl_define_FL_PLASTIC_UP_BOX();
#define FL_PLASTIC_UP_BOX fl_define_FL_PLASTIC_UP_BOX()
#define FL_PLASTIC_DOWN_BOX (Fl_Boxtype)(fl_define_FL_PLASTIC_UP_BOX()+1)
#define FL_PLASTIC_UP_FRAME (Fl_Boxtype)(fl_define_FL_PLASTIC_UP_BOX()+2)
#define FL_PLASTIC_DOWN_FRAME (Fl_Boxtype)(fl_define_FL_PLASTIC_UP_BOX()+3)
#define FL_PLASTIC_THIN_UP_BOX (Fl_Boxtype)(fl_define_FL_PLASTIC_UP_BOX()+4)
#define FL_PLASTIC_THIN_DOWN_BOX (Fl_Boxtype)(fl_define_FL_PLASTIC_UP_BOX()+5)
#define FL_PLASTIC_ROUND_UP_BOX (Fl_Boxtype)(fl_define_FL_PLASTIC_UP_BOX()+6)
#define FL_PLASTIC_ROUND_DOWN_BOX (Fl_Boxtype)(fl_define_FL_PLASTIC_UP_BOX()+7)

extern FL_EXPORT Fl_Boxtype fl_define_FL_GTK_UP_BOX();
#define FL_GTK_UP_BOX fl_define_FL_GTK_UP_BOX()
#define FL_GTK_DOWN_BOX (Fl_Boxtype)(fl_define_FL_GTK_UP_BOX()+1)
#define FL_GTK_UP_FRAME (Fl_Boxtype)(fl_define_FL_GTK_UP_BOX()+2)
#define FL_GTK_DOWN_FRAME (Fl_Boxtype)(fl_define_FL_GTK_UP_BOX()+3)
#define FL_GTK_THIN_UP_BOX (Fl_Boxtype)(fl_define_FL_GTK_UP_BOX()+4)
#define FL_GTK_THIN_DOWN_BOX (Fl_Boxtype)(fl_define_FL_GTK_UP_BOX()+5)
#define FL_GTK_THIN_UP_FRAME (Fl_Boxtype)(fl_define_FL_GTK_UP_BOX()+6)
#define FL_GTK_THIN_DOWN_FRAME (Fl_Boxtype)(fl_define_FL_GTK_UP_BOX()+7)
#define FL_GTK_ROUND_UP_BOX (Fl_Boxtype)(fl_define_FL_GTK_UP_BOX()+8)
#define FL_GTK_ROUND_DOWN_BOX (Fl_Boxtype)(fl_define_FL_GTK_UP_BOX()+9)

extern FL_EXPORT Fl_Boxtype fl_define_FL_GLEAM_UP_BOX();
#define FL_GLEAM_UP_BOX fl_define_FL_GLEAM_UP_BOX()
#define FL_GLEAM_DOWN_BOX (Fl_Boxtype)(fl_define_FL_GLEAM_UP_BOX()+1)
#define FL_GLEAM_UP_FRAME (Fl_Boxtype)(fl_define_FL_GLEAM_UP_BOX()+2)
#define FL_GLEAM_DOWN_FRAME (Fl_Boxtype)(fl_define_FL_GLEAM_UP_BOX()+3)
#define FL_GLEAM_THIN_UP_BOX (Fl_Boxtype)(fl_define_FL_GLEAM_UP_BOX()+4)
#define FL_GLEAM_THIN_DOWN_BOX (Fl_Boxtype)(fl_define_FL_GLEAM_UP_BOX()+5)
#define FL_GLEAM_ROUND_UP_BOX (Fl_Boxtype)(fl_define_FL_GLEAM_UP_BOX()+6)
#define FL_GLEAM_ROUND_DOWN_BOX (Fl_Boxtype)(fl_define_FL_GLEAM_UP_BOX()+7)

// conversions of box types to other boxtypes:
inline Fl_Boxtype fl_box(Fl_Boxtype b) {
	return (Fl_Boxtype)((b < FL_UP_BOX || b % 4>1) ? b : (b - 2));
}
inline Fl_Boxtype fl_down(Fl_Boxtype b) {
	return (Fl_Boxtype)((b < FL_UP_BOX) ? b : (b | 1));
}
inline Fl_Boxtype fl_frame(Fl_Boxtype b) {
	return (Fl_Boxtype)((b % 4 < 2) ? b : (b + 2));
}

// back-compatibility box types:
#define FL_FRAME FL_ENGRAVED_FRAME
#define FL_FRAME_BOX FL_ENGRAVED_BOX
#define FL_CIRCLE_BOX FL_ROUND_DOWN_BOX
#define FL_DIAMOND_BOX FL_DIAMOND_DOWN_BOX
		// group: Box Types

enum Fl_Labeltype {     // labeltypes:
	FL_NORMAL_LABEL = 0,
	FL_NO_LABEL,
	_FL_SHADOW_LABEL,
	_FL_ENGRAVED_LABEL,
	_FL_EMBOSSED_LABEL,
	_FL_MULTI_LABEL,
	_FL_ICON_LABEL,
	_FL_IMAGE_LABEL,

	FL_FREE_LABELTYPE
};

#define FL_SYMBOL_LABEL FL_NORMAL_LABEL
extern Fl_Labeltype FL_EXPORT fl_define_FL_SHADOW_LABEL();
#define FL_SHADOW_LABEL fl_define_FL_SHADOW_LABEL()
extern Fl_Labeltype FL_EXPORT fl_define_FL_ENGRAVED_LABEL();
#define FL_ENGRAVED_LABEL fl_define_FL_ENGRAVED_LABEL()
extern Fl_Labeltype FL_EXPORT fl_define_FL_EMBOSSED_LABEL();
#define FL_EMBOSSED_LABEL fl_define_FL_EMBOSSED_LABEL()

typedef unsigned Fl_Align;
const Fl_Align FL_ALIGN_CENTER = (Fl_Align)0;
const Fl_Align FL_ALIGN_TOP = (Fl_Align)1;
const Fl_Align FL_ALIGN_BOTTOM = (Fl_Align)2;
const Fl_Align FL_ALIGN_LEFT = (Fl_Align)4;
const Fl_Align FL_ALIGN_RIGHT = (Fl_Align)8;
const Fl_Align FL_ALIGN_INSIDE = (Fl_Align)16;
const Fl_Align FL_ALIGN_TEXT_OVER_IMAGE = (Fl_Align)0x0020;
const Fl_Align FL_ALIGN_IMAGE_OVER_TEXT = (Fl_Align)0x0000;
const Fl_Align FL_ALIGN_CLIP = (Fl_Align)64;
const Fl_Align FL_ALIGN_WRAP = (Fl_Align)128;
const Fl_Align FL_ALIGN_IMAGE_NEXT_TO_TEXT = (Fl_Align)0x0100;
const Fl_Align FL_ALIGN_TEXT_NEXT_TO_IMAGE = (Fl_Align)0x0120;
const Fl_Align FL_ALIGN_IMAGE_BACKDROP = (Fl_Align)0x0200;
const Fl_Align FL_ALIGN_TOP_LEFT = FL_ALIGN_TOP | FL_ALIGN_LEFT;
const Fl_Align FL_ALIGN_TOP_RIGHT = FL_ALIGN_TOP | FL_ALIGN_RIGHT;
const Fl_Align FL_ALIGN_BOTTOM_LEFT = FL_ALIGN_BOTTOM | FL_ALIGN_LEFT;
const Fl_Align FL_ALIGN_BOTTOM_RIGHT = FL_ALIGN_BOTTOM | FL_ALIGN_RIGHT;
const Fl_Align FL_ALIGN_LEFT_TOP = 0x0007; // magic value
const Fl_Align FL_ALIGN_RIGHT_TOP = 0x000b; // magic value
const Fl_Align FL_ALIGN_LEFT_BOTTOM = 0x000d; // magic value
const Fl_Align FL_ALIGN_RIGHT_BOTTOM = 0x000e; // magic value
const Fl_Align FL_ALIGN_NOWRAP = (Fl_Align)0; // for back compatibility
const Fl_Align FL_ALIGN_POSITION_MASK = 0x000f; // left, right, top, bottom
const Fl_Align FL_ALIGN_IMAGE_MASK = 0x0320; // l/r, t/b, backdrop
typedef int Fl_Font;

const Fl_Font FL_HELVETICA = 0;
const Fl_Font FL_HELVETICA_BOLD = 1;
const Fl_Font FL_HELVETICA_ITALIC = 2;
const Fl_Font FL_HELVETICA_BOLD_ITALIC = 3;
const Fl_Font FL_COURIER = 4;
const Fl_Font FL_COURIER_BOLD = 5;
const Fl_Font FL_COURIER_ITALIC = 6;
const Fl_Font FL_COURIER_BOLD_ITALIC = 7;
const Fl_Font FL_TIMES = 8;
const Fl_Font FL_TIMES_BOLD = 9;
const Fl_Font FL_TIMES_ITALIC = 10;
const Fl_Font FL_TIMES_BOLD_ITALIC = 11;
const Fl_Font FL_SYMBOL = 12;
const Fl_Font FL_SCREEN = 13;
const Fl_Font FL_SCREEN_BOLD = 14;
const Fl_Font FL_ZAPF_DINGBATS = 15;

const Fl_Font FL_FREE_FONT = 16;
const Fl_Font FL_BOLD = 1;
const Fl_Font FL_ITALIC = 2;
const Fl_Font FL_BOLD_ITALIC = 3;

typedef int Fl_Fontsize;

extern FL_EXPORT Fl_Fontsize FL_NORMAL_SIZE;

typedef unsigned int Fl_Color;

// Standard colors. These are used as default colors in widgets and altered as necessary
const Fl_Color FL_FOREGROUND_COLOR = 0;
const Fl_Color FL_BACKGROUND2_COLOR = 7;
const Fl_Color FL_INACTIVE_COLOR = 8;
const Fl_Color FL_SELECTION_COLOR = 15;

// boxtypes generally limit themselves to these colors so
// the whole ramp is not allocated:

const Fl_Color FL_GRAY0 = 32;                 // 'A'
const Fl_Color FL_DARK3 = 39;                 // 'H'
const Fl_Color FL_DARK2 = 45;                 // 'N'
const Fl_Color FL_DARK1 = 47;                 // 'P'
const Fl_Color FL_BACKGROUND_COLOR = 49;       // 'R' default background color
const Fl_Color FL_LIGHT1 = 50;                 // 'S'
const Fl_Color FL_LIGHT2 = 52;                 // 'U'
const Fl_Color FL_LIGHT3 = 54;                 // 'W'

  // FLTK provides a 5x8x5 color cube that is used with colormap visuals

const Fl_Color FL_BLACK = 56;
const Fl_Color FL_RED = 88;
const Fl_Color FL_GREEN = 63;
const Fl_Color FL_YELLOW = 95;
const Fl_Color FL_BLUE = 216;
const Fl_Color FL_MAGENTA = 248;
const Fl_Color FL_CYAN = 223;
const Fl_Color FL_DARK_RED = 72;

const Fl_Color FL_DARK_GREEN = 60;
const Fl_Color FL_DARK_YELLOW = 76;
const Fl_Color FL_DARK_BLUE = 136;
const Fl_Color FL_DARK_MAGENTA = 152;
const Fl_Color FL_DARK_CYAN = 140;

const Fl_Color FL_WHITE = 255;


#define FL_FREE_COLOR     (Fl_Color)16
#define FL_NUM_FREE_COLOR 16
#define FL_GRAY_RAMP      (Fl_Color)32
#define FL_NUM_GRAY       24
#define FL_GRAY           FL_BACKGROUND_COLOR
#define FL_COLOR_CUBE     (Fl_Color)56
#define FL_NUM_RED        5
#define FL_NUM_GREEN      8
#define FL_NUM_BLUE       5

FL_EXPORT Fl_Color fl_inactive(Fl_Color c);

FL_EXPORT Fl_Color fl_contrast(Fl_Color fg, Fl_Color bg);

FL_EXPORT Fl_Color fl_color_average(Fl_Color c1, Fl_Color c2, float weight);

inline Fl_Color fl_lighter(Fl_Color c) { return fl_color_average(c, FL_WHITE, .67f); }

inline Fl_Color fl_darker(Fl_Color c) { return fl_color_average(c, FL_BLACK, .67f); }

inline Fl_Color fl_rgb_color(uchar r, uchar g, uchar b) {
	if (!r && !g && !b) return FL_BLACK;
	else return (Fl_Color)(((((r << 8) | g) << 8) | b) << 8);
}

inline Fl_Color fl_rgb_color(uchar g) {
	if (!g) return FL_BLACK;
	else return (Fl_Color)(((((g << 8) | g) << 8) | g) << 8);
}

inline Fl_Color fl_gray_ramp(int i) { return (Fl_Color)(i + FL_GRAY_RAMP); }

inline Fl_Color fl_color_cube(int r, int g, int b) {
	return (Fl_Color)((b*FL_NUM_RED + r) * FL_NUM_GREEN + g + FL_COLOR_CUBE);
}
// group: Colors


/* FIXME: We should renumber these, but that will break the ABI */
enum Fl_Cursor {
	FL_CURSOR_DEFAULT = 0,
	FL_CURSOR_ARROW = 35,
	FL_CURSOR_CROSS = 66,
	FL_CURSOR_WAIT = 76,
	FL_CURSOR_INSERT = 77,
	FL_CURSOR_HAND = 31,
	FL_CURSOR_HELP = 47,
	FL_CURSOR_MOVE = 27,
	/* Resize indicators */
	FL_CURSOR_NS = 78,
	FL_CURSOR_WE = 79,
	FL_CURSOR_NWSE = 80,
	FL_CURSOR_NESW = 81,
	FL_CURSOR_N = 70,
	FL_CURSOR_NE = 69,
	FL_CURSOR_E = 49,
	FL_CURSOR_SE = 8,
	FL_CURSOR_S = 9,
	FL_CURSOR_SW = 7,
	FL_CURSOR_W = 36,
	FL_CURSOR_NW = 68,
	FL_CURSOR_NONE = 255
};              // group: Cursors  

enum { // values for "when" passed to Fl::add_fd()
	FL_READ = 1,
	FL_WRITE = 4,
	FL_EXCEPT = 8
};

enum Fl_Mode {
	FL_RGB = 0,
	FL_INDEX = 1,
	FL_SINGLE = 0,
	FL_DOUBLE = 2,
	FL_ACCUM = 4,
	FL_ALPHA = 8,
	FL_DEPTH = 16,
	FL_STENCIL = 32,
	FL_RGB8 = 64,
	FL_MULTISAMPLE = 128,
	FL_STEREO = 256,
	FL_FAKE_SINGLE = 512, // Fake single buffered windows using double-buffer
	FL_OPENGL3 = 1024
};

// image alpha blending

#define FL_IMAGE_WITH_ALPHA 0x40000000

enum Fl_Damage {
	FL_DAMAGE_CHILD = 0x01,
	FL_DAMAGE_EXPOSE = 0x02,
	FL_DAMAGE_SCROLL = 0x04,
	FL_DAMAGE_OVERLAY = 0x08,
	FL_DAMAGE_USER1 = 0x10,
	FL_DAMAGE_USER2 = 0x20,
	FL_DAMAGE_ALL = 0x80
};

// FLTK 1.0.x compatibility definitions...
#  ifdef FLTK_1_0_COMPAT
#    define contrast    fl_contrast
#    define down        fl_down
#    define frame       fl_frame
#    define inactive    fl_inactive
#  endif // FLTK_1_0_COMPAT

#endif

//
// End of "$Id$".
//