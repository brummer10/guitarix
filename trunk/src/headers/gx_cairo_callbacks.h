/*
 * Copyright (C) 2009 Hermann Meyer and James Warden
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 */

/* ------- This is the cairo namespace ------- */

#pragma once

namespace gx_cairo
{

gboolean box12_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box11_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box10_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box9_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box8_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box7_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box6_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box5_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box4_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box3_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box2_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box1_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean box_expose  (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
gboolean label_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);

void gx_init_pixmaps();

}
