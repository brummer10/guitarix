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
 *  This is the guitarix global variable declarations for all namespaces
 *  These global vars are created  /  initialized in gx_globals.cpp
 *
 * --------------------------------------------------------------------------
 */

#pragma once

#ifndef SRC_HEADERS_GX_GLOBALS_H_
#define SRC_HEADERS_GX_GLOBALS_H_

#include <semaphore.h>
#include <jack/midiport.h>
#include <gtk/gtk.h>

#include <string>
#include <vector>

/* ----- main engine ----- */
namespace gx_engine {
/* engine state : can be on or off or bypassed */
typedef enum {
    kEngineOff    = 0,
    kEngineOn     = 1,
    kEngineBypass = 2
} GxEngineState;

typedef enum {
    kMidiOff    = 0,
    kMidiOn     = 1
} GxMidiState;

/* global var  declarations */
extern GxEngineState checky;
extern float* get_frame;
extern float* get_frame1;
extern float* checkfreq;
extern float* oversample;
extern float* result;

/* latency warning  switch */
extern float fwarn;

/* engine init state  */
extern bool initialized;
inline bool isInitialized() { return initialized; }

/* pitchtracker init state  */
extern bool pt_initialized;

/* buffer ready state */
extern bool buffers_ready;
}

/* -------------------------------------------------------------------------- */


/* ----- system namespace ----- */
namespace gx_system {

/* variables and constants */
extern const int SYSTEM_OK;

extern bool is_session;

extern string rcpath;

extern const char*  jcapsetup_file;
extern const char*  jcapfile_wavbase;
extern const string gx_pixmap_dir;
extern const string gx_user_dir;
extern string gx_style_dir;
extern string gx_builder_dir;

/* shell variable names */
extern const char* shell_var_name[];
}

/* -------------------------------------------------------------------------- */

/* ----- GUI namespace ----- */
namespace gx_gui {

/* tuner and osilloscope*/
extern int showwave;
extern int shownote;
extern float show_patch_info;

/* rack handlig */
extern int mono_plugs;
extern int stereo_plugs;
extern int refresh_size;

/* widget orientation */
extern float main_xorg;
extern float main_yorg;

/* for level display */
extern int meter_falloff;
extern int meter_display_timeout;

/*midi_in preset switch */
extern volatile gint       program_change;
extern sem_t               program_change_sem;

extern int g_threads[10];
}

/* -------------------------------------------------------------------------- */

/* ----- cairo namespace ----- */
namespace gx_cairo {
extern GdkPixbuf *tribeimage;
extern GdkPixbuf *tribeimage1;
extern GdkPixbuf *tribeimage2;
}
#endif  // SRC_HEADERS_GX_GLOBALS_H_

