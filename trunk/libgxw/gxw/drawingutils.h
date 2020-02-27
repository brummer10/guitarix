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

GtkStyleContext *gx_get_entry_style_context();
void gx_draw_inset(cairo_t *cr, double x, double y, double width, double height, double rad, double depth);
void gx_draw_glass(cairo_t *cr, double x, double y, double width, double height, double rad);

void gx_create_rectangle(cairo_t * cr, double x, double y, double width, double height, double rad);
void gx_bevel(cairo_t * cr, double x, double y, double width, double height, double rad, double bevel);

#endif /* __DRAWINGUTILS_H__ */
