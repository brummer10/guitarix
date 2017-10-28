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
 ** class GxSeqSettings
 */

GxSeqSettings::GxSeqSettings()
    : seqline() {
}

GxSeqSettings& GxSeqSettings::operator=(GxSeqSettings const& seqset) {
    seqline = seqset.seqline;
    return *this;
}

void GxSeqSettings::writeJSON(gx_system::JsonWriter& w) const {
    w.begin_object(true);
    w.write_key("seq.seqline");
    w.begin_array();
    for (unsigned int i = 0; i < seqline.size(); i++) {
        w.write(seqline[i]);
    }
    w.end_array(true);
    w.end_object(true);
}

bool GxSeqSettings::operator==(const GxSeqSettings& seqset) const {
    if (seqline != seqset.seqline) {
	return false;
    }
    return true;
}

void GxSeqSettings::read_seqline(gx_system::JsonParser& jp) {
    seqline.clear();
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() == gx_system::JsonParser::value_number) {
        jp.next(gx_system::JsonParser::value_number);
        int p = jp.current_value_int();
        seqline.push_back(p);
    }
    jp.next(gx_system::JsonParser::end_array);
}

void GxSeqSettings::readJSON(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::begin_object);
    do {
        jp.next(gx_system::JsonParser::value_key);
        if (jp.current_value() == "seq.seqline") {
            read_seqline(jp);
        } else {
            gx_print_warning("seq settings", "unknown key: " + jp.current_value());
            jp.skip_object();
        }
    } while (jp.peek() == gx_system::JsonParser::value_key);
    jp.next(gx_system::JsonParser::end_object);
}

/****************************************************************
 ** class SeqParameter
 */

ParameterV<GxSeqSettings>::ParameterV(const string& id, GxSeqSettings *v)
    : Parameter(id, "", tp_special, None, true, false),
      json_value(),
      value(v),
      std_value(),
      value_storage(),
      changed() {
    std_value.seqline = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
}

SeqParameter *SeqParameter::insert_param(
    ParamMap &pmap, const string& id, GxSeqSettings *v) {
    SeqParameter *p = new SeqParameter(id, v);
    pmap.insert(p);
    return p;
}

SeqParameter::~ParameterV() {
}

SeqParameter::ParameterV(gx_system::JsonParser& jp)
 : Parameter(jp_next(jp, "Parameter")),
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
		"SeqParameter", Glib::ustring::compose("%1: unknown key: %2", _id, jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
}

void SeqParameter::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_key("Parameter"); Parameter::serializeJSON(jw);
    jw.write_key("value"); value->writeJSON(jw);
    jw.write_key("std_value"); std_value.writeJSON(jw);
    jw.end_object();
}

bool SeqParameter::on_off_value() {
    assert(false);
    return false;
}

void SeqParameter::stdJSON_value() {
    json_value = std_value;
}

void SeqParameter::writeJSON(gx_system::JsonWriter& jw) const {
    jw.write_key(_id.c_str());
    value->writeJSON(jw);
}

void SeqParameter::readJSON_value(gx_system::JsonParser& jp) {
    json_value.readJSON(jp);
}

bool SeqParameter::compareJSON_value() {
    return json_value == *value;
}

bool SeqParameter::set(const GxSeqSettings& val) const {
    if (val == *value) {
	return false;
    }
    *value = val;
    changed(value);
    return true;
}

void SeqParameter::setJSON_value() {
    set(json_value);
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
    if (fGainCor && std::abs(fGain - jcset.fGain) > 1e-4 * (fGain + jcset.fGain)) {
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
 ** class FixedBaseConvolver
 */


FixedBaseConvolver::FixedBaseConvolver(EngineControl& engine_, sigc::slot<void> sync_, gx_resample::BufferResampler& resamp)
    : PluginDef(),
      conv(resamp),
      activate_mutex(),
      engine(engine_),
      sync(sync_),
      activated(false),
      SamplingFreq(0),
      buffersize(0),
      bz(0.0),
      plugin() {
    version = PLUGINDEF_VERSION;
    set_samplerate = init;
    activate_plugin = activate;
    plugin = this;
    engine.signal_buffersize_change().connect(
	sigc::mem_fun(*this, &FixedBaseConvolver::change_buffersize));
}

FixedBaseConvolver::~FixedBaseConvolver() {
    update_conn.disconnect();
}

void FixedBaseConvolver::change_buffersize(unsigned int bufsize) {
    boost::mutex::scoped_lock lock(activate_mutex);
    buffersize = bufsize;
    conv.set_buffersize(static_cast<int>(ceil((bufsize*bz))));
    if (activated) {
	if (!bufsize) {
	    conv.stop_process();
	} else {
	    start(true);
	}
    }
}

void FixedBaseConvolver::init(unsigned int samplingFreq, PluginDef *p) {
    FixedBaseConvolver& self = *static_cast<FixedBaseConvolver*>(p);
    boost::mutex::scoped_lock lock(self.activate_mutex);
    self.SamplingFreq = samplingFreq;
    self.bz = 96000/samplingFreq;
    self.conv.set_buffersize(static_cast<int>(ceil((self.buffersize*self.bz))));
    self.conv.set_samplerate(self.bz*self.SamplingFreq);
    if (self.activated) {
	self.start(true);
    }
}

bool FixedBaseConvolver::check_update_timeout() {
    if (!activated || !plugin.get_on_off()) {
	return false;
    }
    check_update();
    return true;
}

int FixedBaseConvolver::activate(bool start, PluginDef *p) {
    FixedBaseConvolver& self = *static_cast<FixedBaseConvolver*>(p);
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
	    sigc::mem_fun(self, &FixedBaseConvolver::check_update_timeout), 200);
    } else {
	self.conv.stop_process();
    }
    self.activated = start;
    return 0;
}

