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


#include "xtuner.h"
#include "xtuner_private.h"

void tuner_set_temperament (Widget_t *w, float temp) {
    XTuner *xt = (XTuner *)w->parent_struct;
    xt->temperament = temp;
    if((int)temp == 0) xt->temp_adjust = 3;
    else if((int)temp == 1) xt->temp_adjust =  6;
    else if((int)temp == 2) xt->temp_adjust =  7;
    else if((int)temp == 3) xt->temp_adjust =  9;
    else if((int)temp == 4) xt->temp_adjust =  15;
    else xt->temp_adjust = 3;
}

void tuner_set_ref_freq (Widget_t *w, float ref) {
    XTuner *xt = (XTuner *)w->parent_struct;
    xt->ref_freq = ref;
}

static void xtuner_mem_free(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    XTuner *xt = (XTuner *)w->parent_struct;
    free(xt);
}

Widget_t* add_tuner(Widget_t *parent, const char * label,
                int x, int y, int width, int height) {

    XTuner *xt = (XTuner*)malloc(sizeof(XTuner));
    xt->ref_freq = 440.0;
    xt->temp_adjust = 3;
    xt->temperament = 0;
    xt->move = 0;
    xt->smove = 0;
    Widget_t *wid = create_widget(parent->app, parent, x, y, width, height);
    wid->parent_struct = xt;
    wid->label = label;
    wid->adj_y = add_adjustment(wid,20.0, 20.0, 20.0, 20000.0,0.01, CL_CONTINUOS);
    wid->adj = wid->adj_y;
    wid->scale.gravity = CENTER;
   // wid->flags &= ~USE_TRANSPARENCY;
    wid->flags |= HAS_MEM;
    cairo_select_font_face (wid->crb, "FreeMono", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_NORMAL);
    wid->func.mem_free_callback = xtuner_mem_free;
    wid->func.expose_callback = _draw_tuner;
    return wid;
}
