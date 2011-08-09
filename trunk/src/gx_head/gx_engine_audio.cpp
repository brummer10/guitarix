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
 *    This is the Guitarix Audio Engine
 *
 *
 * --------------------------------------------------------------------------
 */

#include "guitarix.h"     // NOLINT

#include <errno.h>        // NOLINT

#include <cstring>        // NOLINT
#include <string>         // NOLINT
#include <list>           // NOLINT
#include <iostream>       // NOLINT

namespace gx_engine {

AudioVariables audio;

#include "gx_faust_includes.cpp"
/****************************************************************
 **  this is the process callback called from jack
 **
 ***************************************************************/

// the gx_head_amp client callback
void compute(int count, float* input, float* output0) {
    // retrieve engine state
    const GxEngineState estate = audio.checky;

    // ------------ determine processing type
    uint16_t process_type = ZEROIZE_BUFFERS;

    if (gx_jack::gxjack.NO_CONNECTION == 0) { // ports connected
        switch (estate) {
        case kEngineOn:
            process_type = PROCESS_BUFFERS;
            break;

        case kEngineBypass:
            process_type = JUSTCOPY_BUFFERS;
            break;

        default: // engine off or whatever: zeroize
            break;
        }
    }

    // check midi state
    if (audio.fmi && !isMidiOn()) turnOnMidi();
    else if (!audio.fmi && isMidiOn()) turnOffMidi();

    // clear oscilloscope buffer if osc is off
    if (audio.fwv != audio.fwv_on) {
        (void)memset(audio.result, 0, count*sizeof(float));
        audio.fwv_on = audio.fwv;
    }

    // check for changes in the audio engine
    if (audio.rack_change) {
        audio.rack_change = gx_reorder_rack(NULL);
    }

    // ------------ main processing routine
    switch (process_type) {

    //---------- run process
    case PROCESS_BUFFERS:
        process_buffers(count, input, output0);
        break;

    // --------- just copy input to outputs
    case JUSTCOPY_BUFFERS:
        if (conv.is_runnable()) {
            conv.checkstate();
        }
       // balance1::compute(count, input, output0);
       (void)memcpy(output0, input, sizeof(float)*count);
        break;

    // ------- zeroize buffers
    case ZEROIZE_BUFFERS:
    default:

        if (conv.is_runnable()) {
            conv.checkstate();
        }
        if (audio.fwv) (void)memset(audio.result, 0, count*sizeof(float));

        // no need of loop.
        (void)memset(output0, 0, count*sizeof(float));
          break;
    }
}

// the gx_head_fx client callback
void compute_insert(int count, float* input1, float* output0, float* output1) {
    // retrieve engine state
    const GxEngineState estate = audio.checky;

    // ------------ determine processing type
    uint16_t process_type = ZEROIZE_BUFFERS;

    if (gx_jack::gxjack.NO_CONNECTION == 0) { // ports connected
        switch (estate) {
        case kEngineOn:
            process_type = PROCESS_BUFFERS;
            break;

        case kEngineBypass:
            process_type = JUSTCOPY_BUFFERS;
            break;

        default: // engine off or whatever: zeroize
            break;
        }
    }

    // ------------ main processing routine
    switch (process_type) {

    // --------- run process
    case PROCESS_BUFFERS:
        process_insert_buffers(count, input1, output0, output1);
        break;

    // --------- just copy input to outputs
    case JUSTCOPY_BUFFERS:
        if (conv.is_runnable()) {
            conv.checkstate();
        }

        // mono to stereo splitter
        gx_effects::balance1::compute(count, input1, output0, output1);

        // copy buffer for the levelmeters
        (void)memcpy(audio.get_frame, output0, sizeof(float)*count);
        (void)memcpy(audio.get_frame1, output1, sizeof(float)*count);
        break;

    // ------- zeroize buffers
    case ZEROIZE_BUFFERS:
    default:

        if (conv.is_runnable()) {
            conv.checkstate();
        }

        // no need of loop.
        (void)memset(output0, 0, count*sizeof(float));
        (void)memset(output1, 0, count*sizeof(float));
        break;
    }
}

/****************************************************************
 ** this is the gx_head audio engine
 */

// gx_head_amp engine
void process_buffers(int count, float* input, float* output0) {

    // move working buffer to the output buffer
    memcpy(output0, input, count*sizeof(float));

    // run mono rack
    for (int m = 1; m < audio.mono_active_counter+1; m++) {
        _modulpointer->mono_rack_order_ptr[m](count, output0, output0);
    }
}

// gx_head_fx engine
void process_insert_buffers(int count, float* input1, float* output0, float* output1) {

    // move working buffer to the output buffer
    memcpy(output0, input1, count*sizeof(float));

    // run stereo rack
    for (int m = 1; m < audio.stereo_active_counter+1; m++) {
        _modulpointer->stereo_rack_order_ptr[m](count, output0, output1, output0, output1);
    }

    // copy output buffer to the level meter
    (void)memcpy(audio.get_frame, output0, sizeof(float)*count);
    (void)memcpy(audio.get_frame1, output1, sizeof(float)*count);
}
} // namespace gx_engine

