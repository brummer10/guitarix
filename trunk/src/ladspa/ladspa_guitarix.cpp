#include <stdlib.h>
#include <string.h>
#include <ladspa.h>
#include <iostream>
#include <jack/jack.h>
#include <jack/thread.h>

#include "engine.h"

#include "gx_faust_plugins.h"
#include "../plugins/pluginlib.h"

using namespace gx_engine;


enum {  // ladspa ports
    GUITARIX_INPUT,
    GUITARIX_OUTPUT,
    GUITARIX_PRESET,
    GUITARIX_BUFFERSIZE,
    GUITARIX_PRIORITY,
    GUITARIX_LATENCY,
    GUITARIX_BUFFERSIZE_OUT,
    GUITARIX_PRIORITY_OUT,
    GUITARIX_PARAM,
    GUITARIX_PARAM_COUNT = 3,
    PORT_COUNT = GUITARIX_PARAM + GUITARIX_PARAM_COUNT
};


/****************************************************************
 ** class ControlParameter
 */

class ControlParameter {
private:
    MidiControllerList::controller_array *midi_control;
    vector<midi_controller_list*> ctlr;
    LADSPA_Data * parameter_port[GUITARIX_PARAM_COUNT];
public:
    ControlParameter();
    ~ControlParameter();
    void set_port(unsigned int n, LADSPA_Data *p);
    void readJSON(gx_system::JsonParser &jp, ParamMap& param);
    void get_values();
};

ControlParameter::ControlParameter()
    : midi_control(0),
      ctlr(GUITARIX_PARAM_COUNT),
      parameter_port() {
}

ControlParameter::~ControlParameter() {
    delete midi_control;
}

void ControlParameter::set_port(unsigned int n, LADSPA_Data *p) {
    if (n < GUITARIX_PARAM_COUNT) {
	parameter_port[n] = p;
    } else {
	assert(false);
    }
}

void ControlParameter::readJSON(gx_system::JsonParser &jp, ParamMap& param) {
    //FIXME concurrency with get_values, design (ctlr size..)
    for (unsigned int i = 0; i < ctlr.size(); ++i) {
	ctlr[i] = 0;
    }
    delete midi_control;
    midi_control = MidiControllerList::create_controller_array();
    MidiControllerList::readJSON(jp, param, *midi_control);
    unsigned int n = 0;
    for (unsigned int i = 0; i < midi_control->size(); ++i) {
	midi_controller_list& cl = (*midi_control)[i];
	if (cl.empty()) {
	    continue;
	}
	ctlr[n++] = &cl;
	if (n >= ctlr.size()) {
	    break;
	}
    }
}

void ControlParameter::get_values() {
    for (unsigned int i = 0; i < ctlr.size(); ++i) {
	midi_controller_list *l = ctlr[i];
	if (!l) { //FIXME
	    break;
	}
        for (midi_controller_list::iterator n = l->begin(); n != l->end(); ++n) {
	    if (parameter_port[i]) {
		n->set(*parameter_port[i], 100);
	    }
	}
    }
}


/****************************************************************
 ** class PresetIO
 */

typedef vector<midi_controller_list*> ctlr_array;

class PresetIO: public gx_system::AbstractPresetIO {
private:
    GxJConvSettings jcset;
    ParamMap& param;
    ConvolverAdapter* convolver;
    ControlParameter& control_parameter;
    friend class StateIO;
public:
    PresetIO(ParamMap& param, ConvolverAdapter* convolver, ControlParameter& cp);
    ~PresetIO();
    void read_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&);
    void commit_preset();
    void write_preset(gx_system::JsonWriter& jw);
    void copy_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&, gx_system::JsonWriter &jw);
};

PresetIO::PresetIO(ParamMap& param_, ConvolverAdapter* convolver_, ControlParameter& cp)
    : param(param_),
      convolver(convolver_),
      control_parameter(cp) {
      }

PresetIO::~PresetIO() {
}

