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

static int load_crybaby_ui(const UiBuilder& builder, int format) {
    if (format & UI_FORM_GLADE) {
	builder.load_glade_file("crybaby_ui.glade");
	return 0;
    }
    if (format & UI_FORM_STACK) {
	builder.openHorizontalhideBox("");
	builder.create_master_slider("crybaby.level", _("  level  "));
	builder.closeBox();
	builder.openHorizontalBox("");
	{
	    builder.insertSpacer();
	    builder.create_selector("crybaby.autowah", _("Mode"));
	    builder.insertSpacer();
	    builder.insertSpacer();
	    builder.openHorizontalTableBox("");
	    {
		builder.create_small_rackknobr("crybaby.wah", _("  wah   "));
		builder.create_small_rackknob("crybaby.level", _("  level  "));
		builder.create_small_rackknob("crybaby.wet_dry", _("  dry/wet  "));
	    }
	    builder.closeBox();
	    builder.insertSpacer();
	}
	builder.closeBox();
	return 0;
    }
    return -1;
}

static plugindef_creator builtin_wah_plugins[] = {
    gx_effects::colwah::plugin,
    gx_effects::dallaswah::plugin,
    gx_effects::foxwah::plugin,
    gx_effects::jenwah::plugin,
    gx_effects::maestrowah::plugin,
    gx_effects::selwah::plugin,
    gx_effects::voxwah::plugin,
    gx_effects::rolwah::plugin,
    gx_effects::colbwah::plugin,
    gx_effects::jenbasswah::plugin,
   0
};

static int load_wah_ui(const UiBuilder& builder, int format) {
    if (format & UI_FORM_GLADE) {
	builder.load_glade_file("wah_ui.glade");
	return 0;
    }
    if (format & UI_FORM_STACK) {
	builder.openHorizontalhideBox("");
	builder.create_master_slider("wah.Wah", _("Wah"));
	builder.closeBox();
	builder.openHorizontalBox("");
	{
		builder.openVerticalBox("");
		{
	    builder.insertSpacer();
	    builder.create_selector("wah.select", _("Model"));
	    builder.insertSpacer();
		builder.create_selector("wah.mode", _("Mode"));
	    builder.insertSpacer();
	    }
	    builder.closeBox();
	    builder.openHorizontalTableBox("");
	    {
		builder.create_small_rackknobr("wah.Wah", _("Wah"));
		builder.create_small_rackknob("wah.freq", _("Alien Freq"));
		builder.create_small_rackknob("wah.wet_dry", _("  dry/wet  "));
	    }
	    builder.closeBox();
	    builder.insertSpacer();
	}
	builder.closeBox();
	return 0;
    }
    return -1;
}

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

static int load_tonestack_ui(const UiBuilder& builder, int format) {
    if (format & UI_FORM_GLADE) {
	builder.load_glade_file("amp.tonestack_ui.glade");
	return 0;
    }
    if (format & UI_FORM_STACK) {
	builder.openHorizontalhideBox("");
	builder.create_selector("amp.tonestack.select", 0);
	builder.closeBox();
	builder.openVerticalBox("");
	{
	    builder.openHorizontalBox("");
	    {
		builder.create_selector("amp.tonestack.select", 0);
		builder.create_small_rackknobr("amp.tonestack.Bass", _("bass"));
		builder.create_small_rackknobr("amp.tonestack.Middle", _("middle"));
		builder.create_small_rackknobr("amp.tonestack.Treble", _("treble"));
	    }
	    builder.closeBox();
	}
	builder.closeBox();
	return 0;
    }
    return -1;
}


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

