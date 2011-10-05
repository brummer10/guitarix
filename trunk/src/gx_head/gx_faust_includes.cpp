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

float *registerVar(const char* id, const char* name, const char* tp,
		 const char* tooltip, float* var, float val,
		 float low, float up, float step, bool exp) {
    if (!name[0]) {
	assert(strrchr(id, '.'));
	name = strrchr(id, '.')+1;
    }
    int n = strlen(tp);
    if (n && tp[n-1] == 'A') {
	if (gx_gui::parameter_map.hasId(id)) {
	    gx_gui::Parameter& p = gx_gui::parameter_map[id];
#ifndef NDEBUG
	    gx_gui::FloatParameter p2(
		id, name, gx_gui::Parameter::Continuous, true,
		p.getFloat().value, val, low, up, step, true, exp);
	    gx_gui::compare_parameter("Alias Parameter", &p, &p2);
#endif
	    return &p.getFloat().value;
	}
    }
    gx_gui::Parameter *p = new gx_gui::FloatParameter(
        id, name, gx_gui::Parameter::Continuous, true, *var, val,
	low, up, step, true, exp);
    if (tooltip && tooltip[0]) {
        p->set_desc(tooltip);
    }
    gx_gui::parameter_map.insert(p);
    return var;
}

void registerEnumVar(
    const char *id, const char* name, const char* tp,
    const char* tooltip, const value_pair* values,
    float *var, float val, float low, float up, float step, bool exp) {
    if (!name[0]) {
        assert(strrchr(id, '.'));
        name = strrchr(id, '.')+1;
    }
    assert(low == 0.0 && step == 1.0);
    gx_gui::FloatEnumParameter *p = new gx_gui::FloatEnumParameter(
        id, name, values, true, *var,
        static_cast<int>(round(val)), true, exp); // false == no_midi_var
    assert(up == p->upper); // calculated by constructor
    gx_gui::parameter_map.insert(p);
}

void registerUEnumVar(
    const char *id, const char* name, const char* tp,
    const char* tooltip, const value_pair* values,
    unsigned int *var, unsigned int std, bool exp) {
    if (!name[0]) {
        assert(strrchr(id, '.'));
        name = strrchr(id, '.')+1;
    }
    gx_gui::UEnumParameter *p = new gx_gui::UEnumParameter(
        id, name, values, true, *var, std, true, exp);
    gx_gui::parameter_map.insert(p);
}

#include <gx_faust_support.h>

/****************************************************************
 **  include faust/dsp2cc generated files
 */

namespace gx_amps {

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
#include "faust/bassbooster.cc"
#include "faust/gxfeed.cc"
#include "faust/gx_feedback.cc"
//#include "faust/balance.cc"
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
#include "faust/softclip.cc"
#include "faust/tonecontroll.cc"
#include "faust/tremolo.cc"
#include "faust/phaser_mono.cc"
#include "faust/chorus_mono.cc"
#include "faust/flanger_mono.cc"
#include "faust/cabinet_impulse_former.cc"
#include "faust/presence_level.cc"
#include "faust/stereoverb.cc"
}

