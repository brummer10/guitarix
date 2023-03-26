/* vim:ts=4:sw=4:et:
 *
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

#ifdef __linux__

#ifdef __cplusplus
extern "C" {
#endif

Display *os_open_display(char *display_name) {
    return XOpenDisplay(display_name);
}

void os_close_display(Display *dpy) {
    XCloseDisplay(dpy);
}

void os_destroy_window(Widget_t *w) {
    if (w->xic) XDestroyIC(w->xic);
    if (w->xim) XCloseIM(w->xim);
    XUnmapWindow(w->app->dpy, w->widget);
    XDestroyWindow(w->app->dpy, w->widget);
}

Window os_get_root_window(Widget_t *w) {
    return DefaultRootWindow(w->app->dpy);
}

void os_translate_coords(Widget_t *w, Window from_window, Window to_window,
                          int from_x, int from_y, int *to_x, int *to_y) {
    Window child;
    XTranslateCoordinates(w->app->dpy, from_window, to_window,
                          from_x, from_y, to_x, to_y, &child);
}

void os_get_window_metrics(Widget_t *w_, Metrics_t *metrics) {
    Widget_t *wid = (Widget_t*)w_;
    XWindowAttributes attrs;
    XGetWindowAttributes(wid->app->dpy, (Window)wid->widget, &attrs);
    metrics->x = attrs.x;
    metrics->y = attrs.y;
    metrics->width = attrs.width;
    metrics->height = attrs.height;
    metrics->visible = (attrs.map_state == IsViewable);
}

void os_set_window_min_size(Widget_t *w, int min_width, int min_height,
                            int base_width, int base_height) {
    XSizeHints* win_size_hints;
    win_size_hints = XAllocSizeHints();
    win_size_hints->flags =  PMinSize|PBaseSize|PWinGravity;
    win_size_hints->min_width = min_width;
    win_size_hints->min_height = min_height;
    win_size_hints->base_width = base_width;
    win_size_hints->base_height = base_height;
    win_size_hints->win_gravity = CenterGravity;
    XSetWMNormalHints(w->app->dpy, w->widget, win_size_hints);
    XFree(win_size_hints);
}

void os_move_window(Display *dpy, Widget_t *w, int x, int y) {
    XMoveWindow(dpy,w->widget, x, y);
}

void os_resize_window(Display *dpy, Widget_t *w, int x, int y) {
    XResizeWindow(dpy, w->widget, x, y);
}

void os_create_main_window_and_surface(Widget_t *w, Xputty *app, Window win,
                          int x, int y, int width, int height) {
    XSetWindowAttributes attributes;
    attributes.save_under = True;
    attributes.override_redirect = 0;

    long event_mask = StructureNotifyMask|ExposureMask|KeyPressMask 
                    |EnterWindowMask|LeaveWindowMask|ButtonReleaseMask
                    |ButtonPressMask|Button1MotionMask;



    w->widget = XCreateWindow(app->dpy, win , x, y, width, height, 0,
                            CopyFromParent, InputOutput, CopyFromParent,
                            CopyFromParent, &attributes);
    debug_print("XCreateWindow\n");

    XSetLocaleModifiers("");
    w->xim = XOpenIM(app->dpy, 0, 0, 0);
    if(!w->xim){
        XSetLocaleModifiers("@im=none");
        w->xim = XOpenIM(app->dpy, 0, 0, 0);
    }

    w->xic = XCreateIC(w->xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                    XNClientWindow, w->widget, XNFocusWindow,  w->widget, NULL);

    XSetICFocus(w->xic);

    XSelectInput(app->dpy, w->widget, event_mask);

    os_set_window_min_size(w, width/2, height/2, width, height);

    w->surface =  cairo_xlib_surface_create (app->dpy, w->widget,  
                  DefaultVisual(app->dpy, DefaultScreen(app->dpy)), width, height);
}

void os_create_widget_window_and_surface(Widget_t *w, Xputty *app, Widget_t *parent,
                          int x, int y, int width, int height) {
    XSetWindowAttributes attributes;
    attributes.save_under = True;
    attributes.override_redirect = True;

    long event_mask = StructureNotifyMask|ExposureMask|KeyPressMask 
                    |EnterWindowMask|LeaveWindowMask|ButtonReleaseMask
                    |ButtonPressMask|Button1MotionMask;



    w->widget = XCreateWindow(app->dpy, parent->widget , x, y, width, height, 0,
                            CopyFromParent, InputOutput, CopyFromParent,
                            CopyFromParent|CWOverrideRedirect, &attributes);
    debug_print("XCreateWindow\n");

    XSetLocaleModifiers("");
    w->xim = XOpenIM(app->dpy, 0, 0, 0);
    if(!w->xim){
        XSetLocaleModifiers("@im=none");
        w->xim = XOpenIM(app->dpy, 0, 0, 0);
    }

    w->xic = XCreateIC(w->xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
                    XNClientWindow, w->widget, XNFocusWindow,  w->widget, NULL);

    XSetICFocus(w->xic);

    XSelectInput(app->dpy, w->widget, event_mask);

    w->surface =  cairo_xlib_surface_create (app->dpy, w->widget,  
                  DefaultVisual(app->dpy, DefaultScreen(app->dpy)), width, height);
}

void os_set_title(Widget_t *w, const char *title) {
    XStoreName(w->app->dpy, w->widget, title);
}

void os_widget_show(Widget_t *w) {
    XMapWindow(w->app->dpy, w->widget);
}

void os_widget_hide(Widget_t *w) {
    XUnmapWindow(w->app->dpy, w->widget);
}

void os_show_tooltip(Widget_t *wid, Widget_t *w) {
    unsigned int mask;
    int x, y, rx, ry;
    Window child, root;
    XQueryPointer(wid->app->dpy, wid->widget, &root, &child, &rx, &ry, &x, &y, &mask);
    int x1, y1;
    os_translate_coords(wid, wid->widget, os_get_root_window(wid), x, y, &x1, &y1);
    XMoveWindow(w->app->dpy,w->widget,x1+10, y1-10);
}

void os_expose_widget(Widget_t *w) {
    XEvent exp;
    memset(&exp, 0, sizeof(exp));
    exp.type = Expose;
    exp.xexpose.window = w->widget;
    XSendEvent(w->app->dpy, w->widget, False, ExposureMask, (XEvent *)&exp);
}

void os_widget_event_loop(void *w_, void* event, Xputty *main, void* user_data) {
    Widget_t *wid = (Widget_t*)w_;
    XEvent *xev = (XEvent*)event;
    if (XFilterEvent(xev, wid->widget))
        return;
    
    switch(xev->type) {
        case ConfigureNotify:
            wid->func.configure_callback(w_, user_data);
            debug_print("Widget_t ConfigureNotify \n");
        break;

        case Expose:
            if (xev->xexpose.count == 0) {
                transparent_draw(w_, user_data);
                debug_print("Widget_t Expose \n");
            }
        break;

        case ButtonPress:
            if (wid->state == 4) break;
            if (wid->flags & HAS_TOOLTIP) hide_tooltip(wid);
            _button_press(wid, &xev->xbutton, user_data);
            debug_print("Widget_t  ButtonPress %i\n", xev->xbutton.button);
        break;

        case ButtonRelease:
            _check_grab(wid, &xev->xbutton, main);
            if (wid->state == 4) break;
            _has_pointer(wid, &xev->xbutton);
            if(wid->flags & HAS_POINTER) wid->state = 1;
            else wid->state = 0;
            _check_enum(wid, &xev->xbutton);
            wid->func.button_release_callback(w_, &xev->xbutton, user_data);
            debug_print("Widget_t  ButtonRelease %i\n", xev->xbutton.button);
        break;

        case KeyPress:
            if (wid->state == 4) break;
            _check_keymap(wid, xev->xkey);
            wid->func.key_press_callback(w_, &xev->xkey, user_data);
            debug_print("Widget_t KeyPress %u\n", xev->xkey.keycode);
        break;

        case KeyRelease: 
            if (wid->state == 4) break;
            {
            unsigned short is_retriggered = 0;
            if(wid->flags & NO_AUTOREPEAT) {
                if (XEventsQueued(main->dpy, QueuedAlready)) {
                    XEvent nev;
                    XPeekEvent(main->dpy, &nev);
                    if (nev.type == KeyPress && nev.xkey.time == xev->xkey.time &&
                        nev.xkey.keycode == xev->xkey.keycode && 
                        (nev.xkey.keycode > 119 || nev.xkey.keycode < 110)) {
                        XNextEvent (main->dpy, xev);
                        is_retriggered = 1;
                    }
                }
            }
            if (!is_retriggered) {
                wid->func.key_release_callback(w_, &xev->xkey, user_data);
                debug_print("Widget_t KeyRelease %u\n", xev->xkey.keycode);
            }
        }
        break;

        case LeaveNotify:
            wid->flags &= ~HAS_FOCUS;
            if (wid->state == 4) break;
            if(!(xev->xcrossing.state & Button1Mask)) {
                wid->state = 0;
                wid->func.leave_callback(w_, user_data);
            }
            if (wid->flags & HAS_TOOLTIP) hide_tooltip(wid);
            debug_print("Widget_t LeaveNotify \n");
        break;

        case EnterNotify:
            wid->flags |= HAS_FOCUS;
            if (wid->state == 4) break;
            if(!(xev->xcrossing.state & Button1Mask)) {
                wid->state = 1;
                wid->func.enter_callback(w_, user_data);
                if (wid->flags & HAS_TOOLTIP) show_tooltip(wid);
                else _hide_all_tooltips(wid);
            }
            debug_print("Widget_t EnterNotify \n");
        break;

        case MotionNotify:
            if (wid->state == 4) break;
            adj_set_motion_state(wid, xev->xmotion.x, xev->xmotion.y);
            wid->func.motion_callback(w_,&xev->xmotion, user_data);
            debug_print("Widget_t MotionNotify x = %i Y = %i \n",xev->xmotion.x,xev->xmotion.y );
        break;

        case ClientMessage:
            if (xev->xclient.message_type == XInternAtom(wid->app->dpy, "WIDGET_DESTROY", 1)) {
                int ch = childlist_has_child(wid->childlist);
                if (ch) {
                    int i = ch;
                    for(;i>0;i--) {
                        quit_widget(wid->childlist->childs[i-1]);
                    }
                    quit_widget(wid);
                } else {
                    destroy_widget(wid,main);
                }
            }

        default:
        break;
    }
    if (main->queue_event) {
        main->queue_event = false;
        transparent_draw(w_, user_data);
    }
}

Atom os_register_wm_delete_window(Widget_t * wid) {
    Atom WM_DELETE_WINDOW;
    WM_DELETE_WINDOW = XInternAtom(wid->app->dpy, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(wid->app->dpy, wid->widget, &WM_DELETE_WINDOW, 1);
    return WM_DELETE_WINDOW;
}

Atom os_register_widget_destroy(Widget_t * wid) {
    return XInternAtom(wid->app->dpy, "WIDGET_DESTROY", False);
}

void os_main_run(Xputty *main) {
    Widget_t * wid = main->childlist->childs[0]; 
    Atom WM_DELETE_WINDOW = os_register_wm_delete_window(wid);

    XEvent xev;
    int ew;

    while (main->run && (XNextEvent(main->dpy, &xev)>=0)) {
        ew = childlist_find_widget(main->childlist, xev.xany.window);
        if(ew  >= 0) {
            Widget_t * w = main->childlist->childs[ew];
            w->event_callback(w, &xev, main, NULL);
        }

        switch (xev.type) {
        case ButtonPress:
            if(main->hold_grab != NULL) {
                Widget_t *view_port = main->hold_grab->childlist->childs[0];
                bool is_item = False;
                int i = view_port->childlist->elem-1;
                for(;i>-1;i--) {
                    Widget_t *w = view_port->childlist->childs[i];
                    if (xev.xbutton.window == w->widget) {
                        is_item = True;
                        break;
                    }
                }
                if (xev.xbutton.window == view_port->widget) is_item = True;
                if (!is_item) {
                    XUngrabPointer(main->dpy,CurrentTime);
                    widget_hide(main->hold_grab);
                    main->hold_grab = NULL;
                }
            }
            break;
            case ClientMessage:
                /* delete window event */
                if (xev.xclient.data.l[0] == (long int)WM_DELETE_WINDOW &&
                        xev.xclient.window == wid->widget) {
                    main->run = false;
                } else {
                    int i = childlist_find_widget(main->childlist, xev.xclient.window);
                    if(i<1) return;
                    Widget_t *w = main->childlist->childs[i];
                    if(w->flags & HIDE_ON_DELETE) widget_hide(w);
                    else destroy_widget(main->childlist->childs[i],main);
                }
            break;
        }
    }
}

