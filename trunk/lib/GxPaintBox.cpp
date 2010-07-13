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


#include "GxPaintBox.h"
#include "GxGradient.h"
#include <gtk/gtkprivate.h>
#include <cmath>
#include <cstring>

#define P_(s) (s)   // FIXME -> gettext

G_DEFINE_TYPE(GxPaintBox, gx_paint_box, GTK_TYPE_BOX)

enum {
	PROP_PAINT_FUNC = 1,
};

static void gx_paint_box_destroy(GtkObject *object);
static void gx_paint_box_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_paint_box_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_paint_box_expose(GtkWidget *widget, GdkEventExpose *event);

static void gx_paint_box_class_init (GxPaintBoxClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS(klass);
	GtkObjectClass *object_class = (GtkObjectClass*) klass;
	GtkWidgetClass *widget_class = (GtkWidgetClass*)klass;
	gobject_class->set_property = gx_paint_box_set_property;
	gobject_class->get_property = gx_paint_box_get_property;
	object_class->destroy = gx_paint_box_destroy;
	widget_class->expose_event = gx_paint_box_expose;
	g_object_class_install_property(
		gobject_class, PROP_PAINT_FUNC,
		g_param_spec_string("paint-func",
		                    P_("Paint Type"),
		                    P_("Type of paint function for background"),
		                    "",
		                    GParamFlags(GTK_PARAM_READWRITE)));
	gtk_widget_class_install_style_property_parser(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_boxed ("skin-gradient",
		                    P_("Skin color"),
		                    P_("Color gradient defined as part of skin"),
		                    GX_TYPE_GRADIENT,
		                    GParamFlags(GTK_PARAM_READABLE)),
		gx_parse_gradient);
}

static void gx_paint_box_init (GxPaintBox *paint_box)
{
	paint_box->paint_func = g_strdup("");
	gtk_widget_set_redraw_on_allocate(GTK_WIDGET(paint_box), TRUE);
}

static void gx_paint_box_destroy(GtkObject *object)
{
	GxPaintBox *paint_box = GX_PAINT_BOX(object);
	if (paint_box->paint_func) {
		g_free(paint_box->paint_func);
		paint_box->paint_func = NULL;
	}
}

static void set_expose_func(GxPaintBox *paint_box, gchar *paint_func);

static gboolean gx_paint_box_expose(GtkWidget *widget, GdkEventExpose *event)
{
	GxPaintBox *paint_box = GX_PAINT_BOX(widget);
	if (paint_box->expose_func) {
		paint_box->expose_func(widget, event);
	}
	GTK_WIDGET_CLASS(GTK_OBJECT_CLASS(gx_paint_box_parent_class))->expose_event(widget, event);
	return FALSE;
}