int FixedBaseConvolver::conv_start() {
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
    { "4x12",        N_("4x12"),              &static_cast<CabDesc&>(cab_data_4x12) },
    { "2x12",        N_("2x12"),              &static_cast<CabDesc&>(cab_data_2x12) },
    { "1x12",        N_("1x12"),              &static_cast<CabDesc&>(cab_data_1x12) },
    { "4x10",        N_("4x10"),              &static_cast<CabDesc&>(cab_data_4x10) },
    { "2x10",        N_("2x10"),              &static_cast<CabDesc&>(cab_data_2x10) },
    { "HighGain",    N_("HighGain Style"),    &static_cast<CabDesc&>(cab_data_HighGain) },
    { "Twin",        N_("Twin Style"),        &static_cast<CabDesc&>(cab_data_Twin) },
    { "Bassman",     N_("Bassman Style"),     &static_cast<CabDesc&>(cab_data_Bassman) },
    { "Marshall",    N_("Marshall Style"),    &static_cast<CabDesc&>(cab_data_Marshall) },
    { "AC-30",       N_("AC-30 Style"),       &static_cast<CabDesc&>(cab_data_AC30) },
    { "Princeton",   N_("Princeton Style"),   &static_cast<CabDesc&>(cab_data_Princeton) },
    { "A2",          N_("A2 Style"),          &static_cast<CabDesc&>(cab_data_A2) },
    { "1x15",        N_("1x15"),              &static_cast<CabDesc&>(cab_data_1x15) },
    { "Mesa Boogie", N_("Mesa Boogie Style"), &static_cast<CabDesc&>(cab_data_mesa) },
    { "Briliant",    N_("Briliant"),          &static_cast<CabDesc&>(cab_data_briliant) },
    { "Vitalize",     N_("Vitalize"),         &static_cast<CabDesc&>(cab_data_vitalize) },
    { "Charisma",    N_("Charisma"),          &static_cast<CabDesc&>(cab_data_charisma) },
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
    if (format & UI_FORM_GLADE) {
	builder.load_glade_file("cabinet_ui.glade");
    return 0;
    } else if (format & UI_FORM_STACK) {
    builder.openHorizontalhideBox("");
    builder.create_selector_no_caption("cab.select");
    builder.closeBox();
    builder.openVerticalBox("");
    {
	builder.openHorizontalBox("");
	{
	    builder.insertSpacer();
	    builder.create_selector_no_caption("cab.select");
	    builder.create_small_rackknobr("cab.bass", "Bass");
	    builder.create_small_rackknobr("cab.treble", "Treble");
	    builder.create_mid_rackknob("cab.Level", "Level");
	}
	builder.closeBox();
    }
    builder.closeBox();
    return 0;
    } else {
    return -1;
    }

}

CabinetConvolver::CabinetConvolver(EngineControl& engine, sigc::slot<void> sync,
    gx_resample::BufferResampler& resamp):
    FixedBaseConvolver(engine, sync, resamp),
    current_cab(-1),
    level(0),
    cabinet(0),
    bass(0),
    treble(0),
    sum(no_sum),
    cab_names(new value_pair[cab_table_size+1]),
    impf(),
    smp() {
    for (unsigned int i = 0; i < cab_table_size; ++i) {
	CabEntry& cab = getCabEntry(i);
	cab_names[i].value_id = cab.value_id;
	cab_names[i].value_label = cab.value_label;
    }
    cab_names[cab_table_size].value_id = 0;
    cab_names[cab_table_size].value_label = 0;
    id = "cab";
    name = N_("Cabinet");
    category = N_("Tone Control");
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
	unsigned int sr = getSamplingFreq();
	unsigned int sru = 96000;
	unsigned int fact = sru/sr;
	
	smp.setup(sr, fact*sr);
	impf.init(cab.ir_sr);
    }
    float cab_irdata_c[cab.ir_count];
    impf.clear_state_f();
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
	FAUSTFLOAT buf[self.smp.max_out_count(count)];
	int ReCount = self.smp.up(count, output0, buf);
    if (!self.conv.compute(ReCount,buf)) {
	self.engine.overload(EngineControl::ov_Convolver, "cab");
    }
	self.smp.down(buf, output0);
}

int CabinetConvolver::register_cab(const ParamReg& reg) {
    CabinetConvolver& cab = *static_cast<CabinetConvolver*>(reg.plugin);
    reg.registerIEnumVar("cab.select", "select", "B", "", cab.cab_names, &cab.cabinet, 0);
    reg.registerVar("cab.Level", N_("Level"),  "S", N_("Level"), &cab.level,  1.0, 0.5, 5.0, 0.5);
    reg.registerVar("cab.bass", N_("Bass"),   "S", N_("Bass"), &cab.bass,   0.0, -10.0, 10.0, 0.5);
    reg.registerVar("cab.treble", N_("Treble"), "S", N_("Treble"), &cab.treble, 0.0, -10.0, 10.0, 0.5);
    cab.impf.register_par(reg);
    return 0;
}

//// STEREO /////
#include "faust/cabinet_impulse_former_st.cc"

static int cab_load_stereo_ui(const UiBuilder& builder, int format) {
    if (format & UI_FORM_GLADE) {
	builder.load_glade_file("cabinet_stereo_ui.glade");
    return 0;
    } else if (format & UI_FORM_STACK) {
    builder.openHorizontalhideBox("");
    builder.create_selector_no_caption("cab_st.select");
    builder.closeBox();
    builder.openVerticalBox("");
    {
	builder.openHorizontalBox("");
	{
	    builder.insertSpacer();
	    builder.create_selector_no_caption("cab_st.select");
	    builder.create_small_rackknobr("cab_st.bass", "Bass");
	    builder.create_small_rackknobr("cab_st.treble", "Treble");
	    builder.create_mid_rackknob("cab_st.Level", "Level");
	}
	builder.closeBox();
    }
    builder.closeBox();
    return 0;
    } else {
    return -1;
    }

}

CabinetStereoConvolver::CabinetStereoConvolver(EngineControl& engine, sigc::slot<void> sync,
    gx_resample::BufferResampler& resamp):
    FixedBaseConvolver(engine, sync, resamp),
    current_cab(-1),
    level(0),
    cabinet(0),
    bass(0),
    treble(0),
    sum(no_sum),
    cab_names(new value_pair[cab_table_size+1]),
    impf(),
    smp(),
    smps() {
    for (unsigned int i = 0; i < cab_table_size; ++i) {
	CabEntry& cab = getCabEntry(i);
	cab_names[i].value_id = cab.value_id;
	cab_names[i].value_label = cab.value_label;
    }
    cab_names[cab_table_size].value_id = 0;
    cab_names[cab_table_size].value_label = 0;
    id = "cab_st";
    name = N_("Cabinet");
    category = N_("Tone Control");
    load_ui = cab_load_stereo_ui;
    stereo_audio = run_cab_conf;
    register_params = register_cab;
}

