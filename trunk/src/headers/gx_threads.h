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
 */

/* ------- This is the threads namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_THREADS_H_
#define SRC_HEADERS_GX_THREADS_H_

namespace gx_threads {

/* --------------  function declarations ---------------- */
/* slow GTK threads, see GxMainInterface::run() */
gboolean gx_update_all_gui(gpointer args);
gboolean gx_refresh_meter_level(gpointer arg);
gboolean gx_check_cab_state(gpointer args);
void cab_conv_restart();
void contrast_conv_restart();

/* --------- calculate power (percent) to decibel -------- */
// Note: could use fast_log10 (see ardour code) to make it faster
inline float power2db(float power) {
    return  20.*log10(power);
}
}
#endif  // SRC_HEADERS_GX_THREADS_H_
