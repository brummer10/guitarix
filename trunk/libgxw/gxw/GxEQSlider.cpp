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

#define P_(s) (s)   // FIXME -> gettext

#define get_stock_id(widget) (GX_EQ_SLIDER_CLASS(GTK_WIDGET_GET_CLASS(widget))->parent_class.stock_id)

static gboolean gx_eq_slider_draw (GtkWidget *widget, cairo_t *cr);
static void gx_eq_slider_get_preferred_width (GtkWidget *widget, gint *min_width, gint *natural_width);
static void gx_eq_slider_get_preferred_height (GtkWidget *widget, gint *min_height, gint *natural_height);
static void gx_eq_slider_size_request (GtkWidget *widget, gint *width, gint *height);
static gboolean gx_eq_slider_button_press (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_eq_slider_pointer_motion (GtkWidget *widget, GdkEventMotion *event);

G_DEFINE_TYPE(GxEQSlider, gx_eq_slider, GX_TYPE_VSLIDER);

static void gx_eq_slider_class_init(GxEQSliderClass *klass)
{
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;

	widget_class->draw = gx_eq_slider_draw;
	widget_class->get_preferred_width = gx_eq_slider_get_preferred_width;
	widget_class->get_preferred_height = gx_eq_slider_get_preferred_height;
	widget_class->button_press_event = gx_eq_slider_button_press;
	widget_class->motion_notify_event = gx_eq_slider_pointer_motion;
	widget_class->enter_notify_event = NULL;
	widget_class->leave_notify_event = NULL;
	klass->parent_class.stock_id = "eqslider";
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("slider-width",P_("size of slider"),
				 P_("Height of movable part of vslider"),
		                 0, 100, 5, GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
}

static void gx_eq_slider_get_preferred_width (GtkWidget *widget, gint *min_width, gint *natural_width)
{
	gint width, height;
	gx_eq_slider_size_request(widget, &width, &height);

	if (min_width) {
		*min_width = width;
	}
	if (natural_width) {
		*natural_width = width;
	}
}

static void gx_eq_slider_get_preferred_height (GtkWidget *widget, gint *min_height, gint *natural_height)
{
	gint width, height;
	gx_eq_slider_size_request(widget, &width, &height);

	if (min_height) {
		*min_height = height;
	}
	if (natural_height) {
		*natural_height = height;
	}
}

static void gx_eq_slider_size_request (GtkWidget *widget, gint *width, gint *height)
{
	g_assert(GX_IS_EQ_SLIDER(widget));
	gint slider_height;
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	if (GDK_IS_PIXBUF(pb)) {
		*width = gdk_pixbuf_get_width(pb);
		*height = (gdk_pixbuf_get_height(pb) + slider_height) / 2;
		g_object_unref(pb);
	} else {
		g_warning("EQSlider icon is NULL");
		*width = 0;
		*height = slider_height / 2;
	}
	_gx_regler_calc_size_request(GX_REGLER(widget), width, height);
}

static void eq_slider_expose(
	cairo_t *cr, GdkRectangle *rect, gdouble sliderstate, GdkPixbuf *image)
{
	gdk_cairo_set_source_pixbuf (cr, image, rect->x, rect->y - (gint)sliderstate);
	cairo_rectangle(cr, rect->x, rect->y, rect->width, rect->height);
	cairo_fill(cr);
}

static gboolean gx_eq_slider_draw(GtkWidget *widget, cairo_t *cr)
{
	g_assert(GX_IS_EQ_SLIDER(widget));
	gint slider_height;
	GdkRectangle image_rect, value_rect;
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	if (GDK_IS_PIXBUF(pb)) {
		image_rect.width = gdk_pixbuf_get_width(pb);
		image_rect.height = (gdk_pixbuf_get_height(pb) + slider_height) / 2;
		gdouble sliderstate = _gx_regler_get_step_pos(GX_REGLER(widget), image_rect.height-slider_height);
		_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
		eq_slider_expose(cr, &image_rect, sliderstate, pb);
		_gx_regler_simple_display_value(GX_REGLER(widget), cr, &value_rect);
		g_object_unref(pb);
	} else {
		g_warning("EQSlider icon is NULL");
	}
	return FALSE;
}

static inline void get_width_height(GtkWidget *widget, GdkRectangle *r)
{
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	if (GDK_IS_PIXBUF(pb)) {
		r->width = gdk_pixbuf_get_width(pb);
		r->height = gdk_pixbuf_get_height(pb);
		g_object_unref(pb);
	} else {
		r->width = r->height = 0;
	}
}

static gboolean slider_set_from_pointer(GtkWidget *widget, int state, gdouble x, gdouble y, gboolean drag, gint button, GdkEventButton *event)
{
	gint slider_height;
	GdkRectangle image_rect, value_rect;
	gtk_widget_style_get(widget, "slider-width", &slider_height, NULL);
	get_width_height(widget, &image_rect);
	image_rect.height = (image_rect.height + slider_height) / 2;
	GtkAllocation allocation;
	gtk_widget_get_allocation(widget, &allocation);
	x += allocation.x;
	y += allocation.y;
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	if (!drag) {
		if (_gx_regler_check_display_popup(GX_REGLER(widget), &image_rect, &value_rect, event)) {
			return FALSE;
		}
	}
	gint height = image_rect.height - slider_height;
	gint off =  image_rect.y + slider_height/2;
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	gdouble upper = gtk_adjustment_get_upper(adj);
	gdouble lower = gtk_adjustment_get_lower(adj);
	static double last_y = 2e20;
	if (!drag) {
		last_y = y;
		if (event && event->type == GDK_2BUTTON_PRESS) {
		    double value = upper - ((y-off) / height) * (upper - lower);
			gtk_range_set_value(GTK_RANGE(widget), value);
		}
	} else {
		double value = ((last_y - y) / height) * (upper - lower);
		if (state & (GDK_CONTROL_MASK|GDK_SHIFT_MASK)) {
			value *= 0.1;
		}
		last_y = y;
		gtk_range_set_value(GTK_RANGE(widget), gtk_adjustment_get_value(adj) + value);
	}
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
