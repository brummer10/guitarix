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

NoiseGate::NoiseGate() : inputdef() , inputlevel() {

    off = true;
    fnglevel = 0;
    ngate = 1;
    
    version = PLUGINDEF_VERSION;
    flags = PGN_SNOOP;
    groups = 0;
    category = "NONE";
    id = "noise_gate";
    name = N_("Noise Gate");
    stereo_audio = 0;
    mono_audio = inputlevel_compute;
    register_params = noisegate_params_static;
    set_samplerate = 0;
    activate_plugin = noisegate_activate;
    load_ui = 0;
    clear_state = 0;
    delete_instance = 0;

    inputlevel.set_pdef(&inputdef);
    inputlevel = this;
}

inline float sqrf(float x) {
    return x * x;
}

void NoiseGate::inputlevel_process(int count, float *input, float *output) {
    float sumnoise = 0;
    for (int i = 0; i < count; i++) {
        sumnoise += sqrf(input[i]);
    }
    if (sumnoise/count > sqrf(fnglevel * 0.1)) {
        ngate = 1; // -75db 0.001 = 65db
    } else if (ngate > 0.01) {
        ngate *= 0.996;
    }
}
void NoiseGate::inputlevel_compute(int count, float *input, float *output, PluginDef* p) {
    static_cast<NoiseGate*>(p)->inputlevel_process(count, input, output);
}

int NoiseGate::noisegate_register(const ParamReg& reg) {
    reg.registerFloatVar("noise_gate.threshold", N_("Threshold"), "S", "", &fnglevel,
             0.017f, 0.01f, 0.31f, 0.001f, 0);
    return 0;
}

int NoiseGate::noisegate_params_static(const ParamReg& reg) {
    return static_cast<NoiseGate*>(reg.plugin)->noisegate_register(reg);
}

int NoiseGate::noisegate_start(bool start) {
    off = !inputlevel.get_on_off();
    return 0;
}

int NoiseGate::noisegate_activate(bool start, PluginDef *p) {
    return static_cast<NoiseGate*>(p)->noisegate_start(start);
}

/****************************************************************
 **  class OutPutGate
 */

OutPutGate::OutPutGate(const NoiseGate *noisegate_) :  outputdef(), outputlevel() {

    version = PLUGINDEF_VERSION;
    groups = 0;
    category = "NONE";
    id = "noiseshut";
    name = "?noiseshut";
    stereo_audio = 0;
    mono_audio = outputgate_compute;
    activate_plugin = 0;
    register_params = 0;
    set_samplerate = 0;
    load_ui = 0;
    clear_state = 0;
    delete_instance = 0;

    noisegate = noisegate_;
    outputlevel.set_pdef(&outputdef);
    outputlevel = this;
}

void OutPutGate::outputgate_process(int count, float *input, float *output) {
    if (noisegate->off) {
        return;
    }
    while (count--) {
        *output++ = noisegate->ngate * *input++;
    }
}

