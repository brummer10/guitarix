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
#include "gx_parameter.h"
#include "gx_pluginloader.h"
#include "gx_ui.h"
#include "gx_convolver.h"
#include "gx_jack.h"
#include "gx_internal_plugins.h"
#include "gx_engine.h" //FIXME: only for audio.result and audio.oversample
#include "gx_pitch_tracker.h"
#include "gx_jconv_settings.h"
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

void MonoMute::process(int count, float *input, float *output) {
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
			 float *output0, float *output1) {
    (void)memset(output0, 0, count*sizeof(float));
    (void)memset(output1, 0, count*sizeof(float));
}

MaxLevel::MaxLevel()
    : PluginDef() {
    version = PLUGINDEF_VERSION;
    id = "maxlevel";
    name = "?maxlevel";
    stereo_audio = process;
    activate_plugin = activate;
}

float MaxLevel::maxlevel[2] = {0};

void MaxLevel::process(int count, float *input1, float *input2, float*, float*) {
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
    id = "midi_out";
    name = N_("Midi Out");
    groups = midi_out_groups;
    mono_audio = fill_buffer;
    plugin.pdef = this;
}

void MidiAudioBuffer::fill_buffer(int count, float *input, float*) {
    gx_jack::gxjack.gx_jack_midi_process(count, input);
}


/****************************************************************
 ** class TunerAdapter
 */

TunerAdapter::TunerAdapter(const Plugin& pl)
    : PluginDef(),
      state(),
      dep_plugin(pl),
      plugin() {
    version = PLUGINDEF_VERSION;
    id = "tuner";
    name = "?tuner";
    mono_audio = feed_tuner;
    register_params = regparam;
    plugin.pdef = this;
}

void TunerAdapter::set_and_check(int use, bool on) {
    if (on) {
	state |= use;
    } else {
	state &= ~use;
    }
    plugin.on_off = state;
}

