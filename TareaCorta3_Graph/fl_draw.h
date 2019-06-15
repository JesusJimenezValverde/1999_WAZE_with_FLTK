#pragma once
//
 // "$Id$"
 //
 // Portable drawing function header file for the Fast Light Tool Kit (FLTK).
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

#ifndef fl_draw_H
#define fl_draw_H

#include <FL/x.H>             // for Fl_Region
#include <FL/Enumerations.H>  // for the color names
#include <FL/Fl_Window.H>     // for fl_set_spot()
#include <FL/Fl_Device.H>     // for fl_graphics_driver

// Image class...
class Fl_Image;

// Label flags...
FL_EXPORT extern char fl_draw_shortcut;

// Colors:
inline void     fl_color(Fl_Color c) { fl_graphics_driver->color(c); } // select indexed color
inline void fl_color(int c) { fl_color((Fl_Color)c); }
inline void     fl_color(uchar r, uchar g, uchar b) { fl_graphics_driver->color(r, g, b); } // select actual color
inline Fl_Color fl_color() { return fl_graphics_driver->color(); }
// clip:
inline void fl_push_clip(int x, int y, int w, int h) { fl_graphics_driver->push_clip(x, y, w, h); }
#define fl_clip fl_push_clip

inline void fl_push_no_clip() { fl_graphics_driver->push_no_clip(); }
inline void fl_pop_clip() { fl_graphics_driver->pop_clip(); }
inline int fl_not_clipped(int x, int y, int w, int h) { return fl_graphics_driver->not_clipped(x, y, w, h); }
inline int fl_clip_box(int x, int y, int w, int h, int& X, int& Y, int& W, int& H)
{
	return fl_graphics_driver->clip_box(x, y, w, h, X, Y, W, H);
}
inline void fl_restore_clip() { fl_graphics_driver->restore_clip(); }
inline void fl_clip_region(Fl_Region r) { fl_graphics_driver->clip_region(r); }
inline Fl_Region fl_clip_region() { return fl_graphics_driver->clip_region(); }


// points:
inline void fl_point(int x, int y) { fl_graphics_driver->point(x, y); }

// line type:
inline void fl_line_style(int style, int width = 0, char* dashes = 0) { fl_graphics_driver->line_style(style, width, dashes); }
enum {
	FL_SOLID = 0,
	FL_DASH = 1,
	FL_DOT = 2,
	FL_DASHDOT = 3,
	FL_DASHDOTDOT = 4,

	FL_CAP_FLAT = 0x100,
	FL_CAP_ROUND = 0x200,
	FL_CAP_SQUARE = 0x300,

	FL_JOIN_MITER = 0x1000,
	FL_JOIN_ROUND = 0x2000,
	FL_JOIN_BEVEL = 0x3000
};

// rectangles tweaked to exactly fill the pixel rectangle:

inline void fl_rect(int x, int y, int w, int h) { fl_graphics_driver->rect(x, y, w, h); }

inline void fl_rect(int x, int y, int w, int h, Fl_Color c) { fl_color(c); fl_rect(x, y, w, h); }
inline void fl_rectf(int x, int y, int w, int h) { fl_graphics_driver->rectf(x, y, w, h); }
inline void fl_rectf(int x, int y, int w, int h, Fl_Color c) { fl_color(c); fl_rectf(x, y, w, h); }

/* note: doxygen comment here to avoid triplication in os-speciic files */
FL_EXPORT void fl_rectf(int x, int y, int w, int h, uchar r, uchar g, uchar b);

// line segments:
inline void fl_line(int x, int y, int x1, int y1) { fl_graphics_driver->line(x, y, x1, y1); }
inline void fl_line(int x, int y, int x1, int y1, int x2, int y2) { fl_graphics_driver->line(x, y, x1, y1, x2, y2); }

// closed line segments:
inline void fl_loop(int x, int y, int x1, int y1, int x2, int y2) { fl_graphics_driver->loop(x, y, x1, y1, x2, y2); }
inline void fl_loop(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3)
{
	fl_graphics_driver->loop(x, y, x1, y1, x2, y2, x3, y3);
}

// filled polygons
inline void fl_polygon(int x, int y, int x1, int y1, int x2, int y2) { fl_graphics_driver->polygon(x, y, x1, y1, x2, y2); }
inline void fl_polygon(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3)
{
	fl_graphics_driver->polygon(x, y, x1, y1, x2, y2, x3, y3);
}

// draw rectilinear lines, horizontal segment first:
inline void fl_xyline(int x, int y, int x1) { fl_graphics_driver->xyline(x, y, x1); }
inline void fl_xyline(int x, int y, int x1, int y2) { fl_graphics_driver->xyline(x, y, x1, y2); }
inline void fl_xyline(int x, int y, int x1, int y2, int x3) { fl_graphics_driver->xyline(x, y, x1, y2, x3); }