void OutPutGate::outputgate_compute(int count, float *input, float *output, PluginDef*p) {
    static_cast<OutPutGate*>(p)->outputgate_process(count, input, output);
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
    if (gainline != jcset.gainline) {
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

#ifndef GUITARIX_AS_PLUGIN
#include "faust/jconv_post.cc"
#include "faust/jconv_post_mono.cc"
#else
#include "jconv_post.cc"
#include "jconv_post_mono.cc"
#endif

ConvolverAdapter::ConvolverAdapter(
    EngineControl& engine_, sigc::slot<void> sync_)
    : PluginDef(),
      conv(),
      activate_mutex(),
      engine(engine_),
      sync(sync_),
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
    EngineControl& engine_, sigc::slot<void> sync_)
    : ConvolverAdapter(engine_, sync_) {
    id = "jconv";
    name = N_("Convolver");
    register_params = convolver_register;
    set_samplerate = convolver_init;
    activate_plugin = activate;
    load_ui = jconv_load_ui;
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
    self.jcp = JConvParameter::insert_param(self.get_parameter_map(), "jconv.convolver", self, &self.jcset);
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

//static
int ConvolverStereoAdapter::jconv_load_ui(const UiBuilder& builder, int format) {
    if (format & UI_FORM_GLADE) {
    builder.load_glade_file("jconv_st_ui.glade");
        return 0;
    } else if (format & UI_FORM_STACK) {
        //static gx_jconv::IRWindow *irw = gx_jconv::IRWindow::create("jconv", window_icon, machine, accels, 2);
        builder.openHorizontalhideBox("");
        {
            builder.create_master_slider("jconv.wet_dry", _("Dry/Wet"));
            builder.insertSpacer();
            builder.insertSpacer();
            //builder.addSmallJConvFavButton(C_("Setup", "S"), irw);
        }
        builder.closeBox();
        builder.openVerticalBox("");
        {
            //builder.openSetLabelBox();
            //builder.closeBox();
            builder.insertSpacer();
            builder.openHorizontalBox("");
            {
                builder.insertSpacer();
                builder.insertSpacer();
                builder.insertSpacer();
                builder.insertSpacer();
                builder.create_mid_rackknob("jconv.gain", _("Gain"));
                builder.create_small_rackknobr("jconv.diff_delay", _("Delta Delay"));
                builder.create_small_rackknobr("jconv.balance", _("Balance"));
                builder.create_small_rackknobr("jconv.wet_dry", _("Dry/Wet"));
                builder.openVerticalBox("");
                {
                    builder.insertSpacer();
                    builder.insertSpacer();
                    //builder.addJConvButton(_("Setup"), irw);
                    builder.insertSpacer();
                }
                builder.closeBox();
                builder.insertSpacer();
                builder.insertSpacer();
                builder.insertSpacer();
            }
            builder.closeBox();
        }
        builder.closeBox();
        return 0;
    } else {
        return -1;
    }
}


/****************************************************************
 ** class ConvolverMonoAdapter
 */

ConvolverMonoAdapter::ConvolverMonoAdapter(
    EngineControl& engine_, sigc::slot<void> sync_)
    : ConvolverAdapter(engine_, sync_) {
    id = "jconv_mono";
    name = N_("Convolver");
    register_params = convolver_register;
    set_samplerate = convolver_init;
    activate_plugin = activate;
    load_ui = jconv_load_ui;
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
    self.jcp = JConvParameter::insert_param(self.get_parameter_map(), "jconv_mono.convolver", self, &self.jcset);
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

//static
int ConvolverMonoAdapter::jconv_load_ui(const UiBuilder& builder, int format) {
    if (format & UI_FORM_GLADE) {
    builder.load_glade_file("jconv_ui.glade");
        return 0;
    } else if (format & UI_FORM_STACK) {
        //static gx_jconv::IRWindow *irw = gx_jconv::IRWindow::create(
        //    "jconv_mono", b->window_icon, b->machine, b->accels, 1);
        builder.openHorizontalhideBox("");
        builder.create_master_slider("jconv_mono.wet_dry", _("Dry/Wet"));
        builder.insertSpacer();
        builder.insertSpacer();
        //builder.addSmallJConvFavButton(C_("Setup", "S"), irw);
        builder.closeBox();
        builder.openVerticalBox("");
        {
            //builder.openSetMonoLabelBox();
            //builder.closeBox();
            builder.insertSpacer();
            builder.openHorizontalBox("");
            {
                builder.insertSpacer();
                builder.insertSpacer();
                builder.insertSpacer();
                builder.insertSpacer();
                builder.insertSpacer();
                builder.insertSpacer();
                builder.create_mid_rackknob("jconv_mono.gain", _("Gain"));
                builder.create_small_rackknobr("jconv_mono.wet_dry", _("Dry/Wet"));
                builder.openVerticalBox("");
                builder.insertSpacer();
                builder.insertSpacer();
                //builder.addJConvButton(_("Setup"), irw);
                builder.insertSpacer();
                builder.closeBox();
                builder.insertSpacer();
                builder.insertSpacer();
                builder.insertSpacer();
                builder.insertSpacer();
                builder.insertSpacer();
                builder.insertSpacer();
            }
            builder.closeBox();
        }
        builder.closeBox();
        return 0;
    } else {
        return -1;
    }
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
        if (!self.update_conn.connected())
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

#ifndef GUITARIX_AS_PLUGIN
#include "faust/cabinet_impulse_former.cc"
#else
#include "cabinet_impulse_former.cc"
#endif

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
        impf.init(sr);
    }
    //float cab_irdata_c[cab.ir_count];
    impf.clear_state_f();
    while (!conv.checkstate());
    if (configure) {
        if (!conv.configure(cab.ir_count, cab.ir_data, cab.ir_sr)) {
            return false;
        }
    } else {
        if (!conv.update(cab.ir_count, cab.ir_data, cab.ir_sr)) {
            return false;
        }
    }
    update_cabinet();
    return conv_start();
}

bool CabinetConvolver::start(bool force) {
    if (force) {
        current_cab = -1;
    }
    if (cabinet_changed()) {
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
    if (cabinet_changed()) {
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
    self.impf.compute(count,output0,output0);
}

int CabinetConvolver::register_cab(const ParamReg& reg) {
    CabinetConvolver& cab = *static_cast<CabinetConvolver*>(reg.plugin);
    reg.registerIntVar("cab.select", "select", "B", "", &cab.cabinet, 0, 0, 0, cab.cab_names);
    reg.registerFloatVar("cab.Level", N_("Level"),  "S", N_("Level"), &cab.level,  1.0, 0.5, 5.0, 0.5, 0);
    reg.registerFloatVar("cab.bass", N_("Bass"),   "S", N_("Bass"), &cab.bass,   0.0, -10.0, 10.0, 0.5, 0);
    reg.registerFloatVar("cab.treble", N_("Treble"), "S", N_("Treble"), &cab.treble, 0.0, -10.0, 10.0, 0.5, 0);
    cab.impf.register_par(reg);
    return 0;
}

//// STEREO /////
#ifndef GUITARIX_AS_PLUGIN
#include "faust/cabinet_impulse_former_st.cc"
#else
#include "cabinet_impulse_former_st.cc"
#endif

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
        impf.init(sr);
    }
    impf.clear_state_f();
    while (!conv.checkstate());
    if (configure) {
        if (!conv.configure_stereo(cab.ir_count, cab.ir_data, cab.ir_sr)) {
            return false;
        }
    } else {
        if (!conv.update_stereo(cab.ir_count, cab.ir_data, cab.ir_sr)) {
            return false;
        }
    }
    update_cabinet();
    return conv_start();
}

bool CabinetStereoConvolver::start(bool force) {
    if (force) {
        current_cab = -1;
    }
    if (cabinet_changed()) {
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
    if (cabinet_changed()) {
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
    self.impf.compute(count, output0, output1, output0, output1);
}

int CabinetStereoConvolver::register_cab(const ParamReg& reg) {
    CabinetStereoConvolver& cab = *static_cast<CabinetStereoConvolver*>(reg.plugin);
    reg.registerIntVar("cab_st.select", "select", "B", "", &cab.cabinet, 0, 0, 0, cab.cab_names);
    reg.registerFloatVar("cab_st.Level", N_("Level"),  "S", N_("Level"), &cab.level,  1.0, 0.5, 5.0, 0.5, 0);
    reg.registerFloatVar("cab_st.bass", N_("Bass"),   "S", N_("Bass"), &cab.bass,   0.0, -10.0, 10.0, 0.5, 0);
    reg.registerFloatVar("cab_st.treble", N_("Treble"), "S", N_("Treble"), &cab.treble, 0.0, -10.0, 10.0, 0.5, 0);
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

#ifndef GUITARIX_AS_PLUGIN
#include "faust/preamp_impulse_former.cc"
#else
#include "preamp_impulse_former.cc"
#endif

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
        impf.init(sr);
    }
    impf.clear_state_f();
    while (!conv.checkstate());
    if (configure) {
        if (!conv.configure(pre.ir_count, pre.ir_data, pre.ir_sr)) {
            return false;
        }
    } else {
        if (!conv.update(pre.ir_count, pre.ir_data, pre.ir_sr)) {
            return false;
        }
    }
    update_preamp();
    return conv_start();
}

bool PreampConvolver::start(bool force) {
    if (force) {
        current_pre = -1;
    }
    if (preamp_changed()) {
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
    if (preamp_changed()) {
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
    self.impf.compute(count,output0,output0);
}

int PreampConvolver::register_pre(const ParamReg& reg) {
    PreampConvolver& pre = *static_cast<PreampConvolver*>(reg.plugin);
    reg.registerIntVar("pre.select", "select", "B", "", &pre.preamp, 0, 0, 0, pre.pre_names);
    reg.registerFloatVar("pre.Level", N_("Level"),  "S", N_("Level"), &pre.level,  1.0, 0.1, 2.1, 0.1, 0);
    reg.registerFloatVar("pre.bass", N_("Bass"),   "S", N_("Bass"), &pre.bass,   0.0, -10.0, 10.0, 0.5, 0);
    reg.registerFloatVar("pre.treble", N_("Treble"), "S", N_("Treble"), &pre.treble, 0.0, -10.0, 10.0, 0.5, 0);
    pre.impf.register_par(reg);
    return 0;
}

//// STEREO /////
#ifndef GUITARIX_AS_PLUGIN
#include "faust/preamp_impulse_former_st.cc"
#else
#include "preamp_impulse_former_st.cc"
#endif

static int pre_load_stereo_ui(const UiBuilder& builder, int format) {
    if (format & UI_FORM_GLADE) {
        builder.load_glade_file("ampimpulse_st_ui.glade");
    return 0;
    } else if (format & UI_FORM_STACK) {
    builder.openHorizontalhideBox("");
    builder.create_selector_no_caption("pre_st.select");
    builder.closeBox();
    builder.openVerticalBox("");
    {
    builder.openHorizontalBox("");
    {
        builder.insertSpacer();
        builder.create_selector_no_caption("pre_st.select");
        builder.create_small_rackknobr("pre_st.bass", "Bass");
        builder.create_small_rackknobr("pre_st.treble", "Treble");
        builder.create_mid_rackknob("pre_st.Level", "Level");
    }
    builder.closeBox();
    }
    builder.closeBox();
    return 0;
    } else {
    return -1;
    }

}

PreampStereoConvolver::PreampStereoConvolver(EngineControl& engine, sigc::slot<void> sync,
    gx_resample::BufferResampler& resamp):
    FixedBaseConvolver(engine, sync, resamp),
    current_pre(-1),
    level(0),
    preamp(0),
    bass(0),
    treble(0),
    pre_names(new value_pair[pre_table_size+1]),
    impf(),
    smp(),
    smps() {
    for (unsigned int i = 0; i < pre_table_size; ++i) {
        PreEntry& pre = getPreEntry(i);
        pre_names[i].value_id = pre.value_id;
        pre_names[i].value_label = pre.value_label;
    }
    pre_names[pre_table_size].value_id = 0;
    pre_names[pre_table_size].value_label = 0;
    id = "pre_st";
    name = N_("Amp Impulse");
    category = N_("Tone Control");
    load_ui = pre_load_stereo_ui;
    stereo_audio = run_pre_conf;
    register_params = register_pre;
}

PreampStereoConvolver::~PreampStereoConvolver() {
    delete[] pre_names;
}

bool PreampStereoConvolver::do_update() {
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
        smps.setup(sr, fact*sr);
        impf.init(sr);
    }
    impf.clear_state_f();
    while (!conv.checkstate());
    if (configure) {
        if (!conv.configure_stereo(pre.ir_count, pre.ir_data, pre.ir_sr)) {
            return false;
        }
    } else {
        if (!conv.update_stereo(pre.ir_count, pre.ir_data, pre.ir_sr)) {
            return false;
        }
    }
    update_preamp();
    return conv_start();
}

bool PreampStereoConvolver::start(bool force) {
    if (force) {
        current_pre = -1;
    }
    if (preamp_changed()) {
        return do_update();
    } else {
    while (!conv.checkstate());
    if (!conv.is_runnable()) {
        return conv_start();
    }
    return true;
    }
}

void PreampStereoConvolver::check_update() {
    if (preamp_changed()) {
        do_update();
    }
}

void PreampStereoConvolver::run_pre_conf(int count, float *input0, float *input1, float *output0, float *output1, PluginDef *p) {
    PreampStereoConvolver& self = *static_cast<PreampStereoConvolver*>(p);
    FAUSTFLOAT buf[self.smp.max_out_count(count)];
    FAUSTFLOAT buf1[self.smps.max_out_count(count)];
    int ReCount = self.smp.up(count, output0, buf);
    self.smps.up(count, output1, buf1);
    if (!self.conv.compute_stereo(ReCount,buf,buf1)) {
        self.engine.overload(EngineControl::ov_Convolver, "pre_st");
    }
    self.smp.down(buf, output0);
    self.smps.down(buf1, output1);
    self.impf.compute(count, output0, output1, output0, output1);
}

int PreampStereoConvolver::register_pre(const ParamReg& reg) {
    PreampStereoConvolver& pre = *static_cast<PreampStereoConvolver*>(reg.plugin);
    reg.registerIntVar("pre_st.select", "select", "B", "", &pre.preamp, 0, 0, 0, pre.pre_names);
    reg.registerFloatVar("pre_st.Level", N_("Level"),  "SA", N_("Level"), &pre.level,  1.0, 0.1, 2.1, 0.1, 0);
    reg.registerFloatVar("pre_st.bass", N_("Bass"),   "SA", N_("Bass"), &pre.bass,   0.0, -10.0, 10.0, 0.5, 0);
    reg.registerFloatVar("pre_st.treble", N_("Treble"), "SA", N_("Treble"), &pre.treble, 0.0, -10.0, 10.0, 0.5, 0);
    pre.impf.register_par(reg);
    return 0;
}

/****************************************************************
 ** class ContrastConvolver
 */

#ifndef GUITARIX_AS_PLUGIN
#include "faust/presence_level.cc"
#else
#include "presence_level.cc"
#endif

ContrastConvolver::ContrastConvolver(EngineControl& engine, sigc::slot<void> sync,
    gx_resample::BufferResampler& resamp)
    : FixedBaseConvolver(engine, sync, resamp),
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
    reg.registerFloatVar("con.Level", "",  "S", "", &self.level,  1.0, 0.5, 5.0, 0.5, 0);
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
 ** class Neural Amp Modeler
 */

NeuralAmp::NeuralAmp(ParamMap& param_, std::string id_, sigc::slot<void> sync_)
    : PluginDef(), model(nullptr), param(param_), smp(), sync(sync_), idstring(id_), plugin() {
    version = PLUGINDEF_VERSION;
    flags = 0;
    id = idstring.c_str();
    name = N_("Neural Amp Modeler");
    groups = 0;
    description = N_("Neural Amp Modeler by Steven Atkinson"); // description (tooltip)
    category = N_("Neural");       // category
    shortname = "NAM";     // shortname
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init_static;
    activate_plugin = 0;
    register_params = register_params_static;
    load_ui = load_ui_f_static;
    clear_state = clear_state_f_static;
    delete_instance = del_instance;
    plugin = this;
    need_resample = 0;
    is_inited = false;
    loudness = 0.0;
    gx_system::atomic_set(&ready, 0);
 }

NeuralAmp::~NeuralAmp() {
    delete model;
}

inline void NeuralAmp::clear_state_f()
{
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
}

void NeuralAmp::clear_state_f_static(PluginDef *p)
{
    static_cast<NeuralAmp*>(p)->clear_state_f();
}

inline void NeuralAmp::init(unsigned int sample_rate)
{
    fSampleRate = sample_rate;
    clear_state_f();
    is_inited = true;
    load_nam_file();
}

void NeuralAmp::init_static(unsigned int sample_rate, PluginDef *p)
{
    static_cast<NeuralAmp*>(p)->init(sample_rate);
}

void always_inline NeuralAmp::compute(int count, float *input0, float *output0)
{
    if (output0 != input0)
        memcpy(output0, input0, count*sizeof(float));
    if (!model) return;
    double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
    double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec0[0] = fSlow0 + 0.999 * fRec0[1];
        output0[i0] = float(double(output0[i0]) * fRec0[0]);
        fRec0[1] = fRec0[0];
    }
    if (model && gx_system::atomic_get(ready)) {
        if (need_resample) {
            int ReCount = count;
            if (need_resample == 1) {
                ReCount = smp.max_out_count(count);
            } else if (need_resample == 2) {
                ReCount = static_cast<int>(ceil((count*static_cast<double>(mSampleRate))/fSampleRate));
            }

            float buf[ReCount];
            memset(buf, 0, ReCount*sizeof(float));

            if (need_resample == 1) {
                ReCount = smp.up(count, output0, buf);
            } else if (need_resample == 2) {
                smp.down(output0, buf);
            } else {
                memcpy(buf, output0, ReCount * sizeof(float));
            }

            model->process(buf, buf, ReCount);
            model->finalize_(ReCount);

            if (need_resample == 1) {
                smp.down(buf, output0);
            } else if (need_resample == 2) {
                smp.up(ReCount, buf, output0);
            }
        } else {
            model->process(output0, output0, count);
            model->finalize_(count);
        }
    }
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec1[0] = fSlow1 + 0.999 * fRec1[1];
        output0[i0] = float(double(output0[i0]) * fRec1[0]);
        fRec1[1] = fRec1[0];
    }
}

void NeuralAmp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<NeuralAmp*>(p)->compute(count, input0, output0);
}

// non rt callback
void NeuralAmp::load_nam_file() {
    if (!load_file.empty() && is_inited) {
        gx_system::atomic_set(&ready, 0);
        sync();
        delete model;
        model = nullptr;
        need_resample = 0;
        clear_state_f();
        int32_t warmUpSize = 4096;
        try {
            model = nam::get_dsp(std::string(load_file)).release();
        } catch (const std::exception&) {
            gx_print_info("Neural Amp Modeler", "fail to load " + load_file);
            load_file = "None";
        }
        
        if (model) {
            if (model->HasLoudness()) loudness = model->GetLoudness();
            mSampleRate = static_cast<int>(model->GetExpectedSampleRate());
            //model->SetLoudness(-15.0);
            if (mSampleRate <= 0) mSampleRate = 48000;
            if (mSampleRate > fSampleRate) {
                smp.setup(fSampleRate, mSampleRate);
                need_resample = 1;
            } else if (mSampleRate < fSampleRate) {
                smp.setup(mSampleRate, fSampleRate);
                need_resample = 2;
            } 
            float* buffer = new float[warmUpSize];
            memset(buffer, 0, warmUpSize * sizeof(float));

            model->process(buffer, buffer, warmUpSize);
            model->finalize_(warmUpSize);

            delete[] buffer;
            //fprintf(stderr, "sample rate = %i file = %i l = %f\n",fSampleRate, mSampleRate, loudness);
            //fprintf(stderr, "%s\n", load_file.c_str());
        } 
        gx_system::atomic_set(&ready, 1);
    }
}

int NeuralAmp::register_par(const ParamReg& reg)
{
    reg.registerFloatVar((idstring + ".input").c_str(),N_("Input"),"S",N_("gain (dB)"),&fVslider0, 0.0, -40.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".output").c_str(),N_("Output"),"S",N_("gain (dB)"),&fVslider1, 0.0, -40.0, 20.0, 0.1, 0);
    param.reg_string((idstring + ".loadfile").c_str(), "", &load_file, "*.nam", true)->set_desc(N_("import *.nam file"));

    param[(idstring + ".loadfile").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &NeuralAmp::load_nam_file)));
    return 0;
}

