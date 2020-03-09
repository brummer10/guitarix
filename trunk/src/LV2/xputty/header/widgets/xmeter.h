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

#ifndef XMETER_H_
#define XMETER_H_

#include "xputty.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief power2db             - power (db) input to db output consider falloff
 * @param power                - mesured power
 * @return float               - calculated db
 */

float power2db(Widget_t *w, float power);

/**
 * @brief add_vmeter          - add a vumeter to a Widget_t
 * connect to func.value_changed_callback to implement your actions
 * @param *parent             - pointer to the Widget_t request the vumeter
 * @param *label              - Label to show on the vumeter
 * @param x,y,width,height    - the position/geometry to create the vumeter
 * @return Widget_t*          - pointer to the Widget_t mete struct
 */

Widget_t* add_vmeter(Widget_t *parent, const char * label, bool show_scale,
                int x, int y, int width, int height);

/**
 * @brief add_hmeter          - add a vumeter to a Widget_t
 * connect to func.value_changed_callback to implement your actions
 * @param *parent             - pointer to the Widget_t request the vumeter
 * @param *label              - Label to show on the vumeter
 * @param x,y,width,height    - the position/geometry to create the vumeter
 * @return Widget_t*          - pointer to the Widget_t meter struct
 */

Widget_t* add_hmeter(Widget_t *parent, const char * label, bool show_scale,
                int x, int y, int width, int height);

#ifdef __cplusplus
}
#endif

#endif //XMETER_H_
