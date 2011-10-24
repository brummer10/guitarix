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
 *    This is part of the Guitarix Audio Engine
 *
 *
 *
 * --------------------------------------------------------------------------
 */

#include <map>
#include <string>
#include <boost/format.hpp>
#include <glibmm/i18n.h>
#include <semaphore.h>

using namespace std;

#include "gx_pitch_tracker.h"
#include "gx_parameter.h"
#include "gx_ui.h"
#include "gx_pluginloader.h"
#include "gx_resampler.h"
#include "gx_convolver.h"
#include "gx_modulesequencer.h"
#include "gx_internal_plugins.h"
#include "gx_engine.h"
#include "gx_json.h"
#include "gx_jack.h"
#include "gx_faust_support.h"

namespace gx_engine {

/****************************************************************
 ** MonoMute, StereoMute, MaxLevel
 */

MonoMute::MonoMute()
    : PluginDef() {
    version = PLUGINDEF_VERSION;
    id = "monomute";
    name = "?monomute";
    mono_audio = process;
}

void MonoMute::process(int count, float *input, float *output, PluginDef*) {
    (void)memset(output, 0, count*sizeof(float));
}

StereoMute::StereoMute()
    : PluginDef() {
    version = PLUGINDEF_VERSION;
    id = "stereomute";
    name = "?stereomute";
    stereo_audio = process;
}

void StereoMute::process(int count, float *input0, float *input1,
			 float *output0, float *output1, PluginDef*) {
    (void)memset(output0, 0, count*sizeof(float));
    (void)memset(output1, 0, count*sizeof(float));
}

MaxLevel::MaxLevel()
    : PluginDef() {
    version = PLUGINDEF_VERSION;
    flags = PGN_SNOOP;
    id = "maxlevel";
    name = "?maxlevel";
    stereo_audio = process;
    activate_plugin = activate;
}

float MaxLevel::maxlevel[2] = {0};

void MaxLevel::process(int count, float *input1, float *input2, float*, float*, PluginDef*) {
    const float *data[2] = {input1, input2};
    for (int c = 0; c < 2; c++) {
        float level = 0;
        for (int i = 0; i < count; i++) {
            float t = abs(data[c][i]);
            if (level < t) {
                level = t;
            }
        }
        maxlevel[c] = max(maxlevel[c], level);
    }
}

int MaxLevel::activate(bool start, PluginDef *plugin) {
    if (!start) {
	reset();
    }
    return 0;
}

static const char *midi_out_groups[] = {
	"channel_1", N_("Midi Out 1"), 
	"channel_2", N_("Midi Out 2"),
	"channel_3", N_("Midi Out 3"),
	".beat_detector",      N_("Beat Detector"),
	0
    };

MidiAudioBuffer::MidiAudioBuffer()
    : PluginDef(),
      plugin() {
    version = PLUGINDEF_VERSION;
    flags = PGN_SNOOP;
    id = "midi_out";
    name = N_("Midi Out");
    groups = midi_out_groups;
    mono_audio = fill_buffer;
    plugin.pdef = this;
}

gx_jack::GxJack* MidiAudioBuffer::jack = 0;

void MidiAudioBuffer::fill_buffer(int count, float *input, float*, PluginDef*) {
    void *buf = jack->get_midi_buffer(count);
    if (buf) {
	gx_engine::process_midi(count, input, buf);
    }
}


/****************************************************************
 ** class TunerAdapter
 */

TunerAdapter::TunerAdapter(const Plugin& pl, ModuleSequencer& engine_)
    : ModuleSelector(engine_),
      PluginDef(),
      pitch_tracker(),
      state(),
      engine(engine_),
      dep_plugin(pl),
      plugin() {
    version = PLUGINDEF_VERSION;
    flags = PGN_SNOOP;
    id = "tuner";
    name = "?tuner";
    mono_audio = feed_tuner;
    set_samplerate = init;
    register_params = regparam;
    plugin.pdef = this;
}

void TunerAdapter::init(unsigned int samplingFreq, PluginDef *plugin) {
    TunerAdapter& self = *static_cast<TunerAdapter*>(plugin);
    int priority, policy;
    // zita-convoler uses 5 levels, so substract 6
    self.engine.get_sched_priority(policy, priority, 6);
    self.pitch_tracker.init(policy, priority, samplingFreq);
}

void TunerAdapter::set_and_check(int use, bool on) {
    if (on) {
	state |= use;
    } else {
	state &= ~use;
    }
    plugin.on_off = state;
}

void TunerAdapter::feed_tuner(int count, float* input, float*, PluginDef* plugin) {
    static_cast<TunerAdapter*>(plugin)->pitch_tracker.add(count, input);
}

int TunerAdapter::regparam(const ParamReg& reg) {
    static_cast<TunerAdapter*>(reg.plugin)->plugin.on_off = false;
    return 0;
}

void TunerAdapter::set_module() {
    used_by_midi(dep_plugin.on_off);
}

/****************************************************************
 **  class NoiseGate
 */

PluginDef NoiseGate::inputdef = PluginDef();
float NoiseGate::fnglevel = 0;
float NoiseGate::ngate = 1;
bool NoiseGate::off = true;
Plugin NoiseGate::inputlevel = Plugin();
PluginDef NoiseGate::outputgate = PluginDef();

NoiseGate::NoiseGate() {

    inputdef.version = PLUGINDEF_VERSION;
    inputdef.flags = PGN_SNOOP;
    inputdef.id = "noise_gate";
    inputdef.name = N_("Noise Gate");
    inputdef.mono_audio = inputlevel_compute;
    inputdef.register_params = noisegate_register;

    inputlevel.pdef = &inputdef;

    outputgate.version = PLUGINDEF_VERSION;
    outputgate.id = "noiseshut";
    outputgate.name = "?noiseshut";
    outputgate.mono_audio = outputgate_compute;
    outputgate.activate_plugin = outputgate_activate;

}

inline float sqrf(float x) {
    return x * x;
}

void NoiseGate::inputlevel_compute(int count, float *input, float *output, PluginDef*) {
    float sumnoise = 0;
    for (int i = 0; i < count; i++) {
        sumnoise += sqrf(input[i]);
    }
    if (sumnoise/count > sqrf(fnglevel * 0.01)) {
        ngate = 1; // -75db 0.001 = 65db
    } else if (ngate > 0.01) {
        ngate *= 0.996;
    }
}

int NoiseGate::noisegate_register(const ParamReg& reg) {
    reg.registerVar("noise_gate.threshold", N_("Threshold"), "S", "", &fnglevel,
		    0.017f, 0.01f, 0.31f, 0.001f);
    return 0;
}

void NoiseGate::outputgate_compute(int count, float *input, float *output, PluginDef*) {
    if (off) {
	return;
    }
    while (count--) {
	*output++ = ngate * *input++;
    }
}

int NoiseGate::outputgate_activate(bool start, PluginDef *pdef) {
    if (start) {
	off = !inputlevel.on_off;
    }
    return 0;
}


/****************************************************************
 ** class OscilloscopeAdapter
 */

OscilloscopeAdapter::OscilloscopeAdapter(
    gx_ui::GxUI *ui, ModuleSequencer& engine)
    : PluginDef(),
      plugin(),
      activation(),
      size_change(),
      post_pre_signal(ui, &plugin.effect_post_pre),
      visible(ui, &plugin.box_visible)
{
    assert(buffer == 0);
    version = PLUGINDEF_VERSION;
    flags = PGN_SNOOP;
    id = "oscilloscope";
    name = N_("Oscilloscope");
    mono_audio = fill_buffer;
    activate_plugin = activate;
    plugin.pdef = this;
    engine.buffersize_change.connect(
	sigc::mem_fun(*this, &OscilloscopeAdapter::change_buffersize));
}

void OscilloscopeAdapter::change_buffersize(unsigned int size_) {
    //FIXME waveview display needs mutex
    size_change(0);
    float *b = buffer;
    buffer = new float[size_];
    size = size_;
    clear_buffer();
    size_change(size_);
    delete b;
}

float* OscilloscopeAdapter::buffer = 0;
unsigned int OscilloscopeAdapter::size = 0;

// rt process function
void OscilloscopeAdapter::fill_buffer(int count, float *input0, float *output0, PluginDef*) {
    assert(count == static_cast<int>(size));
    (void)memcpy(buffer, output0, sizeof(float)*count);
}

int OscilloscopeAdapter::activate(bool start, PluginDef *plugin) {
    return static_cast<OscilloscopeAdapter*>(plugin)->activation(start);
}

void OscilloscopeAdapter::clear_buffer() {
    memset(buffer, 0, size*sizeof(float));
}


/****************************************************************
 ** class GxJConvSettings
 */

bool* GxJConvSettings::checkbutton7 = 0;

GxJConvSettings::GxJConvSettings()
    : fIRFile(""),
      fIRDir(getenv("HOME")),
      fGain(0.2),
      fOffset(0),
      fLength(0),
      fDelay(0),
      gainline(),
      fGainCor(1) {
}

string GxJConvSettings::getFullIRPath() const {
    if (fIRFile.empty()) {
        return fIRFile;
    } else {
        return Glib::build_filename(fIRDir, fIRFile);
    }
}

void GxJConvSettings::setFullIRPath(string name) {
    fIRDir = Glib::path_get_dirname(name);
    fIRFile= Glib::path_get_basename(name);
}

void GxJConvSettings::writeJSON(gx_system::JsonWriter& w) {
    w.begin_object(true);
    w.write_key("jconv.IRFile");
    w.write(fIRFile, true);
    w.write_key("jconv.IRDir");
    w.write(fIRDir, true);
    w.write_key("jconv.Gain");
    w.write(fGain, true);
    w.write_key("jconv.GainCor");
    w.write(fGainCor, true);
    w.write_key("jconv.Offset");
    w.write(fOffset, true);
    w.write_key("jconv.Length");
    w.write(fLength, true);
    w.write_key("jconv.Delay");
    w.write(fDelay, true);
    w.write_key("jconv.gainline");
    w.begin_array();
    for (unsigned int i = 0; i < gainline.size(); i++) {
        w.begin_array();
        w.write(gainline[i].i);
        w.write(gainline[i].g);
        w.end_array();
    }
    w.end_array(true);
    
   // w.end_object(true);
    w.write_key("jconv.favorits");
    w.begin_array(true);
    bool end = true;
    for (faf_iterator its = faflist.begin(); its != faflist.end(); ++its) {
        w.begin_array();
        w.write(*its);
        w.end_array(end);
    }
    w.end_array(true);
    w.end_object(true);
}

void GxJConvSettings::read_gainline(gx_system::JsonParser& jp) {
    gainline.clear();
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() == gx_system::JsonParser::begin_array) {
        jp.next();
        jp.next(gx_system::JsonParser::value_number);
        gain_points p;
        p.i = jp.current_value_int();
        jp.next(gx_system::JsonParser::value_number);
        p.g = jp.current_value_float();
        jp.next(gx_system::JsonParser::end_array);
        gainline.push_back(p);
    }
    jp.next(gx_system::JsonParser::end_array);
}

