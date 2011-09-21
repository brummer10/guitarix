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
 * --------------------------------------------------------------------------
 */


/****************************************************************
 **  definitions for code generated with faust / dsp2cc
 */


typedef struct {
    inifunc func;
    const char *name;
} inidef;


static list<inidef>& get_inilist() {
    static list<inidef> inilist;
    return inilist;
}

static list<gx_gui::Parameter*>& get_paramlist() {
    static list<gx_gui::Parameter*> paramlist;
    return paramlist;
}

void register_faust_parameters() {
    list<gx_gui::Parameter*>& paramlist = get_paramlist();
    for (list<gx_gui::Parameter*>::iterator i = paramlist.begin(); i != paramlist.end(); i++) {
        gx_gui::parameter_map.insert(*i);
        // fprintf(stderr, "%s \n",(*i)->id().c_str() );
    }
    paramlist.clear();
}

static gx_gui::Parameter *find_parameter(const char *id) {
    list<gx_gui::Parameter*>& paramlist = get_paramlist();
    for (list<gx_gui::Parameter*>::iterator i = paramlist.begin(); i != paramlist.end(); i++) {
        if ((*i)->id() == id) {
            return *i;
        }
    }
    return 0;
}

static float& get_alias(const char *id) {
    static float dummy;
    gx_gui::Parameter *p = find_parameter(id);
    if (!p) {
        gx_system::gx_print_error("engine", string
                 ("can't define alias for unknown (or not yet defined) parameter id: ") + id);
        return dummy;
    } else {
        return p->getFloat().value;
    }
}

void registerVar(const char* id, const char* name, const char* tp,
		 const char* tooltip, float* var, float val,
		 float low, float up, float step, bool exp) {
    if (!name[0]) {
	assert(strrchr(id, '.'));
	name = strrchr(id, '.')+1;
    }
    gx_gui::Parameter *p = new gx_gui::FloatParameter(
        id, name, gx_gui::Parameter::Continuous, true, *var, val,
	low, up, step, true, exp);
    if (tooltip) {
        p->set_desc(tooltip);
    }
    get_paramlist().push_back(p);
}

void registerEnumVar(const char *id, const char* name, const char* tp,
		     const char* tooltip, const char** values, float *var,
		     float val, float low, float up, float step, bool exp) {
    if (!name[0]) {
        assert(strrchr(id, '.'));
        name = strrchr(id, '.')+1;
    }
    assert(low == 0.0 && step == 1.0);
    gx_gui::FloatEnumParameter *p = new gx_gui::FloatEnumParameter(
        id, name, values, true, *var,
        static_cast<int>(round(val)), true, exp); // false == no_midi_var
    assert(up == p->upper); // calculated by constructor
    get_paramlist().push_back(p);
}

static inline void registerIntParam(const char*a, const char*b, int*c, int std = 0,
                                    int lower = 0, int upper = 1, bool exp = false) {
     get_paramlist().push_back(
         new gx_gui::IntParameter(a , b, gx_gui::Parameter::Enum, true, *c, std,
                                  lower, upper, true, exp));
}

void registerInit(const char *name, inifunc f) {
    inidef i;
    i.func = f;
    i.name = name;
    // fprintf(stderr, "%s \n", i.name);
    get_inilist().push_back(i);
}

static void jack_sync() {
    while (sem_wait(&gx_jack::jack_sync_sem) == EINTR);
}

#include <gx_faust_support.h>

/****************************************************************
 **  include faust/dsp2cc generated files
 */

namespace gx_amps {

// gxdistortion
static struct GxDistortionParams { GxDistortionParams();}
GxDistortionParams;
GxDistortionParams::GxDistortionParams() {
    static FAUSTFLOAT v1, v2;
    registerVar("gxdistortion.drive",   "", "S", "", &v1, 0.35,  0.0,   1.0, 0.01);
    registerVar("gxdistortion.wet_dry", "", "S", "", &v2, 100.0, 0.0, 100.0, 1.0);
}

#include "faust/gxamp.cc"
#include "faust/gxamp2.cc"
#include "faust/gxamp3.cc"
#include "faust/gxamp4.cc"
#include "faust/gxamp5.cc"
#include "faust/gxamp6.cc"
#include "faust/gxamp7.cc"
#include "faust/gxamp8.cc"
#include "faust/gxamp9.cc"
#include "faust/gxamp10.cc"
#include "faust/gxamp11.cc"
#include "faust/gxamp12.cc"
#include "faust/gxamp13.cc"
#include "faust/gxamp14.cc"
#include "faust/gxamp15.cc"
#include "faust/gxamp16.cc"
#include "faust/gxamp17.cc"
#include "faust/gx_ampmodul.cc"
}

