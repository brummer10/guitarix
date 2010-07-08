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

#include "GxVSlider.h"
#include <gtk/gtkmain.h>

#define P_(s) (s)   // FIXME -> gettext

static gboolean gx_vslider_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_vslider_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_vslider_button_press (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_vslider_pointer_motion (GtkWidget *widget, GdkEventMotion *event);
static gboolean gx_vslider_enter_in (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_vslider_leave_out (GtkWidget *widget, GdkEventCrossing *event);

G_DEFINE_TYPE(GxVSlider, gx_vslider, GX_TYPE_REGLER);

#define get_stock_id(widget) (GX_VSLIDER_CLASS(GTK_OBJECT_GET_CLASS(widget))->stock_id)

static void gx_vslider_class_init(GxVSliderClass *klass)
{
	GtkWidgetClass *widget_class = (GtkWidgetClass*)klass;

	widget_class->expose_event = gx_vslider_expose;
	widget_class->size_request = gx_vslider_size_request;
	widget_class->button_press_event = gx_vslider_button_press;
	widget_class->motion_notify_event = gx_vslider_pointer_motion;
	widget_class->enter_notify_event = gx_vslider_enter_in;
	widget_class->leave_notify_event = gx_vslider_leave_out;
	klass->stock_id = "vslider";
}

static void gx_vslider_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_VSLIDER(widget));
	gint slider_height;
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	requisition->width = gdk_pixbuf_get_width(pb);
	requisition->height = gdk_pixbuf_get_height(pb) - slider_height;
	_gx_regler_calc_size_request(GX_REGLER(widget), requisition);
	g_object_unref(pb);
}

static void vslider_expose(
	GtkWidget *widget, GdkRectangle *rect, gdouble sliderstate, GdkPixbuf *image,
	gdouble sat, gboolean has_focus, gboolean paint_focus)
{
	gint slider_height;
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	GdkPixbuf *image1 = gdk_pixbuf_copy(image);
	gdk_pixbuf_copy_area(image, 0, rect->height, rect->width, slider_height,
	                     image1, 0, rect->height-sliderstate-slider_height);
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

static gboolean gx_vslider_expose(GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_VSLIDER(widget));
	gint slider_height;
	GdkRectangle image_rect, value_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	image_rect.width = gdk_pixbuf_get_width(pb);
	image_rect.height = gdk_pixbuf_get_height(pb) - slider_height;
	gdouble sliderstate = _gx_regler_get_step_pos(GX_REGLER(widget), image_rect.height-slider_height);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	vslider_expose(widget, &image_rect, sliderstate, pb, sat, GTK_WIDGET_HAS_FOCUS(widget), TRUE);
	_gx_regler_display_value(GX_REGLER(widget), &value_rect);
	g_object_unref(pb);
	return FALSE;
}

static gboolean gx_vslider_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_VSLIDER(widget));
	gint slider_height;
	GdkRectangle image_rect, value_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	image_rect.width = gdk_pixbuf_get_width(pb);
	image_rect.height = gdk_pixbuf_get_height(pb) - slider_height;
	gdouble sliderstate = _gx_regler_get_step_pos(GX_REGLER(widget), image_rect.height-slider_height);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	vslider_expose(widget, &image_rect, sliderstate, pb, sat, TRUE, FALSE);
	g_object_unref(pb);
	return TRUE;
}

static gboolean gx_vslider_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_VSLIDER(widget));
	gint slider_height;
	GdkRectangle image_rect, value_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	image_rect.width = gdk_pixbuf_get_width(pb);
	image_rect.height = gdk_pixbuf_get_height(pb) - slider_height;
	gdouble sliderstate = _gx_regler_get_step_pos(GX_REGLER(widget), image_rect.height-slider_height);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	vslider_expose(widget, &image_rect, sliderstate, pb, sat, FALSE, FALSE);
	g_object_unref(pb);
	return TRUE;
}

static void slider_set_from_pointer(GtkWidget *widget, gdouble y)
{
	if (y <= 0) {
		return;
	}
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	gint slider_height;
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	GdkRectangle image_rect;
	image_rect.width = gdk_pixbuf_get_width(pb);
	image_rect.height = gdk_pixbuf_get_height(pb) - slider_height;
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, NULL);
	gint height = image_rect.height - slider_height;
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	double pos = adj->upper - ((y - image_rect.y + widget->allocation.y - slider_height/2)/height)* (adj->upper - adj->lower);
	gtk_range_set_value(GTK_RANGE(widget), _gx_regler_get_value(adj,pos));
	g_object_unref(pb);
}

static gboolean gx_vslider_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_VSLIDER(widget));
	if (event->button == 3) {
		return GTK_WIDGET_CLASS(gx_vslider_parent_class)->button_press_event(widget, event);
	}
	if (event->button != 1) {
		return FALSE;
	}
	gtk_widget_grab_focus(widget);
	gtk_grab_add(widget);
	slider_set_from_pointer(widget, event->y);
	return FALSE;
}

static gboolean gx_vslider_pointer_motion(GtkWidget *widget, GdkEventMotion *event)
{
	g_assert(GX_IS_VSLIDER(widget));
	if (!GTK_WIDGET_HAS_GRAB(widget)) {
		return FALSE;
	}
	gdk_event_request_motions (event);
	slider_set_from_pointer(widget, event->y);
	return FALSE;
}

static void gx_vslider_init(GxVSlider *vslider)
{
}
