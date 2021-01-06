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

/**
 * here are the private functions from xwidget
 */

#pragma once

#ifndef XWIDGET_PRIVATE_H_
#define XWIDGET_PRIVATE_H_

#include "xputty.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief _scroll_event     - internal check which Adjustment_t change it's value
 * on a motion event (POINTER_MOTION)
 * @param *wid              - pointer to the Widget_t receiving a event
 * @param direction         - up/down scroll diretion
 * @return void 
 */

void _scroll_event(Widget_t * wid, int direction);
/**
 * @brief _toggle_event     - internal check which Adjustment_t change it's value
 * on a Button press event (BUTTON_PRESS)
 * @param *wid              - pointer to the Widget_t receiving a event
 * @return void 
 */

void _toggle_event(Widget_t * wid);

/**
 * @brief _check_enum       - internal check if Adjustment_t is of type CL_ENUM
 * and handle events accordingly
 * @param *wid              - pointer to the Widget_t receiving a event
 * @param *xbutton          - pointer to the XButtonEvent
 * @return void 
 */

void _check_enum(Widget_t * wid, XButtonEvent *xbutton);

/**
 * @brief _button_press     - internal check which button is pressed (BUTTON_PRESS)
 * @param *wid              - pointer to the Widget_t receiving a event
 * @param *xbutton          - pointer to the XButtonEvent
 * @param *user_data        - void pointer to attached user_data
 * @return void 
 */

void _button_press(Widget_t * wid, XButtonEvent *xbutton, void* user_data);

/**
 * @brief _check_grab       - internal check if a Widgt_t holds a grab
 * when a BUTTON_PRESS event occur. If so, check if the button is pressed
 * inside the grab Widget_t. If yes, handle the event. In any case destroy the grab
 * @param *wid              - pointer to the Widget_t receiving a event
 * @param *xbutton          - pointer to the XButtonEvent
 * @param *main             - pointer to main struct
 * @return void 
 */

void _check_grab(Widget_t * wid, XButtonEvent *xbutton, Xputty *main);

/**
 * @brief _propagate_child_expose - send expose to any child Widget_t
 * @param *wid                    - pointer to the Widget_t send the event
 * @return void 
 */

void _propagate_child_expose(Widget_t *wid);

/**
 * @brief _check_keymap     - check if key is in map, send requests if so 
 * @param *w                - pointer to the Widget_t receiving the event
 * @param xkey              - the XKeyEvent to check
 * @return void
 */

void _check_keymap (void *w_ , XKeyEvent xkey);

/**
 * @brief _hide_all_tooltips - hide all active tooltips
 * @param *wid               - pointer to the Widget_t receiving the event
 * @return void
 */

void _hide_all_tooltips(Widget_t *wid);

/**
 * @brief _has_pointer      - check if the widget has the pointer 
 * @param *w                - pointer to the Widget_t sending the request
 * @param *button           - pointer to the XButtonEvent sending the notify
 * @return void
 */

void _has_pointer(Widget_t *w, XButtonEvent *button);

/**
 * @brief _set_adj_value    - set value to adjustment from key event
 * @param *w                - pointer to the Widget_t receiving the event
 * @param x                 - use x or y-axis
 * @return void
 */

void _set_adj_value(void *w_, bool x, int direction);

/**
 * @brief _dummy1_callback   - default debugging callback for evfunc's
 * @param *w                 - pointer to the Widget_t receive the event
 * @param user_data          - void pointer to attached user_data
 * @return void 
 */

void _dummy1_callback(void *w_, void* _data, void* user_data);

/**
 * @brief _dummy1_callback    - default debugging callback for xevfunc's
 * @param *w                 - pointer to the Widget_t receive the event
 * @param user_data          - void pointer to attached user_data
 * @return void 
 */

void _dummy_callback(void *w_, void* user_data);

/**
 * @brief _resize_surface    - intern check if a Widget_t surfaces needs resizing
 * @param *wid               - pointer to the Widget_t receive the event
 * @param width              - the new width
 * @param height             - the new height
 * @return void 
 */

void _resize_surface(Widget_t *wid, int width, int height);

/**
 * @brief _resize_childs     - intern check if child widgets needs resizing
 * @param *wid               - pointer to the Widget_t receive the event
 * @return void 
 */

void _resize_childs(Widget_t *wid);

#ifdef __cplusplus
}
#endif

#endif // XWIDGET_PRIVATE_H__