void GxJConvSettings::read_favorites(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() == gx_system::JsonParser::begin_array) {
        jp.next();
        jp.next(gx_system::JsonParser::value_string);
        jp.next(gx_system::JsonParser::end_array);
        faflist.push_back(jp.current_value());
    }
    jp.next(gx_system::JsonParser::end_array);
}

GxJConvSettings::GxJConvSettings(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::begin_object);
    do {
        jp.next(gx_system::JsonParser::value_key);
        if (jp.current_value() == "jconv.IRFile") {
            jp.next(gx_system::JsonParser::value_string);
            fIRFile = jp.current_value();
        } else if (jp.current_value() == "jconv.IRDir") {
            jp.next(gx_system::JsonParser::value_string);
            fIRDir = jp.current_value();
        } else if (jp.current_value() == "jconv.Gain") {
            jp.next(gx_system::JsonParser::value_number);
            fGain = jp.current_value_float();
        } else if (jp.current_value() == "jconv.GainCor") {
            jp.next(gx_system::JsonParser::value_number);
            fGainCor = jp.current_value_int();
        } else if (jp.current_value() == "jconv.Offset") {
            jp.next(gx_system::JsonParser::value_number);
            fOffset = jp.current_value_int();
        } else if (jp.current_value() == "jconv.Length") {
            jp.next(gx_system::JsonParser::value_number);
            fLength = jp.current_value_int();
        } else if (jp.current_value() == "jconv.Delay") {
            jp.next(gx_system::JsonParser::value_number);
            fDelay = jp.current_value_int();
        } else if (jp.current_value() == "jconv.gainline") {
            read_gainline(jp);
        } else if (jp.current_value() == "jconv.favorits") {
            read_favorites(jp);
        } else {
            gx_system::gx_print_warning("jconv settings", "unknown key: " + jp.current_value());
            jp.skip_object();
        }
    } while (jp.peek() == gx_system::JsonParser::value_key);
    jp.next(gx_system::JsonParser::end_object);
}


