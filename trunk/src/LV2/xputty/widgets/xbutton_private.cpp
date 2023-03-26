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


#include "xbutton_private.h"


void _rounded_rectangle(cairo_t *cr,float x, float y, float width, float height) {
	cairo_new_path (cr);
	cairo_move_to  (cr, x, (y + height)/2);
	cairo_curve_to (cr, x ,y, x, y, (x + width)/2, y);
	cairo_curve_to (cr, width, y, width, y, width, (y + height)/2);
	cairo_curve_to (cr, width, height, width, height, (width + x)/2, height);
	cairo_curve_to (cr, x, height, x, height, x, (y + height)/2);
	cairo_close_path (cr);
}

void _pattern_out(Widget_t *w, Color_state st, int height) {
    Colors *c = get_color_scheme(w->app,st);
    if (!c) return;
    cairo_pattern_t *pat = cairo_pattern_create_linear (2, 2, 2, height);
    cairo_pattern_add_color_stop_rgba(pat, 0.0, c->light[0],  c->light[1], c->light[2],  c->light[3]);
    cairo_pattern_add_color_stop_rgba(pat, 0.5, 0.0, 0.0, 0.0, 0.0);
    cairo_pattern_add_color_stop_rgba(pat, 1.0, c->light[0],  c->light[1], c->light[2],  c->light[3]);
    cairo_set_source(w->crb, pat);
    cairo_pattern_destroy (pat);
}

void _pattern_in(Widget_t *w, Color_state st, int height) {
    Colors *c = get_color_scheme(w->app,st);
    if (!c) return;
    cairo_pattern_t *pat = cairo_pattern_create_linear (2, 2, 2, height);
    cairo_pattern_add_color_stop_rgba(pat, 0.0, 0.0, 0.0, 0.0, 0.0);
    cairo_pattern_add_color_stop_rgba(pat, 0.5, c->light[0],  c->light[1], c->light[2],  c->light[3]);
    cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.0, 0.0, 0.0, 0.0);
    cairo_set_source(w->crb, pat);
    cairo_pattern_destroy (pat);
}

void _draw_image_button(Widget_t *w, int width_t, int height_t, float offset) {
    int width = cairo_xlib_surface_get_width(w->image);
    int height = cairo_xlib_surface_get_height(w->image);
    double half_width = (width/height >=2) ? width*0.5 : width;
    double x = (double)width_t/(double)(half_width);
    double y = (double)height_t/(double)height;
    double x1 = (double)height/(double)height_t;
    double y1 = (double)(half_width)/(double)width_t;
    double off_set = offset*x1;
    double buttonstate = adj_get_state(w->adj);
    int findex = (int)(((width/height)-1) * buttonstate) * (width/height >=2);
    cairo_scale(w->crb, x,y);
    cairo_set_source_surface (w->crb, w->image, -height*findex+off_set, off_set);
    cairo_rectangle(w->crb,0, 0, height, height);
    cairo_fill(w->crb);
    cairo_scale(w->crb, x1,y1);
}

void _draw_image_button_with_label(Widget_t *w, int width_t, int height_t) {
    int width = cairo_xlib_surface_get_width(w->image);
    int height = cairo_xlib_surface_get_height(w->image);
    double x = (double)width_t/(double)height;
    double y = (double)height/(double)width_t;
    double buttonstate = adj_get_state(w->adj);
    int findex = (int)(((width/height)-1) * buttonstate);
    cairo_scale(w->crb, x,x);
    cairo_set_source_surface (w->crb, w->image, -height*findex, 0);
    cairo_rectangle(w->crb,0, 0, height, height);
    cairo_fill(w->crb);
    cairo_scale(w->crb, y,y);
    cairo_text_extents_t extents;
    if(w->state==0) {
        use_fg_color_scheme(w, NORMAL_);
    } else if(w->state==1 && ! (int)w->adj_y->value) {
        use_fg_color_scheme(w, PRELIGHT_);
    } else if(w->state==1) {
        use_fg_color_scheme(w, ACTIVE_);
    } else if(w->state==2) {
        use_fg_color_scheme(w, SELECTED_);
    } else if(w->state==3) {
        use_fg_color_scheme(w, ACTIVE_);
    }

    use_text_color_scheme(w, get_color_state(w));
    cairo_set_font_size (w->crb,w->app->normal_font/w->scale.ascale);
    if ((int)adj_get_value(w->adj) && strlen(w->input_label)) {
        cairo_text_extents(w->crb,w->input_label , &extents);
        cairo_move_to (w->crb, (width_t*0.5)-(extents.width/2), height_t-(extents.height/4));
        cairo_show_text(w->crb, w->input_label);
    } else {
        cairo_text_extents(w->crb,w->label , &extents);
        cairo_move_to (w->crb, (width_t*0.5)-(extents.width/2), height_t-(extents.height/4));
        cairo_show_text(w->crb, w->label);
    }
    cairo_new_path (w->crb);
}

