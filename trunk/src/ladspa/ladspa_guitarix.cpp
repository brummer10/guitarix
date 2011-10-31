#include <stdlib.h>
#include <string.h>
#include <ladspa.h>
#include <iostream>
#include <jack/jack.h>
#include <jack/thread.h>

#include "engine.h"

/****************************************************************
 ** class StateIO
 */

class StateIO: public gx_system::AbstractStateIO {
public:
    gx_engine::GxJConvSettings jcset;
    StateIO();
    ~StateIO();
    void read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader&);
    void commit_state();
    void write_state(gx_system::JsonWriter &jw, bool preserve_preset);
};

StateIO::StateIO() {}
StateIO::~StateIO() {}

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
			if (!gx_gui::parameter_map.hasId(jp.current_value())) {
			    gx_system::gx_print_warning(
				_("recall settings"),
				_("unknown parameter: ")+jp.current_value());
			    jp.skip_object();
			    continue;
			}
			gx_gui::Parameter& param = gx_gui::parameter_map[jp.current_value()];
			param.readJSON_value(jp);
			param.setJSON_value();
		    } while (jp.peek() == gx_system::JsonParser::value_key);
		    jp.next(gx_system::JsonParser::end_object);
		} else if (jp.current_value() == "jconv") {
		    gx_system::PathList sl;
		    sl.add(string(getenv("HOME"))+"/.gx_head"); //FIXME
		    sl.add(GX_SOUND_DIR1);
		    jcset = gx_engine::GxJConvSettings();
		    jcset.readJSON(jp, sl);
		} else {
		    jp.skip_object();
		}
	    } while (jp.peek() == gx_system::JsonParser::value_key);
	    jp.next(gx_system::JsonParser::end_object);
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
    gx_engine::GxEngine& engine;
public:
    LadspaSettings(string sfname, gx_engine::GxEngine&);
    ~LadspaSettings();
    void load();
};

LadspaSettings::LadspaSettings(string sfname, gx_engine::GxEngine& engine_)
    : GxSettingsBase(engine_),
      state_io(),
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
 ** class LadspaGuitarix
 */

class LadspaGuitarix {
private:
    unsigned long SampleRate;
    unsigned long SampleCount;   
    LADSPA_Data * input_buffer;
    LADSPA_Data * output_buffer;
    gx_engine::GxEngine engine;
    LadspaSettings settings;
public:
    LadspaGuitarix(unsigned long sr);
    ~LadspaGuitarix();
    static void connectPortToGuitarix(
	LADSPA_Handle Instance, unsigned long Port, LADSPA_Data * DataLocation);
    static void runGuitarix(LADSPA_Handle Instance, unsigned long SampleCount);
};

LadspaGuitarix::LadspaGuitarix(unsigned long sr)
    : SampleRate(sr),
      SampleCount(),
      input_buffer(),
      output_buffer(),
      engine("", gx_gui::get_group_table()),
      settings(string(getenv("HOME"))+"/.gx_head/gx_head_rc", engine) {
    jack_status_t jackstat; // connecting to jack is just a hack for testing
    jack_client_t *client = jack_client_open("guitarix-test", JackNoStartServer, &jackstat);
    if (client) {
	engine.init(jack_get_sample_rate(client), jack_get_buffer_size(client),
		    SCHED_FIFO, jack_client_real_time_priority(client));
	jack_client_close(client);
    }
    //engine.set_samplerate(sr);
    settings.load();
    engine.clear_stateflag(gx_engine::GxEngine::SF_INITIALIZING);
}

LadspaGuitarix::~LadspaGuitarix() {
}

/*
** some dummy definitions
*/

namespace gx_jack {
void *GxJack::get_midi_buffer(jack_nframes_t nframes) { return 0; }
}

void UiBuilder::load(gx_engine::Plugin*) {}
void UiBuilder::load_glade(char const*) const {}


/* Run a delay line instance for a block of SampleCount samples. */
void LadspaGuitarix::runGuitarix(LADSPA_Handle Instance, unsigned long SampleCount) {
    LadspaGuitarix& self = *static_cast<LadspaGuitarix*>(Instance);
    if (SampleCount != self.SampleCount) {
	AVOIDDENORMALS
	self.engine.set_buffersize(SampleCount);
	self.SampleCount = SampleCount;
    }
    self.engine.mono_chain.process(
	SampleCount, self.input_buffer, self.output_buffer);
}


/****************************************************************
 *                      LADSPA Interface                        *
 ****************************************************************/

static void log_terminal(const string& msg, gx_system::GxMsgType tp) {
    const char *t;
    switch (tp) {
    case gx_system::kInfo:    t = "I"; break;
    case gx_system::kWarning: t = "W"; break;
    case gx_system::kError:   t = "E"; break;
    default:       t = "?"; break;
    }
    cerr << t << " " << msg << endl;
}

