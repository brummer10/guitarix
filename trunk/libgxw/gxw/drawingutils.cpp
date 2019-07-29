/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "drawingutils.h"
#include <cstring> 
#include <algorithm> 

void gx_draw_rect (GtkWidget * widget, const gchar * type, GtkStateType * state, gint x, gint y, gint width, gint height, gint rad, float bevel) {
    GdkDrawingContext* ctx = gdk_window_begin_draw_frame(gtk_widget_get_window(widget), nullptr);
    cairo_t * cr = gdk_drawing_context_get_cairo_context(ctx);
    float r, g, b;
    gx_get_color(widget, type, state, &r, &g, &b);
    gx_create_rectangle(cr, x, y, width, height, rad);
	cairo_set_source_rgb(cr, r, g, b);
	cairo_fill(cr);

    if (bevel)
        gx_bevel(cr, x, y, width, height, rad, bevel);

    gdk_window_end_draw_frame(gtk_widget_get_window(widget), ctx);
}
void _gx_draw_inset (cairo_t * cr, gint x, gint y, gint width, gint height, gint rad, gint depth) {
    cairo_pattern_t *pat = cairo_pattern_create_linear (x, y, x, y + height);
    cairo_pattern_add_color_stop_rgba(pat, 0.0, 0.0, 0.0, 0.0, 0.33);
    cairo_pattern_add_color_stop_rgba(pat, 1.0, 1.0, 1.0, 1.0, 0.1);
    cairo_set_source(cr, pat);
    gx_create_rectangle(cr, x-depth, y-depth, width+2*depth, height+2*depth, rad);
	cairo_fill(cr);
    cairo_pattern_destroy (pat);
}
void gx_draw_inset (GtkWidget * widget, gint x, gint y, gint width, gint height, gint rad, gint depth) {
    GdkDrawingContext* ctx = gdk_window_begin_draw_frame(gtk_widget_get_window(widget), nullptr);
    cairo_t * cr = gdk_drawing_context_get_cairo_context(ctx);
    _gx_draw_inset(cr, x, y, width, height, rad, depth);
    gdk_window_end_draw_frame(gtk_widget_get_window(widget), ctx);
}
void _gx_draw_glass (cairo_t *cr, gint x, gint y, gint width, gint height, gint rad) {
    cairo_pattern_t *pat = cairo_pattern_create_linear (x, y, x, y + 3);
    cairo_pattern_add_color_stop_rgba(pat, 0.0, 0.0, 0.0, 0.0, 0.5);
    cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.0, 0.0, 0.0, 0.0);
    cairo_set_source(cr, pat);
    gx_create_rectangle(cr, x, y, width, height, rad);
	cairo_fill(cr);
    cairo_pattern_destroy (pat);
}
void gx_draw_glass (GtkWidget * widget, gint x, gint y, gint width, gint height, gint rad) {
    GdkDrawingContext* ctx = gdk_window_begin_draw_frame(gtk_widget_get_window(widget), nullptr);
    cairo_t * cr = gdk_drawing_context_get_cairo_context(ctx);
    _gx_draw_glass(cr, x, y, width, height, rad);
    gdk_window_end_draw_frame(gtk_widget_get_window(widget), ctx);
}

void gx_get_bg_color (GtkWidget * widget, GtkStateType * state, float * r, float * g, float * b) {
    gx_get_color(widget, "bg", state, r, g, b);
}
void gx_get_fg_color (GtkWidget * widget, GtkStateType * state, float * r, float * g, float * b) {
    gx_get_color(widget, "fg", state, r, g, b);
}
void gx_get_base_color (GtkWidget * widget, GtkStateType * state, float * r, float * g, float * b) {
    gx_get_color(widget, "base", state, r, g, b);
}
void gx_get_text_color (GtkWidget * widget, GtkStateType * state, float * r, float * g, float * b) {
    gx_get_color(widget, "text", state, r, g, b);
}
void gx_get_color (GtkWidget * widget, const gchar * type, GtkStateType * state, float * r, float * g, float * b) {
    GdkColor color;
    GtkStyle * style = gtk_widget_get_style (widget);
    if (style != NULL) {
        GtkStateType s;
        if (state)
            s = *state;
        else
            s = gtk_widget_get_state(widget);
        color = style->bg[s];
        if (!strcmp(type, "bg"))
            color = style->bg[s];
        if (!strcmp(type, "fg"))
            color = style->fg[s];
        if (!strcmp(type, "base"))
            color = style->base[s];
        if (!strcmp(type, "text"))
            color = style->text[s];
        *r = float(color.red)   / 65535;
        *g = float(color.green) / 65535;
        *b = float(color.blue)  / 65535;
    }
}

void gx_create_rectangle (cairo_t * cr, gint x, gint y, gint width, gint height, gint rad) {
    if (rad == 0) {
        cairo_rectangle(cr, x, y, width, height);
        return;
    }
    cairo_move_to(cr,x+rad,y);                      // Move to A
    cairo_line_to(cr,x+width-rad,y);                    // Straight line to B
    cairo_curve_to(cr,x+width,y,x+width,y,x+width,y+rad);       // Curve to C, Control points are both at Q
    cairo_line_to(cr,x+width,y+height-rad);                  // Move to D
    cairo_curve_to(cr,x+width,y+height,x+width,y+height,x+width-rad,y+height); // Curve to E
    cairo_line_to(cr,x+rad,y+height);                    // Line to F
    cairo_curve_to(cr,x,y+height,x,y+height,x,y+height-rad);       // Curve to G
    cairo_line_to(cr,x,y+rad);                      // Line to H
    cairo_curve_to(cr,x,y,x,y,x+rad,y);             // Curve to A
}

void gx_bevel (cairo_t * cr, gint x, gint y, gint width, gint height, gint rad, float bevel) {
    if (bevel == 0)
        return;
    cairo_save(cr);
    gx_create_rectangle(cr, x, y, width, height, rad);
    cairo_pattern_t * pat;
    if (bevel > 0)
        pat = cairo_pattern_create_linear (x, y, x, y + height);
    else
        pat = cairo_pattern_create_linear (x, y + height, x, y);
    cairo_pattern_add_color_stop_rgba(pat, 0.0, 1.0, 1.0, 1.0, bevel / 2);
    cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.0, 0.0, 0.0, bevel);
    cairo_set_source(cr, pat);
    cairo_set_operator(cr, CAIRO_OPERATOR_SOFT_LIGHT);
    cairo_fill_preserve(cr);
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_fill(cr);
    cairo_pattern_destroy (pat);
    cairo_restore(cr);
}
