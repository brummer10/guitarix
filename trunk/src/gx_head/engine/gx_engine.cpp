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

#include "engine.h"
#include "valve.h"

#include "gx_faust_plugins.h"
#include "../plugins/pluginlib.h"

namespace gx_engine {

/****************************************************************
 ** class GxEngine
 */

static plugindef_creator builtin_crybaby_plugins[] = {
    gx_effects::crybaby::plugin,
    gx_effects::autowah::plugin,
    0
};

static plugindef_creator builtin_tonestack_plugins[] = {
    gx_tonestacks::tonestack_default::plugin,
    gx_tonestacks::tonestack_bassman::plugin,
    gx_tonestacks::tonestack_twin::plugin,
    gx_tonestacks::tonestack_princeton::plugin,
    gx_tonestacks::tonestack_jcm800::plugin,
    gx_tonestacks::tonestack_jcm2000::plugin,
    gx_tonestacks::tonestack_mlead::plugin,
    gx_tonestacks::tonestack_m2199::plugin,
    gx_tonestacks::tonestack_ac30::plugin,
    gx_tonestacks::tonestack_soldano::plugin,
    gx_tonestacks::tonestack_mesa::plugin,
    gx_tonestacks::tonestack_jtm45::plugin,
    gx_tonestacks::tonestack_ac15::plugin,
    gx_tonestacks::tonestack_peavey::plugin,
    gx_tonestacks::tonestack_ibanez::plugin,
    gx_tonestacks::tonestack_roland::plugin,
    gx_tonestacks::tonestack_ampeg::plugin,
    gx_tonestacks::tonestack_ampeg_rev::plugin,
    gx_tonestacks::tonestack_sovtek::plugin,
    gx_tonestacks::tonestack_bogner::plugin,
    gx_tonestacks::tonestack_groove::plugin,
    gx_tonestacks::tonestack_crunch::plugin,
    gx_tonestacks::tonestack_fender_blues::plugin,
    gx_tonestacks::tonestack_fender_default::plugin,
    gx_tonestacks::tonestack_fender_deville::plugin,
    gx_tonestacks::tonestack_gibsen::plugin,
    gx_tonestacks::tonestack_engl::plugin,
    0
};

static plugindef_creator builtin_amp_plugins[] = {
    gx_amps::gxamp::plugin,
    gx_amps::gxamp3::plugin,
    gx_amps::gxamp14::plugin,
    gx_amps::gxamp10::plugin,
    gx_amps::gxamp18::plugin,

    gx_amps::gxamp2::plugin,

    gx_amps::gxamp9::plugin,
    gx_amps::gxamp11::plugin,
    gx_amps::gxamp17::plugin,
    gx_amps::gxamp13::plugin,

    gx_amps::gxamp5::plugin,
    gx_amps::gxamp4::plugin,
    gx_amps::gxamp15::plugin,
    gx_amps::gxamp12::plugin,

    gx_amps::gxamp7::plugin,
    gx_amps::gxamp8::plugin,
    gx_amps::gxamp16::plugin,
    gx_amps::gxamp6::plugin,

    gx_amps::gxnoamp::plugin, // keep last position (UI switches controls)

    0
};

static const char* ampstack_groups[] = {
    ".amp2.stage1",  N_("Tube1"),
    ".amp2.stage2",  N_("Tube2"),
    ".tube",         N_("Tube 1"),
    ".gxdistortion", N_("Multi Band Distortion"),
    0
};

GxEngine::GxEngine(const string& plugin_dir, ParamMap& param, ParameterGroups& groups, const gx_system::CmdlineOptions& options)
    : ModuleSequencer(),
      resamp(),
      controller_map(),
      // ModuleSelector's
      crybaby(
	  *this, ui, "crybaby", N_("Crybaby"), N_("Guitar Effects"), builtin_crybaby_plugins,
	  "crybaby.autowah", _("select"), 0, PGN_POST_PRE),
      tonestack(
	  *this, ui, "amp.tonestack", N_("Tonestack"), N_("Tone control"),
	  builtin_tonestack_plugins, "amp.tonestack.select",
	  _("select"), 0, PGN_POST_PRE),
      ampstack(
	  *this, ui, "ampstack", _("Amp"), "", builtin_amp_plugins,
	  "tube.select", _("select"), ampstack_groups),
      // internal audio modules
      noisegate(),
      monomute(),
      stereomute(),
      tuner(*this),
      midiaudiobuffer(tuner),
      maxlevel(),
      oscilloscope(&ui, *this),
      mono_convolver(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync),
		     param, options.get_IR_pathlist(), options.get_sys_IR_dir()),
      stereo_convolver(*this, sigc::mem_fun(stereo_chain, &StereoModuleChain::sync),
		       param, options.get_IR_pathlist(), options.get_sys_IR_dir()),
      cabinet(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync), resamp),
      preamp(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync), resamp),
      contrast(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync), resamp),
      ladspaloader(options) {
    set_overload_interval(options.get_sporadic_overload());
    if (!options.get_convolver_watchdog()) {
	ov_disabled |= ov_Convolver;
    }
    if (!options.get_xrun_watchdog()) {
	ov_disabled |= ov_XRun;
    }
#ifdef USE_MIDI_OUT
    tuner.set_dep_module(&midiaudiobuffer.plugin);
#endif

    load_static_plugins();
    // loaded from shared libs
    if (!plugin_dir.empty()) {
	pluginlist.load_from_path(plugin_dir, PLUGIN_POS_RACK);
    }

    for (unsigned int i = 0; i < ladspaloader.size(); ++i) {
	PluginDef *p = ladspaloader.create(i);
	if (p) {
	    pluginlist.add(p);
	}
    }

    // selector objects to switch "alternative" modules
    add_selector(ampstack);
    add_selector(crybaby);
    add_selector(tonestack);
    add_selector(tuner);

    registerParameter(param, groups);

#ifndef NDEBUG
    pluginlist.printlist();
#endif
}

