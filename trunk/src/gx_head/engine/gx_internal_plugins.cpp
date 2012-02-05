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
      fGainCor(1),
      file_changed(),
      faflist() {
}

GxJConvSettings& GxJConvSettings::operator=(GxJConvSettings const& jcset) {
    bool changed = (fIRFile != jcset.fIRFile || fIRDir != jcset.fIRDir);
    fIRFile = jcset.fIRFile;
    fIRDir = jcset.fIRDir;
    fGain = jcset.fGain;
    fOffset = jcset.fOffset;
    fLength = jcset.fLength;
    fDelay = jcset.fDelay;
    gainline = jcset.gainline;
    fGainCor = jcset.fGainCor;
    // don't assign file_changed
    faflist = jcset.faflist;
    if (changed) {
	file_changed();
    }
    return *this;
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
    file_changed();
}

void GxJConvSettings::writeJSON(gx_system::JsonWriter& w,
				const gx_system::PathList& search_path) {
    w.begin_object(true);
    w.write_key("jconv.IRFile");
    w.write(fIRFile, true);
    w.write_key("jconv.IRDir");
    string dir = fIRDir;
    if (search_path.contains(dir)) {
	dir = "";
    }
    w.write(dir, true);
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

void GxJConvSettings::readJSON(gx_system::JsonParser& jp,
			       const gx_system::PathList& search_path) {
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
    if (!fIRFile.empty() && fIRDir.empty()) {
	search_path.find_dir(&fIRDir, fIRFile);
    }
}


/****************************************************************
 ** class ConvolverAdapter
 */

#include "faust/jconv_post.cc"

ConvolverAdapter::ConvolverAdapter(EngineControl& engine_)
    : PluginDef(),
      conv(),
      activate_mutex(),
      engine(engine_),
      activated(false),
      jc_post(),
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
    engine.signal_buffersize_change().connect(
	sigc::mem_fun(*this, &ConvolverAdapter::change_buffersize));
    GxJConvSettings::checkbutton7 = &plugin.on_off;
}

ConvolverAdapter::~ConvolverAdapter() {
}

void ConvolverAdapter::change_buffersize(unsigned int size) {
    boost::mutex::scoped_lock lock(activate_mutex);
    if (activated) {
	conv.stop();
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
    if (!plugin.on_off) {
        return;
    }
    conv.stop();
    while (conv.is_runnable()) {
	conv.checkstate();
    }
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
        plugin.on_off = false;
    }
}

