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

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include "GxRegler.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <gtk/gtkprivate.h>

#define P_(s) (s)   // FIXME -> gettext

/****************************************************************
 ** GxRegler
 */

#define GX_REGLER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GX_TYPE_REGLER, GxReglerPrivate))

typedef struct
{
	gint last_quadrant;
} GxReglerPrivate;

enum {
	PROP_TYPE = 1,
	PROP_VAR_ID,
	PROP_MODEL,
};

static void gx_regler_buildable_interface_init(GtkBuildableIface *iface);
static void gx_regler_parser_finished(GtkBuildable *buildable, GtkBuilder *builder);
static void gx_regler_destroy(GtkObject *object);
static void gx_regler_init_pixmaps(int change_knob);
static void
gx_regler_set_property(GObject      *object,
                        guint         prop_id,
                        const GValue *value,
                        GParamSpec   *pspec);
static void
gx_regler_get_property(GObject      *object,
                        guint         prop_id,
                        GValue       *value,
                        GParamSpec   *pspec);
static gboolean gx_regler_enter_in (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_regler_leave_out (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_regler_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_regler_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_regler_button_press (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_regler_button_release (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_regler_pointer_motion (GtkWidget *widget, GdkEventMotion *event);
static gboolean gx_regler_key_press (GtkWidget *widget, GdkEventKey *event);
static gboolean gx_regler_scroll (GtkWidget *widget, GdkEventScroll *event);

G_DEFINE_TYPE_WITH_CODE (GxRegler, gx_regler, GTK_TYPE_RANGE,
                         G_IMPLEMENT_INTERFACE (GTK_TYPE_BUILDABLE,
                                                gx_regler_buildable_interface_init));

GType regler_type_get_type(void)
{
	static GType etype = 0;
	if (G_UNLIKELY(etype == 0)) {
		static const GEnumValue values[] = {
			{ GX_REGLER_TYPE_SMALL_KNOB, "REGLER_TYPE_SMALL_KNOB", "small knob" },
			{ GX_REGLER_TYPE_BIG_KNOB, "REGLER_TYPE_BIG_KNOB", "big knob" },
			{ GX_REGLER_TYPE_HSLIDER, "REGLER_TYPE_HSLIDER", "horizontal slider" },
			{ GX_REGLER_TYPE_MINI_SLIDER, "REGLER_TYPE_MINI_SLIDER", "mini slider" },
			{ GX_REGLER_TYPE_WHEEL, "REGLER_TYPE_WHEEL", "wheel" },
			{ GX_REGLER_TYPE_VSLIDER, "REGLER_TYPE_VSLIDER", "vslider" },
			{ GX_REGLER_TYPE_EQ_SLIDER, "REGLER_TYPE_EQ_SLIDER", "eq slider" },
			{ 0, NULL, NULL }
		};
		etype = g_enum_register_static (g_intern_static_string ("GxReglerType"), values);
	}
	return etype;
}

static void gx_regler_class_init(GxReglerClass *klass)
{
	GObjectClass   *gobject_class;
	GtkObjectClass *object_class;
	GtkWidgetClass *widget_class;

	gobject_class = G_OBJECT_CLASS (klass);
	object_class = (GtkObjectClass*) klass;
	widget_class = (GtkWidgetClass*) klass;

	gobject_class->set_property = gx_regler_set_property;
	gobject_class->get_property = gx_regler_get_property;

	object_class->destroy = gx_regler_destroy;


//--------- init pixmaps
	klass->pix_is = 0;

//--------- connect the events with funktions
	widget_class->enter_notify_event = gx_regler_enter_in;
	widget_class->leave_notify_event = gx_regler_leave_out;
	widget_class->expose_event = gx_regler_expose;
	widget_class->size_request = gx_regler_size_request;
	widget_class->button_press_event = gx_regler_button_press;
	widget_class->button_release_event = gx_regler_button_release;
	widget_class->motion_notify_event = gx_regler_pointer_motion;
	widget_class->key_press_event = gx_regler_key_press;
	widget_class->scroll_event = gx_regler_scroll;

	g_object_class_install_property(gobject_class,
	                                PROP_TYPE,
	                                g_param_spec_enum("regler-type",
	                                                  P_("Type"),
	                                                  P_("The type of the control"),
	                                                  regler_type_get_type(),
	                                                  GX_REGLER_TYPE_SMALL_KNOB,
	                                                  GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(gobject_class,
	                                PROP_VAR_ID,
	                                g_param_spec_string("var-id",
	                                                    P_("Variable"),
	                                                    P_("The id of the linked variable"),
	                                                    NULL,
	                                                    GParamFlags(GTK_PARAM_READWRITE)));

	g_type_class_add_private(klass, sizeof (GxReglerPrivate));
	gx_regler_init_pixmaps(0);
}

/****************************************************************
 ** Constants
 */

/** set here the sizes and steps for the used regler **/
//--------- small knob size and steps
gint class_regler_x = 25;
gint class_regler_y = 25;
gint class_regler_step = 86;

//--------- big knob size and steps
gint class_bigknob_x = 51;
gint class_bigknob_y = 51;
gint class_bigknob_step = 86;

//--------- horizontal slider size and steps
gint class_slider_x = 120 ;  //this is the scale size
gint class_vslider_x = 70 ;  //this is the scale size
gint class_slider_y = 10 ;   // this is the knob size x and y be the same
gint class_slider_step = 100;
gint class_vslider_step = 50;

//--------- mini slider size and steps
gint class_minislider_x = 34 ;  //this is the scale size
gint class_minislider_y = 6 ;   // this is the knob size x and y be the same
gint class_minislider_step = 28;

//--------- eqslider size and steps
gint class_eqslider_x = 13 ;  //this is the scale size
gint class_eqslider_y = 55 ;   // this is the knob size x and y be the same
gint class_eqslider_step = 50;

//--------- horizontal wheel size and steps
gint class_wheel_x = 40 ;  //this is the scale size
gint class_wheel_y = 8 ;   // this is the knob size x and y be the same
gint class_wheel_step = 100;


/****************************************************************
 ** calculate the knop pointer with dead zone
 */

const double scale_zero = 20 * (M_PI/180); // defines "dead zone" for knobs

//------------ calculate needed precision
int precision(double n)
{
	if (n < 0.009999) return 3;
	else if (n < 0.099999) return 2;
	else if (n < 0.999999) return 1;
	else return 0;
}

#define min(x, y) ((x) < (y) ? (x) : (y))

static void knob_expose(GtkWidget *widget, int knob_x, int knob_y,
                        GdkPixbuf *regler_image, int arc_offset)
{
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	int reglerx = widget->allocation.x + (widget->allocation.width - knob_x) / 2;
	int reglery = widget->allocation.y + (widget->allocation.height - knob_y) / 2;
	double df = adj->upper - adj->lower;
	double reglerstate = (df == 0.0 ? 0.0 : (adj->value - adj->lower) / df);
	double angle = scale_zero + reglerstate * 2 * (M_PI - scale_zero);
	const double pointer_off = 5;
	double radius = min(knob_x-pointer_off, knob_y-pointer_off) / 2;
	double lengh_x = (reglerx+radius+pointer_off/2) - radius * sin(angle);
	double lengh_y = (reglery+radius+pointer_off/2) + radius * cos(angle);
	double radius1 = min(knob_x, knob_y) / 2;

	GdkColor color;
	if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
		// linear color change in RGB space from (52480, 0, 5120) to (8448, 46004, 5120)
		color.red = 52480 - (int)(44032 * reglerstate);
		color.green = (int)(46004 * reglerstate);
		color.blue = 5120;
		gtk_paint_focus(widget->style, widget->window, GTK_STATE_NORMAL, NULL, widget, NULL,
		                reglerx, reglery, knob_x, knob_y);
	} else {
		color.red = 5120;
		color.green = 742;
		color.blue = 52480;
	}

	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                regler_image, 0,0, reglerx, reglery,
	                knob_x, knob_y, GDK_RGB_DITHER_NORMAL, 0, 0);

	/** this is to create a pointer rotating on the knob with painting funktions **/
	GdkGC *line = gdk_gc_new(GDK_DRAWABLE(widget->window));
	cairo_t *cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));

	cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
	cairo_set_line_width(cr, 5.0);
	cairo_move_to(cr, reglerx+radius1, reglery+radius1);
	cairo_line_to(cr,lengh_x,lengh_y);
	cairo_stroke(cr);
	cairo_set_source_rgb(cr,  0.9, 0.9, 0.9);
	cairo_set_line_width(cr, 1.0);
	cairo_move_to(cr, reglerx+radius1, reglery+radius1);
	cairo_line_to(cr,lengh_x,lengh_y);
	cairo_stroke(cr);
	cairo_destroy(cr);

	gdk_gc_set_rgb_fg_color(line, &color);
	gdk_gc_set_line_attributes(line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
	gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,
	             reglerx+arc_offset, reglery+arc_offset,
	             knob_x-1-2*arc_offset, knob_y-1-2*arc_offset,-90*64,360*64);
	g_object_unref(line);
	/** pointer ready  **/
}

/****************************************************************
 ** general expose events for all "regler" controllers
 */

//----------- draw the Regler when moved
static gboolean gx_regler_expose (GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_REGLER(widget));
	GxRegler *regler = GX_REGLER(widget);
	GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));
	GdkWindow *window = widget->window;

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));

	int reglerx = widget->allocation.x, reglery = widget->allocation.y;

