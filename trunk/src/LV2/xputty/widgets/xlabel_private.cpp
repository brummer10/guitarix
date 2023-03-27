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


#include "xlabel_private.h"


void _draw_label(void *w_, void* user_data) {
    Metrics_t m;
    int width, height;
    Widget_t *w = (Widget_t*)w_;
    os_get_window_metrics(w, &m);
    width = m.width;
    height = m.height;

    cairo_text_extents_t extents;
    use_text_color_scheme(w, get_color_state(w));
    cairo_set_font_size (w->crb, w->app->normal_font/w->scale.ascale);
    cairo_text_extents(w->crb,w->label , &extents);

    cairo_move_to (w->crb, (width*0.5)-(extents.width/2), height);
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
}