/****************************************************************
 ** class ConvolverAdapter
 */

ConvolverAdapter::ConvolverAdapter(ModuleSequencer& engine_)
    : PluginDef(),
      conv(),
      activate_mutex(),
      engine(engine_),
      activated(false),
      plugin(),
      jcset() {
    version = PLUGINDEF_VERSION;
    id = "jconv";
    name = N_("Convolver");
    stereo_audio = convolver;
    set_samplerate = convolver_init;
    activate_plugin = activate;
    register_params = convolver_register;
    //FIXME: add clear_state
    plugin = this;
    engine.buffersize_change.connect(
	sigc::mem_fun(*this, &ConvolverAdapter::change_buffersize));
    GxJConvSettings::checkbutton7 = &plugin.on_off;
}

void ConvolverAdapter::change_buffersize(unsigned int size) {
    boost::mutex::scoped_lock lock(activate_mutex);
    if (activated) {
	conv.stop();
	while (conv.is_runnable()) {
	    conv.checkstate();
	}
	conv.set_buffersize(size);
	conv_start();
    } else {
	conv.set_buffersize(size);
    }
}

static gboolean conv_error_message(gpointer data) {
    gx_system::gx_print_error("Convolver", "overload");
    return false;
}

void ConvolverAdapter::restart() {
    if (!*GxJConvSettings::checkbutton7) {
        return;
    }
    conv.stop();
    while (conv.is_runnable()) {
	conv.checkstate();
    }
    bool rc = conv.configure(
        jcset.getFullIRPath(), jcset.getGain(), jcset.getGain(), jcset.getDelay(),
	jcset.getDelay(), jcset.getOffset(), jcset.getLength(), 0, 0, jcset.getGainline());
    int policy, priority;
    engine.get_sched_priority(policy, priority);
    if (!rc || !conv.start(policy, priority)) {
        *GxJConvSettings::checkbutton7 = 0;
    }
}