void PresetIO::read_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head) {
    jp.next(gx_system::JsonParser::begin_object);
    do {
        jp.next(gx_system::JsonParser::value_key);
        if (jp.current_value() == "engine") {
	    jp.next(gx_system::JsonParser::begin_object);
	    do {
		jp.next(gx_system::JsonParser::value_key);
		if (!param.hasId(jp.current_value())) {
#if 0   // lots of warnings
		    gx_system::gx_print_warning(
			_("recall settings"),
			_("unknown parameter: ")+jp.current_value());
#endif
		    jp.skip_object();
		    continue;
		}
		Parameter& p = param[jp.current_value()];
		p.readJSON_value(jp);
		p.setJSON_value();
	    } while (jp.peek() == gx_system::JsonParser::value_key);
	    jp.next(gx_system::JsonParser::end_object);
        } else if (jp.current_value() == "jconv") {
	    if (convolver) {
		gx_system::PathList sl;
		sl.add(string(getenv("HOME"))+"/.gx_head"); //FIXME
		sl.add(GX_SOUND_DIR1);
		jcset = GxJConvSettings();
		jcset.readJSON(jp, sl);
		convolver->jcset = jcset;
	    } else {
		jp.skip_object();
	    }
        } else if (jp.current_value() == "midi_controller") {
	    control_parameter.readJSON(jp, param);
        } else {
            gx_system::gx_print_warning(
		_("recall settings"),
		_("unknown preset section: ") + jp.current_value());
	    jp.skip_object();
        }
    } while (jp.peek() == gx_system::JsonParser::value_key);
    jp.next(gx_system::JsonParser::end_object);
}

void PresetIO::commit_preset() {}

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
    StateIO(ParamMap& param, ConvolverAdapter* convolver, ControlParameter& cp);
    ~StateIO();
    void read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&);
    void commit_state();
    void write_state(gx_system::JsonWriter &jw, bool preserve_preset);
};

StateIO::StateIO(ParamMap& param, ConvolverAdapter* convolver, ControlParameter& cp)
    : PresetIO(param, convolver, cp) {
}

StateIO::~StateIO() {
}

void StateIO::read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head) {
    do {
	jp.next(gx_system::JsonParser::value_string);
	if (jp.current_value() == "current_preset") {
	    read_preset(jp, head);
	} else if (jp.current_value() == "midi_controller") {
	    control_parameter.readJSON(jp, param);
	} else {
	    jp.skip_object();
	}
    } while (jp.peek() == gx_system::JsonParser::value_string);
}

void StateIO::commit_state() {}

void StateIO::write_state(gx_system::JsonWriter &jw, bool preserve_preset) {}


/****************************************************************
 ** class LadspaSettings
 */

class LadspaSettings: public gx_system::GxSettingsBase {
private:
    PresetIO preset_io;
    StateIO state_io;
public:
    LadspaSettings(string sfname, string presname,
		   ParamMap& param, ModuleSequencer&, ConvolverAdapter*, ControlParameter&);
    ~LadspaSettings();
    void load(int num);
};

LadspaSettings::LadspaSettings(string sfname, string presname, ParamMap& param,
			       ModuleSequencer& seq, ConvolverAdapter* convolver, ControlParameter& cp)
    : GxSettingsBase(seq),
      preset_io(param, convolver, cp),
      state_io(param, convolver, cp) {
    set_io(&state_io, &preset_io);
    set_statefilename(sfname);
    change_preset_file(presname);
}

LadspaSettings::~LadspaSettings() {
}

void LadspaSettings::load(int num) {
    if (num == 0) {
	gx_system::GxSettingsBase::load(state,"","");
    } else if (idx_in_preset(num-1)) {
	load_preset_by_idx(num-1);
    } else {
	gx_system::gx_print_error("preset loader", boost::format("no preset number %1%") % num);
    }
}


/****************************************************************
** misc. definitions
*/

namespace gx_jack {
// need to make guitarix engine a library...
void *GxJack::get_midi_buffer(jack_nframes_t nframes) { return 0; }
}

void UiBuilder::load(Plugin*) {}
void UiBuilder::load_glade(char const*) const {}