static void gx_paint_box_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	GxPaintBox *paint_box = GX_PAINT_BOX(object);
	switch (prop_id) {
	case PROP_PAINT_FUNC: {
		const char *str = g_value_get_string(value);
		g_free(paint_box->paint_func);
		paint_box->paint_func = g_strdup(str ? str : "");
		set_expose_func(paint_box, paint_box->paint_func);
		g_object_notify(object, "paint-func");
		break;
	}
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void gx_paint_box_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	switch (prop_id) {
	case PROP_PAINT_FUNC:
		g_value_set_string(value, GX_PAINT_BOX(object)->paint_func);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

GtkWidget *gx_paint_box_new (gboolean homogeneous, gint spacing)
{
	return (GtkWidget*)g_object_new(
		GX_TYPE_PAINT_BOX,
		"spacing", spacing,
		"homogeneous", homogeneous ? TRUE : FALSE,
		NULL);
}

/****************************************************************
 ** Paint functions
 */


int gx_current_skin = 0; //FIXME (style property / rc files)
int checkbutton7 = 0; //FIXME (2 different functions)
float log_meter(int) //FIXME (fix interface)
{
	return 0;
}


// set cairo color related to the used skin
static void set_skin_color(GtkWidget *wi, cairo_pattern_t *pat)
{
	GxGradient *grad;
	gtk_widget_style_get(wi, "skin-gradient", &grad, NULL);
	if (!grad) {
		return;
	}
	GSList *p;
	for (p = grad->colors; p; p = g_slist_next(p)) {
		GxGradientElement *el = (GxGradientElement*)p->data;
		cairo_pattern_add_color_stop_rgba(pat, el->offset, el->red, el->green, el->blue, el->alpha);
	}
}

//----- paint boxes with cairo -----
static gboolean amp_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	cr = gdk_cairo_create(wi->window);
	double x0      = wi->allocation.x+2;
	double y0      = wi->allocation.y+2;
	double rect_width  = wi->allocation.width-5;
	double rect_height = wi->allocation.height-5;
	double radius = 25.;
	double x1,y1;
	x1=x0+rect_width;
	y1=y0+rect_height;

	cairo_move_to  (cr, x0, y0 + radius);
	cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
	cairo_line_to (cr, x1 - radius, y0);
	cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
	cairo_line_to (cr, x1 , y1 - radius);
	cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
	cairo_line_to (cr, x0 + radius, y1);
	cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
	cairo_close_path (cr);

	cairo_set_source_rgba (cr, 0, 0, 0, 0.6);
	cairo_set_line_width (cr, 5.0);
	cairo_stroke (cr);

	cairo_move_to  (cr, x0, y0 + radius);
	cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
	cairo_line_to (cr, x1 - radius, y0);
	cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
	cairo_line_to (cr, x1 , y1 - radius);
	cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
	cairo_line_to (cr, x0 + radius, y1);
	cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
	cairo_close_path (cr);

	cairo_set_source_rgb (cr, 0.02, 0.02, 0.02);
	cairo_set_line_width (cr, 1.0);
	cairo_stroke (cr);

	cairo_destroy(cr);
	return FALSE;
}

static gboolean conv_widget_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	cairo_pattern_t *pat;

	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+5;
	double y0      = wi->allocation.y+5;
	double rect_width  = wi->allocation.width-10;
	double rect_height = wi->allocation.height-10;
	double radius = 36.;
	double x1,y1;
	x1=x0+rect_width;
	y1=y0+rect_height;

	cairo_move_to  (cr, x0, y0 + radius);
	cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
	cairo_line_to (cr, x1 - radius, y0);
	cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
	cairo_line_to (cr, x1 , y1 - radius);
	cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
	cairo_line_to (cr, x0 + radius, y1);
	cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
	cairo_close_path (cr);

	pat = cairo_pattern_create_linear (0, y0, 0, y1);
    cairo_pattern_add_color_stop_rgba (pat, 1, 0., 0., 0., 0.8);
    cairo_pattern_add_color_stop_rgba (pat, 0, 0, 0, 0, 0.4);
    cairo_set_source (cr, pat);
    cairo_fill_preserve (cr);

	cairo_set_source_rgba (cr, 0, 0, 0, 0.8);
	cairo_set_line_width (cr, 9.0);
	cairo_stroke (cr);

	cairo_move_to  (cr, x0, y0 + radius);
	cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
	cairo_line_to (cr, x1 - radius, y0);
	cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
	cairo_line_to (cr, x1 , y1 - radius);
	cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
	cairo_line_to (cr, x0 + radius, y1);
	cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
	cairo_close_path (cr);

	cairo_set_source_rgb (cr, 0.2, 0.2, 0.2);
	cairo_set_line_width (cr, 1.0);
	cairo_stroke (cr);

	cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

static gboolean upper_widget_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	cairo_pattern_t *pat;

	gint x, y;
	gint w, h;
	/* get the dimensions */
	x = wi->allocation.x+2;
	y = wi->allocation.y+2;
	w = wi->allocation.width-4;
	h = wi->allocation.height-4;

	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	cairo_move_to (cr, x, y);
	cairo_curve_to (cr, x+w*0.66, y, x+w*0.33, y+h, x+w, y+h);
	cairo_line_to (cr, x+w , y);
	cairo_set_line_width (cr, 3.0);
	cairo_close_path (cr);

	pat = cairo_pattern_create_linear (0, y, 0, y+h);
	cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 0.8);
	cairo_pattern_add_color_stop_rgba (pat, 0, 0, 0, 0, 0);
	cairo_set_source (cr, pat);
	cairo_fill_preserve (cr);
	cairo_stroke (cr);

	cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;

}

static gboolean rectangle_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+1;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-11;

	cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill (cr);

	cairo_pattern_t*pat =
		cairo_pattern_create_radial (-50, y0, 5,rect_width+100,  rect_height, 0.0);
	cairo_pattern_add_color_stop_rgb (pat, 0, 0.2, 0.2, 0.3);
	cairo_pattern_add_color_stop_rgb (pat, 1, 0.05, 0.05, 0.05);
	set_skin_color(wi, pat);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
	cairo_fill (cr);

	cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

