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
 * ---------------------------------------------------------------------------
 *
 *        file: paintbox.cpp 
 *
 * ----------------------------------------------------------------------------
 */


#include "paintbox.h"

#include <gtk/gtkprivate.h>
#include <gtk/gtk.h>
#include <cmath>
#include <cstring>

#define P_(s) (s)   // FIXME -> gettext

#include "resources.h"

enum {
	PROP_PAINT_FUNC = 1,
};

static void gx_paint_box_destroy(GtkObject *object);
static void gx_paint_box_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_paint_box_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_paint_box_expose(GtkWidget *widget, GdkEventExpose *event);
static void gx_paint_box_style_set (GtkWidget *widget, GtkStyle  *previous_style);

G_DEFINE_TYPE(GxefnamePaintBox, gx_paint_box, GTK_TYPE_BOX)

static void gx_paint_box_class_init (GxefnamePaintBoxClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS(klass);
	GtkObjectClass *object_class = (GtkObjectClass*) klass;
	GtkWidgetClass *widget_class = (GtkWidgetClass*)klass;
	gobject_class->set_property = gx_paint_box_set_property;
	gobject_class->get_property = gx_paint_box_get_property;
	object_class->destroy = gx_paint_box_destroy;
	widget_class->style_set = gx_paint_box_style_set;
	widget_class->expose_event = gx_paint_box_expose;

	g_object_class_install_property(
		gobject_class, PROP_PAINT_FUNC,
		g_param_spec_string("paint-func",
		                    P_("Paint Type"),
		                    P_("Type of paint function for background"),
		                    "",
		                    GParamFlags(GTK_PARAM_READWRITE)));

	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_string("paint-func",
		                    P_("Paint Type"),
		                    P_("Type of paint function for background"),
		                    NULL,
		                    GParamFlags(GTK_PARAM_READABLE)));
	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_int("width",
		                 P_("Width"),
		                 P_("size.width request for paintbox"),
		                 0,
						 G_MAXINT,
						 0,
		                 GParamFlags(GTK_PARAM_READABLE)));
	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_int("height",
		                 P_("Height"),
		                 P_("size.height request for paintbox"),
		                 0,
						 G_MAXINT,
						 0,
		                 GParamFlags(GTK_PARAM_READABLE)));

}

static void set_paint_func(GxefnamePaintBox *paint_box, const gchar *paint_func)
{
	gchar *spf;
	gtk_widget_style_get(GTK_WIDGET(paint_box), "paint-func", &spf, NULL);
	if (spf) {
		if (paint_box->paint_func && strcmp(paint_box->paint_func, spf) == 0) {
			return;
		}
	} else {
		if (!paint_func) {
			paint_func = "";
		}
		if (paint_box->paint_func && strcmp(paint_box->paint_func, paint_func) == 0) {
			return;
		}
		spf = g_strdup(paint_func);
	}
	g_free(paint_box->paint_func);
	paint_box->paint_func = spf;
	set_expose_func(paint_box, spf);
	g_object_notify(G_OBJECT(paint_box), "paint-func");
}

static void gx_paint_box_style_set(GtkWidget *widget, GtkStyle  *previous_style)
{
	GxefnamePaintBox *paint_box = GX_EFNAME_PAINT_BOX(widget);
	set_paint_func(paint_box, paint_box->paint_func);
}


static void gx_paint_box_init (GxefnamePaintBox *paint_box)
{
	gtk_widget_set_redraw_on_allocate(GTK_WIDGET(paint_box), TRUE);
	paint_box->paint_func = g_strdup("");
	set_paint_func(paint_box, NULL);
	paint_box->gxr_image = NULL;
    paint_box->stock_image = gdk_pixbuf_new_from_resource("/gxplug/pedal.png", NULL);
    //gdk_pixbuf_save(paint_box->stock_image,"plug.png","png",NULL);
}

