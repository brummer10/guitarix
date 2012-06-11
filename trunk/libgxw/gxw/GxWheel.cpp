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

#include "GxWheel.h"

#define P_(s) (s)   // FIXME -> gettext

struct _GxWheelPrivate
{
	int last_x;
};

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
	
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("framecount",
		                P_("framecount"),
		                P_("Number of frames in the animation specified by the gtkrc"),
		                -1, 250, -1,
		                GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	g_type_class_add_private(klass, sizeof (GxWheelPrivate));	                
}

static void get_image_dimensions (GtkWidget *widget, GdkPixbuf *pb, 
										GdkRectangle *rect, gint *frame_count) 
{
	gtk_widget_style_get (widget, "framecount",
							frame_count, NULL);
	
	rect->width  = gdk_pixbuf_get_width(pb);
	rect->height = gdk_pixbuf_get_height(pb);
	
	if (*frame_count >1)
		rect->width = (rect->width / *frame_count);
	if (*frame_count == 0) {// rc directs to assume square frames
		*frame_count = rect->width / rect->height;
		rect->width = rect->height;
		
	}
}

static gboolean gx_wheel_expose (GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_WHEEL(widget));
	GxRegler *regler = GX_REGLER(widget);
	GdkRectangle image_rect, value_rect;
    gint fcount, findex;
    gdouble wheelstate;
	gtk_widget_style_get (widget, "framecount", &fcount, NULL);
	
	GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_back", GtkIconSize(-1), NULL);
	if (fcount > -1) {
		
		wheelstate = _gx_regler_get_step_pos(regler, 1);
		get_image_dimensions (widget, wb, &image_rect, &fcount);
		_gx_regler_get_positions(regler, &image_rect, &value_rect);
		
		fcount--; // zero based index
		findex = (int)(fcount * wheelstate);
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                wb, (image_rect.width * findex),0, image_rect.x, image_rect.y,
	                image_rect.width, image_rect.height, GDK_RGB_DITHER_NORMAL, 0, 0);		
	    _gx_regler_display_value(regler, &value_rect);
	} else {
		
	GdkPixbuf *ws = gtk_widget_render_icon(widget, "wheel_fringe", GtkIconSize(-1), NULL);
	GdkPixbuf *wp = gtk_widget_render_icon(widget, "wheel_pointer", GtkIconSize(-1), NULL);

    image_rect.width = gdk_pixbuf_get_width(wb);
    image_rect.height = gdk_pixbuf_get_height(wb);

	gint step = gdk_pixbuf_get_width(ws) / 2;
	wheelstate = _gx_regler_get_step_pos(regler, step);
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
	
	g_object_unref(ws);
	g_object_unref(wp);
    }
    g_object_unref(wb);
	return TRUE;
}

static void gx_wheel_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_WHEEL(widget));
	gint fcount;
	GdkRectangle rect;
	
    GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_back", GtkIconSize(-1), NULL);
		
    get_image_dimensions (widget, wb, &rect, &fcount); 
    requisition->width = rect.width;
    requisition->height = rect.height;
	_gx_regler_calc_size_request(GX_REGLER(widget), requisition);
	g_object_unref(wb);
}

static gboolean wheel_set_from_pointer(GtkWidget *widget, gdouble x, gdouble y, gboolean drag, int state, int button, GdkEventButton *event)
{
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	GdkPixbuf *wb = gtk_widget_render_icon(widget, "wheel_back", GtkIconSize(-1), NULL);
	GdkRectangle image_rect, value_rect;
	GxWheel *wheel = GX_WHEEL(widget);
	GxWheelPrivate *priv = wheel->priv;
	gint fcount;
	get_image_dimensions (widget, wb, &image_rect, &fcount); 
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
			g_signal_emit_by_name(GX_REGLER(widget), "value-entry", rect, event, &ret);
			return FALSE;
		}
	}

	double value;
	if (!drag) {
		priv->last_x = x;
		if (event && event->type == GDK_2BUTTON_PRESS) {
		    const int frame = 5;
		    value = adj->lower + ((x - (image_rect.x+frame)) * (adj->upper - adj->lower)) / (image_rect.width-2*frame);
		    gtk_range_set_value(GTK_RANGE(widget), value);
		}
		return TRUE;
	}
	int mode = ((state & GDK_CONTROL_MASK) == 0);
	const double scaling = 0.01;
	double scal = (mode ? scaling : scaling*0.1);
	value = adj->value + (((x - priv->last_x) * scal) * (adj->upper - adj->lower));
	priv->last_x = x;
	if (adj->value != value) 
		gtk_range_set_value(GTK_RANGE(widget), value);
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
	if (wheel_set_from_pointer(widget, event->x, event->y, FALSE, event->state, event->button, event)) {
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
	wheel_set_from_pointer(widget, event->x, event->y, TRUE, event->state, 0, NULL);
	return FALSE;
}

static void gx_wheel_init(GxWheel *wheel)
{
	wheel->priv = G_TYPE_INSTANCE_GET_PRIVATE(wheel, GX_TYPE_WHEEL, GxWheelPrivate);
}
