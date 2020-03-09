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

#ifndef XLISTVIEW_H_
#define XLISTVIEW_H_

#include "xputty.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ViewList_t         - struct to hold information for the listview
 * @param prelight_item      - the list item which has the focus
 * @param active_item        - the list item which is selected(active)
 * @param show_items         - the viewable amount of list items
 * @param list_size          - total amount of list items in list
 * @param **list_names       - the list entrys
 */

typedef struct {
    int prelight_item;
    int active_item;
    int show_items;
    int list_size;
    char **list_names;
} ViewList_t;

/**
 * @brief listview_set_active_entry   - set the active listview entry
 * @param *w_                        - void pointer to the Widget_t listview
 * @param active                     - the active entry (int)
 * @return void
 */

void listview_set_active_entry(Widget_t *w, int active);

/**
 * @brief create_listview_viewport     - create a viewport on a listview to a Widget_t
 * @param *parent             - pointer to the Widget_t the listview should pop over
 * @param width               - define the width of the viewport
 * @param height              - define the height of the viewport
 * @return Widget_t*          - pointer to the Widget_t viewport
 */

Widget_t* create_listview_viewport(Widget_t *parent, int elem, int width, int height);

/**
 * @brief add_label           - add a listview to a Widget_t
 * @param *parent             - pointer to the Widget_t request the label
 * @param *label              - Label to show on the button
 * @param x,y,width,height    - the position/geometry to create the label
 * @return Widget_t*          - pointer to the Widget_t label struct
 */

Widget_t* add_listview(Widget_t *parent, const char * label,
                int x, int y, int width, int height);

/**
 * @brief listview_mem_free        - release additional used memory when destroy the Widget_t
 * @param *w_                      - void pointer to the Widget_t
 * @param *user_data               - void pointer to attached user_data
 * @return void
 */

void listview_mem_free(void *w_, void* user_data);

/**
 * @brief listview_set_list   - set a list to a listview  Widget_t
 * @param *listview           - pointer to the Widget_t listview which should show the list
 * @param **list              - pointer to the list
 * @param list_size           - how many items contain the list
 * @return void
 */

void listview_set_list(Widget_t *listview, char **list, int list_size);

#ifdef __cplusplus
}
#endif

#endif //XLISTVIEW_H_
