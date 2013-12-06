/*
 * Copyright (C) 2011, 2012 Andreas Degert, Hermann Meyer
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
 */

#define always_inline inline __attribute__((always_inline))

#include <stdlib.h>
#include <string.h>
#include <ladspa.h>
#include <iostream>

#include <glibmm/init.h>
#include <glibmm/thread.h>

#include <jack/jack.h>
#include <jack/thread.h>

#include "engine.h"

#include "gx_faust_plugins.h"
#include "../plugins/pluginlib.h"

#include "faust/gx_ampout_ladspa.cc"
#include "faust/gx_outputlevel_ladspa.cc"

using namespace gx_engine;

/****************************************************************
 *                       GENERAL CLASSES                        *
 ****************************************************************/


/****************************************************************
 ** class ControlParameter
 */

class ControlParameter {
private:
    ControllerArray *midi_control;
    list<midi_controller_list*> ctlr;
    boost::mutex control_mutex;
    vector<LADSPA_Data*> parameter_port;
    void log_assignment(int ctlr, int var, const midi_controller_list& cl);
public:
    static const LADSPA_Data upper_bound;
    ControlParameter(int sz);
    ~ControlParameter();
    void set_port(unsigned int n, LADSPA_Data *p);
    ControllerArray *readJSON(gx_system::JsonParser &jp, ParamMap& param);
    void set_array(ControllerArray *m);
    void get_values();
};

const LADSPA_Data ControlParameter::upper_bound = 100;

ControlParameter::ControlParameter(int sz)
    : midi_control(0),
      ctlr(),
      control_mutex(),
      parameter_port(sz) {
}

ControlParameter::~ControlParameter() {
    delete midi_control;
}

void ControlParameter::set_port(unsigned int n, LADSPA_Data *p) {
    if (n < parameter_port.size()) {
	parameter_port[n] = p;
    } else {
	assert(false);
    }
}

ControllerArray *ControlParameter::readJSON(
    gx_system::JsonParser &jp, ParamMap& param) {
    ControllerArray *m = new ControllerArray();
    m->readJSON(jp, param);
    return m;
}

void ControlParameter::log_assignment(int ctlr, int var, const midi_controller_list& cl) {
    string s;
    for (midi_controller_list::const_iterator j = cl.begin(); j != cl.end(); ++j) {
	Parameter& p = j->getParameter();
	if (!s.empty()) {
	    s += "; ";
	}
	s += p.l_group() + ": " + p.l_name();
    }
    gx_print_info(
	_("assign parameter"),
	boost::format(_("%1% -> controller %2% [%3%]")) % var % ctlr % s);
}

void ControlParameter::set_array(ControllerArray *m) {
    boost::mutex::scoped_lock lock(control_mutex);
    ctlr.clear();
    delete midi_control;
    midi_control = m;
    if (!midi_control) {
	return;
    }
    unsigned int n = 1;
    for (unsigned int i = 0; i < midi_control->size(); ++i) {
	midi_controller_list& cl = (*midi_control)[i];
	if (cl.empty()) {
	    continue;
	}
	ctlr.push_back(&cl);
	log_assignment(i, n, cl);
	if (n++ >= parameter_port.size()) {
	    break;
	}
    }
}

void ControlParameter::get_values() {
    boost::mutex::scoped_try_lock lock(control_mutex);
    if (!lock.owns_lock()) {
	return;
    }
    int num = 0;
    for (list<midi_controller_list*>::iterator i = ctlr.begin(); i != ctlr.end(); ++i, ++num) {
	if (!parameter_port[num]) {
	    continue;
	}
	LADSPA_Data v = min(max(*parameter_port[num], 0.0f), upper_bound);
        for (midi_controller_list::iterator n = (*i)->begin(); n != (*i)->end(); ++n) {
	    n->set(v, upper_bound);
	}
    }
}


/****************************************************************
 ** class PresetIO
 */

class PresetIO: public gx_system::AbstractPresetIO {
private:
    GxJConvSettings *jcset;
    ParamMap& param;
    paramlist plist;
    ControllerArray *midi_list;
    ConvolverStereoAdapter* stereo_convolver;
    ConvolverMonoAdapter* mono_convolver;
    ControlParameter& control_parameter;
    friend class StateIO;
public:
    PresetIO(ParamMap& param, ConvolverStereoAdapter* stereo_convolver,ConvolverMonoAdapter* mono_convolver, ControlParameter& cp);
    ~PresetIO();
    void read_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&);
    void commit_preset();
    void clear();
    void write_preset(gx_system::JsonWriter& jw);
    void copy_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&, gx_system::JsonWriter &jw);
};

// cp not yet initialized, only use address!
PresetIO::PresetIO(ParamMap& param_, ConvolverStereoAdapter* stereo_convolver_, ConvolverMonoAdapter* mono_convolver_, ControlParameter& cp)
    : jcset(0),
      param(param_),
      plist(),
      midi_list(0),
      stereo_convolver(stereo_convolver_),
      mono_convolver(mono_convolver_),
      control_parameter(cp) {
      }

PresetIO::~PresetIO() {
    clear();
}

void PresetIO::clear() {
    plist.clear();
    delete midi_list;
    midi_list = 0;
    delete jcset;
    jcset = 0;
}

void PresetIO::read_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head) {
    clear();
    jp.next(gx_system::JsonParser::begin_object);
    do {
        jp.next(gx_system::JsonParser::value_key);
        if (jp.current_value() == "engine") {
	    jp.next(gx_system::JsonParser::begin_object);
	    do {
		jp.next(gx_system::JsonParser::value_key);
		if (!param.hasId(jp.current_value())) {
#if 0   // lots of warnings
		    gx_print_warning(
			_("recall settings"),
			_("unknown parameter: ")+jp.current_value());
#endif
		    jp.skip_object();
		    continue;
		}
		Parameter& p = param[jp.current_value()];
		p.readJSON_value(jp);
		plist.push_back(&p);
	    } while (jp.peek() == gx_system::JsonParser::value_key);
	    jp.next(gx_system::JsonParser::end_object);
        } else if (jp.current_value() == "jconv") {
	    if (stereo_convolver) {
		jcset = new GxJConvSettings();
		jcset->readJSON(jp);
	    } else if (mono_convolver) {
		jcset = new GxJConvSettings();
		jcset->readJSON(jp);
	    } else {
		jp.skip_object();
	    }
        } else if (jp.current_value() == "midi_controller") {
	    midi_list = control_parameter.readJSON(jp, param);
        } else {
            gx_print_warning(
		_("recall settings"),
		_("unknown preset section: ") + jp.current_value());
	    jp.skip_object();
        }
    } while (jp.peek() == gx_system::JsonParser::value_key);
    jp.next(gx_system::JsonParser::end_object);
}

void PresetIO::commit_preset() {
    if (stereo_convolver && jcset) {
	stereo_convolver->set(*jcset);
    } else if (mono_convolver && jcset) {
	mono_convolver->set(*jcset);
    }
    for (gx_engine::paramlist::iterator i = plist.begin(); i != plist.end(); ++i) {
        (*i)->setJSON_value();
    }
    control_parameter.set_array(midi_list);
    midi_list = 0;
    clear();
}

void PresetIO::write_preset(gx_system::JsonWriter& jw) {
    assert(false);
}

void PresetIO::copy_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&, gx_system::JsonWriter &jw) {
    assert(false);
}


/****************************************************************
 ** class StateIO
 */

class StateIO: public gx_system::AbstractStateIO, private PresetIO {
public:
    StateIO(ParamMap& param, ConvolverStereoAdapter* stereo_convolver, ConvolverMonoAdapter* mono_convolver, ControlParameter& cp);
    ~StateIO();
    void read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&);
    void commit_state();
    void write_state(gx_system::JsonWriter &jw, bool preserve_preset);
};

// cp not yet initialized, only use address!
StateIO::StateIO(ParamMap& param, ConvolverStereoAdapter* stereo_convolver, ConvolverMonoAdapter* mono_convolver, ControlParameter& cp)
    : PresetIO(param, stereo_convolver, mono_convolver, cp) {
}

StateIO::~StateIO() {
}

