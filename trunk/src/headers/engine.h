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

/* system header files */
#include <semaphore.h>
#include <cmath>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <boost/format.hpp>
#include <boost/thread/mutex.hpp>
#include <glibmm/i18n.h>     // NOLINT
#include <glibmm/optioncontext.h>   // NOLINT
#include <glibmm/dispatcher.h>
#include <glibmm/miscutils.h>
#include <giomm/file.h>

/* waf generated defines */
#include "../config.h"

// define USE_MIDI_OUT to create a midi output port and
// make the MidiAudioBuffer plugin activatable
// for the UI:
// - menudef.xml: make action MidiOut visible (its commented out)
// - ports.glade: set scrolledwindow5 and label12 to visible
//
//#define USE_MIDI_OUT

#ifdef LADSPA_SO
#define gettext(x) dgettext(GETTEXT_PACKAGE, x)
#endif

using namespace std;

#include "gx_compiler.h"

/* guitarix declarations */
#include "gx_plugin.h"
#include "gx_system.h"
#include "gx_parameter.h"

#include "gx_resampler.h"
#include "gx_convolver.h"
#include "gx_pitch_tracker.h"
#include "gx_ui.h"
#include "gx_pluginloader.h"
#include "gx_modulesequencer.h"
#include "gx_json.h"

#include "gx_internal_plugins.h"
#include "gx_preset.h"
#include "gx_engine.h"

#include "gx_jack.h"
#include "tunerswitcher.h"

#endif  // SRC_HEADERS_ENGINE_H_