int NeuralAmp::register_params_static(const ParamReg& reg)
{
    return static_cast<NeuralAmp*>(reg.plugin)->register_par(reg);
}

inline int NeuralAmp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file((idstring + "_ui.glade").c_str());
        return 0;
    }
    if (form & UI_FORM_STACK) {

        b.openHorizontalhideBox("");
            b.create_master_slider((idstring + ".input").c_str(), "Input");
        b.closeBox();
        b.openHorizontalBox("");

            b.create_mid_rackknob((idstring + ".input").c_str(), "Input");
            b.create_fload_switch(sw_button, nullptr, (idstring + ".loadfile").c_str());
            b.create_mid_rackknob((idstring + ".output").c_str(), "Output");

        b.closeBox();

        return 0;
    }
    return -1;
}

int NeuralAmp::load_ui_f_static(const UiBuilder& b, int form)
{
    return static_cast<NeuralAmp*>(b.plugin)->load_ui_f(b, form);
}

void NeuralAmp::del_instance(PluginDef *p)
{
    delete static_cast<NeuralAmp*>(p);
}

/****************************************************************
 ** class NeuralAmpMulti
 */

NeuralAmpMulti::NeuralAmpMulti(ParamMap& param_, std::string id_, ParallelThread* pro_, sigc::slot<void> sync_)
    : PluginDef(), modela(nullptr), modelb(nullptr), param(param_), pro(pro_), smpa(), smpb(), sync(sync_), idstring(id_), plugin() {
    version = PLUGINDEF_VERSION;
    flags = 0;
    id = idstring.c_str();
    name = N_("Neural Multi Amp Modeler");
    groups = 0;
    description = N_("Neural Amp Modeler by Steven Atkinson"); // description (tooltip)
    category = N_("Neural");       // category
    shortname = "NAM Multi";     // shortname
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init_static;
    activate_plugin = 0;
    register_params = register_params_static;
    load_ui = load_ui_f_static;
    clear_state = clear_state_f_static;
    delete_instance = del_instance;
    plugin = this;
    loudnessa = 0.0;
    loudnessb = 0.0;
    need_aresample = 0;
    need_bresample = 0;
    is_inited = false;
    gx_system::atomic_set(&ready, 0);
 }

NeuralAmpMulti::~NeuralAmpMulti() {
    delete modela;
    delete modelb;
}

inline void NeuralAmpMulti::clear_state_f()
{
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec01[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec2[l0] = 0.0;
    for (int l0 = 0; l0 < 16384; l0 = l0 + 1) fDec0[l0] = 0.0;
    for (int l1 = 0; l1 < 2; l1 = l1 + 1) fDel4[l1] = 0.0;
    for (int l2 = 0; l2 < 2; l2 = l2 + 1) fDel0[l2] = 0.0;
    for (int l3 = 0; l3 < 2; l3 = l3 + 1) fDel1[l3] = 0.0;
    for (int l4 = 0; l4 < 2; l4 = l4 + 1) fDel2[l4] = 0.0;
    for (int l5 = 0; l5 < 2; l5 = l5 + 1) fDel3[l5] = 0.0;
}

void NeuralAmpMulti::clear_state_f_static(PluginDef *p)
{
    static_cast<NeuralAmpMulti*>(p)->clear_state_f();
}

inline void NeuralAmpMulti::init(unsigned int sample_rate)
{
    fSampleRate = sample_rate;
    clear_state_f();
    is_inited = true;
    buf = nullptr;
    IOTA0 = 0;
    nframes = 1;
    load_nam_afile();
    load_nam_bfile();
    pro->set<1, NeuralAmpMulti, &NeuralAmpMulti::processModelB>(this);
    
}

void NeuralAmpMulti::init_static(unsigned int sample_rate, PluginDef *p)
{
    static_cast<NeuralAmpMulti*>(p)->init(sample_rate);
}

void always_inline NeuralAmpMulti::processDelay(int count, float *buf)
{
    double fSlow0 = 0.0010000000000000009 * double(fVslider02);
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        double fTemp0 = double(buf[i0]);
        fDec0[IOTA0 & 16383] = fTemp0;
        fDel4[0] = fSlow0 + 0.999 * fDel4[1];
        double fTemp1 = ((fDel0[1] != 0.0) ? (((fDel1[1] > 0.0) & (fDel1[1] < 1.0)) ? fDel0[1] : 0.0) : (((fDel1[1] == 0.0) & (fDel4[0] != fDel2[1])) ? 0.0009765625 : (((fDel1[1] == 1.0) & (fDel4[0] != fDel3[1])) ? -0.0009765625 : 0.0)));
        fDel0[0] = fTemp1;
        fDel1[0] = std::max<double>(0.0, std::min<double>(1.0, fDel1[1] + fTemp1));
        fDel2[0] = (((fDel1[1] >= 1.0) & (fDel3[1] != fDel4[0])) ? fDel4[0] : fDel2[1]);
        fDel3[0] = (((fDel1[1] <= 0.0) & (fDel2[1] != fDel4[0])) ? fDel4[0] : fDel3[1]);
        double fTemp2 = fDec0[(IOTA0 - int(std::min<double>(8192.0, std::max<double>(0.0, fDel2[0])))) & 16383];
        buf[i0] = float(fTemp2 + fDel1[0] * (fDec0[(IOTA0 - int(std::min<double>(8192.0, std::max<double>(0.0, fDel3[0])))) & 16383] - fTemp2));
        IOTA0 = IOTA0 + 1;
        fDel4[1] = fDel4[0];
        fDel0[1] = fDel0[0];
        fDel1[1] = fDel1[0];
        fDel2[1] = fDel2[0];
        fDel3[1] = fDel3[0];
    }
}