static gboolean rectangle_skin_color_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+1;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-2;

	cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill (cr);

	cairo_pattern_t*pat =
		cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	set_skin_color(wi, pat);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
	cairo_fill (cr);

	cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

static gboolean convolver_icon_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	/* create a cairo black arc to given widget */
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+1;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-2;

	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill (cr);

	cairo_pattern_t*pat =
		cairo_pattern_create_radial (-50, y0, 5,rect_width+100,  rect_height, 0.0);
	set_skin_color(wi, pat);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
	cairo_fill (cr);

	cairo_move_to (cr, x0+10, y0 + (rect_height*0.5));
	cairo_curve_to (cr, x0+30,y0 + (rect_height*0.005), x0+50, y0 + (rect_height*0.995), x0+70, y0 + (rect_height*0.5));
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_set_line_width (cr, 1.0);
	cairo_stroke (cr);

	cairo_move_to (cr, x0+10, y0 + (rect_height*0.5));
	cairo_line_to (cr, x0+75 , y0 + (rect_height*0.5));
	cairo_move_to (cr, x0+10, y0 + (rect_height*0.2));
	cairo_line_to (cr, x0+10 , y0 + (rect_height*0.8));
	cairo_set_source_rgb (cr, 0.2, 0.8, 0.2);
	cairo_set_line_width (cr, 1.0);
	cairo_stroke (cr);

	cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

static gboolean zac_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+1;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-3;

	cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
	cairo_pattern_t*pat =
		cairo_pattern_create_radial (200, rect_height*0.5, 5,200,  rect_height*0.5, 200.0);
	cairo_pattern_add_color_stop_rgb (pat, 0, 0.8, 0.8, 0.8);
	cairo_pattern_add_color_stop_rgb (pat, 1, 0.3, 0.3, 0.3);
	cairo_set_source (cr, pat);
	cairo_fill (cr);

	cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

static gboolean level_meter_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);
	cairo_set_font_size (cr, 7.0);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+2;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-4;

	int  db_points[] = { -50, -40, -20, -30, -10, -3, 0, 4 };
	char  buf[32];

	cairo_rectangle (cr, x0,y0,rect_width,rect_height+2);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill (cr);

	cairo_pattern_t*pat =
		cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	cairo_pattern_add_color_stop_rgb (pat, 0, 0.2, 0.2, 0.3);
	cairo_pattern_add_color_stop_rgb (pat, 1, 0.05, 0.05, 0.05);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-2);
	cairo_fill (cr);

	for (unsigned int i = 0; i < sizeof (db_points)/sizeof (db_points[0]); ++i)
	{
		float fraction = log_meter(db_points[i]);
		cairo_set_source_rgb (cr, 0.12*i, 1, 0.1);

		cairo_move_to (cr, x0+rect_width*0.2,y0+rect_height - (rect_height * fraction));
		cairo_line_to (cr, x0+rect_width*0.8 ,y0+rect_height -  (rect_height * fraction));
		if (i<6)
		{
			snprintf (buf, sizeof (buf), "%d", db_points[i]);
			cairo_move_to (cr, x0+rect_width*0.32,y0+rect_height - (rect_height * fraction));
		}
		else
		{
			snprintf (buf, sizeof (buf), " %d", db_points[i]);
			cairo_move_to (cr, x0+rect_width*0.34,y0+rect_height - (rect_height * fraction));
		}
		cairo_show_text (cr, buf);
	}

	cairo_set_source_rgb (cr, 0.4, 0.8, 0.4);
	cairo_set_line_width (cr, 0.5);
	cairo_stroke (cr);

	cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

static gboolean AmpBox_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+1;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-2;

    cairo_rectangle (cr, x0-1,y0-1,rect_width+2,rect_height+2);
            cairo_set_source_rgb (cr, 0, 0, 0);
            cairo_fill (cr);

	cairo_pattern_t*pat =
		cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	set_skin_color(wi, pat);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+2,y0+2,rect_width-4,rect_height-4);
	cairo_fill (cr);

    cairo_set_source_rgb(cr,  0.2, 0.2, 0.2);
    cairo_set_line_width(cr, 2.0);
    cairo_move_to(cr,x0+rect_width-3, y0+3);
    cairo_line_to(cr, x0+rect_width-3, y0+rect_height-2);
    cairo_line_to(cr, x0+2, y0+rect_height-2);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
    cairo_set_line_width(cr, 2.0);
    cairo_move_to(cr,x0+3, y0+rect_height-1);
    cairo_line_to(cr, x0+3, y0+3);
    cairo_line_to(cr, x0+rect_width-3, y0+3);
    cairo_stroke(cr);

    cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

