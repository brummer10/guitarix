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

#include "xputty.h"


void main_init(Xputty *main) {
    main->dpy = XOpenDisplay(0);
    assert(main->dpy);
    main->childlist = (Childlist_t*)malloc(sizeof(Childlist_t));
    assert(main->childlist);
    childlist_init(main->childlist);
    main->color_scheme = (XColor_t*)malloc(sizeof(XColor_t));
    assert(main->color_scheme);
    set_dark_theme(main);
    main->hold_grab = NULL;
    main->run = true;
}

void main_run(Xputty *main) {
    Widget_t * wid = main->childlist->childs[0]; 
    Atom WM_DELETE_WINDOW;
    WM_DELETE_WINDOW = XInternAtom(wid->app->dpy, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(wid->app->dpy, wid->widget, &WM_DELETE_WINDOW, 1);

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

void run_embedded(Xputty *main) {

    XEvent xev;
    int ew = -1;

    while (XPending(main->dpy) > 0) {
        XNextEvent(main->dpy, &xev);
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

void main_quit(Xputty *main) {
    int i = main->childlist->elem-1;
    for(;i>-1;i--) {
        Widget_t *w = main->childlist->childs[i];
        destroy_widget(w, main);
    }
    childlist_destroy(main->childlist);
    free(main->childlist);
    free(main->color_scheme);
    XCloseDisplay(main->dpy);
    debug_print("quit\n");
}