void always_inline NeuralAmpMulti::processModelA(int count, float *bufa) {
    if (!modela ) return;
    double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec0[0] = fSlow0 + 0.999 * fRec0[1];
        bufa[i0] = float(double(bufa[i0]) * fRec0[0]);
        fRec0[1] = fRec0[0];
    }

    if (modela && gx_system::atomic_get(ready)) {
        if (need_aresample) {
            int ReCounta = count;
            if (need_aresample == 1) {
                ReCounta = smpa.max_out_count(count);
            } else if (need_aresample == 2) {
                ReCounta = static_cast<int>(ceil((count*static_cast<double>(maSampleRate))/fSampleRate));
            }

            float bufa1[ReCounta];
            memset(bufa1, 0, ReCounta*sizeof(float));

            if (need_aresample == 1) {
                ReCounta = smpa.up(count, bufa, bufa1);
            } else if (need_aresample == 2) {
                smpa.down(bufa, bufa1);
            } else {
                memcpy(bufa1, bufa, ReCounta * sizeof(float));
            }

            modela->process(bufa1, bufa1, ReCounta);
            modela->finalize_(ReCounta);

            if (need_aresample == 1) {
                smpa.down(bufa1, bufa);
            } else if (need_aresample == 2) {
                smpa.up(ReCounta, bufa1, bufa);
            }
        } else {
            modela->process(bufa, bufa, count);
            modela->finalize_(count);
        }
    }
}

void always_inline NeuralAmpMulti::processModelB() {
    if (!modelb) return;
    double fSlow01 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider01));
    for (int i0 = 0; i0 < nframes; i0 = i0 + 1) {
        fRec01[0] = fSlow01 + 0.999 * fRec01[1];
        buf[i0] = float(double(buf[i0]) * fRec01[0]);
        fRec01[1] = fRec01[0];
    }

    if (modelb && gx_system::atomic_get(ready)) {
        if (need_bresample) {
            int ReCountb = nframes;
            if (need_bresample == 1) {
                ReCountb = smpb.max_out_count(nframes);
            } else if (need_bresample == 2) {
                ReCountb = static_cast<int>(ceil((nframes*static_cast<double>(mbSampleRate))/fSampleRate));
            }

            float buf1[ReCountb];
            memset(buf1, 0, ReCountb*sizeof(float));

            if (need_bresample == 1) {
                ReCountb = smpb.up(nframes, buf, buf1);
            } else if (need_bresample == 2) {
                smpb.down(buf, buf1);
            } else {
                memcpy(buf1, buf, ReCountb * sizeof(float));
            }

            modelb->process(buf1, buf1, ReCountb);
            modelb->finalize_(ReCountb);

            if (need_bresample == 1) {
                smpb.down(buf1, buf);
            } else if (need_bresample == 2) {
                smpb.up(ReCountb, buf1, buf);
            }
        } else {
            modelb->process(buf, buf, nframes);
            modelb->finalize_(nframes);
        }
    }
}


void always_inline NeuralAmpMulti::compute(int count, float *input0, float *output0)
{
    if (output0 != input0)
        memcpy(output0, input0, count*sizeof(float));
    if (!modela && !modelb) return;
    double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
    double fSlow2 = 0.0010000000000000009 * double(fVslider2);

    float bufa[count];
    memcpy(bufa, output0, count*sizeof(float));
    float bufb[count];
    memcpy(bufb, output0, count*sizeof(float));

    if (int(fVslider02) > 0) processDelay(count, bufb);
    else processDelay(count, bufa);

    nframes = count;
    buf = bufb;

    if (pro->getProcess()) {
        pro->setProcessor(1);
        pro->runProcess();
    } else {
        processModelB();
    }

    processModelA(count, bufa);

    pro->processWait();

    if (modela && modelb && gx_system::atomic_get(ready)) {
        for (int i0 = 0; i0 < count; i0 = i0 + 1) {
            fRec2[0] = fSlow2 + 0.999 * fRec2[1];
            output0[i0] = bufa[i0] * (1.0 - fRec2[0]) + bufb[i0] * fRec2[0];
            fRec2[1] = fRec2[0];
        }
    } else if (modela && gx_system::atomic_get(ready)) {
        memcpy(output0, bufa, count*sizeof(float));
    } else if (modelb && gx_system::atomic_get(ready)) {
        memcpy(output0, bufb, count*sizeof(float));
    }
    
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec1[0] = fSlow1 + 0.999 * fRec1[1];
        output0[i0] = float(double(output0[i0]) * fRec1[0]);
        fRec1[1] = fRec1[0];
    }
}

void NeuralAmpMulti::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<NeuralAmpMulti*>(p)->compute(count, input0, output0);
}

// non rt callback
void NeuralAmpMulti::load_nam_afile() {
    if (!load_afile.empty() && is_inited) {
        gx_system::atomic_set(&ready, 0);
        sync();
        delete modela;
        modela = nullptr;
        need_aresample = 0;
        clear_state_f();
        int32_t warmUpSize = 4096;
        try {
            modela = nam::get_dsp(std::string(load_afile)).release();
        } catch (const std::exception&) {
            gx_print_info("Neural Multi Amp Modeler", "fail to load " + load_afile);
            load_afile = "None";
        }
        
        if (modela) {
            if (modela->HasLoudness()) loudnessa = modela->GetLoudness();
            maSampleRate = static_cast<int>(modela->GetExpectedSampleRate());
            //model->SetLoudness(-15.0);
            if (maSampleRate <= 0) maSampleRate = 48000;
            if (maSampleRate > fSampleRate) {
                smpa.setup(fSampleRate, maSampleRate);
                need_aresample = 1;
            } else if (maSampleRate < fSampleRate) {
                smpa.setup(maSampleRate, fSampleRate);
                need_aresample = 2;
            } 
            float* buffer = new float[warmUpSize];
            memset(buffer, 0, warmUpSize * sizeof(float));

            modela->process(buffer, buffer, warmUpSize);
            modela->finalize_(warmUpSize);

            delete[] buffer;
            //fprintf(stderr, "sample rate = %i file = %i l = %f\n",fSampleRate, maSampleRate, loudness);
            //fprintf(stderr, "%s\n", load_file.c_str());
        } 
        gx_system::atomic_set(&ready, 1);
    }
}

// non rt callback
void NeuralAmpMulti::load_nam_bfile() {
    if (!load_bfile.empty() && is_inited) {
        gx_system::atomic_set(&ready, 0);
        sync();
        delete modelb;
        modelb = nullptr;
        need_bresample = 0;
        clear_state_f();
        int32_t warmUpSize = 4096;
        try {
            modelb = nam::get_dsp(std::string(load_bfile)).release();
        } catch (const std::exception&) {
            gx_print_info("Neural Multi Amp Modeler", "fail to load " + load_bfile);
            load_bfile = "None";
        }
        
        if (modelb) {
            if (modelb->HasLoudness()) loudnessb = modelb->GetLoudness();
            mbSampleRate = static_cast<int>(modelb->GetExpectedSampleRate());
            //model->SetLoudness(-15.0);
            if (mbSampleRate <= 0) mbSampleRate = 48000;
            if (mbSampleRate > fSampleRate) {
                smpb.setup(fSampleRate, mbSampleRate);
                need_bresample = 1;
            } else if (mbSampleRate < fSampleRate) {
                smpb.setup(maSampleRate, fSampleRate);
                need_bresample = 2;
            } 
            float* buffer = new float[warmUpSize];
            memset(buffer, 0, warmUpSize * sizeof(float));

            modelb->process(buffer, buffer, warmUpSize);
            modelb->finalize_(warmUpSize);

            delete[] buffer;
            //fprintf(stderr, "sample rate = %i file = %i l = %f\n",fSampleRate, mbSampleRate, loudness);
            //fprintf(stderr, "%s\n", load_file.c_str());
        } 
        gx_system::atomic_set(&ready, 1);
    }
}

