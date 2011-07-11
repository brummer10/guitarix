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
#include <glibmm/i18n.h>  // NOLINT

#include <cstring>        // NOLINT
#include <string>         // NOLINT
#include <fstream>        // NOLINT
#include <iostream>       // NOLINT


namespace gx_engine {

/****************************************************************
 ** registering of audio variables
 */

inline void registerNonMidiParam(const char*a, float*c, bool d, float std = 0,
                                 float lower = 0, float upper = 1) {
    gx_gui::parameter_map.insert(new gx_gui::FloatParameter(a, "", gx_gui::Parameter::None,
                                 d, *c, std, lower, upper, 0, false));
}

inline void registerNonMidiParam(const char*a, bool*c, bool d, float std = false) {
    gx_gui::parameter_map.insert(new gx_gui::BoolParameter(a, "", gx_gui::Parameter::None,
                                 d, *c, std, 0, false));
}

// should be int
inline void registerEnumParam(const char*a, const char*b, const char** vl, float*c,
                              int std = 0, bool exp = false) {
    gx_gui::parameter_map.insert(new gx_gui::FloatEnumParameter(a, b, vl, true, *c, std,
                                 true, exp)); // false == no_midi_var
}

inline void registerEnumParam(const char*a, const char*b, const char** vl, int*c, int std = 0,
                              bool exp = false) {
    gx_gui::parameter_map.insert(new gx_gui::EnumParameter(a, b, vl, true, *c, std,
                                 true, exp)); // false == no_midi_var
}

inline void registerUEnumParam(const char*a, const char*b, const char** vl, unsigned int*c, unsigned int std = 0,
                              bool exp = false) {
    gx_gui::parameter_map.insert(new gx_gui::UEnumParameter(a, b, vl, true, *c, std,
                                 true, exp)); // false == no_midi_var
}

/****************************************************************
 ** definitions for code generated with faust / dsp2cc
 */

#include "./gx_faust_includes.cc"

/****************************************************************
 ** register audio variables to paramtable
 */

void AudioVariables::register_parameter() {
    static const char *on_off = N_("on/off");
    gx_gui::registerParam("amp.bass_boost.on_off", on_off, &fboost, 0);
    gx_gui::registerParam("compressor.on_off", on_off, &fcheckboxcom1, 0);
    gx_gui::registerParam("jconv.on_off", "Run", &gx_jconv::GxJConvSettings::checkbutton7);
    gx_gui::registerParam("crybaby.on_off", on_off, &fcheckbox5, 0);
    gx_gui::registerParam("cab.on_off", "Cabinet", &fcab, 0);
    gx_gui::registerParam("con.on_off", "Contrast-ImpResp", &fcon, 0);
    gx_gui::registerParam("overdrive.on_off", on_off, &foverdrive4, 0);
    gx_gui::registerParam("gx_distortion.on_off", on_off, &fcheckbox4, 0);
    gx_gui::registerParam("freeverb.on_off", on_off, &fcheckbox6, 0);
    gx_gui::registerParam("IR.on_off", on_off, &fcheckbox8, 0);
    gx_gui::registerParam("echo.on_off", on_off, (float*) &fcheckbox7, 0.);
    gx_gui::registerParam("delay.on_off", on_off, (float*) &fdelay, 0.);
    gx_gui::registerParam("chorus.on_off", on_off, (float*) &fchorus, 0.);
    gx_gui::registerParam("eqs.on_off", on_off, &feq, 0);
    gx_gui::registerParam("moog.on_off", on_off, &fmoog, 0);
    gx_gui::registerParam("biquad.on_off", "on_off", &fbiquad, 0);
    gx_gui::registerParam("flanger.on_off", on_off, &fflanger, 0);
    // gx_gui::registerParam("SampleLooper.on_off", "on_off", (float*) &fsloop, 0.);
    gx_gui::registerParam("phaser.on_off", on_off, (float*) &fphaser, 0.);
    gx_gui::registerParam("shaper.on_off", on_off, &fng, 0);
    gx_gui::registerParam("low_highpass.on_off", on_off, &flh, 0);
    gx_gui::registerParam("stereodelay.on_off", on_off, (float*) &fsd, 0);
    gx_gui::registerParam("stereoecho.on_off", on_off, (float*) &fse, 0);
    gx_gui::registerParam("midi_out.on_off", on_off, &fmi, 0);
    gx_gui::registerParam("oscilloscope.on_off", on_off, &fwv, 0);
    gx_gui::registerParam("ampmodul.on_off", on_off, &famp, 0);
    gx_gui::registerParam("noise_gate.on_off", "on/off", &fnoise_g, 0);
    gx_gui::registerParam("amp.on_off", on_off, &fampout, 0);
    gx_gui::registerParam("amp.clip.on_off", on_off, &ftube, 0);
    gx_gui::registerParam("tonemodul.on_off", on_off, &ftone, 0);
    gx_gui::registerParam("tremolo.on_off", on_off, &ftremolo, 0);
    gx_gui::registerParam("phaser_mono.on_off", on_off, &fpm, 0);
    gx_gui::registerParam("chorus_mono.on_off", on_off, (float*) &fchorus_mono, 0.);
    gx_gui::registerParam("flanger_mono.on_off", on_off, &fflanger_mono, 0.);
    gx_gui::registerParam("feedback.on_off", on_off, &ffeedback, 0.);
    gx_gui::registerParam("amp.tonestack.on_off", on_off, &ftonestack, 0.);

    gx_gui::registerParam("noise_gate.threshold", "Threshold", &fnglevel,
                          0.017f, 0.01f, 0.31f, 0.001f);

    static const char *tonestack_model[] = {N_("default"), N_("Bassman"), N_("Twin Reverb"),
        N_("Princeton"), N_("JCM-800"), N_("JCM-2000"), N_("M-Lead"), N_("M2199"), N_("AC-30"),
        N_("Mesa Boogie"), N_("SOL 100"), N_("JTM-45"), N_("AC-15"), N_("Peavey"), N_("Ibanez"),
        N_("Roland"), N_("Ampeg"), N_("Rev.Rocket"), N_("MIG 100 H"), N_("Triple Giant"),
        N_("Trio Preamp"), N_("Hughes&Kettner"), N_("Junior"), N_("Fender"),
        N_("Deville"), N_("Gibsen"), 0};
    registerEnumParam("amp.tonestack.select", "select", tonestack_model, &tonestack, 0);
    static const char *cabinet_model[] = {N_("4x12"), N_("2x12"), N_("1x12"), N_("4x10"),
    N_("2x10"), N_("HighGain"), N_("Twin"), N_("Bassman"), N_("Marshall"), N_("AC-30"),
    N_("Princeton"), N_("A2"), 0};
    registerEnumParam("cab.select", "select", cabinet_model, &cabinet, 0);

    static const char *post_pre[] = {N_("post"), N_("pre"), 0};
    registerUEnumParam("compressor.pp", "select", post_pre, &effect_pre_post[0], 0);
    registerUEnumParam("crybaby.pp", "select", post_pre, &effect_pre_post[1], 0);
    registerUEnumParam("overdrive.pp", "select", post_pre, &effect_pre_post[2], 0);
    registerUEnumParam("gx_distortion.pp", "select", post_pre, &effect_pre_post[3], 0);
    registerUEnumParam("freeverb.pp", "select", post_pre, &effect_pre_post[4], 0);
    registerUEnumParam("IR.pp", "select", post_pre, &effect_pre_post[5], 0);
    registerUEnumParam("echo.pp", "select", post_pre, &effect_pre_post[6], 0);
    registerUEnumParam("delay.pp", "select", post_pre, &effect_pre_post[7], 0);
    registerUEnumParam("eqs.pp", "select", post_pre, &effect_pre_post[8], 0);
    registerUEnumParam("low_highpass.pp", "select", post_pre, &effect_pre_post[9], 0);
    registerUEnumParam("oscilloscope.pp", "select", post_pre, &effect_pre_post[10], 0);
    registerUEnumParam("biquad.pp", "select", post_pre, &effect_pre_post[11], 0);
    registerUEnumParam("tremolo.pp", "select", post_pre, &effect_pre_post[12], 0);
    registerUEnumParam("phaser_mono.pp", "select", post_pre, &effect_pre_post[13], 0);
    registerUEnumParam("chorus_mono.pp", "select", post_pre, &effect_pre_post[14], 0);
    registerUEnumParam("flanger_mono.pp", "select", post_pre, &effect_pre_post[15], 0);
    registerUEnumParam("feedback.pp", "select", post_pre, &effect_pre_post[16], 0);
    registerUEnumParam("amp.tonestack.pp", "select", post_pre, &effect_pre_post[17], 0);
    registerUEnumParam("cab.pp", "select", post_pre, &effect_pre_post[18], 0);

    static const char *crybaby_autowah[] = {N_("manual"), N_("auto"), 0};
    registerEnumParam("crybaby.autowah", "select", crybaby_autowah, &fautowah, 0);

    // static const char *eqt_onetwo[] = {"fixed","scale",0};
    // registerEnumParam("eqt.onetwo", "select", eqt_onetwo, &witcheq, 0);

    registerNonMidiParam("compressor.position", &posit[5], true, 6, 1, 22);
    registerNonMidiParam("crybaby.position", &posit[0], true, 3, 1, 22);
    registerNonMidiParam("overdrive.position", &posit[1], true, 7, 1, 22);
    registerNonMidiParam("gx_distortion.position", &posit[2], true, 4, 1, 22);
    registerNonMidiParam("freeverb.position", &posit[3], true, 10, 1, 22);
    registerNonMidiParam("IR.position", &posit[4], true, 5, 1, 22);
    registerNonMidiParam("echo.position", &posit[6], true, 8, 1, 22);
    registerNonMidiParam("delay.position", &posit[7], true, 9, 1, 22);
    registerNonMidiParam("eqs.position", &posit[10], true, 2, 1, 22);
    registerNonMidiParam("chorus.position", &posit[8], true, 1, 1, 10);
    registerNonMidiParam("flanger.position", &posit[9], true, 2, 1, 10);
    registerNonMidiParam("moog.position", &posit[11], true, 6, 1, 10);
    registerNonMidiParam("phaser.position", &posit[12], true, 3, 1, 10);
    registerNonMidiParam("low_highpass.position", &posit[14], true, 1, 1, 22);
    registerNonMidiParam("stereodelay.position", &posit[15], true, 4, 1, 10);
    registerNonMidiParam("stereoecho.position", &posit[16], true, 5, 1, 10);
    registerNonMidiParam("oscilloscope.position", &posit[17], true, 11, 1, 22);
    registerNonMidiParam("biquad.position", &posit[18], true, 12, 1, 22);
    // registerNonMidiParam("midi_out.position", &posit[28], true, 20, 1, 22);
    registerNonMidiParam("ampmodul.position", &posit[19], true, 7, 1, 10);
    registerNonMidiParam("tonemodul.position", &posit[20], true, 8, 1, 10);
    registerNonMidiParam("tremolo.position", &posit[21], true, 13, 1, 22);
    registerNonMidiParam("phaser_mono.position", &posit[22], true, 14, 1, 22);
    registerNonMidiParam("chorus_mono.position", &posit[23], true, 15, 1, 22);
    registerNonMidiParam("flanger_mono.position", &posit[24], true, 16, 1, 22);
    registerNonMidiParam("feedback.position", &posit[25], true, 17, 1, 22);
    registerNonMidiParam("amp.tonestack.position", &posit[26], true, 18, 1, 22);
    registerNonMidiParam("cab.position", &posit[27], true, 19, 1, 22);


    registerNonMidiParam("system.waveview", &viv, false);
    registerNonMidiParam("midi_out.midistat", &midistat, false);
    registerNonMidiParam("midi_out.midistat1", &midistat1, false);
    registerNonMidiParam("midi_out.midistat2", &midistat2, false);
    registerNonMidiParam("midi_out.midistat3", &midistat3, false);

    // user interface options
    registerNonMidiParam("ui.latency_nowarn", &fwarn, false, 0);
    registerNonMidiParam("ui.skin", &fskin, false, 0, 0, 100);
}

AudioVariables audio;

inline void check_effect_buffer() {
    if (!gx_effects::echo::is_inited()) {
        pre_rack_order_ptr[audio.effect_buffer[0]] = just_return;
        post_rack_order_ptr[audio.effect_buffer[3]] = just_return;
    }
    if (!gx_effects::delay::is_inited()) {
        pre_rack_order_ptr[audio.effect_buffer[1]] = just_return;
        post_rack_order_ptr[audio.effect_buffer[4]] = just_return;
    }
    if (!gx_effects::chorus_mono::is_inited()) {
        pre_rack_order_ptr[audio.effect_buffer[2]] = just_return;
        post_rack_order_ptr[audio.effect_buffer[5]] = just_return;
    }
}

inline void check_stereo_effect_buffer() {
    if (!gx_effects::chorus::is_inited()) {
        stereo_rack_order_ptr[audio.effect_buffer[6]] = just2_return;
    }
    if (!gx_effects::stereodelay::is_inited()) {
        stereo_rack_order_ptr[audio.effect_buffer[7]] = just2_return;
    }
    if (!gx_effects::stereoecho::is_inited()) {
        stereo_rack_order_ptr[audio.effect_buffer[8]] = just2_return;
    }
}

/****************************************************************
 **  this is the process callback called from jack
 **
 ***************************************************************/
void compute_insert(int count, float* input1, float* output0, float* output1) {
// retrieve engine state
    const GxEngineState estate = checky;

    // ------------ determine processing type
    uint16_t process_type = ZEROIZE_BUFFERS;

    if (gx_jack::NO_CONNECTION == 0) { // ports connected
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
        gx_effects::balance1::compute(count, input1, output0, output1);
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

void compute(int count, float* input, float* output0) {
    // retrieve engine state
    const GxEngineState estate = checky;

    // ------------ determine processing type
    uint16_t process_type = ZEROIZE_BUFFERS;

    if (gx_jack::NO_CONNECTION == 0) { // ports connected
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

/****************************************************************
 ** this is the gx_head audio engine
 */


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

    // check if effect buffer is inited
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
    gx_effects::gx_outputlevel::compute(count, output0, output1, output0, output1);
    // copy output buffer to the level meter
    (void)memcpy(get_frame, output0, sizeof(float)*count);
    (void)memcpy(get_frame1, output1, sizeof(float)*count);
}

} // namespace gx_engine

