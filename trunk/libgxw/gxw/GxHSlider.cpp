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

#include "GxHSlider.h"

#define P_(s) (s)   // FIXME -> gettext

static gboolean gx_hslider_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_hslider_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_hslider_button_press (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_hslider_button_release (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_hslider_pointer_motion (GtkWidget *widget, GdkEventMotion *event);
static gboolean gx_hslider_enter_in (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_hslider_leave_out (GtkWidget *widget, GdkEventCrossing *event);
static void gx_hslider_set_pointer (GtkWidget *widget, GdkEventMotion *event);
static void gx_hslider_render_pixbuf (GtkWidget *widget);

G_DEFINE_TYPE(GxHSlider, gx_hslider, GX_TYPE_REGLER);

#define get_stock_id(widget) (GX_HSLIDER_CLASS(GTK_OBJECT_GET_CLASS(widget))->stock_id)
#define get_mouse_scale_factor(widget) (GX_HSLIDER_CLASS(GTK_OBJECT_GET_CLASS(widget))->mouse_scale_factor)

static void gx_hslider_class_init(GxHSliderClass *klass)
{
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;

	widget_class->expose_event = gx_hslider_expose;
	widget_class->size_request = gx_hslider_size_request;
	widget_class->button_press_event   = gx_hslider_button_press;
    widget_class->button_release_event = gx_hslider_button_release;
	widget_class->motion_notify_event  = gx_hslider_pointer_motion;
	widget_class->enter_notify_event   = gx_hslider_enter_in;
	widget_class->leave_notify_event   = gx_hslider_leave_out;
	klass->stock_id = "hslider";
	klass->mouse_scale_factor = 1.0;
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("slider-width",P_("size of slider"),
		                   P_("Width of movable part of vslider"),
		                 0, 100, 20, GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
}

static void gx_hslider_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_HSLIDER(widget));
    GxHSlider *slider   = GX_HSLIDER(widget);
	requisition->width  = slider->width;
	requisition->height = slider->height;
	_gx_regler_calc_size_request(GX_REGLER(widget), requisition);
}

static gboolean gx_hslider_expose(GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_HSLIDER(widget));
    GxHSlider *slider = GX_HSLIDER(widget);
    int x = widget->allocation.x;
    int y = widget->allocation.y;
    slider->image_rect.x = slider->image_rect.y = 0;
    gdouble slstate = _gx_regler_get_step_pos(GX_REGLER(widget), slider->width - slider->slider_width);
	if (gtk_widget_has_focus(widget)) {
        gtk_paint_focus(widget->style, widget->window, GTK_STATE_NORMAL, NULL, widget, NULL,
                        x, y, slider->width, slider->height);
	}
	cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(widget));
    // background
	gdk_cairo_set_source_pixbuf (cr, slider->image, x, y);
	cairo_rectangle(cr, x, y, slider->width, slider->height);
	cairo_fill(cr);
    //slider
    int sx = gtk_widget_get_state(widget) ? slider->slider_width : 0;
    gdk_cairo_set_source_pixbuf (cr, slider->image, x - (slider->width - slstate) - sx, y);
    cairo_rectangle(cr, x + slstate, y, slider->slider_width, slider->height);
    cairo_fill(cr);
	cairo_destroy (cr);
	return FALSE;
}

static gboolean gx_hslider_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
    if (gtk_widget_get_state(widget) == GTK_STATE_NORMAL)
        gtk_widget_set_state(widget, GTK_STATE_PRELIGHT);
    GX_HSLIDER(widget)->hover = 1;
    gx_hslider_set_pointer(widget, NULL);
	return TRUE;
}

static gboolean gx_hslider_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
    if (gtk_widget_get_state(widget) == GTK_STATE_PRELIGHT)
        gtk_widget_set_state(widget, GTK_STATE_NORMAL);
    GX_HSLIDER(widget)->hover = 0;
    gx_hslider_set_pointer(widget, NULL);
	return TRUE;
}