void StateIO::read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head) {
    ControllerArray *m = 0;
    do {
	jp.next(gx_system::JsonParser::value_string);
	if (jp.current_value() == "current_preset") {
	    read_preset(jp, head);
	} else if (jp.current_value() == "midi_controller") {
	    m = control_parameter.readJSON(jp, param);
	} else {
	    jp.skip_object();
	}
    } while (jp.peek() == gx_system::JsonParser::value_string);
    delete midi_list;
    midi_list = m;
}

void StateIO::commit_state() {
    commit_preset();
}

void StateIO::write_state(gx_system::JsonWriter &jw, bool preserve_preset) {}


/****************************************************************
 ** class LadspaSettings
 */

class LadspaSettings: public gx_system::GxSettingsBase {
private:
    enum Source {
	state,
	preset,
    };
    Source current_source;
    PresetIO preset_io;
    StateIO state_io;
    void change_preset_file(const std::string& newfile);
    void load(Source src, const Glib::ustring& name);
public:
    gx_system::PresetFile presetfile;
    LadspaSettings(string sfname, string presname,
		   EngineControl&, ConvolverStereoAdapter*, ConvolverMonoAdapter*, ControlParameter&);
    ~LadspaSettings();
    void load(int num);
    bool idx_in_preset(int idx) { return idx >= 0 && idx < presetfile.size(); }
    void load_preset_by_idx(int idx) { load(preset, presetfile.get_name(idx)); }
};

void LadspaSettings::load(Source src, const Glib::ustring& name) {
    gx_system::PresetFile *p = 0;
    switch (src) {
    case preset:
	if (presetfile.get_index(name) < 0) {
	    return;
	}
	p = &presetfile;
	current_source = src;
	current_name = name;
	current_bank = "";
	break;
    case state:
    default:
	current_source = state;
	current_bank = current_name = "";
	break;
    }
    seq.start_ramp_down();
    loadsetting(p, name);
    seq.start_ramp_up();
    if (current_source == state) {
	// might have changed because we read all state file sections
	current_bank = current_name = "";
    }
    seq.clear_rack_changed();
    selection_changed();
}

void LadspaSettings::change_preset_file(const std::string& newfile) {
    try {
	if (presetfile.get_filename() == newfile) {
	    presetfile.reopen();
	} else {
	    presetfile.open(newfile);
	    if (current_source == preset) {
		current_source = state;
		current_name = "";
		selection_changed();
	    }
	}
	presetlist_changed();
    } catch(gx_system::JsonException& e) {
	gx_print_error(
	    newfile.c_str(), e.what());
    }
}

// seq and cp not yet initialized, only use address!
LadspaSettings::LadspaSettings(string sfname, string presname, EngineControl& seq,
			       ConvolverStereoAdapter* stereo_convolver, ConvolverMonoAdapter* mono_convolver,
			       ControlParameter& cp)
    : GxSettingsBase(seq),
      current_source(state),
      preset_io(seq.get_param(), stereo_convolver, mono_convolver, cp),
      state_io(seq.get_param(), stereo_convolver, mono_convolver, cp) {
    set_io(&state_io, &preset_io);
    set_statefilename(sfname);
    change_preset_file(presname);
}

LadspaSettings::~LadspaSettings() {
}

void LadspaSettings::load(int num) {
    if (num == 0) {
	statefile.ensure_is_current();
	load(state,"");
    } else {
	presetfile.ensure_is_current();
	if (idx_in_preset(num-1)) {
	    load_preset_by_idx(num-1);
	} else {
	    gx_print_error("preset loader", boost::format("no preset number %1%") % num);
	}
    }
}


/****************************************************************
** misc. definitions
*/

static void log_terminal(const string& msg, GxLogger::MsgType tp, bool plugged) {
    const char *t;
    switch (tp) {
    case GxLogger::kInfo:    t = "I"; break;
    case GxLogger::kWarning: t = "W"; break;
    case GxLogger::kError:   t = "E"; break;
    default:       t = "?"; break;
    }
    if (!plugged) {
	cerr << t << " " << msg << endl;
    }
}

static int logger_inited = 0;

static void init_logger() {
    if (logger_inited++) {
	return;
    }
    GxLogger& log(GxLogger::get_logger());
    if (log.signal_message().empty()) {
	log.signal_message().connect(sigc::ptr_fun(log_terminal));
	log.unplug_queue();
    }
}

static void destroy_logger() {
    if (--logger_inited > 0) {
	return;
    }
    GxLogger::destroy();
}


/****************************************************************
 ** class LadspaGuitarix
 */

class LadspaGuitarix {
private:
    class PresetLoader {
    private:
	list<LadspaGuitarix*> ladspa_instances;
	boost::mutex instance_mutex;
	static Glib::Thread *thread;
	Glib::RefPtr<Glib::MainLoop> mainloop;
	Glib::Dispatcher new_preset;
	static PresetLoader *instance;
	static sem_t created_sem;
	static void run_mainloop();
	void load_presets();
	void add(LadspaGuitarix* i);
	bool remove(LadspaGuitarix* i);
	PresetLoader();
	~PresetLoader();
    public:
	static void start_presetloader() { if (!instance) create(); }
	static void create();
	static void destroy();
	static void add_instance(LadspaGuitarix* i);
	static void remove_instance(LadspaGuitarix* i);
	static void preset_change();
    };
protected:
    friend class PresetLoader;
    friend class LibMonitor;
    pthread_t last_thread_id;
    int jack_bs;
    int jack_prio;
    int preset_num;
    int next_preset_num;
    LADSPA_Data * preset_num_port;
    LADSPA_Data * no_buffer_port;
    LADSPA_Data * buffersize_port;
    LADSPA_Data * no_rt_mode_port;
    LADSPA_Data * priority_port;
    LADSPA_Data * latency_port;
    ControlParameter& control_parameter;
    LadspaSettings settings;
    void check_preset();
    int get_buffersize_from_port();
    void prepare_run();
    unsigned int activate(int *policy, int *prio);
    void load();
    LadspaGuitarix(EngineControl& engine, ConvolverStereoAdapter* stereo_convolver, ConvolverMonoAdapter* mono_convolver,
		   ControlParameter& cp, const char *envvar);
    ~LadspaGuitarix();
    static void start_presetloader() { PresetLoader::start_presetloader(); }
};

static string get_statefile() {
    return Glib::build_filename(Glib::get_user_config_dir(), "guitarix/gx_head_rc");
}

static string get_presetfile(const char *envvar) {
    const char *path = getenv(envvar);
    if (path && path[0]) {
	return path;
    }
    path = getenv("LADSPA_GUITARIX_PRESET");
    if (path && path[0]) {
	return path;
    }
    return Glib::build_filename(Glib::get_user_config_dir(), "guitarix/banks/ladspa.gx");
}

// engine and cp not yet initialized, only use address!
LadspaGuitarix::LadspaGuitarix(
    EngineControl& engine, ConvolverStereoAdapter* stereo_convolver, ConvolverMonoAdapter* mono_convolver, ControlParameter& cp, const char *envvar)
    : last_thread_id(),
      jack_bs(),
      jack_prio(),
      preset_num(-1),  // force load
      next_preset_num(0),
      preset_num_port(),
      no_buffer_port(),
      buffersize_port(),
      no_rt_mode_port(),
      priority_port(),
      latency_port(),
      control_parameter(cp),
      settings(get_statefile(), get_presetfile(envvar), engine, stereo_convolver, mono_convolver, cp) {
    PresetLoader::add_instance(this);
}

LadspaGuitarix::~LadspaGuitarix() {
    PresetLoader::remove_instance(this);
}

void LadspaGuitarix::check_preset() {
    if (!preset_num_port) {
	return;
    }
    int num = *preset_num_port;
    if (next_preset_num == num) {
	return;
    }
    gx_system::atomic_set(&next_preset_num, num);
    PresetLoader::preset_change();
}

void LadspaGuitarix::load() {
    int num = gx_system::atomic_get(next_preset_num);
    if (num == preset_num) {
	return;
    }
    preset_num = num;
    settings.load(num);
}

