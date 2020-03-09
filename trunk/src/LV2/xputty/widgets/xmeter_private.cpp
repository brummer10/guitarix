/*
 *                           0BSD 
 * 
 *                    BSD Zero Clause License
 * 
 *  Copyright (c) 2019 Hermann Meyer
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 */


#include "xmeter_private.h"


void _draw_vmeter_scale(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    XWindowAttributes attrs;
    XGetWindowAttributes(w->app->dpy, (Window)w->widget, &attrs);
    int rect_width = attrs.width;
    int rect_height = attrs.height;
    double x0      = 0;
    double y0      = 0;

    int  db_points[] = { -50, -40, -30, -20, -15, -10, -6, -3, 0, 3 };
    //int  db_points[] = { -50, -40, -30, -20, -10, -3, 0, 4 };
    char  buf[32];

    cairo_set_font_size (w->crb, (float)rect_width/2);
    cairo_select_font_face(w->crb, "Sans", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_source_rgb(w->crb, 0.8, 0.8, 0.8);

    for (unsigned int i = 0; i < sizeof (db_points)/sizeof (db_points[0]); ++i)
    {
        float fraction = _log_meter((double)db_points[i]);
        cairo_move_to (w->crb, 0,y0+rect_height - (rect_height * fraction));
        cairo_line_to (w->crb, x0+rect_width-3 ,y0+rect_height -  (rect_height * fraction));
        if (i<6)
        {
            snprintf (buf, sizeof (buf), "%d", db_points[i]);
            cairo_move_to (w->crb, x0+rect_width*0.1,y0+rect_height - (rect_height * fraction)-3);
        }
        else if (i<8)
        {
            snprintf (buf, sizeof (buf), "%d", db_points[i]);
            cairo_move_to (w->crb, x0+rect_width*0.2,y0+rect_height - (rect_height * fraction)-3);
        }
        else
        {
            snprintf (buf, sizeof (buf), " %d", db_points[i]);
            cairo_move_to (w->crb, x0+rect_width*0.21,y0+rect_height - (rect_height * fraction)-3);
        }
        cairo_show_text (w->crb, buf);
    }

    cairo_set_source_rgb(w->crb, 0.6, 0.6, 0.6);
    cairo_set_line_width(w->crb, 2.0);
    cairo_stroke(w->crb);
}

void _draw_hmeter_scale(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    XWindowAttributes attrs;
    XGetWindowAttributes(w->app->dpy, (Window)w->widget, &attrs);
    int rect_width = attrs.width;
    int rect_height = attrs.height;
	double x0      = 0;
	double y0      = 0;

    int  db_points[] = { -50, -40, -30, -20, -15, -10, -6, -3, 0, 3 };
	char  buf[32];

	cairo_set_font_size (w->crb, (float)rect_height/2);
	cairo_select_font_face(w->crb, "Sans", CAIRO_FONT_SLANT_NORMAL,
							   CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_source_rgba(w->crb, 0.6, 0.6, 0.6, 0.6);

	for (unsigned int i = 0; i < sizeof (db_points)/sizeof (db_points[0]); ++i)
	{
		float fraction = _log_meter(db_points[i]);
		//cairo_set_source_rgb (w->crb,0.32 + 0.22*i/2,0.5 +  0.1*i/2, 0.1);

		cairo_move_to (w->crb, x0+(rect_width * fraction),y0+rect_height*0.1);
		cairo_line_to (w->crb, x0+(rect_width * fraction) ,y0+rect_height*0.6);
		if (i<6)
		{
			snprintf (buf, sizeof (buf), "%d", db_points[i]);
			cairo_move_to (w->crb, x0+(rect_width * fraction)+3,y0+rect_height);
		}
		else
		{
			snprintf (buf, sizeof (buf), " %d", db_points[i]);
			cairo_move_to (w->crb, x0+(rect_width * fraction)+3,y0+rect_height );
		}
		cairo_show_text (w->crb, buf);
	}

	cairo_set_source_rgba(w->crb, 0.6, 0.6, 0.6, 0.6);
	cairo_set_line_width(w->crb, 1.5);
	cairo_stroke(w->crb);
}

float _log_meter (float db) {
    float def = 0.0f; /* Meter deflection %age */

    if (db < -70.0f) {
        def = 0.0f;
    } else if (db < -60.0f) {
        def = (db + 70.0f) * 0.25f;
    } else if (db < -50.0f) {
        def = (db + 60.0f) * 0.5f + 2.5f;
    } else if (db < -40.0f) {
        def = (db + 50.0f) * 0.75f + 7.5f;
    } else if (db < -30.0f) {
        def = (db + 40.0f) * 1.5f + 15.0f;
    } else if (db < -20.0f) {
        def = (db + 30.0f) * 2.0f + 30.0f;
    } else if (db < 6.0f) {
        def = (db + 20.0f) * 2.5f + 50.0f;
    } else {
        def = 115.0f;
    }

    /* 115 is the deflection %age that would be
       when db=6.0. this is an arbitrary
       endpoint for our scaling.
    */

    return def/115.0f;
}

void _create_vertical_meter_image(Widget_t *w, int width, int height) {
    w->image = cairo_surface_create_similar (w->surface, 
                        CAIRO_CONTENT_COLOR_ALPHA, width*2, height);
    cairo_t *cri = cairo_create (w->image);

    cairo_rectangle(cri,0.0, 0.0, width, height);
    use_shadow_color_scheme(w, NORMAL_);
    cairo_fill(cri);

    cairo_rectangle(cri,width, 0.0, width, height);
    use_shadow_color_scheme(w, NORMAL_);
    cairo_fill(cri);

    cairo_pattern_t *pat = cairo_pattern_create_linear (0, 0, 0.0, height);
    cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.1, 0.5, 0.1, 0.4);
    cairo_pattern_add_color_stop_rgba(pat, 0.2, 0.4, 0.4, 0.1, 0.4);
    cairo_pattern_add_color_stop_rgba(pat, 0.0, 0.5, 0.0, 0.0, 0.4);
    cairo_set_source(cri, pat);

    int c = (width)/2 ;
    int ci = c-2;

    int i = 1;
    int j = 1;
    for(;i<height-3;) {
        for(;j<width;) {
            cairo_rectangle(cri,j,i,ci,2);
            cairo_fill(cri);
            j +=c;
        }
        i +=3;
        j = 1;
    }

    cairo_pattern_destroy (pat);
    pat = cairo_pattern_create_linear (0, 0, 0.0, height);
    cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.1, 0.5, 0.1, 1);
    cairo_pattern_add_color_stop_rgba(pat, 0.2, 0.4, 0.4, 0.1, 1);
    cairo_pattern_add_color_stop_rgba(pat, 0.0, 0.5, 0.0, 0.0, 1);
    cairo_set_source(cri, pat);
    i = 1;
    j = 1;
    for(;i<height-3;) {
        for(;j<width;) {
            cairo_rectangle(cri,width+j,i,ci,2);
            cairo_fill(cri);
            j +=c;
        }
        i +=3;
        j = 1;
    }

    cairo_pattern_destroy (pat);
    cairo_destroy(cri);
}