void _draw_switch_image_button(void *w_, void* user_data) {
    Metrics_t m;
    int width, height;
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    os_get_window_metrics(w, &m);
    width = m.width-2;
    height = m.height-2;
    if (!m.visible) return;
    if(strlen(w->label)) {
        _draw_image_button_with_label(w, width, height);
    } else {
        _draw_image_button(w, width, height,0.0);
    }
}

void _draw_button_base(Widget_t *w, int width, int height) {
    if (!w->state && (int)w->adj_y->value) {
        w->state = 3;
    } else if (w->state == 3 && !(int)w->adj_y->value) {
        w->state = 0;
    }

    _rounded_rectangle(w->crb,1.0, 1.0, width+1.0, height+1.0);
    cairo_set_source_rgb (w->crb, 0.0, 0.0, 0.0); 
    cairo_set_line_width(w->crb,1);
    cairo_stroke(w->crb);

    _rounded_rectangle(w->crb,2.0, 2.0, width, height);

    if(w->state==0) {
        cairo_set_line_width(w->crb, 1.0);
        _pattern_out(w, NORMAL_, height);
        cairo_fill_preserve(w->crb);
        use_frame_color_scheme(w, PRELIGHT_);
    } else if(w->state==1) {
        _pattern_out(w, PRELIGHT_, height);
        cairo_fill_preserve(w->crb);
        cairo_set_line_width(w->crb, 1.5);
        use_frame_color_scheme(w, PRELIGHT_);
    } else if(w->state==2) {
        _pattern_in(w, SELECTED_, height);
        cairo_fill_preserve(w->crb);
        cairo_set_line_width(w->crb, 1.0);
        use_frame_color_scheme(w, PRELIGHT_);
    } else if(w->state==3) {
        _pattern_in(w, ACTIVE_, height);
        cairo_fill_preserve(w->crb);
        cairo_set_line_width(w->crb, 1.0);
        use_frame_color_scheme(w, PRELIGHT_);
    }
    cairo_stroke(w->crb);

    if(w->state==2) {
        _rounded_rectangle(w->crb,4.0, 4.0, width, height);
        cairo_stroke(w->crb);
        _rounded_rectangle(w->crb,3.0, 3.0, width, height);
        cairo_stroke(w->crb);
    } else if (w->state==3) {
        _rounded_rectangle(w->crb,3.0, 3.0, width, height);
        cairo_stroke(w->crb);
    }
}

void _draw_button(void *w_, void* user_data) {
    Metrics_t m;
    int width, height;
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    os_get_window_metrics(w, &m);
    width = m.width-2;
    height = m.height-2;
    if (!m.visible) return;
    _draw_button_base(w, width, height);

    float offset = 0.0;
    if(w->state==1 && ! (int)w->adj_y->value) {
        offset = 1.0;
    } else if(w->state==1) {
        offset = 2.0;
    } else if(w->state==2) {
        offset = 2.0;
    } else if(w->state==3) {
        offset = 1.0;
    }
    if (w->image) {
        if(strlen(w->label)) {
            _draw_image_button_with_label(w, width, height);
        } else {
            _draw_image_button(w, width, height,offset);
        }
    } else {

        cairo_text_extents_t extents;
        use_text_color_scheme(w, get_color_state(w));
        cairo_set_font_size (w->crb, w->app->normal_font/w->scale.ascale);
        cairo_text_extents(w->crb,w->label , &extents);
        if(IS_UTF8(w->label[0])) {
            cairo_set_font_size (w->crb, w->app->normal_font/w->scale.ascale);
            cairo_text_extents(w->crb,w->label , &extents);
        }

        cairo_move_to (w->crb, (width-extents.width)*0.5 +offset, (height+extents.height)*0.5 +offset);
        cairo_show_text(w->crb, w->label);
        cairo_new_path (w->crb);
    }
}

void _draw_on_off_button(void *w_, void* user_data) {
    Metrics_t m;
    int width, height;
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    os_get_window_metrics(w, &m);
    width = m.width-2;
    height = m.height-2;
    if (!m.visible) return;

    _draw_button_base(w, width, height);

    float offset = 0.0;
    cairo_text_extents_t extents;
    if(w->state==1 && ! (int)w->adj_y->value) {
        offset = 1.0;
    } else if(w->state==1) {
        offset = 2.0;
    } else if(w->state==2) {
        offset = 2.0;
    } else if(w->state==3) {
        offset = 1.0;
    }
    if((int)w->adj_y->value) {
        w->label = "On";
    } else {
        w->label = "Off";
    }

    use_text_color_scheme(w, get_color_state(w));
    cairo_set_font_size (w->crb, w->app->normal_font/w->scale.ascale);
    cairo_text_extents(w->crb,w->label , &extents);
    if(IS_UTF8(w->label[0])) {
        cairo_set_font_size (w->crb, w->app->normal_font/w->scale.ascale);
        cairo_text_extents(w->crb,w->label , &extents);
    }

    cairo_move_to (w->crb, (width-extents.width)*0.5 +offset, (height+extents.height)*0.5 +offset);
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);

}