bool ConvolverAdapter::conv_start() {
    string path = jcset.getFullIRPath();
    if (path.empty()) {
        gx_system::gx_print_warning(_("convolver"), _("no impulseresponse file"));
        return false;
    }
    while (!conv.checkstate());
    if (conv.is_runnable()) {
	return true;
    }
    if (!conv.configure(
            path, jcset.getGain(), jcset.getGain(), jcset.getDelay(), jcset.getDelay(),
            jcset.getOffset(), jcset.getLength(), 0, 0, jcset.getGainline())) {
        return false;
    }
    int policy, priority;
    engine.get_sched_priority(policy, priority);
    return conv.start(policy, priority);
}


#include "faust/jconv_post.cc"

void ConvolverAdapter::convolver(int count, float *input0, float *input1,
				 float *output0, float *output1, PluginDef* plugin) {
    ConvolverAdapter& self = *static_cast<ConvolverAdapter*>(plugin);
    if (self.conv.is_runnable()) {
        float conv_out0[count];
        float conv_out1[count];
        if (!self.conv.compute(count, output0, output1, conv_out0, conv_out1)) {
            *GxJConvSettings::checkbutton7 = 0;
            g_idle_add(conv_error_message, gpointer(NULL));
        } else {
            jconv_post::compute(count, output0, output1,
				conv_out0, conv_out1, output0, output1);
        }
    }
}