// tone stack
namespace gx_tonestacks {

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
 **  audio module initialization
 */

void faust_init(int samplingFreq) {
    gx_effects::balance1::init(gx_jack::gxjack.jack_sr);
}

/****************************************************************
 **  engine helper work threads to watch for user changes in the
 *   rack amp tonestack selection, create a pointer aray to the
 *   selected functions.
 */
#include "gx_engine_helpers.cc"

void GxEngine::load_plugins(string plugin_dir) {

    static PluginDef *builtin_crybaby_plugins[] = {
	&gx_effects::crybaby::plugin,
	&gx_effects::autowah::plugin,
	0
    };

    static ModuleSelector crybaby("crybaby", N_("Crybaby"), builtin_crybaby_plugins,
				  "crybaby.autowah", _("select"), 0, PGN_POST_PRE);


    static PluginDef *builtin_tonestack_plugins[] = {
	&gx_tonestacks::tonestack_default::plugin,
	&gx_tonestacks::tonestack_bassman::plugin,
	&gx_tonestacks::tonestack_twin::plugin,
	&gx_tonestacks::tonestack_princeton::plugin,
	&gx_tonestacks::tonestack_jcm800::plugin,
	&gx_tonestacks::tonestack_jcm2000::plugin,
	&gx_tonestacks::tonestack_mlead::plugin,
	&gx_tonestacks::tonestack_m2199::plugin,
	&gx_tonestacks::tonestack_ac30::plugin,
	&gx_tonestacks::tonestack_soldano::plugin,
	&gx_tonestacks::tonestack_mesa::plugin,
	&gx_tonestacks::tonestack_jtm45::plugin,
	&gx_tonestacks::tonestack_ac15::plugin,
	&gx_tonestacks::tonestack_peavey::plugin,
	&gx_tonestacks::tonestack_ibanez::plugin,
	&gx_tonestacks::tonestack_roland::plugin,
	&gx_tonestacks::tonestack_ampeg::plugin,
	&gx_tonestacks::tonestack_ampeg_rev::plugin,
	&gx_tonestacks::tonestack_sovtek::plugin,
	&gx_tonestacks::tonestack_bogner::plugin,
	&gx_tonestacks::tonestack_groove::plugin,
	&gx_tonestacks::tonestack_crunch::plugin,
	&gx_tonestacks::tonestack_fender_blues::plugin,
	&gx_tonestacks::tonestack_fender_default::plugin,
	&gx_tonestacks::tonestack_fender_deville::plugin,
	&gx_tonestacks::tonestack_gibsen::plugin,
	0
    };

    static ModuleSelector tonestack("amp.tonestack", N_("Tonestack"),
				    builtin_tonestack_plugins, "amp.tonestack.select",
				    _("select"), 0, PGN_POST_PRE);


    static PluginDef *builtin_amp_plugins[] = {
	&gx_amps::gxamp::plugin,
	&gx_amps::gxamp3::plugin,
	&gx_amps::gxamp14::plugin,
	&gx_amps::gxamp10::plugin,

	&gx_amps::gxamp2::plugin,

	&gx_amps::gxamp9::plugin,
	&gx_amps::gxamp11::plugin,
	&gx_amps::gxamp17::plugin,
	&gx_amps::gxamp13::plugin,

	&gx_amps::gxamp5::plugin,
	&gx_amps::gxamp4::plugin,
	&gx_amps::gxamp15::plugin,
	&gx_amps::gxamp12::plugin,

	&gx_amps::gxamp7::plugin,
	&gx_amps::gxamp8::plugin,
	&gx_amps::gxamp16::plugin,
	&gx_amps::gxamp6::plugin,
	0
    };

    static const char* ampstack_groups[] = {
	".amp2.stage1",  N_("Tube1"),
	".amp2.stage2",  N_("Tube2"),
	".tube",         N_("Tube 1"),
	".gxdistortion", N_("Multi Band Distortion"),
	0
    };

    static ModuleSelector ampstack("ampstack", "?Tube", builtin_amp_plugins,
				   "tube.select", _("select"), ampstack_groups);

    PluginList& pl = get_pluginlist();

    // * mono amp input position *

    pl.add(&noisegate.inputlevel,                PLUGIN_POS_START, PGN_GUI|PGN_PRE);
    pl.add(&gx_effects::noise_shaper::plugin,    PLUGIN_POS_START, PGN_GUI|PGN_PRE);

    // rack pre mono modules inserted here

    pl.add(builtin_amp_plugins,                  PLUGIN_POS_START, PGN_ALTERNATIVE|PGN_POST);
    pl.add(&ampstack.plugin,                     PLUGIN_POS_START, PGN_POST);
    pl.add(&gx_effects::softclip::plugin,        PLUGIN_POS_START, PGN_GUI|PGN_POST);

    // rack post mono modules inserted here

    pl.add(&gx_effects::bassbooster::plugin,     PLUGIN_POS_END, PGN_GUI|PGN_POST);
    pl.add(&gx_effects::gx_ampout::plugin,       PLUGIN_POS_END, PGN_GUI|PGN_POST);
    pl.add(&contrast.plugin,                     PLUGIN_POS_END, PGN_GUI|PGN_POST);
    pl.add(&noisegate.outputgate,                PLUGIN_POS_END, PGN_POST);

    // * amp insert position (stereo amp input) *

    pl.add(&gx_effects::gxfeed::plugin,          PLUGIN_POS_START);

    // rack stereo modules inserted here

    pl.add(&gx_effects::gx_outputlevel::plugin,  PLUGIN_POS_END);

    // * fx amp output *

    // dynamic rack modules
    // builtin 
    pl.add(builtin_crybaby_plugins,              PLUGIN_POS_RACK, PGN_ALTERNATIVE);
    pl.add(builtin_tonestack_plugins,            PLUGIN_POS_RACK, PGN_ALTERNATIVE);

    // mono
    pl.add(&gx_effects::low_high_pass::plugin,   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::selecteq::plugin,        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&crybaby.plugin,                      PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::gx_distortion::plugin,   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::impulseresponse::plugin, PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::compressor::plugin,      PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::overdrive::plugin,       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::echo::plugin,            PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::delay::plugin,           PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::freeverb::plugin,        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&oscilloscope.plugin,                 PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::biquad::plugin,          PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::tremolo::plugin,         PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::phaser_mono::plugin,     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::chorus_mono::plugin,     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::flanger_mono::plugin,    PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::gx_feedback::plugin,     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&tonestack.plugin,                    PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&cabinet.plugin,                      PLUGIN_POS_RACK, PGN_GUI);
    // stereo
    pl.add(&gx_effects::chorus::plugin,          PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::flanger::plugin,         PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::phaser::plugin,          PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::stereodelay::plugin,     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::stereoecho::plugin,      PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::moog::plugin,            PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_amps::gx_ampmodul::plugin,        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::tonecontroll::plugin,    PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&convolver.plugin,                    PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&gx_effects::stereoverb::plugin,      PLUGIN_POS_RACK, PGN_GUI);

    // loaded from shared libs
    pl.load_from_path(plugin_dir, PLUGIN_POS_RACK);

    // selector objects to switch "alternative" modules
    engine.add_selector(ampstack);
    engine.add_selector(crybaby);
    engine.add_selector(tonestack);

#ifndef NDEBUG
    pl.printlist();
#endif
}

void register_faust_parameters() {
    gx_effects::balance1::register_params(ParamReg(0));
}
