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
#include "gx_faust_support.h"

namespace gx_engine {

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

    inputlevel.set_pdef(&inputdef);

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
	off = !inputlevel.get_on_off();
    }
    return 0;
}


/****************************************************************
 ** class GxJConvSettings
 */

GxJConvSettings::GxJConvSettings()
    : fIRFile(),
      fIRDir(),
      fGain(0),
      fOffset(0),
      fLength(0),
      fDelay(0),
      gainline(),
      fGainCor(false) {
}

GxJConvSettings& GxJConvSettings::operator=(GxJConvSettings const& jcset) {
    fIRFile = jcset.fIRFile;
    fIRDir = jcset.fIRDir;
    fGain = jcset.fGain;
    fOffset = jcset.fOffset;
    fLength = jcset.fLength;
    fDelay = jcset.fDelay;
    gainline = jcset.gainline;
    fGainCor = jcset.fGainCor;
    return *this;
}

std::string GxJConvSettings::getFullIRPath() const {
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

void GxJConvSettings::writeJSON(gx_system::JsonWriter& w) const {
    w.begin_object(true);
    w.write_kv("jconv.IRFile", fIRFile);
    w.write_kv("jconv.IRDir", gx_system::get_options().get_IR_prefixmap().replace_path(fIRDir));
    w.write_kv("jconv.Gain", fGain);
    w.write_kv("jconv.GainCor", fGainCor);
    w.write_kv("jconv.Offset", fOffset);
    w.write_kv("jconv.Length", fLength);
    w.write_kv("jconv.Delay", fDelay);
    w.write_key("jconv.gainline");
    w.begin_array();
    for (unsigned int i = 0; i < gainline.size(); i++) {
        w.begin_array();
        w.write(gainline[i].i);
        w.write(gainline[i].g);
        w.end_array();
    }
    w.end_array(true);
    w.end_object(true);
}

bool GxJConvSettings::operator==(const GxJConvSettings& jcset) const {
    if (fIRFile != jcset.fIRFile || fIRDir != jcset.fIRDir) {
	return false;
    }
    if (fOffset != jcset.fOffset || fLength != jcset.fLength || fDelay != jcset.fDelay) {
	return false;
    }
    if (fGainCor != jcset.fGainCor) {
	return false;
    }
    if (fGainCor && abs(fGain - jcset.fGain) > 1e-4 * (fGain + jcset.fGain)) {
	return false;
    }
    if (gainline == jcset.gainline) {
	return false;
    }
    return true;
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

void GxJConvSettings::readJSON(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::begin_object);
    do {
        jp.next(gx_system::JsonParser::value_key);
	if (jp.read_kv("jconv.IRFile", fIRFile) ||
	    jp.read_kv("jconv.IRDir", fIRDir) ||
	    jp.read_kv("jconv.Gain", fGain) ||
	    jp.read_kv("jconv.GainCor", fGainCor) ||
	    jp.read_kv("jconv.Offset", fOffset) ||
	    jp.read_kv("jconv.Length", fLength) ||
	    jp.read_kv("jconv.Delay", fDelay)) {
        } else if (jp.current_value() == "jconv.gainline") {
            read_gainline(jp);
        } else if (jp.current_value() == "jconv.favorits") {
            jp.skip_object();
        } else {
            gx_print_warning("jconv settings", "unknown key: " + jp.current_value());
            jp.skip_object();
        }
    } while (jp.peek() == gx_system::JsonParser::value_key);
    jp.next(gx_system::JsonParser::end_object);
    if (!fIRFile.empty()) {
	if (fIRDir.empty()) {
	    gx_system::get_options().get_IR_pathlist().find_dir(&fIRDir, fIRFile);
	} else {
	    fIRDir = gx_system::get_options().get_IR_prefixmap().replace_symbol(fIRDir);
	}
    }
}


/****************************************************************
 ** class JConvParameter
 */

ParameterV<GxJConvSettings>::ParameterV(const string& id, gx_engine::ConvolverAdapter& conv, GxJConvSettings *v)
    : Parameter(id, "", tp_special, None, true, false),
      json_value(),
      value(v),
      std_value(),
      value_storage(),
      changed() {
    std_value.setFullIRPath(gx_system::get_options().get_IR_prefixmap().replace_symbol("%S/greathall.wav"));
    std_value.fGainCor = true;
    std_value.fGain = 0.598717;
    const int ir_len = 112561;
    std_value.fLength = ir_len;
    static gain_points g[2] = {{0, 0}, {ir_len-1, 0}};
    std_value.gainline = Gainline(g, sizeof(g) / sizeof(g[0]));
}

JConvParameter *JConvParameter::insert_param(
    ParamMap &pmap, const string& id, ConvolverAdapter &conv, GxJConvSettings *v) {
    JConvParameter *p = new JConvParameter(id, conv, v);
    pmap.insert(p);
    return p;
}

JConvParameter::~ParameterV() {
}

JConvParameter::ParameterV(gx_system::JsonParser& jp)
 : Parameter(jp_next(jp, "Parameter")),
   searchpath(0),
   pfx_conv(0),
   json_value(),
   value(&value_storage),
   std_value() {
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.current_value() == "value") {
	    value->readJSON(jp);
	} else if (jp.current_value() == "std_value") {
	    std_value.readJSON(jp);
	} else {
	    gx_print_warning(
		"JConvParameter", Glib::ustring::compose("%1: unknown key: %2", _id, jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
}

void JConvParameter::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_key("Parameter"); Parameter::serializeJSON(jw);
    jw.write_key("value"); value->writeJSON(jw);
    jw.write_key("std_value"); std_value.writeJSON(jw);
    jw.end_object();
}

bool JConvParameter::on_off_value() {
    assert(false);
    return false;
}

void JConvParameter::stdJSON_value() {
    json_value = std_value;
}

void JConvParameter::writeJSON(gx_system::JsonWriter& jw) const {
    jw.write_key(_id.c_str());
    value->writeJSON(jw);
}

void JConvParameter::readJSON_value(gx_system::JsonParser& jp) {
    json_value.readJSON(jp);
}

bool JConvParameter::compareJSON_value() {
    return json_value == *value;
}

bool JConvParameter::set(const GxJConvSettings& val) const {
    if (val == *value) {
	return false;
    }
    *value = val;
    changed(value);
    return true;
}

void JConvParameter::setJSON_value() {
    set(json_value);
}


/****************************************************************
 ** class ConvolverAdapter
 */

#include "faust/jconv_post.cc"
#include "faust/jconv_post_mono.cc"

ConvolverAdapter::ConvolverAdapter(
    EngineControl& engine_, sigc::slot<void> sync_, ParamMap& param_)
    : PluginDef(),
      conv(),
      activate_mutex(),
      engine(engine_),
      sync(sync_),
      param(param_),
      activated(false),
      jcset(),
      jcp(0),
      plugin() {
    version = PLUGINDEF_VERSION;
    category = N_("Reverb");
    //FIXME: add clear_state
    plugin = this;
    engine.signal_buffersize_change().connect(
	sigc::mem_fun(*this, &ConvolverAdapter::change_buffersize));
}

ConvolverAdapter::~ConvolverAdapter() {
}

void ConvolverAdapter::change_buffersize(unsigned int size) {
    boost::mutex::scoped_lock lock(activate_mutex);
    if (activated) {
	conv.stop_process();
	while (conv.is_runnable()) {
	    conv.checkstate();
	}
	conv.set_buffersize(size);
	if (size) {
	    conv_start();
	}
    } else {
	conv.set_buffersize(size);
    }
}

void ConvolverAdapter::restart() {
    if (!plugin.get_on_off()) {
        return;
    }
    conv.set_not_runnable();
    sync();
    conv.stop_process();
    while (!conv.checkstate());
    float gain;
    if (jcset.getGainCor()) {
	gain = jcset.getGain();
    } else {
	gain = 1.0;
    }
    bool rc = conv.configure(
        jcset.getFullIRPath(), gain, gain, jcset.getDelay(), jcset.getDelay(),
	jcset.getOffset(), jcset.getLength(), 0, 0, jcset.getGainline());
    int policy, priority;
    engine.get_sched_priority(policy, priority);
    if (!rc || !conv.start(policy, priority)) {
        plugin.set_on_off(false);
    }
}

bool ConvolverAdapter::conv_start() {
    if (!conv.get_buffersize() || !conv.get_samplerate()) {
	return false;
    }
    string path = jcset.getFullIRPath();
    if (path.empty()) {
        gx_print_warning(_("convolver"), _("no impulseresponse file"));
        plugin.set_on_off(false);
        return false;
    }
    while (!conv.checkstate());
    if (conv.is_runnable()) {
	return true;
    }
    float gain;
    if (jcset.getGainCor()) {
	gain = jcset.getGain();
    } else {
	gain = 1.0;
    }
    if (!conv.configure(
            path, gain, gain, jcset.getDelay(), jcset.getDelay(),
            jcset.getOffset(), jcset.getLength(), 0, 0, jcset.getGainline())) {
        return false;
    }
    int policy, priority;
    engine.get_sched_priority(policy, priority);
    return conv.start(policy, priority);
}


/****************************************************************
 ** class ConvolverStereoAdapter
 */

ConvolverStereoAdapter::ConvolverStereoAdapter(
    EngineControl& engine_, sigc::slot<void> sync_, ParamMap& param_)
    : ConvolverAdapter(engine_, sync_, param_) {
    id = "jconv";
    name = N_("Convolver");
    register_params = convolver_register;
    set_samplerate = convolver_init;
    activate_plugin = activate;
    stereo_audio = convolver;
}

ConvolverStereoAdapter::~ConvolverStereoAdapter() {
}

void ConvolverStereoAdapter::convolver(int count, float *input0, float *input1,
				 float *output0, float *output1, PluginDef* plugin) {
    ConvolverStereoAdapter& self = *static_cast<ConvolverStereoAdapter*>(plugin);
    if (self.conv.is_runnable()) {
        float conv_out0[count];
        float conv_out1[count];
        if (self.conv.compute(count, input0, input1, conv_out0, conv_out1)) {
            self.jc_post.compute(count, input0, input1,
				 conv_out0, conv_out1, output0, output1);
	    return;
        }
	self.engine.overload(EngineControl::ov_Convolver, self.id);
    }
    if (input0 != output0) {
	memcpy(output0, input0, count * sizeof(float));
    }
    if (input1 != output1) {
	memcpy(output1, input1, count * sizeof(float));
    }
}

int ConvolverStereoAdapter::convolver_register(const ParamReg& reg) {
    ConvolverStereoAdapter& self = *static_cast<ConvolverStereoAdapter*>(reg.plugin);
    self.jcp = JConvParameter::insert_param(self.param, "jconv.convolver", self, &self.jcset);
    self.jcp->signal_changed().connect(
	sigc::hide(
	    sigc::mem_fun(self, &ConvolverStereoAdapter::restart)));
    return self.jc_post.register_par(reg);
}

void ConvolverStereoAdapter::convolver_init(unsigned int samplingFreq, PluginDef *p) {
    ConvolverStereoAdapter& self = *static_cast<ConvolverStereoAdapter*>(p);
    boost::mutex::scoped_lock lock(self.activate_mutex);
    if (self.activated) {
	self.conv.stop_process();
	self.conv.set_samplerate(samplingFreq);
	self.jc_post.init(samplingFreq);
	while (self.conv.is_runnable()) {
	    self.conv.checkstate();
	}
	self.conv_start();
    } else {
	self.conv.set_samplerate(samplingFreq);
	self.jc_post.init(samplingFreq);
    }
}

int ConvolverStereoAdapter::activate(bool start, PluginDef *p) {
    ConvolverStereoAdapter& self = *static_cast<ConvolverStereoAdapter*>(p);
    boost::mutex::scoped_lock lock(self.activate_mutex);
    if (start) {
	if (self.activated && self.conv.is_runnable()) {
	    return 0;
	}
    } else {
	if (!self.activated) {
	    return 0;
	}
    }
    self.activated = start;
    if (start) {
	if (self.jc_post.activate(true) != 0) {
	    gx_print_error(_("convolver"), "jconv post activate error?!");
	    return -1;
	}
	if (!self.conv_start()) {
	    return -1;
	}
    } else {
	self.conv.stop_process();
	self.jc_post.activate(false);
    }
    return 0;
}


/****************************************************************
 ** class ConvolverMonoAdapter
 */

ConvolverMonoAdapter::ConvolverMonoAdapter(
    EngineControl& engine_, sigc::slot<void> sync_, ParamMap& param_)
    : ConvolverAdapter(engine_, sync_, param_) {
    id = "jconv_mono";
    name = N_("Convolver");
    register_params = convolver_register;
    set_samplerate = convolver_init;
    activate_plugin = activate;
    mono_audio = convolver;
}

ConvolverMonoAdapter::~ConvolverMonoAdapter() {
}

void ConvolverMonoAdapter::convolver(int count, float *input, float *output, PluginDef* plugin) {
    ConvolverMonoAdapter& self = *static_cast<ConvolverMonoAdapter*>(plugin);
    if (self.conv.is_runnable()) {
        float conv_out[count];
        if (self.conv.compute(count, input, conv_out)) {
            self.jc_post_mono.compute(count, output, conv_out, output);
	    return;
        }
	self.engine.overload(EngineControl::ov_Convolver, self.id);
    }
    if (input != output) {
	memcpy(output, input, count * sizeof(float));
    }
}

int ConvolverMonoAdapter::convolver_register(const ParamReg& reg) {
    ConvolverMonoAdapter& self = *static_cast<ConvolverMonoAdapter*>(reg.plugin);
    self.jcp = JConvParameter::insert_param(self.param, "jconv_mono.convolver", self, &self.jcset);
    self.jcp->signal_changed().connect(
	sigc::hide(
	    sigc::mem_fun(self, &ConvolverMonoAdapter::restart)));
    return self.jc_post_mono.register_par(reg);;
}

void ConvolverMonoAdapter::convolver_init(unsigned int samplingFreq, PluginDef *p) {
    ConvolverMonoAdapter& self = *static_cast<ConvolverMonoAdapter*>(p);
    boost::mutex::scoped_lock lock(self.activate_mutex);
    if (self.activated) {
	self.conv.stop_process();
	self.conv.set_samplerate(samplingFreq);
	while (self.conv.is_runnable()) {
	    self.conv.checkstate();
	}
	self.conv_start();
    } else {
	self.conv.set_samplerate(samplingFreq);
    }
}

int ConvolverMonoAdapter::activate(bool start, PluginDef *p) {
    ConvolverMonoAdapter& self = *static_cast<ConvolverMonoAdapter*>(p);
    boost::mutex::scoped_lock lock(self.activate_mutex);
    if (start) {
	if (self.activated && self.conv.is_runnable()) {
	    return 0;
	}
    } else {
	if (!self.activated) {
	    return 0;
	}
    }
    self.activated = start;
    if (start) {
	if (!self.conv_start()) {
	    return -1;
	}
    } else {
	self.conv.stop_process();
    }
    return 0;
}

/****************************************************************
 ** class BaseConvolver
 */


BaseConvolver::BaseConvolver(EngineControl& engine_, sigc::slot<void> sync_, gx_resample::BufferResampler& resamp)
    : PluginDef(),
      conv(resamp),
      activate_mutex(),
      engine(engine_),
      sync(sync_),
      activated(false),
      plugin() {
    version = PLUGINDEF_VERSION;
    set_samplerate = init;
    activate_plugin = activate;
    plugin = this;
    engine.signal_buffersize_change().connect(
	sigc::mem_fun(*this, &BaseConvolver::change_buffersize));
}

BaseConvolver::~BaseConvolver() {
    update_conn.disconnect();
}

void BaseConvolver::change_buffersize(unsigned int bufsize) {
    boost::mutex::scoped_lock lock(activate_mutex);
    conv.set_buffersize(bufsize);
    if (activated) {
	if (!bufsize) {
	    conv.stop_process();
	} else {
	    start(true);
	}
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

bool BaseConvolver::check_update_timeout() {
    if (!activated || !plugin.get_on_off()) {
	return false;
    }
    check_update();
    return true;
}

int BaseConvolver::activate(bool start, PluginDef *p) {
    BaseConvolver& self = *static_cast<BaseConvolver*>(p);
    boost::mutex::scoped_lock lock(self.activate_mutex);
    if (start) {
	if (!self.conv.get_buffersize()) {
	    start = false;
	}
    }
    if (start == self.activated) {
	return 0;
    }
    if (start) {
	if (!self.start()) {
	    return -1;
	}
	self.update_conn = Glib::signal_timeout().connect(
	    sigc::mem_fun(self, &BaseConvolver::check_update_timeout), 200);
    } else {
	self.conv.stop_process();
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
    { "Vitalize",     N_("Vitalize"),     &static_cast<CabDesc&>(cab_data_vitalize) },
    { "Charisma",    N_("Charisma"),    &static_cast<CabDesc&>(cab_data_charisma) },
};
static const unsigned int cab_table_size = sizeof(cab_table) / sizeof(cab_table[0]);

static CabEntry& getCabEntry(unsigned int n) {
    if (n >= cab_table_size) {
	n = cab_table_size - 1;
    }
    return cab_table[n];
}

static const float no_sum = 1e10;

#include "faust/cabinet_impulse_former.cc"

static int cab_load_ui(const UiBuilder& builder, int format) {
    if (!(format & UI_FORM_STACK)) {
	return -1;
    }
    builder.openHorizontalhideBox("");
    builder.create_selector_no_caption("cab.select");
    builder.closeBox();
    builder.openVerticalBox("");
    {
	builder.openHorizontalBox("");
	{
	    builder.create_selector_no_caption("cab.select");
	    builder.create_small_rackknob("cab.bass", "bass");
	    builder.create_small_rackknob("cab.treble", "treble");
	    builder.create_small_rackknobr("cab.Level", "level");
	}
	builder.closeBox();
    }
    builder.closeBox();
    return 0;
}

CabinetConvolver::CabinetConvolver(EngineControl& engine, sigc::slot<void> sync, gx_resample::BufferResampler& resamp):
    BaseConvolver(engine, sync, resamp),
    current_cab(-1),
    level(0),
    cabinet(0),
    bass(0),
    treble(0),
    sum(no_sum),
    cab_names(new value_pair[cab_table_size+1]),
    impf() {
    for (unsigned int i = 0; i < cab_table_size; ++i) {
	CabEntry& cab = getCabEntry(i);
	cab_names[i].value_id = cab.value_id;
	cab_names[i].value_label = cab.value_label;
    }
    cab_names[cab_table_size].value_id = 0;
    cab_names[cab_table_size].value_label = 0;
    id = "cab";
    name = N_("Cabinet");
    category = N_("Tone control");
    load_ui = cab_load_ui;
    mono_audio = run_cab_conf;
    register_params = register_cab;
}

CabinetConvolver::~CabinetConvolver() {
    delete[] cab_names;
}

bool CabinetConvolver::do_update() {
    bool configure = cabinet_changed();
    if (conv.is_runnable()) {
	conv.set_not_runnable();
	sync();
	conv.stop_process();
    }
    CabDesc& cab = *getCabEntry(cabinet).data;
    if (current_cab == -1) {
	impf.init(cab.ir_sr);
    }
    float cab_irdata_c[cab.ir_count];
    impf.compute(cab.ir_count,cab.ir_data,cab_irdata_c);
    while (!conv.checkstate());
    if (configure) {
	if (!conv.configure(cab.ir_count, cab_irdata_c, cab.ir_sr)) {
	    return false;
	}
    } else {
	if (!conv.update(cab.ir_count, cab_irdata_c, cab.ir_sr)) {
	    return false;
	}
    }
    update_cabinet();
    update_sum();
    return conv_start();
}

bool CabinetConvolver::do_only_update() {
    CabDesc& cab = *getCabEntry(cabinet).data;
    float cab_irdata_c[cab.ir_count];
    impf.compute(cab.ir_count,cab.ir_data,cab_irdata_c);

	if (!conv.update(cab.ir_count, cab_irdata_c, cab.ir_sr)) {
	    return false;
	}
    update_sum();
    return true;
}

bool CabinetConvolver::start(bool force) {
    if (force) {
	current_cab = -1;
    }
    if (cabinet_changed() || sum_changed()) {
	return do_update();
    } else {
	while (!conv.checkstate());
	if (!conv.is_runnable()) {
	    return conv_start();
	}
	return true;
    }
}

void CabinetConvolver::check_update() {
    if (cabinet_changed() || sum_changed()) {
	do_update();
    } 
}

void CabinetConvolver::run_cab_conf(int count, float *input0, float *output0, PluginDef *p) {
    CabinetConvolver& self = *static_cast<CabinetConvolver*>(p);
    if (!self.conv.compute(count, output0)) {
	self.engine.overload(EngineControl::ov_Convolver, "cab");
    }
}

int CabinetConvolver::register_cab(const ParamReg& reg) {
    CabinetConvolver& cab = *static_cast<CabinetConvolver*>(reg.plugin);
    reg.registerIEnumVar("cab.select", "select", "B", "", cab.cab_names, &cab.cabinet, 0);
    reg.registerVar("cab.Level", "",  "S", "", &cab.level,  1.0, 0.5, 5.0, 0.5);
    reg.registerVar("cab.bass", "",   "S", "", &cab.bass,   0.0, -10.0, 10.0, 0.5);
    reg.registerVar("cab.treble", "", "S", "", &cab.treble, 0.0, -10.0, 10.0, 0.5);
    cab.impf.register_par(reg);
    return 0;
}

/****************************************************************
 ** class PreampConvolver
 */

struct PreDesc {
    int ir_count;
    int ir_sr;
    float ir_data[];
};

template <int tab_size>
struct PreDesc_imp {
    int ir_count;
    int ir_sr;
    float ir_data[tab_size];
    operator PreDesc&() { return *(PreDesc*)this; }
};

#include "gx_preamp_data.cc"

struct PreEntry {
    const char *value_id;
    const char *value_label;
    PreDesc *data;
} pre_table[] = {
    { "AC30",        N_("AC30"),        &static_cast<PreDesc&>(pre_data_ac30) },
    { "Bassman",     N_("Bassman"),     &static_cast<PreDesc&>(pre_data_bassman) },
    { "Tube",        N_("Tube"),        &static_cast<PreDesc&>(pre_data_tube) },
    { "Fender",      N_("Fender"),      &static_cast<PreDesc&>(pre_data_fender) },
    { "JCM800",      N_("JCM800"),      &static_cast<PreDesc&>(pre_data_jcm800) },
    { "JTM45",       N_("JTM45"),       &static_cast<PreDesc&>(pre_data_jtm45) },
    { "Mesa Boogie", N_("Mesa Boogie"), &static_cast<PreDesc&>(pre_data_mesaboogie) },
    { "Boutique",    N_("Boutique"),    &static_cast<PreDesc&>(pre_data_boutique) },
    { "Ampeg",       N_("Ampeg"),       &static_cast<PreDesc&>(pre_data_ampeg) },
    { "Rectifier",   N_("Rectifier"),   &static_cast<PreDesc&>(pre_data_rectifier) },
};
static const unsigned int pre_table_size = sizeof(pre_table) / sizeof(pre_table[0]);

static PreEntry& getPreEntry(unsigned int n) {
    if (n >= pre_table_size) {
	n = pre_table_size - 1;
    }
    return pre_table[n];
}

#include "faust/preamp_impulse_former.cc"

static int pre_load_ui(const UiBuilder& builder, int format) {
    if (!(format & UI_FORM_STACK)) {
	return -1;
    }
    builder.openHorizontalhideBox("");
    builder.create_selector_no_caption("pre.select");
    builder.closeBox();
    builder.openVerticalBox("");
    {
	builder.openHorizontalBox("");
	{
	    builder.create_selector_no_caption("pre.select");
	    builder.create_small_rackknob("pre.bass", "bass");
	    builder.create_small_rackknob("pre.treble", "treble");
	    builder.create_small_rackknobr("pre.Level", "level");
	}
	builder.closeBox();
    }
    builder.closeBox();
    return 0;
}

PreampConvolver::PreampConvolver(EngineControl& engine, sigc::slot<void> sync, gx_resample::BufferResampler& resamp):
    BaseConvolver(engine, sync, resamp),
    current_pre(-1),
    level(0),
    preamp(0),
    bass(0),
    treble(0),
    sum(no_sum),
    pre_names(new value_pair[pre_table_size+1]),
    impf() {
    for (unsigned int i = 0; i < pre_table_size; ++i) {
	PreEntry& pre = getPreEntry(i);
	pre_names[i].value_id = pre.value_id;
	pre_names[i].value_label = pre.value_label;
    }
    pre_names[pre_table_size].value_id = 0;
    pre_names[pre_table_size].value_label = 0;
    id = "pre";
    name = N_("Amp impulse");
    category = N_("Tone control");
    load_ui = pre_load_ui;
    mono_audio = run_pre_conf;
    register_params = register_pre;
}

PreampConvolver::~PreampConvolver() {
    delete[] pre_names;
}

bool PreampConvolver::do_update() {
    bool configure = preamp_changed();
    if (conv.is_runnable()) {
	conv.set_not_runnable();
	sync();
	conv.stop_process();
    }
    PreDesc& pre = *getPreEntry(preamp).data;
    if (current_pre == -1) {
	impf.init(pre.ir_sr);
    }
    float pre_irdata_c[pre.ir_count];
    impf.compute(pre.ir_count,pre.ir_data,pre_irdata_c);
    while (!conv.checkstate());
    if (configure) {
	if (!conv.configure(pre.ir_count, pre_irdata_c, pre.ir_sr)) {
	    return false;
	}
    } else {
	if (!conv.update(pre.ir_count, pre_irdata_c, pre.ir_sr)) {
	    return false;
	}
    }
    update_preamp();
    update_sum();
    return conv_start();
}

bool PreampConvolver::do_only_update() {
    PreDesc& pre = *getPreEntry(preamp).data;
    float pre_irdata_c[pre.ir_count];
    impf.compute(pre.ir_count,pre.ir_data,pre_irdata_c);
	if (!conv.update(pre.ir_count, pre_irdata_c, pre.ir_sr)) {
	    return false;
	}
    update_sum();
    return true;
}

bool PreampConvolver::start(bool force) {
    if (force) {
	current_pre = -1;
    }
    if (preamp_changed() || sum_changed()) {
	return do_update();
    } else {
	while (!conv.checkstate());
	if (!conv.is_runnable()) {
	    return conv_start();
	}
	return true;
    }
}

void PreampConvolver::check_update() {
    if (preamp_changed() || sum_changed()) {
	do_update();
    }
}

void PreampConvolver::run_pre_conf(int count, float *input0, float *output0, PluginDef *p) {
    PreampConvolver& self = *static_cast<PreampConvolver*>(p);
    if (!self.conv.compute(count, output0)) {
	self.engine.overload(EngineControl::ov_Convolver, "pre");
    }
}

int PreampConvolver::register_pre(const ParamReg& reg) {
    PreampConvolver& pre = *static_cast<PreampConvolver*>(reg.plugin);
    reg.registerIEnumVar("pre.select", "select", "B", "", pre.pre_names, &pre.preamp, 0);
    reg.registerVar("pre.Level", "",  "S", "", &pre.level,  1.0, 0.1, 2.1, 0.1);
    reg.registerVar("pre.bass", "",   "S", "", &pre.bass,   0.0, -10.0, 10.0, 0.5);
    reg.registerVar("pre.treble", "", "S", "", &pre.treble, 0.0, -10.0, 10.0, 0.5);
    pre.impf.register_par(reg);
    return 0;
}

/****************************************************************
 ** class ContrastConvolver
 */

#include "faust/presence_level.cc"

ContrastConvolver::ContrastConvolver(EngineControl& engine, sigc::slot<void> sync, gx_resample::BufferResampler& resamp):
    BaseConvolver(engine, sync, resamp),
    level(0),
    sum(no_sum),
    presl() {
    id = "con";
    name = N_("Contrast convolver");
    mono_audio = run_contrast;
    register_params = register_con;
}

ContrastConvolver::~ContrastConvolver() {
}

bool ContrastConvolver::do_update() {
    bool configure = (sum == no_sum);
    if (conv.is_runnable()) {
	conv.set_not_runnable();
	sync();
	conv.stop_process();
    }
    if (configure) {
	presl.init(contrast_ir_desc.ir_sr);
    }
    float contrast_irdata_c[contrast_ir_desc.ir_count];
    presl.compute(contrast_ir_desc.ir_count,contrast_ir_desc.ir_data,contrast_irdata_c);
    while (!conv.checkstate());
    if (configure) {
	if (!conv.configure(contrast_ir_desc.ir_count, contrast_irdata_c, contrast_ir_desc.ir_sr)) {
	    return false;
	}
    } else {
	if (!conv.update(contrast_ir_desc.ir_count, contrast_irdata_c, contrast_ir_desc.ir_sr)) {
	    return false;
	}
    }
    update_sum();
    return conv_start();
}

bool ContrastConvolver::do_only_update() {
    float contrast_irdata_c[contrast_ir_desc.ir_count];
    presl.compute(contrast_ir_desc.ir_count,contrast_ir_desc.ir_data,contrast_irdata_c);
    
	if (!conv.update(contrast_ir_desc.ir_count, contrast_irdata_c, contrast_ir_desc.ir_sr)) {
	    return false;
	}
    update_sum();
    return true;
}

bool ContrastConvolver::start(bool force) {
    if (force) {
	sum = no_sum;
    }
    if (sum_changed()) {
	return do_update();
    } else {
	while (!conv.checkstate());
	if (!conv.is_runnable()) {
	    return conv_start();
	}
	return true;
    }
}

void ContrastConvolver::check_update() {
    if (sum_changed()) {
	do_update();
    }
}

int ContrastConvolver::register_con(const ParamReg& reg) {
    ContrastConvolver& self = *static_cast<ContrastConvolver*>(reg.plugin);
    reg.registerVar("con.Level", "",  "S", "", &self.level,  1.0, 0.5, 5.0, 0.5);
    self.presl.register_par(reg);
    return 0;
}

void ContrastConvolver::run_contrast(int count, float *input0, float *output0, PluginDef *p) {
    ContrastConvolver& self = *static_cast<ContrastConvolver*>(p);
    if (!self.conv.compute(count, output0)) {
	self.engine.overload(EngineControl::ov_Convolver, "contrast");
    }
}

/****************************************************************
 ** class LiveLooper
 */


LiveLooper::LiveLooper(ParamMap& param_, sigc::slot<void> sync_, const string& loop_dir_)
	: PluginDef(),
	  tape1(0),
	  tape2(0),
	  tape3(0),
	  tape4(0),
	  save1(false),
	  save2(false),
	  save3(false),
	  save4(false),
	  RP1(false),
	  RP2(false),
	  RP3(false),
	  RP4(false),
      preset_name("tape"),
      cur_name("tape"),
      loop_dir(loop_dir_),
      save_p(false),
      param(param_),
	  mem_allocated(false),
      sync(sync_),
      ready(false),
      plugin() {
    version = PLUGINDEF_VERSION;
	id = "dubber";
	name = N_("Dubber");
	groups = 0;
	description = N_("Live Looper"); // description (tooltip)
	category = N_("Echo / Delay");       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = activate_static;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
    plugin = this;
}

LiveLooper::~LiveLooper() {
    activate(false);
}

inline void LiveLooper::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<4194304; i++) tape1[i] = 0;
	for (int i=0; i<2; i++) RecSize1[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) iRec3[i] = 0;
	for (int i=0; i<2; i++) iRec4[i] = 0;
	for (int i=0; i<2; i++) iVec2[i] = 0;
	for (int i=0; i<4194304; i++) tape2[i] = 0;
	for (int i=0; i<2; i++) RecSize2[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) iRec8[i] = 0;
	for (int i=0; i<2; i++) iRec9[i] = 0;
	for (int i=0; i<2; i++) iVec4[i] = 0;
	for (int i=0; i<4194304; i++) tape3[i] = 0;
	for (int i=0; i<2; i++) RecSize3[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) iRec13[i] = 0;
	for (int i=0; i<2; i++) iRec14[i] = 0;
	for (int i=0; i<2; i++) iVec6[i] = 0;
	for (int i=0; i<4194304; i++) tape4[i] = 0;
	for (int i=0; i<2; i++) RecSize4[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) iRec18[i] = 0;
	for (int i=0; i<2; i++) iRec19[i] = 0;
}

void LiveLooper::clear_state_f_static(PluginDef *p)
{
	static_cast<LiveLooper*>(p)->clear_state_f();
}

inline void LiveLooper::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	IOTA1 = 0;
	IOTA2 = 0;
	IOTA3 = 0;
	IOTA4 = 0;
	IOTAR1 = 0;
	IOTAR2 = 0;
	IOTAR3 = 0;
	IOTAR4 = 0;
	fConst0 = (1e+01f / float(fmin(192000, fmax(1, fSamplingFreq))));
	fConst1 = (0 - fConst0);
    fConst2 = (1.0 / float(fmin(192000, fmax(1, fSamplingFreq))));
}

void LiveLooper::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<LiveLooper*>(p)->init(samplingFreq);
}

void LiveLooper::mem_alloc()
{
	if (!tape1) tape1 = new float[4194304];
	if (!tape2) tape2 = new float[4194304];
	if (!tape3) tape3 = new float[4194304];
	if (!tape4) tape4 = new float[4194304];
	mem_allocated = true;
    ready = true;
}

void LiveLooper::mem_free()
{
	mem_allocated = false;
	if (tape1) { delete tape1; tape1 = 0; }
	if (tape2) { delete tape2; tape2 = 0; }
	if (tape3) { delete tape3; tape3 = 0; }
	if (tape4) { delete tape4; tape4 = 0; }
    ready = false;
}

int LiveLooper::load_from_wave(std::string fname, float *tape)
{
    SF_INFO sfinfo;
    int n,f,c;
    int fSize = 0;
    sfinfo.format = 0;
    SNDFILE *sf = sf_open(fname.c_str(),SFM_READ,&sfinfo);
    if (sf ) {
        f = sfinfo.frames;
        c = sfinfo.channels;
        n = f*c;
        fSize = sf_read_float(sf,tape,n);
    }
    sf_close(sf);
    return fSize;
}

void LiveLooper::load_array(std::string name)
{
    RecSize1[1] = load_from_wave(loop_dir+name+"1.wav", tape1);
    IOTAR1= RecSize1[1] - int(RecSize1[1]*(100-fclips1)*0.01);
    
    RecSize2[1] = load_from_wave(loop_dir+name+"2.wav", tape2);
    IOTAR2= RecSize2[1] - int(RecSize2[1]*(100-fclips2)*0.01);
    
    RecSize3[1] = load_from_wave(loop_dir+name+"3.wav", tape3);
    IOTAR3= RecSize3[1] - int(RecSize3[1]*(100-fclips3)*0.01);
    
    RecSize4[1] = load_from_wave(loop_dir+name+"4.wav", tape4);
    IOTAR4= RecSize4[1] - int(RecSize4[1]*(100-fclips4)*0.01);
    
    cur_name = preset_name;
}

void LiveLooper::save_to_wave(std::string fname, float *tape, float fSize)
{
    SF_INFO sfinfo ;
    sfinfo.channels = 1;
    sfinfo.samplerate = fSamplingFreq;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    
    SNDFILE * sf = sf_open(fname.c_str(), SFM_WRITE, &sfinfo);
    if (sf) {
        size_t lSize = 4194304 - int(fSize/fConst2);
        sf_write_float(sf,tape, lSize);
        sf_write_sync(sf);
    }
    sf_close(sf);
}

void LiveLooper::save_array(std::string name)
{
    if (name.compare("tape")==0 || save_p) {
        if (save1) {
            save_to_wave(loop_dir+name+"1.wav",tape1,rectime0);
            save1 = false;
        }
        if (save2) {
            save_to_wave(loop_dir+name+"2.wav",tape2,rectime1);
            save2 = false;
        }
        if (save3) {
            save_to_wave(loop_dir+name+"3.wav",tape3,rectime2);
            save3 = false;
        }
        if (save4) {
            save_to_wave(loop_dir+name+"4.wav",tape4,rectime3);
            save4 = false;
        }
    }
}

int LiveLooper::activate(bool start)
{
	if (start) {
		if (!mem_allocated) {
			mem_alloc();
			clear_state_f();
            load_array(preset_name);
		}
	} else if (mem_allocated) {
        save_array(cur_name);
		mem_free();
	}
	return 0;
}

int LiveLooper::activate_static(bool start, PluginDef *p)
{
	return static_cast<LiveLooper*>(p)->activate(start);
}

void LiveLooper::set_p_state() {
    if (!preset_name.empty()) {
        ready = false;
        sync();
        activate(true);
        if(save_p) {
            save1 = true;
            save2 = true;
            save3 = true;
            save4 = true;
            cur_name = preset_name;
           // fprintf (stderr,"save_p: %s\n",cur_name.c_str());
        }
        activate(false);
        activate(true);
        ready = true;
        save_p = false;
    }
    //fprintf (stderr,"set_p_state: %s\n",preset_name.c_str());
}

void always_inline LiveLooper::compute(int count, float *input0, float *output0)
{
    if (!ready) return;
    // trigger save array on exit
	if(record1 || reset1) save1 = true;
    if(record2 || reset2) save2 = true;
    if(record3 || reset3) save3 = true;
    if(record4 || reset4) save4 = true;
    // make play/ reverse play button act as radio button
    if (rplay1 && !RP1) {play1 = 0.0;RP1=true;}
    else if (play1 && RP1) {rplay1 = 0.0;RP1=false;}
    if (rplay2 && !RP2) {play2 = 0.0;RP2=true;}
    else if (play2 && RP2) {rplay2 = 0.0;RP2=false;}
    if (rplay3 && !RP3) {play3 = 0.0;RP3=true;}
    else if (play3 && RP3) {rplay3 = 0.0;RP3=false;}
    if (rplay4 && !RP4) {play4 = 0.0;RP4=true;}
    else if (play4 && RP4) {rplay4 = 0.0;RP4=false;}
    // switch off record when buffer is full
    record1     = rectime0? record1 : 0.0;
	record2     = rectime1? record2 : 0.0;
	record3     = rectime2? record3 : 0.0;
	record4     = rectime3? record4 : 0.0;
    // reset clip when reset is pressed
    if (reset1) {fclip1=100.0;fclips1=0.0;}
    if (reset2) {fclip2=100.0;fclips2=0.0;}
    if (reset3) {fclip3=100.0;fclips3=0.0;}
    if (reset4) {fclip4=100.0;fclips4=0.0;}
    // switch off reset button when buffer is empty 
    reset1     = (rectime0 < 4194304*fConst2)? reset1 : 0.0;
	reset2     = (rectime1 < 4194304*fConst2)? reset2 : 0.0;
	reset3     = (rectime2 < 4194304*fConst2)? reset3 : 0.0;
	reset4     = (rectime3 < 4194304*fConst2)? reset4 : 0.0;
    // set play head position
    float ph1      = 1.0/(RecSize1[0] * 0.001);
    playh1 = (1-iVec0[0]) * fmin(1000,fmax(0,float(IOTAR1*ph1)));
    float ph2      = 1.0/(RecSize2[0] * 0.001);
    playh2 = (1-iVec2[0]) *  fmin(1000,fmax(0,float(IOTAR2*ph2)));
    float ph3      = 1.0/(RecSize3[0] * 0.001);
    playh3 = (1-iVec4[0]) *  fmin(1000,fmax(0,float(IOTAR3*ph3)));
    float ph4      = 1.0/(RecSize4[0] * 0.001);
    playh4 = (1-iVec6[0]) *  fmin(1000,fmax(0,float(IOTAR4*ph4)));
    // playback speed
    float speed1 = fspeed1;
    float speed2 = fspeed2;
    float speed3 = fspeed3;
    float speed4 = fspeed4;
    // engine var settings
	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * gain)));
	float 	fSlow1 = gain_out;
    int 	iSlow3 = int(record1);
	int 	iSlow4 = int((1 - reset1));
	float 	fSlow5 = (((1 - iSlow3) * gain1) * (play1+rplay1));
	int 	iSlow6 = int(record2);
	int 	iSlow7 = int((1 - reset2));
	float 	fSlow8 = (((1 - iSlow6) * gain2) * (play2+rplay2));
	int 	iSlow9 = int(record3);
	int 	iSlow10 = int((1 - reset3));
	float 	fSlow11 = (((1 - iSlow9) * gain3) * (play3+rplay3));
	int 	iSlow12 = int(record4);
	int 	iSlow13 = int((1 - reset4));
	float 	fSlow14 = (((1 - iSlow12) * gain4) * (play4+rplay4));
	float 	fSlow15 = (0.0001f * fSlow1);
    float   iClip1  = fclip1*0.01;
	float   iClip2  = fclip2*0.01;
	float   iClip3  = fclip3*0.01;
	float   iClip4  = fclip4*0.01;
	float   iClips1  = (100-fclips1)*0.01;
	float   iClips2  = (100-fclips2)*0.01;
	float   iClips3  = (100-fclips3)*0.01;
	float   iClips4  = (100-fclips4)*0.01;
    // run loop
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		float fTemp0 = ((float)input0[i] * fRec0[0]);
		iVec0[0] = iSlow3;
		float fTemp1 = (iSlow3 * fTemp0);
        RecSize1[0] = fmin(4194304, (int)(iSlow4 * (((iSlow3 - iVec0[1]) <= 0) * (iSlow3 + RecSize1[1]))));
		int iTemp2 = (4194304 - RecSize1[0]);
		rectime0 = iTemp2*fConst2;
        int iTemp3 = fmin(4194304-1, (int)(4194304 - iTemp2));
		if (iSlow3 == 1) {
        IOTA1 = IOTA1>int(iTemp3*iClip1)? iTemp3 - int(iTemp3*iClips1):IOTA1+1;
		tape1[IOTA1] = fTemp1;
        }
        if (rplay1) {
        IOTAR1 = IOTAR1-speed1< (iTemp3 - int(iTemp3*iClips1))? int(iTemp3*iClip1):(IOTAR1-speed1)-1;
        } else if (play1) {
        IOTAR1 = IOTAR1+speed1>int(iTemp3*iClip1)? iTemp3 - int(iTemp3*iClips1):(IOTAR1+speed1)+1;
        }
		
        float fTemp4 = ((int((fRec1[1] != 0.0f)))?((int(((fRec2[1] > 0.0f) & (fRec2[1] < 1.0f))))?fRec1[1]:0):((int(((fRec2[1] == 0.0f) & (iTemp3 != iRec3[1]))))?fConst0:((int(((fRec2[1] == 1.0f) & (iTemp3 != iRec4[1]))))?fConst1:0)));
		fRec1[0] = fTemp4;
		fRec2[0] = fmax(0.0f, fmin(1.0f, (fRec2[1] + fTemp4)));
		iRec3[0] = ((int(((fRec2[1] >= 1.0f) & (iRec4[1] != iTemp3))))?iTemp3:iRec3[1]);
		iRec4[0] = ((int(((fRec2[1] <= 0.0f) & (iRec3[1] != iTemp3))))?iTemp3:iRec4[1]);
		iVec2[0] = iSlow6;
		float fTemp5 = (iSlow6 * fTemp0);
		RecSize2[0] = fmin(4194304, (int)(iSlow7 * (((iSlow6 - iVec2[1]) <= 0) * (iSlow6 + RecSize2[1]))));
		int iTemp6 = (4194304 - RecSize2[0]);
		rectime1 = iTemp6*fConst2;
		int iTemp7 = fmin(4194304-1, (int)(4194304 - iTemp6));
		if (iSlow6 == 1) {
		IOTA2 = IOTA2>int(iTemp7*iClip2)? iTemp7 - int(iTemp7*iClips2):IOTA2+1;
		tape2[IOTA2] = fTemp5;
        }
		if (rplay2) {
        IOTAR2 = IOTAR2-speed2< (iTemp7 - int(iTemp7*iClips2))? int(iTemp7*iClip2):(IOTAR2-speed2)-1;
        } else if (play2) {
        IOTAR2 = IOTAR2+speed2>int(iTemp7*iClip2)? iTemp7 - int(iTemp7*iClips2):(IOTAR2+speed2)+1;
        }
		
        float fTemp8 = ((int((fRec6[1] != 0.0f)))?((int(((fRec7[1] > 0.0f) & (fRec7[1] < 1.0f))))?fRec6[1]:0):((int(((fRec7[1] == 0.0f) & (iTemp7 != iRec8[1]))))?fConst0:((int(((fRec7[1] == 1.0f) & (iTemp7 != iRec9[1]))))?fConst1:0)));
		fRec6[0] = fTemp8;
		fRec7[0] = fmax(0.0f, fmin(1.0f, (fRec7[1] + fTemp8)));
		iRec8[0] = ((int(((fRec7[1] >= 1.0f) & (iRec9[1] != iTemp7))))?iTemp7:iRec8[1]);
		iRec9[0] = ((int(((fRec7[1] <= 0.0f) & (iRec8[1] != iTemp7))))?iTemp7:iRec9[1]);
		iVec4[0] = iSlow9;
		float fTemp9 = (iSlow9 * fTemp0);
		RecSize3[0] = fmin(4194304, (int)(iSlow10 * (((iSlow9 - iVec4[1]) <= 0) * (iSlow9 + RecSize3[1]))));
		int iTemp10 = (4194304 - RecSize3[0]);
		rectime2 = iTemp10*fConst2;
		int iTemp11 = fmin(4194304-1, (int)(4194304 - iTemp10));
		if (iSlow9 == 1) {
		IOTA3 = IOTA3>int(iTemp11*iClip3)? iTemp11 - int(iTemp11*iClips3):IOTA3+1;
		tape3[IOTA3] = fTemp9;
        }
		if (rplay3) {
        IOTAR3 = IOTAR3-speed3< (iTemp11 - int(iTemp11*iClips3))? int(iTemp11*iClip3):(IOTAR3-speed3)-1;
        } else if (play3) {
        IOTAR3 = IOTAR3+speed3>int(iTemp11*iClip3)? iTemp11 - int(iTemp11*iClips3):(IOTAR3+speed3)+1;
        }
		
        float fTemp12 = ((int((fRec11[1] != 0.0f)))?((int(((fRec12[1] > 0.0f) & (fRec12[1] < 1.0f))))?fRec11[1]:0):((int(((fRec12[1] == 0.0f) & (iTemp11 != iRec13[1]))))?fConst0:((int(((fRec12[1] == 1.0f) & (iTemp11 != iRec14[1]))))?fConst1:0)));
		fRec11[0] = fTemp12;
		fRec12[0] = fmax(0.0f, fmin(1.0f, (fRec12[1] + fTemp12)));
		iRec13[0] = ((int(((fRec12[1] >= 1.0f) & (iRec14[1] != iTemp11))))?iTemp11:iRec13[1]);
		iRec14[0] = ((int(((fRec12[1] <= 0.0f) & (iRec13[1] != iTemp11))))?iTemp11:iRec14[1]);
		iVec6[0] = iSlow12;
		float fTemp13 = (iSlow12 * fTemp0);
		RecSize4[0] = fmin(4194304, (int)(iSlow13 * (((iSlow12 - iVec6[1]) <= 0) * (iSlow12 + RecSize4[1]))));
		int iTemp14 = (4194304 - RecSize4[0]);
		rectime3 = iTemp14*fConst2;
		int iTemp15 = fmin(4194304-1, (int)(4194304 - iTemp14));
		if (iSlow12 == 1) {
		IOTA4 = IOTA4>int(iTemp15*iClip4)? iTemp15 - int(iTemp15*iClips4):IOTA4+1;
		tape4[IOTA4] = fTemp13;
        }
		if (rplay4) {
        IOTAR4 = IOTAR4-speed4< (iTemp15 - int(iTemp15*iClips4))? int(iTemp15*iClip4):(IOTAR4-speed4)-1;
        } else if (play4) {
        IOTAR4 = IOTAR4+speed4>int(iTemp15*iClip4)? iTemp15 - int(iTemp15*iClips4):(IOTAR4+speed4)+1;
        }
		
        float fTemp16 = ((int((fRec16[1] != 0.0f)))?((int(((fRec17[1] > 0.0f) & (fRec17[1] < 1.0f))))?fRec16[1]:0):((int(((fRec17[1] == 0.0f) & (iTemp15 != iRec18[1]))))?fConst0:((int(((fRec17[1] == 1.0f) & (iTemp15 != iRec19[1]))))?fConst1:0)));
		fRec16[0] = fTemp16;
		fRec17[0] = fmax(0.0f, fmin(1.0f, (fRec17[1] + fTemp16)));
		iRec18[0] = ((int(((fRec17[1] >= 1.0f) & (iRec19[1] != iTemp15))))?iTemp15:iRec18[1]);
		iRec19[0] = ((int(((fRec17[1] <= 0.0f) & (iRec18[1] != iTemp15))))?iTemp15:iRec19[1]);
		output0[i] = (float)((fSlow15 * ((fSlow14 * ((fRec17[0] * tape4[int(IOTAR4)]) + ((1.0f - fRec17[0]) * tape4[int(IOTAR4)]))) + ((fSlow11 * ((fRec12[0] * tape3[int(IOTAR3)]) + ((1.0f - fRec12[0]) * tape3[int(IOTAR3)]))) + ((fSlow8 * ((fRec7[0] * tape2[int(IOTAR2)]) + ((1.0f - fRec7[0]) * tape2[int(IOTAR2)]))) + (fSlow5 * ((fRec2[0] * tape1[int(IOTAR1)]) + ((1.0f - fRec2[0]) * tape1[int(IOTAR1)]))))))) + (fTemp0));
		// post processing
		iRec19[1] = iRec19[0];
		iRec18[1] = iRec18[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		RecSize4[1] = RecSize4[0];
		iVec6[1] = iVec6[0];
		iRec14[1] = iRec14[0];
		iRec13[1] = iRec13[0];
		fRec12[1] = fRec12[0];
		fRec11[1] = fRec11[0];
		RecSize3[1] = RecSize3[0];
		iVec4[1] = iVec4[0];
		iRec9[1] = iRec9[0];
		iRec8[1] = iRec8[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		RecSize2[1] = RecSize2[0];
		iVec2[1] = iVec2[0];
		iRec4[1] = iRec4[0];
		iRec3[1] = iRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		RecSize1[1] = RecSize1[0];
		iVec0[1] = iVec0[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func LiveLooper::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
	static_cast<LiveLooper*>(p)->compute(count, input0, output0);
}

int LiveLooper::register_par(const ParamReg& reg)
{
	reg.registerVar("dubber.clip1","","S",N_("percentage clip at the delay length "),&fclip1, 1e+02f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clip2","","S",N_("percentage clip at the delay length "),&fclip2, 1e+02f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clip3","","S",N_("percentage clip at the delay length "),&fclip3, 1e+02f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clip4","","S",N_("percentage clip at the delay length "),&fclip4, 1e+02f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clips1","","S",N_("percentage cut on the delay start "),&fclips1, 0.0f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clips2","","S",N_("percentage cut on the delay start "),&fclips2, 0.0f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clips3","","S",N_("percentage cut on the delay start "),&fclips3, 0.0f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.clips4","","S",N_("percentage cut on the delay start "),&fclips4, 0.0f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.speed1","","S",N_("playback speed "),&fspeed1, 0.0f, -0.9f, 0.9f, 0.01f);
	reg.registerVar("dubber.speed2","","S",N_("playback speed "),&fspeed2, 0.0f, -0.9f, 0.9f, 0.01f);
	reg.registerVar("dubber.speed3","","S",N_("playback speed "),&fspeed3, 0.0f, -0.9f, 0.9f, 0.01f);
	reg.registerVar("dubber.speed4","","S",N_("playback speed "),&fspeed4, 0.0f, -0.9f, 0.9f, 0.01f);
	reg.registerNonMidiFloatVar("dubber.bar1",&rectime0, false, true, 0.0, 0.0, 96.0, 1.0);
	reg.registerNonMidiFloatVar("dubber.bar2",&rectime1, false, true, 0.0, 0.0, 96.0, 1.0);
	reg.registerNonMidiFloatVar("dubber.bar3",&rectime2, false, true, 0.0, 0.0, 96.0, 1.0);
	reg.registerNonMidiFloatVar("dubber.bar4",&rectime3, false, true, 0.0, 0.0, 96.0, 1.0);
	reg.registerVar("dubber.gain","","S",N_("overall gain of the input"),&gain, 0.0f, -2e+01f, 12.0f, 0.1f);
	reg.registerVar("dubber.level1","","S",N_("percentage of the delay gain level"),&gain1, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.level2","","S",N_("percentage of the delay gain level"),&gain2, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.level3","","S",N_("percentage of the delay gain level"),&gain3, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.level4","","S",N_("percentage of the delay gain level"),&gain4, 5e+01f, 0.0f, 1e+02f, 1.0f);
	reg.registerVar("dubber.mix","","S",N_("overall gain_out of the delay line in percent"),&gain_out, 1e+02f, 0.0f, 1.5e+02f, 1.0f);
	reg.registerVar("dubber.play1","","B",N_("play tape 1"),&play1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.play2","","B",N_("play tape 2"),&play2, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.play3","","B",N_("play tape 3"),&play3, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.play4","","B",N_("play tape 4"),&play4, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rplay1","","B",N_("play reverse"),&rplay1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rplay2","","B",N_("play reverse"),&rplay2, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rplay3","","B",N_("play reverse"),&rplay3, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rplay4","","B",N_("play reverse"),&rplay4, 0.0, 0.0, 1.0, 1.0);
	reg.registerNonMidiFloatVar("dubber.playh1",&playh1, false, true, 0.0, 0.0, 1000.0, 1.0);
	reg.registerNonMidiFloatVar("dubber.playh2",&playh2, false, true, 0.0, 0.0, 1000.0, 1.0);
	reg.registerNonMidiFloatVar("dubber.playh3",&playh3, false, true, 0.0, 0.0, 1000.0, 1.0);
	reg.registerNonMidiFloatVar("dubber.playh4",&playh4, false, true, 0.0, 0.0, 1000.0, 1.0);
	reg.registerVar("dubber.rec1","","B",N_("record"),&record1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rec2","","B",N_("record"),&record2, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rec3","","B",N_("record"),&record3, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.rec4","","B",N_("record"),&record4, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.reset1","","B",N_("erase"),&reset1, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.reset2","","B",N_("erase"),&reset2, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.reset3","","B",N_("erase"),&reset3, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("dubber.reset4","","B",N_("erase"),&reset4, 0.0, 0.0, 1.0, 1.0);
    param.reg_non_midi_par("dubber.savefile", &save_p, false);
    param.reg_preset_string("dubber.filename", "", &preset_name, "tape");
    param["dubber.filename"].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &LiveLooper::set_p_state)));
    return 0;
}

int LiveLooper::register_params_static(const ParamReg& reg)
{
	return static_cast<LiveLooper*>(reg.plugin)->register_par(reg);
}

inline int LiveLooper::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("dubber" "." p)
b.openHorizontalhideBox("");
b.create_feedback_switch(sw_pbutton,PARAM("play1"));
b.create_feedback_switch(sw_pbutton,PARAM("play2"));
b.create_feedback_switch(sw_pbutton,PARAM("play3"));
b.create_feedback_switch(sw_pbutton,PARAM("play4"));
b.closeBox();

b.openHorizontalBox("");
b.create_small_rackknob(PARAM("gain"), 0);

b.openTabBox("");

b.openHorizontalBox(N_("Tape 1"));
b.openpaintampBox("");

b.openVerticalBox("");
b.openHorizontalBox("");
b.insertSpacer();
b.openVerticalBox("");
b.insertSpacer();
b.create_p_display(PARAM("playh1"),PARAM("clips1"),PARAM("clip1"));
b.insertSpacer();
b.openHorizontalBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec1"));
b.create_feedback_switch(sw_pbutton,PARAM("play1"));
b.create_feedback_switch(sw_prbutton,PARAM("rplay1"));
b.create_feedback_switch(sw_button,PARAM("reset1"));
b.closeBox();
b.closeBox();

b.insertSpacer();
b.create_port_display(PARAM("bar1"), "buffer");
b.insertSpacer();
b.closeBox();
b.create_feedback_slider(PARAM("clips1"), "cut");
b.create_feedback_slider(PARAM("clip1"), "clip");
b.create_master_slider(PARAM("speed1"), "speed");

b.closeBox();
b.create_small_rackknob(PARAM("level1"), "level");

b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Tape 2"));
b.openpaintampBox("");
b.openVerticalBox("");

b.openHorizontalBox("");
b.insertSpacer();
b.openVerticalBox("");
b.insertSpacer();
b.create_p_display(PARAM("playh2"),PARAM("clips2"),PARAM("clip2"));
b.insertSpacer();
b.openHorizontalBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec2"));
b.create_feedback_switch(sw_pbutton,PARAM("play2"));
b.create_feedback_switch(sw_prbutton,PARAM("rplay2"));
b.create_feedback_switch(sw_button,PARAM("reset2"));
b.closeBox();
b.closeBox();
b.insertSpacer();
b.create_port_display(PARAM("bar2"), "buffer");
b.insertSpacer();
b.closeBox();
b.create_feedback_slider(PARAM("clips2"), "cut");
b.create_feedback_slider(PARAM("clip2"), "clip");
b.create_master_slider(PARAM("speed2"), "speed");

b.closeBox();

b.create_small_rackknob(PARAM("level2"), "level");
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Tape 3"));
b.openpaintampBox("");
b.openVerticalBox("");

b.openHorizontalBox("");
b.insertSpacer();
b.openVerticalBox("");
b.insertSpacer();
b.create_p_display(PARAM("playh3"),PARAM("clips3"),PARAM("clip3"));
b.insertSpacer();
b.openHorizontalBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec3"));
b.create_feedback_switch(sw_pbutton,PARAM("play3"));
b.create_feedback_switch(sw_prbutton,PARAM("rplay3"));
b.create_feedback_switch(sw_button,PARAM("reset3"));
b.closeBox();
b.closeBox();
b.insertSpacer();
b.create_port_display(PARAM("bar3"), "buffer");
b.insertSpacer();
b.closeBox();
b.create_feedback_slider(PARAM("clips3"), "cut");
b.create_feedback_slider(PARAM("clip3"), "clip");
b.create_master_slider(PARAM("speed3"), "speed");

b.closeBox();
b.create_small_rackknob(PARAM("level3"), "level");
b.closeBox();
b.closeBox();

b.openHorizontalBox(N_("Tape 4"));
b.openpaintampBox("");
b.openVerticalBox("");

b.openHorizontalBox("");
b.insertSpacer();
b.openVerticalBox("");
b.insertSpacer();
b.create_p_display(PARAM("playh4"),PARAM("clips4"),PARAM("clip4"));
b.insertSpacer();
b.openHorizontalBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec4"));
b.create_feedback_switch(sw_pbutton,PARAM("play4"));
b.create_feedback_switch(sw_prbutton,PARAM("rplay4"));
b.create_feedback_switch(sw_button,PARAM("reset4"));
b.closeBox();
b.closeBox();
b.insertSpacer();
b.create_port_display(PARAM("bar4"), "buffer");
b.insertSpacer();
b.closeBox();
b.create_feedback_slider(PARAM("clips4"), "cut");
b.create_feedback_slider(PARAM("clip4"), "clip");
b.create_master_slider(PARAM("speed4"), "speed");

b.closeBox();
b.create_small_rackknob(PARAM("level4"), "level");
b.closeBox();
b.closeBox();

b.closeBox();

b.create_small_rackknob(PARAM("mix"), 0);
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int LiveLooper::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<LiveLooper*>(b.plugin)->load_ui_f(b, form);
}

void LiveLooper::del_instance(PluginDef *p)
{
	delete static_cast<LiveLooper*>(p);
}

} // namespace gx_engine
