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

#ifndef XBUTTON_H_
#define XBUTTON_H_

#include "xputty.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief add_button          - add a button to a Widget_t
 * connect to func.value_changed_callback to implement your actions
 * @param *parent             - pointer to the Widget_t request the button
 * @param *label              - Label to show on the button
 * @param x,y,width,height    - the position/geometry to create the button
 * @return Widget_t*          - pointer to the Widget_t button struct
 */

Widget_t* add_button(Widget_t *parent, const char * label,
                int x, int y, int width, int height);

/**
 * @brief add_on_off_button    - add a button with default on/off label to a Widget_t
 * connect to func.value_changed_callback to implement your actions
 * @param *parent             - pointer to the Widget_t request the button
 * @param *label              - Label (ignored)
 * @param x,y,width,height    - the position/geometry to create the button
 * @return Widget_t*          - pointer to the Widget_t button struct
 */

Widget_t* add_on_off_button(Widget_t *parent, const char * label,
                int x, int y, int width, int height);

/**
 * @brief add_toggle_button          - add a button to a Widget_t
 * connect to func.value_changed_callback to implement your actions
 * @param *parent             - pointer to the Widget_t request the button
 * @param *label              - Label to show on the button
 * @param x,y,width,height    - the position/geometry to create the button
 * @return Widget_t*          - pointer to the Widget_t button struct
 */

Widget_t* add_toggle_button(Widget_t *parent, const char * label,
                int x, int y, int width, int height);

/**
 * @brief add_image_toggle_button          - add a button to a Widget_t
 * connect to func.value_changed_callback to implement your actions
 * @param *parent             - pointer to the Widget_t request the button
 * @param *label              - Label to show on the button
 * @param x,y,width,height    - the position/geometry to create the button
 * @return Widget_t*          - pointer to the Widget_t button struct
 */

Widget_t* add_image_toggle_button(Widget_t *parent, const char * label,
                int x, int y, int width, int height);

/**
 * @brief add_check_button    - add a button to a Widget_t
 * connect to func.value_changed_callback to implement your actions
 * @param *parent             - pointer to the Widget_t request the button
 * @param *label              - Label to show on the button
 * @param x,y,width,height    - the position/geometry to create the button
 * @return Widget_t*          - pointer to the Widget_t button struct
 */

Widget_t* add_check_button(Widget_t *parent, const char * label,
                int x, int y, int width, int height);

/**
 * @brief add_check_box       - add a check box to a Widget_t
 * connect to func.value_changed_callback to implement your actions
 * @param *parent             - pointer to the Widget_t request the button
 * @param *label              - Label to show on the button
 * @param x,y,width,height    - the position/geometry to create the button
 * @return Widget_t*          - pointer to the Widget_t button struct
 */

Widget_t* add_check_box(Widget_t *parent, const char * label,
                int x, int y, int width, int height);

#ifdef __cplusplus
}
#endif

#endif // XBUTTON_H_
