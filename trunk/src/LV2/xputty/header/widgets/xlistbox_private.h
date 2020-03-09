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

#ifndef XLISTBOX_PRIVATE_H_
#define XLISTBOX_PRIVATE_H_

#include "xlistbox.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief _draw_listbox           - draw listbox on expose call
 * @param *w_                  - the listbox to draw
 * @param *user_data           - attached user_data
 * @return void
 */

void _draw_listbox(void *w_, void* user_data);

/**
 * @brief _draw_listbox_item   - draw item on expose call
 * @param *w_                  - the item to draw
 * @param *user_data           - attached user_data
 * @return void
 */

void _draw_listbox_item(void *w_, void* user_data);

/**
 * @brief _draw_listbox_viewslider - draw a slider on the viewport
 * to indicate the view point
 * @param *w_                      - void pointer to view_port
 * @param *user_data               - attached user_data
 * @return void
 */

void _draw_listbox_viewslider(void *w_, void* user_data);

/**
 * @brief _reconfigure_listbox_viewport - reconfigure the viewport adjustment
 * on size changes
 * @param *w_                      - void pointer to view_port
 * @param *user_data               - attached user_data
 * @return void
 */

void _reconfigure_listbox_viewport(void *w_, void* user_data);

/**
 * @brief _configure_listbox       - configure the viewport on mapping
 * @param *w_                      - void pointer to view_port
 * @param *user_data               - attached user_data
 * @return void
 */

void _configure_listbox(void *w_, void* user_data);

/**
 * @brief _set_listbox_viewpoint  - move the view_port to position
 * @param *w_                     - void pointer to view_port
 * @param *user_data              - attached user_data
 * @return void
 */

void _set_listbox_viewpoint(void *w_, void* user_data);

/**
 * @brief _listbox_entry_released  - redraw the slider when buttob released 
 * @param *w_                      - void pointer to the Widget_t entry
 * @param *button_                 - void pointer to the XButtonEvent
 * @param *user_data               - void pointer to attached user_data
 * @return void
 */

void _listbox_entry_released(void *w_, void* button_, void* user_data);

#ifdef __cplusplus
}
#endif

#endif //XLISTBOX_PRIVATE_H_
