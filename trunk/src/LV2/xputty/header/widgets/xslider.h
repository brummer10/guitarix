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

#ifndef XSLIDER_H_
#define XSLIDER_H_

#include "xputty.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief add_vslider          - add a vertical slider to a Widget_t
 * connect to func.value_changed_callback to implement your actions
 * use set_adjustment(w->adj_y, . . ) to set the range you need
 * @param *parent             - pointer to the Widget_t request the button
 * @param *label              - Label to show on the button
 * @param x,y,width,height    - the position/geometry to create the button
 * @return Widget_t*          - pointer to the Widget_t button struct
 */

Widget_t* add_vslider(Widget_t *parent, const char * label,
                int x, int y, int width, int height);

/**
 * @brief add_hslider          - add a horizontal slider to a Widget_t
 * connect to func.value_changed_callback to implement your actions
 * use set_adjustment(w->adj_x, . . ) to set the range you need
 * @param *parent             - pointer to the Widget_t request the button
 * @param *label              - Label to show on the button
 * @param x,y,width,height    - the position/geometry to create the button
 * @return Widget_t*          - pointer to the Widget_t button struct
 */

Widget_t* add_hslider(Widget_t *parent, const char * label,
                int x, int y, int width, int height);

#ifdef __cplusplus
}
#endif

#endif //XSLIDER_H_