// draw rectilinear lines, vertical segment first:
inline void fl_yxline(int x, int y, int y1) { fl_graphics_driver->yxline(x, y, y1); }
inline void fl_yxline(int x, int y, int y1, int x2) { fl_graphics_driver->yxline(x, y, y1, x2); }
inline void fl_yxline(int x, int y, int y1, int x2, int y3) { fl_graphics_driver->yxline(x, y, y1, x2, y3); }

// circular lines and pie slices (code in fl_arci.C):
inline void fl_arc(int x, int y, int w, int h, double a1, double a2) { fl_graphics_driver->arc(x, y, w, h, a1, a2); }
inline void fl_pie(int x, int y, int w, int h, double a1, double a2) { fl_graphics_driver->pie(x, y, w, h, a1, a2); }
FL_EXPORT void fl_chord(int x, int y, int w, int h, double a1, double a2); // nyi

// scalable drawing code (code in fl_vertex.C and fl_arc.C):
inline void fl_push_matrix() { fl_graphics_driver->push_matrix(); }
inline void fl_pop_matrix() { fl_graphics_driver->pop_matrix(); }
inline void fl_scale(double x, double y) { fl_graphics_driver->scale(x, y); }
inline void fl_scale(double x) { fl_graphics_driver->scale(x, x); }
inline void fl_translate(double x, double y) { fl_graphics_driver->translate(x, y); }
inline void fl_rotate(double d) { fl_graphics_driver->rotate(d); }
inline void fl_mult_matrix(double a, double b, double c, double d, double x, double y)
{
	fl_graphics_driver->mult_matrix(a, b, c, d, x, y);
}
inline void fl_begin_points() { fl_graphics_driver->begin_points(); }
inline void fl_begin_line() { fl_graphics_driver->begin_line(); }
inline void fl_begin_loop() { fl_graphics_driver->begin_loop(); }
inline void fl_begin_polygon() { fl_graphics_driver->begin_polygon(); }
inline void fl_vertex(double x, double y) { fl_graphics_driver->vertex(x, y); }
inline void fl_curve(double X0, double Y0, double X1, double Y1, double X2, double Y2, double X3, double Y3)
{
	fl_graphics_driver->curve(X0, Y0, X1, Y1, X2, Y2, X3, Y3);
}
inline void fl_arc(double x, double y, double r, double start, double end) { fl_graphics_driver->arc(x, y, r, start, end); }
inline void fl_circle(double x, double y, double r) { fl_graphics_driver->circle(x, y, r); }
inline void fl_end_points() { fl_graphics_driver->end_points(); }
inline void fl_end_line() { fl_graphics_driver->end_line(); }
inline void fl_end_loop() { fl_graphics_driver->end_loop(); }
inline void fl_end_polygon() { fl_graphics_driver->end_polygon(); }
inline void fl_begin_complex_polygon() { fl_graphics_driver->begin_complex_polygon(); }
inline void fl_gap() { fl_graphics_driver->gap(); }
inline void fl_end_complex_polygon() { fl_graphics_driver->end_complex_polygon(); }
// get and use transformed positions:
inline double fl_transform_x(double x, double y) { return fl_graphics_driver->transform_x(x, y); }
inline double fl_transform_y(double x, double y) { return fl_graphics_driver->transform_y(x, y); }
inline double fl_transform_dx(double x, double y) { return fl_graphics_driver->transform_dx(x, y); }
inline double fl_transform_dy(double x, double y) { return fl_graphics_driver->transform_dy(x, y); }
inline void fl_transformed_vertex(double xf, double yf) { fl_graphics_driver->transformed_vertex(xf, yf); }
/* NOTE: doxygen comments here to avoid triplication in os-specific sources */

// Fonts:
inline void fl_font(Fl_Font face, Fl_Fontsize fsize) { fl_graphics_driver->font(face, fsize); }

inline Fl_Font fl_font() { return fl_graphics_driver->font(); }
inline Fl_Fontsize fl_size() { return fl_graphics_driver->size(); }

// information you can get about the current font:
inline int fl_height() { return fl_graphics_driver->height(); }
FL_EXPORT int fl_height(int font, int size);
inline int  fl_descent() { return fl_graphics_driver->descent(); }
FL_EXPORT double fl_width(const char* txt);
inline double fl_width(const char* txt, int n) { return fl_graphics_driver->width(txt, n); }
inline double fl_width(unsigned int c) { return fl_graphics_driver->width(c); }
FL_EXPORT void fl_text_extents(const char*, int& dx, int& dy, int& w, int& h); // NO fltk symbol expansion will be performed
inline void fl_text_extents(const char *t, int n, int& dx, int& dy, int& w, int& h)
{
	fl_graphics_driver->text_extents(t, n, dx, dy, w, h);
}