int LadspaGuitarix::get_buffersize_from_port() {
    if (!buffersize_port) {
	return 0;
    }
    int sz = round(*buffersize_port);
    if (sz <= 0) {
	return 0;
    }
    sz = 1 << g_bit_storage(sz-1);
    sz = min(max(sz, static_cast<int>(Convproc::MINQUANT)),
	     static_cast<int>(Convproc::MAXQUANT));
    return sz;
}

void LadspaGuitarix::prepare_run() {
    pthread_t tid = pthread_self();
    if (!pthread_equal(tid, last_thread_id)) {
	last_thread_id = tid;
	AVOIDDENORMALS();
    }
    check_preset();
    control_parameter.get_values();
}

unsigned int LadspaGuitarix::activate(int *policy, int *prio) {
    if (no_rt_mode_port && *no_rt_mode_port > 0) {
	*policy = SCHED_OTHER;
	*prio = 0;
    } else {
	*policy = SCHED_FIFO;
	if (priority_port) {
	    *prio = round(*priority_port);
	}
    }
    int bufsize;
    if (no_buffer_port && *no_buffer_port > 0) {
	bufsize = 0;
	*latency_port = 0;
    } else {
	bufsize = get_buffersize_from_port();
	if (jack_bs == 0) {
	    jack_status_t jackstat;
	    jack_client_t *client = jack_client_open("guitarix-test", JackNoStartServer, &jackstat);
	    if (client) {
		jack_bs = jack_get_buffer_size(client);
		jack_prio = jack_client_real_time_priority(client);
		jack_client_close(client);
	    } else {
		jack_bs = jack_prio = -1;
	    }
	}
	if (jack_bs > 0 && (!bufsize || bufsize > jack_bs)) {
	    bufsize = jack_bs;
	}
	if (!bufsize) {
	    bufsize = 64;
	}
	if (!*prio && jack_prio > 0) {
	    *prio = jack_prio;
	}
 	*latency_port = bufsize-1;
    }
    return bufsize;
}

sem_t LadspaGuitarix::PresetLoader::created_sem;
Glib::Thread *LadspaGuitarix::PresetLoader::thread = 0;
LadspaGuitarix::PresetLoader *LadspaGuitarix::PresetLoader::instance = 0;

LadspaGuitarix::PresetLoader::PresetLoader()
    : ladspa_instances(),
      instance_mutex(),
      mainloop(Glib::MainLoop::create(Glib::MainContext::create())),
      new_preset() {
}

LadspaGuitarix::PresetLoader::~PresetLoader() {
}

class LibMonitor {
public:
    ~LibMonitor();
};

static LibMonitor lib_monitor;

LibMonitor::~LibMonitor() {
    LadspaGuitarix::PresetLoader::destroy();
}

void LadspaGuitarix::PresetLoader::destroy() {
    if (!instance) {
	return;
    }
    instance->mainloop->quit();
    thread->join();
    thread = 0;
    // just to be sure, but should happen in other thread
    delete instance;
    instance = 0;
}

void LadspaGuitarix::PresetLoader::run_mainloop() {
    init_logger();
    instance = new PresetLoader();
    instance->new_preset.connect(sigc::mem_fun(*instance, &PresetLoader::load_presets));
    sem_post(&instance->created_sem);
    instance->mainloop->run();
    delete instance;
    instance = 0;
    destroy_logger();
}

void LadspaGuitarix::PresetLoader::load_presets() {
    boost::mutex::scoped_lock lock(instance_mutex);
    for (list<LadspaGuitarix*>::iterator i = ladspa_instances.begin(); i != ladspa_instances.end(); ++i) {
	(*i)->load();
    }
}

void LadspaGuitarix::PresetLoader::create() {
    assert(instance == 0);
    sem_init(&created_sem, 0, 0);
    thread = Glib::Thread::create(sigc::ptr_fun(run_mainloop), true);
    while (sem_wait(&created_sem) == -1 && errno == EINTR);
    assert(instance);
}

void LadspaGuitarix::PresetLoader::preset_change() {
    assert(instance);
    instance->new_preset();
}

void LadspaGuitarix::PresetLoader::add_instance(LadspaGuitarix* i) {
    if (!instance) {
	create();
    }
    boost::mutex::scoped_lock lock(instance->instance_mutex);
    instance->ladspa_instances.push_back(i);
}

void LadspaGuitarix::PresetLoader::remove_instance(LadspaGuitarix* i) {
    assert(instance);
    {
	boost::mutex::scoped_lock lock(instance->instance_mutex);
	instance->ladspa_instances.remove(i);
	if (!instance->ladspa_instances.empty()) {
	    return;
	}
    }
    destroy();
}


/****************************************************************
 *                         MONO Plugin                          *
 ****************************************************************/

/****************************************************************
 ** class MonoEngine
 */

class MonoEngine: public EngineControl {
private:
    gx_resample::BufferResampler resamp;
    void load_static_plugins();
    void sr_changed(unsigned int);
    void bs_changed(unsigned int);
    void overload(OverloadType tp, const char *reason);
    virtual void set_rack_changed();
public:
    MonoModuleChain mono_chain;  // active modules (amp chain, input to insert output)
    // ModuleSelector's
    ModuleSelectorFromList crybaby;
    ModuleSelectorFromList tonestack;
    ModuleSelectorFromList ampstack;
    // internal audio modules
    NoiseGate noisegate;
    ConvolverMonoAdapter mono_convolver;
    CabinetConvolver cabinet;
    PreampConvolver preamp;
    ContrastConvolver contrast;
    LiveLooper  loop;
public:
    MonoEngine(const string& plugin_dir, const string& loop_dir, ParameterGroups& groups);
    ~MonoEngine();
    virtual void wait_ramp_down_finished();
    virtual bool update_module_lists();
    virtual void start_ramp_up();
    virtual void start_ramp_down();
    virtual void set_samplerate(unsigned int samplerate);
    bool prepare_module_lists();
    void commit_module_lists();
};

void MonoEngine::wait_ramp_down_finished() {
    mono_chain.wait_ramp_down_finished();
}

bool MonoEngine::prepare_module_lists() {
    for (list<ModuleSelector*>::iterator i = selectors.begin(); i != selectors.end(); ++i) {
	(*i)->set_module();
    }
    list<Plugin*> modules;
    pluginlist.ordered_mono_list(modules, PGN_MODE_NORMAL);
    bool ret_mono = mono_chain.set_plugin_list(modules);
    if (ret_mono) {
	mono_chain.print();
    }
    return ret_mono;
}

void MonoEngine::commit_module_lists() {
    bool already_down = (mono_chain.get_ramp_mode() == ProcessingChainBase::ramp_mode_down_dead);
    bool monoramp = mono_chain.next_commit_needs_ramp && !already_down;
    if (monoramp) {
	mono_chain.start_ramp_down();
	mono_chain.wait_ramp_down_finished();
    }
    mono_chain.commit(mono_chain.next_commit_needs_ramp, pmap);
    if (monoramp) {
	mono_chain.start_ramp_up();
	mono_chain.next_commit_needs_ramp = false;
    }
}

bool MonoEngine::update_module_lists() {
    if (prepare_module_lists()) {
	commit_module_lists();
	return true;
    }
    return false;
}

void MonoEngine::set_rack_changed() {
    if (rack_changed.connected()) {
	return;
    }
    rack_changed = Glib::signal_idle().connect(
	sigc::bind_return(sigc::mem_fun(this, &MonoEngine::update_module_lists),false));
}

void MonoEngine::start_ramp_up() {
    mono_chain.start_ramp_up();
}

void MonoEngine::start_ramp_down() {
    mono_chain.start_ramp_down();
}

void MonoEngine::set_samplerate(unsigned int samplerate) {
    mono_chain.set_samplerate(samplerate);
    EngineControl::set_samplerate(samplerate);
}

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
    0
};

static const char* ampstack_groups[] = {
    ".amp2.stage1",  N_("Tube1"),
    ".amp2.stage2",  N_("Tube2"),
    ".tube",         N_("Tube 1"),
    ".gxdistortion", N_("Multi Band Distortion"),
    0
};

