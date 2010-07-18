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

#include "GxKnob.h"
#include <gtk/gtkprivate.h>
#include <gtk/gtkmain.h>
#include <cmath>

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x, y) ((x) < (y) ? (y) : (x))
#endif

#define P_(s) (s)   // FIXME -> gettext

#define GX_KNOB_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), GX_TYPE_KNOB, GxKnobPrivate))

typedef struct
{
	gint last_quadrant;
} GxKnobPrivate;

static gboolean gx_knob_pointer_motion(GtkWidget *widget, GdkEventMotion *event);
static gboolean gx_knob_enter_in(GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_knob_leave_out(GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_knob_expose(GtkWidget *widget, GdkEventExpose *event);
static void gx_knob_size_request(GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_knob_button_press(GtkWidget *widget, GdkEventButton *event);


G_DEFINE_ABSTRACT_TYPE(GxKnob, gx_knob, GX_TYPE_REGLER);

#define get_stock_id(widget) (GX_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget))->stock_id)

static void gx_knob_class_init(GxKnobClass *klass)
{
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;
	klass->jump_to_mouse = TRUE;
	widget_class->motion_notify_event = gx_knob_pointer_motion;
	widget_class->enter_notify_event = gx_knob_enter_in;
	widget_class->leave_notify_event = gx_knob_leave_out;
	widget_class->expose_event = gx_knob_expose;
	widget_class->size_request = gx_knob_size_request;
	widget_class->button_press_event = gx_knob_button_press;

	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("arc-inset",P_("inset of arch"),
		                   P_("Inset of the arc around the knob"),
		                 0, 100, 2, GParamFlags(GTK_PARAM_READABLE)));

	g_type_class_add_private(klass, sizeof (GxKnobPrivate));
}

static void gx_knob_init(GxKnob *knob)
{
}

void _gx_knob_draw_arc(GtkWidget *widget, GdkRectangle *rect, gdouble knobstate, gboolean has_focus)
{
	GdkGC *line = gdk_gc_new(GDK_DRAWABLE(widget->window));
	GdkColor color;
	int arc_offset;
	gtk_widget_style_get(widget, "arc-inset", &arc_offset, NULL);

	if (has_focus) {
		// linear color change in RGB space from (52480, 0, 5120) to (8448, 46004, 5120)
		color.red = 52480 - (int)(44032 * knobstate);
		color.green = (int)(46004 * knobstate);
		color.blue = 5120;
	} else {
		color.red = 5120;
		color.green = 742;
		color.blue = 52480;
	}
	gdk_gc_set_rgb_fg_color(line, &color);
	gdk_gc_set_line_attributes(line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
	gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,
	             rect->x+arc_offset, rect->y+arc_offset,
	             rect->width-1-2*arc_offset, rect->height-1-2*arc_offset,-90*64,360*64);
	g_object_unref(line);
}

static const double scale_zero = 20 * (M_PI/180); // defines "dead zone" for knobs

void _gx_knob_expose(GtkWidget *widget, GdkRectangle *image_rect, gdouble knobstate,
                     GdkPixbuf *knob_image)
{
	double angle = scale_zero + knobstate * 2 * (M_PI - scale_zero);
	const double pointer_off = 5;
	double radius = min(image_rect->width-pointer_off, image_rect->height-pointer_off) / 2;
	double lengh_x = (image_rect->x+radius+pointer_off/2) - radius * sin(angle);
	double lengh_y = (image_rect->y+radius+pointer_off/2) + radius * cos(angle);
	double radius1 = min(image_rect->width, image_rect->height) / 2;
	int has_focus = gtk_widget_has_focus(widget);

	if (has_focus) {
		gtk_paint_focus(widget->style, widget->window, GTK_STATE_NORMAL, NULL, widget, NULL,
		                image_rect->x, image_rect->y, image_rect->width, image_rect->height);
	}
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                knob_image, 0,0, image_rect->x, image_rect->y,
	                image_rect->width, image_rect->height, GDK_RGB_DITHER_NORMAL, 0, 0);

	/** this is to create a pointer rotating on the knob with painting funktions **/
	cairo_t *cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));
	cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
	cairo_set_line_width(cr, 5.0);
	cairo_move_to(cr, image_rect->x+radius1, image_rect->y+radius1);
	cairo_line_to(cr,lengh_x,lengh_y);
	cairo_stroke(cr);
	cairo_set_source_rgb(cr,  0.9, 0.9, 0.9);
	cairo_set_line_width(cr, 1.0);
	cairo_move_to(cr, image_rect->x+radius1, image_rect->y+radius1);
	cairo_line_to(cr,lengh_x,lengh_y);
	cairo_stroke(cr);
	cairo_destroy(cr);

	_gx_knob_draw_arc(widget, image_rect, knobstate, has_focus);
}

gboolean _approx_in_rectangle(gdouble x, gdouble y, GdkRectangle *rect)
{
	const int off = 5;
	if (x >= rect->x-off && x < rect->x + rect->width + off &&
	    y >= rect->y-off && y < rect->y + rect->height + off) {
		return TRUE;
	}
	return FALSE;
}

