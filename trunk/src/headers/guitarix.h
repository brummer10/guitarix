/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * --------------------------------------------------------------------------
 *
 *
 *    This is the main guitarix header file. It simply contains the
 *    more specific headers. Note that each header is trying to be
 *    self-contained, i.e. only depends on system declarations.  Let's
 *    try to keep it that way.
 *
 *
 * --------------------------------------------------------------------------
 */

#pragma once

#ifndef SRC_HEADERS_GUITARIX_H_
#define SRC_HEADERS_GUITARIX_H_

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#ifndef GDK_KEY_0
/* 
** compatibility definitions for gdkkeysyms.h before the change in gtk git on 2010-09-08
** can be removed at some point
** list created with:
** tools/search_all GDK_KEY | sed -n 's/\(GDK_KEY_[a-zA-Z0-9_]*\)/\n\1\n/gp' | sort -u \
**   | awk '/GDK_KEY/{v=$0; sub("GDK_KEY_", "GDK_", v); print "#define " $0 " " v}'
*/
#define GDK_KEY_0 GDK_0
#define GDK_KEY_1 GDK_1
#define GDK_KEY_9 GDK_9
#define GDK_KEY_a GDK_a
#define GDK_KEY_A GDK_A
#define GDK_KEY_B GDK_B
#define GDK_KEY_Down GDK_Down
#define GDK_KEY_Escape GDK_Escape
#define GDK_KEY_KP_0 GDK_KP_0
#define GDK_KEY_KP_1 GDK_KP_1
#define GDK_KEY_KP_9 GDK_KP_9
#define GDK_KEY_Left GDK_Left
#define GDK_KEY_M GDK_M
#define GDK_KEY_Return GDK_Return
#define GDK_KEY_Right GDK_Right
#define GDK_KEY_space GDK_space
#define GDK_KEY_Up GDK_Up
#define GDK_KEY_z GDK_z
#define GDK_KEY_Z GDK_Z
#endif

#include <gtkmm.h>

#include "engine.h"

#include "gx_cairo_callbacks.h"

#include "gx_gui_helpers.h"
#include "gx_ui_builder.h"
#include "gx_jack_options.h"
#include "gx_portmap.h"
#include "gx_main_midi.h"
#include "gx_main_boxes.h"
#include "gx_child_process.h"
#include "gx_main_interface.h"
#include "gx_jconv_settings.h"
#include "gx_stackbox_builder.h"
#include "gx_preset_window.h"
#include "gx_main_window.h"

#endif  // SRC_HEADERS_GUITARIX_H_
