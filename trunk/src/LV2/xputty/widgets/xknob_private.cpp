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


#include "xknob_private.h"


void _draw_image_knob(Widget_t *w, int width_t, int height_t) {
    int width = cairo_xlib_surface_get_width(w->image);
    int height = cairo_xlib_surface_get_height(w->image);
    double x = (double)width_t/(double)height;
    double y = (double)height/(double)width_t;
    double knobstate = adj_get_state(w->adj_y);
    int findex = (int)(((width/height)-1) * knobstate);
    cairo_scale(w->crb, x,x);
    //widget_set_scale(w);
    cairo_set_source_surface (w->crb, w->image, -height*findex, 0);
    cairo_rectangle(w->crb,0, 0, height, height);
    cairo_fill(w->crb);
    //widget_reset_scale(w);
    cairo_scale(w->crb, y,y);
}

void _draw_knob(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    XWindowAttributes attrs;
    XGetWindowAttributes(w->app->dpy, (Window)w->widget, &attrs);
    int width = attrs.width-2;
    int height = attrs.height-2;

    const double scale_zero = 20 * (M_PI/180); // defines "dead zone" for knobs
    int arc_offset = 0;
    int knob_x = 0;
    int knob_y = 0;

    int grow = (width > height) ? height:width;
    knob_x = grow-1;
    knob_y = grow-1;
    /** get values for the knob **/

    int knobx = (width - knob_x) * 0.5;
    int knobx1 = width* 0.5;

    int knoby = (height - knob_y) * 0.5;
    int knoby1 = height * 0.5;
    if (w->image) {
        _draw_image_knob(w, width, height);
    } else {

        double knobstate = adj_get_state(w->adj_y);
        double angle = scale_zero + knobstate * 2 * (M_PI - scale_zero);

        double pointer_off =knob_x/6;
        double radius = min(knob_x-pointer_off, knob_y-pointer_off) / 2;
        double lengh_x = (knobx+radius+pointer_off/2) - radius * sin(angle);
        double lengh_y = (knoby+radius+pointer_off/2) + radius * cos(angle);
        double radius_x = (knobx+radius+pointer_off/2) - radius/ 1.18 * sin(angle);
        double radius_y = (knoby+radius+pointer_off/2) + radius/ 1.18 * cos(angle);

        cairo_arc(w->crb,knobx1+arc_offset, knoby1+arc_offset, knob_x/2.1, 0, 2 * M_PI );

        use_shadow_color_scheme(w, get_color_state(w));
        cairo_fill (w->crb);
        cairo_new_path (w->crb);

        use_bg_color_scheme(w, get_color_state(w));
        cairo_arc(w->crb,knobx1+arc_offset, knoby1+arc_offset, knob_x/3.1, 0, 2 * M_PI );
        cairo_fill_preserve(w->crb);
        use_fg_color_scheme(w, NORMAL_);
        cairo_set_line_width(w->crb, knobx1/15);
        cairo_stroke(w->crb);
        cairo_new_path (w->crb);

        /** create a rotating pointer on the kob**/
        cairo_set_line_cap(w->crb, CAIRO_LINE_CAP_ROUND); 
        cairo_set_line_join(w->crb, CAIRO_LINE_JOIN_BEVEL);
        cairo_move_to(w->crb, radius_x, radius_y);
        cairo_line_to(w->crb,lengh_x,lengh_y);
        cairo_set_line_width(w->crb,knobx1/7);
        use_fg_color_scheme(w, NORMAL_);
        cairo_stroke(w->crb);
        cairo_new_path (w->crb);
    }
    cairo_text_extents_t extents;
    /** show value on the kob**/
    if (w->state) {
        char s[64];
        const char* format[] = {"%.1f", "%.2f", "%.3f"};
        if (fabs(w->adj_y->value)>9.99) {
            snprintf(s, 63,"%d",  (int) w->adj_y->value);
        } else if (fabs(w->adj_y->value)>0.99) {
            snprintf(s, 63, format[1-1], w->adj_y->value);
        } else {
            snprintf(s, 63, format[2-1], w->adj_y->value);
        }
        cairo_set_source_rgb (w->crb, 0.6, 0.6, 0.6);
        cairo_set_font_size (w->crb, knobx1/4);
        cairo_text_extents(w->crb, s, &extents);
        cairo_move_to (w->crb, knobx1-extents.width/2, knoby1+extents.height/2);
        cairo_show_text(w->crb, s);
        cairo_new_path (w->crb);
    }

    /** show label below the knob**/
    use_text_color_scheme(w, get_color_state(w));
    float font_size = ((height/2.2 < (width*0.5)/3) ? height/2.2 : (width*0.5)/3);
    cairo_set_font_size (w->crb, font_size);
    cairo_text_extents(w->crb,w->label , &extents);

    cairo_move_to (w->crb, knobx1-extents.width/2, height );
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
}

void _knob_released(void *w_, void* button_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (w->flags & HAS_POINTER) w->state= 1;
    expose_widget(w);
}
