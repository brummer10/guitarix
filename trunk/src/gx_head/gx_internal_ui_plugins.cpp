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


/****************************************************************
 ** class TunerAdapter
 */

TunerAdapter::TunerAdapter(ModuleSequencer& engine_)
    : ModuleSelector(engine_),
      PluginDef(),
      pitch_tracker(),
      state(),
      engine(engine_),
      dep_plugin(),
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
    used_by_midi(dep_plugin->on_off);
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
    engine.signal_buffersize_change().connect(
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

} // namespace gx_engine
