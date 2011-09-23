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
MonoModuleChain mono_chain;
StereoModuleChain stereo_chain;

#include "gx_faust_includes.cpp"

inline bool feed_tuner(int count, float* input) {
    // check if tuner is visible or midi is on
    int tuner_on = gx_gui::guivar.shownote + static_cast<int>(isMidiOn()) + 1;
    if (tuner_on > 0) {
        if (gx_gui::guivar.shownote == 0) {
            gx_gui::guivar.shownote = -1;
        } else {
            // run tuner
            pitch_tracker.add(count, input);
            return true;
        }
    }
    return false;
}

inline void zero_maxlevel() {
    (void)memset(audio.maxlevel, 0, sizeof(audio.maxlevel));
}

inline void set_maxlevel(int count, float *input1, float *input2) {
    const float *data[2] = {input1, input2};
    for (int c = 0; c < 2; c++) {
        float level = 0;
        for (int i = 0; i < count; i++) {
            float t = abs(data[c][i]);
            if (level < t) {
                level = t;
            }
        }
        audio.maxlevel[c] = max(audio.maxlevel[c], level);
    }
}

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
        feed_tuner(count, input);
       // balance1::compute(count, input, output0);
       (void)memcpy(output0, input, sizeof(float)*count);
        break;

    // ------- zeroize buffers
    case ZEROIZE_BUFFERS:
    default:

        if (conv.is_runnable()) {
            conv.checkstate();
        }
        feed_tuner(count, input);
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
	set_maxlevel(count, output0, output1);
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
        zero_maxlevel();
        break;
    }
}

/****************************************************************
 ** this is the gx_head audio engine
 */

void MonoModuleChain::process(int count, float *input, float *output) {
    if (ramp_mode == ramp_down_dead) {
	memset(output, 0, count*sizeof(float));
	return;
    }
    // move working buffer to the output buffer
    memcpy(output, input, count*sizeof(float));
    for (monochainorder *p = get_rt_chain(); *p; p++) {
	(*p)(count, output, output);
    }
    if (ramp_mode == ramp_off) {
	return;
    }
    int i = 0;
    if (ramp_mode == ramp_up_dead) {
	for ( ; i < count; i++) {
	    if (++ramp_value > steps_up_dead) {
		ramp_mode = ramp_up;
		ramp_value = 0;
		break;
	    }
	    output[i] = 0.0;
	}
    }
    if (ramp_mode == ramp_up) {
	for ( ; i < count; i++) {
	    if (++ramp_value >= steps_up) {
		ramp_mode = ramp_off;
		break;
	    }
	    output[i] = (output[i] * ramp_value) / steps_up;
	}
    }
    else if (ramp_mode == ramp_down) {
	for (i = 0; i < count; i++) {
	    if (--ramp_value == 0) {
		ramp_mode = ramp_down_dead;
		break;
	    }
	    output[i] = (output[i] * ramp_value) / steps_down;
	}
	for ( ; i < count; i++) {
	    output[i] = 0.0;
	}
    }
}

void StereoModuleChain::process(int count, float *input, float *output1, float *output2) {
    // run stereo rack
    if (ramp_mode == ramp_down_dead) {
	memset(output1, 0, count*sizeof(float));
	memset(output2, 0, count*sizeof(float));
	return;
    }
    // move working buffer to the output buffer
    memcpy(output1, input, count*sizeof(float));
    memcpy(output2, input, count*sizeof(float));
    for (stereochainorder *p = get_rt_chain(); *p; p++) {
	(*p)(count, output1, output2, output1, output2);
    }
    if (ramp_mode == ramp_off) {
	return;
    }
    int i = 0;
    if (ramp_mode == ramp_up_dead) {
	for ( ; i < count; i++) {
	    if (++ramp_value > steps_up_dead) {
		ramp_mode = ramp_up;
		ramp_value = 0;
		break;
	    }
	    output1[i] = 0.0;
	    output2[i] = 0.0;
	}
    }
    if (ramp_mode == ramp_up) {
	for ( ; i < count; i++) {
	    if (++ramp_value >= steps_up) {
		ramp_mode = ramp_off;
		break;
	    }
	    output1[i] = (output1[i] * ramp_value) / steps_up;
	    output2[i] = (output2[i] * ramp_value) / steps_up;
	}
    }
    else if (ramp_mode == ramp_down) {
	for (i = 0; i < count; i++) {
	    if (--ramp_value == 0) {
		ramp_mode = ramp_down_dead;
		break;
	    }
	    output1[i] = (output1[i] * ramp_value) / steps_down;
	    output2[i] = (output2[i] * ramp_value) / steps_down;
	}
	for ( ; i < count; i++) {
	    output1[i] = 0.0;
	    output2[i] = 0.0;
	}
    }
}

// gx_head_amp engine
void process_buffers(int count, float* input, float* output0) {
    if (feed_tuner(count, input)) {
        // copy buffer to midi thread
        (void)memcpy(audio.checkfreq, input, sizeof(float)*count);
    }
    mono_chain.process(count, input, output0);

}

// gx_head_fx engine
void process_insert_buffers(int count, float* input1, float* output0, float* output1) {
    stereo_chain.process(count, input1, output0, output1);
    set_maxlevel(count, output0, output1);
}

} // end namespace gx_engine