void os_run_embedded(Xputty *main) {
    XEvent xev;
    int ew = -1;

    while (XPending(main->dpy) > 0) {
        XNextEvent(main->dpy, &xev);
        ew = childlist_find_widget(main->childlist, xev.xany.window);
        if(ew  >= 0) {
            Widget_t * w = main->childlist->childs[ew];
            unsigned short retrigger = 0;
            if (xev.type == Expose && XEventsQueued(main->dpy, QueuedAlready)) {
                XEvent nev;
                XPeekEvent(main->dpy, &nev);
                if (nev.type == ConfigureNotify) {
                    retrigger = 1;
                    main->queue_event = true;
                }
            }
            if (!retrigger) {
                w->event_callback(w, &xev, main, NULL);
            }
        }
        switch (xev.type) {
        case ButtonPress:
            if(main->hold_grab != NULL) {
                Widget_t *view_port = main->hold_grab->childlist->childs[0];
                bool is_item = False;
                int i = view_port->childlist->elem-1;
                for(;i>-1;i--) {
                    Widget_t *w = view_port->childlist->childs[i];
                    if (xev.xbutton.window == w->widget) {
                        is_item = True;
                        break;
                    }
                }
                if (xev.xbutton.window == view_port->widget) is_item = True;
                if (!is_item) {
                    XUngrabPointer(main->dpy,CurrentTime);
                    widget_hide(main->hold_grab);
                    main->hold_grab = NULL;
                }
            }
        break;
        case ClientMessage:
            /* delete window event */
            if (xev.xclient.data.l[0] == (long int)XInternAtom(main->dpy, "WM_DELETE_WINDOW", True) ) {
                int i = childlist_find_widget(main->childlist, xev.xclient.window);
                if(i<1) return;
                Widget_t *w = main->childlist->childs[i];
                if(w->flags & HIDE_ON_DELETE) widget_hide(w);
                else destroy_widget(w, main);
            }
        break;
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif /* __linux__ */
