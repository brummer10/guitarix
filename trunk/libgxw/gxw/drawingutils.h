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
 

#ifndef __DRAWINGUTILS_H__
#define __DRAWINGUTILS_H__

#include <gtk/gtk.h>

void gx_draw_simple_box (GtkWidget * widget, GdkEventExpose * ev, gint x, gint y, gint w, gint h);
void gx_draw_rounded_rectangle(cairo_t * cr, gint x, gint y, gint w, gint h, gint r);
void gx_get_bg_color(GtkWidget * widget, gint state, float * r, float * g, float * b);
void gx_get_fg_color(GtkWidget * widget, gint state, float * r, float * g, float * b);
void gx_get_base_color(GtkWidget * widget, gint state, float * r, float * g, float * b);
void gx_get_text_color(GtkWidget * widget, gint state, float * r, float * g, float * b);
void gx_get_color(GtkWidget * widget, const gchar * type, gint state, float * r, float * g, float * b);

#endif /* __DRAWINGUTILS_H__ */