static gboolean tribal_box_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	if (gx_current_skin != 1 && gx_current_skin < 7) {
		GdkPixbuf *_image, *stock_image;
		cairo_t *cr;
		/* create a cairo context */
		cr = gdk_cairo_create(wi->window);

		double x0      = wi->allocation.x+1;
		double y0      = wi->allocation.y+1;
		double rect_width  = wi->allocation.width-2;
		double rect_height = wi->allocation.height-3;

		stock_image = gtk_widget_render_icon(wi,"guitar",(GtkIconSize)-1,NULL);
		_image = gdk_pixbuf_scale_simple(
			stock_image, rect_width, rect_height, GDK_INTERP_HYPER);

		cairo_pattern_t*pat;

		double radius = 38.;
		if (rect_width<38) radius = rect_width;
		else if (rect_height<38) radius = rect_height;
		double x1,y1;

		x1=x0+rect_width;
		y1=y0+rect_height;

		cairo_move_to  (cr, x0, y0 + radius);
		cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
		cairo_line_to (cr, x1 - radius, y0);
		cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
		cairo_line_to (cr, x1 , y1 - radius);
		cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
		cairo_line_to (cr, x0 + radius, y1);
		cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
		cairo_close_path (cr);
		pat = cairo_pattern_create_linear (0, y0, 0, y1);
        cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 0.8);
        cairo_pattern_add_color_stop_rgba (pat, 0.5, 0.05, 0.05, 0.05, 0.6);
        cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.2, 0.4);
		cairo_set_source (cr, pat);
		cairo_fill (cr);

		cairo_pattern_destroy (pat);
		cairo_destroy(cr);

        gdk_draw_pixbuf(GDK_DRAWABLE(wi->window), gdk_gc_new(GDK_DRAWABLE(wi->window)),
                        _image, 0, 0,
                        x0, y0, rect_width,rect_height,
                        GDK_RGB_DITHER_NORMAL, 0, 0);

		g_object_unref(_image);
	}
	return FALSE;
}

static gboolean vbox_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	if (gx_current_skin == 1) {
		cairo_t *cr;
		/* create a cairo context */
		cr = gdk_cairo_create(wi->window);

		double x0      = wi->allocation.x+1;
		double y0      = wi->allocation.y+1;
		double rect_width  = wi->allocation.width-2;
		double rect_height = wi->allocation.height-3;

		cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_fill (cr);

		cairo_pattern_t*pat =
			cairo_pattern_create_radial (-50, y0, 5,rect_width+100,  rect_height, 0.0);
		cairo_pattern_add_color_stop_rgb (pat, 0, 0.2, 0.2, 0.3);
		cairo_pattern_add_color_stop_rgb (pat, 1, 0.05, 0.05, 0.05);

		cairo_set_source (cr, pat);
		cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
		cairo_fill (cr);

		cairo_pattern_destroy (pat);
		cairo_destroy(cr);
	} else if (gx_current_skin >= 7) {
		zac_expose(wi,ev);
	}
	return FALSE;
}

static gboolean filter_box_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	GdkPixbuf *_image, *stock_image;
	cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+1;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-3;

	stock_image = gtk_widget_render_icon(wi,"tribe",(GtkIconSize)-1,NULL);
	_image = gdk_pixbuf_scale_simple(
		stock_image, rect_width, rect_height, GDK_INTERP_HYPER);

	cairo_pattern_t*pat;

	gdk_draw_pixbuf(GDK_DRAWABLE(wi->window), gdk_gc_new(GDK_DRAWABLE(wi->window)),
	                _image, 0, 0,
	                x0, y0, rect_width,rect_height,
	                GDK_RGB_DITHER_NORMAL, 0, 0);

	double radius = 38.;
	if (rect_width<38) radius = rect_width;
	else if (rect_height<38) radius = rect_height;
	double x1,y1;

	x1=x0+rect_width;
	y1=y0+rect_height;

	cairo_move_to  (cr, x0, y0 + radius);
	cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
	cairo_line_to (cr, x1 - radius, y0);
	cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
	cairo_line_to (cr, x1 , y1 - radius);
	cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
	cairo_line_to (cr, x0 + radius, y1);
	cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
	cairo_close_path (cr);

	pat = cairo_pattern_create_linear (0, y0, 0, y1);
	cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 0.8);
	cairo_pattern_add_color_stop_rgba (pat, 0.5, 0.05, 0.05, 0.05, 0.6);
	cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.2, 0.4);
	cairo_set_source (cr, pat);
	cairo_fill (cr);

	cairo_pattern_destroy (pat);
	cairo_destroy(cr);
	g_object_unref(_image);

	return FALSE;
}