int NeuralAmpMulti::register_par(const ParamReg& reg)
{
    reg.registerFloatVar((idstring + ".input").c_str(),N_("Input A"),"S",N_("gain (dB)"),&fVslider0, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".inputb").c_str(),N_("Input B"),"S",N_("gain (dB)"),&fVslider01, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".cdelay").c_str(),N_("Delta Delay"),"S",N_("Delay A/B"),&fVslider02, 0.0, -4096.0, 4096.0, 1.0, 0);
    reg.registerFloatVar((idstring + ".output").c_str(),N_("Output"),"S",N_("gain (dB)"),&fVslider1, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".mix").c_str(),N_("Mix"),"S",N_("mix models"),&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
    param.reg_string((idstring + ".loadafile").c_str(), "", &load_afile, "*.nam", true)->set_desc(N_("import *.nam file"));
    param.reg_string((idstring + ".loadbfile").c_str(), "", &load_bfile, "*.nam", true)->set_desc(N_("import *.nam file"));

    param[(idstring + ".loadafile").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &NeuralAmpMulti::load_nam_afile)));
    param[(idstring + ".loadbfile").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &NeuralAmpMulti::load_nam_bfile)));
    return 0;
}

int NeuralAmpMulti::register_params_static(const ParamReg& reg)
{
    return static_cast<NeuralAmpMulti*>(reg.plugin)->register_par(reg);
}

inline int NeuralAmpMulti::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file((idstring + "_ui.glade").c_str());
        return 0;
    }
    if (form & UI_FORM_STACK) {

        b.openHorizontalhideBox("");
            b.create_master_slider((idstring + "output").c_str(), "output");
        b.closeBox();
        b.openHorizontalBox("");
            b.openVerticalBox("");
            b.create_mid_rackknob((idstring + ".input").c_str(), "Input A");
            b.create_mid_rackknob((idstring + ".inputb").c_str(), "Input B");
            b.closeBox();
            b.openVerticalBox("");
                b.create_fload_switch(sw_button, nullptr, (idstring + ".loadafile").c_str());
                b.create_fload_switch(sw_button, nullptr, (idstring + ".loadbfile").c_str());
            b.closeBox();
            b.create_mid_rackknob((idstring + ".output").c_str(), "Output");
            b.create_mid_rackknob((idstring + ".mix").c_str(), "Mix");

        b.closeBox();

        return 0;
    }
    return -1;
}

int NeuralAmpMulti::load_ui_f_static(const UiBuilder& b, int form)
{
    return static_cast<NeuralAmpMulti*>(b.plugin)->load_ui_f(b, form);
}

void NeuralAmpMulti::del_instance(PluginDef *p)
{
    delete static_cast<NeuralAmpMulti*>(p);
}

/****************************************************************
 ** class RtNeural
 */

RtNeural::RtNeural(ParamMap& param_, std::string id_, sigc::slot<void> sync_)
    : PluginDef(), model(nullptr), param(param_), smp(), sync(sync_), idstring(id_), plugin() {
    version = PLUGINDEF_VERSION;
    flags = 0;
    id = idstring.c_str();
    name = N_("RTNeural Network Engine");
    groups = 0;
    description = N_("Neural network engine written by Jatin Chowdhury"); // description (tooltip)
    category = N_("Neural");       // category
    shortname = "RTNeural";     // shortname
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init_static;
    activate_plugin = 0;
    register_params = register_params_static;
    load_ui = load_ui_f_static;
    clear_state = clear_state_f_static;
    delete_instance = del_instance;
    plugin = this;
    need_resample = 0;
    is_inited = false;
    gx_system::atomic_set(&ready, 0);
 }

RtNeural::~RtNeural() {
    delete model;
}

inline void RtNeural::clear_state_f()
{
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
}

void RtNeural::clear_state_f_static(PluginDef *p)
{
    static_cast<RtNeural*>(p)->clear_state_f();
}

inline void RtNeural::init(unsigned int sample_rate)
{
    fSampleRate = sample_rate;
    clear_state_f();
    is_inited = true;
    load_json_file();
}

void RtNeural::init_static(unsigned int sample_rate, PluginDef *p)
{
    static_cast<RtNeural*>(p)->init(sample_rate);
}

void always_inline RtNeural::compute(int count, float *input0, float *output0)
{
    if (output0 != input0)
        memcpy(output0, input0, count*sizeof(float));
    if (!model) return;
    double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
    double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec0[0] = fSlow0 + 0.999 * fRec0[1];
        output0[i0] = float(double(output0[i0]) * fRec0[0]);
        fRec0[1] = fRec0[0];
    }
    if (model && gx_system::atomic_get(ready)) {
        if (need_resample) {
            int ReCount = count;
            if (need_resample == 1) {
                ReCount = smp.max_out_count(count);
            } else if (need_resample == 2) {
                ReCount = static_cast<int>(ceil((count*static_cast<double>(mSampleRate))/fSampleRate));
            }

            float buf[ReCount];
            memset(buf, 0, ReCount*sizeof(float));

            if (need_resample == 1) {
                ReCount = smp.up(count, output0, buf);
            } else if (need_resample == 2) {
                smp.down(output0, buf);
            } else {
                memcpy(buf, output0, ReCount * sizeof(float));
            }

            for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
                 buf[i0] = model->forward (&buf[i0]);
            }

            if (need_resample == 1) {
                smp.down(buf, output0);
            } else if (need_resample == 2) {
                smp.up(ReCount, buf, output0);
            }
        } else {
            for (int i0 = 0; i0 < count; i0 = i0 + 1) {
                 output0[i0] = model->forward (&output0[i0]);
            }
        }
    }
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec1[0] = fSlow1 + 0.999 * fRec1[1];
        output0[i0] = float(double(output0[i0]) * fRec1[0]);
        fRec1[1] = fRec1[0];
    }
}

void RtNeural::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<RtNeural*>(p)->compute(count, input0, output0);
}

void RtNeural::get_samplerate(std::string config_file) {
    std::ifstream infile(config_file);
    infile.imbue(std::locale::classic());
    std::string line;
    std::string key;
    std::string value;
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            std::istringstream buf(line);
            buf >> key;
            buf >> value;
            if (key.compare("\"samplerate\":") == 0) {
                value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
                mSampleRate = std::stoi(value);
                break;
            }
            key.clear();
            value.clear();
        }
        infile.close();
    }
}

// non rt callback
void RtNeural::load_json_file() {
    if (!load_file.empty() && is_inited) {
        gx_system::atomic_set(&ready, 0);
        sync();
        delete model;
        model = nullptr;
        mSampleRate = 0;
        need_resample = 0;
        clear_state_f();
        try {
            get_samplerate(std::string(load_file));
            std::ifstream jsonStream(std::string(load_file), std::ifstream::binary);
            model = RTNeural::json_parser::parseJson<float>(jsonStream).release();
        } catch (const std::exception&) {
            gx_print_info("RTNeural Amp Modeler", "fail to load " + load_file);
            load_file = "None";
        }
        
        if (model) {
            model->reset();
            if (mSampleRate <= 0) mSampleRate = 48000;
            if (mSampleRate > fSampleRate) {
                smp.setup(fSampleRate, mSampleRate);
                need_resample = 1;
            } else if (mSampleRate < fSampleRate) {
                smp.setup(mSampleRate, fSampleRate);
                need_resample = 2;
            } 
        } 
        gx_system::atomic_set(&ready, 1);
    }
}

int RtNeural::register_par(const ParamReg& reg)
{
    reg.registerFloatVar((idstring + ".input").c_str(),N_("Input"),"S",N_("gain (dB)"),&fVslider0, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".output").c_str(),N_("Output"),"S",N_("gain (dB)"),&fVslider1, 0.0, -20.0, 20.0, 0.1, 0);
    param.reg_string((idstring + ".loadfile").c_str(), "", &load_file, "*.json", true)->set_desc(N_("import *.json file"));

    param[(idstring + ".loadfile").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &RtNeural::load_json_file)));
    return 0;
}

int RtNeural::register_params_static(const ParamReg& reg)
{
    return static_cast<RtNeural*>(reg.plugin)->register_par(reg);
}

inline int RtNeural::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file((idstring + "_ui.glade").c_str());
        return 0;
    }
    if (form & UI_FORM_STACK) {

        b.openHorizontalhideBox("");
            b.create_master_slider((idstring + "input").c_str(), "Input");
        b.closeBox();
        b.openHorizontalBox("");

            b.create_mid_rackknob((idstring + "input").c_str(), "Input");
            b.create_fload_switch(sw_button, nullptr, (idstring + "loadfile").c_str());
            b.create_mid_rackknob((idstring + "output").c_str(), "Output");

        b.closeBox();

        return 0;
    }
    return -1;
}

int RtNeural::load_ui_f_static(const UiBuilder& b, int form)
{
    return static_cast<RtNeural*>(b.plugin)->load_ui_f(b, form);
}

void RtNeural::del_instance(PluginDef *p)
{
    delete static_cast<RtNeural*>(p);
}

/****************************************************************
 ** class RtNeuralMulti
 */

RtNeuralMulti::RtNeuralMulti(ParamMap& param_, std::string id_, ParallelThread *pro_, sigc::slot<void> sync_)
    : PluginDef(), modela(nullptr), modelb(nullptr), param(param_), pro(pro_), smpa(), smpb(), sync(sync_), idstring(id_), plugin() {
    version = PLUGINDEF_VERSION;
    flags = 0;
    id = idstring.c_str();
    name = N_("RTNeural Multi Engine");
    groups = 0;
    description = N_("Neural network engine written by Jatin Chowdhury"); // description (tooltip)
    category = N_("Neural");       // category
    shortname = "RTNeuralMulti";     // shortname
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init_static;
    activate_plugin = 0;
    register_params = register_params_static;
    load_ui = load_ui_f_static;
    clear_state = clear_state_f_static;
    delete_instance = del_instance;
    plugin = this;
    need_aresample = 0;
    need_bresample = 0;
    is_inited = false;
    gx_system::atomic_set(&ready, 0);
 }

