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

#include "xwidget_private.h"


void _scroll_event(Widget_t * wid, int direction) {
    Adjustment_t *adj = NULL;
    if (wid->adj_y) {
        adj = wid->adj_y;
    } else if(wid->adj_x) {
        adj = wid->adj_x;
    }
    if (adj) {
        float value = adj->value;
        switch(adj->type) {
            case (CL_LOGSCALE):
            case (CL_LOGARITHMIC):
            case (CL_CONTINUOS):
                value = min(adj->max_value,max(adj->min_value, 
                                adj->value + (adj->step * direction)));
            break;
            case (CL_VIEWPORT):
            case (CL_ENUM):
                value = min(adj->max_value,max(adj->min_value, 
                                adj->value + (adj->step * -direction)));
            break;
            case (CL_TOGGLE):
               // value = adj->value ? 1.0 : 0.0;
            break;
            default:
            break;
        }
        check_value_changed(adj, &value);
    } 
}

void _toggle_event(Widget_t * wid) {
    Adjustment_t *adj = NULL;
    if (wid->adj_y) {
        adj = wid->adj_y;
    } else if(wid->adj_x) {
        adj = wid->adj_x;
    }
    if (adj && adj->type != CL_TOGGLE) {
        adj_set_start_value(wid);
    }
}

void _check_enum(Widget_t * wid, XButtonEvent *xbutton) {
    if (wid->flags & HAS_POINTER && xbutton->button == Button1) {
        Adjustment_t *adj = NULL;
        if (wid->adj_y) {
            adj = wid->adj_y;
        } else if(wid->adj_x) {
            adj = wid->adj_x;
        }
        if (adj && adj->type == CL_ENUM) {
            float value = adj->value;
            value = adj->value + 1.0;
            if (value>adj->max_value) value = adj->min_value;
            check_value_changed(adj, &value);
        }
    }
}

void _button_press(Widget_t * wid, XButtonEvent *xbutton, void* user_data) {
    switch(xbutton->button) {
        case Button1:
            wid->state = 2;
            _has_pointer(wid, xbutton);
            wid->pos_x = xbutton->x;
            wid->pos_y = xbutton->y;
            _toggle_event(wid);
            wid->func.button_press_callback(wid, xbutton, user_data);
        break;
        case Button2:
            debug_print("Button2 \n");
        break;
        case Button3:
            debug_print("Button3 \n");
            wid->func.button_press_callback(wid, xbutton, user_data);
        break;
        case  Button4:
            _scroll_event(wid, 1);
        break;
        case Button5:
            _scroll_event(wid, -1);
        break;
        default:
        break;
    }
}

void _check_grab(Widget_t * wid, XButtonEvent *xbutton, Xputty *main) {
    if(main->hold_grab != NULL) {
        Widget_t *view_port = main->hold_grab->childlist->childs[0];
        if(xbutton->button == Button1) {
            //if (xbutton->window == view_port->widget) return;
#ifdef _WIN32 //SetCaptureDisabled//XUngrabPointer
            //ReleaseCapture(); // SetCapture() is currently disabled in pop_menu_show()
#else
            XUngrabPointer(main->dpy,CurrentTime);
#endif
            int i = view_port->childlist->elem-1;
            for(;i>-1;i--) {
                Widget_t *w = view_port->childlist->childs[i];
                if (xbutton->window == w->widget) {
                    const char *l = view_port->childlist->childs[i]->label;
                    main->hold_grab->func.button_release_callback
                        (main->hold_grab, &i, &l);
                    break;
                }
            }
            widget_hide(main->hold_grab);
            main->hold_grab = NULL;

        } else if(xbutton->button == Button4) {
            _scroll_event(view_port, 1);
        } else if(xbutton->button == Button5) {
            _scroll_event(view_port, -1);
        }
    }
}

void _propagate_child_expose(Widget_t *wid) {

    if (childlist_has_child(wid->childlist)) {
        int i = 0;
        for(;i<wid->childlist->elem;i++) {
            Widget_t *w = wid->childlist->childs[i];
            if (w->flags & USE_TRANSPARENCY) {
                if(w->flags & FAST_REDRAW)
#ifndef _WIN32 //ForceRedraw
                    transparent_draw(w, NULL);
#else
		    expose_widget(w);
#endif
                else expose_widget(w);
            }
        }
    }      
}

void _check_keymap (void *w_ ,XKeyEvent xkey) {
    Widget_t *wid = (Widget_t*)w_;
    int n = 1;
    int i = 0;
    for(;i<wid->childlist->elem;i++) {
        Widget_t *w = wid->childlist->childs[i];
        if(w->flags & HAS_FOCUS && w->state != 4) {
             wid=w;
            break;
        }
    }
    if(wid->app->hold_grab != NULL) {
        wid = wid->app->hold_grab->childlist->childs[0];
        n = -1;
    }
    int nk = key_mapping(wid->app->dpy, &xkey);
    if (nk) {
        switch (nk) {
            case 3: _set_adj_value(wid, false, 1*n);
            break;
            case 4: _set_adj_value(wid, true, 1*n);
            break;
            case 5: _set_adj_value(wid, false, -1*n);
            break;
            case 6: _set_adj_value(wid, true, -1*n);
            break;
            case 10: 
            {
                int i = 0;
                for(;i<wid->childlist->elem;i++) {
                    Widget_t *w = wid->childlist->childs[i];
                    if(w->flags & HAS_FOCUS && w->state != 4) {
                         wid=w;
                        break;
                    }
                }
                send_button_press_event(wid);
                send_button_release_event(wid);
            }
            break;
            default:
            break;
        }
    }
}