MonoEngine::MonoEngine(const string& plugin_dir, const string& loop_dir, ParameterGroups& groups)
    : EngineControl(),
      resamp(),
      // ModuleSelector's
      crybaby(
	  *this, "crybaby", N_("Crybaby"), "", builtin_crybaby_plugins,
	  "crybaby.autowah", _("select"), 0, 0, PGN_POST_PRE),
      tonestack(
	  *this, "amp.tonestack", N_("Tonestack"), "",
	  builtin_tonestack_plugins, "amp.tonestack.select",
	  _("select"), 0, 0, PGN_POST_PRE),
      ampstack(
	  *this, "ampstack", "?Tube", "", builtin_amp_plugins,
	  "tube.select", _("select"), 0, ampstack_groups),
      // internal audio modules
      noisegate(),
      mono_convolver(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync), get_param()),
      cabinet(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync), resamp),
      preamp(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync), resamp),
      contrast(*this, sigc::mem_fun(mono_chain, &MonoModuleChain::sync), resamp),
      loop(get_param(), sigc::mem_fun(mono_chain, &MonoModuleChain::sync), loop_dir) {

    mono_convolver.set_sync(true);
    cabinet.set_sync(true);
    preamp.set_sync(true);
    contrast.set_sync(true);

    load_static_plugins();

    // loaded from shared libs
    if (!plugin_dir.empty()) {
	pluginlist.load_from_path(plugin_dir, PLUGIN_POS_RACK);
    }

    // selector objects to switch "alternative" modules
    add_selector(ampstack);
    add_selector(crybaby);
    add_selector(tonestack);

    registerParameter(groups);

    signal_samplerate_change().connect(
	sigc::mem_fun(*this, &MonoEngine::sr_changed));
    signal_buffersize_change().connect(
	sigc::mem_fun(*this, &MonoEngine::bs_changed));

#ifndef NDEBUG
    pluginlist.printlist();
#endif
}

MonoEngine::~MonoEngine() {
}

void MonoEngine::sr_changed(unsigned int sr) {
    samplerate = sr;
}

void MonoEngine::bs_changed(unsigned int bs) {
    buffersize = bs;
}

void MonoEngine::overload(OverloadType tp, const char *reason) {
    gx_print_error("overload", reason);
}

