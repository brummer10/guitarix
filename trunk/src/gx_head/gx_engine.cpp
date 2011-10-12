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
 *    This is the guitarix engine definitions
 *
 *
 * --------------------------------------------------------------------------
 */

#include "guitarix.h"    // NOLINT

#include <glibmm/i18n.h>  // NOLINT

#include <cstring>       // NOLINT
#include <string>        // NOLINT


namespace gx_engine {

void gx_engine_init(const string *optvar ) {
    // ----- lock the buffer for the oscilloscope
    const int frag = (const int)get_jack().jack_bs;

    audio.oversample = new float[frag*MAX_UPSAMPLE];
    
    (void)memset(audio.oversample, 0, frag*MAX_UPSAMPLE*sizeof(float));

    midi.init(get_jack().jack_sr);
    // resampTube.setup(gx_jack::jack_sr, 2);
    // resampDist.setup(gx_jack::jack_sr, 2);
    if (!optvar[LOAD_FILE].empty()) {
        gx_preset::gxpreset.gx_recall_settings_file(&optvar[LOAD_FILE]);
    } else {
        gx_preset::gxpreset.gx_recall_settings_file();
    }
    for (int i = 0; i < GX_NUM_OF_FACTORY_PRESET; i++)
        gx_preset::gxpreset.gx_load_factory_file(i);
    audio.initialized = true;
}

void gx_engine_reset() {

    if (audio.oversample) delete[] audio.oversample;
    audio.initialized = false;
}

/****************************************************************
 ** registering of audio variables
 */

inline void registerNonMidiParam(const char*a, float*c, bool d, float std = 0,
                                 float lower = 0, float upper = 1) {
    gx_gui::parameter_map.insert(new gx_gui::FloatParameter(a, "", gx_gui::Parameter::None,
                                 d, *c, std, lower, upper, false, false));
}

inline void registerNonMidiParam(const char*a, int*c, bool d, int std, int lower, int upper) {
    gx_gui::parameter_map.insert(new gx_gui::IntParameter(a, "", gx_gui::Parameter::None,
							  d, *c, std, lower, upper, false, false));
}


inline void registerNonMidiParam(const char*a, bool*c, bool d, float std = false) {
    gx_gui::parameter_map.insert(new gx_gui::BoolParameter(a, "", gx_gui::Parameter::None,
                                 d, *c, std, false, false));
}

// should be int
inline void registerEnumParam(const char*a, const char*b, const value_pair* vl, float*c,
                              int std = 0, bool exp = false) {
    gx_gui::parameter_map.insert(new gx_gui::FloatEnumParameter(a, b, vl, true, *c, std,
                                 true, exp)); // false == no_midi_var
}

/****************************************************************
 ** register audio variables to paramtable
 */

void AudioVariables::register_parameter() {

    // user interface options
    registerNonMidiParam("ui.latency_nowarn",        &fwarn, false, 0);
    registerNonMidiParam("ui.skin",                  &fskin, false, 0, 0, 100);

    oversample  = NULL;
    
    /* engine init state  */
    audio.initialized = false;

    /* buffer ready state */
    audio.buffers_ready = false;
}
} /* end of gx_engine namespace */
