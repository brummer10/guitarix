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

#include "engine.h"

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
    register_params = regparam;
}

float MaxLevel::maxlevel[channelcount] = {0};

int MaxLevel::regparam(const ParamReg& reg) {
    const char *tooltip = _("Overall Rack output");
    reg.registerFloatVar("maxlevel.left", "", "SLMO", tooltip, &maxlevel[0], 0.0, 0.0, 1.0, 0.0, 0);
    reg.registerFloatVar("maxlevel.right", "", "SLMO", tooltip, &maxlevel[1], 0.0, 0.0, 1.0, 0.0, 0);
    return 0;
}

void MaxLevel::process(int count, float *input1, float *input2, float*, float*, PluginDef*) {
    const float *data[channelcount] = {input1, input2};
    assert(channelcount == 2);
    for (unsigned int c = 0; c < channelcount; c++) {
        float level = 0;
        for (int i = 0; i < count; i++) {
            float t = std::abs(data[c][i]);
            if (level < t) {
                level = t;
            }
        }
        maxlevel[c] = max(maxlevel[c], level);
    }
}

int MaxLevel::activate(bool start, PluginDef *plugin) {
    if (!start) {
	for (unsigned int c = 0; c < channelcount; c++) {
	    maxlevel[c] = 0;
	}
    }
    return 0;
}


/****************************************************************
 ** class TunerAdapter
 */

#include "gx_faust_support.h"
#include "faust/low_high_cut.cc"

TunerAdapter::TunerAdapter(ModuleSequencer& engine_)
    : ModuleSelector(engine_),
      PluginDef(),
      trackable(),
      lhc(),
      pitch_tracker(),
      state(),
      engine(engine_),
      dep_plugin(),
      plugin() {
    version = PLUGINDEF_VERSION;
    flags = PGN_SNOOP;
    id = "tuner";
    name = "Rack Tuner";
    mono_audio = feed_tuner;
    set_samplerate = init;
    activate_plugin = activate;
    register_params = regparam;
    plugin.set_pdef(this);
}

void TunerAdapter::init(unsigned int samplingFreq, PluginDef *plugin) {
    TunerAdapter& self = *static_cast<TunerAdapter*>(plugin);
    int priority, policy;
    // zita-convoler uses 5 levels, so substract 6
    self.engine.get_sched_priority(policy, priority, 6);
    self.lhc.init(samplingFreq);
    self.pitch_tracker.init(policy, priority, samplingFreq);
}

void TunerAdapter::set_and_check(int use, bool on) {
    if (on) {
	state |= use;
    } else {
	state &= ~use;
    }
    if (plugin.get_on_off() != bool(state)) {
	plugin.set_on_off(bool(state));
	engine.set_rack_changed();
    }
    if (use == switcher_use) {
	pitch_tracker.set_fast_note_detection(on);
    }
}

int TunerAdapter::activate(bool start, PluginDef *plugin) {
    if (!start) {
	static_cast<TunerAdapter*>(plugin)->pitch_tracker.reset();
    }
    return 0;
}

void TunerAdapter::feed_tuner(int count, float* input, float*, PluginDef* plugin) {
    float t_input[count];
    memcpy(t_input, input, count*sizeof(float));
    static_cast<TunerAdapter*>(plugin)->lhc.compute(count, t_input, t_input);
    static_cast<TunerAdapter*>(plugin)->pitch_tracker.add(count, t_input);
}

int TunerAdapter::regparam(const ParamReg& reg) {
    TunerAdapter* a = static_cast<TunerAdapter*>(reg.plugin);
    a->plugin.set_on_off(false);
    return 0;
}

void TunerAdapter::set_module() {
    if (dep_plugin) {
	used_by_midi(dep_plugin->get_on_off());
    }
}


/****************************************************************
 ** class OscilloscopeAdapter
 */

void OscilloscopeInfo::readJSON(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::begin_array);
    jp.next(gx_system::JsonParser::value_number);
    load = jp.current_value_int();
    jp.next(gx_system::JsonParser::value_number);
    frames = jp.current_value_int();
    jp.next(gx_system::JsonParser::value_number);
    is_rt = jp.current_value_int();
    jp.next(gx_system::JsonParser::value_number);
    bsize = jp.current_value_int();
    jp.next(gx_system::JsonParser::value_number);
    unsigned int sz = jp.current_value_int();
    if (buffer_size != sz) {
	delete[] buffer;
	buffer = new float[sz];
	buffer_size = sz;
	size_change(sz, buffer);
    }
    jp.next(gx_system::JsonParser::begin_array);
    float *p = buffer;
    while (jp.peek() != gx_system::JsonParser::end_array) {
	jp.next(gx_system::JsonParser::value_number);
	*p++ = jp.current_value_float();
    }
    jp.next(gx_system::JsonParser::end_array);
    jp.next(gx_system::JsonParser::end_array);
}

void OscilloscopeInfo::writeJSON(gx_system::JsonWriter& jw) const {
    assert(jack);
    jw.begin_array();
    jw.write(static_cast<int>(round(jack->get_jcpu_load())));
    jw.write(jack->get_time_is()/100000);
    jw.write(jack->get_is_rt());
    jw.write(jack->get_jack_bs());
    float *p = buffer;
    jw.write(buffer_size);
    jw.begin_array();
    for (unsigned int i = 0; i < buffer_size; i++) {
        jw.write(*p++);
    }
    jw.end_array();
    jw.end_array();
}

