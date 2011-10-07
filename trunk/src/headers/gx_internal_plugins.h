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
 */

/* ------- This is the guitarix Engine namespace ------- */

#pragma once

namespace gx_engine {

/****************************************************************
 ** MonoMute, StereoMute, MaxLevel, MidiAudioBuffer
 */

class MonoMute: public PluginDef {
private:
    static void process(int count, float *input, float *output);
public:
    MonoMute();
};

class StereoMute: public PluginDef {
private:
    static void process(int count, float *input0, float *input1,
			float *output0, float *output1);
public:
    StereoMute();
};

class MaxLevel: public PluginDef {
private:
    static float maxlevel[2];
    static void process(int count, float *input0, float *input1,
			float *output0, float *output1);
    static int activate(bool start, PluginDef *plugin);
public:
    static float get(unsigned int channel) {
	assert(channel < 2); return maxlevel[channel];
    }
    static void reset() {
	maxlevel[0] = maxlevel[1] = 0;
    }
    MaxLevel();
};

class MidiAudioBuffer: PluginDef {
private:
    static void fill_buffer(int count, float *input0, float *output0);
public:
    Plugin plugin;
    MidiAudioBuffer();
};

/****************************************************************
 ** class TunerAdapter
 */

class TunerAdapter: public ModuleSelector, private PluginDef {
private:
    static void feed_tuner(int count, float *input, float *output);
    static int regparam(const ParamReg& reg);
    int state;
    enum { tuner_use = 0x01, midi_use = 0x02 };
    void set_and_check(int use, bool on);
    const Plugin& dep_plugin;
public:
    Plugin plugin;
    TunerAdapter(const Plugin& pl);
    void used_for_display(bool on) { set_and_check(tuner_use, on); }
    void used_by_midi(bool on) { set_and_check(midi_use, on); }
    void set_module();
};

/****************************************************************
 ** class NoiseGate
 */

class NoiseGate {
private:
    static PluginDef inputdef;
    static float fnglevel;
    static float ngate;
    static bool off;
    static int noisegate_register(const ParamReg& reg);
    static void inputlevel_compute(int count, float *input0, float *output0);
    static void outputgate_compute(int count, float *input, float *output);
    static int outputgate_activate(bool start, PluginDef *pdef);
public:
    static Plugin inputlevel;
    static PluginDef outputgate;
    NoiseGate();
};

/****************************************************************
 ** class OscilloscopeAdapter
 */

class OscilloscopeAdapter: PluginDef {
private:
    static float*& buffer;
    static void fill_buffer(int count, float *input0, float *output0);
    static int activate(bool start, PluginDef *p);
public:
    Plugin plugin;
    sigc::signal<int, bool> activation;
    gx_ui::UiSignalUInt     post_pre_signal;
    void clear_buffer();
    OscilloscopeAdapter(gx_ui::GxUI *ui);
};


/****************************************************************
 ** class ConvolverAdapter
 */

class ConvolverAdapter: PluginDef {
public:
    Plugin plugin;
    static GxConvolver conv;
private:
    // wrapper for the rack order function pointers
    static void convolver(int count, float *input0, float *input1,
			  float *output0, float *output1);
    static int activate(bool start, PluginDef *pdef);
    static int convolver_register(const ParamReg& reg);
    static void convolver_init(int samplingFreq, PluginDef *pdef);
public:
    sigc::signal<int, bool> activation;
    ConvolverAdapter(gx_ui::GxUI *ui);
};

/****************************************************************
 ** class CabinetConvolver
 */

class CabinetConvolver: PluginDef {
private:
    static GxSimpleConvolver conv;
    static int current_cab;
    static float level;
    int cabinet;
    float bass;
    float treble;
    float sum;
    value_pair *cab_names;
    static inline void compensate_cab(int count, float *input0, float *output0);
    static void run_cab_conf(int count, float *input, float *output);
    static int activate(bool start, PluginDef *pdef);
    static int register_cab(const ParamReg& reg);
    bool update();
public:
    Plugin plugin;
    CabinetConvolver(gx_ui::GxUI *ui);
    ~CabinetConvolver();
    inline bool is_runnable() { return conv.is_runnable(); }
    inline void set_not_runnable() { conv.set_not_runnable(); }
    inline void conv_stop() { conv.stop(); }
    bool conv_start();
    bool cabinet_changed() { return current_cab != cabinet; }
    void update_cabinet() { current_cab = cabinet; }
    bool sum_changed() { return abs(sum - (level + bass + treble + gx_jack::gxjack.jack_bs)) > 0.01; }
    void update_sum() { sum = level + bass + treble + gx_jack::gxjack.jack_bs; }
    bool conv_update();
};

/****************************************************************
 ** class ContrastConvolver
 */

class ContrastConvolver: PluginDef {
private:
    static GxSimpleConvolver conv;
    static float level;
    static float sum;
    // wrapper for the rack order function pointers
    static inline void compensate_con(int count, float *input0, float *output0);
    static void run_contrast(int count, float *input, float *output);
    static int activate(bool start, PluginDef *pdef);
    static int register_con(const ParamReg& reg);
public:
    Plugin plugin;
    ContrastConvolver(gx_ui::GxUI *ui);
    inline bool is_runnable() { return conv.is_runnable(); }
    inline void set_not_runnable() { conv.set_not_runnable(); }
    inline bool sum_changed() { return abs(sum - (level + gx_jack::gxjack.jack_bs)) > 0.01; }
    inline void update_sum() { sum = level + gx_jack::gxjack.jack_bs; }
    bool conv_start();
    void conv_stop() { conv.stop(); }
};

} // namespace gx_engine
