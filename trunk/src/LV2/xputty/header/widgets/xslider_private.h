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

#ifndef XSLIDER_PRIVATE_H_
#define XSLIDER_PRIVATE_H_

#include "xslider.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief _pattern_vslider  - set pattern for the slider base
 * @param *w_               - void pointer to the Widget_t button
 * @param st                - the Widget_t Color_t mode to use
 * @param width             - the width of the base
 * @return void
 */

void _pattern_vslider(Widget_t *w, Color_state st, int width);

/**
 * @brief _pattern_hslider  - set pattern for the slider base
 * @param *w_               - void pointer to the Widget_t button
 * @param st                - the Widget_t Color_t mode to use
 * @param width             - the width of the base
 * @return void
 */

void _pattern_hslider(Widget_t *w, Color_state st, int width);

/**
 * @brief _draw_vslider          - internal draw the slider to the buffer
 * @param *w_                    - void pointer to the Widget_t button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_vslider(void *w_, void* user_data);

/**
 * @brief _draw_hslider          - internal draw the slider to the buffer
 * @param *w_                    - void pointer to the Widget_t button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_hslider(void *w_, void* user_data);

/**
 * @brief _slider_released  - redraw the slider when button released 
 * @param *w_               - void pointer to the Widget_t button
 * @param *user_data        - void pointer to attached user_data
 * @return void
 */

void _slider_released(void *w_, void* button_, void* user_data);

#ifdef __cplusplus
}
#endif

#endif //XSLIDER_PRIVATE_H_
