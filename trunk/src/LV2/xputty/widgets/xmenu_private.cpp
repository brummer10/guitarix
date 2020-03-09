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


#include "xmenu_private.h"


void _draw_menu(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    use_bg_color_scheme(w, get_color_state(w));
    cairo_paint (w->crb);
}

void _draw_item(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (!w) return;
    XWindowAttributes attrs;
    XGetWindowAttributes(w->app->dpy, (Window)w->widget, &attrs);
    int width = attrs.width;
    int height = attrs.height;
    if (attrs.map_state != IsViewable) return;

    use_base_color_scheme(w, NORMAL_);
    cairo_rectangle(w->crb, 0, 0, width , height);
    if(w->state==1) {
        use_base_color_scheme(w, PRELIGHT_);
    } else if(w->state==2) {
        use_base_color_scheme(w, SELECTED_);
    } else if(w->state==3) {
        use_base_color_scheme(w, ACTIVE_);
    }
    cairo_fill_preserve(w->crb);
    cairo_set_line_width(w->crb, 1.0);
    use_frame_color_scheme(w, PRELIGHT_);
    cairo_stroke(w->crb); 

    cairo_text_extents_t extents;
    /** show label **/
    use_text_color_scheme(w, get_color_state(w));
    cairo_set_font_size (w->crb, height/2);
    cairo_select_font_face (w->crb, "Sans", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
    cairo_text_extents(w->crb,w->label , &extents);

    cairo_move_to (w->crb, (width-extents.width)/2., height - extents.height );
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
}

void _draw_check_item(void *w_, void* user_data) {
    _draw_item(w_, user_data);
    Widget_t *w = (Widget_t*)w_;
    XWindowAttributes attrs;
    XGetWindowAttributes(w->app->dpy, (Window)w->widget, &attrs);
    int height = attrs.height;
    if (w->flags & IS_RADIO) {
        cairo_arc(w->crb, height/3, height/2, height/6, 0, 2 * M_PI );
    } else {
        cairo_rectangle(w->crb, height/6, height/3, height/3 , height/3);
    }
    use_shadow_color_scheme(w, get_color_state(w));
    cairo_fill(w->crb);
    if ((int) w->adj_y->value) {
        if (w->flags & IS_RADIO) {
            cairo_arc(w->crb, height/3, height/2, height/6-2, 0, 2 * M_PI );
        } else {
            cairo_rectangle(w->crb, height/6+1, height/3+1, height/3-2 , height/3-2);
        }
        use_fg_color_scheme(w, ACTIVE_);
        cairo_fill(w->crb);
    }
}

void _draw_viewslider(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    int v = (int)w->adj->max_value;
    if (!v) return;
    XWindowAttributes attrs;
    XGetWindowAttributes(w->app->dpy, (Window)w->widget, &attrs);
    if (attrs.map_state != IsViewable) return;
    int width = attrs.width;
    int height = attrs.height;
    float sliderstate = adj_get_state(w->adj);
    use_bg_color_scheme(w, NORMAL_);
    cairo_rectangle(w->crb, width-5,0,5,height);
    cairo_fill_preserve(w->crb);
    use_shadow_color_scheme(w, NORMAL_);
    cairo_fill(w->crb);
    use_bg_color_scheme(w, NORMAL_);
    cairo_rectangle(w->crb, width-5,(height-10)*sliderstate,5,10);
    cairo_fill_preserve(w->crb);
    use_fg_color_scheme(w, NORMAL_);
    cairo_set_line_width(w->crb,1);
    cairo_stroke(w->crb);
}

void _set_viewpoint(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    int v = (int)max(0,adj_get_value(w->adj));
    XWindowAttributes attrs;
    XGetWindowAttributes(w->app->dpy, (Window)w->childlist->childs[0]->widget, &attrs);
    int height = attrs.height;
    XMoveWindow(w->app->dpy,w->widget,0, -height*v);
}

void _check_item_button_pressed(void *w_, void* button_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (w->flags & HAS_FOCUS) {
        float value = w->adj_y->value ? 0.0 : 1.0;
        adj_set_value(w->adj_y, value);
    }
}

void _radio_item_button_pressed(void *w_, void* button_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    if (w->flags & HAS_FOCUS) {
        radio_item_set_active(w);
    }
}

void _configure_menu(Widget_t *parent, Widget_t *menu, int elem, bool above) {
    Widget_t* view_port =  menu->childlist->childs[0];
    if (!view_port->childlist->elem) return;
    XWindowAttributes attrs;
    XGetWindowAttributes(menu->app->dpy, (Window)view_port->childlist->childs[0]->widget, &attrs);
    int height = attrs.height;
    int x1, y1;
    int posy = (above) ? parent->height : 0;
    Window child;
    XTranslateCoordinates( parent->app->dpy, parent->widget, DefaultRootWindow(parent->app->dpy), 0, posy, &x1, &y1, &child );
    int item_width = 1.0;
    cairo_text_extents_t extents;
    int i = view_port->childlist->elem-1;
    set_adjustment(view_port->adj,0.0, view_port->adj->value, 0.0, i-(elem-1),1.0, CL_VIEWPORT);
    bool is_not_scrolable = false;
    if(view_port->childlist->elem <= elem) {
        elem = view_port->childlist->elem;
        is_not_scrolable = true;
    }
    for(;i>-1;i--) {
        Widget_t *w = view_port->childlist->childs[i];
        cairo_set_font_size (w->crb, height/2);
        cairo_select_font_face (w->crb, "Sans", CAIRO_FONT_SLANT_NORMAL,
                                   CAIRO_FONT_WEIGHT_BOLD);
        cairo_text_extents(w->crb,w->label , &extents);
        
        item_width = max(item_width, (int)extents.width+40);
        if(is_not_scrolable) w->scale.gravity = NORTHEAST;
    }
    if(above) {
        if(item_width<parent->width)item_width = parent->width;
    }
    XResizeWindow (menu->app->dpy, menu->widget, item_width, height*elem);
    XResizeWindow (view_port->app->dpy, view_port->widget, item_width, height*view_port->childlist->elem);
    XMoveWindow(menu->app->dpy,menu->widget,x1, y1);   
}