static LadspaGuitarix *instance = 0;

/* Construct a new plugin instance. */
LADSPA_Handle instantiateGuitarix(
    const LADSPA_Descriptor * Descriptor, unsigned long SampleRate) {
    static bool seen = false;
    if (!seen) {
	gx_system::Logger::get_logger().signal_message().connect(
	    sigc::ptr_fun(log_terminal));
	seen = true;
    }
    if (instance) {
    	return instance;
    }
    instance = new LadspaGuitarix(SampleRate);
    return instance;
}

/*****************************************************************************/

/* Throw away a simple delay line. */
void cleanupGuitarix(LADSPA_Handle Instance) {
    //delete static_cast<LadspaGuitarix*>(Instance);
}

/*****************************************************************************/

#define GUITARIX_INPUT   0
#define GUITARIX_OUTPUT 1

/* Connect a port to a data location. */
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
    }
}

/*****************************************************************************/

LADSPA_Descriptor * g_psDescriptor;

/*****************************************************************************/

/* _init() is called automatically when the plugin library is first
   loaded. */
void _init() {
    char ** pcPortNames;
    LADSPA_PortDescriptor *piPortDescriptors;
    LADSPA_PortRangeHint *psPortRangeHints;

    g_psDescriptor = (LADSPA_Descriptor *)malloc(sizeof(LADSPA_Descriptor));
    if (g_psDescriptor) {
	g_psDescriptor->UniqueID = 745;
	g_psDescriptor->Label = strdup("guitarix");
	g_psDescriptor->Properties = LADSPA_PROPERTY_HARD_RT_CAPABLE;
	g_psDescriptor->Name = strdup("Guitarix");
	g_psDescriptor->Maker = strdup("Guitarix Team");
	g_psDescriptor->Copyright = strdup("None");
	g_psDescriptor->PortCount = 2;
	piPortDescriptors = (LADSPA_PortDescriptor *)calloc(2, sizeof(LADSPA_PortDescriptor));
	g_psDescriptor->PortDescriptors = (const LADSPA_PortDescriptor *)piPortDescriptors;
	piPortDescriptors[GUITARIX_INPUT] =   LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO;
	piPortDescriptors[GUITARIX_OUTPUT] = LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO;
	pcPortNames = (char **)calloc(2, sizeof(char *));
	g_psDescriptor->PortNames = (const char **)pcPortNames;
	pcPortNames[GUITARIX_INPUT] = strdup("Input");
	pcPortNames[GUITARIX_OUTPUT] = strdup("Output");
	psPortRangeHints = ((LADSPA_PortRangeHint *)calloc(2, sizeof(LADSPA_PortRangeHint)));
	psPortRangeHints[GUITARIX_INPUT].HintDescriptor = 0;
	psPortRangeHints[GUITARIX_OUTPUT].HintDescriptor = 0;
	g_psDescriptor->PortRangeHints = (const LADSPA_PortRangeHint *)psPortRangeHints;
	g_psDescriptor->instantiate = instantiateGuitarix;
	g_psDescriptor->connect_port = LadspaGuitarix::connectPortToGuitarix;
	g_psDescriptor->activate = 0;
	g_psDescriptor->run = LadspaGuitarix::runGuitarix;
	g_psDescriptor->run_adding = 0;
	g_psDescriptor->set_run_adding_gain = 0;
	g_psDescriptor->deactivate = 0;
	g_psDescriptor->cleanup = cleanupGuitarix;
    }
}

/*****************************************************************************/

/* _fini() is called automatically when the library is unloaded. */
void _fini() {
    if (g_psDescriptor) {
	free((char *)g_psDescriptor->Label);
	free((char *)g_psDescriptor->Name);
	free((char *)g_psDescriptor->Maker);
	free((char *)g_psDescriptor->Copyright);
	free((LADSPA_PortDescriptor *)g_psDescriptor->PortDescriptors);
	for (unsigned long lIndex = 0; lIndex < g_psDescriptor->PortCount; lIndex++)
	    free((char *)(g_psDescriptor->PortNames[lIndex]));
	free((char **)g_psDescriptor->PortNames);
	free((LADSPA_PortRangeHint *)g_psDescriptor->PortRangeHints);
	free(g_psDescriptor);
    }
}
  
/*****************************************************************************/

/* Return a descriptor of the requested plugin type. */
const LADSPA_Descriptor * ladspa_descriptor(unsigned long Index) {
    _init();
    if (Index != 0) {
	return NULL;
    }
    return g_psDescriptor;
}

/*****************************************************************************/