/****************************************************************
 ** class MonoEngine
 **
 ** ModuleSequencer contains the unused stereo chain. To make a
 ** better implementation we would need a more abstract engine
 ** object (e.g. for GxBaseSettings), the guitarix engine object
 ** files in a library and loader functions for mono modules,
 ** stereo modules and UI related modules.
 */

class MonoEngine: public ModuleSequencer {
private:
    gx_resample::BufferResampler resamp;
    void load_static_plugins();
public:
    // ModuleSelector's
    ModuleSelectorFromList crybaby;
    ModuleSelectorFromList tonestack;
    ModuleSelectorFromList ampstack;
    // internal audio modules
    NoiseGate noisegate;
    CabinetConvolver cabinet;
    ContrastConvolver contrast;
public:
    MonoEngine(const string& plugin_dir, ParamMap& param, ParameterGroups& groups);
    ~MonoEngine();
};

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
    0
};

static plugindef_creator builtin_amp_plugins[] = {
    gx_amps::gxamp::plugin,
    gx_amps::gxamp3::plugin,
    gx_amps::gxamp14::plugin,
    gx_amps::gxamp10::plugin,

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

MonoEngine::MonoEngine(const string& plugin_dir, ParamMap& param, ParameterGroups& groups)
    : ModuleSequencer(),
      resamp(),
      // ModuleSelector's
      crybaby(
	  *this, ui, "crybaby", N_("Crybaby"), builtin_crybaby_plugins,
	  "crybaby.autowah", _("select"), 0, PGN_POST_PRE),
      tonestack(
	  *this, ui, "amp.tonestack", N_("Tonestack"),
	  builtin_tonestack_plugins, "amp.tonestack.select",
	  _("select"), 0, PGN_POST_PRE),
      ampstack(
	  *this, ui, "ampstack", "?Tube", builtin_amp_plugins,
	  "tube.select", _("select"), ampstack_groups),
      // internal audio modules
      noisegate(),
      cabinet(*this, resamp),
      contrast(*this, resamp) {

    load_static_plugins();

    // loaded from shared libs
    if (!plugin_dir.empty()) {
	pluginlist.load_from_path(plugin_dir, PLUGIN_POS_RACK);
    }

    // selector objects to switch "alternative" modules
    add_selector(ampstack);
    add_selector(crybaby);
    add_selector(tonestack);

    registerParameter(param, groups);

#ifndef NDEBUG
    pluginlist.printlist();
#endif
}

MonoEngine::~MonoEngine() {
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
    pl.add(gx_effects::gx_ampout::plugin(),       PLUGIN_POS_END, PGN_GUI|PGN_POST);
    pl.add(&contrast.plugin,                      PLUGIN_POS_END, PGN_GUI|PGN_POST);
    pl.add(&noisegate.outputgate,                 PLUGIN_POS_END, PGN_POST);

    // dynamic rack modules
    // builtin 
    pl.add(builtin_crybaby_plugins,               PLUGIN_POS_RACK, PGN_ALTERNATIVE);
    pl.add(builtin_tonestack_plugins,             PLUGIN_POS_RACK, PGN_ALTERNATIVE);

    // mono
    pl.add(gx_effects::low_high_pass::plugin(),   PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::selecteq::plugin(),        PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&crybaby.plugin,                       PLUGIN_POS_RACK, PGN_GUI);
    pl.add(gx_effects::gx_distortion::plugin(),   PLUGIN_POS_RACK, PGN_GUI);
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
    pl.add(gx_effects::gx_feedback::plugin(),     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&tonestack.plugin,                     PLUGIN_POS_RACK, PGN_GUI);
    pl.add(&cabinet.plugin,                       PLUGIN_POS_RACK, PGN_GUI);
}


/****************************************************************
 ** class ReBuffer
 */

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
    bool is_active(int bufsize);
    int get_count() { return buffer_size; }
    LADSPA_Data *get_input() { return in_buffer; }
    LADSPA_Data *get_output() { return out_buffer; }
    bool put();
    void set(int cnt, LADSPA_Data *input_buffer, LADSPA_Data *output_buffer);
    void finish();
};

