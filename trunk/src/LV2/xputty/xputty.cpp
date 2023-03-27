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
    main->dpy = os_open_display(0);
    assert(main->dpy);
    main->childlist = (Childlist_t*)malloc(sizeof(Childlist_t));
    assert(main->childlist);
    childlist_init(main->childlist);
    main->color_scheme = (XColor_t*)malloc(sizeof(XColor_t));
    assert(main->color_scheme);
    set_dark_theme(main);
    main->hold_grab = NULL;
    main->run = true;
    main->small_font = 10;
    main->normal_font = 12;
    main->big_font = 16;
    main->queue_event = false;
}

void main_run(Xputty *main) {
  os_main_run(main);
}

void run_embedded(Xputty *main) {
  os_run_embedded(main);
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
    os_close_display(main->dpy);
    debug_print("quit\n");
}
