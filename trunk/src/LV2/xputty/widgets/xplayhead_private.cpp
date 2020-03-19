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


#include "xplayhead_private.h"


void _create_playhead_image(Widget_t *w, int width, int height) {
    w->image = cairo_surface_create_similar (w->surface, 
                        CAIRO_CONTENT_COLOR_ALPHA, width, height*2);
    cairo_t *cri = cairo_create (w->image);
    Colors *c = get_color_scheme(w->app, NORMAL_);

    //cairo_rectangle(cri,0.0, 0.0, width, height*2);
    //cairo_set_source_rgba (cri, c->bg[0],  c->bg[1], c->bg[2],  c->bg[3]); 
    //cairo_fill(cri);

    cairo_set_source_rgba (cri, c->shadow[0],  c->shadow[1], c->shadow[2],  c->shadow[3]); 

    int h = height ;
    int ci = h-2;

    int i = 1;
    for(;i<width;) {
        cairo_rectangle(cri,i,1,2,ci);
        cairo_fill(cri);
        i +=3;
    }

    cairo_set_source_rgba (cri, c->text[0],  c->text[1], c->text[2],  c->text[3]); 

    i = 1;
    for(;i<width;) {
        cairo_rectangle(cri,i,height+1,2,ci);
        cairo_fill(cri);
        i +=3;
    }

    cairo_destroy(cri);
}

void _draw_playhead(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;

    int width = cairo_xlib_surface_get_width(w->image);
    int height = cairo_xlib_surface_get_height(w->image);
    double state = adj_get_state(w->adj);
    double clip = adj_get_state(w->adj_x);
    double cut = adj_get_state(w->adj_y);
    widget_set_scale(w);
    cairo_set_source_surface (w->crb, w->image, 0, 0);
    cairo_rectangle(w->crb,0, 0, width, height/2);
    cairo_fill(w->crb);
    cairo_set_source_surface (w->crb, w->image, 0, -height/2);
    cairo_rectangle(w->crb, width*state,0,3, height/2);
    cairo_fill(w->crb);

    cairo_set_source_rgba (w->crb, 0.5, 0.0, 0.0, 0.4);
    cairo_rectangle(w->crb, 0,0,width*clip, height/2);
    cairo_fill(w->crb);

    cairo_rectangle(w->crb, width,0,(width*cut)-width, height/2);
    cairo_fill(w->crb);

    widget_reset_scale(w);
}