ReBuffer::ReBuffer()
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

ReBuffer::~ReBuffer() {
    delete[] in_buffer;
    delete[] out_buffer;
}

void ReBuffer::set(int cnt, LADSPA_Data *input_buffer, LADSPA_Data *output_buffer) {
    in_block_index = 0;
    out_block_index = 0;
    block_size = cnt;
    in_block = input_buffer;
    out_block = output_buffer;
}

bool ReBuffer::put() {
    int n = min(buffer_size-out_buffer_index, block_size-in_block_index);
    if (n) {
	// copy values from out buffer
	copy(out_block+out_block_index, out_buffer+out_buffer_index, n);
	out_block_index += n;
	out_buffer_index += n;
    }
    n = min(buffer_size - in_buffer_index, block_size - in_block_index);
    if (n) {
	// copy value to in buffer
	copy(in_buffer+in_buffer_index, in_block+in_block_index, n);
	in_buffer_index += n;
	in_block_index += n;
    }
    if (in_buffer_index == buffer_size) {
	in_buffer_index = 0;
	out_buffer_index = 0;
	return true;
    }
    return false;
}

bool ReBuffer::is_active(int bufsize) {
    if (bufsize) {
	if (bufsize != buffer_size) {
	    delete[] in_buffer;
	    in_buffer = new LADSPA_Data[bufsize];
	    delete[] out_buffer;
	    out_buffer = new LADSPA_Data[bufsize];
	    buffer_size = bufsize;
	    memset(out_buffer, 0, sizeof(out_buffer));
	    in_buffer_index = 0;
	    out_buffer_index = 1;
	}
	return true;
    } else if (buffer_size) {
	delete[] in_buffer;
	in_buffer = 0;
	delete[] out_buffer;
	out_buffer = 0;
	buffer_size = 0;
	return false;
    }
    return false;
}


/****************************************************************
 ** class LadspaGuitarix
 */

class PresetLoader;

class LadspaGuitarix {
private:
    friend class PresetLoader;
    ReBuffer rebuffer;
    unsigned long SampleRate;
    unsigned long SampleCount;
    int preset_num;
    int next_preset_num;
    int priority;
    ControlParameter control_parameter;
    LADSPA_Data * input_buffer;
    LADSPA_Data * output_buffer;
    LADSPA_Data * preset_num_port;
    LADSPA_Data * buffersize_port;
    LADSPA_Data * priority_port;
    LADSPA_Data * latency_port;
    LADSPA_Data * buffersize_out;
    LADSPA_Data * priority_out;
    ParamMap param;
    MonoEngine engine;
    LadspaSettings settings;
    void check_preset();
    void load(int num) { settings.load(num); }
    LadspaGuitarix(unsigned long sr);
    ~LadspaGuitarix();
public:
    static LADSPA_Handle instantiateGuitarix(const LADSPA_Descriptor * Descriptor,
					     unsigned long SampleRate);
    static void activateGuitarix(LADSPA_Handle Instance);
    static void connectPortToGuitarix(LADSPA_Handle Instance, unsigned long Port,
				      LADSPA_Data *DataLocation);
    static void runGuitarix(LADSPA_Handle Instance, unsigned long SampleCount);
    static void cleanupGuitarix(LADSPA_Handle Instance);
};


/****************************************************************
 ** class PresetLoader
 */

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
    static void create();
    static void destroy();
    static void add_instance(LadspaGuitarix* i);
    static void remove_instance(LadspaGuitarix* i);
    static void preset_change();
};

sem_t PresetLoader::created_sem;
Glib::Thread *PresetLoader::thread = 0;
PresetLoader *PresetLoader::instance = 0;


PresetLoader::PresetLoader()
    : ladspa_instances(),
      instance_mutex(),
      mainloop(Glib::MainLoop::create()),
      new_preset() {
}

PresetLoader::~PresetLoader() {
}

