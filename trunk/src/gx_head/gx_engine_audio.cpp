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

AudioVariables audio;

/****************************************************************
 **
 */

#include "./gx_faust_includes.cc"


/****************************************************************
 **  engine helpers and working threads
 */

// pointer to the default tonestack
void (*tonestack_ptr)(int count, float *output, float *output1) =
                   &gx_tonestacks::tonestack_default::compute;

// pointer to the default tube/amp
void (*amp_ptr)(int count, float *output, float *output1) =
                   &gx_amps::gxamp::compute;


// working thread to set the pointer to the selected tonestack and tube/amp
gboolean gx_check_engine_state(gpointer) {

    // only run when tonestack selection have changed
    if (audio.cur_tonestack != audio.tonestack) {
        jack_sync();
        switch (audio.tonestack) {
        case 0: // "default"
            tonestack_ptr = &gx_tonestacks::tonestack_default::compute;
            break;
        case 1: // "Bassman"
            tonestack_ptr = &gx_tonestacks::tonestack_bassman::compute;
            break;
        case 2: // "Twin Reverb"
            tonestack_ptr = &gx_tonestacks::tonestack_twin::compute;
            break;
        case 3: // "Princeton"
            tonestack_ptr = &gx_tonestacks::tonestack_princeton::compute;
            break;
        case 4: // "JCM-800"
            tonestack_ptr = &gx_tonestacks::tonestack_jcm800::compute;
            break;
        case 5: // "JCM-2000"
            tonestack_ptr = &gx_tonestacks::tonestack_jcm2000::compute;
            break;
        case 6: // "M-Lead"
            tonestack_ptr = &gx_tonestacks::tonestack_mlead::compute;
            break;
        case 7: // "M2199"
            tonestack_ptr = &gx_tonestacks::tonestack_m2199::compute;
            break;
        case 8: // "AC-30"
            tonestack_ptr = &gx_tonestacks::tonestack_ac30::compute;
            break;
        case 9: // "Mesa"
            tonestack_ptr = &gx_tonestacks::tonestack_mesa::compute;
            break;
        case 10: // "Soldano"
            tonestack_ptr = &gx_tonestacks::tonestack_soldano::compute;
            break;
        case 11: // "jtm45"
            tonestack_ptr = &gx_tonestacks::tonestack_jtm45::compute;
            break;
        case 12: // "ac15"
            tonestack_ptr = &gx_tonestacks::tonestack_ac15::compute;
            break;
        case 13: // "peavey"
            tonestack_ptr = &gx_tonestacks::tonestack_peavey::compute;
            break;
        case 14: // "ibanez"
            tonestack_ptr = gx_tonestacks::tonestack_ibanez::compute;
            break;
        case 15: // "roland"
            tonestack_ptr = &gx_tonestacks::tonestack_roland::compute;
            break;
        case 16: // "ampeg"
            tonestack_ptr = &gx_tonestacks::tonestack_ampeg::compute;
            break;
        case 17: // "ampeg rev"
            tonestack_ptr = &gx_tonestacks::tonestack_ampeg_rev::compute;
            break;
        case 18: // "sovtek"
            tonestack_ptr = &gx_tonestacks::tonestack_sovtek::compute;
            break;
        case 19: // "bogner"
            tonestack_ptr = &gx_tonestacks::tonestack_bogner::compute;
            break;
        case 20: // "groove"
            tonestack_ptr = &gx_tonestacks::tonestack_groove::compute;
            break;
        case 21: // "crunch"
            tonestack_ptr = &gx_tonestacks::tonestack_crunch::compute;
            break;
        case 22: // "fender_blues"
            tonestack_ptr = &gx_tonestacks::tonestack_fender_blues::compute;
            break;
        case 23: // "fender_default"
            tonestack_ptr = &gx_tonestacks::tonestack_fender_default::compute;
            break;
        case 24: // "fender_deville"
            tonestack_ptr = &gx_tonestacks::tonestack_fender_deville::compute;
            break;
        case 25: // "gibsen"
            tonestack_ptr = &gx_tonestacks::tonestack_gibsen::compute;
            break;
        case 26: // "Off"
            break;
        }
        audio.cur_tonestack = audio.tonestack;
    }

    // only run when tube/amp selection have changed
    if (audio.cur_gxtube != audio.gxtube) {
        jack_sync();
         switch (audio.gxtube) {
        case 0: // "never"
            amp_ptr = &gx_amps::gxamp::compute;
            break;
        case 1: // "default"
            amp_ptr = &gx_amps::gxamp::compute;
            break;
        case 2:
            amp_ptr = &gx_amps::gxamp3::compute;
            break;
        case 3:
            amp_ptr = &gx_amps::gxamp2::compute;
            break;
        case 4:
            amp_ptr = &gx_amps::gxamp4::compute;
            break;
        case 5:
            amp_ptr = &gx_amps::gxamp5::compute;
            break;
        case 6:
            amp_ptr = &gx_amps::gxamp10::compute;
            break;
        case 7:
            amp_ptr = &gx_amps::gxamp12::compute;
            break;
        case 8:
            amp_ptr = &gx_amps::gxamp6::compute;
            break;
        case 9:
            amp_ptr = &gx_amps::gxamp7::compute;
            break;
        case 10:
            amp_ptr = &gx_amps::gxamp8::compute;
            break;
        case 11:
            amp_ptr = &gx_amps::gxamp9::compute;
            break;
        case 12:
            amp_ptr = &gx_amps::gxamp11::compute;
            break;
        case 13:
            amp_ptr = &gx_amps::gxamp13::compute;
            break;
        default:
            amp_ptr = &gx_amps::gxamp::compute;
            break;
        }
        audio.cur_gxtube = audio.gxtube;
    }
    return TRUE;
}