void OscilloscopeInfo::update() {
    if (!jack) {
        return;
    }
    load = static_cast<int>(round(jack->get_jcpu_load()));
    frames = jack->get_time_is()/100000;
    is_rt = jack->get_is_rt();
    bsize = jack->get_jack_bs();
}

OscParameter::ParameterV(const string& id, OscilloscopeInfo *v)
    : Parameter(id, "", tp_special, None, true, false),
      value_storage(),
      value(v) {
    setSavable(false);
    setOutput(true);
}

OscParameter::~ParameterV() {
}

void OscParameter::trigger_changed() {
    value->update();
    changed(*value);
}

OscParameter *OscParameter::insert_param(ParamMap &pmap, const string& id,
                                         OscilloscopeInfo *v) {
    OscParameter *p = new OscParameter(id, v);
    pmap.insert(p);
    return p;
}

OscParameter::ParameterV(gx_system::JsonParser& jp)
    : Parameter(jp_next(jp, "Parameter")),
      value_storage(),
      value(&value_storage) {
    while (jp.peek() != gx_system::JsonParser::end_object) {
        jp.next(gx_system::JsonParser::value_key);
        if (jp.current_value() == "value") {
            value->readJSON(jp);
        } else {
            gx_print_warning(
                "OscParameter", Glib::ustring::compose("%1: unknown key: %2", _id, jp.current_value()));
            jp.skip_object();
        }
    }
    jp.next(gx_system::JsonParser::end_object);
}

void OscParameter::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_key("Parameter"); Parameter::serializeJSON(jw);
    jw.write_key("value"); value->writeJSON(jw);
    //jw.write_key("std_value"); std_value.writeJSON(jw);
    jw.end_object();
}

bool OscParameter::on_off_value() {
    assert(false);
    return false;
}

void OscParameter::stdJSON_value() {
    assert(false);
}

void OscParameter::writeJSON(gx_system::JsonWriter& jw) const {
    jw.write_key(_id.c_str());
    value->writeJSON(jw);
}

void OscParameter::readJSON_value(gx_system::JsonParser& jp) {
    value->readJSON(jp);
}

bool OscParameter::compareJSON_value() {
    assert(false);
    return false;
}

void OscParameter::setJSON_value() {
    changed(*value);
}

OscilloscopeAdapter::OscilloscopeAdapter(ModuleSequencer& engine)
    : PluginDef(),
      info(),
      pmap(engine.get_param()),
      mul_buffer(1),
      plugin() {
    assert(info.buffer == 0);
    version = PLUGINDEF_VERSION;
    flags = PGN_SNOOP | PGN_NO_PRESETS;
    id = "oscilloscope";
    name = N_("Oscilloscope");
    category = N_("Misc");
    mono_audio = fill_buffer;
    register_params = osc_register;
    load_ui = osc_load_ui;
    plugin.set_pdef(this);
    engine.signal_buffersize_change().connect(
	sigc::mem_fun(*this, &OscilloscopeAdapter::change_buffersize));
}

int OscilloscopeAdapter::osc_register(const ParamReg& reg) {
    OscilloscopeAdapter& self = *static_cast<OscilloscopeAdapter*>(reg.plugin);
    OscParameter::insert_param(self.pmap, "oscilloscope.info", &self.info);
    return 0;
}

void OscilloscopeAdapter::change_buffersize(unsigned int size) {
    //FIXME waveview display needs mutex
    info.size_change(0, 0);
    float *b = info.buffer;
    unsigned int d = info.buffer_size < 1024 ? mul_buffer : 1;
    info.buffer = new float[size * d];
    info.buffer_size = size * d;
    clear_buffer();
    info.size_change(info.buffer_size, info.buffer);
    delete[] b;
}

// rt process function
void OscilloscopeAdapter::fill_buffer(int count, float *input0, float *output0, PluginDef *p) {
    OscilloscopeAdapter& self = *static_cast<OscilloscopeAdapter*>(p);
    if (count*self.mul_buffer != static_cast<int>(self.info.buffer_size)) {
	return;
    }
    if (self.mul_buffer > 1) {
	(void)memmove(self.info.buffer, &self.info.buffer[count], sizeof(float)*count*(self.mul_buffer-1));
    }
    (void)memcpy(&self.info.buffer[count*(self.mul_buffer-1)], output0, sizeof(float)*count);
}

void OscilloscopeAdapter::clear_buffer() {
    memset(info.buffer, 0, info.buffer_size*sizeof(float));
}

//static
int OscilloscopeAdapter::osc_load_ui(const UiBuilder& builder, int format) {
    if (format & UI_FORM_GLADE) {
	builder.load_glade_file("oscilloscope_ui.glade");
        return 0;
    } else if (format & UI_FORM_STACK) {
        builder.openHorizontalhideBox("");
        builder.closeBox();
        builder.openVerticalBox("");
        {
            builder.openFrameBox("");
            builder.closeBox();
            builder.openHorizontalBox("");
            {
                builder.openFrameBox("");
                builder.closeBox();
                //builder.addLiveWaveDisplay(" ");
                builder.openFrameBox("");
                builder.closeBox();
            }
            builder.closeBox();
            builder.openFrameBox("");
            builder.closeBox();
        }
        builder.closeBox();
        return 0;
    } else {
        return -1;
    }
}

} // namespace gx_engine