void PresetLoader::destroy() {
    assert(instance != 0);
    instance->mainloop->quit();
    instance = 0;
    thread->join();
    thread = 0;
}

void PresetLoader::run_mainloop() {
    instance = new PresetLoader();
    instance->new_preset.connect(sigc::mem_fun(*instance, &PresetLoader::load_presets));
    sem_post(&instance->created_sem);
    instance->mainloop->run();
    delete instance;
}

void PresetLoader::load_presets() {
    boost::mutex::scoped_lock lock(instance_mutex);
    for (list<LadspaGuitarix*>::iterator i = ladspa_instances.begin(); i != ladspa_instances.end(); ++i) {
	LadspaGuitarix& lg = **i;
	int num = g_atomic_int_get(&(lg.next_preset_num));
	if (num == lg.preset_num) {
	    continue;
	}
	lg.preset_num = num;
	lg.load(num);
    }
}

void PresetLoader::create() {
    assert(instance == 0);
    sem_init(&created_sem, 0, 0);
    thread = Glib::Thread::create(sigc::ptr_fun(run_mainloop), true);
    while (sem_wait(&created_sem) == EINTR);
    assert(instance);
}

void PresetLoader::preset_change() {
    assert(instance);
    instance->new_preset();
}

void PresetLoader::add_instance(LadspaGuitarix* i) {
    if (!instance) {
	create();
    }
    boost::mutex::scoped_lock lock(instance->instance_mutex);
    instance->ladspa_instances.push_back(i);
}