GxEngine::GxEngine(const string& plugin_dir, ParameterGroups& groups, const gx_system::CmdlineOptions& options)
    : ModuleSequencer(),
      resamp(),
      plugin_changed(),
      ladspaloader(options, get_param()),
      controller_map(),
      // ModuleSelector's
      crybaby(
	  *this, "crybaby", N_("Crybaby"), N_("Guitar Effects"), builtin_crybaby_plugins,
	  "crybaby.autowah", _("select"), load_crybaby_ui, 0, PGN_POST_PRE),
      wah(
	  *this, "wah", N_("Wah"), N_("Guitar Effects"), builtin_wah_plugins,
	  "wah.select", _("select"), load_wah_ui, 0, PGN_POST_PRE),
      tonestack(
	  *this, "amp.tonestack", N_("Tonestack"), N_("Tone Control"),
	  builtin_tonestack_plugins, "amp.tonestack.select",
	  _("select"), load_tonestack_ui, 0, PGN_POST_PRE),
      ampstack(
	  *this, "ampstack", _("Amp"), "", builtin_amp_plugins,
	  "tube.select", _("select"), 0, ampstack_groups),
      // internal audio modules
      noisegate(),
      monomute(),
      stereomute(),
      tuner(*this),
      drumout(),
      directout(*this, sigc::mem_fun(mono_chain, &StereoModuleChain::sync)),
      maxlevel(),
      oscilloscope(*this),
      mono_convolver(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync)),
      stereo_convolver(*this, sigc::mem_fun(stereo_chain, &StereoModuleChain::sync)),
      cabinet(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync), resamp),
      cabinet_st(*this, sigc::mem_fun(stereo_chain, &StereoModuleChain::sync), resamp),
      preamp(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync), resamp),
      preamp_st(*this, sigc::mem_fun(stereo_chain, &StereoModuleChain::sync), resamp),
      contrast(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync), resamp),
      loop(get_param(), sigc::mem_fun(mono_chain,&MonoModuleChain::sync),options.get_loop_dir()),
      record(*this, 1), record_st(*this, 2),
      dseq(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync)),
      detune(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync)) {
    set_overload_interval(options.get_sporadic_overload());
    if (!options.get_convolver_watchdog()) {
	ov_disabled |= ov_Convolver;
    }
    if (!options.get_xrun_watchdog()) {
	ov_disabled |= ov_XRun;
    }
    if (options.get_mute()) {
	set_state(kEngineOff);;
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
    add_selector(wah);
    add_selector(tonestack);
    add_selector(tuner);

    registerParameter(groups);

#ifndef NDEBUG
    pluginlist.printlist();
#endif
}

GxEngine::~GxEngine() {
    pluginlist.cleanup();
}

void GxEngine::load_static_plugins() {
    PluginList& pl = pluginlist; // just a shortcut

    // * mono amp input position *

    pl.add(&tuner.plugin,                         PLUGIN_POS_START, PGN_PRE|PGN_MODE_NORMAL|PGN_MODE_BYPASS|PGN_MODE_MUTE);
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
    pl.add(&drumout.outputdrum,                   PLUGIN_POS_END, PGN_MODE_NORMAL);
    pl.add(&directout,                            PLUGIN_POS_END, PGN_MODE_NORMAL);
    pl.add(&maxlevel,                             PLUGIN_POS_END, PGN_MODE_NORMAL|PGN_MODE_BYPASS);

    // * fx amp output *

    // dynamic rack modules
    // builtin
    pl.add(builtin_crybaby_plugins,               PLUGIN_POS_RACK, PGN_ALTERNATIVE);
    pl.add(builtin_wah_plugins,                   PLUGIN_POS_RACK, PGN_ALTERNATIVE);
    pl.add(builtin_tonestack_plugins,             PLUGIN_POS_RACK, PGN_ALTERNATIVE);

    // mono
    pl.add(gx_effects::gain::plugin(),            PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::low_high_pass::plugin(),   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::highbooster::plugin(),     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::selecteq::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&crybaby.plugin,                       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&wah.plugin,                           PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&loop.plugin,                          PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&record.plugin,                        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&detune.plugin,                        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&dseq.plugin,                          PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::gx_distortion::plugin(),   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::bitdowner::plugin(),       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::thick_distortion::plugin(), PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::ts9sim::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::aclipper::plugin(),         PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::mxrdist::plugin(),          PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::bossds1::plugin(),          PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::bmp::plugin(),              PLUGIN_POS_RACK, PGN_GUI);
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
    pl.add(gx_effects::ring_modulator::plugin(),  PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::graphiceq::plugin(),       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::vibe::plugin_mono(),        PLUGIN_POS_RACK);
    pl.add(pluginlib::mbc::plugin(),              PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::mbd::plugin(),              PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::mbe::plugin(),              PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::mbdel::plugin(),            PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::mbclipper::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::bassboom::plugin(),         PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::mbchor::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::jcm800pre::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::gcb_95::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
	pl.add(gx_effects::duck_delay::plugin(),      PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::reversedelay::plugin(),     PLUGIN_POS_RACK, PGN_GUI);
	pl.add(gx_effects::baxandall::plugin(),       PLUGIN_POS_RACK, PGN_GUI);
	pl.add(gx_effects::distortion2::plugin(),     PLUGIN_POS_RACK, PGN_GUI);
	pl.add(gx_effects::fuzzface::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
	pl.add(gx_effects::trbuff::plugin(),          PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::fuzzfacefm::plugin(),       PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::fuzzfacerm::plugin(),       PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::hornet::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::susta::plugin(),            PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::hfb::plugin(),              PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::muff::plugin(),             PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::scream::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::lpbboost::plugin(),         PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::foxeylady::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::hogsfoot::plugin(),         PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::cstb::plugin(),             PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::coverd::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::rangem::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::ruin::plugin(),             PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::ffreak::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::fumaster::plugin(),         PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::fuzzdrive::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::rolandwah::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::astrofuzz::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::buffb::plugin(),            PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::eldist::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::mole::plugin(),             PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::buzz::plugin(),             PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::bfuzz::plugin(),            PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::axface::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::metronome::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::vumeter::plugin(),          PLUGIN_POS_RACK, PGN_GUI);
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
    pl.add(&record_st.plugin,                     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::stereoverb::plugin(),      PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::zita_rev1::plugin(),        PLUGIN_POS_RACK);
    pl.add(pluginlib::vibe::plugin_stereo(),      PLUGIN_POS_RACK);
    pl.add(pluginlib::mbcs::plugin(),             PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::dattorros_progenitor::plugin(),PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::panoram_enhancer::plugin(),PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::bass_enhancer::plugin(),   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::ring_modulator_st::plugin(),PLUGIN_POS_RACK, PGN_GUI);
	pl.add(gx_effects::duck_delay_st::plugin(),   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&cabinet_st.plugin,                    PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&preamp_st.plugin,                     PLUGIN_POS_RACK, PGN_GUI);
	pl.add(pluginlib::vumeter_st::plugin(),       PLUGIN_POS_RACK, PGN_GUI);
}

static LadspaLoader::pluginarray::iterator find_plugin(LadspaLoader::pluginarray& ml, plugdesc *pl) {
    for (LadspaLoader::pluginarray::iterator i = ml.begin(); i != ml.end(); ++i) {
	if (pl->quirks & is_lv2) {
	    if ((*i)->path == pl->path) {
		return i;
	    }
	} else {
	    if ((*i)->UniqueID == pl->UniqueID) {
		return i;
	    }
	}
    }
    return ml.end();
}

void GxEngine::ladspaloader_update_plugins() {
    // load plugindesc list
    LadspaLoader::pluginarray ml;
    ladspaloader.load(ml);
    // look for removed and changed plugins
    std::vector<PluginChange> pv;
    for (LadspaLoader::pluginarray::iterator i = ladspaloader.begin(); i != ladspaloader.end(); ++i) {
	Plugin *pl = pluginlist.lookup_plugin((*i)->id_str);
	LadspaLoader::pluginarray::iterator j = find_plugin(ml, *i);
	if (j == ml.end()) {
	    pl->set_on_off(false);
	    pv.push_back(PluginChange(pl, PluginChange::remove));
	} else {
	    ladspaloader.update_instance(pl->get_pdef(), *j);
	    if (pl->get_pdef()->register_params) {
		pmap.set_replace_mode(true);
		gx_engine::ParamRegImpl preg(&pmap);
        // FIXME we need to register on_off parameters new when ui is changed
        bool state = pl->get_on_off();
        pluginlist.rescueParameter(pl, pmap);
        pl->set_on_off(state);
		preg.plugin = pl->get_pdef();
		pl->get_pdef()->register_params(preg);
		pmap.set_replace_mode(false);
	    }
	    pv.push_back(
		PluginChange(
		    pl,
		    ((*j)->category == (*i)->category ? PluginChange::update : PluginChange::update_category)));
	}
    }

    // update engine for plugins to be removed
    update_module_lists();
    mono_chain.release();
    stereo_chain.release();
    // remove plugins
    for (std::vector<PluginChange>::iterator i = pv.begin(); i != pv.end(); ++i) {
	if (i->status == PluginChange::remove) {
	    plugin_changed(i->pl, PluginChange::remove);
	    pluginlist.unregisterPlugin(i->pl, pmap, get_group_table());
	    pluginlist.delete_module(i->pl);
	} else {
	    plugin_changed(i->pl, i->status);
	}
    }
    // add new plugins (engine)
    for (LadspaLoader::pluginarray::const_iterator i = ml.begin(); i != ml.end(); ++i) {
	if (ladspaloader.find(*i) == ladspaloader.end()) {
	    PluginDef *plugin = ladspaloader.create(*i);
	    if (plugin) {
		Plugin *p = pluginlist.add(plugin);
		pluginlist.registerPlugin(p, get_param(), get_group_table());
		plugin->set_samplerate(get_samplerate(), plugin);
		plugin_changed(p, PluginChange::add);
	    }
	}
    }
    // update ladspaloader with new list
    ladspaloader.set_plugins(ml);
    plugin_changed(0, PluginChange::update);
}

} /* end of gx_engine namespace */
