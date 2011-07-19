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

// set cairo color related to the used skin
static void gx_skin_color(cairo_pattern_t *pat)
{
	int skin_is = int(float(gx_gui::skin.gx_current_skin));

	switch (skin_is)
	{
	case 0: // black
		cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.3, 0.6);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 0.6);
		break;
	case 1: // cairo
		cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.3, 0.6);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 0.6);
		break;
	case 2: // default
		cairo_pattern_add_color_stop_rgba (pat, 0, 0.3, 0.2, 0.3, 0.6);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 0.6);
		break;
	case 3: // pix
		cairo_pattern_add_color_stop_rgba (pat, 0, 0.5, 0.02, 0.03, 0.6);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.1, 0.6);
		break;
	case 4: // rainbox
		cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.5, 0.2, 0.6);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.1, 0.05, 0.6);
		break;
	case 5: // sunburst
		cairo_pattern_add_color_stop_rgba (pat, 0, 0.8, 0.2, 0.02, 0.6);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0.2, 0.09, 0.005, 0.6);
		break;
	case 6: // yellow
		cairo_pattern_add_color_stop_rgba (pat, 0, 0.8, 0.3, 0.02, 0.6);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0.2, 0.06, 0.005, 0.6);
		break;
	case 7: // zac
		cairo_pattern_add_color_stop_rgba (pat, 0, 0.8, 0.8, 0.8, 0.6);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0.3, 0.3, 0.3, 0.6);
		break;
	case 8: // zreadable
		cairo_pattern_add_color_stop_rgba (pat, 0, 1, 1, 1, 0.9);
		cairo_pattern_add_color_stop_rgba (pat, 0.8, 0.9, 0.9, 1, 0.9);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0.8, 0.8, 0.9, 0.5);
		break;
	}

}

gboolean rectangle_skin_color_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
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
	gx_skin_color(pat);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
	cairo_fill (cr);

	cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

gboolean conv_widget_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
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

gboolean level_meter_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
{
	cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);
	cairo_set_font_size (cr, 7.0);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+2;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-4;

	int  db_points[] = { -50, -40, -30, -20, -10, -3, 0, 4 };
	char  buf[32];

	cairo_rectangle (cr, x0,y0,rect_width,rect_height+2);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill (cr);

	cairo_pattern_t*pat = cairo_pattern_create_linear (0, y0, 0, y0+rect_height);
		//cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	cairo_pattern_add_color_stop_rgb (pat, 0, 0.1, 0.1, 0.2);
	cairo_pattern_add_color_stop_rgb (pat, 0.3, 0.06, 0.06, 0.07);
	cairo_pattern_add_color_stop_rgb (pat, 1, 0.03, 0.03, 0.03);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-2);
	cairo_fill_preserve (cr);
	
	pat = cairo_pattern_create_linear (x0, 0, x0+rect_width, 0);
	cairo_pattern_add_color_stop_rgba (pat, 0.3, 0.01, 0.01, 0.02, 0.3);
	cairo_pattern_add_color_stop_rgba (pat, 0.5, 0.6, 0.6, 0.7, 0.5);
	cairo_pattern_add_color_stop_rgba (pat, 0.7, 0.01, 0.01, 0.01, 0.3);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-2);
	cairo_fill (cr);

	for (uint32_t i = 0; i < sizeof (db_points)/sizeof (db_points[0]); ++i)
	{
		float fraction = gx_threads::log_meter (db_points[i]);
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

gboolean info_box_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
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
    if(gx_jconv::GxJConvSettings::checkbutton7 == 1) {
        cairo_pattern_add_color_stop_rgba (pat, 0, 0, 0.8, 0, 0.8);
        cairo_pattern_add_color_stop_rgba (pat, 0.5, 0.05, 0.8, 0.05, 0.6);
        cairo_pattern_add_color_stop_rgba (pat, 1, 0.2, 0.8, 0.2, 0.4);
    } else {
        gx_skin_color(pat);
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
    gx_skin_color(pat);
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
}