void PresetLoader::remove_instance(LadspaGuitarix* i) {
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
 ** LadspaGuitarix implementation
 */

LadspaGuitarix::LadspaGuitarix(unsigned long sr)
    : rebuffer(),
      SampleRate(sr),
      SampleCount(),
      preset_num(-1),
      next_preset_num(0),
      priority(-2),  // out-of-range value
      control_parameter(),
      input_buffer(),
      output_buffer(),
      preset_num_port(),
      buffersize_port(),
      priority_port(),
      latency_port(),
      buffersize_out(),
      priority_out(),
      param(),
      engine("", param, get_group_table()),
      settings(string(getenv("HOME"))+"/.gx_head/gx_head_rc",
	       string(getenv("HOME"))+"/.gx_head/gx_headpre_rc",
	       param, engine, 0, control_parameter) {
}

LadspaGuitarix::~LadspaGuitarix() {
    PresetLoader::remove_instance(this);
}

void LadspaGuitarix::activateGuitarix(LADSPA_Handle Instance) {
    LadspaGuitarix& self = *static_cast<LadspaGuitarix*>(Instance);
    PresetLoader::add_instance(&self);
    jack_status_t jackstat; // connecting to jack is just a hack for testing
    jack_client_t *client = jack_client_open("guitarix-test", JackNoStartServer, &jackstat);
    if (client) {
	self.engine.init(jack_get_sample_rate(client), jack_get_buffer_size(client),
			 SCHED_FIFO, jack_client_real_time_priority(client));
	jack_client_close(client);
    } else {
	self.engine.set_buffersize(64);
	self.engine.set_samplerate(self.SampleRate);
    }
    self.param.set_init_values();
    self.check_preset();
    self.engine.clear_stateflag(ModuleSequencer::SF_INITIALIZING);
    self.engine.stereo_chain.set_stopped(true);
}

void LadspaGuitarix::check_preset() {
    if (!preset_num_port) {
	return;
    }
    int num = *preset_num_port;
    if (next_preset_num == num) {
	return;
    }
    g_atomic_pointer_set(&next_preset_num, num);
    PresetLoader::preset_change();
}

void LadspaGuitarix::runGuitarix(LADSPA_Handle Instance, unsigned long SampleCount) {
    LadspaGuitarix& self = *static_cast<LadspaGuitarix*>(Instance);
    int policy, prio = -1;
    struct sched_param sp;
    if (pthread_getschedparam(pthread_self(), &policy, &sp) == 0) {
	if (policy == SCHED_FIFO) {
	    prio = sp.sched_priority;
	}
    }
    if (prio != self.priority) {
	self.priority = prio;
	*self.priority_out = prio;
	//FIXME restart convolver?
    }
    if (SampleCount != self.SampleCount) {
	AVOIDDENORMALS;
	self.engine.set_buffersize(SampleCount);
	self.SampleCount = SampleCount;
	*self.buffersize_out = 1 << (g_bit_storage(SampleCount)-1);
    }
    self.check_preset();
    self.control_parameter.get_values();
    if (self.rebuffer.is_active(static_cast<unsigned int>(*self.buffersize_port))) {
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

void LadspaGuitarix::connectPortToGuitarix(
    LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation) {
    LadspaGuitarix *self = static_cast<LadspaGuitarix*>(Instance);
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
    case GUITARIX_BUFFERSIZE:
	self->buffersize_port = DataLocation;
	break;
    case GUITARIX_PRIORITY:
	self->priority_port = DataLocation;
	break;
    case GUITARIX_LATENCY:
	self->latency_port = DataLocation;
	*self->latency_port = 0;
	break;
    case GUITARIX_BUFFERSIZE_OUT:
	self->buffersize_out = DataLocation;
	*self->buffersize_out = 0;
	break;
    case GUITARIX_PRIORITY_OUT:
	self->priority_out = DataLocation;
	*self->priority_out = 0;
	break;
    default:
	self->control_parameter.set_port(Port-GUITARIX_PARAM, DataLocation);
	break;
    }
}

LADSPA_Handle LadspaGuitarix::instantiateGuitarix(
    const LADSPA_Descriptor * Descriptor, unsigned long SampleRate) {
    return new LadspaGuitarix(SampleRate);
}

void LadspaGuitarix::cleanupGuitarix(LADSPA_Handle Instance) {
    delete static_cast<LadspaGuitarix*>(Instance);
}


/****************************************************************
 ** class LADSPA
 */

class LADSPA: public LADSPA_Descriptor { 
    LADSPA_PortDescriptor pdesc[PORT_COUNT];
    const char *pnames[PORT_COUNT];
    LADSPA_PortRangeHint prangehint[PORT_COUNT];
public:
    LADSPA();
    ~LADSPA();
};

static void log_terminal(const string& msg, gx_system::GxMsgType tp, bool plugged) {
    const char *t;
    switch (tp) {
    case gx_system::kInfo:    t = "I"; break;
    case gx_system::kWarning: t = "W"; break;
    case gx_system::kError:   t = "E"; break;
    default:       t = "?"; break;
    }
    if (!plugged) {
	cerr << t << " " << msg << endl;
    }
}

LADSPA::LADSPA()
    : LADSPA_Descriptor() {
    //Glib::thread_init();
    Glib::init();
    gx_system::Logger& log(gx_system::Logger::get_logger());
    log.signal_message().connect(sigc::ptr_fun(log_terminal));
    log.unplug_queue();

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
    prangehint[GUITARIX_PRESET].LowerBound = 99;

    pdesc[GUITARIX_BUFFERSIZE] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_BUFFERSIZE] = "Buffersize";
    prangehint[GUITARIX_BUFFERSIZE].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	LADSPA_HINT_INTEGER | LADSPA_HINT_DEFAULT_0;
    prangehint[GUITARIX_BUFFERSIZE].LowerBound = -1;
    prangehint[GUITARIX_BUFFERSIZE].UpperBound = 1024;

    pdesc[GUITARIX_PRIORITY] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_PRIORITY] = "RT Priority";
    prangehint[GUITARIX_PRIORITY].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	LADSPA_HINT_INTEGER | LADSPA_HINT_DEFAULT_0;
    prangehint[GUITARIX_PRIORITY].LowerBound = -1;
    prangehint[GUITARIX_PRIORITY].UpperBound = 99;

    pdesc[GUITARIX_LATENCY] = LADSPA_PORT_OUTPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_LATENCY] = "latency";
    prangehint[GUITARIX_LATENCY].HintDescriptor = 0;

    pdesc[GUITARIX_BUFFERSIZE_OUT] = LADSPA_PORT_OUTPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_BUFFERSIZE_OUT] = "Show Buffersize";
    prangehint[GUITARIX_BUFFERSIZE_OUT].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_INTEGER;
    prangehint[GUITARIX_BUFFERSIZE_OUT].LowerBound = -1;

    pdesc[GUITARIX_PRIORITY_OUT] = LADSPA_PORT_OUTPUT | LADSPA_PORT_CONTROL;
    pnames[GUITARIX_PRIORITY_OUT] = "Show RT Priority";
    prangehint[GUITARIX_PRIORITY_OUT].HintDescriptor =
	LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	LADSPA_HINT_INTEGER;
    prangehint[GUITARIX_PRIORITY_OUT].LowerBound = -1;
    prangehint[GUITARIX_PRIORITY_OUT].UpperBound = 99;

    for (int i = 0; i < GUITARIX_PARAM_COUNT; ++i) {
	pdesc[GUITARIX_PARAM+i] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
	pnames[GUITARIX_PARAM+i] = strdup(("parameter " + gx_system::to_string(i)).c_str());
	prangehint[GUITARIX_PARAM+i].HintDescriptor =
	    LADSPA_HINT_BOUNDED_BELOW | LADSPA_HINT_BOUNDED_ABOVE |
	    LADSPA_HINT_DEFAULT_NONE;
	prangehint[GUITARIX_PARAM+i].LowerBound = 0;
	prangehint[GUITARIX_PARAM+i].UpperBound = 100;
    }

    UniqueID = 4069;
    Label = "guitarix";
    Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
    Name = "Guitarix";
    Maker = "Guitarix Team";
    Copyright = "GPL";
    PortCount = PORT_COUNT;
    PortDescriptors = pdesc;
    PortNames = pnames;
    PortRangeHints = prangehint;
    ImplementationData = 0;
    instantiate = LadspaGuitarix::instantiateGuitarix;
    connect_port = LadspaGuitarix::connectPortToGuitarix;
    activate = LadspaGuitarix::activateGuitarix;
    run = LadspaGuitarix::runGuitarix;
    run_adding = 0;
    set_run_adding_gain = 0;
    deactivate = 0;
    cleanup = LadspaGuitarix::cleanupGuitarix;
}