GxEngine::~GxEngine() {
}

void GxEngine::load_static_plugins() {
    PluginList& pl = pluginlist; // just a shortcut

    // * mono amp input position *

    pl.add(&tuner.plugin,                         PLUGIN_POS_START, PGN_PRE|PGN_MODE_NORMAL|PGN_MODE_BYPASS|PGN_MODE_MUTE);
    pl.add(&midiaudiobuffer.plugin,               PLUGIN_POS_START, PGN_GUI|PGN_PRE|PGN_MODE_NORMAL|PGN_MODE_BYPASS);
    pl.add(&noisegate.inputlevel,                 PLUGIN_POS_START, PGN_GUI|PGN_FIXED_GUI|PGN_PRE);
    pl.add(gx_effects::noise_shaper::plugin(),    PLUGIN_POS_START, PGN_GUI|PGN_FIXED_GUI|PGN_PRE);

    // rack pre mono modules inserted here

    pl.add(builtin_amp_plugins,                   PLUGIN_POS_START, PGN_ALTERNATIVE|PGN_POST);
    pl.add(&ampstack.plugin,                      PLUGIN_POS_START, PGN_POST);
    pl.add(gx_effects::softclip::plugin(),        PLUGIN_POS_START, PGN_GUI|PGN_FIXED_GUI|PGN_POST);

    // rack post mono modules inserted here

    pl.add(gx_effects::bassbooster::plugin(),     PLUGIN_POS_END, PGN_GUI|PGN_FIXED_GUI|PGN_POST);
    pl.add(gx_effects::gx_ampout::plugin(),       PLUGIN_POS_END, PGN_GUI|PGN_FIXED_GUI|PGN_POST);
    pl.add(&contrast.plugin,                      PLUGIN_POS_END, PGN_GUI|PGN_FIXED_GUI|PGN_POST);
    pl.add(&noisegate.outputgate,                 PLUGIN_POS_END, PGN_POST);
    pl.add(&monomute,                             PLUGIN_POS_END, PGN_POST|PGN_MODE_MUTE);

    // * amp insert position (stereo amp input) *

    pl.add(gx_effects::gxfeed::plugin(),          PLUGIN_POS_START);

    // rack stereo modules inserted here

    pl.add(gx_effects::gx_outputlevel::plugin(),  PLUGIN_POS_END);
    pl.add(balance::plugin(),                     PLUGIN_POS_END, PGN_MODE_BYPASS);
    pl.add(&stereomute,                           PLUGIN_POS_END, PGN_MODE_MUTE);
    pl.add(&maxlevel,                             PLUGIN_POS_END, PGN_MODE_NORMAL|PGN_MODE_BYPASS);

    // * fx amp output *

    // dynamic rack modules
    // builtin 
    pl.add(builtin_crybaby_plugins,               PLUGIN_POS_RACK, PGN_ALTERNATIVE);
    pl.add(builtin_tonestack_plugins,             PLUGIN_POS_RACK, PGN_ALTERNATIVE);

    // mono
    pl.add(gx_effects::low_high_pass::plugin(),   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::highbooster::plugin(),     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::selecteq::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&crybaby.plugin,                       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::gx_distortion::plugin(),   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::ts9sim::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::impulseresponse::plugin(), PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::compressor::plugin(),      PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::expander::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::overdrive::plugin(),       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::echo::plugin(),            PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::delay::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&mono_convolver.plugin,                PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::freeverb::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&oscilloscope.plugin,                  PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::biquad::plugin(),          PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::tremolo::plugin(),         PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::phaser_mono::plugin(),     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::chorus_mono::plugin(),     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::flanger_mono::plugin(),    PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::flanger_gx::plugin(),       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::gx_feedback::plugin(),     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::peak_eq::plugin(),         PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::digital_delay::plugin(),   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&tonestack.plugin,                     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&cabinet.plugin,                       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&preamp.plugin,                        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::abgate::plugin(),           PLUGIN_POS_RACK);
    pl.add(pluginlib::vibe::plugin_mono(),        PLUGIN_POS_RACK);
    pl.add(pluginlib::mbc::plugin(),              PLUGIN_POS_RACK);
    // stereo
    pl.add(gx_effects::chorus::plugin(),          PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::flanger::plugin(),         PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::phaser::plugin(),          PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::stereodelay::plugin(),     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::stereoecho::plugin(),      PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::moog::plugin(),            PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_amps::gx_ampmodul::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::tonecontroll::plugin(),    PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::digital_delay_st::plugin(),PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&stereo_convolver.plugin,              PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::stereoverb::plugin(),      PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::zita_rev1::plugin(),        PLUGIN_POS_RACK);
    pl.add(pluginlib::vibe::plugin_stereo(),      PLUGIN_POS_RACK);
    pl.add(pluginlib::mbcs::plugin(),             PLUGIN_POS_RACK);
}

} /* end of gx_engine namespace */