static void gx_paint_box_destroy(GtkObject *object)
{
	GxefnamePaintBox *paint_box = GX_EFNAME_PAINT_BOX(object);
	if (paint_box->paint_func) {
		g_free(paint_box->paint_func);
		paint_box->paint_func = NULL;
	}
	if (G_IS_OBJECT(paint_box->gxr_image)) {
		g_object_unref(paint_box->gxr_image);
	}
	paint_box->gxr_image = NULL;
    if (G_IS_OBJECT(paint_box->stock_image)) {
		g_object_unref(paint_box->stock_image);
	}
	paint_box->stock_image = NULL;
	GTK_OBJECT_CLASS(gx_paint_box_parent_class)->destroy(object);
}

static gboolean gx_paint_box_expose(GtkWidget *widget, GdkEventExpose *event)
{
	GxefnamePaintBox *paint_box = GX_EFNAME_PAINT_BOX(widget);
	if (paint_box->expose_func) {
		paint_box->expose_func(widget, event);
	}
	GTK_WIDGET_CLASS(GTK_OBJECT_CLASS(gx_paint_box_parent_class))->expose_event(widget, event);
	return FALSE;
}

static void gx_paint_box_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	GxefnamePaintBox *paint_box = GX_EFNAME_PAINT_BOX(object);
	switch (prop_id) {
	case PROP_PAINT_FUNC:
		set_paint_func(paint_box, g_value_get_string(value));
		break;
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
		g_value_set_string(value, GX_EFNAME_PAINT_BOX(object)->paint_func);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

GtkWidget *gx_paint_box_new (GtkOrientation orientation, gboolean homogeneous, gint spacing)
{
	return (GtkWidget*)g_object_new(
		GX_TYPE_EFNAME_PAINT_BOX,
		"orientation", orientation,
		"spacing",     spacing,
		"homogeneous", homogeneous ? TRUE : FALSE,
		NULL);
}

/****************************************************************
 ** Paint functions
 */

static void pedal_expose(GtkWidget *wi, GdkEventExpose *ev)
{
    GtkAllocation *allocation = g_new0 (GtkAllocation, 1);
    gtk_widget_get_allocation(GTK_WIDGET(wi), allocation); 
	gint rect_width  = allocation->width-2;
	gint rect_height = allocation->height-3;
	if (rect_width <= 0 || rect_height <= 0) {
	    return;
	}
	cairo_t *cr;
	GxefnamePaintBox *paintbox = GX_EFNAME_PAINT_BOX(wi);
	/* create a cairo context */
	cr = gdk_cairo_create(gtk_widget_get_window(wi));
	GdkRegion *region;
	region = gdk_region_rectangle (allocation);
	gdk_region_intersect (region, ev->region);
	gdk_cairo_region (cr, region);
	cairo_clip (cr);
	
	gint x0      = allocation->x+1;
	gint y0      = allocation->y+1;

	static double ne_w = 0.;
	if (ne_w != rect_width*rect_height || !(GDK_IS_PIXBUF (paintbox-> gxr_image))) {
		ne_w = rect_width*rect_height;
		if (G_IS_OBJECT(paintbox-> gxr_image)) {
			g_object_unref(paintbox->gxr_image);
		}
		
		paintbox->gxr_image = gdk_pixbuf_scale_simple(
			paintbox->stock_image, wi->allocation.width ,wi->allocation.height, GDK_INTERP_NEAREST);
			//g_object_unref(paintbox->stock_image);
	}

	// base 
	gdk_cairo_set_source_pixbuf(cr,paintbox->gxr_image, x0, y0);
	cairo_rectangle (cr, x0,y0,rect_width,rect_height);
	cairo_fill (cr);

	cairo_destroy(cr);
	gdk_region_destroy (region);                
    g_free (allocation); 
}

void set_expose_func(GxefnamePaintBox *paint_box, const gchar *paint_func)
{
	if (strcmp(paint_func, "pedal_expose") == 0) {
		paint_box->expose_func = pedal_expose;
	} else {
		paint_box->expose_func = 0;
	}
}
