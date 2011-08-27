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
    const int frag = (const int)gx_jack::gxjack.jack_bs;
    _modulpointer = new ModulPointer;
    
    audio.get_frame  = new float[frag];
    audio.get_frame1  = new float[frag];
    audio.checkfreq  = new float[frag];
    audio.oversample = new float[frag*MAX_UPSAMPLE];
    audio.result = new float[frag+46];
    audio.gxtube = 1;
    audio.gxtube_select = 1;
    audio.amp_pos = 0;
    audio.cur_tonestack = 0;
    audio.tube_changed = true;
    for (int i = 0; i < 9; i++) audio.effect_buffer[i] = 0;
    for (int i = 0; i < 30; i++) audio.posit[i] = 0;
    audio.rack_change = true;

    (void)memset(audio.get_frame,  0, frag*sizeof(float));
    (void)memset(audio.get_frame1,  0, frag*sizeof(float));
    (void)memset(audio.checkfreq,  0, frag*sizeof(float));
    (void)memset(audio.oversample, 0, frag*MAX_UPSAMPLE*sizeof(float));
    (void)memset(audio.result, 0, (frag+46)*sizeof(float));

    midi.init(gx_jack::gxjack.jack_sr);
    faust_init(gx_jack::gxjack.jack_sr);
    // resampTube.setup(gx_jack::jack_sr, 2);
    // resampDist.setup(gx_jack::jack_sr, 2);

    if (!optvar[LOAD_FILE].empty()) {
        gx_preset::gxpreset.gx_recall_settings_file(&optvar[LOAD_FILE]);
    } else {
        gx_preset::gxpreset.gx_recall_settings_file();
    }
    for (int i = 0; i < GX_NUM_OF_FACTORY_PRESET; i++)
        gx_preset::gxpreset.gx_load_factory_file(i);
    audio.rack_change = order_rack(NULL);
    audio.initialized = true;
}

void gx_engine_reset() {

    if (audio.checkfreq)  delete[] audio.checkfreq;
    if (audio.get_frame)  delete[] audio.get_frame;
    if (audio.get_frame1)  delete[] audio.get_frame1;
    if (audio.oversample) delete[] audio.oversample;
    if (audio.result) delete[] audio.result;
    delete _modulpointer;
    //delete gx_tubes::tubetab;
    audio.initialized = false;
}

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
 ** register audio variables to paramtable
 */