int ConvolverAdapter::convolver_register(const ParamReg& reg) {
    jconv_post::register_params(reg);
    return 0;
}

void ConvolverAdapter::convolver_init(unsigned int samplingFreq, PluginDef *p) {
    ConvolverAdapter& self = *static_cast<ConvolverAdapter*>(p);
    boost::mutex::scoped_lock lock(self.activate_mutex);
    if (self.activated) {
	self.conv.stop();
	self.conv.set_samplerate(samplingFreq);
	jconv_post::init(samplingFreq, p);
	while (self.conv.is_runnable()) {
	    self.conv.checkstate();
	}
	self.conv_start();
    } else {
	self.conv.set_samplerate(samplingFreq);
	jconv_post::init(samplingFreq, p);
    }
}

int ConvolverAdapter::activate(bool start, PluginDef *p) {
    ConvolverAdapter& self = *static_cast<ConvolverAdapter*>(p);
    boost::mutex::scoped_lock lock(self.activate_mutex);
    if (start == self.activated) {
	return 0;
    }
    if (start) {
	if (!self.conv_start()) {
	    return -1;
	}
    } else {
	self.conv.stop();
    }
    self.activated = start;
    return 0;
}


/****************************************************************
 ** class BaseConvolver
 */


BaseConvolver::BaseConvolver(ModuleSequencer& engine_, gx_resample::BufferResampler& resamp)
    : PluginDef(),
      conv(resamp),
      activate_mutex(),
      engine(engine_),
      activated(false),
      plugin() {
    version = PLUGINDEF_VERSION;
    set_samplerate = init;
    activate_plugin = activate;
    plugin = this;
    engine.buffersize_change.connect(
	sigc::mem_fun(*this, &BaseConvolver::change_buffersize));
}

BaseConvolver::~BaseConvolver() {
}

void BaseConvolver::change_buffersize(unsigned int bufsize) {
    boost::mutex::scoped_lock lock(activate_mutex);
    conv.set_buffersize(bufsize);
    if (activated) {
	start(true);
    }
}

void BaseConvolver::init(unsigned int samplingFreq, PluginDef *p) {
    BaseConvolver& self = *static_cast<BaseConvolver*>(p);
    boost::mutex::scoped_lock lock(self.activate_mutex);
    self.conv.set_samplerate(samplingFreq);
    if (self.activated) {
	self.start(true);
    }
}

int BaseConvolver::activate(bool start, PluginDef *p) {
    BaseConvolver& self = *static_cast<BaseConvolver*>(p);
    boost::mutex::scoped_lock lock(self.activate_mutex);
    if (start == self.activated) {
	return 0;
    }
    if (start) {
	if (!self.start()) {
	    return -1;
	}
    } else {
	self.conv_stop();
    }
    self.activated = start;
    return 0;
}

int BaseConvolver::conv_start() {
    int policy, priority;
    engine.get_sched_priority(policy, priority);
    return conv.start(policy, priority);
}

/****************************************************************
 ** class CabinetConvolver
 */

struct CabDesc {
    int ir_count;
    int ir_sr;
    float ir_data[];
};

template <int tab_size>
struct CabDesc_imp {
    int ir_count;
    int ir_sr;
    float ir_data[tab_size];
    operator CabDesc&() { return *(CabDesc*)this; }
};

#include "gx_cabinet_data.cc"