LADSPA::~LADSPA() {
    for (int i = 0; i < GUITARIX_PARAM_COUNT; ++i) {
	free(const_cast<char*>(pnames[GUITARIX_PARAM+i]));
    }
}

/****************************************************************
 ** function ladspa_descriptor
 */

/* Return a descriptor of the requested plugin type. */
const LADSPA_Descriptor * ladspa_descriptor(unsigned long Index) {
    static LADSPA ladspa_desc;
    if (Index != 0) {
	return NULL;
    }
    return &ladspa_desc;
}


/****************************************************************
 ** test driver
 */

#if 0
int main() {
    const LADSPA_Descriptor * ladspa = ladspa_descriptor(0);
    LADSPA_Handle hand = ladspa->instantiate(ladspa, 48000);
    //printf("%p\n", hand);
    int count = 64;
    LADSPA_Data input[count], output[count];
    ladspa->connect_port(hand, 0, input);
    ladspa->connect_port(hand, 1, output);
    LADSPA_Data data[ladspa->PortCount-2];
    for (unsigned int i = 2; i < ladspa->PortCount; i++) {
	data[i] = 0;
	if (i == GUITARIX_PRESET) {
	    data[GUITARIX_PRESET] = 1;
	}
	ladspa->connect_port(hand, i, data+i);
    }
    ladspa->activate(hand);
    for (int n = 0; n < 10000; n++) {
	ladspa->run(hand, count);
    }
    //printf("%f %f\n", data[GUITARIX_BUFFERSIZE_OUT], data[GUITARIX_PRIORITY_OUT]);
    ladspa->cleanup(hand);
    return 0;
}
#endif
