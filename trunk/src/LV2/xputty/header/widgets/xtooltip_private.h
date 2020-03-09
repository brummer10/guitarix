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

#ifndef XTOOLTIP_PRIVATE_H_
#define XTOOLTIP_PRIVATE_H_

#include "xtooltip.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief _get_width           - get the width of a tooltip text and resize the
 * tooltip widget to match the size
 * @param *w                   - the tooltip Widget_t
 * @return void
 */

void _get_width(Widget_t *w);

/**
 * @brief _draw_tooltip        - draw tooltip on expose call
 * @param *w_                  - the tooltip to draw
 * @param *user_data           - attached user_data
 * @return void
 */

void _draw_tooltip(void *w_, void* user_data);

#ifdef __cplusplus
}
#endif

#endif //XTOOLTIP_PRIVATE_H_
