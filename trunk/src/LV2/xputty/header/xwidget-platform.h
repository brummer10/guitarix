/* vim:ts=4:sw=4:et:
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

/*
 * Platform wrapper functions (Linux, MSWindows):
 * This file contains forward definitions and structs for platform support.
 * Platform specific implementations are located in xwidget-linux.cpp
 * and xwidget-mswin.cpp.
 * Xlib compatibility definitions are located in xputty-mswin.h.
 */


#pragma once

#ifndef XWIDGET_PLATFORM_H
#define XWIDGET_PLATFORM_H

#include "xputty.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------
----------------------------------------------------------------------- 
                    wrapper functions
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

void os_create_main_window_and_surface(Widget_t *w, Xputty *app, Window win,
                          int x, int y, int width, int height);


#ifdef __cplusplus
}
#endif

#endif //XWIDGET_PLATFORM_H