RtNeuralMulti::~RtNeuralMulti() {
    delete modela;
    delete modelb;
}

inline void RtNeuralMulti::clear_state_f()
{
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec01[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec2[l0] = 0.0;
    for (int l0 = 0; l0 < 16384; l0 = l0 + 1) fDec0[l0] = 0.0;
    for (int l1 = 0; l1 < 2; l1 = l1 + 1) fDel4[l1] = 0.0;
    for (int l2 = 0; l2 < 2; l2 = l2 + 1) fDel0[l2] = 0.0;
    for (int l3 = 0; l3 < 2; l3 = l3 + 1) fDel1[l3] = 0.0;
    for (int l4 = 0; l4 < 2; l4 = l4 + 1) fDel2[l4] = 0.0;
    for (int l5 = 0; l5 < 2; l5 = l5 + 1) fDel3[l5] = 0.0;
}

void RtNeuralMulti::clear_state_f_static(PluginDef *p)
{
    static_cast<RtNeuralMulti*>(p)->clear_state_f();
}

inline void RtNeuralMulti::init(unsigned int sample_rate)
{
    fSampleRate = sample_rate;
    clear_state_f();
    IOTA0 = 0;
    is_inited = true;
    buf = nullptr;
    nframes = 1;
    load_json_afile();
    load_json_bfile();
    pro->set<0, RtNeuralMulti, &RtNeuralMulti::processModelB>(this);
}

void RtNeuralMulti::init_static(unsigned int sample_rate, PluginDef *p)
{
    static_cast<RtNeuralMulti*>(p)->init(sample_rate);
}

void always_inline RtNeuralMulti::processDelay(int count, float *buf)
{
	double fSlow0 = 0.0010000000000000009 * double(fVslider02);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(buf[i0]);
		fDec0[IOTA0 & 16383] = fTemp0;
		fDel4[0] = fSlow0 + 0.999 * fDel4[1];
		double fTemp1 = ((fDel0[1] != 0.0) ? (((fDel1[1] > 0.0) & (fDel1[1] < 1.0)) ? fDel0[1] : 0.0) : (((fDel1[1] == 0.0) & (fDel4[0] != fDel2[1])) ? 0.0009765625 : (((fDel1[1] == 1.0) & (fDel4[0] != fDel3[1])) ? -0.0009765625 : 0.0)));
		fDel0[0] = fTemp1;
		fDel1[0] = std::max<double>(0.0, std::min<double>(1.0, fDel1[1] + fTemp1));
		fDel2[0] = (((fDel1[1] >= 1.0) & (fDel3[1] != fDel4[0])) ? fDel4[0] : fDel2[1]);
		fDel3[0] = (((fDel1[1] <= 0.0) & (fDel2[1] != fDel4[0])) ? fDel4[0] : fDel3[1]);
		double fTemp2 = fDec0[(IOTA0 - int(std::min<double>(8192.0, std::max<double>(0.0, fDel2[0])))) & 16383];
		buf[i0] = float(fTemp2 + fDel1[0] * (fDec0[(IOTA0 - int(std::min<double>(8192.0, std::max<double>(0.0, fDel3[0])))) & 16383] - fTemp2));
		IOTA0 = IOTA0 + 1;
		fDel4[1] = fDel4[0];
		fDel0[1] = fDel0[0];
		fDel1[1] = fDel1[0];
		fDel2[1] = fDel2[0];
		fDel3[1] = fDel3[0];
	}
}

void always_inline RtNeuralMulti::processModelA(int count, float *bufa) {
    if (!modela) return;
    double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));

    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec0[0] = fSlow0 + 0.999 * fRec0[1];
        bufa[i0] = float(double(bufa[i0]) * fRec0[0]);
        fRec0[1] = fRec0[0];
    }

    if (modela && gx_system::atomic_get(ready)) {
        if (need_aresample ) {
            int ReCounta = count;

            if (need_aresample == 1) {
                ReCounta = smpa.max_out_count(count);
            } else if (need_aresample == 2) {
                ReCounta = static_cast<int>(ceil((count*static_cast<double>(maSampleRate))/fSampleRate));
            }

            float bufa1[ReCounta];
            memset(bufa1, 0, ReCounta*sizeof(float));

            if (need_aresample == 1) {
                ReCounta = smpa.up(count, bufa, bufa1);
            } else if (need_aresample == 2) {
                smpa.down(bufa, bufa1);
            } else {
                memcpy(bufa1, bufa, ReCounta * sizeof(float));
            }

            for (int i0 = 0; i0 < ReCounta; i0 = i0 + 1) {
                 bufa1[i0] = modela->forward (&bufa1[i0]);
            }

            if (need_aresample == 1) {
                smpa.down(bufa1, bufa);
            } else if (need_aresample == 2) {
                smpa.up(ReCounta, bufa1, bufa);
            }
        } else {
            for (int i0 = 0; i0 < count; i0 = i0 + 1) {
                 bufa[i0] = modela->forward (&bufa[i0]);
            }
        }
    }
}

void always_inline RtNeuralMulti::processModelB() {
    if (!modelb) return;
    double fSlow01 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider01));

    for (int i0 = 0; i0 < nframes; i0 = i0 + 1) {
        fRec01[0] = fSlow01 + 0.999 * fRec01[1];
        buf[i0] = float(double(buf[i0]) * fRec01[0]);
        fRec01[1] = fRec01[0];
    }
    if (modelb && gx_system::atomic_get(ready)) {
        if (need_bresample) {
            int ReCountb = nframes;

            if (need_bresample == 1) {
                ReCountb = smpb.max_out_count(nframes);
            } else if (need_bresample == 2) {
                ReCountb = static_cast<int>(ceil((nframes*static_cast<double>(mbSampleRate))/fSampleRate));
            }

            float buf1[ReCountb];
            memset(buf1, 0, ReCountb*sizeof(float));

            if (need_bresample == 1) {
                ReCountb = smpb.up(nframes, buf, buf1);
            } else if (need_bresample == 2) {
                smpb.down(buf, buf1);
            } else {
                memcpy(buf1, buf, ReCountb * sizeof(float));
            }

            for (int i0 = 0; i0 < ReCountb; i0 = i0 + 1) {
                 buf1[i0] = modelb->forward (&buf1[i0]);
            }

            if (need_bresample == 1) {
                smpb.down(buf1, buf);
            } else if (need_bresample == 2) {
                smpb.up(ReCountb, buf1, buf);
            }
        } else {
            for (int i0 = 0; i0 < nframes; i0 = i0 + 1) {
                 buf[i0] = modelb->forward (&buf[i0]);
            }
        }
    }
}

void always_inline RtNeuralMulti::compute(int count, float *input0, float *output0)
{
    if (output0 != input0)
        memcpy(output0, input0, count*sizeof(float));
    if (!modela || !modelb) return;
    double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
    double fSlow2 = 0.0010000000000000009 * double(fVslider2);

    float bufa[count];
    memcpy(bufa, output0, count*sizeof(float));
    float bufb[count];
    memcpy(bufb, output0, count*sizeof(float));

    if (int(fVslider02) > 0) processDelay(count, bufb);
    else processDelay(count, bufa);

    nframes = count;
    buf = bufb;

    if (pro->getProcess()) {
        pro->setProcessor(0);
        pro->runProcess();
    } else {
        processModelB();
    }

    processModelA(count, bufa);

    pro->processWait();

    if (modela && modelb && gx_system::atomic_get(ready)) {
        for (int i0 = 0; i0 < count; i0 = i0 + 1) {
            fRec2[0] = fSlow2 + 0.999 * fRec2[1];
            output0[i0] = bufa[i0] * (1.0 - fRec2[0]) + bufb[i0] * fRec2[0];
            fRec2[1] = fRec2[0];
        }
    } else if (modela && gx_system::atomic_get(ready)) {
        memcpy(output0, bufa, count*sizeof(float));
    } else if (modelb && gx_system::atomic_get(ready)) {
        memcpy(output0, bufb, count*sizeof(float));
    }
    
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec1[0] = fSlow1 + 0.999 * fRec1[1];
        output0[i0] = float(double(output0[i0]) * fRec1[0]);
        fRec1[1] = fRec1[0];
    }
}

void RtNeuralMulti::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<RtNeuralMulti*>(p)->compute(count, input0, output0);
}

void RtNeuralMulti::get_samplerate(std::string config_file, int *mSampleRate) {
    std::ifstream infile(config_file);
    infile.imbue(std::locale::classic());
    std::string line;
    std::string key;
    std::string value;
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            std::istringstream buf(line);
            buf >> key;
            buf >> value;
            if (key.compare("\"samplerate\":") == 0) {
                value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
                (*mSampleRate) = std::stoi(value);
                break;
            }
            key.clear();
            value.clear();
        }
        infile.close();
    }
}

