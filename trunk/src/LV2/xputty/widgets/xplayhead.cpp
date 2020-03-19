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


#include "xplayhead.h"
#include "xplayhead_private.h"

void playhead_mem_free(void *w_, void* user_data) {
    Widget_t *wid = (Widget_t*)w_;
    wid->adj_x = NULL;
    wid->adj_y = NULL;
}


Widget_t* add_playhead(Widget_t *parent, const char * label, Adjustment_t *clip,
                Adjustment_t *cut, int x, int y, int width, int height) {

    Widget_t *wid = create_widget(parent->app, parent, x, y, width, height);
    _create_playhead_image(wid, width, height);
    wid->flags |= HAS_MEM;
    wid->label = label;
    wid->adj = add_adjustment(wid,0.0, 0.0, 0.0, 1000.0,1.0, CL_METER);
    wid->adj_x = clip;
    wid->adj_y = cut;
    wid->scale.gravity = ASPECT;
    wid->func.expose_callback = _draw_playhead;
    wid->func.mem_free_callback = playhead_mem_free;
    return wid;
}
