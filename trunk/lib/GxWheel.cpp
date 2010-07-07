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

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include "GxWheel.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <gtk/gtkprivate.h>

#define P_(s) (s)   // FIXME -> gettext

static gboolean gx_wheel_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_wheel_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_wheel_button_press (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_wheel_pointer_motion (GtkWidget *widget, GdkEventMotion *event);

G_DEFINE_TYPE(GxWheel, gx_wheel, GX_TYPE_REGLER);

static void gx_wheel_class_init(GxWheelClass *klass)
{
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;

	widget_class->expose_event = gx_wheel_expose;
	widget_class->size_request = gx_wheel_size_request;
	widget_class->button_press_event = gx_wheel_button_press;
	widget_class->motion_notify_event = gx_wheel_pointer_motion;
}

static gboolean gx_wheel_expose (GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_WHEEL(widget));
	GxRegler *regler = GX_REGLER(widget);
	GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_back", GtkIconSize(-1), NULL);
	GdkPixbuf *ws = gtk_widget_render_icon(widget, "wheel_fringe", GtkIconSize(-1), NULL);
	GdkPixbuf *wp = gtk_widget_render_icon(widget, "wheel_pointer", GtkIconSize(-1), NULL);
	GdkRectangle image_rect, value_rect;
	GdkPoint text_pos;
	image_rect.width = gdk_pixbuf_get_width(wb);
	image_rect.height = gdk_pixbuf_get_height(wb);
	gint step = gdk_pixbuf_get_width(ws) / 2;
	gdouble wheelstate = _gx_regler_get_positions(
		regler, step, &image_rect, &value_rect, &text_pos);
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	int smoth_pointer = 0;
	if (wheelstate > (adj->upper - adj->lower)) {
		smoth_pointer = -4;
	}
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                wb, 0, 0,
	                image_rect.x, image_rect.y, image_rect.width, image_rect.height,
	                GDK_RGB_DITHER_NORMAL, 0, 0);
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                ws, wheelstate + image_rect.width, 0,
	                image_rect.x, image_rect.y, image_rect.width, image_rect.height,
	                GDK_RGB_DITHER_NORMAL, 0, 0);
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                wp,0, 0,
	                image_rect.x+smoth_pointer+wheelstate*0.4, image_rect.y,
	                gdk_pixbuf_get_width(wp), image_rect.height,
	                GDK_RGB_DITHER_NORMAL, 0, 0);
	_gx_regler_display_value(regler, &value_rect);
	return TRUE;
}


static void gx_wheel_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_WHEEL(widget));
	GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_back", GtkIconSize(-1), NULL);
	requisition->width = gdk_pixbuf_get_width(wb);
	requisition->height = gdk_pixbuf_get_height(wb);
	_gx_regler_calc_size_request(GX_REGLER(widget), requisition);
}

static gboolean gx_wheel_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_WHEEL(widget));
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));

	if (event->button == 3) {
		return GTK_WIDGET_CLASS(gx_wheel_parent_class)->button_press_event(widget, event);
	}

	if (event->button != 1) {
		return FALSE;
	}

	gtk_widget_grab_focus(widget);
	gtk_widget_grab_default (widget);
	gtk_grab_add(widget);
	GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_back", GtkIconSize(-1), NULL);
	gint width = gdk_pixbuf_get_width(wb);
	int  wheelx = (widget->allocation.width - width) / 2;
	double pos = adj->lower + (((event->x - wheelx)*0.03)* (adj->upper - adj->lower));
	gtk_range_set_value(GTK_RANGE(widget), _gx_regler_get_value(adj,pos));
	return FALSE;
}

/****************************************************************
 ** set the value from mouse movement
 */

static gboolean gx_wheel_pointer_motion (GtkWidget *widget, GdkEventMotion *event)
{
	g_assert(GX_IS_WHEEL(widget));
	if (!GTK_WIDGET_HAS_GRAB(widget)) {
		return FALSE;
	}
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	gdk_event_request_motions (event);
	GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_back", GtkIconSize(-1), NULL);
	gint width = gdk_pixbuf_get_width(wb);
	if (event->x > 0) {
		int  wheelx = (widget->allocation.width - width) / 2;
		double pos = adj->lower + (((event->x - wheelx)*0.03)* (adj->upper - adj->lower));
		gtk_range_set_value(GTK_RANGE(widget), _gx_regler_get_value(adj,pos));
	}
	return FALSE;
}

static void gx_wheel_init(GxWheel *wheel)
{
}