CabinetStereoConvolver::~CabinetStereoConvolver() {
    delete[] cab_names;
}

bool CabinetStereoConvolver::do_update() {
    bool configure = cabinet_changed();
    if (conv.is_runnable()) {
	conv.set_not_runnable();
	sync();
	conv.stop_process();
    }
    CabDesc& cab = *getCabEntry(cabinet).data;
    if (current_cab == -1) {
	unsigned int sr = getSamplingFreq();
	unsigned int sru = 96000;
	unsigned int fact = sru/sr;
	
	smp.setup(sr, fact*sr);
	smps.setup(sr, fact*sr);
	impf.init(cab.ir_sr);
    }
    float cab_irdata_c[cab.ir_count];
    impf.clear_state_f();
    impf.compute(cab.ir_count,cab.ir_data,cab_irdata_c);
    while (!conv.checkstate());
    if (configure) {
	if (!conv.configure_stereo(cab.ir_count, cab_irdata_c, cab.ir_sr)) {
	    return false;
	}
    } else {
	if (!conv.update_stereo(cab.ir_count, cab_irdata_c, cab.ir_sr)) {
	    return false;
	}
    }
    update_cabinet();
    update_sum();
    return conv_start();
}

bool CabinetStereoConvolver::start(bool force) {
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

void CabinetStereoConvolver::check_update() {
    if (cabinet_changed() || sum_changed()) {
	do_update();
    } 
}

void CabinetStereoConvolver::run_cab_conf(int count, float *input0, float *input1, float *output0, float *output1, PluginDef *p) {
    CabinetStereoConvolver& self = *static_cast<CabinetStereoConvolver*>(p);
	FAUSTFLOAT buf[self.smp.max_out_count(count)];
	FAUSTFLOAT buf1[self.smps.max_out_count(count)];
	int ReCount = self.smp.up(count, output0, buf);
	self.smps.up(count, output1, buf1);
    if (!self.conv.compute_stereo(ReCount,buf,buf1)) {
	self.engine.overload(EngineControl::ov_Convolver, "cab_st");
    }
	self.smp.down(buf, output0);
	self.smps.down(buf1, output1);
}

int CabinetStereoConvolver::register_cab(const ParamReg& reg) {
    CabinetStereoConvolver& cab = *static_cast<CabinetStereoConvolver*>(reg.plugin);
    reg.registerIEnumVar("cab_st.select", "select", "B", "", cab.cab_names, &cab.cabinet, 0);
    reg.registerVar("cab_st.Level", N_("Level"),  "S", N_("Level"), &cab.level,  1.0, 0.5, 5.0, 0.5);
    reg.registerVar("cab_st.bass", N_("Bass"),   "S", N_("Bass"), &cab.bass,   0.0, -10.0, 10.0, 0.5);
    reg.registerVar("cab_st.treble", N_("Treble"), "S", N_("Treble"), &cab.treble, 0.0, -10.0, 10.0, 0.5);
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
    { "AC30",        N_("AC30 Style"),        &static_cast<PreDesc&>(pre_data_ac30) },
    { "Bassman",     N_("Bassman Style"),     &static_cast<PreDesc&>(pre_data_bassman) },
    { "Tube",        N_("Tube Style"),        &static_cast<PreDesc&>(pre_data_tube) },
    { "Fender",      N_("Fender Style"),      &static_cast<PreDesc&>(pre_data_fender) },
    { "JCM800",      N_("JCM800 Style"),      &static_cast<PreDesc&>(pre_data_jcm800) },
    { "JTM45",       N_("JTM45 Style"),       &static_cast<PreDesc&>(pre_data_jtm45) },
    { "Mesa Boogie", N_("Mesa Boogie Style"), &static_cast<PreDesc&>(pre_data_mesaboogie) },
    { "Boutique",    N_("Boutique Style"),    &static_cast<PreDesc&>(pre_data_boutique) },
    { "Ampeg",       N_("Ampeg Style"),       &static_cast<PreDesc&>(pre_data_ampeg) },
    { "Rectifier",   N_("Rectifier Style"),   &static_cast<PreDesc&>(pre_data_rectifier) },
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
    if (format & UI_FORM_GLADE) {
	builder.load_glade_file("ampimpulse_ui.glade");
    return 0;
    } else if (format & UI_FORM_STACK) {
    builder.openHorizontalhideBox("");
    builder.create_selector_no_caption("pre.select");
    builder.closeBox();
    builder.openVerticalBox("");
    {
	builder.openHorizontalBox("");
	{
	    builder.insertSpacer();
	    builder.create_selector_no_caption("pre.select");
	    builder.create_small_rackknobr("pre.bass", "Bass");
	    builder.create_small_rackknobr("pre.treble", "Treble");
	    builder.create_mid_rackknob("pre.Level", "Level");
	}
	builder.closeBox();
    }
    builder.closeBox();
    return 0;
	} else {
	return -1;
    }

}

PreampConvolver::PreampConvolver(EngineControl& engine, sigc::slot<void> sync,
    gx_resample::BufferResampler& resamp):
    FixedBaseConvolver(engine, sync, resamp),
    current_pre(-1),
    level(0),
    preamp(0),
    bass(0),
    treble(0),
    sum(no_sum),
    pre_names(new value_pair[pre_table_size+1]),
    impf(),
    smp() {
    for (unsigned int i = 0; i < pre_table_size; ++i) {
	PreEntry& pre = getPreEntry(i);
	pre_names[i].value_id = pre.value_id;
	pre_names[i].value_label = pre.value_label;
    }
    pre_names[pre_table_size].value_id = 0;
    pre_names[pre_table_size].value_label = 0;
    id = "pre";
    name = N_("Amp Impulse");
    category = N_("Tone Control");
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
	unsigned int sr = getSamplingFreq();
	unsigned int sru = 96000;
	unsigned int fact = sru/sr;
	
	smp.setup(sr, fact*sr);
	impf.init(pre.ir_sr);
    }
    float pre_irdata_c[pre.ir_count];
    impf.clear_state_f();
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
	FAUSTFLOAT buf[self.smp.max_out_count(count)];
	int ReCount = self.smp.up(count, output0, buf);
     if (!self.conv.compute(ReCount, buf)) {
	self.engine.overload(EngineControl::ov_Convolver, "pre");
    }
	self.smp.down(buf, output0);
}

