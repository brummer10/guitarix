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

#ifndef XPLAYHEAD_PRIVATE_H_
#define XPLAYHEAD_PRIVATE_H_

#include "xplayhead.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief _create_playhead_image            - internal draw the playhead image
 * to the cairo image surface
 * @param *w                                - pointer to the Widget_t meter
 * @param width                             - widget width
 * @param height                            - widget height
 * @return void
 */

void _create_playhead_image(Widget_t *w, int width, int height);

/**
 * @brief _draw_playhead          - internal draw the playhead to the buffer
 * @param *w_                    - void pointer to the Widget_t button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_playhead(void *w_, void* user_data);

#ifdef __cplusplus
}
#endif

#endif //XPLAYHEAD_PRIVATE_H_
