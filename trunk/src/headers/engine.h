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

#pragma once

#ifndef SRC_HEADERS_ENGINE_H_
#define SRC_HEADERS_ENGINE_H_

#ifdef GUITARIX_AS_PLUGIN
#define GX_DATA_FOLDER "gx_head/"
#define GX_STYLE_DIR GX_DATA_FOLDER ""
#define GX_FACTORY_DIR GX_DATA_FOLDER "factorysettings"
#define GX_SOUND_DIR GX_DATA_FOLDER "sounds"
#define GX_SOUND_BPB_DIR GX_DATA_FOLDER "sounds/bands"
#define GX_SOUND_BPA_DIR GX_DATA_FOLDER "sounds/amps"
#define GX_BUILDER_DIR GX_DATA_FOLDER ""
#define GX_ICON_DIR GX_DATA_FOLDER ""
#define GX_PIXMAPS_DIR GX_DATA_FOLDER ""
#define GX_FONTS_DIR GX_DATA_FOLDER ""
#define GX_VERSION "0.44.1"
#endif // GUITARIX_AS_PLUGIN

/* system header files */
#include <semaphore.h>
#include <cmath>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <sys/stat.h>
#include <boost/format.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>
#include <glibmm/i18n.h>     // NOLINT
#include <glibmm/optioncontext.h>   // NOLINT
#include <glibmm/dispatcher.h>
#include <glibmm/miscutils.h>
#include <giomm/file.h>

/* LV2 header files */
#include <lilv/lilv.h>
#include "lv2/lv2plug.in/ns/ext/presets/presets.h"
#include "lv2/lv2plug.in/ns/ext/state/state.h"
#include "lv2/lv2plug.in/ns/ext/urid/urid.h"
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/buf-size/buf-size.h>
#include <lv2/lv2plug.in/ns/ext/options/options.h>
#include <lv2/lv2plug.in/ns/ext/uri-map/uri-map.h>
#include <lv2/lv2plug.in/ns/ext/port-props/port-props.h>

#ifndef GUITARIX_AS_PLUGIN
/* waf generated defines */
#include "../config.h"
#endif // GUITARIX_AS_PLUGIN

// define USE_MIDI_OUT to create a midi output port and
// make the MidiAudioBuffer plugin activatable
// for the UI:
// - menudef.xml: make action MidiOut visible (its commented out)
// - ports.glade: set scrolledwindow5 and label12 to visible
//
//#define USE_MIDI_OUT

// use MIDI controll out
#define USE_MIDI_CC_OUT

#ifdef LADSPA_SO
#define gettext(x) dgettext(GETTEXT_PACKAGE, x)
#endif

#ifndef LV2_CORE__enabled
#define LV2_CORE__enabled LV2_CORE_PREFIX "enabled"
#endif

using namespace std;

#include "gx_compiler.h"

/* guitarix declarations */
#include "gx_plugin.h"
#include "gx_logging.h"
#include "gx_system.h"
#include "gx_parameter.h"

#include "gx_resampler.h"
#include "gx_convolver.h"
#include "gx_pitch_tracker.h"
#include "gx_pluginloader.h"
#include "gx_modulesequencer.h"
#include "gx_json.h"

#ifndef GUITARIX_AS_PLUGIN
#include "gx_jack.h"
#else
#include "gx_jack_wrapper.h"
#endif // GUITARIX_AS_PLUGIN
#include "gx_internal_plugins.h"
#include "gx_preset.h"
#include "gx_engine.h"

#include "tunerswitcher.h"
#include "ladspaback.h"

#ifdef GUITARIX_AS_PLUGIN
#include <glibmm/i18n.h>     // NOLINT
#include <glibmm/optioncontext.h>   // NOLINT
#include <glibmm/dispatcher.h>
#include <glibmm/miscutils.h>
#include <giomm/file.h>
#endif // GUITARIX_AS_PLUGIN

#ifdef _WINDOWS
#include <io.h>
#define R_OK    4       /* Test for read permission.  */
#define W_OK    2       /* Test for write permission.  */
#define X_OK    1       /* execute permission - unsupported in windows*/
#define F_OK    0       /* Test for existence.  */
#define access _access

#include <chrono>
#include <thread>
#undef _stat
#endif // _WINDOWS

#endif  // SRC_HEADERS_ENGINE_H_
