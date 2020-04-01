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

#ifndef XBUTTON_PRIVATE_H_
#define XBUTTON_PRIVATE_H_

#include "xbutton.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief _rounded_rectangle  - internal draw a rounded button
 * @param x                   - point on x axis
 * @param y                   - point on y axis
 * @param width               - the button width
 * @param height              - the button height
 * @return void
 */

void _rounded_rectangle(cairo_t *cr,float x, float y, float width, float height);

/**
 * @brief _pattern_in         - a little pattern to make press state more visible
 * @param *w_                 - void pointer to the Widget_t button
 * @param st                  - the color state to use
 * @param height              - the button height
 * @return void
 */

void _pattern_out(Widget_t *w, Color_state st, int height);

/**
 * @brief _pattern_in         - a little pattern to make press state more visible
 * @param *w_                 - void pointer to the Widget_t button
 * @param st                  - the color state to use
 * @param height              - the button height
 * @return void
 */

void _pattern_in(Widget_t *w, Color_state st, int height);

/**
 * @brief _draw_ switch_image_button - internal draw the button to the buffer
 * @param *w_                        - void pointer to the Widget_t button
 * @param *user_data                 - void pointer to attached user_data
 * @return void
 */

void _draw_switch_image_button(void *w_, void* user_data);

/**
 * @brief _draw_button        - internal draw the button to the buffer
 * @param *w_                 - void pointer to the Widget_t button
 * @param *user_data          - void pointer to attached user_data
 * @return void
 */

void _draw_button(void *w_, void* user_data);

/**
 * @brief _draw_on_off_button    - internal draw the on/off button to the buffer
 * @param *w_                    - void pointer to the Widget_t button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_on_off_button(void *w_, void* user_data);

/**
 * @brief _draw_ti_button           - internal draw the button to the buffer
 * @param *w_                    - void pointer to the Widget_t button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_ti_button(void *w_, void* user_data);

/**
 * @brief _draw_check_button     - internal draw the button to the buffer
 * @param *w_                    - void pointer to the Widget_t button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_check_button(void *w_, void* user_data);

/**
 * @brief _draw_check_box        - internal draw the check box to the buffer
 * @param *w_                    - void pointer to the Widget_t button
 * @param *user_data             - void pointer to attached user_data
 * @return void
 */

void _draw_check_box(void *w_, void* user_data);

/*---------------------------------------------------------------------
-----------------------------------------------------------------------	
                            button
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

/**
 * @brief _button_pressed   - redraw the button and send state via user_callback
 * @param *w_               - void pointer to the Widget_t button
 * @param *button           - void pointer to XEvent.xbutton struct
 * @param *user_data        - void pointer to attached user_data
 * @return void
 */

void _button_pressed(void *w_, void* button, void* user_data);

/**
 * @brief _button_released  - redraw the button and send state via user_callback
 * @param *w_               - void pointer to the Widget_t button
 * @param *button           - void pointer to XEvent.xbutton struct
 * @param *user_data        - void pointer to attached user_data
 * @return void
 */

void _button_released(void *w_, void* button_, void* user_data);

/*---------------------------------------------------------------------
-----------------------------------------------------------------------	
                        toggle button
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

/**
 * @brief _toggle_button_pressed  - redraw the button and send state via user_callback
 * @param *w_                     - void pointer to the Widget_t button
 * @param *button                 - void pointer to XEvent.xbutton struct
 * @param *user_data              - void pointer to attached user_data
 * @return void
 */

void _toggle_button_pressed(void *w_, void* button, void* user_data);

/**
 * @brief _toggle_button_released  - redraw the button and send state via user_callback
 * @param *w_                      - void pointer to the Widget_t button
 * @param *button                  - void pointer to XEvent.xbutton struct
 * @param *user_data               - void pointer to attached user_data
 * @return void
 */

void _toggle_button_released(void *w_, void* button_, void* user_data);

#ifdef __cplusplus
}
#endif

#endif // XBUTTON_PRIVATE_H_
