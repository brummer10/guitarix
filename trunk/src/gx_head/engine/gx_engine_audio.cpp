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

#include "engine.h"     // NOLINT

namespace gx_engine {

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
    modules(),
    next_commit_needs_ramp() {
    sem_init(&sync_sem, 0, 0);
}

void ProcessingChainBase::set_samplerate(int samplerate) {
    steps_down = 8 * (256 * samplerate) / 48000;
    steps_up = steps_down;
    //steps_down = (64 * samplerate) / 48000;
    //steps_up = 4 * steps_down;
    steps_up_dead = 0;
}

void __rt_func ProcessingChainBase::set_stopped(bool v) {
    stopped = v;
    if (v) {
	post_rt_finished();  // in case someone is already waiting
    }
}

bool ProcessingChainBase::wait_rt_finished() {
    if (stopped) {
	return true;
    }
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    const long ns_in_sec = 1000000000;
    ts.tv_nsec += ns_in_sec / 10;
    if (ts.tv_nsec >= ns_in_sec) {
	ts.tv_nsec -= ns_in_sec;
	ts.tv_sec += 1;
    }
    while (sem_timedwait(&sync_sem, &ts) == -1) {
	if (errno == EINTR) {
	    continue;
	}
	if (errno == ETIMEDOUT) {
	    gx_print_warning("sem_timedwait", "timeout");
	    return false;
	}
	gx_print_error("sem_timedwait", "unknown error");
	break;
    }
    return true;
}

void ProcessingChainBase::set_latch() {
    int val;
    sem_getvalue(&sync_sem, &val);
    if (val > 0) {
	sem_wait(&sync_sem);
    }
    assert(sem_getvalue(&sync_sem, &val) == 0 && val == 0);
}

void ProcessingChainBase::wait_ramp_down_finished() {
    if (stopped) {
	return;
    }
    while (ramp_mode == ramp_mode_down) {
	if (!wait_rt_finished()) {
	    break;
	}
    }
}

void ProcessingChainBase::start_ramp_up() {
    RampMode rm = get_ramp_mode();
    if (!stopped) {
	if (rm != ramp_mode_down_dead && rm != ramp_mode_down) {
	    return;
	}
	set_ramp_value(0);
	set_ramp_mode(ramp_mode_up_dead);
    }
}

void ProcessingChainBase::start_ramp_down() {
    RampMode rm = get_ramp_mode();
    if (rm == ramp_mode_down_dead || rm == ramp_mode_down) {
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

void __rt_func ProcessingChainBase::try_set_ramp_mode(RampMode oldmode, RampMode newmode, int oldrv, int newrv) {
    if (oldmode != newmode) {
	if (!gx_system::atomic_compare_and_exchange(&ramp_mode, oldmode, newmode)) {
	    return;
	}
    }
    if (oldrv != newrv) {
	if (!gx_system::atomic_compare_and_exchange(&ramp_value, oldrv, newrv)) {
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
	    while ((*i1)->get_pdef()->flags & PGN_SNOOP) {
		++i1;
		if (i1 == p1.end()) {
		    break;
		}
	    }
	    while ((*i2)->get_pdef()->flags & PGN_SNOOP) {
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
	new_ids.insert((*i)->get_pdef()->id);
    }
    for (list<Plugin*>::const_iterator i = modules.begin(); i != modules.end(); ++i) {
	if (!(*i)->get_pdef()->activate_plugin) {
	    continue;
	}
	pchar_set::iterator r = new_ids.find((*i)->get_pdef()->id);
	if (r == new_ids.end()) {
	    to_release.push_back(*i);
	}
    }
    modules = p;
    return true;
}

void ProcessingChainBase::clear_module_states() {
    for (list<Plugin*>::const_iterator p = modules.begin(); p != modules.end(); ++p) {
	PluginDef* pd = (*p)->get_pdef();
	if (pd->activate_plugin) {
	    pd->activate_plugin(true, pd);
	} else if (pd->clear_state) {
	    pd->clear_state(pd);
	}
    }
}

void ProcessingChainBase::release() {
    wait_latch();
    for (list<Plugin*>::const_iterator p = to_release.begin(); p != to_release.end(); ++p) {
	(*p)->get_pdef()->activate_plugin(false, (*p)->get_pdef());
    }
    to_release.clear();
}

#ifndef NDEBUG
void ProcessingChainBase::print_chain_state(const char *title) {
    int val;
    sem_getvalue(&sync_sem, &val);
    printf("%s sync_sem = %d, stopped = %d, ramp_mode = %d\n",
	   title, val, stopped, ramp_mode);
}
#endif


/****************************************************************
 ** MonoModuleChain, StereoModuleChain
 */

void __rt_func MonoModuleChain::process(int count, float *input, float *output) {
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

void __rt_func StereoModuleChain::process(int count, float *input1, float *input2, float *output1, float *output2) {
    // run stereo rack
    RampMode rm = get_ramp_mode();
    if (rm == ramp_mode_down_dead) {
	memset(output1, 0, count*sizeof(float));
	memset(output2, 0, count*sizeof(float));
	return;
    }
    memcpy(output1, input1, count*sizeof(float));
    memcpy(output2, input2, count*sizeof(float));
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
 ** ModuleSelectorFromList
 */

ModuleSelectorFromList::ModuleSelectorFromList(
    EngineControl& seq_, const char* id_, const char* name_,
    const char* category_, plugindef_creator plugins[], const char* select_id_,
    const char* select_name_, uiloader loader, const char** groups_, int flags_)
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
    plugindef_creator *p = plugins;
    for (size = 0; *p; ++p, ++size);
    modules = new PluginDef*[size];
    for (unsigned int i = 0; i < size; ++i) {
	modules[i] = plugins[i]();
    }
    id = id_;
    name = name_;
    category = category_;
    groups = groups_;
    flags = flags_;
    load_ui = loader;
    plugin = this;
}

ModuleSelectorFromList::~ModuleSelectorFromList() {
    delete[] modules;
}

int ModuleSelectorFromList::register_parameter(const ParamReg &param) {
    value_pair *p = new value_pair[size+1];
    for (unsigned int i = 0; i < size; ++i) {
	p[i].value_id = modules[i]->id;
	p[i].value_label = modules[i]->name;
    }
    p[size].value_id = 0;
    p[size].value_label = 0;
    param.registerIEnumVar(select_id, select_name, "S", "", p, &selector, 0);
    seq.get_param()[select_id].signal_changed_int().connect(
	sigc::hide(sigc::mem_fun(seq, &EngineControl::set_rack_changed)));
    return 0;
}

int ModuleSelectorFromList::static_register(const ParamReg &param) {
    return static_cast<ModuleSelectorFromList*>(param.plugin)
	->register_parameter(param);
}

void ModuleSelectorFromList::set_module() {
    if (plugin.get_on_off()) {
	Plugin *old = current_plugin;
	current_plugin = seq.pluginlist.lookup_plugin(modules[selector]->id);
	if (old && old != current_plugin) {
	    old->set_on_off(false);
	}
	current_plugin->set_on_off(true);
	current_plugin->copy_position(plugin);
    } else if (current_plugin) {
	current_plugin->set_on_off(false);
	current_plugin = 0;
    }
}


/****************************************************************
 ** class EngineControl
 */

EngineControl::EngineControl()
    : selectors(),
      rack_changed(),
      pmap(),
      policy(),
      priority(),
      buffersize_change(),
      samplerate_change(),
      buffersize(0),
      samplerate(0),
      pluginlist(*this) {
}

EngineControl::~EngineControl() {
}

void EngineControl::add_selector(ModuleSelector& sel) {
    selectors.push_back(&sel);
}

void EngineControl::registerParameter(ParameterGroups& groups)
{
    pluginlist.registerAllPlugins(pmap, groups);
}

void EngineControl::get_sched_priority(int &policy_, int &priority_, int prio_dim) { 
    policy_ = policy;
    priority_ = priority;
    if (!prio_dim) {
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

void EngineControl::set_samplerate(unsigned int samplerate_) {
    if (samplerate == samplerate_) {
	return;
    }
    samplerate = samplerate_;
    pluginlist.set_samplerate(samplerate);
    samplerate_change(samplerate);
}

void EngineControl::set_buffersize(unsigned int buffersize_) {
    if (buffersize == buffersize_) {
	return;
    }
    buffersize = buffersize_;
    buffersize_change(buffersize);
}

void EngineControl::init(unsigned int samplerate_, unsigned int buffersize_,
			 int policy_, int priority_) {
    if (policy_ != policy || priority_ != priority) {
	policy = policy_;
	priority = priority_;
	set_buffersize(buffersize_);
	set_samplerate(samplerate_);
	return;
    }
    if (buffersize_ != buffersize) {
	set_buffersize(buffersize_);
    }
    if (samplerate_ != samplerate) {
	set_samplerate(samplerate_);
    }
}

void EngineControl::clear_rack_changed() {
    rack_changed.disconnect();
}

bool EngineControl::get_rack_changed() {
    return rack_changed.connected();
}


/****************************************************************
 ** ModuleSequencer
 */

ModuleSequencer::ModuleSequencer()
    : EngineControl(),
      audio_mode(PGN_MODE_NORMAL),
      stateflags_mutex(),
      stateflags(SF_INITIALIZING),
      state_change(),
      overload_detected(),
      overload_reason(),
      ov_disabled(0),
      mono_chain(),
      stereo_chain() {
    overload_detected.connect(
	sigc::mem_fun(this, &ModuleSequencer::check_overload));
}

ModuleSequencer::~ModuleSequencer() {
    start_ramp_down();
    wait_ramp_down_finished();
    set_stateflag(SF_INITIALIZING);
}

void ModuleSequencer::start_ramp_up() {
    mono_chain.start_ramp_up();
    stereo_chain.start_ramp_up();
}

void ModuleSequencer::start_ramp_down() {
    mono_chain.start_ramp_down();
    stereo_chain.start_ramp_down();
}

void ModuleSequencer::wait_ramp_down_finished() {
    mono_chain.wait_ramp_down_finished();
    stereo_chain.wait_ramp_down_finished();
}

bool ModuleSequencer::update_module_lists() {
    if (!get_buffersize() || !get_samplerate()) {
	return false;
    }
    if (prepare_module_lists()) {
	commit_module_lists();
	if (stateflags & SF_OVERLOAD) {
	    // hack: jackd need some time for new load statistic
	    Glib::signal_timeout().connect_once(
		sigc::bind(
		    sigc::mem_fun(this,&ModuleSequencer::clear_stateflag),
		    SF_OVERLOAD), 1000);
	}
	return true;
    }
    return false;
}

void ModuleSequencer::set_samplerate(unsigned int samplerate) {
    mono_chain.set_samplerate(samplerate);
    stereo_chain.set_samplerate(samplerate);
    EngineControl::set_samplerate(samplerate);
}

bool ModuleSequencer::check_module_lists() {
    if (mono_chain.check_release()) {
	mono_chain.release();
    }
    if (stereo_chain.check_release()) {
	stereo_chain.release();
    }
    if (get_rack_changed()) {
	update_module_lists();
	return mono_chain.check_release() || stereo_chain.check_release();
    }
    return false;
}

void ModuleSequencer::set_rack_changed() {
    if (rack_changed.connected()) {
	return;
    }
    rack_changed = Glib::signal_idle().connect(
	sigc::mem_fun(this, &ModuleSequencer::check_module_lists));
}

bool ModuleSequencer::prepare_module_lists() {
    for (list<ModuleSelector*>::iterator i = selectors.begin(); i != selectors.end(); ++i) {
	(*i)->set_module();
    }
    list<Plugin*> modules;
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
    mono_chain.commit(mono_chain.next_commit_needs_ramp, get_param());
    already_down =  (stereo_chain.get_ramp_mode() == ProcessingChainBase::ramp_mode_down_dead);
    bool stereoramp = stereo_chain.next_commit_needs_ramp && !already_down;
    if (stereoramp) {
	stereo_chain.start_ramp_down();
	stereo_chain.wait_ramp_down_finished();
    }
    stereo_chain.commit(stereo_chain.next_commit_needs_ramp, get_param());
    if (monoramp) {
	mono_chain.start_ramp_up();
	mono_chain.next_commit_needs_ramp = false;
    }
    if (stereoramp) {
	stereo_chain.start_ramp_up();
	stereo_chain.next_commit_needs_ramp = false;
    }
}

int ModuleSequencer::sporadic_interval = 0;

void __rt_func ModuleSequencer::overload(OverloadType tp, const char *reason) {
    if (!(audio_mode & PGN_MODE_NORMAL)) {
	return; // no overload message in mute/bypass modes
    }
    if ((tp & ov_disabled) == ov_XRun) {
	return; // the xrun should show up in the log anyhow
    }
    bool ignore = false;
    if ((tp & ov_disabled) == ov_Convolver) {
	ignore = true;
    }
    if (sporadic_interval > 0 && !ignore && (tp & (ov_Convolver|ov_XRun))) {
	static float last = -sporadic_interval;
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	float now = ts.tv_sec + ts.tv_nsec * 1e-9;
	if (now - last < sporadic_interval) { // max. 1 event every sporadic_interval seconds
	    last = now;
	    ignore = true;
	}
    }
    if (!ignore) {
	set_stateflag(SF_OVERLOAD);
    }
    gx_system::atomic_set(&overload_reason, reason);
    overload_detected();
}

void __rt_func ModuleSequencer::set_stateflag(StateFlag flag) {
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

void __rt_func ModuleSequencer::clear_stateflag(StateFlag flag) {
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

void ModuleSequencer::check_overload() {
    if (stateflags & SF_OVERLOAD) {
	set_state(kEngineBypass);
	check_module_lists();
	gx_print_error(
	    "watchdog",
	    boost::format(_("Overload (%s)")) % gx_system::atomic_get(overload_reason));
    } else {
	gx_print_error(
	    "watchdog",
	    boost::format(_("Overload ignored (%s)")) % gx_system::atomic_get(overload_reason));
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
    state_change(state);
}

#ifndef NDEBUG
void ModuleSequencer::print_engine_state() {
    printf("stateflags = %d, audio_mode = %d\n", stateflags, audio_mode);
    mono_chain.print_chain_state("mono  :");
    stereo_chain.print_chain_state("stereo:");
}
#endif

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

} // end namespace gx_engine