int PreampConvolver::register_pre(const ParamReg& reg) {
    PreampConvolver& pre = *static_cast<PreampConvolver*>(reg.plugin);
    reg.registerIEnumVar("pre.select", "select", "B", "", pre.pre_names, &pre.preamp, 0);
    reg.registerVar("pre.Level", N_("Level"),  "S", N_("Level"), &pre.level,  1.0, 0.1, 2.1, 0.1);
    reg.registerVar("pre.bass", N_("Bass"),   "S", N_("Bass"), &pre.bass,   0.0, -10.0, 10.0, 0.5);
    reg.registerVar("pre.treble", N_("Treble"), "S", N_("Treble"), &pre.treble, 0.0, -10.0, 10.0, 0.5);
    pre.impf.register_par(reg);
    return 0;
}

/****************************************************************
 ** class ContrastConvolver
 */

#include "faust/presence_level.cc"

ContrastConvolver::ContrastConvolver(EngineControl& engine, sigc::slot<void> sync,
    gx_resample::BufferResampler& resamp):
    FixedBaseConvolver(engine, sync, resamp),
    level(0),
    sum(no_sum),
    presl(),
    smp() {
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
	unsigned int sr = getSamplingFreq();
	unsigned int sru = 96000;
	unsigned int fact = sru/sr;
	
	smp.setup(sr, fact*sr);
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
	FAUSTFLOAT buf[self.smp.max_out_count(count)];
	int ReCount = self.smp.up(count, output0, buf);
    if (!self.conv.compute(ReCount,buf)) {
	self.engine.overload(EngineControl::ov_Convolver, "contrast");
    }
	self.smp.down(buf, output0);
    
}

/****************************************************************
 ** class smbPitchShift
 */

#include "gx_livelooper.cc"

/****************************************************************
 ** class SCapture
 */

#include "gx_record.cc"

/****************************************************************
 ** class DrumSequencer
 */

#include "faust/drumseq.cc"

static const char* seq_groups[] = {
	"hat_closed.dsp", N_("DrumSequencer"),
	"kick.dsp", N_("DrumSequencer"),
	"snare.dsp", N_("DrumSequencer"),
	"tom.dsp", N_("DrumSequencer"),
	"sequencer", N_("DrumSequencer"),
	0
};

DrumSequencer::DrumSequencer(ParamMap& param_)
	: PluginDef(), 
	  Vectom(0),
	  Vectom1(0),
	  Vectom2(0),
	  Veckick(0),
	  Vecsnare(0),
	  Vechat(0),
	  param(param_),
	  tomset(),
	  tomp(0),
	  tomset1(),
	  tomp1(0),
	  tomset2(),
	  tomp2(0),
	  snareset(),
	  snarep(0),
	  hatset(),
	  hatp(0),
	  kickset(),
	  kickp(0),
	  plugin() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "seq";
	name = N_("DrumSequencer");
	groups = seq_groups;
	description = N_("Simple Drum Step Sequencer"); // description (tooltip)
	category = N_("Misc");       // category
	shortname = N_("Drum");     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	delete_instance = del_instance;
	plugin = this;
}

DrumSequencer::~DrumSequencer() {
}

inline void DrumSequencer::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	counter = 0;
	step = 0;
	step_orig = 0;
	fSlow1 = 0.0;
	fSlow3 = 0.0;
	fSlow5 = 0.0;
	fSlow7 = 0.0;
	fSlow18 = 150.0;
	position = 0.0;
	drums.init(samplingFreq);
}

void DrumSequencer::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<DrumSequencer*>(p)->init(samplingFreq);
}

int DrumSequencer::min_seq_size(){
	int i = min(min(min(Vectom.size(),Veckick.size()),min(Vechat.size(),Vecsnare.size())),min(Vectom1.size(),Vectom2.size()));
	return i-1;
}

void DrumSequencer::reset_tom() {
	Vectom = tomset.getseqline() ;
	seq_size = min_seq_size();
}

void DrumSequencer::reset_tom1() {
	Vectom1 = tomset1.getseqline() ;
	seq_size = min_seq_size();
}

void DrumSequencer::reset_tom2() {
	Vectom2 = tomset2.getseqline() ;
	seq_size = min_seq_size();
}

void DrumSequencer::reset_kick() {
	Veckick = kickset.getseqline() ;
	seq_size = min_seq_size();
}

void DrumSequencer::reset_hat() {
	Vechat = hatset.getseqline() ;
	seq_size = min_seq_size();
}

void DrumSequencer::reset_snare() {
	Vecsnare = snareset.getseqline() ;
	seq_size = min_seq_size();
}

void always_inline DrumSequencer::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow15 = (60.0/double(fsliderbpm*ftact))*fSamplingFreq;
	counter += count;
	int iSlow15 = (int)fSlow15;
	// beat
	if (counter >= iSlow15) {
		int istep = (int)step;
		fSlow1 = double(Vecsnare[istep]);
		// disable hat when sequencer runs to fast
		if (iSlow15 > 4800) {
			fSlow3 = double(Vechat[istep]);
		}
		fSlow5 = double(Veckick[istep]);
        // only one tom at time
		if (Vectom2[istep]) {
			fSlow7 = double(Vectom2[istep]);
			fSlow18 = 150.0;
			fSlow20 = fSlow16;
		} else if (Vectom1[istep]) {
			fSlow7 = double(Vectom1[istep]);
			fSlow18 = 128.0;
			fSlow20 = fSlow14;
		} else if(Vectom[istep]) {
			fSlow7 = double(Vectom[istep]);
			fSlow18 = 90.0;
			fSlow20 = fSlow12;
		}
		int m = ftact;
		int r = rand()%(m+1 - (-m))+ (-m);
		counter = 0; //int(r*fsliderhum);
		
		if (step<seq_size) step = fmin(seq_size,fmax(0,step + 1.0 + int(r*fsliderhum)));
		else step = 0.0;
		if (step_orig<seq_size) step_orig += 1.0;
		else step_orig = 0.0;
		double ph1 = 2300.0/seq_size;
		position = fmin(2300,fmax(0,(step*ph1)));
	} else {
		fSlow1 = 0.0;
		fSlow3 = 0.0;
		fSlow5 = 0.0;
		fSlow7 = 0.0;
	}
	drums.compute(count,input0,output0);
}

