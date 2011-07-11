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

#include <cstring>       // NOLINT
#include <string>        // NOLINT


namespace gx_engine {

void gx_engine_init(const string *optvar ) {
    // ----- lock the buffer for the oscilloscope
    const int frag = (const int)gx_jack::gxjack.jack_bs;

    get_frame  = new float[frag];
    get_frame1  = new float[frag];
    checkfreq  = new float[frag];
    oversample = new float[frag*MAX_UPSAMPLE];
    result = new float[frag+46];
    audio.gxtube = 1;
    audio.cur_tonestack = 0;
    for (int i = 0; i < 9; i++) audio.effect_buffer[i] = 0;
    audio.rack_change = true;

    (void)memset(get_frame,  0, frag*sizeof(float));
    (void)memset(get_frame1,  0, frag*sizeof(float));
    (void)memset(checkfreq,  0, frag*sizeof(float));
    (void)memset(oversample, 0, frag*MAX_UPSAMPLE*sizeof(float));
    (void)memset(result, 0, (frag+46)*sizeof(float));

    midi.init(gx_jack::gxjack.jack_sr);
    faust_init(gx_jack::gxjack.jack_sr);
    // resampTube.setup(gx_jack::jack_sr, 2);
    // resampDist.setup(gx_jack::jack_sr, 2);
    if (!optvar[LOAD_FILE].empty()) {
        gx_preset::gx_recall_settings_file(&optvar[LOAD_FILE]);
    } else {
        gx_preset::gx_recall_settings_file();
    }
    for (int i = 0; i < GX_NUM_OF_FACTORY_PRESET; i++)
        gx_preset::gx_load_factory_file(i);
    initialized = true;
}

void gx_engine_reset() {

    if (checkfreq)  delete[] checkfreq;
    if (get_frame)  delete[] get_frame;
    if (get_frame1)  delete[] get_frame1;
    if (oversample) delete[] oversample;
    if (result) delete[] result;
    initialized = false;
}

} /* end of gx_engine namespace */