// non rt callback
void RtNeuralMulti::load_json_afile() {
    if (!load_afile.empty() && is_inited) {
        gx_system::atomic_set(&ready, 0);
        sync();
        delete modela;
        modela = nullptr;
        maSampleRate = 0;
        need_aresample = 0;
        clear_state_f();
        try {
            get_samplerate(std::string(load_afile), &maSampleRate);
            std::ifstream jsonStream(std::string(load_afile), std::ifstream::binary);
            modela = RTNeural::json_parser::parseJson<float>(jsonStream).release();
        } catch (const std::exception&) {
            gx_print_info("RTNeural Multi Amp Modeler", "fail to load " + load_afile);
            load_afile = "None";
        }
        
        if (modela) {
            modela->reset();
            if (maSampleRate <= 0) maSampleRate = 48000;
            if (maSampleRate > fSampleRate) {
                smpa.setup(fSampleRate, maSampleRate);
                need_aresample = 1;
            } else if (maSampleRate < fSampleRate) {
                smpa.setup(maSampleRate, fSampleRate);
                need_aresample = 2;
            } 
            // fprintf(stderr, "A: %s\n", load_afile.c_str());
       } 
        gx_system::atomic_set(&ready, 1);
    }
}

// non rt callback
void RtNeuralMulti::load_json_bfile() {
    if (!load_bfile.empty() && is_inited) {
        gx_system::atomic_set(&ready, 0);
        sync();
        delete modelb;
        modelb = nullptr;
        mbSampleRate = 0;
        need_bresample = 0;
        clear_state_f();
        try {
            get_samplerate(std::string(load_bfile), &mbSampleRate);
            std::ifstream jsonStream(std::string(load_bfile), std::ifstream::binary);
            modelb = RTNeural::json_parser::parseJson<float>(jsonStream).release();
        } catch (const std::exception&) {
            gx_print_info("RTNeural Amp Modeler", "fail to load " + load_bfile);
            load_bfile = "None";
        }
        
        if (modelb) {
            modelb->reset();
            if (mbSampleRate <= 0) mbSampleRate = 48000;
            if (mbSampleRate > fSampleRate) {
                smpb.setup(fSampleRate, mbSampleRate);
                need_bresample = 1;
            } else if (mbSampleRate < fSampleRate) {
                smpb.setup(mbSampleRate, fSampleRate);
                need_bresample = 2;
            } 
            // fprintf(stderr, "B: %s\n", load_bfile.c_str());
        } 
        gx_system::atomic_set(&ready, 1);
    }
}

int RtNeuralMulti::register_par(const ParamReg& reg)
{
    reg.registerFloatVar((idstring + ".input").c_str(),N_("Input A"),"S",N_("gain (dB)"),&fVslider0, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".inputb").c_str(),N_("Input B"),"S",N_("gain (dB)"),&fVslider01, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".cdelay").c_str(),N_("Delta Delay"),"S",N_("Delay A/B"),&fVslider02, 0.0, -4096.0, 4096.0, 1.0, 0);
    reg.registerFloatVar((idstring + ".output").c_str(),N_("Output"),"S",N_("gain (dB)"),&fVslider1, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".mix").c_str(),N_("Mix"),"S",N_("mix models"),&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
    param.reg_string((idstring + ".loadafile").c_str(), "", &load_afile, "*.json", true)->set_desc(N_("import *.json file"));
    param.reg_string((idstring + ".loadbfile").c_str(), "", &load_bfile, "*.json", true)->set_desc(N_("import *.json file"));

    param[(idstring + ".loadafile").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &RtNeuralMulti::load_json_afile)));
    param[(idstring + ".loadbfile").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &RtNeuralMulti::load_json_bfile)));
    return 0;
}

int RtNeuralMulti::register_params_static(const ParamReg& reg)
{
    return static_cast<RtNeuralMulti*>(reg.plugin)->register_par(reg);
}

inline int RtNeuralMulti::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file((idstring + "_ui.glade").c_str());
        return 0;
    }
    if (form & UI_FORM_STACK) {

        b.openHorizontalhideBox("");
            b.create_master_slider((idstring + "output").c_str(), "Output");
        b.closeBox();
        b.openHorizontalBox("");
            b.openVerticalBox("");
                b.create_mid_rackknob((idstring + ".input").c_str(), "Input A");
                b.create_mid_rackknob((idstring + ".inputb").c_str(), "Input B");
            b.closeBox();
            b.openVerticalBox("");
                b.create_fload_switch(sw_button, nullptr, (idstring + ".loadafile").c_str());
                b.create_fload_switch(sw_button, nullptr, (idstring + ".loadbfile").c_str());
            b.closeBox();
            b.create_mid_rackknob((idstring + ".output").c_str(), "Output");
            b.create_mid_rackknob((idstring + ".mix").c_str(), "Mix");

        b.closeBox();

        return 0;
    }
    return -1;
}

int RtNeuralMulti::load_ui_f_static(const UiBuilder& b, int form)
{
    return static_cast<RtNeuralMulti*>(b.plugin)->load_ui_f(b, form);
}

void RtNeuralMulti::del_instance(PluginDef *p)
{
    delete static_cast<RtNeuralMulti*>(p);
}

/****************************************************************
 ** class Directout
 */

Directout::Directout(EngineControl& engine_, sigc::slot<void> sync_)
    : PluginDef(),
      outdata(0),
      engine(engine_),
      sync(sync_),
      mem_allocated(false),
      plugin() {
    version = PLUGINDEF_VERSION;
    groups = 0;
    flags = 0;
    category = "NONE";
    id = "dout";
    name = N_("Directoutput");
    stereo_audio = compute_static;
    mono_audio = 0;
    set_samplerate = init_static;
    activate_plugin = 0;
    load_ui = 0;
    register_params = 0;
    plugin.set_pdef(this);
    plugin = this;
    engine.signal_buffersize_change().connect(
    sigc::mem_fun(*this, &Directout::change_buffersize));
}

Directout::~Directout() {
    mem_free();
}

inline void Directout::init(unsigned int samplingFreq)
{
    bsize = int(engine.get_buffersize());
    fSamplingFreq = samplingFreq;
    mem_alloc();
}

void Directout::init_static(unsigned int samplingFreq, PluginDef *p)
{
    static_cast<Directout*>(p)->init(samplingFreq);
}

void Directout::mem_alloc()
{
    if (mem_allocated) {
        return;
    }
    bsize = int(engine.get_buffersize());
    assert(bsize>0);
    try {
       outdata = new float[bsize]();
    } catch(...) {
            gx_print_error("Directout", "cannot allocate memory pool");
            return;
        }
    mem_allocated = true;
}

void Directout::mem_free()
{
    mem_allocated = false;
    if (outdata) {
        delete[] outdata;
        outdata = 0;
    }
}

void Directout::change_buffersize(unsigned int size)
{
    sync();
    if (mem_allocated) {
        mem_free();
        mem_alloc();
    }
}

void always_inline Directout::compute(int count, float *input0, float *input1, float *output0, float *output1) {
    if (!fdfill) {
        return;
    }
    for (int i=0; i<count; i++) {
        output0[i] =  input0[i] + outdata[i];
        output1[i] =  input1[i] + outdata[i];
    }
    memset(outdata,0,count*sizeof(float));
    fdfill = false;
}

void Directout::set_data(bool dfill) {
    fdfill = dfill;
}

void __rt_func Directout::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1, PluginDef *p)
{
    static_cast<Directout*>(p)->compute(count, input0, input1, output0, output1);
}


/****************************************************************
 ** class LiveLooper
 */

#include "gx_livelooper.cc"

/****************************************************************
 ** class SCapture
 */

#include "gx_record.cc"

/****************************************************************
 ** class DrumSequencer
 */

#ifndef GUITARIX_AS_PLUGIN
#include "faust/drumseq.cc"
#else
#include "drumseq.cc"
#endif

float* Drumout::set = 0;
float* Drumout::data = 0;
bool Drumout::mb = false;
Plugin Drumout::output_drum = Plugin();
Plugin Drumout::input_drum = Plugin();
PluginDef Drumout::outputdrum = PluginDef();

Drumout::Drumout() {

    output_drum.set_pdef(&outputdrum);

    outputdrum.version = PLUGINDEF_VERSION;
    outputdrum.id = "drumout";
    outputdrum.name = "?drumout";
    outputdrum.stereo_audio = outputdrum_compute;
}

void always_inline Drumout::outputdrum_compute(int count, float *input0, float *input1, float *output0, float *output1, PluginDef*) {
    if (!(*set) || !input_drum.get_on_off() || !mb) {
        return;
    }
    for (int i=0; i<count; i++) {
        output0[i] =  input0[i] + data[i];
        output1[i] =  input1[i] + data[i];
    }
    memset(data,0,count*sizeof(float));
}

void Drumout::set_data(float* mode, bool ready, float* buf) {
    set = mode;
    mb = ready;
    data = buf;
}

void Drumout::set_plugin(Plugin p) {
    input_drum = p;
}

static const char* seq_groups[] = {
    "hat_closed.dsp", N_("DrumSequencer"),
    "kick.dsp", N_("DrumSequencer"),
    "snare.dsp", N_("DrumSequencer"),
    "tom.dsp", N_("DrumSequencer"),
    "sequencer", N_("DrumSequencer"),
    0
};

DrumSequencer::DrumSequencer(EngineControl& engine_, sigc::slot<void> sync_)
    : PluginDef(),
      Vectom(0),
      Vectom1(0),
      Vectom2(0),
      Veckick(0),
      Vecsnare(0),
      Vechat(0),
      engine(engine_),
      mem_allocated(false),
      sync(sync_),
      ready(false),
      outdata(0),
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
    load_ui = drum_load_ui;
    register_params = register_params_static;
    delete_instance = del_instance;
    plugin = this;
    engine.signal_buffersize_change().connect(
    sigc::mem_fun(*this, &DrumSequencer::change_buffersize));
}

