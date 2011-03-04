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

#include "GxWheel.h"
#include <gtk/gtkmain.h>

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
	widget_class->enter_notify_event = NULL;
	widget_class->leave_notify_event = NULL;
}

static gboolean gx_wheel_expose (GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_WHEEL(widget));
	GxRegler *regler = GX_REGLER(widget);
	GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_back", GtkIconSize(-1), NULL);
	GdkPixbuf *ws = gtk_widget_render_icon(widget, "wheel_fringe", GtkIconSize(-1), NULL);
	GdkPixbuf *wp = gtk_widget_render_icon(widget, "wheel_pointer", GtkIconSize(-1), NULL);
	GdkRectangle image_rect, value_rect;
	image_rect.width = gdk_pixbuf_get_width(wb);
	image_rect.height = gdk_pixbuf_get_height(wb);
	gint step = gdk_pixbuf_get_width(ws) / 2;
	gdouble wheelstate = _gx_regler_get_step_pos(regler, step);
	_gx_regler_get_positions(regler, &image_rect, &value_rect);
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
	                ws, (int)(wheelstate) + image_rect.width, 0,
	                image_rect.x, image_rect.y, image_rect.width, image_rect.height,
	                GDK_RGB_DITHER_NORMAL, 0, 0);
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                wp,0, 0,
	                image_rect.x+smoth_pointer+(int)(wheelstate*0.4), image_rect.y,
	                gdk_pixbuf_get_width(wp), image_rect.height,
	                GDK_RGB_DITHER_NORMAL, 0, 0);
	_gx_regler_display_value(regler, &value_rect);
	g_object_unref(wb);
	g_object_unref(ws);
	g_object_unref(wp);
	return TRUE;
}


static void gx_wheel_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_WHEEL(widget));
	GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_back", GtkIconSize(-1), NULL);
	requisition->width = gdk_pixbuf_get_width(wb);
	requisition->height = gdk_pixbuf_get_height(wb);
	_gx_regler_calc_size_request(GX_REGLER(widget), requisition);
	g_object_unref(wb);
}

static gboolean wheel_set_from_pointer(GtkWidget *widget, gdouble x, gdouble y, gboolean drag, int button)
{
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_back", GtkIconSize(-1), NULL);
	GdkRectangle image_rect, value_rect;
	image_rect.width = gdk_pixbuf_get_width(wb);
	image_rect.height = gdk_pixbuf_get_height(wb);
	x += widget->allocation.x;
	y += widget->allocation.y;
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	if (!drag) {
		GdkRectangle *rect = NULL;
		if (_approx_in_rectangle(x, y, &image_rect)) {
			if (button == 3) {
				rect = &image_rect;
			}
		} else if (_approx_in_rectangle(x, y, &value_rect)) {
			if (button == 1 || button == 3) {
				rect = &value_rect;
			} else {
				return FALSE;
			}
		} else {
			return FALSE;
		}
		if (rect) {
			gboolean ret;
			g_signal_emit_by_name(GX_REGLER(widget), "values-entry", rect, &ret);
			return FALSE;
		}
	}
	double pos = adj->lower + ((x - image_rect.x)/image_rect.width)* (adj->upper - adj->lower);
	gboolean handled;
	g_signal_emit(widget, GX_REGLER_CLASS(G_OBJECT_GET_CLASS(widget))->change_value_id,
	              0, GTK_SCROLL_JUMP, pos, &handled);
	g_object_unref(wb);
	return TRUE;
}

static gboolean gx_wheel_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_WHEEL(widget));
	if (event->button != 1 && event->button != 3) {
		return FALSE;
	}
	gtk_widget_grab_focus(widget);
	if (wheel_set_from_pointer(widget, event->x, event->y, FALSE, event->button)) {
		gtk_grab_add(widget);
	}
	return FALSE;
}

/****************************************************************
 ** set the value from mouse movement
 */

static gboolean gx_wheel_pointer_motion (GtkWidget *widget, GdkEventMotion *event)
{
	g_assert(GX_IS_WHEEL(widget));
	gdk_event_request_motions (event);
	if (!gtk_widget_has_grab(widget)) {
		return FALSE;
	}
	wheel_set_from_pointer(widget, event->x, event->y, TRUE, 0);
	return FALSE;
}

static void gx_wheel_init(GxWheel *wheel)
{
}
