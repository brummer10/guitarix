/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 * --------------------------------------------------------------------------
 */

/* ------- This is the cairo namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_CAIRO_CALLBACKS_H_
#define SRC_HEADERS_GX_CAIRO_CALLBACKS_H_

namespace gx_cairo
{
// forwarddeclaration
gboolean conv_widget_draw (GtkWidget *wi, cairo_t *cr, gpointer user_data);
gboolean info_box_draw(GtkWidget *wi, cairo_t *cr, gpointer user_data);
gboolean error_box_draw(GtkWidget *wi, cairo_t *cr, gpointer user_data);
gboolean start_box_draw(GtkWidget *wi, cairo_t *cr, gpointer user_data);
gboolean rectangle_skin_color_draw(GtkWidget *wi, cairo_t *cr, gpointer user_data);
gboolean splash_draw(GtkWidget *wi, cairo_t* cr, gpointer user_data);
}
#endif  // SRC_HEADERS_GX_CAIRO_CALLBACKS_H_