DrumSequencer::~DrumSequencer() {
    mem_free();
}

inline void DrumSequencer::init(unsigned int samplingFreq)
{
    bsize = int(engine.get_buffersize());
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
    mem_alloc();
    drums.init(samplingFreq);
    Drumout::set_plugin(plugin);
}

void DrumSequencer::init_static(unsigned int samplingFreq, PluginDef *p)
{
    static_cast<DrumSequencer*>(p)->init(samplingFreq);
}

void DrumSequencer::mem_alloc()
{
    if (mem_allocated) {
        return;
    }
    bsize = int(engine.get_buffersize());
    assert(bsize>0);
    try {
       outdata = new float[bsize]();
    } catch(...) {
            gx_print_error("DrumSequencer", "cannot allocate memory pool");
            return;
        }
    mem_allocated = true;
    Drumout::set_data(&fSlow22, mem_allocated, outdata);
}

void DrumSequencer::mem_free()
{
    ready = false;
    mem_allocated = false;
    Drumout::set_data(0, mem_allocated, 0);
    if (outdata) {
        delete[] outdata;
        outdata = 0;
    }
}

void DrumSequencer::change_buffersize(unsigned int size)
{
    sync();
    ready = false;
    if (mem_allocated) {
        mem_free();
        mem_alloc();
    }
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

// hat = 1600Hz
// kick = 50Hz
// toms = 90 - 128 - 150Hz
// snare = 523 - 7040Hz
// todo: add compressor

void always_inline DrumSequencer::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
    double     fSlow15 = (60.0/double(fsliderbpm*ftact))*fSamplingFreq;
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
        counter -= iSlow15; //int(r*fsliderhum);
        
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
    if (int(fSlow22 && mem_allocated)) {
        memcpy(output0, input0, count * sizeof(float));
        drums.compute(count,outdata,outdata);
    } else {
        drums.compute(count,input0,output0);
    }
}

void __rt_func DrumSequencer::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
    static_cast<DrumSequencer*>(p)->compute(count, input0, output0);
}

int DrumSequencer::register_par(const ParamReg& reg)
{
    reg.registerFloatVar("seq.hat_closed.dsp.gate","","BA","",&fSlow3, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.kick.dsp.gate","","BA","",&fSlow5, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.snare.dsp.gate","","BA","",&fSlow1, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.tom.dsp.gate","","BA","",&fSlow7, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.tom.dsp.Gainf","","SA","",&fSlow20, -2e+01, -6e+01, 4e+01, 0.1, 0);
    reg.registerFloatVar("seq.tom.dsp.Gain","","S",N_("Volume level in decibels"),&fSlow12, -2e+01, -6e+01, 4e+01, 0.1, 0);
    reg.registerFloatVar("seq.tom.dsp.Gain1","","S",N_("Volume level in decibels"),&fSlow14, -2e+01, -6e+01, 4e+01, 0.1, 0);
    reg.registerFloatVar("seq.tom.dsp.Gain2","","S",N_("Volume level in decibels"),&fSlow16, -2e+01, -6e+01, 4e+01, 0.1, 0);
    reg.registerFloatVar("seq.tom.dsp.freq","","SA","",&fSlow18, 9e+01, 9e+01, 1.5e+02, 1.0, 0);
    reg.registerFloatVar("seq.bpm","","S",N_("Beats per Minute"),&fsliderbpm, 120, 24, 360, 1, 0);
    static const value_pair ftact_values[] = {{"1/4"},{"2/4"},{"3/4"},{"4/4"},{0}};
    reg.registerFloatVar("seq.tact","","S",N_("select tact"),&ftact, 4.0, 1.0, 4.0, 1.0, ftact_values);
    reg.registerFloatVar("seq.asequences","","S",N_("Number of Sequences"),&fsec, 24.0, 24.0, 240.0, 4.0, 0);
    reg.registerFloatVar("seq.hum","","B",N_("Randomize Sequence"),&fsliderhum, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.npreset","","BO",N_("Load next unit preset"),0, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.ppreset","","BO",N_("Load previous unit preset"),0, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.pos","","SN","",&position, 0.0, 0.0, 2300.0, 1.0, 0);
    reg.registerFloatVar("seq.step","","SN","",&step, 0.0, 0.0, 240.0, 1.0, 0);
    reg.registerFloatVar("seq.step_orig","","SN","",&step_orig, 0.0, 0.0, 240.0, 1.0, 0);
    reg.registerFloatVar("seq.set_step","","BO",N_("Set stepper one Beat back"),0, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.set_fstep","","BO",N_("Set stepper one Beat forward"),0, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.set_sync","","BO",N_("Set stepper back on Beat "),0, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.reset_step","","BO",N_("Set stepper one Start"),0, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.follow","","BA",N_("follow playhead"),0, 0.0, 0.0, 1.0, 1.0, 0);
    reg.registerFloatVar("seq.direct_out","","BA",N_("bypass the rack for direct output"),&fSlow22, 0.0, 0.0, 1.0, 1.0, 0);
    for (int i=0; i<24; i++) Vectom.push_back(0);
    for (int i=0; i<24; i++) Vectom1.push_back(0);
    for (int i=0; i<24; i++) Vectom2.push_back(0);
    for (int i=0; i<24; i++) Veckick.push_back(0);
    for (int i=0; i<24; i++) Vechat.push_back(0);
    for (int i=0; i<24; i++) Vecsnare.push_back(0);
    seq_size = min_seq_size();
        ParamMap& param = engine.get_param();
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

//static
int DrumSequencer::drum_load_ui(const UiBuilder& builder, int format) {
    if (format & UI_FORM_GLADE) {
        builder.load_glade_file("drumsequencer_ui.glade");
        return 0;
    } else if (format & UI_FORM_STACK) {
        //static gx_seq::SEQWindow *seqw = gx_seq::SEQWindow::create("seq", machine);
        builder.openHorizontalhideBox("");
        builder.create_master_slider("seq.gain", _("Gain"));
        builder.insertSpacer();
        builder.insertSpacer();
        //builder.addSmallSeqButton(C_("Setup", "S"), seqw);
        builder.closeBox();
        builder.openVerticalBox("");
        {
            builder.openFrameBox("");
            builder.closeBox();
            builder.openHorizontalBox("");
            {
                builder.openFrameBox("");
                builder.closeBox();
                builder.openFrameBox("");
                //builder.addSeqButton(_("Setup"), seqw);
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
*                         The Wide Open License (WOL)
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

smbPitchShift::smbPitchShift(EngineControl& engine_, sigc::slot<void> sync_):
  PluginDef(),
  engine(engine_),
  mem_allocated(false),
  sync(sync_),
  ready(false),
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
            gx_print_error("detune", "cannot allocate memory pool");
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
    
    if (!ready || count != numSampsToProcess) {
        if (indata != outdata) {
            memcpy(outdata,indata,count*sizeof(float));
        }
        return;
    }
    
    resamp.down(numSampsToResamp,indata,resampin);
    double     fSlow0 = (0.01 * wet);
    double     fSlow1 = (0.01 * dry);

    // collect data for latency compensation
    for (i = 0; i < count; i++) {
        indata2[ii] = indata[i];
        ii++;
    }
    // collect data for fft
    for (i = 0; i < numSampsToResamp; i++) {
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
        for (i = 0; i < fftFrameSize; i++) {

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
    reg.registerFloatVar("smbPitchShift.semitone", N_("Detune"), "S", "", &semitones, 0.0, -12., 12., 0.1, 0);
    static const value_pair octave_values[] = {{"unison"},{"octave up"},{"octave down"},{0}};
    reg.registerIntVar("smbPitchShift.octave",N_("add harmonics"),"B",N_("add harmonics"),&octave, 0, 0, 0, octave_values);
    static const value_pair latency_values[] = {{"latency "},{"compensate"},{0}};
    reg.registerFloatVar("smbPitchShift.l",N_("compensate latency"),"S",N_("compensate latency"),&l, 0.0f, 0.0f, 1.0f, 1.0f, latency_values);
    static const value_pair latency_set[] = {{"high quality"},{"low quality"},{"realtime"},{0}};
    reg.registerIntVar("smbPitchShift.latency",N_("latency settings"),"B",N_("latency settings"),&latency, 0, 0, 0, latency_set);
    reg.registerFloatVar("smbPitchShift.wet", N_("Wet"), "S", N_("Wet amount"), &wet, 50.0, 0.0, 100.0, 1, 0);
    reg.registerFloatVar("smbPitchShift.dry", N_("Dry"), "S", N_("Dry amount"), &dry, 50.0, 0.0, 100.0, 1, 0);
    reg.registerFloatVar("smbPitchShift.a", N_("low"), "S", N_("Sub"), &a, 1.0, 0.0, 2.0, 0.01, 0);
    reg.registerFloatVar("smbPitchShift.b", N_("middle low"), "S", N_("Low"), &b, 1.0, 0.0, 2.0, 0.01, 0);
    reg.registerFloatVar("smbPitchShift.c", N_("middle treble"), "S", N_("Mid"), &c, 1.0, 0.0, 2.0, 0.01, 0);
    reg.registerFloatVar("smbPitchShift.d", N_("treble"), "S", N_("Hi"), &d, 1.0, 0.0, 2.0, 0.01, 0);
    engine.get_param()["smbPitchShift.latency"].signal_changed_int().connect(
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
