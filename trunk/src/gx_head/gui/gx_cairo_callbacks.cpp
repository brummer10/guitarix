/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 * --------------------------------------------------------------------------
 *
 *
 *	This are the cairo callbacks to draw the guitarix UI
 *
 *
 * --------------------------------------------------------------------------
 */

#include "guitarix.h"

/* --------------------------- gx_cairo namespace ------------------------ */
namespace gx_cairo
{

static void render (GtkWidget *wi, cairo_t* cr) {
    GtkAllocation allocation;
    gtk_widget_get_allocation(wi, &allocation);
    double rect_width  = allocation.width;
    double rect_height = allocation.height;
    double x0      = 0;
    double y0      = 0;
    
    cairo_set_source_rgba (cr, 1.0f, 1.0f, 1.0f, 0.0f);
    cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);
    cairo_paint (cr);
    
    string path = string(GX_PIXMAPS_DIR) + "/gx_splash.png";
    cairo_surface_t *image = cairo_image_surface_create_from_png(path.c_str());
    cairo_rectangle(cr, x0, y0, rect_width, rect_height);
    cairo_set_source_surface(cr, image, 0, 0);
    cairo_paint(cr);
    cairo_surface_destroy (image);
}

void make_transparency(GtkWidget* wi) {

    GtkAllocation allocation;
    gtk_widget_get_allocation(wi, &allocation);
    // get widget dimension
    gint rect_width  = allocation.width;
    gint rect_height = allocation.height;

    // make Image to fake transparency
    cairo_surface_t *ShapeBitmap = NULL;
    cairo_t* cr = NULL;

    ShapeBitmap = cairo_image_surface_create(CAIRO_FORMAT_A1, rect_width, rect_height);
    if (ShapeBitmap) {
        cr = cairo_create (ShapeBitmap);
        if (cairo_status (cr) == CAIRO_STATUS_SUCCESS) {
            render (wi, cr);
            cairo_region_t *region = gdk_cairo_region_create_from_surface(ShapeBitmap);
            gtk_widget_shape_combine_region(wi, nullptr);
            gtk_widget_shape_combine_region(wi, region);
            cairo_region_destroy(region);
        }
        cairo_destroy (cr);
        cairo_surface_destroy(ShapeBitmap);
    }
}

gboolean splash_draw(GtkWidget *wi, cairo_t* cr, gpointer user_data)
{
    static bool ms = true;
    if(ms) {
        make_transparency(wi);
        ms = false;
    }
    render (wi, cr);
    return FALSE;
}

gboolean rectangle_skin_color_draw(GtkWidget *wi, cairo_t *cr, gpointer user_data)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0      = 2;
	double y0      = 2;
	double rect_width  = allocation.width-2;
	double rect_height = allocation.height-2;

	cairo_rectangle (cr, x0,y0,rect_width,rect_height+1);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill (cr);

	cairo_pattern_t*pat =
	cairo_pattern_create_linear (0, y0, 0, y0+rect_height);
		//cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.3, 0.6);
    cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 0.6);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
	cairo_fill (cr);

	cairo_pattern_destroy (pat);
	return FALSE;
    
}

gboolean conv_widget_draw(GtkWidget *wi, cairo_t *cr, gpointer user_data)
{
	cairo_pattern_t *pat;

	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0      = 5;
	double y0      = 5;
	double rect_width  = allocation.width-10;
	double rect_height = allocation.height-10;
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

	return FALSE;
}

gboolean error_box_draw(GtkWidget *wi, cairo_t *cr, gpointer user_data)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0      = 0;
	double y0      = 0;
	double rect_width  = allocation.width;
	double rect_height = allocation.height;

    cairo_rectangle (cr, x0,y0,rect_width,rect_height);
    cairo_set_source_rgb (cr, 0.22, 0.22, 0.22);
   // cairo_set_line_width(cr, 2.0);
    cairo_fill(cr);

	return FALSE;
}

gboolean start_box_draw(GtkWidget *wi, cairo_t *cr, gpointer user_data)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0      = 1;
	double y0      = 1;
	double rect_width  = allocation.width-2;
	double rect_height = allocation.height-2;

    cairo_rectangle (cr, x0-1,y0-1,rect_width+2,rect_height+2);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_set_line_width(cr, 2.0);
    cairo_stroke(cr);

	cairo_pattern_t*pat = cairo_pattern_create_linear (x0, y0+rect_height/2,x0, y0);
    cairo_pattern_set_extend(pat, CAIRO_EXTEND_REFLECT);
    
    cairo_pattern_add_color_stop_rgba (pat, 0, 0.1, 0.1, 0.2, 0.6);
    cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 0.6);

	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+2,y0+2,rect_width-4,rect_height-4);
	cairo_fill (cr);

	cairo_rectangle (cr, x0+8,y0+31,rect_width-16,rect_height-75);
	cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);
    cairo_set_line_width(cr, 2.0);
	cairo_stroke_preserve(cr);
	pat = cairo_pattern_create_linear (x0+8, y0+rect_height/2-37,x0, y0);
    cairo_pattern_set_extend(pat, CAIRO_EXTEND_REFLECT);
    cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.3, 0.6);
    cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 0.6);
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

	return FALSE;
}
}