//----------- small knob
	if (regler->regler_type == GX_REGLER_TYPE_SMALL_KNOB) {
		knob_expose(widget, class_regler_x, class_regler_y, klass->regler_image, 0);
	}
//--------- Big knob
	else if (regler->regler_type == GX_REGLER_TYPE_BIG_KNOB) {
		knob_expose(widget, class_bigknob_x, class_bigknob_y, klass->bigregler_image, 2);
	}

//--------- horizontal slider
	else if (regler->regler_type == GX_REGLER_TYPE_HSLIDER) {
		reglerx += (widget->allocation.width -
		            class_slider_x) *0.5;
		reglery += (widget->allocation.height -
		            class_slider_y) *0.5;

		double df = adj->upper - adj->lower;
		int reglerstate = (int)(df == 0.0 ? 0.0 : (adj->value - adj->lower) * class_slider_step / df);

		if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			gtk_paint_focus(widget->style, window, GTK_STATE_NORMAL, NULL, widget, NULL,
			                reglerx, reglery, class_slider_x,
			                class_slider_y);

			gdk_pixbuf_copy_area(klass->slider_image,0,0,
			                     class_slider_x,
			                     class_slider_y,
			                     klass->slider_image1,0,0);

			gdk_pixbuf_copy_area(klass->slider_image,
			                     class_slider_x,0,20,
			                     class_slider_y,
			                     klass->slider_image1, reglerstate,0);

			gdk_pixbuf_saturate_and_pixelate(klass->slider_image1,
			                                 klass->slider_image1,70.0,FALSE);

			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->slider_image1, 0, 0, reglerx, reglery,
			                class_slider_x,
			                class_slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		} else {

			gdk_pixbuf_copy_area(klass->slider_image,0,0,
			                     class_slider_x,
			                     class_slider_y,
			                     klass->slider_image1,0,0);

			gdk_pixbuf_copy_area(klass->slider_image,
			                     class_slider_x,0,20,
			                     class_slider_y,
			                     klass->slider_image1, reglerstate,0);

			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->slider_image1, 0, 0, reglerx, reglery,
			                class_slider_x,
			                class_slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		}
	}

//--------- mini slider
	else if (regler->regler_type == GX_REGLER_TYPE_MINI_SLIDER) {
		reglerx += (widget->allocation.width -
		            class_minislider_x) *0.5;
		reglery += (widget->allocation.height -
		            class_minislider_y) *0.5;

		double df = adj->upper - adj->lower;
		int reglerstate = (int)(df == 0.0 ? 0.0 : (adj->value - adj->lower) * class_minislider_step / df);

		if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			gdk_pixbuf_copy_area(klass->minislider_image,0,0,
			                     class_minislider_x,
			                     class_minislider_y,
			                     klass->minislider_image1,0,0);

			gdk_pixbuf_copy_area(klass->minislider_image,
			                     class_minislider_x,0,6,
			                     class_minislider_y,
			                     klass->minislider_image1, reglerstate,0);

			gdk_pixbuf_saturate_and_pixelate(klass->minislider_image1,
			                                 klass->minislider_image1,99.0,FALSE);

			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->minislider_image1, 0, 0, reglerx, reglery,
			                class_minislider_x,
			                class_minislider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		} else {

			gdk_pixbuf_copy_area(klass->minislider_image,0,0,
			                     class_minislider_x,
			                     class_minislider_y,
			                     klass->minislider_image1,0,0);

			gdk_pixbuf_copy_area(klass->minislider_image,
			                     class_minislider_x,0,6,
			                     class_minislider_y,
			                     klass->minislider_image1, reglerstate,0);

			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->minislider_image1, 0, 0, reglerx, reglery,
			                class_minislider_x,
			                class_minislider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		}
	}

