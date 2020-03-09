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

#ifndef XLISTBOX_H_
#define XLISTBOX_H_

#include "xputty.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief listbox_set_active_entry   - set the active listbox entry
 * @param *w_                        - void pointer to the Widget_t listbox
 * @param active                     - the active entry (int)
 * @return void
 */

void listbox_set_active_entry(Widget_t *w, int active);

/**
 * @brief create_listbox_viewport     - create a viewport on a listbox to a Widget_t
 * @param *parent             - pointer to the Widget_t the listbox should pop over
 * @param width               - define the width of the viewport
 * @param height              - define the height of the viewport
 * @return Widget_t*          - pointer to the Widget_t viewport
 */

Widget_t* create_listbox_viewport(Widget_t *parent, int elem, int width, int height);

/**
 * @brief add_label           - add a listbox to a Widget_t
 * @param *parent             - pointer to the Widget_t request the label
 * @param *label              - Label to show on the button
 * @param x,y,width,height    - the position/geometry to create the label
 * @return Widget_t*          - pointer to the Widget_t label struct
 */

Widget_t* add_listbox(Widget_t *parent, const char * label,
                int x, int y, int width, int height);

/**
 * @brief listbox_add_entry    - add a item to listbox
 * @param *listbox            - pointer to the Widget_t listbox
 * @param *label              - Label to show on the listbox
 * @return Widget_t*          - pointer to the Widget_t listbox_item struct
 */

Widget_t* listbox_add_entry(Widget_t *listbox, const char * label);

#ifdef __cplusplus
}
#endif

#endif //XLISTBOX_H_
