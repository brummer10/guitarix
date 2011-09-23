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
 *    This is part of the Guitarix Audio Engine
 *
 *
 *
 * --------------------------------------------------------------------------
 */


/****************************************************************
 **  set the function pointer to the selected tonestack and tube/amp
 */

// seletc tonestack, only run when tonestack selection have changed
static int gx_check_tonestack_state(gpointer arg) {

    switch (audio.tonestack) {
    case 0: // "default"
	mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_default::compute;
        break;
    case 1: // "Bassman"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_bassman::compute;
        break;
    case 2: // "Twin Reverb"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_twin::compute;
        break;
    case 3: // "Princeton"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_princeton::compute;
        break;
    case 4: // "JCM-800"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_jcm800::compute;
        break;
    case 5: // "JCM-2000"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_jcm2000::compute;
        break;
    case 6: // "M-Lead"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_mlead::compute;
        break;
    case 7: // "M2199"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_m2199::compute;
        break;
    case 8: // "AC-30"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_ac30::compute;
        break;
    case 9: // "Mesa"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_mesa::compute;
        break;
    case 10: // "Soldano"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_soldano::compute;
        break;
    case 11: // "jtm45"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_jtm45::compute;
        break;
    case 12: // "ac15"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_ac15::compute;
        break;
    case 13: // "peavey"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_peavey::compute;
        break;
    case 14: // "ibanez"
        mono_chain.tonestack_ptr = gx_tonestacks::tonestack_ibanez::compute;
        break;
    case 15: // "roland"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_roland::compute;
        break;
    case 16: // "ampeg"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_ampeg::compute;
        break;
    case 17: // "ampeg rev"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_ampeg_rev::compute;
        break;
    case 18: // "sovtek"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_sovtek::compute;
        break;
    case 19: // "bogner"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_bogner::compute;
        break;
    case 20: // "groove"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_groove::compute;
        break;
    case 21: // "crunch"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_crunch::compute;
        break;
    case 22: // "fender_blues"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_fender_blues::compute;
        break;
    case 23: // "fender_default"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_fender_default::compute;
        break;
    case 24: // "fender_deville"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_fender_deville::compute;
        break;
    case 25: // "gibsen"
        mono_chain.tonestack_ptr = &gx_tonestacks::tonestack_gibsen::compute;
        break;
    case 26: // "Off"
        mono_chain.tonestack_ptr = 0;
        break;
    }
    return audio.tonestack;
}

// select amp, only run when tube/amp selection have changed
static void gx_check_engine_state(gpointer arg) {

    switch (audio.gxtube) {
    case 0: // "never"
        mono_chain.amp_ptr = &gx_amps::gxamp::compute;
        break;
    case 1: // "default" 12ax7
        mono_chain.amp_ptr = &gx_amps::gxamp::compute;
        break;
    case 2: // 12AU7
        mono_chain.amp_ptr = &gx_amps::gxamp3::compute;
        break;
    case 3: // 6V6
        mono_chain.amp_ptr = &gx_amps::gxamp2::compute;
        break;
    case 4: // pre 12AU7/ master 6V6
        mono_chain.amp_ptr = &gx_amps::gxamp4::compute;
        break;
    case 5: // pre 12ax7/ master 6V6
        mono_chain.amp_ptr = &gx_amps::gxamp5::compute;
        break;
    case 6: // 6DJ8
        mono_chain.amp_ptr = &gx_amps::gxamp10::compute;
        break;
    case 7: // pre 6DJ8/ master 6V6
        mono_chain.amp_ptr = &gx_amps::gxamp12::compute;
        break;
    case 8: // pre 6DJ8/ push-pull 6V6
        mono_chain.amp_ptr = &gx_amps::gxamp6::compute;
        break;
    case 9: // pre 12ax7/ push-pull 6V6
        mono_chain.amp_ptr = &gx_amps::gxamp7::compute;
        break;
    case 10: // pre 12AU7/ push-pull 6V6
        mono_chain.amp_ptr = &gx_amps::gxamp8::compute;
        break;
    case 11: // 12ax7 feedback
        mono_chain.amp_ptr = &gx_amps::gxamp9::compute;
        break;
    case 12: // 12AU7 feedback
        mono_chain.amp_ptr = &gx_amps::gxamp11::compute;
        break;
    case 13: // 6DJ8 feedback
        mono_chain.amp_ptr = &gx_amps::gxamp13::compute;
        break;
    case 14: // 12AT7
        mono_chain.amp_ptr = &gx_amps::gxamp14::compute;
        break;
    case 15: // pre 12AT7/ master 6V6
        mono_chain.amp_ptr = &gx_amps::gxamp15::compute;
        break;
    case 16: // pre 12AT7/ push pull 6V6
        mono_chain.amp_ptr = &gx_amps::gxamp16::compute;
        break;
    case 17: // 12AT7 feedback
        mono_chain.amp_ptr = &gx_amps::gxamp17::compute;
        break;
    default:
        mono_chain.amp_ptr = &gx_amps::gxamp::compute;
        break;
    }
    audio.tube_changed = false;
   // mono_chain.mono_rack_order_ptr[audio.amp_pos] = mono_chain.amp_ptr;

    return;
}