static gboolean slider_set_from_pointer(GtkWidget *widget, int state, gdouble x, gdouble y, gboolean drag, gint button, GdkEventButton *event)
{
    GxHSlider *slider = GX_HSLIDER(widget);
	GdkRectangle value_rect;
    slider->image_rect.x = slider->image_rect.y = 0;
    _gx_regler_get_positions(GX_REGLER(widget), &slider->image_rect, &value_rect);
	x += widget->allocation.x;
	y += widget->allocation.y;
	if (!drag) {
		if (_gx_regler_check_display_popup(GX_REGLER(widget), &slider->image_rect, &value_rect, event)) {
			return FALSE;
		}
	}
	gint off =  slider->image_rect.x + slider->slider_width/2;
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
    static double last_x = 2e20;
	if (!drag) {
		last_x = x;
		if (event && event->type == GDK_2BUTTON_PRESS) {
		    double value = adj->lower + ((x - off) / slider->width) * (adj->upper - adj->lower);
		    gtk_range_set_value(GTK_RANGE(widget), value);
		}
	} else {
		double value = ((x - last_x) / slider->width) * (adj->upper - adj->lower);
		value *= get_mouse_scale_factor(widget);
		if (state & (GDK_CONTROL_MASK|GDK_SHIFT_MASK)) {
			value *= 0.1;
		}
		last_x = x;
		gtk_range_set_value(GTK_RANGE(widget), adj->value + value);
	}
	return TRUE;
}

static gboolean gx_hslider_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_HSLIDER(widget));
	if (event->button != 1 && event->button != 3) {
		return FALSE;
	}
	gtk_widget_grab_focus(widget);
	if (slider_set_from_pointer(widget, event->state, event->x, event->y, FALSE, event->button, event)) {
		gtk_grab_add(widget);
        gtk_widget_set_state(widget, GTK_STATE_ACTIVE);
        gx_hslider_set_pointer(widget, NULL);
	}
	return FALSE;
}

static gboolean gx_hslider_button_release (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_HSLIDER(widget));
	if (event->button != 1 && event->button != 3) {
		return FALSE;
	}
    gtk_grab_remove(widget);
    gtk_widget_set_state(widget, GX_HSLIDER(widget)->hover ? GTK_STATE_PRELIGHT : GTK_STATE_NORMAL);
	return TRUE;
}

static gboolean gx_hslider_pointer_motion(GtkWidget *widget, GdkEventMotion *event)
{
    g_assert(GX_IS_HSLIDER(widget));
    gx_hslider_set_pointer(widget, event);
	if (!gtk_widget_has_grab(widget))
		return FALSE;
	gdk_event_request_motions (event);
	slider_set_from_pointer(widget, event->state, event->x, event->y, TRUE, 0, NULL);
	return FALSE;
}

static void gx_hslider_init(GxHSlider *hslider)
{
    GtkWidget *widget = GTK_WIDGET(hslider);
    hslider->hover        = 0;
    gx_hslider_render_pixbuf(widget);
    g_signal_connect ( GTK_OBJECT (widget), "style-set",
                     G_CALLBACK (gx_hslider_render_pixbuf), NULL);
}

static void gx_hslider_set_pointer (GtkWidget *widget, GdkEventMotion *event)
{
    GxHSlider *slider = GX_HSLIDER(widget);
    GdkCursor *cur = gdk_cursor_new(GDK_HAND2);
    gdouble slstate = _gx_regler_get_step_pos(GX_REGLER(widget), slider->width - slider->slider_width);
    if (gtk_widget_get_state(widget) == GTK_STATE_ACTIVE
    or (event and event->x > slstate and event->x < slstate + slider->slider_width))
        gdk_window_set_cursor(GDK_WINDOW(gtk_widget_get_window(widget)), cur);
    else
        gdk_window_set_cursor(GDK_WINDOW(gtk_widget_get_window(widget)), NULL);
}

static void gx_hslider_render_pixbuf (GtkWidget *widget)
{
    GxHSlider *hslider = GX_HSLIDER(widget);
    gtk_widget_style_get(widget, "slider-width", &hslider->slider_width, NULL);
    hslider->image        = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
    hslider->width        = gdk_pixbuf_get_width(hslider->image) - hslider->slider_width * 2;
    hslider->height       = gdk_pixbuf_get_height(hslider->image);
    GdkRectangle rect;
    rect.width  = hslider->width;
    rect.height = hslider->height;
    hslider->image_rect = rect;
}
