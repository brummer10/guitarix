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

#include "GxWheelVertical.h"

#define P_(s) (s)   // FIXME -> gettext

struct _GxWheelVerticalPrivate
{
    int last_x;
};

static gboolean gx_wheel_vertical_draw (GtkWidget *widget, cairo_t *cr);
static void gx_wheel_vertical_get_preferred_width (GtkWidget *widget, gint *min_width, gint *natural_width);
static void gx_wheel_vertical_get_preferred_height (GtkWidget *widget, gint *min_height, gint *natural_height);
static void gx_wheel_vertical_size_request (GtkWidget *widget, gint *width, gint *height);
static gboolean gx_wheel_vertical_button_press (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_wheel_vertical_pointer_motion (GtkWidget *widget, GdkEventMotion *event);

G_DEFINE_TYPE_WITH_PRIVATE(GxWheelVertical, gx_wheel_vertical, GX_TYPE_REGLER);

static void gx_wheel_vertical_class_init(GxWheelVerticalClass *klass)
{
    GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;

    widget_class->draw = gx_wheel_vertical_draw;
    widget_class->get_preferred_width = gx_wheel_vertical_get_preferred_width;
    widget_class->get_preferred_height = gx_wheel_vertical_get_preferred_height;
    widget_class->button_press_event = gx_wheel_vertical_button_press;
    widget_class->motion_notify_event = gx_wheel_vertical_pointer_motion;
    widget_class->enter_notify_event = NULL;
    widget_class->leave_notify_event = NULL;
    
    gtk_widget_class_install_style_property(
        widget_class,
        g_param_spec_int("framecount",
                        P_("framecount"),
                        P_("Number of frames in the animation specified by the gtkrc"),
                        -1, 250, -1,
                        GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
}

static void get_image_dimensions (GtkWidget *widget, GdkPixbuf *pb, 
                                        GdkRectangle *rect, gint *frame_count) 
{
    gtk_widget_style_get (widget, "framecount",
                            frame_count, NULL);

    rect->width  = gdk_pixbuf_get_width(pb);
    rect->height = (gdk_pixbuf_get_height(pb) / *frame_count);
}

static gboolean gx_wheel_vertical_draw (GtkWidget *widget, cairo_t *cr)
{
	g_assert(GX_IS_WHEEL_VERTICAL(widget));
	GxRegler *regler = GX_REGLER(widget);
	GdkRectangle image_rect, value_rect;
	gint fcount, findex;
	gdouble wheel_verticalstate;
	gtk_widget_style_get (widget, "framecount", &fcount, NULL);

	GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_vertical_back", GtkIconSize(-1), NULL);

	wheel_verticalstate = _gx_regler_get_step_pos(regler, 1);
	get_image_dimensions (widget, wb, &image_rect, &fcount);
	_gx_regler_get_positions(regler, &image_rect, &value_rect);

	fcount--; // zero based index
	findex = (int)(fcount * wheel_verticalstate);
	gdk_cairo_set_source_pixbuf (cr, wb, image_rect.x, image_rect.y - (image_rect.height * findex));
	cairo_rectangle(cr, image_rect.x, image_rect.y, image_rect.width, image_rect.height);
	cairo_fill(cr);
	_gx_regler_display_value(regler, cr, &value_rect);

	g_object_unref(wb);
	return TRUE;
}

static void gx_wheel_vertical_get_preferred_width (GtkWidget *widget, gint *min_width, gint *natural_width)
{
	gint width, height;
	gx_wheel_vertical_size_request(widget, &width, &height);

	if (min_width) {
		*min_width = width;
	}
	if (natural_width) {
		*natural_width = width;
	}
}

static void gx_wheel_vertical_get_preferred_height (GtkWidget *widget, gint *min_height, gint *natural_height)
{
	gint width, height;
	gx_wheel_vertical_size_request(widget, &width, &height);

	if (min_height) {
		*min_height = height;
	}
	if (natural_height) {
		*natural_height = height;
	}
}


static void gx_wheel_vertical_size_request (GtkWidget *widget, gint *width, gint *height)
{
    g_assert(GX_IS_WHEEL_VERTICAL(widget));
    gint fcount;
    GdkRectangle rect;

    GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_vertical_back", GtkIconSize(-1), NULL);

    get_image_dimensions (widget, wb, &rect, &fcount);
    *width = rect.width;
    *height = rect.height;
    _gx_regler_calc_size_request(GX_REGLER(widget), width, height);
    g_object_unref(wb);
}

static gboolean wheel_vertical_set_from_pointer(GtkWidget *widget, gdouble x, gdouble y, gboolean drag, int state, int button, GdkEventButton *event)
{
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
    GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_vertical_back", GtkIconSize(-1), NULL);
    GdkRectangle image_rect, value_rect;
    GxWheelVertical *wheel_vertical = GX_WHEEL_VERTICAL(widget);
    GxWheelVerticalPrivate *priv = wheel_vertical->priv;
    gint fcount;
    get_image_dimensions (widget, wb, &image_rect, &fcount); 
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    x += allocation.x;
    y += allocation.y;

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
            g_signal_emit_by_name(GX_REGLER(widget), "value-entry", rect, event, &ret);
            return FALSE;
        }
    }

    double value;
    gdouble lower = gtk_adjustment_get_lower(adj);
    gdouble upper = gtk_adjustment_get_upper(adj);
    gdouble adj_value = gtk_adjustment_get_value(adj);
    if (!drag) {
        priv->last_x = y;
	if (event && event->type == GDK_2BUTTON_PRESS) {
	    const int frame = 5;
	    value = lower + ((y - (image_rect.y+frame)) * (upper - lower)) / (image_rect.height-2*frame);
	    gtk_range_set_value(GTK_RANGE(widget), value);
	}
        return TRUE;
    }
    int mode = ((state & GDK_CONTROL_MASK) == 0);
    const double scaling = 0.01;
    double scal = (mode ? scaling : scaling*0.1);
    value = adj_value + (((y - priv->last_x) * scal) * (upper - lower));
    priv->last_x = y;
    if (adj_value != value)
        gtk_range_set_value(GTK_RANGE(widget), value);
    g_object_unref(wb);
    return TRUE;
}

static gboolean gx_wheel_vertical_button_press (GtkWidget *widget, GdkEventButton *event)
{
    g_assert(GX_IS_WHEEL_VERTICAL(widget));
    if (event->button != 1 && event->button != 3) {
        return FALSE;
    }
    gtk_widget_grab_focus(widget);
    if (wheel_vertical_set_from_pointer(widget, event->x, event->y, FALSE, event->state, event->button, event)) {
        gtk_grab_add(widget);
    }
    return FALSE;
}

/****************************************************************
 ** set the value from mouse movement
 */

static gboolean gx_wheel_vertical_pointer_motion (GtkWidget *widget, GdkEventMotion *event)
{
    g_assert(GX_IS_WHEEL_VERTICAL(widget));
    gdk_event_request_motions (event);
    if (!gtk_widget_has_grab(widget)) {
        return FALSE;
    }
    wheel_vertical_set_from_pointer(widget, event->x, event->y, TRUE, event->state, 0, NULL);
    return FALSE;
}

static void gx_wheel_vertical_init(GxWheelVertical *wheel_vertical)
{
    wheel_vertical->priv = G_TYPE_INSTANCE_GET_PRIVATE(wheel_vertical, GX_TYPE_WHEEL_VERTICAL, GxWheelVerticalPrivate);
}
