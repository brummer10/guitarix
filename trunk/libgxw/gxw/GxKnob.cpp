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

#include "GxKnob.h"
#include <cmath>


#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x, y) ((x) < (y) ? (y) : (x))
#endif

#define P_(s) (s)   // FIXME -> gettext

//#define GX_KNOB_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), GX_TYPE_KNOB, GxKnobPrivate))



struct _GxKnobPrivate
{
	gint last_quadrant;
};

static gboolean gx_knob_pointer_motion(GtkWidget *widget, GdkEventMotion *event);
static gboolean gx_knob_enter_in(GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_knob_leave_out(GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_knob_draw(GtkWidget *widget, cairo_t *cr);
static void gx_knob_get_preferred_width(GtkWidget *widget, gint *min_width, gint *natural_width);
static void gx_knob_get_preferred_height(GtkWidget *widget, gint *min_height, gint *natural_height);
static void gx_knob_size_request(GtkWidget *widget, gint *width, gint *height);
static gboolean gx_knob_button_press(GtkWidget *widget, GdkEventButton *event);


G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE(GxKnob, gx_knob, GX_TYPE_REGLER);

#define get_stock_id(widget) (GX_KNOB_CLASS(GTK_WIDGET_GET_CLASS(widget))->stock_id)

static void gx_knob_class_init(GxKnobClass *klass)
{
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;
	widget_class->motion_notify_event = gx_knob_pointer_motion;
	widget_class->enter_notify_event = gx_knob_enter_in;
	widget_class->leave_notify_event = gx_knob_leave_out;
	widget_class->draw = gx_knob_draw;
	widget_class->get_preferred_width = gx_knob_get_preferred_width;
	widget_class->get_preferred_height = gx_knob_get_preferred_height;
	widget_class->button_press_event = gx_knob_button_press;

	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("arc-inset",P_("inset of arch"),
				 P_("Inset of the arc around the knob"),
		                 0, 100, 2, GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
		                    
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("framecount",
		                    P_("Framecount"),
		                    P_("Number of frames in the animation specified by the gtkrc"),
		                    -1, 250, 0,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
                            
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("x-center",
		                    P_("X-Center"),
		                    P_("Horizontal position of the center, -1 for auto."),
		                    -1, 250, -1,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("y-center",
		                    P_("Y-Center"),
		                    P_("Verical position of the center, -1 for auto."),
		                    -1, 250, -1,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("ring-radius",
		                    P_("Ring-Radius"),
		                    P_("Radius of the outer edge of the ring, -1 for max possible."),
                            -1, 250, -1,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("ring-width",
		                    P_("Ring-Width"),
		                    P_("Width of the outer ring"),
		                    0, 250, 2,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("ring-led-size",
		                    P_("Ring-LED-Size"),
		                    P_("Length of one LED in the ring, 0 for seamless ring."),
		                    0, 250, 3,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("ring-led-distance",
		                    P_("Ring-LED-Distance"),
		                    P_("Distance between two LED in the ring"),
		                    0, 250, 2,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("indicator-radius",
		                    P_("Indicator-Radius"),
		                    P_("Radius of the outer edge of the indicator, -1 for half max."),
		                    -1, 250, -1,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("indicator-width",
		                    P_("Indicator-Width"),
		                    P_("Width of the indicator"),
		                    0, 250, 2,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("indicator-length",
		                    P_("Indicator-Length"),
		                    P_("Length of the indicator"),
		                    0, 250, 5,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
                            
}

static void gx_knob_init(GxKnob *knob)
{
	knob->priv = G_TYPE_INSTANCE_GET_PRIVATE(knob, GX_TYPE_KNOB, GxKnobPrivate);
}

static const double scale_zero = 40 * (M_PI/180); // defines "dead zone" for knobs

void _gx_knob_draw_shtuff(GtkWidget *widget, cairo_t *cr, GdkRectangle *image_rect, gdouble knobstate)
{
	// add a value Indicator around the knob
    gint x0 = 0; //image_rect->x;
    gint y0 = 0; //image_rect->y;
    
    // style definitions
    gint ind_radius, ind_width, ind_length, ring_radius, ring_width;
    gint ring_led_size, ring_led_distance, x_center, y_center;
    gtk_widget_style_get(widget, "indicator_radius", &ind_radius, "indicator_width", &ind_width,
                                 "indicator_length", &ind_length, "ring_radius", &ring_radius,
                                 "ring_led_distance", &ring_led_distance,
                                 "ring_width", &ring_width, "ring_led_size", &ring_led_size,
                                 "x_center", &x_center, "y_center", &y_center, NULL);
	
    GtkStyleContext *style = gtk_widget_get_style_context(widget);
    // foreground and background color
    GdkRGBA color;
    gtk_style_context_get_color(style, gtk_widget_get_state_flags(widget), &color);
    GdkRGBA color_;
    gtk_style_context_get_color(style, GTK_STATE_FLAG_INSENSITIVE, &color_);

    // auto values in style?
    gint minrad = min(image_rect->width, image_rect->height) / 2;
    if(x_center < 0)
        x_center = image_rect->width / 2;
    if(y_center < 0)
        y_center = image_rect->height / 2;
    if(ring_radius < 0)
        ring_radius = minrad - ring_radius / 2;
    if(ind_radius < 0)
        ind_radius = minrad / 2;
    
    // precalcs
	double angle = scale_zero + knobstate * 2 * (M_PI - scale_zero);
	double add_angle = 90 * (M_PI / 180.);
    
    double x1 = sin(angle) * -ind_radius;
    double y1 = cos(angle) * ind_radius;
    double x2 = sin(angle) * -(ind_radius - ind_length);
    double y2 = cos(angle) * (ind_radius - ind_length);
    
    // dashed ring
	if (ring_led_size) {
        double dashes[] = {double(ring_led_size), double(ring_led_distance)};
        cairo_set_dash(cr, dashes, sizeof(dashes)/sizeof(dashes[0]), 0);
    }
    
    // draw background
    if (scale_zero < 320 * (M_PI/180)) {
        gdk_cairo_set_source_rgba(cr, &color_);
        cairo_set_line_width(cr, ring_width);
        cairo_arc (cr, x_center + x0, y_center + y0, ring_radius,
            add_angle + scale_zero, add_angle + 320 * (M_PI/180));
        cairo_stroke(cr);
    }
    
    // draw foreground
    if (scale_zero < angle) {
        gdk_cairo_set_source_rgba(cr, &color);
        cairo_arc (cr, x_center + x0, y_center + y0, ring_radius,
            add_angle + scale_zero, add_angle + angle);

        if (ring_width >= 3) {
            cairo_stroke_preserve(cr);
            
            cairo_pattern_t * pat1 = cairo_pattern_create_radial(
                x0 + x_center, y0 + y_center, ring_radius - ring_width / 2., 
                x0 + x_center, y0 + y_center, ring_radius + ring_width / 2.);
            cairo_pattern_add_color_stop_rgba(pat1, 0.0, 0., 0., 0., 0.6);
            cairo_pattern_add_color_stop_rgba(pat1, 0.5, 1., 1., 1., 0.4);
            cairo_pattern_add_color_stop_rgba(pat1, 1.0, 0., 0., 0., 0.6);
            cairo_set_source(cr, pat1);
            cairo_set_operator(cr, CAIRO_OPERATOR_SOFT_LIGHT);
            cairo_stroke(cr);
            cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
            cairo_pattern_destroy(pat1);
        } else {
            cairo_stroke(cr);
        }
    }    
    cairo_set_dash(cr, NULL, 0, 0);
    
    // draw indicator
    gdk_cairo_set_source_rgba(cr, &color);
    cairo_set_line_width(cr, ind_width);
    cairo_move_to(cr, x0 + x1 + x_center, y0 + y1 + y_center);
    cairo_line_to(cr, x0 + x2 + x_center, y0 + y2 + y_center);
    if (ring_width >= 3) {
        cairo_stroke_preserve(cr);
        
        cairo_pattern_t * pat2 = cairo_pattern_create_radial(
            x0 + x_center, y0 + y_center, ind_radius - ind_length, 
            x0 + x_center, y0 + y_center, ind_radius);
        cairo_pattern_add_color_stop_rgba(pat2, 0.0, 0., 0., 0., 0.6);
        cairo_pattern_add_color_stop_rgba(pat2, 0.5, 1., 1., 1., 0.4);
        cairo_pattern_add_color_stop_rgba(pat2, 1.0, 0., 0., 0., 0.6);
        cairo_set_source(cr, pat2);
        cairo_set_operator(cr, CAIRO_OPERATOR_SOFT_LIGHT);
        cairo_stroke(cr);
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        cairo_pattern_destroy(pat2);
    } else {
        cairo_stroke(cr);
    }
}

void _gx_knob_expose(GtkWidget *widget, cairo_t *cr, GdkRectangle *image_rect, gdouble knobstate,
                     GdkPixbuf *knob_image, gint framecount, int has_focus)
{
	if (framecount > 1) {
        int findex;
		framecount--; // zero based index
		findex = (int)(framecount * knobstate);
		gdk_cairo_set_source_pixbuf(cr, knob_image, image_rect->x - (image_rect->width * findex), image_rect->y);
		cairo_rectangle(cr, image_rect->x, image_rect->y, image_rect->width, image_rect->height);
		cairo_fill(cr);
	}
	else {
		if (gtk_widget_has_focus(widget)) {
			gtk_render_focus(gtk_widget_get_style_context(widget), cr,
							 image_rect->x, image_rect->y, image_rect->width, image_rect->height);
		}
		cairo_surface_t *surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 
                               image_rect->width, image_rect->height);
        cairo_t *cr_s = cairo_create(surface);
		gdk_cairo_set_source_pixbuf(cr_s, knob_image, 0, 0);
		cairo_rectangle(cr_s, 0, 0, image_rect->width, image_rect->height);
		cairo_fill(cr_s);
        // shtuff
		_gx_knob_draw_shtuff(widget, cr_s, image_rect, knobstate);
		cairo_set_source_surface(cr, surface, image_rect->x, image_rect->y);
        cairo_paint(cr);
        cairo_surface_destroy (surface);
		cairo_destroy(cr_s);
	}

	
}

static void get_image_dimensions(GtkWidget *widget, GdkPixbuf *pb,
				 GdkRectangle *rect, gint *frame_count)
{
	gtk_widget_style_get(widget, "framecount", frame_count, NULL);

	rect->width  = gdk_pixbuf_get_width(pb);
	rect->height = gdk_pixbuf_get_height(pb);
	
	if (*frame_count >1) {
		rect->width = (rect->width / *frame_count);
	}
	if (*frame_count == 0) {// rc directs to assume square frames
		*frame_count = rect->width / rect->height;
		if (rect->width > (2*rect->height)) {
			rect->width = rect->height;
		}
	}
}

gboolean _gx_knob_pointer_event(GtkWidget *widget, gdouble x, gdouble y, const gchar *icon,
                                gboolean drag, int state, int button, GdkEventButton *event)
{
	int fcount;
	bool finemode = ((state & (GDK_CONTROL_MASK|GDK_SHIFT_MASK)) != 0);
	GdkRectangle image_rect, value_rect;
	
	GxKnob *knob = GX_KNOB(widget);
	GdkPixbuf *pb = gtk_widget_render_icon_pixbuf(widget, icon, GtkIconSize(-1));
	GxKnobPrivate *priv = knob->priv;
	
	get_image_dimensions (widget, pb, &image_rect, &fcount);
	
	g_object_unref(pb);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	if (!drag) {
		if (_gx_regler_check_display_popup(GX_REGLER(widget), &image_rect, &value_rect, event)) {
			return FALSE;
		}
	}
	static double last_y = 2e20;
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	gdouble lower = gtk_adjustment_get_lower(adj);
	gdouble upper = gtk_adjustment_get_upper(adj);
	double radius =	 min(image_rect.width, image_rect.height) / 2;
	double posx = radius - x + image_rect.x; // x axis right -> left
	double posy = radius - y + image_rect.y; // y axis top -> bottom
	double value;
	if (!drag) {
		if (event && event->type == GDK_2BUTTON_PRESS) {
			last_y = 2e20;
		} else {
			last_y = posy;
			return TRUE;
		}
	}
	if (last_y < 1e20) { // in drag started in linear mode
		const double scaling = 0.005;
		double scal = (finemode ? scaling*0.1 : scaling);
		value = (posy - last_y) * scal;
		last_y = posy;
		gdouble adj_value = gtk_adjustment_get_value(adj);
		gtk_range_set_value(GTK_RANGE(widget), adj_value + value * (upper - lower));
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
	gtk_range_set_value(GTK_RANGE(widget), lower + angle * (upper - lower));
	return TRUE;
}

static gboolean gx_knob_pointer_motion(GtkWidget *widget, GdkEventMotion *event)
{
	g_assert(GX_IS_KNOB(widget));
	if (!gtk_widget_has_grab(widget)) {
		return FALSE;
	}
	gdk_event_request_motions (event);
	_gx_knob_pointer_event(widget, event->x, event->y, get_stock_id(widget), TRUE, event->state, 0, NULL);
	return FALSE;
}

static gboolean gx_knob_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	gint fcount;
	g_assert(GX_IS_KNOB(widget));
	if (gtk_widget_has_grab(widget) || gtk_widget_has_focus(widget)== TRUE) {
		return TRUE;
	}
	GdkRectangle image_rect;
	GdkPixbuf *pb = gtk_widget_render_icon_pixbuf(widget, get_stock_id(widget), GtkIconSize(-1));
	get_image_dimensions (widget, pb, &image_rect, &fcount);
	g_object_unref(pb);
	gdouble knobstate = _gx_regler_get_step_pos(GX_REGLER(widget), 1);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, NULL);
	if (fcount == -1) {
		cairo_region_t *rgn = cairo_region_create();
		GdkDrawingContext *ctx = gdk_window_begin_draw_frame(gtk_widget_get_window(widget), rgn);
		cairo_t *cr = gdk_drawing_context_get_cairo_context(ctx);
		_gx_knob_expose(widget, cr, &image_rect, knobstate, pb, fcount, TRUE);
		gdk_window_end_draw_frame(gtk_widget_get_window(widget), ctx);
		cairo_region_destroy(rgn);
	}
	return TRUE;
}

static gboolean gx_knob_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_KNOB(widget));
	if (gtk_widget_has_grab(widget) || gtk_widget_has_focus(widget)== TRUE) {
		return TRUE;
	}
	GdkRectangle image_rect;
	GdkPixbuf *pb = gtk_widget_render_icon_pixbuf(widget, get_stock_id(widget), GtkIconSize(-1));
	gint fcount;
	get_image_dimensions (widget, pb, &image_rect, &fcount);
	g_object_unref(pb);
	gdouble knobstate = _gx_regler_get_step_pos(GX_REGLER(widget), 1);
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, NULL);
	if (fcount == -1) {
		cairo_region_t *rgn = cairo_region_create();
		GdkDrawingContext *ctx = gdk_window_begin_draw_frame(gtk_widget_get_window(widget), rgn);
		cairo_t *cr = gdk_drawing_context_get_cairo_context(ctx);
		_gx_knob_expose(widget, cr, &image_rect, knobstate, pb, fcount, FALSE);
		gdk_window_end_draw_frame(gtk_widget_get_window(widget), ctx);
		cairo_region_destroy(rgn);
	}
	return TRUE;
}

static void gx_knob_get_preferred_width(GtkWidget *widget, gint *min_width, gint *natural_width)
{
	gint width, height;
	gx_knob_size_request(widget, &width, &height);

	if (min_width) {
		*min_width = width;
	}
	if (natural_width) {
		*natural_width = width;
	}
}

static void gx_knob_get_preferred_height(GtkWidget *widget, gint *min_height, gint *natural_height)
{
	gint width, height;
	gx_knob_size_request(widget, &width, &height);

	if (min_height) {
		*min_height = height;
	}
	if (natural_height) {
		*natural_height = height;
	}
}

static void gx_knob_size_request (GtkWidget *widget, gint *width, gint *height)
{
	g_assert(GX_IS_KNOB(widget));
	GdkPixbuf *pb = gtk_widget_render_icon_pixbuf(widget, get_stock_id(widget), GtkIconSize(-1));
	if (GDK_IS_PIXBUF (pb)) {
		gint fcount;
		GdkRectangle rect;
		get_image_dimensions (widget, pb, &rect, &fcount);
		*width = rect.width;
		*height = rect.height;
		_gx_regler_calc_size_request(GX_REGLER(widget), width, height);
		g_object_unref(pb);
	}
}

static gboolean gx_knob_draw(GtkWidget *widget, cairo_t *cr)
{
	g_assert(GX_IS_KNOB(widget));
	GdkRectangle image_rect, value_rect;
	GdkPixbuf *pb = gtk_widget_render_icon_pixbuf(widget, get_stock_id(widget), GtkIconSize(-1));
	if (GDK_IS_PIXBUF (pb)) {
		gint fcount;
		get_image_dimensions (widget, pb, &image_rect, &fcount);
		gdouble knobstate = _gx_regler_get_step_pos(GX_REGLER(widget), 1);
		_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
		_gx_knob_expose(widget, cr, &image_rect, knobstate, pb, fcount, gtk_widget_has_focus(widget));
		_gx_regler_display_value(GX_REGLER(widget), cr, &value_rect);
		g_object_unref(pb);
	}
	return FALSE;
}

static gboolean gx_knob_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_KNOB(widget));
	if (event->button != 1 && event->button != 3) {
		return FALSE;
	}
	gtk_widget_grab_focus(widget);
	if (_gx_knob_pointer_event(widget, event->x, event->y, get_stock_id(widget), FALSE, event->state, event->button, event)) {
		gtk_grab_add(widget);
	}
	return FALSE;
}