bool ConvolverAdapter::conv_start() {
    if (!conv.get_buffersize() || !conv.get_samplerate()) {
	return false;
    }
    string path = jcset.getFullIRPath();
    if (path.empty()) {
        gx_system::gx_print_warning(_("convolver"), _("no impulseresponse file"));
        plugin.on_off = false;
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

void ConvolverAdapter::convolver(int count, float *input0, float *input1,
				 float *output0, float *output1, PluginDef* plugin) {
    ConvolverAdapter& self = *static_cast<ConvolverAdapter*>(plugin);
    if (self.conv.is_runnable()) {
        float conv_out0[count];
        float conv_out1[count];
        if (!self.conv.compute(count, output0, output1, conv_out0, conv_out1)) {
            self.plugin.on_off = false;
	    gx_system::gx_print_error("Convolver", "overload");
        } else {
            self.jc_post.compute(count, output0, output1,
			    conv_out0, conv_out1, output0, output1);
        }
    }
}

int ConvolverAdapter::convolver_register(const ParamReg& reg) {
    return static_cast<ConvolverAdapter*>(reg.plugin)->jc_post.register_par(reg);
}

void ConvolverAdapter::convolver_init(unsigned int samplingFreq, PluginDef *p) {
    ConvolverAdapter& self = *static_cast<ConvolverAdapter*>(p);
    boost::mutex::scoped_lock lock(self.activate_mutex);
    if (self.activated) {
	self.conv.stop();
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

int ConvolverAdapter::activate(bool start, PluginDef *p) {
    ConvolverAdapter& self = *static_cast<ConvolverAdapter*>(p);
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
	    gx_system::gx_print_error(_("convolver"), "jconv post activate error?!");
	    return -1;
	}
	if (!self.conv_start()) {
	    return -1;
	}
    } else {
	self.conv.stop();
	self.jc_post.activate(false);
    }
    return 0;
}


/****************************************************************
 ** class BaseConvolver
 */


BaseConvolver::BaseConvolver(EngineControl& engine_, gx_resample::BufferResampler& resamp)
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
    engine.signal_buffersize_change().connect(
	sigc::mem_fun(*this, &BaseConvolver::change_buffersize));
}

BaseConvolver::~BaseConvolver() {
}

void BaseConvolver::change_buffersize(unsigned int bufsize) {
    boost::mutex::scoped_lock lock(activate_mutex);
    conv.set_buffersize(bufsize);
    if (activated) {
	if (!bufsize) {
	    conv_stop();
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

#include "faust/cabinet_impulse_former.cc"

CabinetConvolver::CabinetConvolver(EngineControl& engine, gx_resample::BufferResampler& resamp):
    BaseConvolver(engine, resamp),
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
    mono_audio = run_cab_conf;
    register_params = register_cab;
}

CabinetConvolver::~CabinetConvolver() {
    delete[] cab_names;
}

bool CabinetConvolver::conv_update() {
    update_sum();
    bool ret = update();
    if (! ret) {
	ret = start();
    }
    return ret;
}

bool CabinetConvolver::start(bool force) {
    CabDesc& cab = *getCabEntry(cabinet).data;
    if (cabinet_changed() || sum_changed() || force) {
	conv.stop();
        update_cabinet();
	update_sum();
	impf.init(cab.ir_sr);
	float cab_irdata_c[cab.ir_count];
	impf.compute(cab.ir_count,cab.ir_data,cab_irdata_c);
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
    impf.compute(cab.ir_count,cab.ir_data,cab_irdata_c);
    return conv.update(cab.ir_count, cab_irdata_c, cab.ir_sr);
}

// reduce gain to compensate the increased gain by the cabinet
inline void CabinetConvolver::compensate_cab(int count, float *input0, float *output0) {
    double fSlow0 = 0.001 * pow(10, -0.1 * level);
    static double fRec0[2] = {0, 0};
    for (int i = 0; i < count; i++) {
        fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
        output0[i] = input0[i] * fRec0[0];
        // post processing
        fRec0[1] = fRec0[0];
    }
}

// wraper for the rack order function pointers
void CabinetConvolver::run_cab_conf(int count, float *input0, float *output0, PluginDef *p) {
    CabinetConvolver& self = *static_cast<CabinetConvolver*>(p);
    self.compensate_cab(count, output0, output0);
    if (!self.conv.compute(count, output0)) {
	gx_system::gx_print_error("Convolver", "cabinet overload");
        self.current_cab = -1;
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
 ** class ContrastConvolver
 */

#include "faust/presence_level.cc"

ContrastConvolver::ContrastConvolver(EngineControl& engine, gx_resample::BufferResampler& resamp):
    BaseConvolver(engine, resamp),
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

bool ContrastConvolver::start(bool force) {
    if (sum_changed() || force) {
	conv.stop();
	update_sum();
	presl.init(contrast_ir_desc.ir_sr);
	float contrast_irdata_c[contrast_ir_desc.ir_count];
	presl.compute(contrast_ir_desc.ir_count,contrast_ir_desc.ir_data,contrast_irdata_c);
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
    self.presl.register_par(reg);
    return 0;
}

// wraper for the presence function
void ContrastConvolver::run_contrast(int count, float *input0, float *output0, PluginDef *p) {
    ContrastConvolver& self = *static_cast<ContrastConvolver*>(p);
    self.compensate_con(count, output0, output0);
    if (!self.conv.compute(count, output0)) {
	gx_system::gx_print_error("Convolver", "presence overload");
        self.sum = no_sum;
    }
}

} // namespace gx_engine
