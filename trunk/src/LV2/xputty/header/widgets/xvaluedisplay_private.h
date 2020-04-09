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

#ifndef XVALUEDISPLAY_PRIVATE_H_
#define XVALUEDISPLAY_PRIVATE_H_

#include "xvaluedisplay.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief _draw_valuedisplay   - draw a valuedisplay on expose call
 * @param *w_                  - The Widget_t contain the valuedisplay
 * @param *user_data           - attached user_data
 * @return void
 */

void _draw_valuedisplay(void *w_, void* user_data);

#ifdef __cplusplus
}
#endif

#endif //XVALUEDISPLAY_PRIVATE_H_