void MonoEngine::load_static_plugins() {
    PluginList& pl = pluginlist; // just a shortcut

    // * mono amp input position *

    pl.add(&noisegate.inputlevel,                 PLUGIN_POS_START, PGN_GUI|PGN_PRE);
    pl.add(gx_effects::noise_shaper::plugin(),    PLUGIN_POS_START, PGN_GUI|PGN_PRE);

    // rack pre mono modules inserted here

    pl.add(builtin_amp_plugins,                   PLUGIN_POS_START, PGN_ALTERNATIVE|PGN_POST);
    pl.add(&ampstack.plugin,                      PLUGIN_POS_START, PGN_POST);
    pl.add(gx_effects::softclip::plugin(),        PLUGIN_POS_START, PGN_GUI|PGN_POST);

    // rack post mono modules inserted here

    pl.add(gx_effects::bassbooster::plugin(),     PLUGIN_POS_END, PGN_GUI|PGN_POST);
    pl.add(gx_ampout_ladspa::plugin(),            PLUGIN_POS_END, PGN_POST);
    pl.add(&contrast.plugin,                      PLUGIN_POS_END, PGN_GUI|PGN_POST);
    pl.add(&noisegate.outputgate,                 PLUGIN_POS_END, PGN_POST);

    // dynamic rack modules
    // builtin 
    pl.add(builtin_crybaby_plugins,               PLUGIN_POS_RACK, PGN_ALTERNATIVE);
    pl.add(builtin_tonestack_plugins,             PLUGIN_POS_RACK, PGN_ALTERNATIVE);

    // mono
    pl.add(gx_effects::low_high_pass::plugin(),   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::highbooster::plugin(),     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::selecteq::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&crybaby.plugin,                       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&loop.plugin,                          PLUGIN_POS_RACK,  PGN_GUI);
    pl.add(gx_effects::gx_distortion::plugin(),   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::ts9sim::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::impulseresponse::plugin(), PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::compressor::plugin(),      PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::overdrive::plugin(),       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::echo::plugin(),            PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::delay::plugin(),           PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::freeverb::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
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
    pl.add(&mono_convolver.plugin,                PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&cabinet.plugin,                       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&preamp.plugin,                        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(pluginlib::abgate::plugin(),           PLUGIN_POS_RACK);
    pl.add(pluginlib::vibe::plugin_mono(),        PLUGIN_POS_RACK);
    pl.add(pluginlib::mbc::plugin(),              PLUGIN_POS_RACK);
    pl.add(pluginlib::mbd::plugin(),              PLUGIN_POS_RACK);
    pl.add(pluginlib::mbe::plugin(),              PLUGIN_POS_RACK);
    pl.add(pluginlib::mbdel::plugin(),              PLUGIN_POS_RACK);
    pl.add(pluginlib::mbchor::plugin(),              PLUGIN_POS_RACK);
}


/****************************************************************
 ** class LadspaGuitarixMono
 */

class LadspaGuitarixMono: LadspaGuitarix {
private:

    enum {  // ladspa ports
	GUITARIX_INPUT,
	GUITARIX_OUTPUT,
	GUITARIX_PRESET,
	GUITARIX_VOLUME,
	GUITARIX_PARAM,
	GUITARIX_PARAM_COUNT = 5,
	GUITARIX_NO_BUFFER = GUITARIX_PARAM + GUITARIX_PARAM_COUNT,
	GUITARIX_BUFFERSIZE,
	GUITARIX_NO_RT_MODE,
	GUITARIX_PRIORITY,
	GUITARIX_LATENCY,
	PORT_COUNT
    };

    class LADSPA: public LADSPA_Descriptor { 
	LADSPA_PortDescriptor pdesc[PORT_COUNT];
	const char *pnames[PORT_COUNT];
	LADSPA_PortRangeHint prangehint[PORT_COUNT];
    public:
	LADSPA();
	~LADSPA();
    };

    class ReBuffer {
    private:
	// data for compute
	int buffer_size;
	int in_buffer_index;
	int out_buffer_index;
	LADSPA_Data *in_buffer;
	LADSPA_Data *out_buffer;
	// input data for run()
	int block_size;
	int in_block_index;
	int out_block_index;
	LADSPA_Data *in_block;
	LADSPA_Data *out_block;
	static inline void copy(LADSPA_Data *dst, LADSPA_Data *src, int cnt) {
	    memcpy(dst, src, cnt * sizeof(dst[0]));
	}
    public:
	ReBuffer();
	~ReBuffer();
	int get_count() { return buffer_size; }
	LADSPA_Data *get_input() { return in_buffer; }
	LADSPA_Data *get_output() { return out_buffer; }
	bool put();
	void set_bufsize(int bufsize);
	int get_bufsize() { return buffer_size; }
	void set(int cnt, LADSPA_Data *input_buffer, LADSPA_Data *output_buffer);
    };

    MonoEngine engine;
    ControlParameter control_parameter;
    ReBuffer rebuffer;
    LADSPA_Data * volume_port;
    FloatParameter& volume_param;
    LADSPA_Data * input_buffer;
    LADSPA_Data * output_buffer;
    LadspaGuitarixMono(unsigned long sr);
    ~LadspaGuitarixMono();
public:
    static void activateGuitarix(LADSPA_Handle Instance);
    static void runGuitarix(LADSPA_Handle Instance, unsigned long SampleCount);
    static const LADSPA_Descriptor * ladspa_descriptor();
    static void connectPortToGuitarix(LADSPA_Handle Instance, unsigned long Port,
				      LADSPA_Data *DataLocation);
    static LADSPA_Handle instantiateGuitarix(const LADSPA_Descriptor * Descriptor,
					     unsigned long SampleRate);
    static void cleanupGuitarix(LADSPA_Handle Instance);
};

LadspaGuitarixMono::LadspaGuitarixMono(unsigned long sr)
    : LadspaGuitarix(engine, 0, &engine.mono_convolver, control_parameter, "LADSPA_GUITARIX_MONO_PRESET"),
      engine(Glib::build_filename(Glib::get_user_config_dir(), "guitarix/plugins/"),
       Glib::build_filename(Glib::get_user_config_dir(), "guitarix/pluginpresets/loops/"), get_group_table()),
      control_parameter(GUITARIX_PARAM_COUNT),
      rebuffer(),
      volume_port(),
      volume_param(engine.get_param()["amp.out_ladspa"].getFloat()),
      input_buffer(),
      output_buffer() {
    engine.get_param().set_init_values();
    engine.set_samplerate(sr);
}

LadspaGuitarixMono::~LadspaGuitarixMono() {
}

const LADSPA_Descriptor *LadspaGuitarixMono::ladspa_descriptor() {
    static LADSPA ladspa;
    return &ladspa;
}

void LadspaGuitarixMono::activateGuitarix(LADSPA_Handle Instance) {
    LadspaGuitarixMono& self = *static_cast<LadspaGuitarixMono*>(Instance);
    int policy, prio, bufsize;
    bufsize = self.activate(&policy, &prio);
    self.rebuffer.set_bufsize(bufsize);
    self.engine.set_buffersize(bufsize);
    gx_print_info(
	"amp activate",
	boost::format("instance %1%, SR %2%, BS %3%, prio %4%")
	% Instance % self.engine.get_samplerate() % bufsize % prio);
    self.engine.init(self.engine.get_samplerate(), bufsize, policy, prio);
    self.engine.mono_chain.set_stopped(true);
    self.load();
    self.engine.mono_chain.set_stopped(false);
    self.engine.mono_chain.start_ramp_up();
}

void LadspaGuitarixMono::runGuitarix(LADSPA_Handle Instance, unsigned long SampleCount) {
    LadspaGuitarixMono& self = *static_cast<LadspaGuitarixMono*>(Instance);
    self.prepare_run();
    self.volume_param.set(*self.volume_port);
    if (self.rebuffer.get_bufsize()) {
	self.rebuffer.set(SampleCount, self.input_buffer, self.output_buffer);
	while (self.rebuffer.put()) {
	    self.engine.mono_chain.process(
		self.rebuffer.get_count(), self.rebuffer.get_input(),
		self.rebuffer.get_output());
	}
    } else {
	self.engine.mono_chain.process(
	    SampleCount, self.input_buffer, self.output_buffer);
    }
    self.engine.mono_chain.post_rt_finished();
}

void LadspaGuitarixMono::connectPortToGuitarix(
    LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation) {
    LadspaGuitarixMono *self = static_cast<LadspaGuitarixMono*>(Instance);
    switch (Port) {
    case GUITARIX_INPUT:
	self->input_buffer = DataLocation;
	break;
    case GUITARIX_OUTPUT:
	self->output_buffer = DataLocation;
	break;
    case GUITARIX_PRESET:
	self->preset_num_port = DataLocation;
	break;
    case GUITARIX_VOLUME:
	self->volume_port = DataLocation;
	break;
    case GUITARIX_NO_BUFFER:
	self->no_buffer_port = DataLocation;
	break;
    case GUITARIX_BUFFERSIZE:
	self->buffersize_port = DataLocation;
	break;
    case GUITARIX_NO_RT_MODE:
	self->no_rt_mode_port = DataLocation;
	break;
    case GUITARIX_PRIORITY:
	self->priority_port = DataLocation;
	break;
    case GUITARIX_LATENCY:
	self->latency_port = DataLocation;
	*self->latency_port = 0;
	break;
    default:
	self->control_parameter.set_port(Port-GUITARIX_PARAM, DataLocation);
	break;
    }
}

LADSPA_Handle LadspaGuitarixMono::instantiateGuitarix(
    const LADSPA_Descriptor * Descriptor, unsigned long SampleRate) {
    start_presetloader();
    return new LadspaGuitarixMono(SampleRate);
}

void LadspaGuitarixMono::cleanupGuitarix(LADSPA_Handle Instance) {
    delete static_cast<LadspaGuitarixMono*>(Instance);
}

LadspaGuitarixMono::ReBuffer::ReBuffer()
    : buffer_size(0),
      in_buffer_index(0),
      out_buffer_index(0),
      in_buffer(0),
      out_buffer(0),
      block_size(0),
      in_block_index(0),
      out_block_index(0),
      in_block(0),
      out_block(0) {
}

LadspaGuitarixMono::ReBuffer::~ReBuffer() {
    delete[] in_buffer;
    delete[] out_buffer;
}

void LadspaGuitarixMono::ReBuffer::set_bufsize(int bufsize) {
    if (bufsize) {
	if (bufsize != buffer_size) {
	    delete[] in_buffer;
	    in_buffer = new LADSPA_Data[bufsize];
	    delete[] out_buffer;
	    out_buffer = new LADSPA_Data[bufsize];
	    buffer_size = bufsize;
	    memset(out_buffer, 0, bufsize * sizeof(out_buffer[0]));
	    in_buffer_index = 0;
	    out_buffer_index = 1;
	}
    } else if (buffer_size) {
	delete[] in_buffer;
	in_buffer = 0;
	delete[] out_buffer;
	out_buffer = 0;
	buffer_size = 0;
    }
}

void LadspaGuitarixMono::ReBuffer::set(
    int cnt, LADSPA_Data *input_buffer, LADSPA_Data *output_buffer) {
    in_block_index = 0;
    out_block_index = 0;
    block_size = cnt;
    in_block = input_buffer;
    out_block = output_buffer;
}

bool LadspaGuitarixMono::ReBuffer::put() {
    int n = min(buffer_size - in_buffer_index, block_size - in_block_index);
    if (n) {
	// copy values to in buffer
	copy(in_buffer+in_buffer_index, in_block+in_block_index, n);
	in_buffer_index += n;
	in_block_index += n;
    }
    n = min(buffer_size-out_buffer_index, block_size-out_block_index);
    if (n) {
	// copy values from out buffer
	copy(out_block+out_block_index, out_buffer+out_buffer_index, n);
	out_block_index += n;
	out_buffer_index += n;
    }
    if (in_buffer_index == buffer_size) {
	// had enough input data left to fill buffer -> process
	in_buffer_index = 0;
	out_buffer_index = 0;
	return true;
    }
    return false;
}


/****************************************************************
 ** class LadspaGuitarixMono::LADSPA
 */

LadspaGuitarixMono::LADSPA::LADSPA()
    : LADSPA_Descriptor() {
    pdesc[GUITARIX_INPUT]  = LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO;
    pnames[GUITARIX_INPUT] = "Input";
    prangehint[GUITARIX_INPUT].HintDescriptor = 0;

    pdesc[GUITARIX_OUTPUT] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
    pnames[GUITARIX_OUTPUT] = "Output";
    prangehint[GUITARIX_OUTPUT].HintDescriptor = 0;

    pdesc[GUITARIX_PRESET] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_PRESET] = "Preset";
    prangehint[GUITARIX_PRESET].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	LADSPA_HINT_INTEGER | LADSPA_HINT_DEFAULT_0;
    prangehint[GUITARIX_PRESET].LowerBound = 0;
    prangehint[GUITARIX_PRESET].UpperBound = 99;

    pdesc[GUITARIX_VOLUME] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_VOLUME] = "Level adj. (dB)";
    prangehint[GUITARIX_VOLUME].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	LADSPA_HINT_DEFAULT_0;
    prangehint[GUITARIX_VOLUME].LowerBound = -20;
    prangehint[GUITARIX_VOLUME].UpperBound = 20;

    pdesc[GUITARIX_NO_BUFFER] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_NO_BUFFER] = "No Buffer";
    prangehint[GUITARIX_NO_BUFFER].HintDescriptor =
	LADSPA_HINT_TOGGLED | LADSPA_HINT_DEFAULT_0;

    pdesc[GUITARIX_BUFFERSIZE] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_BUFFERSIZE] = "Buffersize";
    prangehint[GUITARIX_BUFFERSIZE].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	LADSPA_HINT_DEFAULT_0;
    prangehint[GUITARIX_BUFFERSIZE].LowerBound = 0;
    prangehint[GUITARIX_BUFFERSIZE].UpperBound = Convproc::MAXQUANT;

    pdesc[GUITARIX_NO_RT_MODE] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_NO_RT_MODE] = "Non-RT Mode";
    prangehint[GUITARIX_NO_RT_MODE].HintDescriptor =
	LADSPA_HINT_TOGGLED | LADSPA_HINT_DEFAULT_0;

    pdesc[GUITARIX_PRIORITY] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_PRIORITY] = "RT Priority";
    prangehint[GUITARIX_PRIORITY].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	LADSPA_HINT_INTEGER | LADSPA_HINT_DEFAULT_0;
    prangehint[GUITARIX_PRIORITY].LowerBound = 0;
    prangehint[GUITARIX_PRIORITY].UpperBound = 99;

    pdesc[GUITARIX_LATENCY] = LADSPA_PORT_OUTPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_LATENCY] = "latency"; // predefined name
    prangehint[GUITARIX_LATENCY].HintDescriptor = 0;

    for (int i = 0; i < GUITARIX_PARAM_COUNT; ++i) {
	pdesc[GUITARIX_PARAM+i] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
	pnames[GUITARIX_PARAM+i] = strdup(("Parameter " + gx_system::to_string(i+1)).c_str());
	prangehint[GUITARIX_PARAM+i].HintDescriptor =
	    LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	    LADSPA_HINT_DEFAULT_NONE;
	prangehint[GUITARIX_PARAM+i].LowerBound = 0;
	prangehint[GUITARIX_PARAM+i].UpperBound = ControlParameter::upper_bound;
    }

    UniqueID = 4069;
    Label = "guitarix-amp";
    Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
    Name = "Guitarix Amp";
    Maker = "Guitarix Team";
    Copyright = "GPL";
    PortCount = PORT_COUNT;
    PortDescriptors = pdesc;
    PortNames = pnames;
    PortRangeHints = prangehint;
    ImplementationData = 0;
    instantiate = instantiateGuitarix;
    connect_port = connectPortToGuitarix;
    activate = activateGuitarix;
    run = runGuitarix;
    run_adding = 0;
    set_run_adding_gain = 0;
    deactivate = 0;
    cleanup = cleanupGuitarix;
}