static gboolean plug_box_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+1;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-2;

    cairo_rectangle (cr, x0-1,y0-1,rect_width+2,rect_height+2);
            cairo_set_source_rgb (cr, 0, 0, 0);
            cairo_fill (cr);

	cairo_pattern_t*pat =
		cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	set_skin_color(wi, pat);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+2,y0+2,rect_width-4,rect_height-4);
	cairo_fill (cr);

    cairo_set_source_rgb(cr,  0.2, 0.2, 0.2);
    cairo_set_line_width(cr, 2.0);
    cairo_move_to(cr,x0+rect_width-3, y0+3);
    cairo_line_to(cr, x0+rect_width-3, y0+rect_height-2);
    cairo_line_to(cr, x0+2, y0+rect_height-2);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
    cairo_set_line_width(cr, 2.0);
    cairo_move_to(cr,x0+3, y0+rect_height-1);
    cairo_line_to(cr, x0+3, y0+3);
    cairo_line_to(cr, x0+rect_width-3, y0+3);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr,  0.5, 0.5, 0.5);
    cairo_set_line_width(cr, 1.5);
    cairo_arc (cr, x0+7, y0+7, 1.5, 0, 2*M_PI);
    cairo_move_to(cr,x0+rect_width-8, y0+7);
    cairo_arc (cr, x0+rect_width-7, y0+7, 1.5, 0, 2*M_PI);
    cairo_move_to(cr,x0+rect_width-7, y0+rect_height-6);
    cairo_arc (cr, x0+rect_width-7, y0+rect_height-6, 1.5, 0, 2*M_PI);
    cairo_move_to(cr,x0+7, y0+rect_height-6);
    cairo_arc (cr, x0+7, y0+rect_height-6, 1.5, 0, 2*M_PI);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
    cairo_fill (cr);

    cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

static gboolean info_box_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+1;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-2;

    cairo_rectangle (cr, x0-1,y0-1,rect_width+2,rect_height+2);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_set_line_width(cr, 2.0);
    cairo_stroke(cr);

	cairo_pattern_t*pat = cairo_pattern_create_linear (x0, y0+50,x0, y0);
    cairo_pattern_set_extend(pat, CAIRO_EXTEND_REFLECT);
    if(checkbutton7 == 1) {
        cairo_pattern_add_color_stop_rgba (pat, 0, 0, 0.8, 0, 0.8);
        cairo_pattern_add_color_stop_rgba (pat, 0.5, 0.05, 0.8, 0.05, 0.6);
        cairo_pattern_add_color_stop_rgba (pat, 1, 0.2, 0.8, 0.2, 0.4);
    } else {
	    set_skin_color(wi, pat);
    }
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+2,y0+2,rect_width-4,rect_height-4);
	cairo_fill (cr);

	cairo_rectangle (cr, x0+8,y0+31,rect_width-16,rect_height-60);
	cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);
    cairo_set_line_width(cr, 2.0);
	cairo_stroke_preserve(cr);
	pat = cairo_pattern_create_linear (x0, y0+50,x0, y0);
    cairo_pattern_set_extend(pat, CAIRO_EXTEND_REFLECT);
    set_skin_color(wi, pat);
    cairo_set_source (cr, pat);
	cairo_fill (cr);

    cairo_set_source_rgb(cr,  0.2, 0.2, 0.2);
    cairo_set_line_width(cr, 2.0);
    cairo_move_to(cr,x0+rect_width-3, y0+3);
    cairo_line_to(cr, x0+rect_width-3, y0+rect_height-2);
    cairo_line_to(cr, x0+2, y0+rect_height-2);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
    cairo_set_line_width(cr, 2.0);
    cairo_move_to(cr,x0+3, y0+rect_height-1);
    cairo_line_to(cr, x0+3, y0+3);
    cairo_line_to(cr, x0+rect_width-3, y0+3);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr,  0.5, 0.5, 0.5);
    cairo_set_line_width(cr, 1.5);
    cairo_arc (cr, x0+7, y0+7, 1.5, 0, 2*M_PI);
    cairo_move_to(cr,x0+rect_width-8, y0+7);
    cairo_arc (cr, x0+rect_width-7, y0+7, 1.5, 0, 2*M_PI);
    cairo_move_to(cr,x0+rect_width-7, y0+rect_height-6);
    cairo_arc (cr, x0+rect_width-7, y0+rect_height-6, 1.5, 0, 2*M_PI);
    cairo_move_to(cr,x0+7, y0+rect_height-6);
    cairo_arc (cr, x0+7, y0+rect_height-6, 1.5, 0, 2*M_PI);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
    cairo_fill (cr);

    cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

