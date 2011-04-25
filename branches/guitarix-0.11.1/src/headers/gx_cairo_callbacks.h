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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 */

/* ------- This is the cairo namespace ------- */

#pragma once

namespace gx_cairo
{

extern "C" {
	gboolean filter_box_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean vbox_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean tribal_box_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean AmpBox_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean level_meter_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean zac_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean convolver_icon_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean rectangle_skin_color_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean rectangle_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean upper_widget_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean conv_widget_expose (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean amp_expose  (GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean boxamp_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean eq_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean plug_box_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean info_box_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
	gboolean slooper_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data);
}

void gx_init_pixmaps();

}