LadspaGuitarixMono::LADSPA::~LADSPA() {
    for (int i = 0; i < GUITARIX_PARAM_COUNT; ++i) {
	free(const_cast<char*>(pnames[GUITARIX_PARAM+i]));
    }
}


/****************************************************************
 *                        STEREO Plugin                         *
 ****************************************************************/

/****************************************************************
 ** class StereoEngine
 */

class StereoEngine: public EngineControl {
private:
    void load_static_plugins();
    void overload(OverloadType tp, const char *reason);
    virtual void set_rack_changed();
public:
    StereoModuleChain stereo_chain;
    ConvolverStereoAdapter stereo_convolver;
public:
    StereoEngine(const string& plugin_dir, ParameterGroups& groups);
    ~StereoEngine();
    virtual void wait_ramp_down_finished();
    virtual bool update_module_lists();
    virtual void start_ramp_up();
    virtual void start_ramp_down();
    virtual void set_samplerate(unsigned int samplerate);
    bool prepare_module_lists();
    void commit_module_lists();
};

void StereoEngine::overload(OverloadType tp, const char *reason) {
    gx_print_error("overload", reason);
}

void StereoEngine::wait_ramp_down_finished() {
    stereo_chain.wait_ramp_down_finished();
}

bool StereoEngine::prepare_module_lists() {
    for (list<ModuleSelector*>::iterator i = selectors.begin(); i != selectors.end(); ++i) {
	(*i)->set_module();
    }
    list<Plugin*> modules;
    pluginlist.ordered_stereo_list(modules, PGN_MODE_NORMAL);
    bool ret_stereo = stereo_chain.set_plugin_list(modules);
    if (ret_stereo) {
	stereo_chain.print();
    }
    return ret_stereo;
}

void StereoEngine::commit_module_lists() {
    bool already_down = (stereo_chain.get_ramp_mode() == ProcessingChainBase::ramp_mode_down_dead);
    bool stereoramp = stereo_chain.next_commit_needs_ramp && !already_down;
    if (stereoramp) {
	stereo_chain.start_ramp_down();
	stereo_chain.wait_ramp_down_finished();
    }
    stereo_chain.commit(stereo_chain.next_commit_needs_ramp, pmap);
    if (stereoramp) {
	stereo_chain.start_ramp_up();
	stereo_chain.next_commit_needs_ramp = false;
    }
}

bool StereoEngine::update_module_lists() {
    if (prepare_module_lists()) {
	commit_module_lists();
	return true;
    }
    return false;
}

void StereoEngine::set_rack_changed() {
    if (rack_changed.connected()) {
	return;
    }
    rack_changed = Glib::signal_idle().connect(
	sigc::bind_return(sigc::mem_fun(this, &StereoEngine::update_module_lists),false));
}

void StereoEngine::start_ramp_up() {
    stereo_chain.start_ramp_up();
}

void StereoEngine::start_ramp_down() {
    stereo_chain.start_ramp_down();
}

void StereoEngine::set_samplerate(unsigned int samplerate) {
    stereo_chain.set_samplerate(samplerate);
    EngineControl::set_samplerate(samplerate);
}

StereoEngine::StereoEngine(const string& plugin_dir, ParameterGroups& groups)
    : EngineControl(),
      // internal audio modules
      stereo_convolver(*this, sigc::mem_fun(stereo_chain, &StereoModuleChain::sync), get_param()) {

    stereo_convolver.set_sync(true);

    load_static_plugins();

    // loaded from shared libs
    if (!plugin_dir.empty()) {
	pluginlist.load_from_path(plugin_dir, PLUGIN_POS_RACK);
    }

    registerParameter(groups);

#ifndef NDEBUG
    pluginlist.printlist();
#endif
}

StereoEngine::~StereoEngine() {
}