//----------- wheel
	else if (regler->regler_type == GX_REGLER_TYPE_WHEEL) {
		reglerx += (widget->allocation.width -
		            class_wheel_x) *0.5;
		reglery += (widget->allocation.height -
		            class_wheel_y) *0.5;
		double df = adj->upper - adj->lower;
		int reglerstate = (int)(df == 0.0 ? 0.0 : (adj->value - adj->lower) * class_wheel_step / df);
		int smoth_pointer = 0;
		if (reglerstate > (adj->upper - adj->lower)) {
			smoth_pointer = -4;
		}
		if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->wheel_image1, 0, 0, reglerx, reglery,
			                class_wheel_x,
			                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->wheel_image,
			                reglerstate + class_wheel_x, 0,
			                reglerx, reglery, class_wheel_x,
			                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->pointer_image1,0, 0,
			                reglerx+smoth_pointer+reglerstate*0.4, reglery, 2,
			                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);

		} else {
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->wheel_image1, 0, 0, reglerx, reglery,
			                class_wheel_x,
			                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->wheel_image,
			                reglerstate + class_wheel_x, 0,
			                reglerx, reglery, class_wheel_x,
			                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->pointer_image1,0, 0,
			                reglerx+smoth_pointer+reglerstate*0.4, reglery, 2,
			                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);

		}
	}

//--------- vertical slider
	else if (regler->regler_type == GX_REGLER_TYPE_VSLIDER) {
		reglerx += (widget->allocation.width -
		            class_slider_y) *0.5;
		reglery += (widget->allocation.height -
		            class_vslider_x) *0.5;

		double df = adj->upper - adj->lower;
		int reglerstate = (int)(df == 0.0 ? 0.0 : (adj->upper - adj->value ) * class_vslider_step / df);

		if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			gtk_paint_focus(widget->style, window, GTK_STATE_NORMAL, NULL, widget, NULL,
			                reglerx, reglery, class_slider_y,
			                class_vslider_x);

			gdk_pixbuf_copy_area(klass->vslider_image,0,20,
			                     class_slider_y,
			                     class_vslider_x,
			                     klass->vslider_image1,0,0);

			gdk_pixbuf_copy_area(klass->vslider_image,0,
			                     class_slider_x,10,20,
			                     klass->vslider_image1,0, reglerstate);

			gdk_pixbuf_saturate_and_pixelate(klass->vslider_image1,
			                                 klass->vslider_image1,70.0,FALSE);

			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->vslider_image1, 0, 0, reglerx, reglery,
			                class_slider_y,
			                class_vslider_x, GDK_RGB_DITHER_NORMAL, 0, 0);
		} else {

			gdk_pixbuf_copy_area(klass->vslider_image,0,20,
			                     class_slider_y,
			                     class_vslider_x,
			                     klass->vslider_image1,0,0);

			gdk_pixbuf_copy_area(klass->vslider_image,0,
			                     class_slider_x,10,20,
			                     klass->vslider_image1, 0,reglerstate);

			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->vslider_image1, 0, 0, reglerx, reglery,
			                class_slider_y,
			                class_vslider_x, GDK_RGB_DITHER_NORMAL, 0, 0);
		}
	}

//--------- mini slider
	else if (regler->regler_type == GX_REGLER_TYPE_EQ_SLIDER) {
		reglerx += (widget->allocation.width -
		            class_eqslider_x) *0.5;
		reglery += (widget->allocation.height -
		            class_eqslider_y) *0.5;

		double df = adj->upper - adj->lower;
		int reglerstate = (int)(df == 0.0 ? 0.0 : (adj->value - adj->lower) * class_eqslider_step / df);

		gdk_pixbuf_copy_area(klass->eqslider_image,0,reglerstate+8,
		                     class_eqslider_x,
		                     class_eqslider_y,
		                     klass->eqslider_image1,0,0);

		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->eqslider_image1, 0, 0, reglerx, reglery,
		                class_eqslider_x,
		                class_eqslider_y, GDK_RGB_DITHER_NORMAL, 0, 0);

	}
	return TRUE;
}

/****************************************************************
 ** redraw when leave
 */

static gboolean gx_regler_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_REGLER(widget));
	GxRegler *regler = GX_REGLER(widget);
	GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	int reglerx = widget->allocation.x, reglery = widget->allocation.y;

//----------- small knob
	if (regler->regler_type == GX_REGLER_TYPE_SMALL_KNOB) {
		if (GTK_WIDGET_HAS_GRAB(widget) || GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			return TRUE;
		}
		reglerx += (widget->allocation.width -
		            class_regler_x) *0.5;
		reglery += (widget->allocation.height -
		            class_regler_y) *0.5;

		GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
		GdkColor color ;

		color.red = 20 * 256;
		color.blue = 205 * 256;
		color.green = 742;
		gdk_gc_set_rgb_fg_color(line, &color);
		gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
		gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx, reglery,
		             class_regler_x-1 ,
		             class_regler_y-1,-90*64,360*64);
		g_object_unref(line );
	}

//----------- Big knob
	else if (regler->regler_type == GX_REGLER_TYPE_BIG_KNOB) {
		if (GTK_WIDGET_HAS_GRAB(widget) || GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			return TRUE;
		}
		reglerx += (widget->allocation.width -
		            class_bigknob_x) *0.5;
		reglery += (widget->allocation.height -
		            class_bigknob_y) *0.5;

		GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
		GdkColor color ;

		color.red = 20 * 256;
		color.blue = 205 * 256;
		color.green = 742;
		gdk_gc_set_rgb_fg_color(line, &color);
		gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
		gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx+2, reglery+2,
		             class_bigknob_x-5 ,
		             class_bigknob_y-5,-90*64,360*64);
		g_object_unref(line );
	}