void _create_horizontal_meter_image(Widget_t *w, int width, int height) {
    w->image = cairo_surface_create_similar (w->surface, 
                        CAIRO_CONTENT_COLOR_ALPHA, width, height*2);
    cairo_t *cri = cairo_create (w->image);

    cairo_rectangle(cri,0.0, 0.0, width, height);
    use_shadow_color_scheme(w, NORMAL_);
    cairo_fill(cri);

    cairo_rectangle(cri, 0.0, height, width, height);
    use_shadow_color_scheme(w, NORMAL_);
    cairo_fill(cri);

    cairo_pattern_t *pat = cairo_pattern_create_linear (0, 0, width, 0.0);
    cairo_pattern_add_color_stop_rgba(pat, 0.0, 0.1, 0.5, 0.1, 0.4);
    cairo_pattern_add_color_stop_rgba(pat, 0.8, 0.4, 0.4, 0.1, 0.4);
    cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.5, 0.0, 0.0, 0.4);
    cairo_set_source(cri, pat);

    int c = (height)/2 ;
    int ci = c-2;

    int i = 1;
    int j = 1;
    for(;i<width;) {
        for(;j<height;) {
            cairo_rectangle(cri,i,j,2,ci);
            cairo_fill(cri);
            j +=c;
        }
        i +=3;
        j = 1;
    }

    cairo_pattern_destroy (pat);
    pat = cairo_pattern_create_linear (0, 0, width, 0.0);
    cairo_pattern_add_color_stop_rgba(pat, 0.0, 0.1, 0.5, 0.1, 1);
    cairo_pattern_add_color_stop_rgba(pat, 0.8, 0.4, 0.4, 0.1, 1);
    cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.5, 0.0, 0.0, 1);
    cairo_set_source(cri, pat);
    i = 1;
    j = 1;
    for(;i<width;) {
        for(;j<height;) {
            cairo_rectangle(cri,i,height+j,2,ci);
            cairo_fill(cri);
            j +=c;
        }
        i +=3;
        j = 1;
    }

    cairo_pattern_destroy (pat);
    cairo_destroy(cri);
}

void _draw_v_meter(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;

    int width = cairo_xlib_surface_get_width(w->image);
    int height = cairo_xlib_surface_get_height(w->image);
    double meterstate = _log_meter(adj_get_value(w->adj_y));
    double oldstate = _log_meter(w->adj_y->start_value);
    widget_set_scale(w);
    cairo_set_source_surface (w->crb, w->image, 0, 0);
    cairo_rectangle(w->crb,0, 0, width/2, height);
    cairo_fill(w->crb);
    cairo_set_source_surface (w->crb, w->image, -width/2, 0);
    cairo_rectangle(w->crb, 0, height, width/2, -height*meterstate);
    cairo_fill(w->crb);

    cairo_rectangle(w->crb, 0, height-height*oldstate, width/2, 3);
    cairo_fill(w->crb);
    widget_reset_scale(w);
}

void _draw_h_meter(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;

    int width = cairo_xlib_surface_get_width(w->image);
    int height = cairo_xlib_surface_get_height(w->image);
    double meterstate = _log_meter(adj_get_value(w->adj_x));
    double oldstate = _log_meter(w->adj_x->start_value);
    widget_set_scale(w);
    cairo_set_source_surface (w->crb, w->image, 0, 0);
    cairo_rectangle(w->crb,0, 0, width, height/2);
    cairo_fill(w->crb);
    cairo_set_source_surface (w->crb, w->image, 0, -height/2);
    cairo_rectangle(w->crb, 0, 0, width*meterstate, height/2);
    cairo_fill(w->crb);

    cairo_rectangle(w->crb,(width*oldstate)-3, 0, 3, height/2);
    cairo_fill(w->crb);

    widget_reset_scale(w);
}
