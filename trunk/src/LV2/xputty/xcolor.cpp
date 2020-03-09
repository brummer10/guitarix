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

#include "xcolor.h"


void set_dark_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.85, 0.85, 0.85, 1.0},
        .bg =       { 0.1, 0.1, 0.1, 1.0},
        .base =     { 0.0, 0.0, 0.0, 1.0},
        .text =     { 0.9, 0.9, 0.9, 1.0},
        .shadow =   { 0.0, 0.0, 0.0, 0.2},
        .frame =    { 0.0, 0.0, 0.0, 1.0},
        .light =    { 0.1, 0.1, 0.1, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        .fg =       { 1.0, 0.0, 1.0, 1.0},
        .bg =       { 0.25, 0.25, 0.25, 1.0},
        .base =     { 0.3, 0.3, 0.3, 1.0},
        .text =     { 1.0, 1.0, 1.0, 1.0},
        .shadow =   { 0.1, 0.1, 0.1, 0.4},
        .frame =    { 0.3, 0.3, 0.3, 1.0},
        .light =    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        .fg =       { 0.9, 0.9, 0.9, 1.0},
        .bg =       { 0.2, 0.2, 0.2, 1.0},
        .base =     { 0.5, 0.18, 0.18, 1.0},
        .text =     { 1.0, 1.0, 1.0, 1.0},
        .shadow =   { 0.8, 0.18, 0.18, 0.2},
        .frame =    { 0.5, 0.18, 0.18, 1.0},
        .light =    { 0.5, 0.18, 0.18, 1.0}
    };

    main->color_scheme->active = (Colors) {
        .fg =       { 0.0, 1.0, 1.0, 1.0},
        .bg =       { 0.0, 0.0, 0.0, 1.0},
        .base =     { 0.18, 0.38, 0.38, 1.0},
        .text =     { 0.75, 0.75, 0.75, 1.0},
        .shadow =   { 0.18, 0.38, 0.38, 0.5},
        .frame =    { 0.18, 0.38, 0.38, 1.0},
        .light =    { 0.18, 0.38, 0.38, 1.0}
    };

    main->color_scheme->insensitive = (Colors) {
        .fg =       { 0.85, 0.85, 0.85, 0.5},
        .bg =       { 0.1, 0.1, 0.1, 0.5},
        .base =     { 0.0, 0.0, 0.0, 0.5},
        .text =     { 0.9, 0.9, 0.9, 0.5},
        .shadow =   { 0.0, 0.0, 0.0, 0.1},
        .frame =    { 0.0, 0.0, 0.0, 0.5},
        .light =    { 0.1, 0.1, 0.1, 0.5}
    };
}