//----------- horizontal slider
	else if (regler->regler_type == GX_REGLER_TYPE_HSLIDER) {
		reglerx += (widget->allocation.width -
		            class_slider_x) *0.5;
		reglery += (widget->allocation.height -
		            class_slider_y) *0.5;
		int reglerstate = (int)((adj->value - adj->lower) *
		                        class_slider_step / (adj->upper - adj->lower));

		gdk_pixbuf_copy_area(klass->slider_image,0,0,
		                     class_slider_x,
		                     class_slider_y,
		                     klass->slider_image1,0,0);

		gdk_pixbuf_copy_area(klass->slider_image,
		                     class_slider_x,0,20,
		                     class_slider_y,
		                     klass->slider_image1, reglerstate,0);

		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->slider_image1, 0, 0, reglerx, reglery,
		                class_slider_x,
		                class_slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

//----------- mini slider
	else if (regler->regler_type == GX_REGLER_TYPE_MINI_SLIDER) {
		reglerx += (widget->allocation.width -
		            class_minislider_x) *0.5;
		reglery += (widget->allocation.height -
		            class_minislider_y) *0.5;
		int reglerstate = (int)((adj->value - adj->lower) *
		                        class_minislider_step / (adj->upper - adj->lower));

		gdk_pixbuf_copy_area(klass->minislider_image,0,0,
		                     class_minislider_x,
		                     class_minislider_y,
		                     klass->minislider_image1,0,0);

		gdk_pixbuf_copy_area(klass->minislider_image,
		                     class_minislider_x,0,6,
		                     class_minislider_y,
		                     klass->minislider_image1, reglerstate,0);

		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->minislider_image1, 0, 0, reglerx, reglery,
		                class_minislider_x,
		                class_minislider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

//----------- wheel
	else if (regler->regler_type == GX_REGLER_TYPE_WHEEL) {
		reglerx += (widget->allocation.width -
		            class_wheel_x) *0.5;
		reglery += (widget->allocation.height -
		            class_wheel_y) *0.5;
		int reglerstate = (int)((adj->value - adj->lower) *
		                        class_wheel_step / (adj->upper - adj->lower));
		int smoth_pointer = 0;
		if (reglerstate>(adj->upper - adj->lower))smoth_pointer=-4;
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->wheel_image1, 0, 0, reglerx, reglery,
		                class_wheel_x,
		                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->wheel_image,
		                reglerstate + class_wheel_x, 0, reglerx, reglery,
		                class_wheel_x,
		                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->pointer_image1,0, 0,
		                reglerx+smoth_pointer+reglerstate*0.4, reglery, 2,
		                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);

	}

//----------- vertical slider
	else if (regler->regler_type == GX_REGLER_TYPE_VSLIDER) {
		reglerx += (widget->allocation.width -
		            class_slider_y) *0.5;
		reglery += (widget->allocation.height -
		            class_vslider_x) *0.5;
		int reglerstate = (int)((adj->upper -adj->value ) *
		                        class_vslider_step / (adj->upper - adj->lower));

		gdk_pixbuf_copy_area(klass->vslider_image,0,20,
		                     class_slider_y,
		                     class_vslider_x,
		                     klass->vslider_image1,0,0);

		gdk_pixbuf_copy_area(klass->vslider_image,0,
		                     class_slider_x,10,20,
		                     klass->vslider_image1, 0,reglerstate);

		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->vslider_image1, 0, 0, reglerx, reglery,
		                class_slider_y,
		                class_vslider_x, GDK_RGB_DITHER_NORMAL, 0, 0);
	}
	return TRUE;
}

/****************************************************************
 ** redraw when enter
 */

static gboolean gx_regler_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_REGLER(widget));
	GxRegler *regler = GX_REGLER(widget);
	GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	int reglerx = widget->allocation.x, reglery = widget->allocation.y;

//----------- small knob
	if (regler->regler_type == GX_REGLER_TYPE_SMALL_KNOB) {
		if (GTK_WIDGET_HAS_GRAB(widget) || GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			return TRUE;
		}
		reglerx += (widget->allocation.width -
		            class_regler_x) *0.5;
		reglery += (widget->allocation.height -
		            class_regler_y) *0.5;
		int reglerstate = (int)((adj->value - adj->lower) *
		                        class_regler_step / (adj->upper - adj->lower));

		GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
		GdkColor color ;

		color.red = (205-reglerstate*2) * 256;
		color.blue = 20 * 256;
		color.green = reglerstate*742;
		gdk_gc_set_rgb_fg_color(line, &color);
		gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
		gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx, reglery,
		             class_regler_x-1 ,
		             class_regler_y-1,
		             (-reglerstate-90)*64,(-reglerstate-360)*64);
		g_object_unref(line );

	}

//----------- Big knob
	else if (regler->regler_type == GX_REGLER_TYPE_BIG_KNOB) {
		if (GTK_WIDGET_HAS_GRAB(widget) || GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			return TRUE;
		}
		reglerx += (widget->allocation.width -
		            class_bigknob_x) *0.5;
		reglery += (widget->allocation.height -
		            class_bigknob_y) *0.5;
		int reglerstate = (int)((adj->value - adj->lower) *
		                        class_bigknob_step / (adj->upper - adj->lower));

		GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
		GdkColor color ;

		color.red = (205-reglerstate*2) * 256;
		color.blue = 20 * 256;
		color.green = reglerstate*742;
		gdk_gc_set_rgb_fg_color(line, &color);
		gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
		gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx+2, reglery+2,
		             class_bigknob_x-5 ,
		             class_bigknob_y-5,
		             (-reglerstate-90)*64,(-reglerstate-360)*64);
		g_object_unref(line );

	}