// reduce gain to compensate the increased gain by the cabinet
inline void compensate_cab(int count, float *input0, float *output0) {
    double fSlow0 = (0.0010000000000000009 * pow(10, (0.05 * (-audio.cab_level*2.0))));
    static double fRec0[2] = {0, 0};
    for (int i = 0; i < count; i++) {
        fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
        output0[i] = (FAUSTFLOAT)(static_cast<double>(input0[i]) * fRec0[0]);
        // post processing
        fRec0[1] = fRec0[0];
    }
}

// calculate noisgate level
inline float noise_gate(int sf, float* input, float ngate) {
    float sumnoise = 0;
    for (int i = 0; i < sf; i++) {
        sumnoise += sqrf(fabs(input[i]));
    }
    float noisepulse = sqrtf(sumnoise/sf);
    if (noisepulse > audio.fnglevel * 0.01) {
        return 1; // -75db 0.001 = 65db
    } else if (ngate > 0.01) {
        return ngate * 0.996;
    } else {
        return ngate;
    }
}

// wraper for the rack order function pointers
inline void set_osc_buffer(int count, float *input0, float *output0) {
    (void)memcpy(result, output0, sizeof(float)*count);
}

// wraper for the rack order function pointers
inline void run_cab_conf(int count, float *input0, float *output0) {
    compensate_cab(count, output0, output0);
    if (!cab_conv.compute(count, output0))
        std::cout << "overload" << endl;
}

// wraper for the presence function
inline void run_contrast(int count, float *input0, float *output0) {
    if (!contrast_conv.compute(count, output0))
    std::cout << "overload contrast" << endl;
    // FIXME error message??
}

// wraper for the noisgate function
inline void set_noisegate_level(int count, float *input0, float *output0) {
    gx_effects::noisegate::ngate = noise_gate(count, output0, gx_effects::noisegate::ngate);
}

// wraper for the mono2stereo function
inline void run_gxfeed(int count, float *input0, float *input1, float *output0, float *output1) {
    gx_effects::gxfeed::compute(count, output0, output0, output1);
}

// empty mono pointer
void just_return(int count, float *input0, float *output0) {
    return;
}