void __rt_func DrumSequencer::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<DrumSequencer*>(p)->compute(count, input0, output0);
}

int DrumSequencer::register_par(const ParamReg& reg)
{
	reg.registerNonMidiFloatVar("seq.hat_closed.dsp.gate",&fSlow3, false, true, 0.0, 0.0, 1.0, 1.0);
	reg.registerNonMidiFloatVar("seq.kick.dsp.gate",&fSlow5, false, true, 0.0, 0.0, 1.0, 1.0);
	reg.registerNonMidiFloatVar("seq.snare.dsp.gate",&fSlow1, false, true, 0.0, 0.0, 1.0, 1.0);
	reg.registerNonMidiFloatVar("seq.tom.dsp.gate",&fSlow7, false, true, 0.0, 0.0, 1.0, 1.0);
	reg.registerNonMidiSharedVar("seq.tom.dsp.Gainf",&fSlow20, false, true, -2e+01, -6e+01, 4e+01, 0.1);
	reg.registerVar("seq.tom.dsp.Gain","","S",N_("Volume level in decibels"),&fSlow12, -2e+01, -6e+01, 4e+01, 0.1);
	reg.registerVar("seq.tom.dsp.Gain1","","S",N_("Volume level in decibels"),&fSlow14, -2e+01, -6e+01, 4e+01, 0.1);
	reg.registerVar("seq.tom.dsp.Gain2","","S",N_("Volume level in decibels"),&fSlow16, -2e+01, -6e+01, 4e+01, 0.1);
	reg.registerNonMidiFloatVar("seq.tom.dsp.freq",&fSlow18, false, true, 9e+01, 9e+01, 1.5e+02, 1.0);
	reg.registerVar("seq.bpm","","S",N_("Beats per Minute"),&fsliderbpm, 120, 24, 360, 1);
	static const value_pair ftact_values[] = {{"1/4"},{"2/4"},{"3/4"},{"4/4"},{0}};
	reg.registerEnumVar("seq.tact","","S",N_("select tact"),ftact_values,&ftact, 4.0, 1.0, 4.0, 1.0);
	reg.registerVar("seq.asequences","","S",N_("Number of Sequences"),&fsec, 24.0, 24.0, 240.0, 4.0);
	reg.registerVar("seq.hum","","B",N_("Randomize Sequence"),&fsliderhum, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("seq.npreset","","BO",N_("Load next unit preset"),0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("seq.ppreset","","BO",N_("Load previous unit preset"),0, 0.0, 0.0, 1.0, 1.0);
	reg.registerNonMidiFloatVar("seq.pos",&position, false, true, 0.0, 0.0, 2300.0, 1.0);
	reg.registerNonMidiFloatVar("seq.step",&step, false, true, 0.0, 0.0, 240.0, 1.0);
	reg.registerNonMidiFloatVar("seq.step_orig",&step_orig, false, true, 0.0, 0.0, 240.0, 1.0);
	reg.registerVar("seq.set_step","","BO",N_("Set stepper one Beat back"),0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("seq.set_fstep","","BO",N_("Set stepper one Beat forward"),0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("seq.set_sync","","BO",N_("Set stepper back on Beat "),0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("seq.reset_step","","BO",N_("Set stepper one Start"),0, 0.0, 0.0, 1.0, 1.0);
	reg.registerVar("seq.follow","","BO",N_("follow playhead"),0, 0.0, 0.0, 1.0, 1.0);
	for (int i=0; i<24; i++) Vectom.push_back(0);
	for (int i=0; i<24; i++) Vectom1.push_back(0);
	for (int i=0; i<24; i++) Vectom2.push_back(0);
	for (int i=0; i<24; i++) Veckick.push_back(0);
	for (int i=0; i<24; i++) Vechat.push_back(0);
	for (int i=0; i<24; i++) Vecsnare.push_back(0);
	seq_size = min_seq_size();
	tomp = SeqParameter::insert_param(param, "seq.sequencer.tom", &tomset);
	tomp1 = SeqParameter::insert_param(param, "seq.sequencer.tom1", &tomset1);
	tomp2 = SeqParameter::insert_param(param, "seq.sequencer.tom2", &tomset2);
	snarep = SeqParameter::insert_param(param, "seq.sequencer.snare", &snareset);
	hatp = SeqParameter::insert_param(param, "seq.sequencer.hat", &hatset);
	kickp = SeqParameter::insert_param(param, "seq.sequencer.kick", &kickset);
	tomp->signal_changed().connect(
	sigc::hide(
		sigc::mem_fun(this, &DrumSequencer::reset_tom)));
	tomp1->signal_changed().connect(
	sigc::hide(
		sigc::mem_fun(this, &DrumSequencer::reset_tom1)));
	tomp2->signal_changed().connect(
	sigc::hide(
		sigc::mem_fun(this, &DrumSequencer::reset_tom2)));
	snarep->signal_changed().connect(
	sigc::hide(
		sigc::mem_fun(this, &DrumSequencer::reset_snare)));
	hatp->signal_changed().connect(
	sigc::hide(
		sigc::mem_fun(this, &DrumSequencer::reset_hat)));
	kickp->signal_changed().connect(
	sigc::hide(
		sigc::mem_fun(this, &DrumSequencer::reset_kick)));

	drums.register_par(reg);
	return 0;
}

int DrumSequencer::register_params_static(const ParamReg& reg)
{
	return static_cast<DrumSequencer*>(reg.plugin)->register_par(reg);
}

void DrumSequencer::del_instance(PluginDef *p)
{
	delete static_cast<DrumSequencer*>(p);
}

/****************************************************************************
*
* NAME: smbPitchShift.cpp
* VERSION: 1.2
* HOME URL: http://www.dspdimension.com
* KNOWN BUGS: none
* 
*
* COPYRIGHT 1999-2009 Stephan M. Bernsee <smb [AT] dspdimension [DOT] com>
* 
* Modified for guitarix by Hermann Meyer 2014
*
* 						The Wide Open License (WOL)
*
* Permission to use, copy, modify, distribute and sell this software and its
* documentation for any purpose is hereby granted without fee, provided that
* the above copyright notice and this license appear in all source copies. 
* THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY OF
* ANY KIND. See http://www.dspguru.com/wol.htm for more information.
*
*****************************************************************************/ 

bool smbPitchShift::setParameters(int sampleRate_)
{
    numSampsToProcess = int(engine.get_buffersize());
    fftFrameSize = numSampsToProcess/4;
    sampleRate = int(sampleRate_);
    assert(sampleRate>0);
    osamp = 8;
    osamp1 = 1./osamp;
    osamp2 = 2.*M_PI*osamp1;
    mpi = (1./(2.*M_PI)) * osamp;
    mpi1 = 1./M_PI;
    fpb = 0; 
    expect = 0; 
    hanning = 0; 
    hanningd = 0;
    resampin = 0;
    resampout = 0;
    indata2 = 0;
    resamp.setup(sampleRate,4);
    gRover = inFifoLatency;
    return true;
}

smbPitchShift::smbPitchShift(ParamMap& param_, EngineControl& engine_, sigc::slot<void> sync_):
  PluginDef(),
  engine(engine_),
  mem_allocated(false),
  sync(sync_),
  ready(false),
  param(param_),
  ftPlanForward(0),
  ftPlanInverse(0),
  plugin() {
    memset(gInFIFO, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gOutFIFO, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gLastPhase, 0, (MAX_FRAME_LENGTH/2+1)*sizeof(float));
    memset(gSumPhase, 0, (MAX_FRAME_LENGTH/2+1)*sizeof(float));
    memset(gOutputAccum, 0, 2*MAX_FRAME_LENGTH*sizeof(float));
    memset(gAnaFreq, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gAnaMagn, 0, MAX_FRAME_LENGTH*sizeof(float));
    version = PLUGINDEF_VERSION;
    id = "smbPitchShift";
    name = N_("Detune");
    groups = 0;
    description = N_("detune and pitch shift up"); // description (tooltip)
    category = N_("Misc");       // category
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init;
    activate_plugin = activate_static;
    register_params = registerparam;
    delete_instance = del_instance;
    load_ui = load_ui_f_static;
    plugin = this;
    engine.signal_buffersize_change().connect(
    sigc::mem_fun(*this, &smbPitchShift::change_buffersize));
}

void smbPitchShift::init(unsigned int samplingFreq, PluginDef *plugin) {
    static_cast<smbPitchShift*>(plugin)->setParameters(samplingFreq);
    
}

void smbPitchShift::clear_state()
{
    stepSize = fftFrameSize/osamp;
    freqPerBin = (double)(sampleRate/4)/(double)fftFrameSize;
    freqPerBin1 = (1/freqPerBin)*osamp2;
    freqPerBin2 = freqPerBin*mpi;
    expct = 2.*M_PI*(double)stepSize/(double)fftFrameSize;
    inFifoLatency = fftFrameSize-stepSize;
    fftFrameSize3 = 2. * (1./ ((double)(fftFrameSize2)*osamp));
    fftFrameSize4 = 1./(double)fftFrameSize;
    ai = 0;
    aio = 0;
    ii = 0;
    tone =0;
    memset(gInFIFO, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gOutFIFO, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gLastPhase, 0, (MAX_FRAME_LENGTH/2+1)*sizeof(float));
    memset(gSumPhase, 0, (MAX_FRAME_LENGTH/2+1)*sizeof(float));
    memset(gOutputAccum, 0, 2*MAX_FRAME_LENGTH*sizeof(float));
    memset(gAnaFreq, 0, MAX_FRAME_LENGTH*sizeof(float));
    memset(gAnaMagn, 0, MAX_FRAME_LENGTH*sizeof(float));
    for (k = 0; k < fftFrameSize2;k++) {
        fpb[k] = (double)k*freqPerBin;
    }
    for (k = 0; k < fftFrameSize2;k++) {
        expect[k] = (double)k*expct;
    }
    for (k = 0; k < fftFrameSize;k++) {
        hanning[k] = 0.5*(1-cos(2.*M_PI*(double)k/((double)fftFrameSize)));
    }
    for (k = 0; k < fftFrameSize;k++) {
        hanningd[k] = 0.5*(1-cos(2.*M_PI*(double)k * fftFrameSize4)) * fftFrameSize3; 
    }
    for (k = 0; k < fftFrameSize;k++) {
        resampin[k] = 0.0; 
    }
    for (k = 0; k < fftFrameSize;k++) {
        resampin2[k] = 0.0; 
    }
    for (k = 0; k < fftFrameSize*4;k++) {
        resampout[k] = 0.0; 
    }
    for (k = 0; k < fftFrameSize*4;k++) {
        indata2[k] = 0.0; 
    }
    gRover = inFifoLatency;
    mem_allocated = true;
    ready = true;
}

void smbPitchShift::mem_alloc()
{
    numSampsToProcess = int(engine.get_buffersize());
    assert(numSampsToProcess>0);
    numSampsToResamp = numSampsToProcess/4;
    sampleRate = int(engine.get_samplerate());
    assert(sampleRate>0);
    
    switch(latency) {
      case(0):
        if (numSampsToProcess <= 2048) {
          fftFrameSize = 512 ; 
        } else {
          fftFrameSize = numSampsToProcess*0.25 ;
        }
        break;
      case(1):
        fftFrameSize = numSampsToProcess;
        break;
      case(2):
        fftFrameSize = numSampsToProcess*0.25;
        break;
      default:
        if (numSampsToProcess <= 2048) {
          fftFrameSize = 512 ; 
        } else {
          fftFrameSize = numSampsToProcess*0.25 ;
        }
        break;
    }
    fftFrameSize2 = fftFrameSize/2;

    try {
        //create FFTW plan
        ftPlanForward = fftwf_plan_dft_1d(fftFrameSize, fftw_in, fftw_out, FFTW_FORWARD, FFTW_ESTIMATE);
        ftPlanInverse = fftwf_plan_dft_1d(fftFrameSize, fftw_in, fftw_out, FFTW_BACKWARD, FFTW_ESTIMATE);
        // alloc buffers
        fpb = new float[fftFrameSize2];
        expect = new float[fftFrameSize2];
        hanning = new float[fftFrameSize];
        hanningd = new float[fftFrameSize];
        resampin = new float[fftFrameSize];
        resampin2 = new float[fftFrameSize];
        resampout = new float[fftFrameSize*4];
        indata2 = new float[fftFrameSize*4];
    } catch(...) {
            gx_print_error("detune", "cant allocate memory pool");
            return;
        }
    clear_state();
}

void smbPitchShift::mem_free()
{
    ready = false;
    mem_allocated = false;
    if (fpb) { delete fpb; fpb = 0; }
    if (expect) { delete expect; expect = 0; }
    if (hanning) { delete hanning; hanning = 0; }
    if (hanningd) { delete hanningd; hanningd = 0; }
    if (resampin) { delete resampin; resampin = 0; }
    if (resampin2) { delete resampin2; resampin2 = 0; }
    if (resampout) { delete resampout; resampout = 0; }
    if (indata2) { delete indata2; indata2 = 0; }
    if (ftPlanForward)
        {fftwf_destroy_plan(ftPlanForward);ftPlanForward = 0; }
    if (ftPlanInverse) 
        { fftwf_destroy_plan(ftPlanInverse);ftPlanInverse = 0; }
}

int smbPitchShift::activate(bool start)
{
    if (start) {
        if (!mem_allocated) {
            mem_alloc();
        }
    } else if (mem_allocated) {
        mem_free();
    }
    return 0;
}

void smbPitchShift::change_buffersize(unsigned int size)
{
    sync();
    ready = false;
    if (mem_allocated) {
        mem_free();
        mem_alloc();
    }
}

void smbPitchShift::change_latency()
{
    sync();
    ready = false;
    if (mem_allocated) {
        mem_free();
        mem_alloc();
    }
}

smbPitchShift::~smbPitchShift()
{
    if (mem_allocated) {
        mem_free();
    }
}

// -----------------------------------------------------------------------------------------------------------------
void __rt_func smbPitchShift::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<smbPitchShift*>(p)->PitchShift(count, input0, output0);
}


void always_inline smbPitchShift::PitchShift(int count, float *indata, float *outdata)
{
    
    if (!ready || count != numSampsToProcess)  {
        if (indata != outdata)
        {
            memcpy(outdata,indata,count*sizeof(float));
        }
        return;
    }
    
    resamp.down(numSampsToResamp,indata,resampin);
    double     fSlow0 = (0.01 * wet);
    double     fSlow1 = (0.01 * dry);

    // collect data for latency compensation
    for (i = 0; i < count; i++){
        indata2[ii] = indata[i];
        ii++;
    }
    // collect data for fft
    for (i = 0; i < numSampsToResamp; i++){
        resampin2[ai] = resampin[i];
        ai++;
    }
    // now we have enough data
    if (ai>=fftFrameSize) {
        ai = 0;
        ii = 0;
        switch(octave) {
          case(0):
            tone =0;
            break;
          case(1):
            tone =12;
            break;
          case(2):
            tone =-12;
            break;
          default:
            tone =0;
            break;
        }
        float pitchShift = pow(2., (semitones+tone)*0.0833333333);
        /* main processing loop */
        for (i = 0; i < fftFrameSize; i++){

            /* As long as we have not yet collected enough data just read in */
            float fTemp = resampin2[i];
            gInFIFO[gRover] = fTemp;
            resampin2[i] = gOutFIFO[gRover-inFifoLatency];
            gRover++;

            /* now we have enough data for processing */
            if (gRover >= fftFrameSize) {
                gRover = inFifoLatency;

                /* do windowing and re,im interleave */
                for (k = 0; k < fftFrameSize;k++) {
                    fftw_in[k][0] = gInFIFO[k] * hanning[k];
                    fftw_in[k][1] = 0.0;
                }


                /* ***************** ANALYSIS ******************* */
                /* do transform */
                fftwf_execute(ftPlanForward);

                /* this is the analysis step */
                for (k = 0; k < fftFrameSize2; k++) {

                    /* de-interlace FFT buffer */
                    real = fftw_out[k][0];
                    imag = fftw_out[k][1];

                    /* compute magnitude and phase */
                    magn = 2.*sqrt(real*real + imag*imag);
                    phase = atan2(imag,real);

                    /* compute phase difference */
                    tmp = phase - gLastPhase[k];
                    gLastPhase[k] = phase;

                    /* subtract expected phase difference */
                    tmp -= expect[k];

                    /* map delta phase into +/- Pi interval */
                    qpd = tmp*mpi1;
                    if (qpd >= 0) qpd += qpd&1;
                    else qpd -= qpd&1;
                    tmp -= M_PI*(double)qpd;

                    /* get deviation from bin frequency from the +/- Pi interval */
                    /* compute the k-th partials' true frequency */
                    tmp = fpb[k] + tmp*freqPerBin2;

                    /* store magnitude and true frequency in analysis arrays */
                    gAnaMagn[k] = magn;
                    gAnaFreq[k] = tmp;

                }

                /* ***************** PROCESSING ******************* */
                /* this does the actual pitch shifting */
                memset(gSynMagn, 0, fftFrameSize*sizeof(float));
                memset(gSynFreq, 0, fftFrameSize*sizeof(float));
                for (k = 1; k < fftFrameSize2-2; k++) { 
                    index = k*pitchShift;
                    if (index < fftFrameSize2) { 
                        if (index < fftFrameSize2*0.20)
                            gSynMagn[index] += gAnaMagn[k]*a; 
                        else if (index < fftFrameSize2*0.45)
                            gSynMagn[index] += gAnaMagn[k]*b; 
                        else if (index < fftFrameSize2*0.667)
                            gSynMagn[index] += gAnaMagn[k]*c; 
                        else 
                            gSynMagn[index] += gAnaMagn[k]*d; 
                           gSynFreq[index] = gAnaFreq[k] * pitchShift; 
                    } 
                }
                
                /* ***************** SYNTHESIS ******************* */
                /* this is the synthesis step */
                for (k = 0; k < fftFrameSize2; k++) {

                    /* get magnitude and true frequency from synthesis arrays */
                    magn = gSynMagn[k];
                    //tmp = gSynFreq[k];

                    /* subtract bin mid frequency */
                    /* get bin deviation from freq deviation */
                    /* take osamp into account */
                    /* add the overlap phase advance back in */
                    tmp = ((gSynFreq[k] - fpb[k]) * freqPerBin1) + expect[k];

                    /* accumulate delta phase to get bin phase */
                    gSumPhase[k] += tmp;
                    phase = gSumPhase[k];
                    if (magn == 0.0) continue;

                    /* get real and imag part and re-interleave */                
                    fftw_in[k][0] = magn * cos (phase);
                    fftw_in[k][1] = magn * sin (phase);
                } 

                /* do inverse transform */
                fftwf_execute(ftPlanInverse);
                /* do windowing and add to output accumulator */ 
                for(k=0; k < fftFrameSize; k++) {
                    gOutputAccum[k] += hanningd[k] * fftw_out[ k][0] ;
                }
                for (k = 0; k < stepSize; k++) gOutFIFO[k] = gOutputAccum[k];

                /* shift accumulator */
                memmove(gOutputAccum, gOutputAccum+stepSize, fftFrameSize*sizeof(float));

                /* move input FIFO */
                for (k = 0; k < inFifoLatency; k++) gInFIFO[k] = gInFIFO[k+stepSize];
            }
        }
        resamp.up(fftFrameSize,resampin2,resampout);
        aio = 0;
    }
    if(l) {
        for (i = 0; i < count; i++){
            outdata[i] = ((fSlow0 * resampout[aio]) + (fSlow1 *indata2[aio]));
            aio++;
        }
    } else {
        for (i = 0; i < count; i++){
            outdata[i] = ((fSlow0 * resampout[aio]) + (fSlow1 *indata[i]));
            aio++;
        }
    }
}

int smbPitchShift::register_par(const ParamReg& reg) 
{
    reg.registerVar("smbPitchShift.semitone", N_("Detune"), "S", "", &semitones, 0.0, -12., 12., 0.1);
    static const value_pair octave_values[] = {{"unison"},{"octave up"},{"octave down"},{0}};
    reg.registerIEnumVar("smbPitchShift.octave",N_("add harmonics"),"B",N_("add harmonics"),octave_values,&octave, 0);
    static const value_pair latency_values[] = {{"latency "},{"compensate"},{0}};
    reg.registerEnumVar("smbPitchShift.l",N_("compensate latency"),"S",N_("compensate latency"),latency_values,&l, 0.0f, 0.0f, 1.0f, 1.0f);
    static const value_pair latency_set[] = {{"high quality"},{"low quality"},{"realtime"},{0}};
    reg.registerIEnumVar("smbPitchShift.latency",N_("latency settings"),"B",N_("latency settings"),latency_set,&latency, 0);
    reg.registerVar("smbPitchShift.wet", N_("Wet"), "S", N_("Wet amount"), &wet, 50.0, 0.0, 100.0, 1);
    reg.registerVar("smbPitchShift.dry", N_("Dry"), "S", N_("Dry amount"), &dry, 50.0, 0.0, 100.0, 1);
    reg.registerVar("smbPitchShift.a", N_("low"), "S", N_("Sub"), &a, 1.0, 0.0, 2.0, 0.01);
    reg.registerVar("smbPitchShift.b", N_("middle low"), "S", N_("Low"), &b, 1.0, 0.0, 2.0, 0.01);
    reg.registerVar("smbPitchShift.c", N_("middle treble"), "S", N_("Mid"), &c, 1.0, 0.0, 2.0, 0.01);
    reg.registerVar("smbPitchShift.d", N_("treble"), "S", N_("Hi"), &d, 1.0, 0.0, 2.0, 0.01);
    param["smbPitchShift.latency"].signal_changed_int().connect(
        sigc::hide(sigc::mem_fun(this, &smbPitchShift::change_latency)));
    return 0;
}

int smbPitchShift::registerparam(const ParamReg& reg) 
{
    return static_cast<smbPitchShift*>(reg.plugin)->register_par(reg);
}

int smbPitchShift::load_ui_f(const UiBuilder& b, int form) 
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file("gx_detune_ui.glade");
        return 0;
    }
    if (form & UI_FORM_STACK) {
    b.openHorizontalhideBox("");
    {
        b.create_master_slider("smbPitchShift.semitone",N_("Detune"));
    }
    b.closeBox();
    b.openVerticalBox("");
    {
    b.openHorizontalBox("");
    {
    b.openVerticalBox("");
    {
    b.insertSpacer();
    b.create_selector_no_caption("smbPitchShift.octave");
    b.create_selector_no_caption("smbPitchShift.l");
    b.create_selector_no_caption("smbPitchShift.latency");
    b.insertSpacer();
    }
    b.closeBox();
    b.create_mid_rackknob("smbPitchShift.semitone",N_("Detune"));
    b.create_small_rackknobr("smbPitchShift.dry",N_("Dry"));
    b.create_small_rackknobr("smbPitchShift.wet",N_("Wet"));
    }
    b.closeBox();
    b.insertSpacer();
    b.openHorizontalBox("");
    {
    b.set_next_flags(UI_LABEL_INVERSE);
    b.create_small_rackknobr("smbPitchShift.a",N_("Lo"));
    b.set_next_flags(UI_LABEL_INVERSE);
    b.create_small_rackknobr("smbPitchShift.b",N_("LoMid"));
    b.set_next_flags(UI_LABEL_INVERSE);
    b.create_small_rackknobr("smbPitchShift.c",N_("HiMid"));
    b.set_next_flags(UI_LABEL_INVERSE);
    b.create_small_rackknobr("smbPitchShift.d",N_("Hi"));
    }
    b.closeBox();
    }
    b.closeBox();
    return 0;
    }
    return -1;
}

int smbPitchShift::activate_static(bool start, PluginDef *p)
{
    return static_cast<smbPitchShift*>(p)->activate(start);
}

int smbPitchShift::load_ui_f_static(const UiBuilder& b, int form)
{
    return static_cast<smbPitchShift*>(b.plugin)->load_ui_f(b, form);
}

void smbPitchShift::del_instance(PluginDef *p)
{
    delete static_cast<smbPitchShift*>(p);
}


} // namespace gx_engine
