#include <stdlib.h>
#include <string.h>
#include <ladspa.h>
#include <iostream>
#include <jack/jack.h>
#include <jack/thread.h>

#include "engine.h"

using namespace gx_engine;

/****************************************************************
 ** class StateIO
 */

typedef vector<midi_controller_list*> ctlr_array;

class StateIO: public gx_system::AbstractStateIO {
public:
    GxJConvSettings jcset;
    ParamMap& param;
    MidiControllerList::controller_array *midi_control;
    ctlr_array& ctlr;
    StateIO(ParamMap& param, MidiControllerList::controller_array *midi_control,
	    ctlr_array& ctlr);
    ~StateIO();
    void read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&);
    void commit_state();
    void write_state(gx_system::JsonWriter &jw, bool preserve_preset);
};

StateIO::StateIO(
    ParamMap& param_, MidiControllerList::controller_array *midi_control_,
    ctlr_array& ctlr_)
    : param(param_),
      midi_control(midi_control_),
      ctlr(ctlr_) {
}

StateIO::~StateIO() {
}

void StateIO::read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&) {
    do {
	jp.next(gx_system::JsonParser::value_string);
	if (jp.current_value() == "current_preset") {
	    jp.next(gx_system::JsonParser::begin_object);
	    do {
		jp.next(gx_system::JsonParser::value_key);
		if (jp.current_value() == "engine") {
		    jp.next(gx_system::JsonParser::begin_object);
		    do {
			jp.next(gx_system::JsonParser::value_key);
			if (!param.hasId(jp.current_value())) {
			    gx_system::gx_print_warning(
				_("recall settings"),
				_("unknown parameter: ")+jp.current_value());
			    jp.skip_object();
			    continue;
			}
			Parameter& p = param[jp.current_value()];
			p.readJSON_value(jp);
			p.setJSON_value();
		    } while (jp.peek() == gx_system::JsonParser::value_key);
		    jp.next(gx_system::JsonParser::end_object);
		} else if (jp.current_value() == "jconv") {
		    gx_system::PathList sl;
		    sl.add(string(getenv("HOME"))+"/.gx_head"); //FIXME
		    sl.add(GX_SOUND_DIR1);
		    jcset = GxJConvSettings();
		    jcset.readJSON(jp, sl);
		} else {
		    jp.skip_object();
		}
	    } while (jp.peek() == gx_system::JsonParser::value_key);
	    jp.next(gx_system::JsonParser::end_object);
	} else if (jp.current_value() == "midi_controller") {
	    //FIXME concurrency, design (ctlr size..)
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
    StateIO state_io;
    GxEngine& engine;
public:
    LadspaSettings(string sfname, ParamMap& param, GxEngine&,
		   MidiControllerList::controller_array*, ctlr_array&);
    ~LadspaSettings();
    void load();
};

LadspaSettings::LadspaSettings(string sfname, ParamMap& param, GxEngine& engine_,
			       MidiControllerList::controller_array *midi_control,
			       ctlr_array& ctlr)
    : GxSettingsBase(engine_),
      state_io(param, midi_control, ctlr),
      engine(engine_) {
    set_io(&state_io, 0);
    set_statefilename(sfname);
}

LadspaSettings::~LadspaSettings() {
}

void LadspaSettings::load() {
    gx_system::GxSettingsBase::load(state,"","");
    engine.convolver.jcset = state_io.jcset;
}


/****************************************************************
** misc. definitions
*/

namespace gx_jack {
void *GxJack::get_midi_buffer(jack_nframes_t nframes) { return 0; }
}

void UiBuilder::load(Plugin*) {}
void UiBuilder::load_glade(char const*) const {}


/****************************************************************
 ** class LadspaGuitarix
 */

enum {
    GUITARIX_INPUT,
    GUITARIX_OUTPUT,
    GUITARIX_PRESET,
    GUITARIX_BUFFERSIZE,
    GUITARIX_PRIORITY,
    GUITARIX_LATENCY,
    GUITARIX_BUFFERSIZE_OUT,
    GUITARIX_PRIORITY_OUT,
    GUITARIX_PARAM,
    GUITARIX_PARAM_COUNT = 3,  // max 9, see impl.
    PORT_COUNT = GUITARIX_PARAM + GUITARIX_PARAM_COUNT
};

class LadspaGuitarix {
private:
    unsigned long SampleRate;
    unsigned long SampleCount;
    int preset_num;
    int priority;
    MidiControllerList::controller_array *midi_control;
    vector<midi_controller_list*> ctlr;
    LADSPA_Data * input_buffer;
    LADSPA_Data * output_buffer;
    LADSPA_Data * preset_num_port;
    LADSPA_Data * buffersize_port;
    LADSPA_Data * priority_port;
    LADSPA_Data * latency_port;
    LADSPA_Data * buffersize_out;
    LADSPA_Data * priority_out;
    LADSPA_Data * parameter_port[GUITARIX_PARAM_COUNT];
    ParamMap param;
    GxEngine engine;
    LadspaSettings settings;
    LadspaGuitarix(unsigned long sr);
    ~LadspaGuitarix();
public:
    static LADSPA_Handle instantiateGuitarix(const LADSPA_Descriptor * Descriptor,
					     unsigned long SampleRate);
    static void connectPortToGuitarix(LADSPA_Handle Instance, unsigned long Port,
				      LADSPA_Data *DataLocation);
    static void runGuitarix(LADSPA_Handle Instance, unsigned long SampleCount);
    static void cleanupGuitarix(LADSPA_Handle Instance);
};

LadspaGuitarix::LadspaGuitarix(unsigned long sr)
    : SampleRate(sr),
      SampleCount(),
      preset_num(0),
      priority(-1),
      midi_control(0),
      ctlr(GUITARIX_PARAM_COUNT),
      input_buffer(),
      output_buffer(),
      preset_num_port(),
      buffersize_port(),
      priority_port(),
      latency_port(),
      buffersize_out(),
      priority_out(),
      parameter_port(),
      param(),
      engine("", param, get_group_table()),
      settings(string(getenv("HOME"))+"/.gx_head/gx_head_rc", param, engine,
	       midi_control, ctlr) {
    jack_status_t jackstat; // connecting to jack is just a hack for testing
    jack_client_t *client = jack_client_open("guitarix-test", JackNoStartServer, &jackstat);
    if (client) {
	engine.init(jack_get_sample_rate(client), jack_get_buffer_size(client),
		    SCHED_FIFO, jack_client_real_time_priority(client));
	jack_client_close(client);
    }
    //engine.set_samplerate(sr);
    settings.load();
    engine.clear_stateflag(GxEngine::SF_INITIALIZING);
}

LadspaGuitarix::~LadspaGuitarix() {
    delete midi_control;
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
    for (unsigned int i = 0; i < self.ctlr.size(); ++i) {
	midi_controller_list *l = self.ctlr[i];
	if (!l) { //FIXME
	    break;
	}
        for (midi_controller_list::iterator n = l->begin(); n != l->end(); ++n) {
            n->set(*self.parameter_port[i], 100);
	}
    }
    self.engine.mono_chain.process(
	SampleCount, self.input_buffer, self.output_buffer);
}

void LadspaGuitarix::connectPortToGuitarix(
    LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation) {
    LadspaGuitarix *self = static_cast<LadspaGuitarix*>(Instance);
    unsigned int n;
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
	n = Port-GUITARIX_PARAM;
	if (n < GUITARIX_PARAM_COUNT) {
	    self->parameter_port[n] = DataLocation;
	}
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

    char p[] = "parameter _"; // only works for max 9 parameters!!
    int n = strlen(p);
    for (int i = 0; i < GUITARIX_PARAM_COUNT; ++i) {
	pdesc[GUITARIX_PARAM+i] = LADSPA_PORT_INPUT | LADSPA_PORT_CONTROL;
	char *q = new char[n+1];
	strcpy(q, p);
	q[n-1] = '1' + i;
	pnames[GUITARIX_PARAM+i] = q;
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
    activate = 0;
    run = LadspaGuitarix::runGuitarix;
    run_adding = 0;
    set_run_adding_gain = 0;
    deactivate = 0;
    cleanup = LadspaGuitarix::cleanupGuitarix;
}

LADSPA::~LADSPA() {
    for (int i = 0; i < GUITARIX_PARAM_COUNT; ++i) {
	delete[] pnames[GUITARIX_PARAM+i];
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
    printf("%p\n", hand);
    return 0;
}
#endif
