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

#include <iostream>       // NOLINT

namespace gx_engine {

AudioVariables audio;

/****************************************************************
 **  this is the process callback called from jack
 **
 ***************************************************************/

// the gx_head_amp client callback
void compute(int count, float* input, float* output0) {
    // retrieve engine state
    const GxEngineState estate = checky;

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
    if (audio.fmi && !isMidiOn()) turnOnMidi();
    else if (!audio.fmi && isMidiOn()) turnOffMidi();

    if (audio.fwv != audio.fwv_on) {
        (void)memset(result, 0, count*sizeof(float));
        audio.fwv_on = audio.fwv;
    }

    // ------------ main processing routine
    switch (process_type) {

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
        if (audio.fwv) (void)memset(result, 0, count*sizeof(float));

        // no need of loop.
        (void)memset(output0, 0, count*sizeof(float));
          break;
    }
}

// the gx_head_fx client callback
void compute_insert(int count, float* input1, float* output0, float* output1) {
// retrieve engine state
    const GxEngineState estate = checky;

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
        (void)memcpy(get_frame, output0, sizeof(float)*count);
        (void)memcpy(get_frame1, output1, sizeof(float)*count);
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

    // check if tuner is visible or midi is on
    int tuner_on = gx_gui::shownote + static_cast<int>(isMidiOn()) + 1;
    if (tuner_on > 0) {
        if (gx_gui::shownote == 0) {
            gx_gui::shownote = -1;
        } else {
            // run tuner
            pitch_tracker.add(count, input);
            // copy buffer to midi thread
            (void)memcpy(checkfreq, input, sizeof(float)*count);
        }
    }

    // move working buffer to the output buffer
    memcpy(output0, input, count*sizeof(float));

    // check if mono effect buffer is inited
    if (audio.rack_change) {
        check_effect_buffer();
    }

    // run pre rack
    for (int m = 1; m < audio.pre_active_counter+1; m++) {
        pre_rack_order_ptr[m](count, output0, output0);
    }

    // run selected tube/amp model
    amp_ptr(count, output0, output0);

    // run post rack
    for (int m = 1; m < audio.post_active_counter+1; m++) {
        post_rack_order_ptr[m](count, output0, output0);
    }
}

// gx_head_fx engine
void process_insert_buffers(int count, float* input1, float* output0, float* output1) {

    // move working buffer to the output buffer
    memcpy(output0, input1, count*sizeof(float));

    // check if effect buffer is inited
    if (audio.rack_change) {
        check_stereo_effect_buffer();
    }

    // run stereo rack
    for (int m = 1; m < audio.stereo_active_counter+1; m++) {
        stereo_rack_order_ptr[m](count, output0, output1, output0, output1);
    }

    // run convolver
    if (conv.is_runnable()) {
        // reuse oversampling buffer
        float *conv_out0 = oversample;
        float *conv_out1 = oversample+count;
        if (!conv.compute(count, output0, output1, conv_out0, conv_out1)) {
            gx_jconv::GxJConvSettings::checkbutton7 = 0;
            std::cout << "overload" << endl;
            // FIXME error message??
        } else {
            gx_effects::jconv_post::compute(count, output0, output1, conv_out0, conv_out1,
                        output0, output1);
        }
    }

    // run outputlevel controler
    gx_effects::gx_outputlevel::compute(count, output0, output1, output0, output1);

    // copy output buffer to the level meter
    (void)memcpy(get_frame, output0, sizeof(float)*count);
    (void)memcpy(get_frame1, output1, sizeof(float)*count);
}
} // namespace gx_engine