//----------- horizontal slider
	else if (regler->regler_type == GX_REGLER_TYPE_HSLIDER) {
		reglerx += (widget->allocation.width -
		            class_slider_x) *0.5;
		reglery += (widget->allocation.height -
		            class_slider_y) *0.5;
		int reglerstate = (int)((adj->value - adj->lower) *
		                        class_slider_step / (adj->upper - adj->lower));

		gdk_pixbuf_copy_area(klass->slider_image,0,0,
		                     class_slider_x,
		                     class_slider_y,
		                     klass->slider_image1,0,0);

		gdk_pixbuf_copy_area(klass->slider_image,
		                     class_slider_x,0,20,
		                     class_slider_y,
		                     klass->slider_image1, reglerstate,0);

		gdk_pixbuf_saturate_and_pixelate(klass->slider_image1,
		                                 klass->slider_image1,70.0,FALSE);

		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->slider_image1, 0, 0,
		                reglerx, reglery, class_slider_x,
		                class_slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

//----------- mini slider
	else if (regler->regler_type == GX_REGLER_TYPE_MINI_SLIDER) {
		reglerx += (widget->allocation.width -
		            class_minislider_x) *0.5;
		reglery += (widget->allocation.height -
		            class_minislider_y) *0.5;
		int reglerstate = (int)((adj->value - adj->lower) *
		                        class_minislider_step / (adj->upper - adj->lower));

		gdk_pixbuf_copy_area(klass->minislider_image,0,0,
		                     class_minislider_x,
		                     class_minislider_y,
		                     klass->minislider_image1,0,0);

		gdk_pixbuf_copy_area(klass->minislider_image,
		                     class_minislider_x,0,6,
		                     class_minislider_y,
		                     klass->minislider_image1, reglerstate,0);

		gdk_pixbuf_saturate_and_pixelate(klass->minislider_image1,
		                                 klass->minislider_image1,99.0,FALSE);

		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->minislider_image1, 0, 0,
		                reglerx, reglery, class_minislider_x,
		                class_minislider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

//----------- wheel
	else if (regler->regler_type == GX_REGLER_TYPE_WHEEL) {
		reglerx += (widget->allocation.width -
		            class_wheel_x) *0.5;
		reglery += (widget->allocation.height -
		            class_wheel_y) *0.5;
		int reglerstate = (int)((adj->value - adj->lower) *
		                        class_wheel_step / (adj->upper - adj->lower));
		int smoth_pointer = 0;
		if (reglerstate>(adj->upper - adj->lower))smoth_pointer=-4;
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->wheel_image1, 0, 0, reglerx, reglery,
		                class_wheel_x,
		                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->wheel_image,
		                reglerstate + class_wheel_x, 0,
		                reglerx, reglery, class_wheel_x,
		                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->pointer_image1,0, 0,
		                reglerx+smoth_pointer+reglerstate*0.4, reglery, 2,
		                class_wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);

	}

//----------- vertical slider
	else if (regler->regler_type == GX_REGLER_TYPE_VSLIDER) {
		reglerx += (widget->allocation.width -
		            class_slider_y) *0.5;
		reglery += (widget->allocation.height -
		            class_vslider_x) *0.5;
		int reglerstate = (int)((adj->upper -adj->value ) *
		                        class_vslider_step / (adj->upper - adj->lower));

		gdk_pixbuf_copy_area(klass->vslider_image,0,20,
		                     class_slider_y,
		                     class_vslider_x,
		                     klass->vslider_image1,0,0);

		gdk_pixbuf_copy_area(klass->vslider_image,0,
		                     class_slider_x,10,20,
		                     klass->vslider_image1, 0,reglerstate);

		gdk_pixbuf_saturate_and_pixelate(klass->vslider_image1,
		                                 klass->vslider_image1,70.0,FALSE);

		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->vslider_image1, 0, 0,
		                reglerx, reglery, class_slider_y,
		                class_vslider_x, GDK_RGB_DITHER_NORMAL, 0, 0);
	}


	return TRUE;
}

/****************************************************************
 ** set size for GdkDrawable per type
 */

static void gx_regler_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_REGLER(widget));
	GxRegler *regler = GX_REGLER(widget);
	//GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));

//----------- small knob
	if (regler->regler_type == GX_REGLER_TYPE_SMALL_KNOB) {
		requisition->width = class_regler_x;
		requisition->height = class_regler_y;
	}
//----------- Big knob
	else if (regler->regler_type == GX_REGLER_TYPE_BIG_KNOB) {
		requisition->width = class_bigknob_x;
		requisition->height = class_bigknob_y;
	}
//----------- horizontal slider
	else if (regler->regler_type == GX_REGLER_TYPE_HSLIDER) {
		requisition->width = class_slider_x;
		requisition->height = class_slider_y;
	}
//----------- mini slider
	else if (regler->regler_type == GX_REGLER_TYPE_MINI_SLIDER) {
		requisition->width = class_minislider_x;
		requisition->height = class_minislider_y;
	}
	else if (regler->regler_type == GX_REGLER_TYPE_WHEEL) {
		requisition->width = class_wheel_x;
		requisition->height = class_wheel_y;
	}
//----------- vertical slider
	else if (regler->regler_type == GX_REGLER_TYPE_VSLIDER) {
		requisition->width = class_slider_y;
		requisition->height = class_vslider_x;
	}
//-----------  eqslider
	else if (regler->regler_type == GX_REGLER_TYPE_EQ_SLIDER) {
		requisition->width = class_eqslider_x;
		requisition->height = class_eqslider_y;
	}
}

/****************************************************************
 ** set value from key bindings
 */

static void gx_regler_set_value (GtkWidget *widget, int dir_down)
{
	g_assert(GX_IS_REGLER(widget));

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));

	int oldstep = (int)(0.5f + (adj->value - adj->lower) / adj->step_increment);
	int step;
	int nsteps = (int)(0.5f + (adj->upper - adj->lower) / adj->step_increment);
	if (dir_down)
		step = oldstep - 1;
	else
		step = oldstep + 1;
	float value = adj->lower + step * (double)(adj->upper - adj->lower) / nsteps;
	gtk_widget_grab_focus(widget);
	gtk_range_set_value(GTK_RANGE(widget), value);
}

/****************************************************************
 ** keyboard bindings
 */

static gboolean gx_regler_key_press (GtkWidget *widget, GdkEventKey *event)
{
	g_assert(GX_IS_REGLER(widget));

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	switch (event->keyval) {
	case GDK_Home:
		gtk_range_set_value(GTK_RANGE(widget), adj->lower);
		return TRUE;
	case GDK_End:
		gtk_range_set_value(GTK_RANGE(widget), adj->upper);
		return TRUE;
	case GDK_Up:
		gx_regler_set_value(widget, 0);
		return TRUE;
	case GDK_Right:
		gx_regler_set_value(widget, 0);
		return TRUE;
	case GDK_Down:
		gx_regler_set_value(widget, 1);
		return TRUE;
	case GDK_Left:
		gx_regler_set_value(widget, 1);
		return TRUE;
	}

	return FALSE;
}

//------------ calculate value for display
static double gx_regler_get_value(GtkAdjustment *adj,double pos)
{
    if (adj->step_increment < 0.009999) pos = (floor (pos*1000))*0.001;
    else if (adj->step_increment < 0.099999) pos = (floor (pos*100))*0.01;
    else if (adj->step_increment < 0.999999) pos = (floor (pos*10))*0.1;
    else pos = floor (pos);
    return pos;

}

