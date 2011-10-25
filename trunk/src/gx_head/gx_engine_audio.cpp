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
#include <iostream>       // NOLINT

#include "gx_faust_plugins.h"
#include "../plugins/pluginlib.h"

namespace gx_engine {

AudioVariables audio;

/****************************************************************
 ** class ProcessingChainBase
 */

ProcessingChainBase::ProcessingChainBase():
    sync_sem(),
    to_release(),
    ramp_value(0),
    ramp_mode(ramp_mode_down_dead),
    stopped(true),
    steps_up(),
    steps_up_dead(),
    steps_down(),
    latch(false),
    modules(),
    next_commit_needs_ramp() {
    sem_init(&sync_sem, 0, 0);
}

void ProcessingChainBase::set_samplerate(int samplerate) {
    //steps_down = (256 * samplerate) / 48000;
    //steps_up = 8 * steps_down;
    steps_down = (64 * samplerate) / 48000;
    steps_up = 4 * steps_down;
    steps_up_dead = 0;
}

void ProcessingChainBase::start_ramp_up() {
    if (!stopped) {
	set_ramp_value(0);
	set_ramp_mode(ramp_mode_up_dead);
    }
}

void ProcessingChainBase::start_ramp_down() {
    RampMode rm = get_ramp_mode();
    if (rm == ramp_mode_down_dead or rm == ramp_mode_down) {
	return;
    }
    int rv = min(steps_down,get_ramp_value());
    if (rv == 0) {
	set_ramp_mode(ramp_mode_down_dead);
    } else {
	set_ramp_value(rv);
	set_ramp_mode(ramp_mode_down);
    }
}

void ProcessingChainBase::try_set_ramp_mode(RampMode oldmode, RampMode newmode, int oldrv, int newrv) {
    if (oldmode != newmode) {
	if (!g_atomic_int_compare_and_exchange(&ramp_mode, oldmode, newmode)) {
	    return;
	}
    }
    if (oldrv != newrv) {
	if (!g_atomic_int_compare_and_exchange(&ramp_value, oldrv, newrv)) {
	    return;
	}
    }
}

bool lists_equal(const list<Plugin*>& p1, const list<Plugin*>& p2, bool *need_ramp)
{
    list<Plugin*>::const_iterator i1 = p1.begin();
    list<Plugin*>::const_iterator i2 = p2.begin(); 
    bool ret = true;
    bool nr = false;
    while (true) {
	if (i1 == p1.end()) {
	    if (i2 != p2.end()) {
		ret = false;
		nr = true;
	    }
	    break;
	}
	if (i2 == p2.end()) {
	    ret = false;
	    nr = true;
	    break;
	}
	if (*i1 != *i2) {
	    ret = false;
	    while ((*i1)->pdef->flags & PGN_SNOOP) {
		++i1;
		if (i1 == p1.end()) {
		    break;
		}
	    }
	    while ((*i2)->pdef->flags & PGN_SNOOP) {
		++i2;
		if (i2 == p2.end()) {
		    break;
		}
	    }
	    if (*i1 != *i2) {
		nr = true;
		break;
	    }
	}
	++i1;
	++i2;
    }
    if (ret) {
	nr = false;
    }
    *need_ramp = nr;
    return ret;
}

bool ProcessingChainBase::set_plugin_list(const list<Plugin*> &p) {
    if (lists_equal(p, modules, &next_commit_needs_ramp)) {
	return false;
    }
    wait_latch();
    if (check_release()) {
	release();
    }
    typedef set<const char*, stringcomp> pchar_set;
    pchar_set new_ids;
    for (list<Plugin*>::const_iterator i = p.begin(); i != p.end(); ++i) {
	new_ids.insert((*i)->pdef->id);
    }
    for (list<Plugin*>::const_iterator i = modules.begin(); i != modules.end(); ++i) {
	if (!(*i)->pdef->activate_plugin) {
	    continue;
	}
	pchar_set::iterator r = new_ids.find((*i)->pdef->id);
	if (r == new_ids.end()) {
	    to_release.push_back(*i);
	}
    }
    modules = p;
    return true;
}

void ProcessingChainBase::clear_module_states() {
    for (list<Plugin*>::const_iterator p = modules.begin(); p != modules.end(); ++p) {
	PluginDef* pd = (*p)->pdef;
	if (pd->activate_plugin) {
	    pd->activate_plugin(true, pd);
	} else if (pd->clear_state) {
	    pd->clear_state(pd);
	}
    }
}

void ProcessingChainBase::release() {
    if (latch) {
	wait_rt_finished();
    }
    for (list<Plugin*>::const_iterator p = to_release.begin(); p != to_release.end(); ++p) {
	(*p)->pdef->activate_plugin(false, (*p)->pdef);
    }
    to_release.clear();
}

/****************************************************************
 ** MonoModuleChain, StereoModuleChain
 */

void MonoModuleChain::process(int count, float *input, float *output) {
    RampMode rm = get_ramp_mode();
    if (rm == ramp_mode_down_dead) {
	memset(output, 0, count*sizeof(float));
	return;
    }
    memcpy(output, input, count*sizeof(float));
    for (monochain_data *p = get_rt_chain(); p->func; ++p) {
	p->func(count, output, output, p->plugin);
    }
    if (rm == ramp_mode_off) {
	return;
    }
    int rv = get_ramp_value();
    int rv1 = rv;
    RampMode rm1 = get_ramp_mode();
    if (rm != rm1) {
	// ramp_mode has changed while processing
	if (rm1 != ramp_mode_up && rm1 != ramp_mode_down) {
	    return;
	}
	rv1 = rv = get_ramp_value();
	// assume ramp_mode doesn't change too fast
	rm = rm1;
    }
    int i = 0;
    if (rm1 == ramp_mode_up_dead) {
	for ( ; i < count; ++i) {
	    if (++rv1 > steps_up_dead) {
		rm1 = ramp_mode_up;
		rv1 = 0;
		break;
	    }
	    output[i] = 0.0;
	}
    }
    if (rm1 == ramp_mode_up) {
	for ( ; i < count; ++i) {
	    if (++rv1 >= steps_up) {
		rm1 = ramp_mode_off;
		break;
	    }
	    output[i] = (output[i] * rv1) / steps_up;
	}
    }
    else if (rm1 == ramp_mode_down) {
	for (i = 0; i < count; ++i) {
	    if (--rv1 == 0) {
		rm1 = ramp_mode_down_dead;
		break;
	    }
	    output[i] = (output[i] * rv1) / steps_down;
	}
	for ( ; i < count; ++i) {
	    output[i] = 0.0;
	}
    }
    try_set_ramp_mode(rm, rm1, rv, rv1);
}

void StereoModuleChain::process(int count, float *input, float *output1, float *output2) {
    // run stereo rack
    RampMode rm = get_ramp_mode();
    if (rm == ramp_mode_down_dead) {
	memset(output1, 0, count*sizeof(float));
	memset(output2, 0, count*sizeof(float));
	return;
    }
    memcpy(output1, input, count*sizeof(float));
    memcpy(output2, input, count*sizeof(float));
    for (stereochain_data *p = get_rt_chain(); p->func; ++p) {
	(p->func)(count, output1, output2, output1, output2, p->plugin);
    }
    if (rm == ramp_mode_off) {
	return;
    }
    int rv = get_ramp_value();
    int rv1 = rv;
    RampMode rm1 = get_ramp_mode();
    if (rm != rm1) {
	// ramp_mode has changed while processing
	if (rm1 != ramp_mode_up && rm1 != ramp_mode_down) {
	    return;
	}
	rv1 = rv = get_ramp_value();
	// assume ramp_mode doesn't change too fast
	rm = rm1;
    }
    int i = 0;
    if (rm1 == ramp_mode_up_dead) {
	for ( ; i < count; ++i) {
	    if (++rv1 > steps_up_dead) {
		rm1 = ramp_mode_up;
		rv1 = 0;
		break;
	    }
	    output1[i] = 0.0;
	    output2[i] = 0.0;
	}
    }
    if (rm1 == ramp_mode_up) {
	for ( ; i < count; ++i) {
	    if (++rv1 >= steps_up) {
		rm1 = ramp_mode_off;
		break;
	    }
	    output1[i] = (output1[i] * rv1) / steps_up;
	    output2[i] = (output2[i] * rv1) / steps_up;
	}
    }
    else if (rm1 == ramp_mode_down) {
	for (i = 0; i < count; ++i) {
	    if (--rv1 == 0) {
		rm1 = ramp_mode_down_dead;
		break;
	    }
	    output1[i] = (output1[i] * rv1) / steps_down;
	    output2[i] = (output2[i] * rv1) / steps_down;
	}
	for ( ; i < count; ++i) {
	    output1[i] = 0.0;
	    output2[i] = 0.0;
	}
    }
    try_set_ramp_mode(rm, rm1, rv, rv1);
}

/****************************************************************
 ** ModuleSelector
 */

ModuleSelectorFromList::ModuleSelectorFromList(
    ModuleSequencer& seq_, const char* id_, const char* name_,
    PluginDef *plugins[], const char* select_id_,
    const char* select_name_, const char** groups_, int flags_)
    : ModuleSelector(seq_),
      PluginDef(),
      selector(0),
      select_id(select_id_),
      select_name(select_name_),
      current_plugin(0),
      modules(),
      size(),
      plugin() {
    version = PLUGINDEF_VERSION;
    register_params = static_register;
    modules = plugins;
    PluginDef **p = plugins;
    for (size = 0; *p; ++p, ++size);
    id = id_;
    name = name_;
    groups = groups_;
    flags = flags_;
    plugin = this;
}

int ModuleSelectorFromList::register_parameter(const ParamReg &param) {
    value_pair *p = new value_pair[size+1];
    for (unsigned int i = 0; i < size; ++i) {
	p[i].value_id = modules[i]->id;
	p[i].value_label = gettext(modules[i]->name);
    }
    p[size].value_id = 0;
    p[size].value_label = 0;
    param.registerUEnumVar(select_id, select_name, "S", "", p, &selector, 0, false);
    return 0;
}

int ModuleSelectorFromList::static_register(const ParamReg &param) {
    return static_cast<ModuleSelectorFromList*>(param.plugin)
	->register_parameter(param);
}

void ModuleSelectorFromList::set_selector(unsigned int n) {
    if (n >= size) {
	n = size-1;
    }
    selector = n;
    seq.set_rack_changed();
}

void ModuleSelectorFromList::set_module() {
    if (current_plugin) {
	current_plugin->on_off = false;
    }
    if (plugin.on_off) {
	const char* id;
	id = modules[selector]->id;
	current_plugin = seq.pluginlist.lookup_plugin(id);
	current_plugin->on_off = true;
	current_plugin->effect_post_pre = plugin.effect_post_pre;
    } else {
	current_plugin = 0;
    }
}

/****************************************************************
 ** ModuleSequencer
 */

ModuleSequencer::ModuleSequencer():
    selectors(),
    rack_changed(true),
    audio_mode(PGN_MODE_NORMAL),
    policy(),
    priority(),
    ui(),
    pluginlist(ui,*this),
    mono_chain(),
    stereo_chain(),
    stateflags_mutex(),
    stateflags(SF_INITIALIZING),
    buffersize_change(),
    samplerate_change() {
}

void ModuleSequencer::init(unsigned int samplerate, unsigned int buffersize,
			   int policy_, int priority_) {
    set_buffersize(buffersize);
    set_samplerate(samplerate);
    policy = policy_;
    priority = priority_;
}

ModuleSequencer::~ModuleSequencer() {
}

void ModuleSequencer::set_samplerate(unsigned int samplerate) {
    pluginlist.set_samplerate(samplerate);
    mono_chain.set_samplerate(samplerate);
    stereo_chain.set_samplerate(samplerate);
    samplerate_change(samplerate);
}

void ModuleSequencer::set_buffersize(unsigned int buffersize) {
    buffersize_change(buffersize);
}

bool ModuleSequencer::prepare_module_lists() {
    for (list<ModuleSelector*>::iterator i = selectors.begin(); i != selectors.end(); ++i) {
	(*i)->set_module();
    }
    list<Plugin*> modules;
    rack_changed = false;
    pluginlist.ordered_mono_list(modules, audio_mode);
    bool ret_mono = mono_chain.set_plugin_list(modules);
    pluginlist.ordered_stereo_list(modules, audio_mode);
    bool ret_stereo = stereo_chain.set_plugin_list(modules);
    if (ret_mono || ret_stereo) {
	mono_chain.print();
	stereo_chain.print();
    }
    return ret_mono || ret_stereo;
}

void ModuleSequencer::commit_module_lists() {
    bool already_down = (mono_chain.get_ramp_mode() == ProcessingChainBase::ramp_mode_down_dead);
    bool monoramp = mono_chain.next_commit_needs_ramp && !already_down;
    if (monoramp) {
	mono_chain.start_ramp_down();
	mono_chain.wait_ramp_down_finished();
    }
    mono_chain.commit(mono_chain.next_commit_needs_ramp);
    already_down =  (stereo_chain.get_ramp_mode() == ProcessingChainBase::ramp_mode_down_dead);
    bool stereoramp = stereo_chain.next_commit_needs_ramp && !already_down;
    if (stereoramp) {
	stereo_chain.start_ramp_down();
	stereo_chain.wait_ramp_down_finished();
    }
    stereo_chain.commit(stereo_chain.next_commit_needs_ramp);
    if (monoramp) {
	mono_chain.start_ramp_up();
	mono_chain.next_commit_needs_ramp = false;
    }
    if (stereoramp) {
	stereo_chain.start_ramp_up();
	stereo_chain.next_commit_needs_ramp = false;
    }
}

void ModuleSequencer::add_selector(ModuleSelector& sel) {
    selectors.push_back(&sel);
}

void ModuleSequencer::set_stateflag(StateFlag flag) {
    if (stateflags & flag) {
	return;
    }
    boost::mutex::scoped_lock lock(stateflags_mutex);
    mono_chain.set_stopped(true);
    stereo_chain.set_stopped(true);
    if (!stateflags) {
	set_down_dead();
    }
    stateflags |= flag;
}

void ModuleSequencer::clear_stateflag(StateFlag flag) {
    if (!(stateflags & flag)) {
	return;
    }
    boost::mutex::scoped_lock lock(stateflags_mutex);
    stateflags &= ~flag;
    if (!stateflags) {
	mono_chain.set_stopped(false);
	stereo_chain.set_stopped(false);
	start_ramp_up();
    }
}

void ModuleSequencer::set_state(GxEngineState state) {
    int newmode = PGN_MODE_MUTE;
    switch( state ) {
    case kEngineOn:     newmode = PGN_MODE_NORMAL; break;
    case kEngineBypass: newmode = PGN_MODE_BYPASS; break;
    case kEngineOff:    newmode = PGN_MODE_MUTE;   break;
    }
    if (audio_mode == newmode) {
	return;
    }
    audio_mode = newmode;
    set_rack_changed();
}

GxEngineState ModuleSequencer::get_state() {
    if (audio_mode & PGN_MODE_NORMAL) {
	return kEngineOn;
    } else if (audio_mode & PGN_MODE_BYPASS) {
	return kEngineBypass;
    } else if (audio_mode & PGN_MODE_MUTE) {
	return kEngineOff;
    } else {
	assert(false);
	return kEngineOff;
    }
}

void ModuleSequencer::registerParameter(gx_gui::ParameterGroups& groups)
{
    pluginlist.registerParameter(groups);
}

void ModuleSequencer::get_sched_priority(int &policy_, int &priority_, int prio_dim) { 
    policy_ = policy;
    priority_ = priority;
    if (prio_dim) {
	return;
    }
    int min, max;
    min = sched_get_priority_min(policy);
    max = sched_get_priority_max(policy);
    priority_ = priority - prio_dim;
    if (priority_ > max) {
	priority_ = max;
    }
    if (priority_ < min) {
	priority_ = min;
    }
}


/****************************************************************
 ** class GxEngine
 */

static PluginDef *builtin_crybaby_plugins[] = {
    &gx_effects::crybaby::plugin,
    &gx_effects::autowah::plugin,
    0
};

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

GxEngine::GxEngine(const string& plugin_dir, gx_gui::ParameterGroups& groups)
    : ModuleSequencer(),
      resamp(),
      // ModuleSelector's
      crybaby(
	  *this, "crybaby", N_("Crybaby"), builtin_crybaby_plugins,
	  "crybaby.autowah", _("select"), 0, PGN_POST_PRE),
      tonestack(
	  *this, "amp.tonestack", N_("Tonestack"),
	  builtin_tonestack_plugins, "amp.tonestack.select",
	  _("select"), 0, PGN_POST_PRE),
      ampstack(
	  *this, "ampstack", "?Tube", builtin_amp_plugins,
	  "tube.select", _("select"), ampstack_groups),
      // internal audio modules
      noisegate(),
      monomute(),
      stereomute(),
      midiaudiobuffer(),
      tuner(midiaudiobuffer.plugin, *this),
      maxlevel(),
      oscilloscope(&ui, *this),
      convolver(*this),
      cabinet(*this, resamp),
      contrast(*this, resamp) {

    load_static_plugins();

    // loaded from shared libs
    pluginlist.load_from_path(plugin_dir, PLUGIN_POS_RACK);

    // selector objects to switch "alternative" modules
    add_selector(ampstack);
    add_selector(crybaby);
    add_selector(tonestack);
    add_selector(tuner);

    registerParameter(groups);

#ifndef NDEBUG
    pluginlist.printlist();
#endif
}

GxEngine::~GxEngine() {
}

void GxEngine::load_static_plugins() {
    PluginList& pl = pluginlist; // just a shortcut

    // * mono amp input position *

    pl.add(&tuner.plugin,                        PLUGIN_POS_START, PGN_PRE|PGN_MODE_NORMAL|PGN_MODE_BYPASS|PGN_MODE_MUTE);
    pl.add(&midiaudiobuffer.plugin,              PLUGIN_POS_START, PGN_GUI|PGN_PRE|PGN_MODE_NORMAL|PGN_MODE_BYPASS);
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
    pl.add(&monomute,                            PLUGIN_POS_END, PGN_POST|PGN_MODE_MUTE);

    // * amp insert position (stereo amp input) *

    pl.add(&gx_effects::gxfeed::plugin,          PLUGIN_POS_START);

    // rack stereo modules inserted here

    pl.add(&gx_effects::gx_outputlevel::plugin,  PLUGIN_POS_END);
    pl.add(&balance::plugin,                     PLUGIN_POS_END, PGN_MODE_BYPASS);
    pl.add(&stereomute,                          PLUGIN_POS_END, PGN_MODE_MUTE);
    pl.add(&maxlevel,                            PLUGIN_POS_END, PGN_MODE_NORMAL|PGN_MODE_BYPASS);

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
    pl.add(&pluginlib::zita_rev1::plugin,        PLUGIN_POS_RACK);
}

} // end namespace gx_engine