// font encoding:
// Note: doxygen comments here to avoid duplication for os-sepecific cases
FL_EXPORT const char *fl_latin1_to_local(const char *t, int n = -1);
FL_EXPORT const char *fl_local_to_latin1(const char *t, int n = -1);
FL_EXPORT const char *fl_mac_roman_to_local(const char *t, int n = -1);
FL_EXPORT const char *fl_local_to_mac_roman(const char *t, int n = -1);
FL_EXPORT void fl_draw(const char* str, int x, int y);
FL_EXPORT void fl_draw(int angle, const char* str, int x, int y);
inline void fl_draw(const char* str, int n, int x, int y) { fl_graphics_driver->draw(str, n, x, y); }
inline void fl_draw(int angle, const char* str, int n, int x, int y) { fl_graphics_driver->draw(angle, str, n, x, y); }
inline void fl_rtl_draw(const char* str, int n, int x, int y) { fl_graphics_driver->rtl_draw(str, n, x, y); }
FL_EXPORT void fl_measure(const char* str, int& x, int& y,
	int draw_symbols = 1);
FL_EXPORT void fl_draw(const char* str, int x, int y, int w, int h,
	Fl_Align align,
	Fl_Image* img = 0, int draw_symbols = 1);
FL_EXPORT void fl_draw(const char* str, int x, int y, int w, int h,
	Fl_Align align,
	void(*callthis)(const char *, int, int, int),
	Fl_Image* img = 0, int draw_symbols = 1);

// boxtypes:
FL_EXPORT void fl_frame(const char* s, int x, int y, int w, int h);
FL_EXPORT void fl_frame2(const char* s, int x, int y, int w, int h);
FL_EXPORT void fl_draw_box(Fl_Boxtype, int x, int y, int w, int h, Fl_Color);

// images:

inline void fl_draw_image(const uchar* buf, int X, int Y, int W, int H, int D = 3, int L = 0)
{
	fl_graphics_driver->draw_image(buf, X, Y, W, H, D, L);
}

inline void fl_draw_image_mono(const uchar* buf, int X, int Y, int W, int H, int D = 1, int L = 0)
{
	fl_graphics_driver->draw_image_mono(buf, X, Y, W, H, D, L);
}

inline void fl_draw_image(Fl_Draw_Image_Cb cb, void* data, int X, int Y, int W, int H, int D = 3)
{
	fl_graphics_driver->draw_image(cb, data, X, Y, W, H, D);
}

inline void fl_draw_image_mono(Fl_Draw_Image_Cb cb, void* data, int X, int Y, int W, int H, int D = 1)
{
	fl_graphics_driver->draw_image_mono(cb, data, X, Y, W, H, D);
}

/* note: doxygen comment here to avoid triplication in os-speciic files */
FL_EXPORT char fl_can_do_alpha_blending();

/* note: doxygen comment here to avoid triplication in os-speciic files */
FL_EXPORT uchar *fl_read_image(uchar *p, int X, int Y, int W, int H, int alpha = 0);

// pixmaps:
FL_EXPORT int fl_draw_pixmap(/*const*/ char* const* data, int x, int y, Fl_Color = FL_GRAY);
FL_EXPORT int fl_draw_pixmap(const char* const* cdata, int x, int y, Fl_Color = FL_GRAY);
FL_EXPORT int fl_measure_pixmap(/*const*/ char* const* data, int &w, int &h);
FL_EXPORT int fl_measure_pixmap(const char* const* cdata, int &w, int &h);

// other:
FL_EXPORT void fl_scroll(int X, int Y, int W, int H, int dx, int dy,
	void(*draw_area)(void*, int, int, int, int), void* data);
FL_EXPORT const char* fl_shortcut_label(unsigned int shortcut);
FL_EXPORT const char* fl_shortcut_label(unsigned int shortcut, const char **eom);
FL_EXPORT unsigned int fl_old_shortcut(const char* s);
FL_EXPORT void fl_overlay_rect(int x, int y, int w, int h);
FL_EXPORT void fl_overlay_clear();
FL_EXPORT void fl_cursor(Fl_Cursor);
FL_EXPORT void fl_cursor(Fl_Cursor, Fl_Color fg, Fl_Color bg = FL_WHITE);
FL_EXPORT const char* fl_expand_text(const char* from, char* buf, int maxbuf,
	double maxw, int& n, double &width,
	int wrap, int draw_symbols = 0);

// XIM:
FL_EXPORT void fl_set_status(int X, int Y, int W, int H);
FL_EXPORT void fl_set_spot(int font, int size, int X, int Y, int W, int H, Fl_Window *win = 0);
FL_EXPORT void fl_reset_spot(void);



// XForms symbols:
FL_EXPORT int fl_draw_symbol(const char* label, int x, int y, int w, int h, Fl_Color);
FL_EXPORT int fl_add_symbol(const char* name, void(*drawit)(Fl_Color), int scalable);
#endif

//
// End of "$Id$".
//