// effects
namespace gx_effects {

// foreign variable added to faust module feed
namespace noisegate { float ngate = 1;}  // noise-gate, modifies output gain

static struct CabParams { CabParams();}
CabParams;
CabParams::CabParams() {
    registerVar("cab.Level", "",  "S", "", &audio.cab_level,  1.0, 0.5, 5.0, 0.5);
    registerVar("cab.bass", "",   "S", "", &audio.cab_bass,   0.0, -10.0, 10.0, 0.5);
    registerVar("cab.treble", "", "S", "", &audio.cab_treble, 0.0, -10.0, 10.0, 0.5);

    registerVar("con.Level", "",  "S", "", &audio.con_level,  1.0, 0.5, 5.0, 0.5);
}


#include "faust/bassbooster.cc"
#include "faust/gxfeed.cc"
#include "faust/gx_feedback.cc"
#include "faust/balance.cc"
#include "faust/jconv_post.cc"
#include "faust/balance1.cc"
#include "faust/gx_outputlevel.cc"
#include "faust/gx_ampout.cc"
#include "faust/overdrive.cc"
#include "faust/compressor.cc"
#include "faust/crybaby.cc"
#include "faust/autowah.cc"
#include "faust/echo.cc"
#include "faust/delay.cc"
#include "faust/stereodelay.cc"
#include "faust/stereoecho.cc"
#include "faust/noise_shaper.cc"
#include "faust/gx_distortion.cc"
#include "faust/freeverb.cc"
#include "faust/impulseresponse.cc"
#include "faust/chorus.cc"
#include "faust/moog.cc"
#include "faust/biquad.cc"
#include "faust/flanger.cc"
#include "faust/selecteq.cc"
#include "faust/phaser.cc"
#include "faust/low_high_pass.cc"
#include "faust/noisegate.cc"
#include "faust/softclip.cc"
#include "faust/tonecontroll.cc"
#include "faust/tremolo.cc"
#include "faust/phaser_mono.cc"
#include "faust/chorus_mono.cc"
#include "faust/flanger_mono.cc"
#include "cabinet_impulse_former.cc"
#include "faust/presence_level.cc"
#include "faust/stereoverb.cc"
}

// init cabinet impulse former to 48000 Hz, the buffer will resampled
// afterwards when needed.
void init_non_rt_processing() {
    gx_effects::cabinet_impulse_former::init(48000);
}

void non_rt_processing(int count, float* input, float* output0) {
    gx_effects::cabinet_impulse_former::compute(count, input, output0);
}

// init presence impulse former to 48000 Hz, the buffer will resampled
// afterwards when needed.
void init_presence_processing() {
    gx_effects::presence_level::init(48000);
}

void presence_processing(int count, float* input, float* output0) {
    gx_effects::presence_level::compute(count, input, output0);
}

// tone stack
namespace gx_tonestacks {

static struct ToneStackParams { ToneStackParams(); }
ToneStackParams;
ToneStackParams::ToneStackParams() {
    static FAUSTFLOAT v1, v2, v3;
    registerVar("amp.tonestack.Treble", "", "S", "", &v1, 0.5, 0.0, 1.0, 0.01);
    registerVar("amp.tonestack.Bass",   "", "S", "", &v2, 0.5, 0.0, 1.0, 0.01);
    registerVar("amp.tonestack.Middle", "", "S", "", &v3, 0.5, 0.0, 1.0, 0.01);
}

#include "faust/tonestack_default.cc"
#include "faust/tonestack_bassman.cc"
#include "faust/tonestack_twin.cc"
#include "faust/tonestack_princeton.cc"
#include "faust/tonestack_jcm800.cc"
#include "faust/tonestack_jcm2000.cc"
#include "faust/tonestack_mlead.cc"
#include "faust/tonestack_m2199.cc"
#include "faust/tonestack_ac30.cc"
#include "faust/tonestack_mesa.cc"
#include "faust/tonestack_soldano.cc"
#include "faust/tonestack_jtm45.cc"
#include "faust/tonestack_ac15.cc"
#include "faust/tonestack_peavey.cc"
#include "faust/tonestack_ibanez.cc"
#include "faust/tonestack_roland.cc"
#include "faust/tonestack_ampeg.cc"
#include "faust/tonestack_ampeg_rev.cc"
#include "faust/tonestack_sovtek.cc"
#include "faust/tonestack_bogner.cc"
#include "faust/tonestack_groove.cc"
#include "faust/tonestack_crunch.cc"
#include "faust/tonestack_fender_blues.cc"
#include "faust/tonestack_fender_default.cc"
#include "faust/tonestack_fender_deville.cc"
#include "faust/tonestack_gibsen.cc"
}

/****************************************************************
 **  free memory when effects are unused, load with jack_sync
 */

static void activate_callback(float val, void *data) {
    ((void (*)(bool, int))data)(!(val == 0.0), gx_jack::gxjack.jack_sr);
}

static void faust_add_callback(const char* id, void (*func)(bool, int)) {
    new gx_ui::GxUiCallbackItemFloat(gx_gui::GxMainInterface::instance(),
                                     reinterpret_cast<float*>(gx_gui::parameter_map[id].zone()),
                                     activate_callback, reinterpret_cast<void*>(func));
}

void faust_init(int samplingFreq) {
    // faust_add_callback("SampleLooper.on_off", sloop::activate);
    faust_add_callback("delay.on_off",         gx_effects::delay::activate);
    faust_add_callback("echo.on_off",          gx_effects::echo::activate);
    faust_add_callback("chorus.on_off",        gx_effects::chorus::activate);
    faust_add_callback("chorus_mono.on_off",   gx_effects::chorus::activate);
    faust_add_callback("stereodelay.on_off",   gx_effects::stereodelay::activate);
    faust_add_callback("stereoecho.on_off",    gx_effects::stereoecho::activate);
    list<inidef>& inilist = get_inilist();
    for (list<inidef>::iterator i = inilist.begin(); i != inilist.end(); i++) {
        try {
            i->func(samplingFreq);
        } catch(bad_alloc) {
            string name = gx_gui::param_group(i->name, true);
            gx_system::gx_print_error("DSP Module", (boost::format
                      ("not enough memory to initialize module %1%") % i->name).str());
        }
    }
}
/****************************************************************
 **  engine helper work threads to watch for user changes in the
 *   rack amp tonestack selection, create a pointer aray to the
 *   selected functions.
 */
#include "gx_engine_helpers.cc"