struct CabEntry {
    const char *value_id;
    const char *value_label;
    CabDesc *data;
} cab_table[] = {
    { "4x12",        N_("4x12"),        &static_cast<CabDesc&>(cab_data_4x12) },
    { "2x12",        N_("2x12"),        &static_cast<CabDesc&>(cab_data_2x12) },
    { "1x12",        N_("1x12"),        &static_cast<CabDesc&>(cab_data_1x12) },
    { "4x10",        N_("4x10"),        &static_cast<CabDesc&>(cab_data_4x10) },
    { "2x10",        N_("2x10"),        &static_cast<CabDesc&>(cab_data_2x10) },
    { "HighGain",    N_("HighGain"),    &static_cast<CabDesc&>(cab_data_HighGain) },
    { "Twin",        N_("Twin"),        &static_cast<CabDesc&>(cab_data_Twin) },
    { "Bassman",     N_("Bassman"),     &static_cast<CabDesc&>(cab_data_Bassman) },
    { "Marshall",    N_("Marshall"),    &static_cast<CabDesc&>(cab_data_Marshall) },
    { "AC-30",       N_("AC-30"),       &static_cast<CabDesc&>(cab_data_AC30) },
    { "Princeton",   N_("Princeton"),   &static_cast<CabDesc&>(cab_data_Princeton) },
    { "A2",          N_("A2"),          &static_cast<CabDesc&>(cab_data_A2) },
    { "1x15",        N_("1x15"),        &static_cast<CabDesc&>(cab_data_1x15) },
    { "Mesa Boogie", N_("Mesa Boogie"), &static_cast<CabDesc&>(cab_data_mesa) },
    { "Briliant",    N_("Briliant"),    &static_cast<CabDesc&>(cab_data_briliant) },
};
static const unsigned int cab_table_size = sizeof(cab_table) / sizeof(cab_table[0]);

static CabEntry& getCabEntry(unsigned int n) {
    if (n >= cab_table_size) {
	n = cab_table_size - 1;
    }
    return cab_table[n];
}

static const float no_sum = 1e10;

CabinetConvolver::CabinetConvolver(ModuleSequencer& engine, gx_resample::BufferResampler& resamp):
    BaseConvolver(engine, resamp),
    current_cab(-1),
    level(0),
    cabinet(0),
    bass(0),
    treble(0),
    sum(no_sum),
    cab_names(new value_pair[cab_table_size+1]) {
    for (unsigned int i = 0; i < cab_table_size; ++i) {
	CabEntry& cab = getCabEntry(i);
	cab_names[i].value_id = cab.value_id;
	cab_names[i].value_label = cab.value_label;
    }
    cab_names[cab_table_size].value_id = 0;
    cab_names[cab_table_size].value_label = 0;
    id = "cab";
    name = N_("Cabinet");
    mono_audio = run_cab_conf;
    register_params = register_cab;
}

CabinetConvolver::~CabinetConvolver() {
    delete cab_names;
}

bool CabinetConvolver::conv_update() {
    update_sum();
    bool ret = update();
    if (! ret) {
	ret = start();
    }
    return ret;
}

#include "faust/cabinet_impulse_former.cc"

bool CabinetConvolver::start(bool force) {
    CabDesc& cab = *getCabEntry(cabinet).data;
    if (cabinet_changed() || sum_changed() || force) {
	conv.stop();
        update_cabinet();
	update_sum();
	cabinet_impulse_former::init(cab.ir_sr);
	float cab_irdata_c[cab.ir_count];
	cabinet_impulse_former::compute(cab.ir_count,cab.ir_data,cab_irdata_c);
	while (!conv.checkstate());
	if (!conv.configure(cab.ir_count, cab_irdata_c, cab.ir_sr)) {
	    return false;
	}
	return conv_start();
    } else {
	while (!conv.checkstate());
	if (!conv.is_runnable()) {
	    return conv_start();
	}
	return true;
    }
}

bool CabinetConvolver::update() {
    CabDesc& cab = *getCabEntry(cabinet).data;
    float cab_irdata_c[cab.ir_count];
    cabinet_impulse_former::compute(cab.ir_count,cab.ir_data,cab_irdata_c);
    return conv.update(cab.ir_count, cab_irdata_c, cab.ir_sr);
}

// reduce gain to compensate the increased gain by the cabinet
inline void CabinetConvolver::compensate_cab(int count, float *input0, float *output0) {
    double fSlow0 = (0.0010000000000000009 * pow(10, (0.05 * (-level*2.0))));
    static double fRec0[2] = {0, 0};
    for (int i = 0; i < count; i++) {
        fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
        output0[i] = (FAUSTFLOAT)(static_cast<double>(input0[i]) * fRec0[0]);
        // post processing
        fRec0[1] = fRec0[0];
    }
}

