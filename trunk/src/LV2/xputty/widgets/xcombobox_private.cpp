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


#include "xcombobox_private.h"
#include "xtooltip.h"


void _draw_combobox_button(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    Metrics_t m;
    int width, height;
    os_get_window_metrics(w, &m);
    width = m.width-2;
    height = m.height-4;
    if (!m.visible) return;

    if (!w->state && (int)w->adj_y->value)
        w->state = 3;

    cairo_rectangle(w->crb,2.0, 4.0, width, height);

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
        cairo_rectangle(w->crb,4.0, 6.0, width, height);
        cairo_stroke(w->crb);
        cairo_rectangle(w->crb,3.0, 4.0, width, height);
        cairo_stroke(w->crb);
    } else if (w->state==3) {
        cairo_rectangle(w->crb,3.0, 4.0, width, height);
        cairo_stroke(w->crb);
    }

    float offset = 0.0;
    if(w->state==0) {
        use_fg_color_scheme(w, NORMAL_);
    } else if(w->state==1) {
        use_fg_color_scheme(w, PRELIGHT_);
        offset = 1.0;
    } else if(w->state==2) {
        use_fg_color_scheme(w, SELECTED_);
        offset = 2.0;
    } else if(w->state==3) {
        use_fg_color_scheme(w, ACTIVE_);
        offset = 1.0;
    }
    use_text_color_scheme(w, get_color_state(w));
    int wa = width/1.1;
    int h = height/2.2;
    int wa1 = width/1.55;
    int h1 = height/1.3;
    int wa2 = width/2.8;
   
    cairo_move_to(w->crb, wa+offset, h+offset);
    cairo_line_to(w->crb, wa1+offset, h1+offset);
    cairo_line_to(w->crb, wa2+offset, h+offset);
    cairo_line_to(w->crb, wa+offset, h+offset);
    cairo_fill(w->crb);
   
}

void _draw_combobox(void *w_, void* user_data) {
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

    use_text_color_scheme(w, get_color_state(w));
    float font_size = w->app->normal_font/w->scale.ascale;
    cairo_set_font_size (w->crb, font_size);
    cairo_text_extents(w->crb,w->label , &extents);

    cairo_move_to (w->crb, (width-extents.width)*0.4, (height+extents.height)*0.55);
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
    if (extents.width > (float)width-20) {
        tooltip_set_text(w,w->label);
        w->flags |= HAS_TOOLTIP;
    } else {
        w->flags &= ~HAS_TOOLTIP;
    }
}

void _combobox_button_released(void *w_, void* button_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (w->flags & HAS_POINTER){
        XButtonEvent *xbutton = (XButtonEvent*)button_;
        if (xbutton->button == Button3) {
            w->state=1;
            pop_menu_show(w, w->childlist->childs[1], 6, true);
        }
    }
}

void _button_combobox_released(void *w_, void* button_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    XButtonEvent *xbutton = (XButtonEvent*)button_;
    if (w->flags & HAS_POINTER && xbutton->button == Button1) {
        Widget_t *parent = (Widget_t*)w->parent;
        w->state=1;
        pop_menu_show(parent, parent->childlist->childs[1], 6, true);
    }
    adj_set_value(w->adj, 0.0);
}

void _entry_released(void *w_, void* item_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    Widget_t * combo = NULL;
    int i = w->app->childlist->elem-1;
    for(;i>-1;i--) {
        Widget_t *wid = w->app->childlist->childs[i];
        if (wid == w) {
            combo = w->app->childlist->childs[i-2];
            adj_set_value(combo->adj, (float)*(int*)item_);
            break;
        }
    }    
}

void _set_entry(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    int v = (int)adj_get_value(w->adj);
    Widget_t * menu = w->childlist->childs[1];
    if (!childlist_has_child(menu->childlist)) return;
    Widget_t* view_port =  menu->childlist->childs[0];
    if(v>=0) {
        w->label = view_port->childlist->childs[v]->label;
        transparent_draw(w, user_data);
#ifdef _WIN32 //ForceRedraw
	os_expose_widget(w);
#endif
    }
}