/****************************************************************
 **  engine functions and wrapers
 */

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

// reduce gain to compensate the increased gain by the cabinet
inline void compensate_con(int count, float *input0, float *output0) {
    double fSlow0 = (0.0010000000000000009 * pow(10, (0.05 * (-audio.con_level*2.0))));
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

gboolean conv_error_message(gpointer data) {
    gx_system::gx_print_error("Convolver", "overload");
    return false;
}

gboolean cab_error_message(gpointer data) {
    gx_system::gx_print_error("Convolver", "cabinet overload");
    return false;
}

gboolean contrast_error_message(gpointer data) {
    gx_system::gx_print_error("Convolver", "presence overload");
    return false;
}

static void convolver(int count, float *input0, float *input1,
                      float *output0, float *output1) {
    if (conv.is_runnable()) {
        // reuse oversampling buffer
        float *conv_out0 = audio.oversample;
        float *conv_out1 = audio.oversample+count;
        if (!conv.compute(count, output0, output1, conv_out0, conv_out1)) {
            gx_jconv::GxJConvSettings::checkbutton7 = 0;
            g_idle_add(conv_error_message, gpointer(NULL));
        } else {
            gx_effects::jconv_post::compute(count, output0, output1,
                                            conv_out0, conv_out1, output0, output1);
        }
    }
}

// wraper for the rack order function pointers
static void set_osc_buffer(int count, float *input0, float *output0) {
    (void)memcpy(audio.result, output0, sizeof(float)*count);
}

// wraper for the rack order function pointers
static void run_cab_conf(int count, float *input0, float *output0) {
    compensate_cab(count, output0, output0);
    if (!cab_conv.compute(count, output0)) {
        g_idle_add(cab_error_message, gpointer(NULL));
        gx_engine::audio.cab_switched = -1;
    }
}

// wraper for the presence function
static void run_contrast(int count, float *input0, float *output0) {
    compensate_con(count, output0, output0);
    if (!contrast_conv.compute(count, output0)) {
        g_idle_add(contrast_error_message, gpointer(NULL));
        gx_engine::audio.con_sum = -1;
    }
}

// wraper for the noisgate function
static void set_noisegate_level(int count, float *input0, float *output0) {
    gx_effects::noisegate::ngate = noise_gate(count, output0, gx_effects::noisegate::ngate);
}

// wraper for the mono2stereo function
static void run_gxfeed(int count, float *input0, float *input1,
                       float *output0, float *output1) {
    gx_effects::gxfeed::compute(count, output0, output0, output1);
}

/****************************************************************
 **  working thread to set the order in the all racks
 */

void gx_reorder_rack(bool do_commit) {

    audio.rack_change = false;

    // set active plugins counters to sero
    mono_chain.clear();
    stereo_chain.clear();
    
    // check if amp is changed
    if (audio.tube_changed) {
        gx_check_engine_state(NULL);
    }

    // check if tonestack is changed
    if (audio.cur_tonestack != audio.tonestack) {
        audio.cur_tonestack = gx_check_tonestack_state(NULL);
    }
    
    // set noisgate var
    if (audio.fnoise_g) {
        mono_chain.append(set_noisegate_level);
    } else {
        gx_effects::noisegate::ngate = 1;
    }

    // run noisesharper
    if (audio.fng) {
        mono_chain.append(gx_effects::noise_shaper::compute);
    }

    // set order and activate pointer for the pre mono rack
    for (unsigned int m = 1; m < audio.mono_plug_counter; m++) {
        if (audio.posit[0] == m && audio.fcheckbox5 && !audio.fautowah
                              && audio.effect_pre_post[1]) {
            mono_chain.append(gx_effects::crybaby::compute);
        } else if (audio.posit[0] == m && audio.fcheckbox5 && audio.fautowah
                                     && audio.effect_pre_post[1]) {
            mono_chain.append(gx_effects::autowah::compute);
        } else if (audio.posit[5] == m && audio.fcheckboxcom1 && audio.effect_pre_post[0]) {
	    mono_chain.append(gx_effects::compressor::compute);
        } else if (audio.posit[1] == m && audio.foverdrive4 && audio.effect_pre_post[2]) {
            mono_chain.append(gx_effects::overdrive::compute);
        } else if (audio.posit[2] == m && audio.fcheckbox4 && audio.effect_pre_post[3]) {
            mono_chain.append(gx_effects::gx_distortion::compute);
        } else if (audio.posit[3] == m && audio.fcheckbox6 && audio.effect_pre_post[4]) {
            mono_chain.append(gx_effects::freeverb::compute);
        } else if (audio.posit[6] == m && audio.fcheckbox7 && gx_effects::echo::is_inited()
                                     && audio.effect_pre_post[6]) {
            mono_chain.append(gx_effects::echo::compute);
        } else if (audio.posit[4] == m && audio.fcheckbox8 && audio.effect_pre_post[5]) {
            mono_chain.append(gx_effects::impulseresponse::compute);
        } else if (audio.posit[7] == m && audio.fdelay && gx_effects::delay::is_inited()
                                     && audio.effect_pre_post[7]) {
            mono_chain.append(gx_effects::delay::compute);
        } else if (audio.posit[10] == m && audio.feq && audio.effect_pre_post[8]) {
            mono_chain.append(gx_effects::selecteq::compute);
        } else if (audio.posit[14] == m && audio.flh && audio.effect_pre_post[9]) {
            mono_chain.append(gx_effects::low_high_pass::compute);
        } else if (audio.posit[17] == m && audio.fwv && audio.effect_pre_post[10]) {
            mono_chain.append(set_osc_buffer);
        } else if (audio.posit[18] == m && audio.fbiquad && audio.effect_pre_post[11]) {
            mono_chain.append(gx_effects::biquad::compute);
        } else if (audio.posit[21] == m && audio.ftremolo && audio.effect_pre_post[12]) {
            mono_chain.append(gx_effects::tremolo::compute);
        } else if (audio.posit[22] == m && audio.fpm && audio.effect_pre_post[13]) {
            mono_chain.append(gx_effects::phaser_mono::compute);
        } else if (audio.posit[23] == m && audio.fchorus_mono && audio.effect_pre_post[14]
                                      && gx_effects::chorus_mono::is_inited()) {
            mono_chain.append(gx_effects::chorus_mono::compute);
        } else if (audio.posit[24] == m && audio.fflanger_mono && audio.effect_pre_post[15]) {
            mono_chain.append(gx_effects::flanger_mono::compute);
        } else if (audio.posit[25] == m && audio.ffeedback && audio.effect_pre_post[16]) {
            mono_chain.append(gx_effects::gx_feedback::compute);
        } else if (audio.posit[26] == m && audio.ftonestack && audio.effect_pre_post[17]) {
	    if (mono_chain.tonestack_ptr) {
		mono_chain.append(mono_chain.tonestack_ptr);
	    }
        } else if (audio.posit[27] == m && audio.fcab && audio.effect_pre_post[18]) {
            mono_chain.append(run_cab_conf);
        } else {
	    get_pluginlist().append_module(m, 0);
	}
    }

    mono_chain.append(mono_chain.amp_ptr);

    // clipper
    if (audio.ftube) {
        mono_chain.append(gx_effects::softclip::compute);
    }

    // set order and activate pointer for the post mono rack
    for (unsigned int m = 1; m < audio.mono_plug_counter; m++) {
        if (audio.posit[0] == m && audio.fcheckbox5 && !audio.fautowah
                              && !audio.effect_pre_post[1]) {
            mono_chain.append(gx_effects::crybaby::compute);
        } else if (audio.posit[0] == m && audio.fcheckbox5 && audio.fautowah
                                     && !audio.effect_pre_post[1]) {
            mono_chain.append(gx_effects::autowah::compute);
        } else if (audio.posit[5] == m && audio.fcheckboxcom1 && !audio.effect_pre_post[0]) {
            mono_chain.append(gx_effects::compressor::compute);
        } else if (audio.posit[1] == m && audio.foverdrive4 && !audio.effect_pre_post[2]) {
            mono_chain.append(gx_effects::overdrive::compute);
        } else if (audio.posit[2] == m && audio.fcheckbox4 && !audio.effect_pre_post[3]) {
            mono_chain.append(gx_effects::gx_distortion::compute);
        } else if (audio.posit[3] == m && audio.fcheckbox6 && !audio.effect_pre_post[4]) {
            mono_chain.append(gx_effects::freeverb::compute);
        } else if (audio.posit[6] == m && audio.fcheckbox7 && gx_effects::echo::is_inited()
                                     && !audio.effect_pre_post[6]) {
            mono_chain.append(gx_effects::echo::compute);
        } else if (audio.posit[4] == m && audio.fcheckbox8 && !audio.effect_pre_post[5]) {
            mono_chain.append(gx_effects::impulseresponse::compute);
        } else if (audio.posit[7] == m && audio.fdelay && gx_effects::delay::is_inited()
                                     && !audio.effect_pre_post[7]) {
            mono_chain.append(gx_effects::delay::compute);
        } else if (audio.posit[10] == m && audio.feq && !audio.effect_pre_post[8]) {
            mono_chain.append(gx_effects::selecteq::compute);
        } else if (audio.posit[14] == m && audio.flh && !audio.effect_pre_post[9]) {
            mono_chain.append(gx_effects::low_high_pass::compute);
        } else if (audio.posit[17] == m && audio.fwv && !audio.effect_pre_post[10]) {
            mono_chain.append(set_osc_buffer);
        } else if (audio.posit[18] == m && audio.fbiquad && !audio.effect_pre_post[11]) {
            mono_chain.append(gx_effects::biquad::compute);
        } else if (audio.posit[21] == m && audio.ftremolo && !audio.effect_pre_post[12]) {
            mono_chain.append(gx_effects::tremolo::compute);
        } else if (audio.posit[22] == m && audio.fpm && !audio.effect_pre_post[13]) {
            mono_chain.append(gx_effects::phaser_mono::compute);
        } else if (audio.posit[23] == m && audio.fchorus_mono && !audio.effect_pre_post[14]
                                      && gx_effects::chorus_mono::is_inited()) {
            mono_chain.append(gx_effects::chorus_mono::compute);
        } else if (audio.posit[24] == m && audio.fflanger_mono && !audio.effect_pre_post[15]) {
            mono_chain.append(gx_effects::flanger_mono::compute);
        } else if (audio.posit[25] == m && audio.ffeedback && !audio.effect_pre_post[16]) {
            mono_chain.append(gx_effects::gx_feedback::compute);
        } else if (audio.posit[26] == m && audio.ftonestack && !audio.effect_pre_post[17]) {
	    if (mono_chain.tonestack_ptr) {
		mono_chain.append(mono_chain.tonestack_ptr);
	    }
        } else if (audio.posit[27] == m && audio.fcab && !audio.effect_pre_post[18]) {
            mono_chain.append(run_cab_conf);
        } else {
	    get_pluginlist().append_module(m, 1);
	}
    }

    // bass boster
    if (audio.fboost) {
        mono_chain.append(gx_effects::bassbooster::compute);
    }

    // mono output level
    if (audio.fampout) {
        mono_chain.append(gx_effects::gx_ampout::compute);
    }

    // run noisegate
    if (audio.fnoise_g) {
        mono_chain.append(gx_effects::noisegate::compute);
    }

    // presence
    if (audio.fcon) {
        mono_chain.append(run_contrast);
    }

    // split mono input to stereo source
    stereo_chain.append(run_gxfeed);

    // set order and activate pointer for the stereo rack
    for (unsigned int m = 1; m < audio.stereo_plug_counter; m++) {
        if (audio.posit[8] == m && audio.fchorus && gx_effects::chorus::is_inited()) {
            stereo_chain.append(gx_effects::chorus::compute);
        } else if (audio.posit[9] == m && audio.fflanger) {
            stereo_chain.append(gx_effects::flanger::compute);
        } else if (audio.posit[11] == m && audio.fmoog) {
            stereo_chain.append(gx_effects::moog::compute);
        } else if (audio.posit[12] == m && audio.fphaser) {
            stereo_chain.append(gx_effects::phaser::compute);
        } else if (audio.posit[15] == m && audio.fsd && gx_effects::stereodelay::is_inited()) {
            stereo_chain.append(gx_effects::stereodelay::compute);
        } else if (audio.posit[16] == m && audio.fse && gx_effects::stereoecho::is_inited()) {
            stereo_chain.append(gx_effects::stereoecho::compute);
        } else if (audio.posit[19] == m && audio.famp) {
            stereo_chain.append(gx_amps::gx_ampmodul::compute);
        } else if (audio.posit[20] == m && audio.ftone) {
            stereo_chain.append(gx_effects::tonecontroll::compute);
        } else if (audio.posit[28] == m && gx_jconv::GxJConvSettings::checkbutton7) {
            stereo_chain.append(convolver);
        } else if (audio.posit[29] == m && audio.ffreevst) {
            stereo_chain.append(gx_effects::stereoverb::compute);
        } else {
	    get_pluginlist().append_module(m, 2);
	}
    }

    stereo_chain.append(gx_effects::gx_outputlevel::compute);
    //stereo_chain.append(set_level_meter_bufer);

    if (do_commit) {
	mono_chain.commit();
	stereo_chain.commit();
    } else {
	mono_chain.append(0);
	stereo_chain.append(0);
    }
}

void order_rack(bool do_commit) {
    gx_check_engine_state(NULL);
    gx_reorder_rack(do_commit);
}
