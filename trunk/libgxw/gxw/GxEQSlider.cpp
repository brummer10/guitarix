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

#include "GxEQSlider.h"
#include <gtk/gtkmain.h>
#include <gtk/gtkprivate.h>

#define P_(s) (s)   // FIXME -> gettext

#define get_stock_id(widget) (GX_EQ_SLIDER_CLASS(GTK_OBJECT_GET_CLASS(widget))->parent_class.stock_id)

static gboolean gx_eq_slider_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_eq_slider_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_eq_slider_button_press (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_eq_slider_pointer_motion (GtkWidget *widget, GdkEventMotion *event);

G_DEFINE_TYPE(GxEQSlider, gx_eq_slider, GX_TYPE_VSLIDER);

static void gx_eq_slider_class_init(GxEQSliderClass *klass)
{
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;

	widget_class->expose_event = gx_eq_slider_expose;
	widget_class->size_request = gx_eq_slider_size_request;
	widget_class->button_press_event = gx_eq_slider_button_press;
	widget_class->motion_notify_event = gx_eq_slider_pointer_motion;
	widget_class->enter_notify_event = NULL;
	widget_class->leave_notify_event = NULL;
	klass->parent_class.stock_id = "eqslider";
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("slider-width",P_("size of slider"),
		                   P_("Height of movable part of vslider"),
		                 0, 100, 5, GParamFlags(GTK_PARAM_READABLE)));
}

static void gx_eq_slider_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_EQ_SLIDER(widget));
	gint slider_height;
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	requisition->width = gdk_pixbuf_get_width(pb);
	requisition->height = (gdk_pixbuf_get_height(pb) + slider_height) / 2;
	_gx_regler_calc_size_request(GX_REGLER(widget), requisition);
	g_object_unref(pb);
}

static void eq_slider_expose(
	GtkWidget *widget, GdkRectangle *rect, gdouble sliderstate, GdkPixbuf *image)
{
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                image, 0, (gint)sliderstate, rect->x, rect->y,
	                rect->width, rect->height, GDK_RGB_DITHER_NORMAL, 0, 0);
}

static gboolean gx_eq_slider_expose(GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_EQ_SLIDER(widget));
	gint slider_height;
	GdkRectangle image_rect, value_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	image_rect.width = gdk_pixbuf_get_width(pb);
	image_rect.height = (gdk_pixbuf_get_height(pb) + slider_height) / 2;
	gdouble sliderstate = _gx_regler_get_step_pos(GX_REGLER(widget), image_rect.height-slider_height);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	eq_slider_expose(widget, &image_rect, sliderstate, pb);
	_gx_regler_simple_display_value(GX_REGLER(widget), &value_rect);
	g_object_unref(pb);
	return FALSE;
}

static gboolean slider_set_from_pointer(GtkWidget *widget, int state, gdouble x, gdouble y, gboolean drag, gint button, GdkEventButton *event)
{
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	gint slider_height;
	GdkRectangle image_rect, value_rect;
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	image_rect.width = gdk_pixbuf_get_width(pb);
	image_rect.height = (gdk_pixbuf_get_height(pb) + slider_height) / 2;
	x += widget->allocation.x;
	y += widget->allocation.y;
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	if (!drag && !_approx_in_rectangle(x, y, &image_rect)) {
		return FALSE;
	}
	if (button == 3) {
		gboolean ret;
		g_signal_emit_by_name(GX_REGLER(widget), "value-entry", &image_rect, event, &ret);
		return FALSE;
	}
    static double last_y = 2e20;
    
	double slidery = image_rect.height;
	double posy = slidery - y + image_rect.y; 
	double value;
	if (!drag) {
		last_y = posy;
		return TRUE;
	}
    double sc = 0.02;
    if (state & GDK_CONTROL_MASK) {
        sc = 0.002;
    }
	value = (posy - last_y) * sc;
	last_y = posy;
	gtk_range_set_value(GTK_RANGE(widget), adj->value + value * (adj->upper - adj->lower));
	g_object_unref(pb);
	return TRUE;
}

static gboolean gx_eq_slider_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_EQ_SLIDER(widget));
	if (event->button != 1 && event->button != 3) {
		return FALSE;
	}
	gtk_widget_grab_focus(widget);
	if (slider_set_from_pointer(widget, event->state, event->x, event->y, FALSE, event->button, event)) {
		gtk_grab_add(widget);
	}
	return FALSE;
}

static gboolean gx_eq_slider_pointer_motion(GtkWidget *widget, GdkEventMotion *event)
{
	g_assert(GX_IS_EQ_SLIDER(widget));
	if (!gtk_widget_has_grab(widget)) {
		return FALSE;
	}
	gdk_event_request_motions (event);
	slider_set_from_pointer(widget, event->state, event->x, event->y, TRUE, 0, NULL);
	return FALSE;
}


static void gx_eq_slider_init(GxEQSlider *eq_slider)
{
	gtk_widget_set_name (GTK_WIDGET(eq_slider),"rack_slider");
}
