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
void gx_skin_color(cairo_pattern_t *pat)
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

//----- paint boxes with cairo -----
gboolean amp_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
{
	cairo_t *cr;
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+2;
	double y0      = wi->allocation.y+2;
	double rect_width  = wi->allocation.width-4;
	double rect_height = wi->allocation.height-4;
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

gboolean upper_widget_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
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

gboolean rectangle_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
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
	gx_skin_color(pat);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
	cairo_fill (cr);

	cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
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

gboolean convolver_icon_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
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
	gx_skin_color(pat);
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

gboolean zac_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
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

gboolean AmpBox_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
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
	gx_skin_color(pat);
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

gboolean tribal_box_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
{
	if (int(float(gx_gui::skin.gx_current_skin)!=1) && int(float(gx_gui::skin.gx_current_skin)<7))
	{
		GdkPixbuf *_image;
		cairo_t *cr;
		/* create a cairo context */
		cr = gdk_cairo_create(wi->window);

		gint x0      = wi->allocation.x+1;
		gint y0      = wi->allocation.y+1;
		gint rect_width  = wi->allocation.width-2;
		gint rect_height = wi->allocation.height-3;

		_image = gdk_pixbuf_scale_simple(tribeimage1,rect_width,rect_height,GDK_INTERP_HYPER);

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

gboolean vbox_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
{
	if (int(float(gx_gui::skin.gx_current_skin)==1))
	{
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
	}
	else if (int(float(gx_gui::skin.gx_current_skin)>=7))
		zac_expose(wi,ev,user_data);

	return FALSE;
}

gboolean filter_box_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
{
	GdkPixbuf *_image;
	cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	gint x0      = wi->allocation.x+1;
	gint y0      = wi->allocation.y+1;
	gint rect_width  = wi->allocation.width-2;
	gint rect_height = wi->allocation.height-3;

	_image = gdk_pixbuf_scale_simple(tribeimage,rect_width,rect_height,GDK_INTERP_HYPER);

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

gboolean boxamp_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
{
    if(!gx_engine::audio.fampexpand) {
		GdkPixbuf *_image;
        cairo_t *cr;
        /* create a cairo context */
        cr = gdk_cairo_create(wi->window);

        gint x0      = wi->allocation.x+1;
        gint y0      = wi->allocation.y;
        gint rect_width  = wi->allocation.width-2;
        gint rect_height = wi->allocation.height;

        _image = gdk_pixbuf_scale_simple(tribeimage2,rect_width,rect_height,GDK_INTERP_HYPER);

        gdk_draw_pixbuf(GDK_DRAWABLE(wi->window), gdk_gc_new(GDK_DRAWABLE(wi->window)),
                        _image, 0, 0,
                        x0, y0, rect_width,rect_height,
                        GDK_RGB_DITHER_NORMAL, 0, 0);

        cairo_destroy(cr);
        g_object_unref(_image);
    }
	return FALSE;
}

gboolean eq_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
{
	//float p = gx_gui::parameter_map["eq.f31_25"].getFloat().value;
    cairo_t *cr;
    cairo_text_extents_t extents;
	/* create a cairo context */
	cr = gdk_cairo_create(wi->window);

	double x0      = wi->allocation.x+1;
	double y0      = wi->allocation.y+1;
	double rect_width  = wi->allocation.width-2;
	double rect_height = wi->allocation.height-3;

	cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
	cairo_pattern_t*pat =
		cairo_pattern_create_radial (x0+200,y0+ rect_height*0.5, 5,x0+800, y0+ rect_height*0.5, 200.0);
	cairo_pattern_add_color_stop_rgb (pat, 0, 0.3, 0.3, 0.3);
	cairo_pattern_add_color_stop_rgb (pat, 0.5, 0.15, 0.15, 0.15);
	cairo_pattern_add_color_stop_rgb (pat, 1, 0.1, 0.1, 0.1);
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
    
    const gchar * title = "faust";
    cairo_select_font_face (cr, "sans", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (cr, 10);
	cairo_text_extents (cr,title , &extents);
	double x = x0+rect_width-extents.height - 3 ;
	double y = y0+rect_height*0.9+extents.height/2 - 3;
	cairo_move_to(cr,x, y);
	cairo_rotate (cr,270* M_PI/180);
	cairo_text_path (cr,title);
	cairo_set_source_rgb (cr, 0.3, 0.3, 0.3);
    cairo_fill (cr);

	cairo_pattern_destroy (pat);
	cairo_destroy(cr);

	return FALSE;
}

gboolean plug_box_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
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
	gx_skin_color(pat);
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

gboolean slooper_expose(GtkWidget *wi, GdkEventExpose *ev, gpointer user_data)
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
	gx_skin_color(pat);
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

void gx_init_pixmaps()
{
	/* XPM */
	static const char * tribe_xpm[] =
		{
			"200 129 3 1",
			" 	c None",
			".	c #194C4C",
			"+	c #194E4E",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                           .+           ",
			"                                                                                                                                                                                           ++           ",
			"                                                                                                                                                                                           ++           ",
			"                                                                                                                                                                                           ..           ",
			"                                                                                                                                                                                          +++           ",
			"                                                                                                                                                                                          +.+           ",
			"                                                                                                                                                                                         +.+.           ",
			"                                                                                                                                                                                         ++.+           ",
			"                                                                                                                                                                                        ++ +.           ",
			"                                                                                                                                                                                        +  +            ",
			"                                                                                                                                                                                       .  ++            ",
			"                                                                                                                                                                                      +.  +.            ",
			"                                                                                                                                                                                     ..  +.             ",
			"                                                                                                                                                                                    +.  +++             ",
			"                                                                                                                                                                            ++    ++    ...             ",
			"                                                                                                                                                                             +  +.+    .+.              ",
			"                                                                                                                                                                             .+ ...   .... +            ",
			"                                                                                                                                                                              . .++..+.++ .+            ",
			"                                                                                                                                                                              ++ .. ..++  .             ",
			"                                                                                                                                                                            . .. ..++.+  .              ",
			"                                                                                                                                                                            . ++  .    .++              ",
			"                                                                                                                                                                           .+ .++  +.+...               ",
			"                                                                                                                                                                           +. ... .  +.                 ",
			"                                                                                                                                                                           .. .++ . ..                  ",
			"                                                                                                                                                                          +.  +++ ..                    ",
			"                                                                                                                                                                         .+.  .+.                       ",
			"                                                                                                                                                                         +.. ++..                       ",
			"                                                                                                                                                        .               . .. .++.                       ",
			"                                                                                                                                                         +             +  .  ++.                        ",
			"                                                                                                                               .                          +.         ++  .. .+                          ",
			"                                                                                                                              .                            ++       ++   +  +                           ",
			"                                                                                                                             .                             +..     +.   .+                              ",
			"                                                                                                                            .+ .                            ++.  ..    .+                               ",
			"                                                                                                                           ++ .                              +.. ++    +                                ",
			"                                                                                                                          +++ .                            . .+.+ +.  .+                                ",
			"                                                                                                                         .+. .+                            +  .... ..++                                 ",
			"                                                                                                                         +.+ ++                            +. .+.+ ++.                                  ",
			"                                                                                                                        .++ .+                             .+ ..++. +                                   ",
			"                                                                                                                       +... ..                             ++ .++.++                                    ",
			"                                                                                                                       +.++ +.                             +.  +++..                                    ",
			"                                                                                                                      .++.  ++                             ..  .+++.+                                   ",
			"                                                                                                                     ..+++ .++.                +           ..  .+.+..                                   ",
			"                                                                                                                     .+++. .+++               ++           ..  .++                                      ",
			"                                                                                                                     ...++ .++.              +..          +.+  ..                                       ",
			"                                                                                                                      +... +++.              ...          +++ ..                                        ",
			"                                                                                                                       +.. +++.+            +..+         ...  .                                         ",
			"                                                                                                                        .  +++++            +..+        .+..                                            ",
			"                                                                                                                         + +++.++           .+++     ++.+.+.                                            ",
			"                                                                                                                .          +++++.           +++..    ++++..                                             ",
			"                                                                                                                .          ++++.++          ++++. +++ +.+..                                             ",
			"                                                                                                               .. .        ++++...         +.+.+. +... ..+                                              ",
			"                                                                                                               +..+        +++++++.        +..++ ++++++                                                 ",
			"                                                                                                              ...+++       +.+++++..       +++ +.++++.++                                                ",
			"                                                                                                              ..+.++        ..++++..+      ++++.+++.+..+                                                ",
			"                                                                                                              .+. .++       .++++....     +.+..++++..+                                                  ",
			"                                                                                               .+.+           .+. .+++      +++.... .+ .  ++.++++.++..+..                                               ",
			"                                                                       +  +...+..             +.   ++...        + .+...      .+++.  ....+.  .++.+.++..+.+.++++++.+.                                     ",
			"                                                                             .+++..++..+        ..   .+...      + .++++.      .+   .+ ..+..  .++++.++++++.++.+.++                                       ",
			"                                                                       +..++       .+.+..         ++++  +++       +.+++.+.     ++++.  .++..+  ++.+...+     ...                                          ",
			"                                                                            +++...+    +..          ....  .+      ++++++++.      .   +..++.+.  +++  .                                                   ",
			"                                                                              +.+..+...   +.         .+.+. .+      .+++++++     +++++++++++..+  ++                                                      ",
			"                                                                                 ..+.+..+             ..++.+ +      .++++.+.    ..+++++++++++..                                                         ",
			"                                                      +                            .+.+.+++           ++.++++       ..++++..  .  +.+.+++......+.                                                        ",
			"                                                       ...  .+.+                    +.++.+..+          +..++.+       .++..+. .++.  ..+.+. ++++.                                                         ",
			"                                                         ++.   +..+                   .++ ..+.+         +.+++.+       .+.+.  ++++.  +++..+   ++                                                         ",
			"                                                           +..  .....                  ..+ +..++.        +.++...        +   .++...+  ..++  ....+.                                                       ",
			"                                                            ++.   .+.++                 ..++.+.++.       .+++++++     +.  ....++...   .+. +......+                                                      ",
			"                                                             ++.+  +..+++                ++.  .+..+       +.+++..     +...++++++.+..   . .+  +.+..+                                                     ",
			"                                                              ..++  ++.++.                +.+..+++.+      +++++.. ..+  +++++.++.+++.+     +  ....++..                                                   ",
			"                                                      +        .++++  +..+.+              ++.++++++++      .++.+  ..++  +++++. .+++++     ..  +.+..+.+..                                                ",
			"                                            +        +.         .+...  ..++.+              +.++++++..       ...  +.+...  .+++.+.           .+   ..+++.+.+..                                             ",
			"                                           .         +.       .  ++++.  +..+                .++++++++     .+    ...+++.   +++.+ .+++         ++    .++.++++++.                                          ",
			"                                          +.         .+        .  ++..+  .+                 +.++++...     ++....++++++.+  +++. +..+..         ....+    .+..++++...+.+..++.+  +                          ",
			"                                          .          ..         . ....++  +                  .++..++. +.  .+++++++++++.++  ... +++++.+           ++.+...+  ..+..++.+.....  ++                           ",
			"                                         +.          ..+        +. +...++ ++                  ...++  ....  ...++++++++++.   .. .++++.+.               ..+.++..+++.+++   +.+                             ",
			"                                         +.          ..+         + .++ ++                    .      ..+++.  .+++++++++++..     .+.+++.++              +.          ++++....                              ",
			"                                         +.        + ...+        ++ .+  ..                  +++.++.++..+.+. ++.++..++.+..+      +.+++++.+              ..++.....+..+...                                 ",
			"                                         +.        + ...+  .      + .+   +.              ++  .+.+.++.++++.+  ......+    .        +..+++.++              ............                                    ",
			"                                         ..        .  .+..  .     +. ++   ++            +++. ..+++++++++++.  +.+.+   ..            +++...+..             ..+.+.+..                                      ",
			"                                      .  .+        +  +....  +    +. +.   ..            ...+  ++++++++++++..  +++. ++++.+           .++.+.++.+            ..++                                          ",
			"                                      .  +..       +.  .....  +.   +  +    .+  ...    +..++.. .+++++++++++..   ..  .+++.+             + .  ..+++++                                                      ",
			"                                      +  .+.        ++ ..++++  ..  .. +.   .+  ..+..++..+++.+  +.++++++++++.+      .+++++.             .+++.  +                                                         ",
			"                                      +  ...        ..  .+...+  ..+.. ..    ..  ..+++.++++++.  ....+ +...+..+      ++++++.              ++...+.+...                                                     ",
			"                                      .. +..+  .  +.+++ ...+....  +++ ..   +.+  +.++++++++++++  +++++.    ...       +..+++                                                                              ",
			"                             +        +.  .++. ..   +++. ++.++++.   .  ++..++.  +..++++.+...++  .++..  ..+           ..+++..                                                                            ",
			"                              ++       .  .+++.  ++    .   ++...++.    ..        ++++.+++...++  .+.. ..+....         ...+.+                                                                             ",
			"                              +..+     +.  +.+++  +.++++    ...+++.       ..+    +.+..    +.+..  +. ++.   ..+         +.++. +                                                                           ",
			"                               ...+.+. ..  ++...+   +..+++         +..+ +++   .  +++.+...++.+++     ..     ..         .+++. +.                                                                          ",
			"                                +++...  ..  ...+...  +.+.+ .++++. .+...    +....  +.+.+     +++     ..     +.+        ++++. ..                                                                          ",
			"                                 .++.+  .+   +++++..   +.  +.++.+. ...   +....+.  ...               +.+     ..         ..+. ..                                                                          ",
			"                                  ..+    ++   .+.+.++.    +..++++  ..   +.+   +.  .++                .+     .+         +++. .+                                                                          ",
			"                                     ... +.+   ++.+++..    ....  ++++   +++    +.  .+                ...    .+         ...+ +.                                                                          ",
			"                                    +.++  ...   .++++.+ .++    +..+.  +. +.    .+                     ++ +  +.          +.++.                                                                           ",
			"                                  +++.+.+  ..+  ..+++.  ..+.  .+.+.+ +++ +..   +.                     .++..+++          .. ..                                                                           ",
			"                                ...+++++.. +.+  .+++.+ ...+   ++++.  .+++ .++  ++                      .+..++.          ++ +                                                                            ",
			"                              ...+++++++.+  ..  ..+++  +++    .++++ +. .++ ++  .+                      +.+++++          .. +                                                                            ",
			"                             ...++++++++++  .+  .++++ ++.  .  +++.  ++  .. +.+ +.+ +                   .++++.           . +                                                                             ",
			"                       ++  ...+.++++++++++  +. +.++.. ..  ++  +++.  +    +. +..++. ++                  .++++. ..        + .                                                                             ",
			"                     .++  ++..+++.+..++.++  +. +.++++ ++ +.+  ++++  +    +. ++.++. .+                  ..+++. +.                                                                                        ",
			"                  + ++.  +++.+..+++.    ..  +. ..+++.++  . .  ++++  +     +  ++++. +.+                 +.+.+. +.         +                                                                              ",
			"                 ..++.  ++.+..+         .+  .+  .+++.++ +  ++ +.+.  +     +. .+++. +...+               ..+..  +..                                                                                       ",
			"                ...+.  +..++           +..+ +.  .+++ +.    .. ..+.  +      . +..++ ++.++               ....+ ...                                                                                        ",
			"               .++++  ....            +.+.+  +  +.++. .     +  +.++ .      . ....  ++++                +..+  ..                                                                                         ",
			"               +.+. ...+              .+.+   +.  +..+       +. ++.. +         +.+  ++..                +++. +..                                                                                         ",
			"               .++  ..                +..     .  .+++        +  +..  +        +.+  +.+                 ..+. +.                                                                                          ",
			"              .... ++                 +.+     +.  +...        .  ..+          +++  +..                .+.. .+.                                                                                          ",
			"              +.. ++                  ..+      .  ...+         +  ++.         ++. +++                 ++.  ++                                                                                           ",
			"               + +                    ++       ++  +...         .  .+         +.+ ..+                 ... ..                                                                                            ",
			"              +.                       ++       .. .+.+             ..        +.  ++                 .++ .+                                                                                             ",
			"              .                        ++        .  ..+.             +.       ++  ..                 +.  .                                                                                              ",
			"              .                         +         .  ++++             +.      +. .+                 +.  .                                                                                               ",
			"             .                                         +..                   +.  .+                 .  .                                                                                                ",
			"                                                         +.                  +.  +                 +  +                                                                                                 ",
			"                                                           ++.               .  +                                                                                                                       ",
			"                                                                             .                                                                                                                          ",
			"                                                                            +                                                                                                                           ",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                                        ",
			"                                                                                                                                                                                                        "};

/* XPM */
	static const char * guitar_xpm[] = {
		"65 20 3 1",
		" 	c None",
		".	c #353535",
		"+	c #343434",
		"                                                                 ",
		"                                                                 ",
		"                                                                 ",
		"                                                                 ",
		"                          .           +                          ",
		"                    ..  ++.+++     .   ...++                     ",
		"                    . ++.    +     + +  +.+                      ",
		"   +                 ++  .+ .+     +. +.  ..+                ++  ",
		"  +..    .+        . ++  .+. +       +..  +. .         +    ++.+ ",
		" +   +    .         .   +  .+       +.      +  .      .+   ..  + ",
		" +       +.   .   .  .  +  +.++    .++. +.    +   +.   +    .  + ",
		" ++   .. . +++++.   +  ++.... .   + .++.+   .   ....... ++.   +. ",
		"   + ++ +..+++.++. +      ..          +       . + +.++.++  .+.   ",
		"   .  .+                                                     .   ",
		"   +..                                                      ++   ",
		"   +.                                                        .   ",
		"                                                                 ",
		"                                                                 ",
		"                                                                 ",
		"                                                                 "};

	/* XPM */
	static const char * skull_xpm[] = {
"240 30 26 1",
" 	c None",
".	c #562334",
"+	c #4A2B64",
"@	c #4A2E7F",
"#	c #4C383C",
"$	c #4A3D68",
"%	c #69399B",
"&	c #673FAC",
"*	c #5A4B9B",
"=	c #6A4988",
"-	c #4E5297",
";	c #505BC3",
">	c #67618D",
",	c #6D636A",
"'	c #59748A",
")	c #5875B8",
"!	c #5078D0",
"~	c #5A7AA5",
"{	c #54857C",
"]	c #6D8266",
"^	c #8C7C4D",
"/	c #837E69",
"(	c #549070",
"_	c #8C7F81",
":	c #788F56",
"<	c #5DA961",
"                                                                                                                                                                                                                                                ",
"                                                                                                                                                                                                                                                ",
"                                                                                                                                                                                                                                                ",
"                                                                                                                                                                                                                                                ",
"                                                                                                                    .+$--           @*%%==                                     ......+$                                                         ",
"                                                                                                                    ++$*;           *%%%%                                     @+....++                                                =...#     ",
"                                                                                                                    +$$*;           %%%%=                                    +@++++++$                                                *=..#     ",
"                                                                                                                    +++=*           %%%==                                    ++++++                                                   >=>.#     ",
"                                                                                                                   ==+++=          %%===>                                    +++++                                                   ##,>..     ",
"      =>>>>>>'{]]:        /:_=.,$=     ,>.##  +++=*   *==**     %%%%===>>     {]]:::]'',    _=.,$=$##      #+++++=*****=           %===> >>>>'{]  ::]''    :_=.,$         ##+++++=*****==******%     ==>>>>   {]]::     ,]/:_=.,$= ##_,,>.##+   ",
"      ->~>>>>']_/],     /]]:_=.$%%$    _,.#$  ++***  --*+=;    ***@@**->~>    ]_/],]]',,   :_=.$%%$##,    #$++++*****--*           @**->~>>>>']_/ ,]]',    :_=.$%         #$++++*****--*+=;;*****    *->~>    ]_/],   ,,/]]:_=.$%% ##,__,.#$+   ",
"      ~''''''{]>//>    ,/]^:_=#,=%$$   .##$+ +++*--  --*==;  --****---~''''   ]>//>,'',, ]^:_=#,=%$$###  #$+++++*------*           ---~''''''{]>/  ,'',    :_=#,          $+++++*------*==;;;--**    -~'''    ]>//>   ,,/]^:_=#,=% $###.##$++   ",
"      >''''''{]>_:,    /^^^:_=:<,&=+   ##$++ @@**-* *--*=*   ;;---->>>>''''   ]>_:,,,,,/ ^^:_=:<,&=+$##  $++@@@**-*;*--*           >>>>''''''{]>_  ,,,,/  ^:_=:<            @@@**    --*=*;!;;;--    >>'''    ]>_:,   ,/^^^:_=:<,&   ####$      ",
"     >~'''{   ]__/:   ::^^^:   <,=&+   $++@@ @@@--; *--*=*  ;;;;--    ~'''{  ']__/:     ^^^:_,    &++++ ++@@@@    ;**--           >>>>~''   {']__  ^^^::  ^:_,<            @@@@@-           ;;;;-   >>~'''   ']__/:   ::^^^:_,<     +++$++      ",
"     )~~~''   {]__^   ::^^:    :<=%&   @@@@@@=@@@*;******   ;;;;;;!!))~~~''  {{]__^     ^^::>]<:<=%&+@@ @@@@@     ;****           !!))~~    {{{]_  /^::: ^::>]<            @@=@@     *****;;;;;;;   ))~~~    {{]__    ::^^::>]<:<   +@@@@       ",
"     ;;!))    {(:/,   ::^^:    ::{*%   @%@='''>=%****===*   ;;;;;;;;;;;!))~  ({(:/      ^^:/,::::{*%&@@ %@=''     ***==           ;;;;;     {({(:  ^:::: ^:/,:             '''>=    *===*&;;;;;;;   ;;;!)    ({(:/    ::^^:/,::::   &@@@%       ",
"     ;;;!!    ({{::   _:::]    :::-%   %%$''==> =@*;****    *;;;;;;;;;;;!!)  {({{:      ::]>]].:::-%*&& %$''=    @*;***           ;;;;;     '{({{   ,$_:::]>]              '==>>   ;****;;***;;;;   ;;;;!   '{({{:     :::]>]].::   *&&%%       ",
"     !!!!!   '{{{(:   #>__>   #:]]-%   @=>'-*** >@*);;*-    !;;!;           ~'{{{(      __>/:           =>'-*   >@*);;*          ;;!!!!    )~'{{{   ^$#>__>/:              -***>   );;*-)) -!;;!;   !!!!!   ~'{{{(        >/:/#:]   *&*@=       ",
"    ~~~~~)!!)~'({((   /,,,::^^]:_/*    =>'>@=*  >@-))))     ~>)!;;!)~~~~~)  )~'({       ,,::^^]:_/*&*;  >'>@=**=>@-)))           ;!)~~~~~)!!)~'(    ^_/,,,::              >@=**=   ))))~'~>~~>)!;   ~~~~~)!!)~'({    _/,,,::^^]:_   *;*=>'      ",
"    {{{{''~!))'{{(    /]:<:^/::/_,%    >>'>@-*  >@---)~     )~~)!;!~{{{{''  ))'{{       :<:^/::/_,%%&;  >'>@-***>@---)           ;!~{{{{''~!))'{    :^/]:<:^              >@-**    --)~~~))))~~)    {{{{''~!))'{{   :^/]:<:^/::/_   &;*>>'>@    ",
"    ((]{{'~))!'{{      /,,,////__>     >,,>@=-  **---~       !)~!!!~((]{{'  )!'{{        ,,////__>%%*;  ,,>@=-->**---~           !!~((]{{'~))!'      ::/,,,               >@=--    --~~~)))!!!)~    ((]{{'~))!'{{   <::/,,,////__   *;*>,,>@    ",
"    ({'''~~))~{{        //_,___/       ,,,>**   @*-->'        )~)!!'({'''~  )~{{(         _,___/_,*&*;   ,>**==*@*-->'           !!'({'''~~))~       <<://                >**==     >'~)))!!!!)~    ({'''~~))~{{(   <<<://_,___     *;-,,,>*    ",
"   {('~~~                                                                                                                                            <<<]/                                                                                      ",
"   (<{'~                                                                                                                                           <<<<<:                                                                                       ",
"   <<<((                                                                                                                                         (<<(<<<:                                                                                       ",
"   <<<<<                                                                                                                                         <<<<<<<                                                                                        ",
"   ({((<                                                                                                                                         <<<<<<                                                                                         ",
"                                                                                                                                                                                                                                                ",
"                                                                                                                                                                                                                                                ",
"                                                                                                                                                                                                                                                "};


	tribeimage = gdk_pixbuf_new_from_xpm_data(tribe_xpm);
	tribeimage1 = gdk_pixbuf_new_from_xpm_data(guitar_xpm);
	tribeimage2 = gdk_pixbuf_new_from_xpm_data(skull_xpm);
}

}
