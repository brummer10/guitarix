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
 */

#include "GxRadioButton.h"

#define P_(s) (s)   // FIXME -> gettext

/****************************************************************
 ** GxRadioButton
 */

static void draw_indicator(GtkCheckButton *check_button, GdkRectangle *rect);

G_DEFINE_TYPE(GxRadioButton, gx_radio_button, GTK_TYPE_RADIO_BUTTON);

static void gx_radio_button_class_init(GxRadioButtonClass *klass)
{
	((GtkCheckButtonClass*)klass)->draw_indicator = draw_indicator;
}

static void gx_radio_button_init(GxRadioButton *radio_button)
{
}

static void draw_indicator(GtkCheckButton *check_button, GdkRectangle *rect)
{
	GtkWidget *widget = GTK_WIDGET(check_button);
	const char *s;
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button))) {
		s = "led_on";
	} else {
		s = "led_off";
	}
	GdkPixbuf *pb = gtk_widget_render_icon(widget, s, GTK_ICON_SIZE_BUTTON, NULL);
	int x = rect->x + (rect->width - gdk_pixbuf_get_width(pb)) / 2;
	int y = rect->y + (rect->height- gdk_pixbuf_get_height(pb))/ 2;
	gdk_draw_pixbuf(gtk_widget_get_window(widget), NULL, pb, 0, 0, x, y, -1, -1,
	                GDK_RGB_DITHER_NORMAL, 0, 0);
}