void StereoEngine::load_static_plugins() {
    PluginList& pl = pluginlist; // just a shortcut

    // * amp insert position (stereo amp input) *

    pl.add(gx_effects::gxfeed::plugin(),          PLUGIN_POS_START);

    // rack stereo modules inserted here

    pl.add(gx_outputlevel_ladspa::plugin(),       PLUGIN_POS_END);

    // * fx amp output *

    // dynamic rack modules
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


/****************************************************************
 ** class LadspaGuitarixStereo
 */

class LadspaGuitarixStereo: LadspaGuitarix {
private:

    enum {  // ladspa ports
	GUITARIX_INPUT1,
	GUITARIX_INPUT2,
	GUITARIX_OUTPUT1,
	GUITARIX_OUTPUT2,
	GUITARIX_PRESET,
	GUITARIX_VOLUME,
	GUITARIX_PARAM,
	GUITARIX_PARAM_COUNT = 5,
	GUITARIX_NO_BUFFER = GUITARIX_PARAM + GUITARIX_PARAM_COUNT,
	GUITARIX_BUFFERSIZE,
	GUITARIX_NO_RT_MODE,
	GUITARIX_PRIORITY,
	GUITARIX_LATENCY,
	PORT_COUNT
    };

    class LADSPA: public LADSPA_Descriptor { 
	LADSPA_PortDescriptor pdesc[PORT_COUNT];
	const char *pnames[PORT_COUNT];
	LADSPA_PortRangeHint prangehint[PORT_COUNT];
    public:
	LADSPA();
	~LADSPA();
    };

    class ReBuffer {
    private:
	// data for compute
	int buffer_size;
	int in_buffer_index;
	int out_buffer_index;
	LADSPA_Data *in_buffer1;
	LADSPA_Data *in_buffer2;
	LADSPA_Data *out_buffer1;
	LADSPA_Data *out_buffer2;
	// input data for run()
	int block_size;
	int in_block_index;
	int out_block_index;
	LADSPA_Data *in_block1;
	LADSPA_Data *in_block2;
	LADSPA_Data *out_block1;
	LADSPA_Data *out_block2;
	static inline void copy(LADSPA_Data *dst1, LADSPA_Data *dst2,
				LADSPA_Data *src1, LADSPA_Data *src2, int cnt) {
	    memcpy(dst1, src1, cnt * sizeof(dst1[0]));
	    memcpy(dst2, src2, cnt * sizeof(dst2[0]));
	}
    public:
	ReBuffer();
	~ReBuffer();
	int get_count() { return buffer_size; }
	LADSPA_Data *get_input1() { return in_buffer1; }
	LADSPA_Data *get_input2() { return in_buffer2; }
	LADSPA_Data *get_output1() { return out_buffer1; }
	LADSPA_Data *get_output2() { return out_buffer2; }
	bool put();
	void set_bufsize(int bufsize);
	int get_bufsize() { return buffer_size; }
	void set(int cnt, LADSPA_Data *input_buffer1, LADSPA_Data *input_buffer2,
		 LADSPA_Data *output_buffer1, LADSPA_Data *output_buffer2);
    };

    StereoEngine engine;
    ControlParameter control_parameter;
    ReBuffer rebuffer;
    LADSPA_Data * volume_port;
    FloatParameter& volume_param;
    LADSPA_Data * input_buffer1;
    LADSPA_Data * input_buffer2;
    LADSPA_Data * output_buffer1;
    LADSPA_Data * output_buffer2;
    LadspaGuitarixStereo(unsigned long sr);
    ~LadspaGuitarixStereo();
public:
    static void activateGuitarix(LADSPA_Handle Instance);
    static void runGuitarix(LADSPA_Handle Instance, unsigned long SampleCount);
    static const LADSPA_Descriptor * ladspa_descriptor();
    static void connectPortToGuitarix(LADSPA_Handle Instance, unsigned long Port,
				      LADSPA_Data *DataLocation);
    static LADSPA_Handle instantiateGuitarix(const LADSPA_Descriptor * Descriptor,
					     unsigned long SampleRate);
    static void cleanupGuitarix(LADSPA_Handle Instance);
};

LadspaGuitarixStereo::LadspaGuitarixStereo(unsigned long sr)
    : LadspaGuitarix(engine, &engine.stereo_convolver, 0, control_parameter, "LADSPA_GUITARIX_STEREO_PRESET"),
      engine(Glib::build_filename(Glib::get_user_config_dir(), "guitarix/plugins/"), get_group_table()),
      control_parameter(GUITARIX_PARAM_COUNT),
      rebuffer(),
      volume_port(),
      volume_param(engine.get_param()["amp.out_master_ladspa"].getFloat()),
      input_buffer1(),
      input_buffer2(),
      output_buffer1(),
      output_buffer2() {
    engine.get_param().set_init_values();
    engine.set_samplerate(sr);
}

LadspaGuitarixStereo::~LadspaGuitarixStereo() {
}

const LADSPA_Descriptor *LadspaGuitarixStereo::ladspa_descriptor() {
    static LADSPA ladspa;
    return &ladspa;
}

void LadspaGuitarixStereo::activateGuitarix(LADSPA_Handle Instance) {
    LadspaGuitarixStereo& self = *static_cast<LadspaGuitarixStereo*>(Instance);
    int policy, prio, bufsize;
    bufsize = self.activate(&policy, &prio);
    self.rebuffer.set_bufsize(bufsize);
    self.engine.set_buffersize(bufsize);
    gx_print_info(
	"fx activate",
	boost::format("instance %1%, SR %2%, BS %3%, prio %4%")
	% Instance % self.engine.get_samplerate() % bufsize % prio);
    self.engine.init(self.engine.get_samplerate(), bufsize, policy, prio);
    self.engine.stereo_chain.set_stopped(true);
    self.load();
    self.engine.stereo_chain.set_stopped(false);
    self.engine.stereo_chain.start_ramp_up();
}

void LadspaGuitarixStereo::runGuitarix(LADSPA_Handle Instance, unsigned long SampleCount) {
    LadspaGuitarixStereo& self = *static_cast<LadspaGuitarixStereo*>(Instance);
    self.prepare_run();
    self.volume_param.set(*self.volume_port);
    if (self.rebuffer.get_bufsize()) {
	self.rebuffer.set(SampleCount, self.input_buffer1, self.input_buffer2,
			  self.output_buffer1, self.output_buffer2);
	while (self.rebuffer.put()) {
	    self.engine.stereo_chain.process(
		self.rebuffer.get_count(), self.rebuffer.get_input1(), self.rebuffer.get_input2(),
		self.rebuffer.get_output1(), self.rebuffer.get_output2());
	}
    } else {
	self.engine.stereo_chain.process(
	    SampleCount, self.input_buffer1, self.input_buffer2,
	    self.output_buffer1, self.output_buffer2);
    }
    self.engine.stereo_chain.post_rt_finished();
}

void LadspaGuitarixStereo::connectPortToGuitarix(
    LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation) {
    LadspaGuitarixStereo *self = static_cast<LadspaGuitarixStereo*>(Instance);
    switch (Port) {
    case GUITARIX_INPUT1:
	self->input_buffer1 = DataLocation;
	break;
    case GUITARIX_INPUT2:
	self->input_buffer2 = DataLocation;
	break;
    case GUITARIX_OUTPUT1:
	self->output_buffer1 = DataLocation;
	break;
    case GUITARIX_OUTPUT2:
	self->output_buffer2 = DataLocation;
	break;
    case GUITARIX_PRESET:
	self->preset_num_port = DataLocation;
	break;
    case GUITARIX_VOLUME:
	self->volume_port = DataLocation;
	break;
    case GUITARIX_NO_BUFFER:
	self->no_buffer_port = DataLocation;
	break;
    case GUITARIX_BUFFERSIZE:
	self->buffersize_port = DataLocation;
	break;
    case GUITARIX_NO_RT_MODE:
	self->no_rt_mode_port = DataLocation;
	break;
    case GUITARIX_PRIORITY:
	self->priority_port = DataLocation;
	break;
    case GUITARIX_LATENCY:
	self->latency_port = DataLocation;
	*self->latency_port = 0;
	break;
    default:
	self->control_parameter.set_port(Port-GUITARIX_PARAM, DataLocation);
	break;
    }
}

LADSPA_Handle LadspaGuitarixStereo::instantiateGuitarix(
    const LADSPA_Descriptor * Descriptor, unsigned long SampleRate) {
    start_presetloader();
    return new LadspaGuitarixStereo(SampleRate);
}

void LadspaGuitarixStereo::cleanupGuitarix(LADSPA_Handle Instance) {
    delete static_cast<LadspaGuitarixStereo*>(Instance);
}

LadspaGuitarixStereo::ReBuffer::ReBuffer()
    : buffer_size(0),
      in_buffer_index(0),
      out_buffer_index(0),
      in_buffer1(0),
      in_buffer2(0),
      out_buffer1(0),
      out_buffer2(0),
      block_size(0),
      in_block_index(0),
      out_block_index(0),
      in_block1(0),
      in_block2(0),
      out_block1(0),
      out_block2(0) {
}

LadspaGuitarixStereo::ReBuffer::~ReBuffer() {
    delete[] in_buffer1;
    delete[] in_buffer2;
    delete[] out_buffer1;
    delete[] out_buffer2;
}

void LadspaGuitarixStereo::ReBuffer::set_bufsize(int bufsize) {
    if (bufsize) {
	if (bufsize != buffer_size) {
	    delete[] in_buffer1;
	    in_buffer1 = new LADSPA_Data[bufsize];
	    delete[] in_buffer2;
	    in_buffer2 = new LADSPA_Data[bufsize];
	    delete[] out_buffer1;
	    out_buffer1 = new LADSPA_Data[bufsize];
	    delete[] out_buffer2;
	    out_buffer2 = new LADSPA_Data[bufsize];
	    buffer_size = bufsize;
	    memset(out_buffer1, 0, bufsize * sizeof(out_buffer1[0]));
	    memset(out_buffer2, 0, bufsize * sizeof(out_buffer2[0]));
	    in_buffer_index = 0;
	    out_buffer_index = 1;
	}
    } else if (buffer_size) {
	delete[] in_buffer1;
	in_buffer1 = 0;
	delete[] in_buffer1;
	in_buffer2 = 0;
	delete[] out_buffer1;
	out_buffer1 = 0;
	delete[] out_buffer2;
	out_buffer2 = 0;
	buffer_size = 0;
    }
}

void LadspaGuitarixStereo::ReBuffer::set(
    int cnt, LADSPA_Data *input_buffer1, LADSPA_Data *input_buffer2,
    LADSPA_Data *output_buffer1, LADSPA_Data *output_buffer2) {
    in_block_index = 0;
    out_block_index = 0;
    block_size = cnt;
    in_block1 = input_buffer1;
    in_block2 = input_buffer2;
    out_block1 = output_buffer1;
    out_block2 = output_buffer2;
}

bool LadspaGuitarixStereo::ReBuffer::put() {
    int n = min(buffer_size - in_buffer_index, block_size - in_block_index);
    if (n) {
	// copy values to in buffer
	copy(in_buffer1+in_buffer_index, in_buffer2+in_buffer_index,
	     in_block1+in_block_index, in_block2+in_block_index, n);
	in_buffer_index += n;
	in_block_index += n;
    }
    n = min(buffer_size-out_buffer_index, block_size-out_block_index);
    if (n) {
	// copy values from out buffer
	copy(out_block1+out_block_index, out_block2+out_block_index,
	     out_buffer1+out_buffer_index, out_buffer2+out_buffer_index, n);
	out_block_index += n;
	out_buffer_index += n;
    }
    if (in_buffer_index == buffer_size) {
	// had enough input data left to fill buffer -> process
	in_buffer_index = 0;
	out_buffer_index = 0;
	return true;
    }
    return false;
}


/****************************************************************
 ** class LadspaGuitarixStereo::LADSPA
 */

LadspaGuitarixStereo::LADSPA::LADSPA()
    : LADSPA_Descriptor() {
    pdesc[GUITARIX_INPUT1]  = LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO;
    pnames[GUITARIX_INPUT1] = "Input1";
    prangehint[GUITARIX_INPUT1].HintDescriptor = 0;

    pdesc[GUITARIX_INPUT2]  = LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO;
    pnames[GUITARIX_INPUT2] = "Input2";
    prangehint[GUITARIX_INPUT2].HintDescriptor = 0;

    pdesc[GUITARIX_OUTPUT1] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
    pnames[GUITARIX_OUTPUT1] = "Output1";
    prangehint[GUITARIX_OUTPUT1].HintDescriptor = 0;

    pdesc[GUITARIX_OUTPUT2] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
    pnames[GUITARIX_OUTPUT2] = "Output2";
    prangehint[GUITARIX_OUTPUT2].HintDescriptor = 0;

    pdesc[GUITARIX_PRESET] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_PRESET] = "Preset";
    prangehint[GUITARIX_PRESET].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	LADSPA_HINT_INTEGER | LADSPA_HINT_DEFAULT_0;
    prangehint[GUITARIX_PRESET].LowerBound = 0;
    prangehint[GUITARIX_PRESET].UpperBound = 99;

    pdesc[GUITARIX_VOLUME] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_VOLUME] = "Level adj. (dB)";
    prangehint[GUITARIX_VOLUME].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	LADSPA_HINT_DEFAULT_0;
    prangehint[GUITARIX_VOLUME].LowerBound = -20;
    prangehint[GUITARIX_VOLUME].UpperBound = 20;

    pdesc[GUITARIX_NO_BUFFER] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_NO_BUFFER] = "No Buffer";
    prangehint[GUITARIX_NO_BUFFER].HintDescriptor =
	LADSPA_HINT_TOGGLED | LADSPA_HINT_DEFAULT_0;

    pdesc[GUITARIX_BUFFERSIZE] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_BUFFERSIZE] = "Buffersize";
    prangehint[GUITARIX_BUFFERSIZE].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	LADSPA_HINT_DEFAULT_0;
    prangehint[GUITARIX_BUFFERSIZE].LowerBound = 0;
    prangehint[GUITARIX_BUFFERSIZE].UpperBound = Convproc::MAXQUANT;

    pdesc[GUITARIX_NO_RT_MODE] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_NO_RT_MODE] = "Non-RT Mode";
    prangehint[GUITARIX_NO_RT_MODE].HintDescriptor =
	LADSPA_HINT_TOGGLED | LADSPA_HINT_DEFAULT_0;

    pdesc[GUITARIX_PRIORITY] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_PRIORITY] = "RT Priority";
    prangehint[GUITARIX_PRIORITY].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	LADSPA_HINT_INTEGER | LADSPA_HINT_DEFAULT_0;
    prangehint[GUITARIX_PRIORITY].LowerBound = 0;
    prangehint[GUITARIX_PRIORITY].UpperBound = 99;

    pdesc[GUITARIX_LATENCY] = LADSPA_PORT_OUTPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_LATENCY] = "latency"; // predefined name
    prangehint[GUITARIX_LATENCY].HintDescriptor = 0;

    for (int i = 0; i < GUITARIX_PARAM_COUNT; ++i) {
	pdesc[GUITARIX_PARAM+i] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
	pnames[GUITARIX_PARAM+i] = strdup(("Parameter " + gx_system::to_string(i+1)).c_str());
	prangehint[GUITARIX_PARAM+i].HintDescriptor =
	    LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	    LADSPA_HINT_DEFAULT_NONE;
	prangehint[GUITARIX_PARAM+i].LowerBound = 0;
	prangehint[GUITARIX_PARAM+i].UpperBound = ControlParameter::upper_bound;
    }

    UniqueID = 4070;
    Label = "guitarix-fx";
    Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
    Name = "Guitarix Stereo Fx";
    Maker = "Guitarix Team";
    Copyright = "GPL";
    PortCount = PORT_COUNT;
    PortDescriptors = pdesc;
    PortNames = pnames;
    PortRangeHints = prangehint;
    ImplementationData = 0;
    instantiate = instantiateGuitarix;
    connect_port = connectPortToGuitarix;
    activate = activateGuitarix;
    run = runGuitarix;
    run_adding = 0;
    set_run_adding_gain = 0;
    deactivate = 0;
    cleanup = cleanupGuitarix;
}

