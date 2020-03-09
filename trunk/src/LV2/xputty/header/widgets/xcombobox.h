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

#ifndef XCOMBOBOX_H_
#define XCOMBOBOX_H_

#include "xputty.h"
#include "xmenu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief add_combobox        - add a combobox
 * @param *parent             - pointer to the Widget_t request the button
 * @param x,y,width,height    - the position/geometry to create the button
 * @return Widget_t*          - pointer to the Widget_t button struct
 */

Widget_t* add_combobox(Widget_t *parent, const char  * label, int x, int y, int width, int height);

/**
 * @brief combobox_add_entry    - add a entry to the combobox
 * @param *wid                  - pointer to the Widget_t combobox
 * @param *label                - Label to show on the menu
 * @return Widget_t*            - pointer to the Widget_t menu_item struct
 */

Widget_t *combobox_add_entry(Widget_t *wid, const char  * label);

/**
 * @brief combobox_set_active_entry  - set the active combobox entry
 * @param *w_                        - void pointer to the Widget_t combobox
 * @param active                     - the active entry (int)
 * @return void
 */

void combobox_set_active_entry(Widget_t *w, int active);

#ifdef __cplusplus
}
#endif

#endif //XCOMBOBOX_H_