void _hide_all_tooltips(Widget_t *wid) {
    int i = 0;
    for(;i<wid->app->childlist->elem;i++) {
        Widget_t *w = wid->app->childlist->childs[i];
        if (w->flags & IS_TOOLTIP) {
            widget_hide(w);
        }
    }
}

void _has_pointer(Widget_t *w, XButtonEvent *button) {
    Metrics_t metrics;
    os_get_window_metrics(w, &metrics);
    
    if ((button->x<metrics.width && button->y<metrics.height) &&
                                (button->x>0 && button->y>0)){
        w->flags |= HAS_POINTER;
    } else {
        w->flags &= ~HAS_POINTER;
    }
}

void _set_adj_value(void *w_, bool x, int direction) {
    Widget_t *wid = (Widget_t*)w_;
    Adjustment_t *adj = NULL;
    if (x && wid->adj_x) {
        adj = wid->adj_x;
    } else if (!x && wid->adj_y) {
        adj = wid->adj_y;
    }
    if (adj) {
        float value = min(adj->max_value,max(adj->min_value, 
        adj->value + (adj->step * direction)));
        check_value_changed(adj, &value);
    }
}

void _dummy1_callback(void *w_, void* _data, void* user_data) {
    debug_print("Widget_t _dummy callback\n");
}

void _dummy_callback(void *w_, void* user_data) {
    debug_print("Widget_t _dummy callback\n");
}

void _resize_surface(Widget_t *wid, int width, int height) {
    wid->width = width;
    wid->height = height;
    os_set_widget_surface_size(wid, wid->width, wid->height);
    cairo_font_face_t *ff = cairo_get_font_face(wid->crb);
    cairo_destroy(wid->crb);
    cairo_surface_destroy(wid->buffer);
    wid->buffer = cairo_surface_create_similar (wid->surface, 
                        CAIRO_CONTENT_COLOR_ALPHA, width, height);
    assert(cairo_surface_status(wid->buffer) == CAIRO_STATUS_SUCCESS);
    wid->crb = cairo_create (wid->buffer);
    cairo_set_font_face(wid->crb, ff);
}

void _resize_childs(Widget_t *wid) {
    if(!childlist_has_child(wid->childlist)) return;
    int i = 0;
    for(;i<wid->childlist->elem;i++) {
        Widget_t *w = wid->childlist->childs[i];
        switch(w->scale.gravity) {
            case(NORTHWEST):
                os_resize_window (wid->app->dpy, w, max(1,
                    w->scale.init_width - (wid->scale.scale_x)), 
                    max(1,w->scale.init_height - (wid->scale.scale_y)));
            break;
            case(NORTHEAST):
                os_resize_window (wid->app->dpy, w, max(1,
                    w->scale.init_width - (wid->scale.scale_x)), w->height);
            break;
            case(SOUTHWEST):
                os_move_window(wid->app->dpy,w,w->scale.init_x-wid->scale.scale_x,
                                        w->scale.init_y-wid->scale.scale_y);
            
            break;
            case(SOUTHEAST):
                os_move_window(wid->app->dpy,w,w->scale.init_x,
                                            w->scale.init_y-wid->scale.scale_y);
            break;
            case(CENTER):
                os_move_window(wid->app->dpy,w,w->scale.init_x /
                    wid->scale.cscale_x,w->scale.init_y / wid->scale.cscale_y);
                os_resize_window (wid->app->dpy, w, max(1,
                    w->scale.init_width / (wid->scale.cscale_x)), 
                    max(1,w->scale.init_height / (wid->scale.cscale_y)));
            break;
            case(ASPECT):
                os_move_window(wid->app->dpy,w,(
                    (w->scale.init_x + w->scale.init_width*0.5) /
                    wid->scale.cscale_x) - w->width*0.5,
                    ((w->scale.init_y + w->scale.init_height*0.5) /
                    wid->scale.cscale_y)- w->height*0.5) ;
                os_resize_window (wid->app->dpy, w, max(1,
                    w->scale.init_width / (wid->scale.ascale)), 
                    max(1,w->scale.init_height / (wid->scale.ascale)));
            break;
            case(FIXEDSIZE):
                os_move_window(wid->app->dpy,w,(
                    (w->scale.init_x + w->scale.init_width*0.5) /
                    wid->scale.cscale_x) - w->width*0.5,
                    ((w->scale.init_y + w->scale.init_height*0.5) /
                    wid->scale.cscale_y)- w->height*0.5) ;
            break;
            case(MENUITEM):
                os_resize_window (wid->app->dpy, w, max(1,
                    w->scale.init_width - (wid->scale.scale_x)-5), w->scale.init_height);
            break;
            case(NONE):
            break;
            default:
            break;
        }
        w->func.configure_notify_callback(w,NULL);
    }
}