static gboolean cab_error_message(gpointer data) {
    gx_system::gx_print_error("Convolver", "cabinet overload");
    return false;
}

// wraper for the rack order function pointers
void CabinetConvolver::run_cab_conf(int count, float *input0, float *output0, PluginDef *p) {
    CabinetConvolver& self = *static_cast<CabinetConvolver*>(p);
    self.compensate_cab(count, output0, output0);
    if (!self.conv.compute(count, output0)) {
        g_idle_add(cab_error_message, gpointer(NULL));
        self.current_cab = -1;
    }
}

int CabinetConvolver::register_cab(const ParamReg& reg) {
    CabinetConvolver& cab = *static_cast<CabinetConvolver*>(reg.plugin);
    gx_gui::registerEnumParam("cab.select", "select", cab.cab_names, &cab.cabinet, 0);
    reg.registerVar("cab.Level", "",  "S", "", &cab.level,  1.0, 0.5, 5.0, 0.5);
    reg.registerVar("cab.bass", "",   "S", "", &cab.bass,   0.0, -10.0, 10.0, 0.5);
    reg.registerVar("cab.treble", "", "S", "", &cab.treble, 0.0, -10.0, 10.0, 0.5);
    cabinet_impulse_former::register_params(reg);
    return 0;
}


/****************************************************************
 ** class ContrastConvolver
 */

ContrastConvolver::ContrastConvolver(ModuleSequencer& engine, gx_resample::BufferResampler& resamp):
    BaseConvolver(engine, resamp),
    level(0),
    sum(no_sum) {
    id = "con";
    name = N_("Contrast convolver");
    mono_audio = run_contrast;
    register_params = register_con;
}

#include "faust/presence_level.cc"

bool ContrastConvolver::start(bool force) {
    if (sum_changed() || force) {
	conv.stop();
	update_sum();
	presence_level::init(contrast_ir_desc.ir_sr);
	float contrast_irdata_c[contrast_ir_desc.ir_count];
	presence_level::compute(contrast_ir_desc.ir_count,contrast_ir_desc.ir_data,contrast_irdata_c);
	while (!conv.checkstate());
	if (!conv.configure(contrast_ir_desc.ir_count, contrast_irdata_c, contrast_ir_desc.ir_sr)) {
	    return false;
	}
	return conv_start();
    } else {
	while (!conv.checkstate());
	if (!conv.is_runnable()) {
	    return conv_start();
	}
	return true;
    }
}

// reduce gain to compensate the increased gain by the cabinet
inline void ContrastConvolver::compensate_con(int count, float *input0, float *output0) {
    double fSlow0 = (0.0010000000000000009 * pow(10, (0.05 * (-level*2.0))));
    static double fRec0[2] = {0, 0};
    for (int i = 0; i < count; i++) {
        fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
        output0[i] = input0[i] * fRec0[0];
        // post processing
        fRec0[1] = fRec0[0];
    }
}

int ContrastConvolver::register_con(const ParamReg& reg) {
    ContrastConvolver& self = *static_cast<ContrastConvolver*>(reg.plugin);
    reg.registerVar("con.Level", "",  "S", "", &self.level,  1.0, 0.5, 5.0, 0.5);
    presence_level::register_params(reg);
    return 0;
}

static gboolean contrast_error_message(gpointer data) {
    gx_system::gx_print_error("Convolver", "presence overload");
    return false;
}

// wraper for the presence function
void ContrastConvolver::run_contrast(int count, float *input0, float *output0, PluginDef *p) {
    ContrastConvolver& self = *static_cast<ContrastConvolver*>(p);
    self.compensate_con(count, output0, output0);
    if (!self.conv.compute(count, output0)) {
        g_idle_add(contrast_error_message, gpointer(NULL));
        self.sum = no_sum;
    }
}

} // namespace gx_engine