LadspaGuitarixStereo::LADSPA::~LADSPA() {
    for (int i = 0; i < GUITARIX_PARAM_COUNT; ++i) {
	free(const_cast<char*>(pnames[GUITARIX_PARAM+i]));
    }
}


/****************************************************************
 *                         ENTRY POINT                          *
 ****************************************************************/

/****************************************************************
 ** function ladspa_descriptor
 */

static void initBasicOptions() {
    static gx_system::BasicOptions options;
}

/* Return a descriptor of the requested plugin type. */
extern "C" __attribute__ ((visibility ("default")))
const LADSPA_Descriptor * ladspa_descriptor(unsigned long Index) {
    Glib::init();
    if (!Glib::thread_supported()) {
	Glib::thread_init();
    }
    static bool inited = 0;
    if (!inited) {
	inited = 1;
#if ENABLE_NLS
	bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
#endif
	initBasicOptions();
    }
    switch (Index) {
    case 0:
	return LadspaGuitarixMono::ladspa_descriptor();
    case 1:
	return LadspaGuitarixStereo::ladspa_descriptor();
    default:
	return 0;
    }
}


/****************************************************************
 ** test driver
 ** defined when not building as shared lib
 */

#ifndef PIC
int main() {
    const int count = 64;
    LADSPA_Data input[2][count], output[2][count];
    int in_idx = 0, out_idx = 0;
    const LADSPA_Descriptor * ladspa = ladspa_descriptor(0);
    LADSPA_Handle hand = ladspa->instantiate(ladspa, 48000);
    LADSPA_Data data[ladspa->PortCount];
    for (unsigned int i = 0; i < ladspa->PortCount; i++) {
	if (ladspa->PortDescriptors[i] & LADSPA_PORT_AUDIO) {
	    if (ladspa->PortDescriptors[i] & LADSPA_PORT_INPUT) {
		ladspa->connect_port(hand, i, input[in_idx++]);
	    } else {
		ladspa->connect_port(hand, i, output[out_idx++]);
	    }
	} else {
	    if (LADSPA_IS_HINT_DEFAULT_1(ladspa->PortRangeHints[i].HintDescriptor)) {
		data[i] = 1;
	    } else {
		data[i] = 0;
	    }
	    if (strcmp(ladspa->PortNames[i], "Buffersize") == 0) {
		//data[i] = 256;
	    }
	    ladspa->connect_port(hand, i, data+i);
	}
    }
    ladspa->activate(hand);
    for (int n = 0; n < 100; n++) {
	ladspa->run(hand, count);
    }
    ladspa->cleanup(hand);
    return 0;
}
#endif