/****************************************************************
 ** alternative knob motion mode (ctrl + mouse pressed)
 */

static void knob_pointer_event(GtkWidget *widget, gdouble x, gdouble y, int knob_x, int knob_y,
                               gboolean drag, int state)
{
	static double last_x = 2e20;
	GxRegler *regler = GX_REGLER(widget);
	GxReglerPrivate *priv = GX_REGLER_GET_PRIVATE(regler);
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	double radius =  min(knob_x, knob_y) / 2;
	int  reglerx = (widget->allocation.width - knob_x) / 2;
	int  reglery = (widget->allocation.height - knob_y) / 2;
	double posx = (reglerx + radius) - x; // x axis right -> left
	double posy = (reglery + radius) - y; // y axis top -> bottom
	double value;
	if (!drag) {
		if (state & GDK_CONTROL_MASK) {
			last_x = posx;
			return;
		} else {
			last_x = 2e20;
		}
	}
	if (last_x < 1e20) { // in drag started with Control Key
		const double scaling = 0.005;
		double scal = (state & GDK_CONTROL_MASK ? scaling : scaling*0.1);
		value = (last_x - posx) * scal;
		last_x = posx;
		gtk_range_set_value(GTK_RANGE(widget), adj->value + value * (adj->upper - adj->lower));
		return;
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
}

/****************************************************************
 ** mouse button pressed set value
 */

static gboolean gx_regler_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_REGLER(widget));
	GxRegler *regler = GX_REGLER(widget);
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	GtkWidget * dialog,* spinner, *ok_button, *vbox, *toplevel;

	switch (event->button) {
	case 1:  // left button

		gtk_widget_grab_focus(widget);
		gtk_widget_grab_default (widget);
		gtk_grab_add(widget);

		if (regler->regler_type == GX_REGLER_TYPE_SMALL_KNOB) {
			knob_pointer_event(widget, event->x, event->y, class_regler_x, class_regler_y,
			                   FALSE, event->state);
		}
		else if (regler->regler_type == GX_REGLER_TYPE_BIG_KNOB) {
			knob_pointer_event(widget, event->x, event->y, class_bigknob_x, class_bigknob_y,
			                   FALSE, event->state);
		}
		else if (regler->regler_type == GX_REGLER_TYPE_HSLIDER) {

			int  reglerx = (widget->allocation.width -
			                class_slider_x) *0.5;
			double pos = adj->lower + (((event->x - reglerx-10)*0.01)* (adj->upper - adj->lower));
			gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		}
		else if (regler->regler_type == GX_REGLER_TYPE_MINI_SLIDER) {

			int  reglerx = (widget->allocation.width -
			                class_minislider_x) *0.5;
			double pos = adj->lower + (((event->x - reglerx-3)*0.03575)* (adj->upper - adj->lower));
			gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		}
		else if (regler->regler_type == GX_REGLER_TYPE_WHEEL) {

			int  wheelx = (widget->allocation.width -
			               class_wheel_x) *0.5;
			double pos = adj->lower + (((event->x - wheelx)*0.03)* (adj->upper - adj->lower));
			gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		}
		else if (regler->regler_type == GX_REGLER_TYPE_VSLIDER) {

			int  reglery = (widget->allocation.height -
			                class_vslider_x) *0.5;
			double pos = adj->upper - (((event->y - reglery-10)*0.02)* (adj->upper - adj->lower));
			gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		}
		else if (regler->regler_type == GX_REGLER_TYPE_EQ_SLIDER) {

			int  reglery = (widget->allocation.height -
			                class_eqslider_x) *0.5;
			double pos = adj->upper - (((event->y - reglery+18)*0.02)* (adj->upper - adj->lower));
			gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		}
		break;

	case 3:  // right button show num entry
		dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		spinner = gtk_spin_button_new (GTK_ADJUSTMENT(adj), adj->step_increment,
		                               precision(adj->step_increment));
		gtk_entry_set_activates_default(GTK_ENTRY(spinner), TRUE);
		ok_button  = gtk_button_new_from_stock(GTK_STOCK_OK);
		GTK_WIDGET_SET_FLAGS (GTK_WIDGET(ok_button), GTK_CAN_DEFAULT);
		vbox = gtk_vbox_new (FALSE, 4);
		gtk_container_add (GTK_CONTAINER(vbox), spinner);
		gtk_container_add (GTK_CONTAINER(vbox), ok_button);
		gtk_container_add (GTK_CONTAINER(dialog), vbox);
		gtk_window_set_decorated(GTK_WINDOW(dialog), FALSE);
		gtk_window_set_title (GTK_WINDOW (dialog), "set");
		gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
		gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
		gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
		gtk_window_set_keep_below (GTK_WINDOW(dialog), FALSE);
		gtk_widget_grab_default(ok_button);
		toplevel = gtk_widget_get_toplevel (widget);
        if (GTK_WIDGET_TOPLEVEL (toplevel))
           {
             gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(toplevel));
           }

		gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);
		g_signal_connect_swapped (ok_button, "clicked",
		                          G_CALLBACK (gtk_widget_destroy), dialog);

		gtk_widget_show_all(dialog);
		break;

	}
	return TRUE;
}

/****************************************************************
 ** mouse button release
 */

static gboolean gx_regler_button_release (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_REGLER(widget));
	if (GTK_WIDGET_HAS_GRAB(widget))
		gtk_grab_remove(widget);
	return FALSE;
}

/****************************************************************
 ** set the value from mouse movement
 */