static gboolean slooper_expose(GtkWidget *wi, GdkEventExpose *ev)
{
	cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+1;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-2;

    cairo_rectangle (cr, x0-1,y0-1,rect_width+2,rect_height+2);
            cairo_set_source_rgb (cr, 0, 0, 0);
            cairo_fill (cr);

	cairo_pattern_t*pat =
		cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	set_skin_color(wi, pat);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+2,y0+2,rect_width-4,rect_height-27);
	cairo_fill (cr);

    cairo_set_source_rgb(cr,  0.2, 0.2, 0.2);
    cairo_set_line_width(cr, 2.0);
    cairo_move_to(cr,x0+rect_width-3, y0+3);
    cairo_line_to(cr, x0+rect_width-3, y0+rect_height-2);
    cairo_line_to(cr, x0+2, y0+rect_height-2);
    cairo_move_to(cr,x0+2, y0+rect_height-25);
    cairo_line_to(cr, x0+rect_width-3, y0+rect_height-25);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
    cairo_set_line_width(cr, 2.0);
    cairo_move_to(cr,x0+3, y0+rect_height-1);
    cairo_line_to(cr, x0+3, y0+3);
    cairo_line_to(cr, x0+rect_width-3, y0+3);
    cairo_move_to(cr,x0+2, y0+rect_height-27);
    cairo_line_to(cr, x0+rect_width-3, y0+rect_height-27);
    cairo_stroke(cr);


    cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

static void set_expose_func(GxPaintBox *paint_box, gchar *paint_func)
{
	if (strcmp(paint_func, "amp_expose") == 0) {
		paint_box->expose_func = amp_expose;
	} else if (strcmp(paint_func, "conv_widget_expose") == 0) {
		paint_box->expose_func = conv_widget_expose;
	} else if (strcmp(paint_func, "upper_widget_expose") == 0) {
		paint_box->expose_func = upper_widget_expose;
	} else if (strcmp(paint_func, "rectangle_expose") == 0) {
		paint_box->expose_func = rectangle_expose;
	} else if (strcmp(paint_func, "rectangle_skin_color_expose") == 0) {
		paint_box->expose_func = rectangle_skin_color_expose;
	} else if (strcmp(paint_func, "convolver_icon_expose") == 0) {
		paint_box->expose_func = convolver_icon_expose;
	} else if (strcmp(paint_func, "level_meter_expose") == 0) {
		paint_box->expose_func = level_meter_expose;
	} else if (strcmp(paint_func, "AmpBox_expose") == 0) {
		paint_box->expose_func = AmpBox_expose;
	} else if (strcmp(paint_func, "tribal_box_expose") == 0) {
		paint_box->expose_func = tribal_box_expose;
	} else if (strcmp(paint_func, "vbox_expose") == 0) {
		paint_box->expose_func = vbox_expose;
	} else if (strcmp(paint_func, "filter_box_expose") == 0) {
		paint_box->expose_func = filter_box_expose;
	} else if (strcmp(paint_func, "plug_box_expose") == 0) {
		paint_box->expose_func = plug_box_expose;
	} else if (strcmp(paint_func, "info_box_expose") == 0) {
		paint_box->expose_func = info_box_expose;
	} else if (strcmp(paint_func, "slooper_expose") == 0) {
		paint_box->expose_func = slooper_expose;
	} else if (strcmp(paint_func, "zac_expose") == 0) {
		paint_box->expose_func = zac_expose;
	} else {
		paint_box->expose_func = 0;
	}
}
