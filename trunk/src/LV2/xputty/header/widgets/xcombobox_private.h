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

#ifndef XCOMBOBOX_PRIVATE_H_
#define XCOMBOBOX_PRIVATE_H_

#include "xcombobox.h"
#include "xbutton_private.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief _draw_combobox_button  - internal draw the combobox button to the buffer
 * @param *w_                    - void pointer to the Widget_t combobox button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_combobox_button(void *w_, void* user_data);

/**
 * @brief _draw_combobox         - internal draw the combobox to the buffer
 * @param *w_                    - void pointer to the Widget_t combobox
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_combobox(void *w_, void* user_data);

/**
 * @brief _combobox_button_released  - popup menu on right click
 * @param *w_                        - void pointer to the Widget_t button
 * @param *button                    - void pointer to XEvent.xbutton struct
 * @param *user_data                 - void pointer to attached user_data
 * @return void
 */

void _combobox_button_released(void *w_, void* button_, void* user_data);

/**
 * @brief _button_combobox_released  - popup the combobox menu
 * @param *w_                        - void pointer to the Widget_t button
 * @param *button                    - void pointer to XEvent.xbutton struct
 * @param *user_data                 - void pointer to attached user_data
 * @return void
 */

void _button_combobox_released(void *w_, void* button_, void* user_data);

/**
 * @brief _entry_released            - the combobox menu release func
 * @param *w_                        - void pointer to the Widget_t menu
 * @param *item                      - void pointer to the selected item *(int*)
 * @param *user_data                 - void pointer to the item label *(const char**)
 * @return void
 */

void _entry_released(void *w_, void* item_, void* user_data);

/**
 * @brief _set_entry                 - set the active combobox entry on adjustment change
 * @param *w_                        - void pointer to the Widget_t combobox
 * @param *user_data                 - void pointer to the item label *(const char**)
 * @return void
 */

void _set_entry(void *w_, void* user_data);


#ifdef __cplusplus
}
#endif

#endif //XCOMBOBOX_PRIVATE_H_