void AudioVariables::register_parameter() {
    static const char *on_off = N_("on/off");
    
    gx_gui::registerParam("jconv.on_off", "Run", &gx_jconv::GxJConvSettings::checkbutton7);
    gx_gui::registerParam("cab.on_off",   "Cabinet", &fcab, 0);
    gx_gui::registerParam("con.on_off",   "Contrast-ImpResp", &fcon, 0);

    gx_gui::registerParam("amp.bass_boost.on_off", on_off, &fboost, 0);
    gx_gui::registerParam("compressor.on_off",     on_off, &fcheckboxcom1, 0);
    gx_gui::registerParam("crybaby.on_off",        on_off, &fcheckbox5, 0);
    gx_gui::registerParam("overdrive.on_off",      on_off, &foverdrive4, 0);
    gx_gui::registerParam("gx_distortion.on_off",  on_off, &fcheckbox4, 0);
    gx_gui::registerParam("freeverb.on_off",       on_off, &fcheckbox6, 0);
    gx_gui::registerParam("IR.on_off",             on_off, &fcheckbox8, 0);
    gx_gui::registerParam("echo.on_off",           on_off, (float*) &fcheckbox7, 0.);
    gx_gui::registerParam("delay.on_off",          on_off, (float*) &fdelay, 0.);
    gx_gui::registerParam("chorus.on_off",         on_off, (float*) &fchorus, 0.);
    gx_gui::registerParam("eqs.on_off",            on_off, &feq, 0);
    gx_gui::registerParam("moog.on_off",           on_off, &fmoog, 0);
    gx_gui::registerParam("biquad.on_off",         on_off, &fbiquad, 0);
    gx_gui::registerParam("flanger.on_off",        on_off, &fflanger, 0);
    gx_gui::registerParam("phaser.on_off",         on_off, (float*) &fphaser, 0.);
    gx_gui::registerParam("shaper.on_off",         on_off, &fng, 0);
    gx_gui::registerParam("low_highpass.on_off",   on_off, &flh, 0);
    gx_gui::registerParam("stereodelay.on_off",    on_off, (float*) &fsd, 0.);
    gx_gui::registerParam("stereoecho.on_off",     on_off, (float*) &fse, 0.);
    gx_gui::registerParam("midi_out.on_off",       on_off, &fmi, 0);
    gx_gui::registerParam("oscilloscope.on_off",   on_off, &fwv, 0);
    gx_gui::registerParam("ampmodul.on_off",       on_off, &famp, 0);
    gx_gui::registerParam("noise_gate.on_off",     on_off, &fnoise_g, 0);
    gx_gui::registerParam("amp.on_off",            on_off, &fampout, 0);
    gx_gui::registerParam("amp.clip.on_off",       on_off, &ftube, 0);
    gx_gui::registerParam("tonemodul.on_off",      on_off, &ftone, 0);
    gx_gui::registerParam("tremolo.on_off",        on_off, &ftremolo, 0);
    gx_gui::registerParam("phaser_mono.on_off",    on_off, &fpm, 0);
    gx_gui::registerParam("chorus_mono.on_off",    on_off, (float*) &fchorus_mono, 0.);
    gx_gui::registerParam("flanger_mono.on_off",   on_off, &fflanger_mono, 0);
    gx_gui::registerParam("feedback.on_off",       on_off, &ffeedback, 0);
    gx_gui::registerParam("amp.tonestack.on_off",  on_off, &ftonestack, 0);

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
    N_("Princeton"), N_("A2"), N_("1x15"), N_("Mesa Boogie"), N_("Briliant"), 0};
    registerEnumParam("cab.select", "select", cabinet_model, &cabinet, 0);


    static const char *tube_model[] = {N_("12ax7"), N_("12AU7"), N_("12AT7"), N_("6DJ8"),
    N_("6V6"), N_("12ax7 feedback"), N_("12AU7 feedback"), N_("12AT7 feedback"), N_("6DJ8 feedback"), N_("pre 12ax7/ master 6V6"),
    N_("pre 12AU7/ master 6V6"), N_("pre 12AT7/ master 6V6"), N_("pre 6DJ8/ master 6V6"),
    N_("pre 12ax7/ push-pull 6V6"), N_("pre 12AU7/ push-pull 6V6"), N_("pre 12AT7/ push pull 6V6"), N_("pre 6DJ8/ push-pull 6V6"), 0};
    registerEnumParam("tube.select", "select", tube_model, &gxtube_select, 0);

    /*static const char *tube_model[] = {N_(" "), N_("12ax7"), N_("12AU7"), N_("6V6"), N_("pre 12AU7/ master 6V6"), N_("pre 12ax7/ master 6V6"),
    N_("6DJ8"), N_("pre 6DJ8/ master 6V6"), N_("pre 6DJ8/ push-pull 6V6"), N_("pre 12ax7/ push-pull 6V6"), N_("pre 12AU7/ push-pull 6V6"),
    N_("12ax7 feedback"), N_("12AU7 feedback"), N_("6DJ8 feedback"), N_("12AT7"),
    N_("pre 12AT7/ master 6V6"), N_("pre 12AT7/ push pull 6V6"), N_("12AT7 feedback"), 0};
    registerEnumParam("amp.select", "select", tube_model, &gxtube, 0); */

    static const char *post_pre[] = {N_("post"), N_("pre"), 0};
    registerUEnumParam("compressor.pp", "select",     post_pre, &effect_pre_post[0], 0);
    registerUEnumParam("crybaby.pp", "select",        post_pre, &effect_pre_post[1], 0);
    registerUEnumParam("overdrive.pp", "select",      post_pre, &effect_pre_post[2], 0);
    registerUEnumParam("gx_distortion.pp", "select",  post_pre, &effect_pre_post[3], 0);
    registerUEnumParam("freeverb.pp", "select",       post_pre, &effect_pre_post[4], 0);
    registerUEnumParam("IR.pp", "select",             post_pre, &effect_pre_post[5], 0);
    registerUEnumParam("echo.pp", "select",           post_pre, &effect_pre_post[6], 0);
    registerUEnumParam("delay.pp", "select",          post_pre, &effect_pre_post[7], 0);
    registerUEnumParam("eqs.pp", "select",            post_pre, &effect_pre_post[8], 0);
    registerUEnumParam("low_highpass.pp", "select",   post_pre, &effect_pre_post[9], 0);
    registerUEnumParam("oscilloscope.pp", "select",   post_pre, &effect_pre_post[10], 0);
    registerUEnumParam("biquad.pp", "select",         post_pre, &effect_pre_post[11], 0);
    registerUEnumParam("tremolo.pp", "select",        post_pre, &effect_pre_post[12], 0);
    registerUEnumParam("phaser_mono.pp", "select",    post_pre, &effect_pre_post[13], 0);
    registerUEnumParam("chorus_mono.pp", "select",    post_pre, &effect_pre_post[14], 0);
    registerUEnumParam("flanger_mono.pp", "select",   post_pre, &effect_pre_post[15], 0);
    registerUEnumParam("feedback.pp", "select",       post_pre, &effect_pre_post[16], 0);
    registerUEnumParam("amp.tonestack.pp", "select",  post_pre, &effect_pre_post[17], 0);
    registerUEnumParam("cab.pp", "select",            post_pre, &effect_pre_post[18], 0);

    static const char *crybaby_autowah[] = {N_("manual"), N_("auto"), 0};
    registerEnumParam("crybaby.autowah", "select", crybaby_autowah, &fautowah, 0);

    registerNonMidiParam("compressor.position",      &posit[5],  true, 6,  1, 29);
    registerNonMidiParam("crybaby.position",         &posit[0],  true, 3,  1, 29);
    registerNonMidiParam("overdrive.position",       &posit[1],  true, 7,  1, 29);
    registerNonMidiParam("gx_distortion.position",   &posit[2],  true, 4,  1, 29);
    registerNonMidiParam("freeverb.position",        &posit[3],  true, 10, 1, 29);
    registerNonMidiParam("IR.position",              &posit[4],  true, 5,  1, 29);
    registerNonMidiParam("echo.position",            &posit[6],  true, 8,  1, 29);
    registerNonMidiParam("delay.position",           &posit[7],  true, 9,  1, 29);
    registerNonMidiParam("eqs.position",             &posit[10], true, 2,  1, 29);
    registerNonMidiParam("chorus.position",          &posit[8],  true, 1,  1, 19);
    registerNonMidiParam("flanger.position",         &posit[9],  true, 2,  1, 19);
    registerNonMidiParam("moog.position",            &posit[11], true, 6,  1, 19);
    registerNonMidiParam("phaser.position",          &posit[12], true, 3,  1, 19);
    registerNonMidiParam("low_highpass.position",    &posit[14], true, 1,  1, 29);
    registerNonMidiParam("stereodelay.position",     &posit[15], true, 4,  1, 19);
    registerNonMidiParam("stereoecho.position",      &posit[16], true, 5,  1, 19);
    registerNonMidiParam("oscilloscope.position",    &posit[17], true, 11, 1, 29);
    registerNonMidiParam("biquad.position",          &posit[18], true, 12, 1, 29);
    // registerNonMidiParam("midi_out.position",     &posit[28], true, 20, 1, 29);
    registerNonMidiParam("ampmodul.position",        &posit[19], true, 7,  1, 19);
    registerNonMidiParam("tonemodul.position",       &posit[20], true, 8,  1, 19);
    registerNonMidiParam("tremolo.position",         &posit[21], true, 13, 1, 29);
    registerNonMidiParam("phaser_mono.position",     &posit[22], true, 14, 1, 29);
    registerNonMidiParam("chorus_mono.position",     &posit[23], true, 15, 1, 29);
    registerNonMidiParam("flanger_mono.position",    &posit[24], true, 16, 1, 29);
    registerNonMidiParam("feedback.position",        &posit[25], true, 17, 1, 29);
    registerNonMidiParam("amp.tonestack.position",   &posit[26], true, 18, 1, 29);
    registerNonMidiParam("cab.position",             &posit[27], true, 19, 1, 29);
    registerNonMidiParam("jconv.position",           &posit[28], true, 9, 1, 19);

    registerNonMidiParam("system.waveview",          &viv, false);
    registerNonMidiParam("midi_out.midistat",        &midistat, false);
    registerNonMidiParam("midi_out.midistat1",       &midistat1, false);
    registerNonMidiParam("midi_out.midistat2",       &midistat2, false);
    registerNonMidiParam("midi_out.midistat3",       &midistat3, false);

    // user interface options
    registerNonMidiParam("ui.latency_nowarn",        &fwarn, false, 0);
    registerNonMidiParam("ui.skin",                  &fskin, false, 0, 0, 100);

    get_frame   = NULL;
    get_frame1  = NULL;
    checkfreq   = NULL;
    oversample  = NULL;
    result      = NULL;
    checky      = kEngineOn;
    
    /* engine init state  */
    audio.initialized = false;

    /* pitchtracker init state  */
    pitch_tracker.pt_initialized = false;

    /* buffer ready state */
    audio.buffers_ready = false;
}
} /* end of gx_engine namespace */