void _draw_ti_button(void *w_, void* user_data) {
    Metrics_t m;
    int width, height;
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    os_get_window_metrics(w, &m);
    width = m.width-2;
    height = m.height-2;
    if (!m.visible) return;
    _draw_button_base(w, width, height);
    if (w->image) {
        float offset = 0.0;
        if(w->state==1 && ! (int)w->adj_y->value) {
            offset = 1.0;
        } else if(w->state==1) {
            offset = 2.0;
        } else if(w->state==2) {
            offset = 2.0;
        } else if(w->state==3) {
            offset = 1.0;
        }
        
       _draw_image_button(w, width, height,offset);
   }
}

void _draw_check_button(void *w_, void* user_data) {
    Metrics_t m;
    int width, height;
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    os_get_window_metrics(w, &m);
    width = m.width-2;
    height = m.height-2;
    if (!m.visible) return;
    if (w->image) {
        _draw_image_button(w, width, height,0.0);
    } else {
        _draw_button_base(w, width, height);

        if(w->state==3) {
            use_fg_color_scheme(w, get_color_state(w));
            float offset = 1.0;
            int wa = width/1.3;
            int h = height/2.2;
            int wa1 = width/2.2;
            int h1 = height/1.3;
            int wa2 = width/2.8;

            cairo_set_line_width(w->crb, 2.5);
            cairo_move_to(w->crb, wa+offset, h+offset);
            cairo_line_to(w->crb, wa1+offset, h1+offset);
            cairo_line_to(w->crb, wa2+offset, h+offset);
            cairo_stroke(w->crb);
        }

        cairo_new_path (w->crb);
    }
}

void _draw_check_box(void *w_, void* user_data) {
    Metrics_t m;
    int height;
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    os_get_window_metrics(w, &m);
    height = m.height-2;
    if (!m.visible) return;
    if (w->image) {
        _draw_image_button(w, height, height,0.0);
    } else {
        _draw_button_base(w, height, height);

        if(adj_get_value(w->adj)) {
            use_fg_color_scheme(w, get_color_state(w));
            float offset = 1.0;
            int wa = height/1.3;
            int h = height/2.2;
            int wa1 = height/2.2;
            int h1 = height/1.3;
            int wa2 = height/2.8;

            cairo_set_line_width(w->crb, 2.5);
            cairo_move_to(w->crb, wa+offset, h+offset);
            cairo_line_to(w->crb, wa1+offset, h1+offset);
            cairo_line_to(w->crb, wa2+offset, h+offset);
            cairo_stroke(w->crb);
        }

        cairo_new_path (w->crb);

        cairo_text_extents_t extents;
        use_text_color_scheme(w, get_color_state(w));
        cairo_set_font_size (w->crb, w->app->normal_font/w->scale.ascale);
        cairo_text_extents(w->crb,w->label , &extents);
        cairo_move_to (w->crb, height+5 , (height+extents.height)*0.5 );
        cairo_show_text(w->crb, w->label);
        cairo_new_path (w->crb);
    }
}

/*---------------------------------------------------------------------
-----------------------------------------------------------------------	
                            button
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

void _button_pressed(void *w_, void* button, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    adj_set_value(w->adj_y, 1.0);
}

void _button_released(void *w_, void* button_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (w->flags & HAS_POINTER) w->state=1;
    adj_set_value(w->adj_y, 0.0);
}

/*---------------------------------------------------------------------
-----------------------------------------------------------------------	
                        toggle button
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

void _toggle_button_pressed(void *w_, void* button, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    expose_widget(w);
}

void _toggle_button_released(void *w_, void* button_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    XButtonEvent *xbutton = (XButtonEvent*)button_;
    if (w->flags & HAS_POINTER) {
        float value = w->adj->value;
        if (xbutton->button == Button1) value = value ? 
                w->adj->min_value : w->adj->max_value; 
        if (xbutton->button == Button4) value = w->adj->max_value; 
        if (xbutton->button == Button5) value = w->adj->min_value; 
        adj_set_value(w->adj, value);
        w->state = (int) w->adj->value ? 3 : 1;
    } else {
        w->state = (int) w->adj->value ? 3 : 0;
    }
    expose_widget(w);
}
