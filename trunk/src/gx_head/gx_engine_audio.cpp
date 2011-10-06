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

namespace gx_engine {

AudioVariables audio;

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
    if (midi.fmi && !isMidiOn()) turnOnMidi();
    else if (!midi.fmi && isMidiOn()) turnOffMidi();

    // ------------ main processing routine
    switch (process_type) {

    //---------- run process
    case PROCESS_BUFFERS:
        process_buffers(count, input, output0);
        break;

    // --------- just copy input to outputs
    case JUSTCOPY_BUFFERS:
        feed_tuner(count, input);
       (void)memcpy(output0, input, sizeof(float)*count);
        break;

    // ------- zeroize buffers
    case ZEROIZE_BUFFERS:
    default:
        feed_tuner(count, input);
        if (get_engine().oscilloscope.plugin.on_off) {
	    (void)memset(audio.result, 0, count*sizeof(float));
	}
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
        // mono to stereo splitter
        gx_effects::balance1::compute(count, input1, output0, output1);
	set_maxlevel(count, output0, output1);
        break;

    // ------- zeroize buffers
    case ZEROIZE_BUFFERS:
    default:
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

// gx_head_amp engine
void process_buffers(int count, float* input, float* output0) {
    if (feed_tuner(count, input)) {
        // copy buffer to midi thread
        (void)memcpy(audio.checkfreq, input, sizeof(float)*count);
    }
    get_engine().mono_chain.process(count, input, output0);

}

// gx_head_fx engine
void process_insert_buffers(int count, float* input1, float* output0, float* output1) {
    get_engine().stereo_chain.process(count, input1, output0, output1);
    set_maxlevel(count, output0, output1);
}

/****************************************************************
 ** class ProcessingChainBase
 */

ProcessingChainBase::ProcessingChainBase():
    ramp_value(0),
    ramp_mode(ramp_mode_down_dead),
    latch(false) {
    sem_init(&sync_sem, 0, 0);
}

void ProcessingChainBase::set_samplefreq(int samplefreq) {
    //steps_down = (256 * samplefreq) / 48000;
    //steps_up = 8 * steps_down;
    steps_down = (64 * samplefreq) / 48000;
    steps_up = 4 * steps_down;
    steps_up_dead = 0;
}

void ProcessingChainBase::try_set_ramp_mode(RampMode oldmode, RampMode newmode, int oldrv, int newrv) {
    if (oldmode != newmode) {
	if (!g_atomic_int_compare_and_exchange(
		reinterpret_cast<gint*>(&ramp_mode), oldmode, newmode)) {
	    return;
	}
    }
    if (oldrv != newrv) {
	if (!g_atomic_int_compare_and_exchange(&ramp_value, oldrv, newrv)) {
	    return;
	}
    }
}

bool ProcessingChainBase::set_plugin_list(const list<Plugin*> &p) {
    if (lists_equal(p, modules)) {
	return false;
    }
    wait_latch();
    if (check_release()) {
	release();
    }
    typedef set<const char*, stringcomp> pchar_set;
    pchar_set new_ids;
    for (list<Plugin*>::const_iterator i = p.begin(); i != p.end(); i++) {
	new_ids.insert((*i)->pdef->id);
    }
    for (list<Plugin*>::const_iterator i = modules.begin(); i != modules.end(); i++) {
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
    for (list<Plugin*>::const_iterator p = modules.begin(); p != modules.end(); p++) {
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
    for (list<Plugin*>::const_iterator p = to_release.begin(); p != to_release.end(); p++) {
	(*p)->pdef->activate_plugin(false, (*p)->pdef);
    }
    to_release.clear();
}

/****************************************************************
 ** MonoModuleChain, StereoModuleChain
 */

void MonoModuleChain::print() {
    printlist("Mono", modules);
}

void StereoModuleChain::print() {
    printlist("Stereo", modules);
}

void MonoModuleChain::process(int count, float *input, float *output) {
    RampMode rm = get_ramp_mode();
    if (rm == ramp_mode_down_dead) {
	memset(output, 0, count*sizeof(float));
	return;
    }
    memcpy(output, input, count*sizeof(float));
    for (monochainorder *p = get_rt_chain(); *p; p++) {
	(*p)(count, output, output);
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
	for ( ; i < count; i++) {
	    if (++rv1 > steps_up_dead) {
		rm1 = ramp_mode_up;
		rv1 = 0;
		break;
	    }
	    output[i] = 0.0;
	}
    }
    if (rm1 == ramp_mode_up) {
	for ( ; i < count; i++) {
	    if (++rv1 >= steps_up) {
		rm1 = ramp_mode_off;
		break;
	    }
	    output[i] = (output[i] * rv1) / steps_up;
	}
    }
    else if (rm1 == ramp_mode_down) {
	for (i = 0; i < count; i++) {
	    if (--rv1 == 0) {
		rm1 = ramp_mode_down_dead;
		break;
	    }
	    output[i] = (output[i] * rv1) / steps_down;
	}
	for ( ; i < count; i++) {
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
    for (stereochainorder *p = get_rt_chain(); *p; p++) {
	(*p)(count, output1, output2, output1, output2);
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
	for ( ; i < count; i++) {
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
	for ( ; i < count; i++) {
	    if (++rv1 >= steps_up) {
		rm1 = ramp_mode_off;
		break;
	    }
	    output1[i] = (output1[i] * rv1) / steps_up;
	    output2[i] = (output2[i] * rv1) / steps_up;
	}
    }
    else if (rm1 == ramp_mode_down) {
	for (i = 0; i < count; i++) {
	    if (--rv1 == 0) {
		rm1 = ramp_mode_down_dead;
		break;
	    }
	    output1[i] = (output1[i] * rv1) / steps_down;
	    output2[i] = (output2[i] * rv1) / steps_down;
	}
	for ( ; i < count; i++) {
	    output1[i] = 0.0;
	    output2[i] = 0.0;
	}
    }
    try_set_ramp_mode(rm, rm1, rv, rv1);
}

/****************************************************************
 ** ModuleSelector
 */

ModuleSelector::ModuleSelector(const char* id_, const char* name_,
			       PluginDef *plugins[], const char* select_id_,
			       const char* select_name_, const char** groups_,
			       int flags_)
    : PluginDef(),
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
    for (size = 0; *p; p++, size++);
    id = id_;
    name = name_;
    groups = groups_;
    flags = flags_;
    plugin = this;
}

int ModuleSelector::register_parameter(const ParamReg &param) {
    value_pair *p = new value_pair[size+1];
    for (unsigned int i = 0; i < size; i++) {
	p[i].value_id = modules[i]->id;
	p[i].value_label = gettext(modules[i]->name);
    }
    p[size].value_id = 0;
    p[size].value_label = 0;
    param.registerUEnumVar(select_id, select_name, "S", "", p, &selector, 0, false);
    return 0;
}

int ModuleSelector::static_register(const ParamReg &param) {
    return static_cast<ModuleSelector*>(param.plugin)->register_parameter(param);
}

void ModuleSelector::set_selector(unsigned int n) {
    if (n >= size) {
	n = size-1;
    }
    selector = n; //FIXME: rack_changed??
}

void ModuleSelector::set_module() {
    if (current_plugin) {
	current_plugin->on_off = false;
    }
    if (plugin.on_off) {
	const char* id;
	id = modules[selector]->id;
	current_plugin = get_pluginlist().lookup_plugin(id);
	current_plugin->on_off = true;
	current_plugin->effect_post_pre = plugin.effect_post_pre;
    } else {
	current_plugin = 0;
    }
}

/****************************************************************
 ** ModuleSequencer
 */

ModuleSequencer::ModuleSequencer(PluginList& pl):
    selectors(),
    pluginlist(pl),
    rack_changed(false),
    audio_mode(PGN_MODE_NORMAL),
    mono_chain(),
    stereo_chain() {
}

ModuleSequencer::~ModuleSequencer() {
}

void ModuleSequencer::set_samplefreq(int samplefreq) {
    pluginlist.set_samplerate(samplefreq);
    mono_chain.set_samplefreq(samplefreq);
    stereo_chain.set_samplefreq(samplefreq);
    start_ramp_up();
}

bool ModuleSequencer::prepare_module_lists() {
    for (list<ModuleSelector*>::iterator i = selectors.begin(); i != selectors.end(); i++) {
	(*i)->set_module();
    }
    list<Plugin*> modules;
    rack_changed = false;
    pluginlist.ordered_mono_list(modules, audio_mode);
    bool ret_mono = mono_chain.set_plugin_list(modules);
    mono_chain.print();
    pluginlist.ordered_stereo_list(modules, audio_mode);
    bool ret_stereo = stereo_chain.set_plugin_list(modules);
    stereo_chain.print();
    return ret_mono || ret_stereo;
}

void ModuleSequencer::commit_module_lists(bool ramp) {
    if (ramp) {
	start_ramp_down();
	mono_chain.wait_ramp_down_finished();
    }
    mono_chain.commit();
    if (ramp) {
	stereo_chain.wait_ramp_down_finished();
    }
    stereo_chain.commit();
    if (ramp) {
	start_ramp_up();
    }
}

void ModuleSequencer::add_selector(ModuleSelector& sel) {
    selectors.push_back(&sel);
}


/****************************************************************
 ** class GxEngine
 */

GxEngine::GxEngine(PluginList& pl):
    ModuleSequencer(pl),
    ui(),
    noisegate(),
    oscilloscope(&ui),
    convolver(&ui),
    cabinet(&ui),
    contrast(&ui) {}

GxEngine::~GxEngine() {
}

GxEngine& get_engine() {
    static GxEngine engine(get_pluginlist());
    return engine;
}

} // end namespace gx_engine
