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

#ifndef XTOOLTIP_H_
#define XTOOLTIP_H_

#include "xputty.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief tooltip_set_text     - set a (new) text to a tooltip for Widget_t
 * @param *w                   - pointer to the Widget_t request the tooltip
 * @param *label               - the tooltip text
 * @return void
 */

void tooltip_set_text(Widget_t *w, const char* label);

/**
 * @brief add_tooltip          - add a tooltip to Widget_t
 * @param *w                   - pointer to the Widget_t request the tooltip
 * @param *label               - the tooltip text
 * @return void
 */

void add_tooltip(Widget_t *w, const char* label);

/**
 * @brief create_tooltip      - create a tooltip for a Widget_t
 * @param *parent             - pointer to the Widget_t the tooltip should pop over
 * @param width               - define the width of the tooltip
 * @param height              - define the height of the tooltip
 * @return Widget_t*          - pointer to the Widget_t button struct
 */

Widget_t* create_tooltip(Widget_t *parent, int width, int height);

#ifdef __cplusplus
}
#endif

#endif //XTOOLTIP_H_