gboolean _gx_knob_pointer_event(GtkWidget *widget, gdouble x, gdouble y, const gchar *icon,
                                gboolean drag, int state, int button)
{
	int linearmode = ((state & GDK_CONTROL_MASK) == 0) ^ GX_KNOB_CLASS(GTK_OBJECT_GET_CLASS(widget))->jump_to_mouse;
	GdkRectangle image_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, icon, GtkIconSize(-1), NULL);
	image_rect.width = gdk_pixbuf_get_width(pb);
	image_rect.height = gdk_pixbuf_get_height(pb);
	g_object_unref(pb);
	x += widget->allocation.x;
	y += widget->allocation.y;
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, NULL);
	if (!drag && !_approx_in_rectangle(x, y, &image_rect)) {
		return FALSE;
	}
	if (button == 3) {
		gboolean ret;
		g_signal_emit_by_name(GX_REGLER(widget), "value-entry", &image_rect, &ret);
		return FALSE;
	}
	static double last_y = 2e20;
	GxKnob *knob = GX_KNOB(widget);
	GxKnobPrivate *priv = GX_KNOB_GET_PRIVATE(knob);
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	double radius =  min(image_rect.width, image_rect.height) / 2;
	double posx = radius - x + image_rect.x; // x axis right -> left
	double posy = radius - y + image_rect.y; // y axis top -> bottom
	double value;
	if (!drag) {
		if (linearmode) {
			last_y = posy;
			return TRUE;
		} else {
			last_y = 2e20;
		}
	}
	if (last_y < 1e20) { // in drag started in linear mode
		const double scaling = 0.005;
		double scal = (linearmode ? scaling : scaling*0.1);
		value = (posy - last_y) * scal;
		last_y = posy;
		gtk_range_set_value(GTK_RANGE(widget), adj->value + value * (adj->upper - adj->lower));
		return TRUE;
	}

	double angle = atan2(-posx, posy) + M_PI; // clockwise, zero at 6 o'clock, 0 .. 2*M_PI
	if (drag) {
		// block "forbidden zone" and direct moves between quadrant 1 and 4
		int quadrant = 1 + (int)(angle/M_PI_2);
		if (priv->last_quadrant == 1 && (quadrant == 3 || quadrant == 4)) {
			angle = scale_zero;
		} else if (priv->last_quadrant == 4 && (quadrant == 1 || quadrant == 2)) {
			angle = 2*M_PI - scale_zero;
		} else {
			if (angle < scale_zero) {
				angle = scale_zero;
			} else if (angle > 2*M_PI - scale_zero) {
				angle = 2*M_PI - scale_zero;
			}
			priv->last_quadrant = quadrant;
		}
	} else {
		if (angle < scale_zero) {
			angle = scale_zero;
		} else if (angle > 2*M_PI - scale_zero) {
			angle = 2*M_PI - scale_zero;
		}
		priv->last_quadrant = 0;
	}
	angle = (angle - scale_zero) / (2 * (M_PI-scale_zero)); // normalize to 0..1
	gtk_range_set_value(GTK_RANGE(widget), adj->lower + angle * (adj->upper - adj->lower));
	return TRUE;
}

static gboolean gx_knob_pointer_motion(GtkWidget *widget, GdkEventMotion *event)
{
	g_assert(GX_IS_KNOB(widget));
	if (!gtk_widget_has_grab(widget)) {
		return FALSE;
	}
	gdk_event_request_motions (event);
	_gx_knob_pointer_event(widget, event->x, event->y, get_stock_id(widget), TRUE, event->state, 0);
	return FALSE;
}

static gboolean gx_knob_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_KNOB(widget));
	GdkRectangle image_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	image_rect.width = gdk_pixbuf_get_width(pb);
	image_rect.height = gdk_pixbuf_get_height(pb);
	g_object_unref(pb);
	gdouble knobstate = _gx_regler_get_step_pos(GX_REGLER(widget), 1);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, NULL);
	if (gtk_widget_has_grab(widget) || gtk_widget_has_focus(widget)== TRUE) {
		return TRUE;
	}
	_gx_knob_draw_arc(widget, &image_rect, knobstate, TRUE);
	return TRUE;
}

static gboolean gx_knob_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_KNOB(widget));
	GdkRectangle image_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	image_rect.width = gdk_pixbuf_get_width(pb);
	image_rect.height = gdk_pixbuf_get_height(pb);
	g_object_unref(pb);
	gdouble knobstate = _gx_regler_get_step_pos(GX_REGLER(widget), 1);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, NULL);
	if (gtk_widget_has_grab(widget) || gtk_widget_has_focus(widget)== TRUE) {
		return TRUE;
	}
	_gx_knob_draw_arc(widget, &image_rect, knobstate, FALSE);
	return TRUE;
}

static void gx_knob_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_KNOB(widget));
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	requisition->width = gdk_pixbuf_get_width(pb);
	requisition->height = gdk_pixbuf_get_height(pb);
	_gx_regler_calc_size_request(GX_REGLER(widget), requisition);
	g_object_unref(pb);
}

static gboolean gx_knob_expose(GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_KNOB(widget));
	GdkRectangle image_rect, value_rect;
	GdkPixbuf *pb = gtk_widget_render_icon(widget, get_stock_id(widget), GtkIconSize(-1), NULL);
	image_rect.width = gdk_pixbuf_get_width(pb);
	image_rect.height = gdk_pixbuf_get_height(pb);
	gdouble knobstate = _gx_regler_get_step_pos(GX_REGLER(widget), 1);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	_gx_knob_expose(widget, &image_rect, knobstate, pb);
	_gx_regler_display_value(GX_REGLER(widget), &value_rect);
	g_object_unref(pb);
	return FALSE;
}

static gboolean gx_knob_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_KNOB(widget));
	if (event->button != 1 && event->button != 3) {
		return FALSE;
	}
	gtk_widget_grab_focus(widget);
	if (_gx_knob_pointer_event(widget, event->x, event->y, get_stock_id(widget), FALSE, event->state, event->button)) {
		gtk_grab_add(widget);
	}
	return FALSE;
}