void TunerAdapter::feed_tuner(int count, float* input, float*) {
    pitch_tracker.add(count, input);
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

void NoiseGate::inputlevel_compute(int count, float *input, float *output) {
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

void NoiseGate::outputgate_compute(int count, float *input, float *output) {
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

OscilloscopeAdapter::OscilloscopeAdapter(gx_ui::GxUI *ui):
  PluginDef(),
  plugin(),
  activation(),
  post_pre_signal(ui, &plugin.effect_post_pre)
{
    assert(buffer == 0);
    version = PLUGINDEF_VERSION;
    id = "oscilloscope";
    name = N_("Oscilloscope");
    mono_audio = fill_buffer;
    activate_plugin = activate;
    plugin.pdef = this;
}

float*& OscilloscopeAdapter::buffer = audio.result; //FIXME (-> gxjack service)

// rt process function
void OscilloscopeAdapter::fill_buffer(int count, float *input0, float *output0) {
    (void)memcpy(buffer, output0, sizeof(float)*count);
}

int OscilloscopeAdapter::activate(bool start, PluginDef *plugin) {
    return static_cast<OscilloscopeAdapter*>(plugin)->activation(start);
}

void OscilloscopeAdapter::clear_buffer() {
    memset(buffer, 0, gx_jack::gxjack.jack_bs*sizeof(float)); //FIXME
}


/****************************************************************
 ** class ConvolverAdapter
 */

ConvolverAdapter::ConvolverAdapter(gx_ui::GxUI *ui)
    : PluginDef(),
      plugin(),
      activation() {
    version = PLUGINDEF_VERSION;
    id = "jconv";
    name = N_("Convolver");
    stereo_audio = convolver;
    set_samplerate = convolver_init;
    activate_plugin = activate;
    register_params = convolver_register;
    //FIXME: add clear_state
    plugin = this;
}

GxConvolver ConvolverAdapter::conv;

static gboolean conv_error_message(gpointer data) {
    gx_system::gx_print_error("Convolver", "overload");
    return false;
}

#include "faust/jconv_post.cc"

void ConvolverAdapter::convolver(int count, float *input0, float *input1,
				 float *output0, float *output1) {
    if (conv.is_runnable()) {
        // reuse oversampling buffer
        float *conv_out0 = audio.oversample;
        float *conv_out1 = audio.oversample+count;
        if (!conv.compute(count, output0, output1, conv_out0, conv_out1)) {
            *gx_jconv::GxJConvSettings::checkbutton7 = 0;
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

void ConvolverAdapter::convolver_init(int samplingFreq, PluginDef *p) {
    jconv_post::init(samplingFreq, p);
}

int ConvolverAdapter::activate(bool start, PluginDef *plugin) {
    return static_cast<ConvolverAdapter*>(plugin)->activation(start);
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

CabinetConvolver::CabinetConvolver(gx_ui::GxUI *ui):
    PluginDef(),
    cabinet(0),
    bass(0),
    treble(0),
    sum(no_sum),
    cab_names(new value_pair[cab_table_size+1]),
    plugin() {
    for (unsigned int i = 0; i < cab_table_size; ++i) {
	CabEntry& cab = getCabEntry(i);
	cab_names[i].value_id = cab.value_id;
	cab_names[i].value_label = cab.value_label;
    }
    cab_names[cab_table_size].value_id = 0;
    cab_names[cab_table_size].value_label = 0;
    version = PLUGINDEF_VERSION;
    id = "cab";
    name = N_("Cabinet");
    mono_audio = run_cab_conf;
    activate_plugin = activate;
    register_params = register_cab;
    plugin = this;
}

CabinetConvolver::~CabinetConvolver() {
    delete cab_names;
}

GxSimpleConvolver CabinetConvolver::conv;
int CabinetConvolver::current_cab = -1;
float CabinetConvolver::level = 0;

bool CabinetConvolver::conv_update() {
    update_sum();
    bool ret = update();
    if (! ret) {
	ret = conv_start();
    }
    return ret;
}

#include "faust/cabinet_impulse_former.cc"

bool CabinetConvolver::conv_start() {
    if (cabinet_changed() || sum_changed()) {
	conv.stop();
        update_cabinet();
	update_sum();
	CabDesc& cab = *getCabEntry(cabinet).data;
	cabinet_impulse_former::init(cab.ir_sr);
	float cab_irdata_c[cab.ir_count];
	cabinet_impulse_former::compute(cab.ir_count,cab.ir_data,cab_irdata_c);
	while (!conv.checkstate());
	if (!conv.configure(cab.ir_count, cab_irdata_c, cab.ir_sr)) {
	    return false;
	}
	return conv.start();
    } else {
	while (!conv.checkstate());
	if (!conv.is_runnable()) {
	    return conv.start();
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
void CabinetConvolver::run_cab_conf(int count, float *input0, float *output0) {
    compensate_cab(count, output0, output0);
    if (!conv.compute(count, output0)) {
        g_idle_add(cab_error_message, gpointer(NULL));
        current_cab = -1;
    }
}

int CabinetConvolver::activate(bool start, PluginDef *p) {
    if (start) {
	if (!static_cast<CabinetConvolver*>(p)->conv_start()) {
	    return -1;
	}
    } else {
	static_cast<CabinetConvolver*>(p)->conv_stop();
    }
    return 0;
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

ContrastConvolver::ContrastConvolver(gx_ui::GxUI *ui):
    PluginDef(),
    plugin() {
    version = PLUGINDEF_VERSION;
    id = "con";
    name = N_("Contrast convolver");
    mono_audio = run_contrast;
    activate_plugin = activate;
    register_params = register_con;
    plugin = this;
}

GxSimpleConvolver ContrastConvolver::conv;
float ContrastConvolver::level = 0;
float ContrastConvolver::sum = no_sum;

#include "faust/presence_level.cc"

bool ContrastConvolver::conv_start() {
    conv.stop();
    presence_level::init(contrast_ir_desc.ir_sr);
    float contrast_irdata_c[contrast_ir_desc.ir_count];
    presence_level::compute(contrast_ir_desc.ir_count,contrast_ir_desc.ir_data,contrast_irdata_c);
    while (!conv.checkstate());
    if (!conv.configure(contrast_ir_desc.ir_count, contrast_irdata_c, contrast_ir_desc.ir_sr)) {
        return false;
    }
    return conv.start();
}

// reduce gain to compensate the increased gain by the cabinet
inline void ContrastConvolver::compensate_con(int count, float *input0, float *output0) {
    double fSlow0 = (0.0010000000000000009 * pow(10, (0.05 * (-level*2.0))));
    static double fRec0[2] = {0, 0};
    for (int i = 0; i < count; i++) {
        fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
        output0[i] = (FAUSTFLOAT)(static_cast<double>(input0[i]) * fRec0[0]);
        // post processing
        fRec0[1] = fRec0[0];
    }
}

int ContrastConvolver::register_con(const ParamReg& reg) {
    reg.registerVar("con.Level", "",  "S", "", &level,  1.0, 0.5, 5.0, 0.5);
    presence_level::register_params(reg);
    return 0;
}

int ContrastConvolver::activate(bool start, PluginDef *p) {
    if (start) {
	if (!static_cast<ContrastConvolver*>(p)->conv_start()) {
	    return -1;
	}
    } else {
	static_cast<ContrastConvolver*>(p)->conv_stop();
    }
    return 0;
}

static gboolean contrast_error_message(gpointer data) {
    gx_system::gx_print_error("Convolver", "presence overload");
    return false;
}

// wraper for the presence function
void ContrastConvolver::run_contrast(int count, float *input0, float *output0) {
    compensate_con(count, output0, output0);
    if (!conv.compute(count, output0)) {
        g_idle_add(contrast_error_message, gpointer(NULL));
        sum = no_sum;
    }
}

} // namespace gx_engine
