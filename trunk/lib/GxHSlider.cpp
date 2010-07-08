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

#include "GxHSlider.h"
#include <gtk/gtkmain.h>

#define P_(s) (s)   // FIXME -> gettext

static gboolean gx_hslider_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_hslider_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_hslider_button_press (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_hslider_pointer_motion (GtkWidget *widget, GdkEventMotion *event);
static gboolean gx_hslider_enter_in (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_hslider_leave_out (GtkWidget *widget, GdkEventCrossing *event);

G_DEFINE_TYPE(GxHSlider, gx_hslider, GX_TYPE_REGLER);

#define get_stock_id(widget) (GX_HSLIDER_CLASS(GTK_OBJECT_GET_CLASS(widget))->stock_id)

static void gx_hslider_class_init(GxHSliderClass *klass)
{
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;

	widget_class->expose_event = gx_hslider_expose;
	widget_class->size_request = gx_hslider_size_request;
	widget_class->button_press_event = gx_hslider_button_press;
	widget_class->motion_notify_event = gx_hslider_pointer_motion;
	widget_class->enter_notify_event = gx_hslider_enter_in;
	widget_class->leave_notify_event = gx_hslider_leave_out;
	klass->stock_id = "hslider";
}

static void gx_hslider_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_HSLIDER(widget));
	gint slider_width;
	gtk_widget_style_get(widget, "slider-width", &slider_width, NULL);
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	requisition->width = gdk_pixbuf_get_width(pb) - slider_width;
	requisition->height = gdk_pixbuf_get_height(pb);
	_gx_regler_calc_size_request(GX_REGLER(widget), requisition);
	g_object_unref(pb);
}

static void hslider_expose(
	GtkWidget *widget, GdkRectangle *rect, gdouble sliderstate, GdkPixbuf *image,
	gdouble sat, gboolean has_focus, gboolean paint_focus)
{
	gint slider_width;
	gtk_widget_style_get(widget, "slider-width", &slider_width, NULL);
	GdkPixbuf *image1 = gdk_pixbuf_copy(image);
	gdk_pixbuf_copy_area(image, rect->width, 0, slider_width, rect->height, image1, sliderstate, 0);
	if (has_focus) {
		gdk_pixbuf_saturate_and_pixelate(image1, image1, sat, FALSE);
		if (paint_focus) {
			gtk_paint_focus(widget->style, widget->window, GTK_STATE_NORMAL, NULL, widget, NULL,
			                rect->x, rect->y, rect->width, rect->height);
		}
	}
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                image1, 0, 0, rect->x, rect->y,
	                rect->width, rect->height, GDK_RGB_DITHER_NORMAL, 0, 0);
	g_object_unref(image1);
}

static const gint sat = 70.0;

static gboolean gx_hslider_expose(GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_HSLIDER(widget));
	gint slider_width;
	GdkRectangle image_rect, value_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	gtk_widget_style_get(widget, "slider-width", &slider_width, NULL);
	image_rect.width = gdk_pixbuf_get_width(pb) - slider_width;
	image_rect.height = gdk_pixbuf_get_height(pb);
	gdouble sliderstate = _gx_regler_get_step_pos(GX_REGLER(widget), image_rect.width-slider_width);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	hslider_expose(widget, &image_rect, sliderstate, pb, sat, GTK_WIDGET_HAS_FOCUS(widget), TRUE);
	_gx_regler_display_value(GX_REGLER(widget), &value_rect);
	g_object_unref(pb);
	return FALSE;
}

static gboolean gx_hslider_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_HSLIDER(widget));
	gint slider_width;
	GdkRectangle image_rect, value_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	gtk_widget_style_get(widget, "slider-width", &slider_width, NULL);
	image_rect.width = gdk_pixbuf_get_width(pb) - slider_width;
	image_rect.height = gdk_pixbuf_get_height(pb);
	gdouble sliderstate = _gx_regler_get_step_pos(GX_REGLER(widget), image_rect.width-slider_width);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	hslider_expose(widget, &image_rect, sliderstate, pb, sat, TRUE, FALSE);
	g_object_unref(pb);
	return TRUE;
}

static gboolean gx_hslider_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_HSLIDER(widget));
	gint slider_width;
	GdkRectangle image_rect, value_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	gtk_widget_style_get(widget, "slider-width", &slider_width, NULL);
	image_rect.width = gdk_pixbuf_get_width(pb) - slider_width;
	image_rect.height = gdk_pixbuf_get_height(pb);
	gdouble sliderstate = _gx_regler_get_step_pos(GX_REGLER(widget), image_rect.width-slider_width);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	hslider_expose(widget, &image_rect, sliderstate, pb, sat, FALSE, FALSE);
	g_object_unref(pb);
	return TRUE;
}

static void slider_set_from_pointer(GtkWidget *widget, gdouble x)
{
	if (x <= 0) {
		return;
	}
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	gint slider_width;
	gtk_widget_style_get(widget, "slider-width", &slider_width, NULL);
	GdkRectangle image_rect;
	image_rect.width = gdk_pixbuf_get_width(pb) - slider_width;
	image_rect.height = gdk_pixbuf_get_height(pb);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, NULL);
	double pos = adj->lower + ((x - image_rect.x + widget->allocation.x)/image_rect.width)* (adj->upper - adj->lower);
	gtk_range_set_value(GTK_RANGE(widget), _gx_regler_get_value(adj,pos));
	g_object_unref(pb);
}

static gboolean gx_hslider_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_HSLIDER(widget));
	if (event->button == 3) {
		return GTK_WIDGET_CLASS(gx_hslider_parent_class)->button_press_event(widget, event);
	}
	if (event->button != 1) {
		return FALSE;
	}
	gtk_widget_grab_focus(widget);
	gtk_grab_add(widget);
	slider_set_from_pointer(widget, event->x);
	return FALSE;
}

static gboolean gx_hslider_pointer_motion(GtkWidget *widget, GdkEventMotion *event)
{
	g_assert(GX_IS_HSLIDER(widget));
	if (!GTK_WIDGET_HAS_GRAB(widget)) {
		return FALSE;
	}
	gdk_event_request_motions (event);
	slider_set_from_pointer(widget, event->x);
	return FALSE;
}

static void gx_hslider_init(GxHSlider *hslider)
{
}
