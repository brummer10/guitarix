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

#ifndef XMETER_PRIVATE_H_
#define XMETER_PRIVATE_H_

#include "xmeter.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief _draw_meter_scale    - draw a meter scale beside the meter widget
 * @param w                    - the widget to draw to
 * @return void
 */

void _draw_vmeter_scale(void *w_, void* user_data);

/**
 * @brief _draw_hmeter_scale   - draw a hmeter scale beside the meter widget
 * @param w                    - the widget to draw to
 * @return void
 */

void _draw_hmeter_scale(void *w_, void* user_data);

/**
 * @brief _log_meter           - logaritmic meter deflection
 * @param db                   - mesured db
 * @return float               - state to show on the meter
 */

float _log_meter (float db);

/**
 * @brief _create_vertical_meter_image      - internal draw the meter image
 * to the cairo image surface
 * @param *w                                - pointer to the Widget_t meter
 * @param width                             - widget width
 * @param height                            - widget height
 * @return void
 */

void _create_vertical_meter_image(Widget_t *w, int width, int height);

/**
 * @brief _create_horizontal_meter_image    - internal draw the meter image
 * to the cairo image surface
 * @param *w                                - pointer to the Widget_t meter
 * @param width                             - widget width
 * @param height                            - widget height
 * @return void
 */

void _create_horizontal_meter_image(Widget_t *w, int width, int height);

/**
 * @brief _draw_v_meter          - internal draw the meter to the buffer
 * @param *w_                    - void pointer to the Widget_t button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_v_meter(void *w_, void* user_data);

/**
 * @brief _draw_h_meter          - internal draw the meter to the buffer
 * @param *w_                    - void pointer to the Widget_t button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_h_meter(void *w_, void* user_data);

#ifdef __cplusplus
}
#endif

#endif //XMETER_PRIVATE_H_