void set_light_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.15, 0.15, 0.15, 1.0},
        .bg =       { 0.85, 0.85, 0.85, 1.0},
        .base =     { 0.9, 0.9, 0.9, 1.0},
        .text =     { 0.25, 0.25, 0.25, 1.0},
        .shadow =   { 0.0, 0.0, 0.0, 0.2},
        .frame =    { 0.2, 0.2, 0.2, 1.0},
        .light =    { 0.9, 0.9, 0.9, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        .fg =       { 0.25, 0.25, 0.25, 1.0},
        .bg =       { 1.0, 1.0, 1.0, 1.0},
        .base =     { 0.75, 0.75, 0.75, 1.0},
        .text =     { 0.15, 0.15, 0.15, 1.0},
        .shadow =   { 0.1, 0.1, 0.1, 0.4},
        .frame =    { 0.3, 0.3, 0.3, 1.0},
        .light =    { 0.75, 0.75, 0.75, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        .fg =       { 0.2, 0.2, 0.2, 1.0},
        .bg =       { 0.9, 0.9, 0.9, 1.0},
        .base =     { 0.0, 0.5, 0.65, 1.0},
        .text =     { 0.8, 0.8, 0.8, 1.0},
        .shadow =   { 0.8, 0.18, 0.18, 0.2},
        .frame =    { 0.5, 0.18, 0.18, 1.0},
        .light =    { 0.5, 0.5, 0.5, 1.0}
    };

    main->color_scheme->active = (Colors) {
        .fg =       { 0.0, 0.0, 0.0, 1.0},
        .bg =       { 1.0, 1.0, 1.0, 1.0},
        .base =     { 0.0, 0.3, 0.65, 1.0},
        .text =     { 0.8, 0.8, 0.8, 1.0},
        .shadow =   { 0.18, 0.38, 0.38, 0.5},
        .frame =    { 0.18, 0.38, 0.38, 1.0},
        .light =    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->insensitive = (Colors) {
        .fg =       { 0.15, 0.15, 0.15, 0.5},
        .bg =       { 0.85, 0.85, 0.85, 0.5},
        .base =     { 0.9, 0.9, 0.9, 0.5},
        .text =     { 0.25, 0.25, 0.25, 0.5},
        .shadow =   { 0.0, 0.0, 0.0, 0.1},
        .frame =    { 0.2, 0.2, 0.2, 0.5},
        .light =    { 0.9, 0.9, 0.9, 0.5}
    };
}

Colors *get_color_scheme(Xputty *main, Color_state st) {
    switch(st) {
        case NORMAL_:
            return &main->color_scheme->normal;
        break;
        case PRELIGHT_:
            return &main->color_scheme->prelight;
        break;
        case SELECTED_:
            return &main->color_scheme->selected;
        break;
        case ACTIVE_:
            return &main->color_scheme->active;
        break;
        case INSENSITIVE_:
            return &main->color_scheme->insensitive;
        break;
        default:
            return &main->color_scheme->normal;
        break;
    }
    return NULL;
   
}

Color_state get_color_state(Widget_t *wid) {
    switch(wid->state) {
        case 0:
            return NORMAL_;
        break;
        case 1:
            return PRELIGHT_;
        break;
        case 2:
            return SELECTED_;
        break;
        case 3:
            return ACTIVE_;
        break;
        case 4:
            return INSENSITIVE_;
        break;
        default:
            return NORMAL_;
        break;        
    }
}

void use_fg_color_scheme(Widget_t *w, Color_state st) {
    Colors *c = get_color_scheme(w->app, st);
    if (!c) return;
    cairo_set_source_rgba(w->cr, c->fg[0],  c->fg[1], c->fg[2],  c->fg[3]);
    cairo_set_source_rgba(w->crb, c->fg[0],  c->fg[1], c->fg[2],  c->fg[3]);
}

void use_bg_color_scheme(Widget_t *w, Color_state st) {
    Colors *c = get_color_scheme(w->app, st);
    if (!c) return;
    cairo_set_source_rgba(w->cr, c->bg[0],  c->bg[1], c->bg[2],  c->bg[3]);
    cairo_set_source_rgba(w->crb, c->bg[0],  c->bg[1], c->bg[2],  c->bg[3]);
}

void use_base_color_scheme(Widget_t *w, Color_state st) {
    Colors *c = get_color_scheme(w->app, st);
    if (!c) return;
    cairo_set_source_rgba(w->cr, c->base[0],  c->base[1], c->base[2],  c->base[3]);
    cairo_set_source_rgba(w->crb, c->base[0],  c->base[1], c->base[2],  c->base[3]);
}

void use_text_color_scheme(Widget_t *w, Color_state st) {
    Colors *c = get_color_scheme(w->app, st);
    if (!c) return;
    cairo_set_source_rgba(w->cr, c->text[0],  c->text[1], c->text[2],  c->text[3]);
    cairo_set_source_rgba(w->crb, c->text[0],  c->text[1], c->text[2],  c->text[3]);
}

void use_shadow_color_scheme(Widget_t *w, Color_state st) {
    Colors *c = get_color_scheme(w->app, st);
    if (!c) return;
    cairo_set_source_rgba(w->cr, c->shadow[0],  c->shadow[1], c->shadow[2],  c->shadow[3]);
    cairo_set_source_rgba(w->crb, c->shadow[0],  c->shadow[1], c->shadow[2],  c->shadow[3]);
}

void use_frame_color_scheme(Widget_t *w, Color_state st) {
    Colors *c = get_color_scheme(w->app, st);
    if (!c) return;
    cairo_set_source_rgba(w->cr, c->frame[0],  c->frame[1], c->frame[2],  c->frame[3]);
    cairo_set_source_rgba(w->crb, c->frame[0],  c->frame[1], c->frame[2],  c->frame[3]);
}

void use_light_color_scheme(Widget_t *w, Color_state st) {
    Colors *c = get_color_scheme(w->app, st);
    if (!c) return;
    cairo_set_source_rgba(w->cr, c->light[0],  c->light[1], c->light[2],  c->light[3]);
    cairo_set_source_rgba(w->crb, c->light[0],  c->light[1], c->light[2],  c->light[3]);
}

void set_pattern(Widget_t *w, Colors *from, Colors *to, Color_mod mod) {
    double *col_from = NULL;
    double *col_to = NULL;
    switch (mod) {
        case FORGROUND_:
            col_from = from->fg;
            col_to = to->fg;
        break;
        case BACKGROUND_:
            col_from = from->bg;
            col_to = to->bg;
        break;
        case BASE_:
            col_from = from->base;
            col_to = to->base;
        break;
        case TEXT_:
            col_from = from->text;
            col_to = to->text;
        break;
        case SHADOW_:
            col_from = from->shadow;
            col_to = to->shadow;
        break;
        case FRAME_:
            col_from = from->frame;
            col_to = to->frame;
        break;
        case LIGHT_:
            col_from = from->light;
            col_to = to->light;
        break;
   }
    XWindowAttributes attrs;
    XGetWindowAttributes(w->app->dpy, (Window)w->widget, &attrs);
    int width = attrs.width;
    int height = attrs.height;
    cairo_pattern_t *pat = cairo_pattern_create_linear (0, 0, width, height);
    cairo_pattern_add_color_stop_rgba(pat, 0.0, col_from[0], col_from[1], col_from[2], col_from[3]);
    cairo_pattern_add_color_stop_rgba(pat, 1.0, col_to[0], col_to[1], col_to[2], col_to[3]);
    cairo_set_source(w->crb, pat);
    cairo_set_source(w->cr, pat);
    cairo_pattern_destroy (pat);
}
