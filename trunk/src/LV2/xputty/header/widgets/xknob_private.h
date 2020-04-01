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

#ifndef XKNOB_PRIVATE_H_
#define XKNOB_PRIVATE_H_

#include "xknob.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief _draw_image_knob       - internal draw the knob from image
 * to the buffer
 * @param *w                     - pointer to the Widget_t knob
 * @return void
 */

void _draw_image_knob(Widget_t *w, int width_t, int height_t);

/**
 * @brief _draw_knob_image       - internal draw the knob to the buffer
 * @param *w_                    - void pointer to the Widget_t button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_knob_image(void *w_, void* user_data);

/**
 * @brief _draw_knob             - internal draw the knob to the buffer
 * @param *w_                    - void pointer to the Widget_t button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_knob(void *w_, void* user_data);

/**
 * @brief _knob_released  - redraw the slider when buttob released 
 * @param *w_               - void pointer to the Widget_t button
 * @param *user_data        - void pointer to attached user_data
 * @return void
 */

void _knob_released(void *w_, void* button_, void* user_data);


#ifdef __cplusplus
}
#endif

#endif //XKNOB_PRIVATE_H_