static gboolean gx_regler_pointer_motion (GtkWidget *widget, GdkEventMotion *event)
{
	g_assert(GX_IS_REGLER(widget));
	GxRegler *regler = GX_REGLER(widget);
	//GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	gdk_event_request_motions (event);
	if (GTK_WIDGET_HAS_GRAB(widget)) {
		if (regler->regler_type == GX_REGLER_TYPE_SMALL_KNOB) {
			knob_pointer_event(widget, event->x, event->y, class_regler_x, class_regler_y,
			                   TRUE, event->state);
		} else if (regler->regler_type == GX_REGLER_TYPE_BIG_KNOB) {
			knob_pointer_event(widget, event->x, event->y, class_bigknob_x, class_bigknob_y,
			                   TRUE, event->state);
		}
		else if (regler->regler_type == GX_REGLER_TYPE_HSLIDER) {
			if (event->x > 0) {
				int  sliderx = (widget->allocation.width -
				                class_slider_x)*0.5;
				double pos = adj->lower + (((event->x - sliderx-10)*0.01)* (adj->upper - adj->lower));
				gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
			}
		}
//----------- minislider
		else if (regler->regler_type == GX_REGLER_TYPE_MINI_SLIDER) {
			if (event->x > 0) {
				int  sliderx = (widget->allocation.width -
				                class_minislider_x)*0.5;
				double pos = adj->lower + (((event->x - sliderx-3)*0.03575)* (adj->upper - adj->lower));
				gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
			}
		}
//----------- wheel
		else if (regler->regler_type == GX_REGLER_TYPE_WHEEL) {
			if (event->x > 0) {
				int  wheelx = (widget->allocation.width -
				               class_wheel_x)*0.5;
				double pos = adj->lower + (((event->x - wheelx)*0.03)* (adj->upper - adj->lower));
				gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
			}
		}
//----------- vertical slider
		else if (regler->regler_type == GX_REGLER_TYPE_VSLIDER) {
			if (event->y > 0) {
				int  slidery = (widget->allocation.height -
				                class_vslider_x)*0.5;
				double pos = adj->upper - (((event->y - slidery-10)*0.02)* (adj->upper - adj->lower));
				gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
			}
		}
//----------- eqslider
		else if (regler->regler_type == GX_REGLER_TYPE_EQ_SLIDER) {
			if (event->y > 0) {
				int  slidery = (widget->allocation.height -
				                class_eqslider_x)*0.5;
				double pos = adj->upper - (((event->y - slidery+18)*0.02)* (adj->upper - adj->lower));
				gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
			}
		}
	}
	return FALSE;
}

/****************************************************************
 ** set value from mouseweel
 */

static gboolean gx_regler_scroll (GtkWidget *widget, GdkEventScroll *event)
{
	usleep(5000);
	gx_regler_set_value(widget, event->direction);
	return FALSE;
}

/****************************************************************
 ** init the used background images to the used skins
 */

//---------- here are the inline pixmaps for regler
#include "GxReglerPix.cpp"

void gx_regler_init_pixmaps(int change_knob)
{
	GtkWidget *widget = GTK_WIDGET( g_object_new (GX_TYPE_REGLER, NULL ));
	g_assert(GX_IS_REGLER(widget));
	GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));

	klass->pix_switch = change_knob;
	if (klass->pix_switch == 0) {
//----------- Big knob
		klass->bigregler_image = gdk_pixbuf_new_from_xpm_data (knob1_xpm);
		g_assert(klass->bigregler_image != NULL);
//----------- small knob
		klass->regler_image = gdk_pixbuf_scale_simple(klass->bigregler_image,25,25,GDK_INTERP_HYPER);
		g_assert(klass->regler_image != NULL);
		klass->pix_switch = 1;
	} else if (klass->pix_switch == 1) {
//----------- Big knob
		klass->bigregler_image = gdk_pixbuf_new_from_xpm_data (knob2_xpm);
		g_assert(klass->bigregler_image != NULL);
//----------- small knob
		klass->regler_image = gdk_pixbuf_scale_simple(klass->bigregler_image,25,25,GDK_INTERP_HYPER);
		g_assert(klass->regler_image != NULL);
		klass->pix_switch = 0;
	} else if (klass->pix_switch == 2) {
//----------- Big knob
		klass->bigregler_image = gdk_pixbuf_new_from_xpm_data (knob3_xpm);
		g_assert(klass->bigregler_image != NULL);
//----------- small knob
		klass->regler_image = gdk_pixbuf_scale_simple(klass->bigregler_image,25,25,GDK_INTERP_HYPER);
		g_assert(klass->regler_image != NULL);
		klass->pix_switch = 0;
	} else if (klass->pix_switch == 3) {
//----------- Big knob
		klass->bigregler_image = gdk_pixbuf_new_from_xpm_data (knob4_xpm);
		g_assert(klass->bigregler_image != NULL);
//----------- small knob
		klass->regler_image = gdk_pixbuf_scale_simple(klass->bigregler_image,25,25,GDK_INTERP_HYPER);
		g_assert(klass->regler_image != NULL);
		klass->pix_switch = 0;
	} else if (klass->pix_switch == 4) {
//----------- Big knob
		klass->bigregler_image = gdk_pixbuf_new_from_xpm_data (knob5_xpm);
		g_assert(klass->bigregler_image != NULL);
//----------- small knob
		klass->regler_image = gdk_pixbuf_scale_simple(klass->bigregler_image,25,25,GDK_INTERP_HYPER);
		g_assert(klass->regler_image != NULL);
		klass->pix_switch = 0;
	} else if (klass->pix_switch == 5) {
//----------- Big knob
		klass->bigregler_image = gdk_pixbuf_new_from_xpm_data (knob6_xpm);
		g_assert(klass->bigregler_image != NULL);
//----------- small knob
		klass->regler_image = gdk_pixbuf_scale_simple(klass->bigregler_image,25,25,GDK_INTERP_HYPER);
		g_assert(klass->regler_image != NULL);
		klass->pix_switch = 0;
	}

//----------- general pixmap init
	if (klass->pix_is != 1) {
//----------- horizontal slider
		klass->slider_image = gdk_pixbuf_new_from_xpm_data(slidersm_xpm);
		g_assert(klass->slider_image != NULL);
		klass->slider_image1 = gdk_pixbuf_copy( klass->slider_image );
		g_assert(klass->slider_image1 != NULL);
//----------- vertical slider
		klass->vslider_image = gdk_pixbuf_rotate_simple(klass->slider_image,
		                                                GDK_PIXBUF_ROTATE_CLOCKWISE);
		g_assert(klass->vslider_image != NULL);
		klass->vslider_image = gdk_pixbuf_flip(klass->vslider_image, TRUE);
		klass->vslider_image1 = gdk_pixbuf_copy( klass->vslider_image );
		g_assert(klass->vslider_image1 != NULL);
//----------- mini slider
		klass->minislider_image = gdk_pixbuf_scale_simple(klass->slider_image,40,6,GDK_INTERP_HYPER);
		g_assert(klass->minislider_image != NULL);
		klass->minislider_image1 = gdk_pixbuf_copy( klass->minislider_image );
		g_assert(klass->minislider_image1 != NULL);
//----------- eq slider
		klass->eqslider_image = gdk_pixbuf_new_from_xpm_data(eqslider_xpm);
		g_assert(klass->eqslider_image != NULL);
		klass->eqslider_image1 = gdk_pixbuf_copy( klass->eqslider_image );
		g_assert(klass->eqslider_image1 != NULL);
//----------- horizontal wheel
		klass->wheel_image = gdk_pixbuf_new_from_xpm_data(wheel_xpm);
		g_assert(klass->wheel_image != NULL);
		klass->wheel_image1 = gdk_pixbuf_new_from_xpm_data(wheel_s_xpm);
		g_assert(klass->wheel_image1 != NULL);
		klass->pointer_image1 = gdk_pixbuf_new_from_xpm_data(pointer_xpm);
		g_assert(klass->pointer_image1 != NULL);

		klass->pix_is = 1;
	}
}