// empty stereo pointer
void just2_return(int count, float *input0, float *input1, float *output0, float *output1) {
    return;
}

// mono rack order pointer
chainorder pre_rack_order_ptr[30];
chainorder post_rack_order_ptr[30];

// stereo rack order pointer
stereochainorder stereo_rack_order_ptr[12];

// working thread to set the order in the all racks
gboolean gx_reorder_rack(gpointer args) {

    if (gx_engine::audio.rack_change) {
        // sync to jack_buffer_callback
        jack_sync();

        // set all pointers to just return
        for (int m = 0; m < audio.mono_plug_counter + 4; m++) {
            pre_rack_order_ptr[m] = just_return;
        }

        for (int m = 0; m < audio.mono_plug_counter + 6; m++) {
            post_rack_order_ptr[m] = just_return;
        }

        for (int m = 0; m < audio.stereo_plug_counter + 4; m++) {
            stereo_rack_order_ptr[m] = just2_return;
        }

        for (int i = 0; i < 9; i++) audio.effect_buffer[i] = 0;

        // count active plugs in etch rack
        audio.pre_active_counter = 0;
        audio.post_active_counter = 0;
        audio.stereo_active_counter = 0;

        // set noisgate var
        if (audio.fnoise_g) {
            audio.pre_active_counter += 1;
            pre_rack_order_ptr[audio.pre_active_counter] = set_noisegate_level;
        } else {
            gx_effects::noisegate::ngate = 1;
        } 

        // run noisesharper
        if (audio.fng) {
            audio.pre_active_counter += 1;
            pre_rack_order_ptr[audio.pre_active_counter] =
                              &gx_effects::noise_shaper::compute;
        }

        // set order and activate pointer for the pre mono rack
        for (int m = 1; m < audio.mono_plug_counter; m++) {
            if (audio.posit[0] == m && audio.fcheckbox5 && !audio.fautowah
                                  && audio.effect_pre_post[1]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::crybaby::compute;
            } else if (audio.posit[0] == m && audio.fcheckbox5 && audio.fautowah
                                         && audio.effect_pre_post[1]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::autowah::compute;
            } else if (audio.posit[5] == m && audio.fcheckboxcom1 && audio.effect_pre_post[0]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::compressor::compute;
            } else if (audio.posit[1] == m && audio.foverdrive4 && audio.effect_pre_post[2]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::overdrive::compute;
            } else if (audio.posit[2] == m && audio.fcheckbox4 && audio.effect_pre_post[3]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::gx_distortion::compute;
            } else if (audio.posit[3] == m && audio.fcheckbox6 && audio.effect_pre_post[4]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::freeverb::compute;
            } else if (audio.posit[6] == m && audio.fcheckbox7 && gx_effects::echo::is_inited()
                                         && audio.effect_pre_post[6]) {
                audio.pre_active_counter += 1;
                audio.effect_buffer[0] = audio.pre_active_counter;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::echo::compute;
            } else if (audio.posit[4] == m && audio.fcheckbox8 && audio.effect_pre_post[5]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::impulseresponse::compute;
            } else if (audio.posit[7] == m && audio.fdelay && gx_effects::delay::is_inited()
                                         && audio.effect_pre_post[7]) {
                audio.pre_active_counter += 1;
                audio.effect_buffer[1] = audio.pre_active_counter;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::delay::compute;
            } else if (audio.posit[10] == m && audio.feq && audio.effect_pre_post[8]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::selecteq::compute;
            } else if (audio.posit[14] == m && audio.flh && audio.effect_pre_post[9]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::low_high_pass::compute;
            } else if (audio.posit[17] == m && audio.fwv && audio.effect_pre_post[10]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] = &set_osc_buffer;
            } else if (audio.posit[18] == m && audio.fbiquad && audio.effect_pre_post[11]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::biquad::compute;
            } else if (audio.posit[21] == m && audio.ftremolo && audio.effect_pre_post[12]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::tremolo::compute;
            } else if (audio.posit[22] == m && audio.fpm && audio.effect_pre_post[13]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::phaser_mono::compute;
            } else if (audio.posit[23] == m && audio.fchorus_mono && audio.effect_pre_post[14]
                                          && gx_effects::chorus_mono::is_inited()) {
                audio.pre_active_counter += 1;
                audio.effect_buffer[2] = audio.pre_active_counter;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::chorus_mono::compute;
            } else if (audio.posit[24] == m && audio.fflanger_mono && audio.effect_pre_post[15]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::flanger_mono::compute;
            } else if (audio.posit[25] == m && audio.ffeedback && audio.effect_pre_post[16]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] =
                                  &gx_effects::gx_feedback::compute;
            } else if (audio.posit[26] == m && audio.ftonestack && audio.effect_pre_post[17]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] = tonestack_ptr;
            } else if (audio.posit[27] == m && audio.fcab && audio.effect_pre_post[18]) {
                audio.pre_active_counter += 1;
                pre_rack_order_ptr[audio.pre_active_counter] = &run_cab_conf;
            }
        }

        // clipper
        if (audio.ftube) {
            audio.post_active_counter += 1;
            post_rack_order_ptr[audio.post_active_counter] =
                               &gx_effects::softclip::compute;
        }

        // set order and activate pointer for the post mono rack
        for (int m = 1; m < audio.mono_plug_counter; m++) {
            if (audio.posit[0] == m && audio.fcheckbox5 && !audio.fautowah
                                  && !audio.effect_pre_post[1]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::crybaby::compute;
            } else if (audio.posit[0] == m && audio.fcheckbox5 && audio.fautowah
                                         && !audio.effect_pre_post[1]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::autowah::compute;
            } else if (audio.posit[5] == m && audio.fcheckboxcom1 && !audio.effect_pre_post[0]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::compressor::compute;
            } else if (audio.posit[1] == m && audio.foverdrive4 && !audio.effect_pre_post[2]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::overdrive::compute;
            } else if (audio.posit[2] == m && audio.fcheckbox4 && !audio.effect_pre_post[3]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::gx_distortion::compute;
            } else if (audio.posit[3] == m && audio.fcheckbox6 && !audio.effect_pre_post[4]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::freeverb::compute;
            } else if (audio.posit[6] == m && audio.fcheckbox7 && gx_effects::echo::is_inited()
                                         && !audio.effect_pre_post[6]) {
                audio.post_active_counter += 1;
                audio.effect_buffer[3] = audio.post_active_counter;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::echo::compute;
            } else if (audio.posit[4] == m && audio.fcheckbox8 && !audio.effect_pre_post[5]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::impulseresponse::compute;
            } else if (audio.posit[7] == m && audio.fdelay && gx_effects::delay::is_inited()
                                         && !audio.effect_pre_post[7]) {
                audio.post_active_counter += 1;
                audio.effect_buffer[4] = audio.post_active_counter;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::delay::compute;
            } else if (audio.posit[10] == m && audio.feq && !audio.effect_pre_post[8]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::selecteq::compute;
            } else if (audio.posit[14] == m && audio.flh && !audio.effect_pre_post[9]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::low_high_pass::compute;
            } else if (audio.posit[17] == m && audio.fwv && !audio.effect_pre_post[10]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] = &set_osc_buffer;
            } else if (audio.posit[18] == m && audio.fbiquad && !audio.effect_pre_post[11]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::biquad::compute;
            } else if (audio.posit[21] == m && audio.ftremolo && !audio.effect_pre_post[12]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::tremolo::compute;
            } else if (audio.posit[22] == m && audio.fpm && !audio.effect_pre_post[13]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::phaser_mono::compute;
            } else if (audio.posit[23] == m && audio.fchorus_mono && !audio.effect_pre_post[14]
                                          && gx_effects::chorus_mono::is_inited()) {
                audio.post_active_counter += 1;
                audio.effect_buffer[5] = audio.post_active_counter;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::chorus_mono::compute;
            } else if (audio.posit[24] == m && audio.fflanger_mono && !audio.effect_pre_post[15]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::flanger_mono::compute;
            } else if (audio.posit[25] == m && audio.ffeedback && !audio.effect_pre_post[16]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] =
                                   &gx_effects::gx_feedback::compute;
            } else if (audio.posit[26] == m && audio.ftonestack && !audio.effect_pre_post[17]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] = tonestack_ptr;
            } else if (audio.posit[27] == m && audio.fcab && !audio.effect_pre_post[18]) {
                audio.post_active_counter += 1;
                post_rack_order_ptr[audio.post_active_counter] = &run_cab_conf;
            }
        }

        // bass boster
        if (audio.fboost) {
            audio.post_active_counter += 1;
            post_rack_order_ptr[audio.post_active_counter] =
                               &gx_effects::bassbooster::compute;
        }

        // mono output level
        if (audio.fampout) {
            audio.post_active_counter += 1;
            post_rack_order_ptr[audio.post_active_counter] =
                               &gx_effects::gx_ampout::compute;
        }

        // run noisegate
        if (audio.fnoise_g) {
            audio.post_active_counter += 1;
            post_rack_order_ptr[audio.post_active_counter] =
                               &gx_effects::noisegate::compute;
        }

        // presence
        if (audio.fcon) {
            audio.post_active_counter += 1;
            post_rack_order_ptr[audio.post_active_counter] = &run_contrast;
        }

        // split mono input to stereo source
        audio.stereo_active_counter += 1;
        stereo_rack_order_ptr[audio.stereo_active_counter] =
                             &run_gxfeed;

        // set order and activate pointer for the stereo rack
        for (int m = 1; m < audio.stereo_plug_counter; m++) {
            if (audio.posit[8] == m && audio.fchorus && gx_effects::chorus::is_inited()) {
                audio.stereo_active_counter += 1;
                audio.effect_buffer[6] = audio.stereo_active_counter;
                stereo_rack_order_ptr[audio.stereo_active_counter] =
                                     &gx_effects::chorus::compute;
            } else if (audio.posit[9] == m && audio.fflanger) {
                audio.stereo_active_counter += 1;
                stereo_rack_order_ptr[audio.stereo_active_counter] =
                                     &gx_effects::flanger::compute;
            } else if (audio.posit[11] == m && audio.fmoog) {
                audio.stereo_active_counter += 1;
                stereo_rack_order_ptr[audio.stereo_active_counter] =
                                     &gx_effects::moog::compute;
            } else if (audio.posit[12] == m && audio.fphaser) {
                audio.stereo_active_counter += 1;
                stereo_rack_order_ptr[audio.stereo_active_counter] =
                                     &gx_effects::phaser::compute;
            } else if (audio.posit[15] == m && audio.fsd && gx_effects::stereodelay::is_inited()) {
                audio.stereo_active_counter += 1;
                audio.effect_buffer[7] = audio.stereo_active_counter;
                stereo_rack_order_ptr[audio.stereo_active_counter] =
                                     &gx_effects::stereodelay::compute;
            } else if (audio.posit[16] == m && audio.fse && gx_effects::stereoecho::is_inited()) {
                audio.stereo_active_counter += 1;
                audio.effect_buffer[8] = audio.stereo_active_counter;
                stereo_rack_order_ptr[audio.stereo_active_counter] =
                                     &gx_effects::stereoecho::compute;
            } else if (audio.posit[19] == m && audio.famp) {
                audio.stereo_active_counter += 1;
                stereo_rack_order_ptr[audio.stereo_active_counter] =
                                     &gx_amps::gx_ampmodul::compute;
            } else if (audio.posit[20] == m && audio.ftone) {
                audio.stereo_active_counter += 1;
                stereo_rack_order_ptr[audio.stereo_active_counter] =
                                     &gx_effects::tonecontroll::compute;
            }
        }
        gx_engine::audio.rack_change = false;
    }
    return TRUE;
}

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

