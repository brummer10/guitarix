/* abGate - LV2 Noise Gate Plugin
 *
 * Copyright 2011 Antanas Bružas
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "gx_plugin.h"
#include <cmath>

namespace pluginlib {
namespace abgate {

#define N_(x) (x)

#define CLOSED 1
#define ATTACK 2
#define OPENED 3
#define DECAY 4

class Gate: public PluginDef {
private:
    int state;
    int holding;
    float gate;
    float sample_rate;
    //
    float threshold, attack, hold, decay, range;
public:
    Gate();
    static void init(unsigned int samplingFreq, PluginDef *plugin);
    static void process(int count, float *input, float *output, PluginDef *plugin);
    static int registerparam(const ParamReg& reg);
    static void del_instance(PluginDef *plugin);
    static int load_ui_f_static(const UiBuilder& b, int form);
    int load_ui_f(const UiBuilder& b, int form);
    static const char *glade_def;
};

Gate::Gate():
    PluginDef(),
    state(CLOSED),
    holding(0),
    gate(0),
    sample_rate(0) {
    version = PLUGINDEF_VERSION;
    id = "abgate";
    name = N_("abGate");
    category = N_("Misc");
    mono_audio = process;
    set_samplerate = init;
    register_params = registerparam;
    load_ui = load_ui_f_static;
    delete_instance = del_instance;
}

int Gate::registerparam(const ParamReg& reg) {
    Gate& self = *static_cast<Gate*>(reg.plugin);
    reg.registerVar("abgate.threshold", N_("Threshold"), "S", N_("threshold (dB) value\nput it just above the noise level"), &self.threshold, -70, -70, 12, 1);
    reg.registerVar("abgate.attack", N_("Attack"), "S", N_("time (ms) until gate opens (sensitivity)"), &self.attack, 4, 0.1, 500, 0.1);
    reg.registerVar("abgate.hold", N_("Hold"), "S", N_("time (ms) to keep open when input is below threshold"), &self.hold, 5, 5, 3000, 0.1);
    reg.registerVar("abgate.decay", N_("Decay"), "S", "duration (ms) of shutting gate down", &self.decay, 50, 5, 4000, 0.1);
    reg.registerVar("abgate.gaterange", N_("Range"), "S", N_("damping (dB) when the gate is closed"), &self.range, -30, -90, -20, 1);
    return 0;
}

void Gate::init(unsigned int samplingFreq, PluginDef *plugin) {
    static_cast<Gate*>(plugin)->sample_rate = samplingFreq;
}

void Gate::process(int count, float *input, float *output, PluginDef *plugin) {
    Gate& self = *static_cast<Gate*>(plugin);
    float range_coef = self.range > -90 ? pow(10, self.range * 0.05) : 0;
    float attack_coef = 1000 / (self.attack * self.sample_rate);
    float decay_coef = 1000 / (self.decay * self.sample_rate);
    float thres = std::pow(10, self.threshold / 20);
    for (int i = 0; i < count; ++i) {
	float input_abs = std::abs(input[i]);
	switch (self.state){
	case CLOSED:
	    if (input_abs >= thres) {
		self.state = ATTACK;
	    }
	    break;
	case ATTACK:
	    // attacking :)
	    self.gate += attack_coef;
	    if (self.gate >= 1) {
		self.gate = 1;
		self.state = OPENED;
		self.holding = round(self.hold * self.sample_rate * 0.001);
	    }
	    break;
	case OPENED:
	    if (self.holding <= 0) {
		if (input_abs < thres) {
		    self.state = DECAY;
		}
	    }
	    else {
		self.holding--;
	    }
	    break;
	case DECAY:
	    self.gate -= decay_coef;
	    if (input_abs >= thres) {
		self.state = ATTACK;
	    } else if (self.gate <= 0) {
		self.gate = 0;
		self.state = CLOSED;
	    }
	    break;
	default:
	    self.state = CLOSED;
	}
	output[i] = input[i] * (range_coef * (1 - self.gate) + self.gate);
    }	
}

int Gate::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file("abgate_ui.glade");
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("abgate" "." p)
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("threshold"), N_("Threshold"));
b.closeBox();
b.openHorizontalBox("");
b.insertSpacer();
b.create_small_rackknobr(PARAM("threshold"), N_("Threshold"));
b.create_small_rackknob(PARAM("attack"), N_("Attack"));
b.create_small_rackknob(PARAM("hold"), N_("Hold"));
b.create_small_rackknob(PARAM("decay"),  N_("Decay"));
b.create_small_rackknob(PARAM("gaterange"),  N_("Range"));
b.insertSpacer();
b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Gate::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Gate*>(b.plugin)->load_ui_f(b, form);
}

void Gate::del_instance(PluginDef *p)
{
    delete static_cast<Gate*>(p);
}


#if true

PluginDef *plugin() {
    return new Gate;
}

#else

extern "C" __attribute__ ((visibility ("default"))) int
get_gx_plugin(unsigned int idx, PluginDef **pplugin)
{
    const int count = 1;
    if (!pplugin) {
	return count;
    }
    switch (idx) {
    case 0: *pplugin = new Gate; return count;
    default: *pplugin = 0; return -1;
    }
}

#endif

} // end namespace abgate
} // end namespace pluginlib
