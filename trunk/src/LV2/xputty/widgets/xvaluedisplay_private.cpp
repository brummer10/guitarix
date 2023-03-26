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


#include "xvaluedisplay_private.h"


void _draw_valuedisplay(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    Metrics_t m;
    int width, height;
    os_get_window_metrics(w, &m);
    width = m.width-2;
    height = m.height-2;
    if (!m.visible) return;

    cairo_rectangle(w->crb,2.0, 2.0, width, height);

    if(w->state==0) {
        cairo_set_line_width(w->crb, 1.0);
        use_shadow_color_scheme(w, NORMAL_);
        cairo_fill_preserve(w->crb);
        use_frame_color_scheme(w, NORMAL_);
    } else if(w->state==1) {
        use_shadow_color_scheme(w, PRELIGHT_);
        cairo_fill_preserve(w->crb);
        cairo_set_line_width(w->crb, 1.5);
        use_frame_color_scheme(w, NORMAL_);
    } else if(w->state==2) {
        use_shadow_color_scheme(w, SELECTED_);
        cairo_fill_preserve(w->crb);
        cairo_set_line_width(w->crb, 1.0);
        use_frame_color_scheme(w, SELECTED_);
    } else if(w->state==3) {
        use_shadow_color_scheme(w, ACTIVE_);
        cairo_fill_preserve(w->crb);
        cairo_set_line_width(w->crb, 1.0);
        use_frame_color_scheme(w, ACTIVE_);
    } else if(w->state==4) {
        use_shadow_color_scheme(w, INSENSITIVE_);
        cairo_fill_preserve(w->crb);
        cairo_set_line_width(w->crb, 1.0);
        use_frame_color_scheme(w, INSENSITIVE_);
    }
    cairo_stroke(w->crb); 

    cairo_rectangle(w->crb,4.0, 4.0, width, height);
    cairo_stroke(w->crb);
    cairo_rectangle(w->crb,3.0, 3.0, width, height);
    cairo_stroke(w->crb);

    cairo_text_extents_t extents;

    char s[64];
    const char* format[] = {"%.1f ", "%.2f ", "%. Hz"};
    float value = adj_get_value(w->adj);
    snprintf(s, 63, format[2-1], value);

    
    use_text_color_scheme(w, get_color_state(w));
    float font_size = w->app->normal_font/w->scale.ascale;
    cairo_set_font_size (w->crb, font_size);
    cairo_text_extents(w->crb,s , &extents);
    cairo_move_to (w->crb, (width-extents.width)*0.5, (height+extents.height)*0.55);
    cairo_show_text(w->crb, s);
    cairo_new_path (w->crb);

}
