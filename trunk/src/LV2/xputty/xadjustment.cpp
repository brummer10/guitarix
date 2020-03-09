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

#include "xadjustment.h"
#include "xadjustment_private.h"


Adjustment_t *add_adjustment(Widget_t *w, float std_value, float value,
                float min_value,float max_value, float step, CL_type type) {
    Adjustment_t *adj = (Adjustment_t*)malloc(sizeof(Adjustment_t));
    assert(adj);
    *(adj) = (Adjustment_t){w, std_value, value, min_value, max_value, step, value, 1.0, type};

    debug_print("Widget_t add adjustment\n");
    return adj;
}

void set_adjustment(Adjustment_t *adj, float std_value, float value,
                float min_value,float max_value, float step, CL_type type) {
    if (!adj)
    adj = (Adjustment_t*)malloc(sizeof(Adjustment_t));
    assert(adj);
    *(adj) = (Adjustment_t){adj->w, std_value, value, min_value, max_value, step, value, 1.0, type};

    debug_print("Widget_t set adjustment\n");
}

void *delete_adjustment(Adjustment_t *adj) {
    if(adj) {
        free(adj);
        debug_print("Widget_t delete adjustment\n");
    }
    return NULL;
}

void adj_set_state(Adjustment_t *adj, float state) {
    if (!adj) return;
    float nvalue = min(1.0,max(0.0,state));
    float value = nvalue * (adj->max_value - adj->min_value) + adj->min_value;
    check_value_changed(adj, &value);
}

float adj_get_state(Adjustment_t *adj) {
    if (!adj) return 0.0;
    return (adj->value - adj->min_value) /
       (adj->max_value - adj->min_value);
}

float adj_get_value(Adjustment_t *adj) {
    if (!adj) return 0.0;
    return (adj->value);
}

void adj_set_value(Adjustment_t *adj, float v) {
    if (!adj) return;
    v = min(adj->max_value,max(adj->min_value, v));
    check_value_changed(adj, &v);
}

void adj_set_start_value(void *w) {
    Widget_t * wid = (Widget_t*)w;
    if(wid->adj_x)wid->adj_x->start_value = wid->adj_x->value;
    if(wid->adj_y)wid->adj_y->start_value = wid->adj_y->value;
}

void adj_set_scale(Adjustment_t *adj, float value) {
    adj->scale = value;
}

void adj_set_motion_state(void *w, float x, float y) {
    Widget_t * wid = (Widget_t*)w;
    if(wid->adj_x) {
        float value= wid->adj_x->value;
        switch(wid->adj_x->type) {
            case (CL_CONTINUOS):
            {
                float state = (wid->adj_x->start_value - wid->adj_x->min_value) / 
                    (wid->adj_x->max_value - wid->adj_x->min_value);
                float nsteps = wid->adj_x->step / (wid->adj_x->max_value - wid->adj_x->min_value);
                float nvalue = min(1.0,max(0.0,state + ((float)(x - wid->pos_x)*wid->adj_x->scale *nsteps)));
                float prevalue = nvalue * (wid->adj_x->max_value - wid->adj_x->min_value) + wid->adj_x->min_value;
                float mulscale = round(prevalue/wid->adj_x->step);
                value = mulscale*wid->adj_x->step;
            }
            break;
            case (CL_TOGGLE):
                // dont toggle on motion!
                // value = wid->adj_x->value ? 0.0 : 1.0;
            break;
            default:
            break;
        }
        check_value_changed(wid->adj_x, &value);
    }
    if(wid->adj_y) {
        float value = wid->adj_y->value;
        switch(wid->adj_y->type) {
            case (CL_CONTINUOS):
            {
                float state = (wid->adj_y->start_value - wid->adj_y->min_value) / 
                    (wid->adj_y->max_value - wid->adj_y->min_value);
                float nsteps = wid->adj_y->step / (wid->adj_y->max_value - wid->adj_y->min_value);
                float nvalue = min(1.0,max(0.0,state + ((float)(wid->pos_y - y)*wid->adj_y->scale *nsteps)));
                float prevalue = nvalue * (wid->adj_y->max_value - wid->adj_y->min_value) + wid->adj_y->min_value;
                float mulscale = round(prevalue/wid->adj_y->step);
                value = (float)mulscale*wid->adj_y->step;
            }
            break;
            case (CL_TOGGLE):
                // dont toggle on motion!
                // value = wid->adj_y->value ? 0.0 : 1.0;
            break;
            default:
            break;
        }
        check_value_changed(wid->adj_y, &value);
    }
}

void check_value_changed(Adjustment_t *adj, float *value) {
    debug_print("Adjustment_t check_value_changed %f\n", *(value));
    if(fabs(*(value) - adj->value)>=0.00001) {
        adj->value = *(value);
        adj->w->func.adj_callback(adj->w, NULL);
        adj->w->func.value_changed_callback(adj->w, value);
    }
}