/****************************************************************
 ** init the Regler type/size
 */

static void gx_regler_init(GxRegler *regler)
{
	GxReglerPrivate *priv;
	GtkWidget *widget = GTK_WIDGET(regler);
	//GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));

	gtk_widget_set_has_window (GTK_WIDGET (regler), FALSE);
	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(regler), GTK_CAN_FOCUS);
	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(regler), GTK_CAN_DEFAULT);
	//gtk_range_set_adjustment(GTK_RANGE(regler), GTK_ADJUSTMENT(gtk_adjustment_new(0,0,1,1,1,1)));
	priv = GX_REGLER_GET_PRIVATE(regler);
	priv->last_quadrant = 0;

	if (regler->regler_type == GX_REGLER_TYPE_SMALL_KNOB) {
		widget->requisition.width = class_regler_x;
		widget->requisition.height = class_regler_y;
	} else if (regler->regler_type == GX_REGLER_TYPE_BIG_KNOB) {
		widget->requisition.width = class_bigknob_x;
		widget->requisition.height = class_bigknob_y;
	} else if (regler->regler_type == GX_REGLER_TYPE_HSLIDER) {
		widget->requisition.width = class_slider_x;
		widget->requisition.height = class_slider_y;
	} else if (regler->regler_type == GX_REGLER_TYPE_MINI_SLIDER) {
		widget->requisition.width = class_minislider_x;
		widget->requisition.height = class_minislider_y;
	} else if (regler->regler_type == GX_REGLER_TYPE_WHEEL) {
		widget->requisition.width = class_wheel_x;
		widget->requisition.height = class_wheel_y;
	} else if (regler->regler_type == GX_REGLER_TYPE_VSLIDER) {
		widget->requisition.width = class_slider_y;
		widget->requisition.height = class_vslider_x;
	} else if (regler->regler_type == GX_REGLER_TYPE_EQ_SLIDER) {
		widget->requisition.width = class_eqslider_x;
		widget->requisition.height = class_eqslider_y;
	}
}

/****************************************************************
 ** redraw when value changed
 */

/*
static gboolean gx_regler_value_changed(gpointer obj)
{
	GtkWidget *widget = (GtkWidget *)obj;
	gtk_widget_queue_draw(widget);
	return FALSE;
}
*/

/****************************************************************
 */
void gx_regler_destroy(GtkObject *object)
{
/*
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> regler_image))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> regler_image);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> bigregler_image))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> bigregler_image);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> toggle_image))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> toggle_image1))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image1);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> slider_image))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> slider_image1))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> minislider_image))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> minislider_image1))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> switch_image))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> switch_image1))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image1);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> wheel_image))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> wheel_image1))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image1);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> b_toggle_image))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_image);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> vslider_image))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> vslider_image1))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> eqslider_image))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->eqslider_image);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> eqslider_image1))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->eqslider_image1);
	if (G_IS_OBJECT(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> led_image))
		g_object_unref(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->led_image);
*/
	GTK_OBJECT_CLASS (gx_regler_parent_class)->destroy (object);
}


/****************************************************************
 ** get the Regler type
 */

/*
GType gx_regler_get_type (void)
{
	static GType kn_type = 0;
	if (!kn_type) {
		static const GTypeInfo kn_info = {
			sizeof(GxReglerClass), NULL,  NULL, (GClassInitFunc)gx_regler_class_init, NULL, NULL, sizeof (GxRegler), 0, (GInstanceInitFunc)gx_regler_init
		};
		kn_type = g_type_register_static(GTK_TYPE_RANGE,  "GxRegler", &kn_info, (GTypeFlags)0);
	}
	return kn_type;
}
*/

/****************************************************************
 ** GtkBuildable Interface
 */

static GtkBuildableIface *buildable_parent_iface = NULL;

static void gx_regler_buildable_interface_init(GtkBuildableIface *iface)
{
	buildable_parent_iface = (GtkBuildableIface*)g_type_interface_peek_parent(iface);
	iface->parser_finished = gx_regler_parser_finished;
}

static void gx_regler_parser_finished(GtkBuildable *buildable, GtkBuilder *builder)
{
}

/****************************************************************
 ** Properties
 */

static regler_connect_func *p_regler_connect_func;

void set_regler_connect_func(regler_connect_func f)
{
	p_regler_connect_func = f;
}

static gboolean gx_regler_connect_var(GxRegler *regler, const gchar *var)
{
	if (p_regler_connect_func) {
		return p_regler_connect_func(regler, var);
	}
	return TRUE;
}

static void gx_regler_set_var_id (GxRegler *regler, const gchar *str)
{
	g_free(regler->var_id);
	regler->var_id = g_strdup (str ? str : "");
	gx_regler_connect_var(regler, regler->var_id);
}

gchar *gx_regler_get_var(GxRegler *regler)
{
	return regler->var_id;
}

static void
gx_regler_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
	GxRegler *regler;

	regler = GX_REGLER (object);

	switch(prop_id) {
	case PROP_TYPE:
		regler->regler_type = g_value_get_enum(value);
		break;
	case PROP_VAR_ID:
		gx_regler_set_var_id (regler, g_value_get_string (value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
gx_regler_get_property(GObject      *object,
                        guint         prop_id,
                        GValue       *value,
                        GParamSpec   *pspec)
{
	GxRegler *regler;

	regler = GX_REGLER(object);

	switch(prop_id) {
	case PROP_TYPE:
		g_value_set_enum(value, regler->regler_type);
		break;
	case PROP_VAR_ID:
		g_value_set_string (value, regler->var_id);
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
