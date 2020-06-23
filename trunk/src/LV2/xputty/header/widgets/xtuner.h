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

#pragma once

#ifndef XTUNER_H_
#define XTUNER_H_

#include "xputty.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    float ref_freq;
    float temperament;
    int temp_adjust;
    int move;
    int smove;
} XTuner;

void tuner_set_temperament (Widget_t *w, float temp);

void tuner_set_ref_freq (Widget_t *w, float ref);

/**
 * @brief add_tuner           - add a tuner widget to a Widget_t
 * @param *parent             - pointer to the Widget_t request the tuner
 * @param *label              - Label to show on the tuner
 * @param x,y,width,height    - the position/geometry to create the tuner
 * @return Widget_t*          - pointer to the Widget_t tuner struct
 */

Widget_t* add_tuner(Widget_t *parent, const char * label,
                int x, int y, int width, int height);

#ifdef __cplusplus
}
#endif

#endif //XTUNER_H_
