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
 ** class MidiAudioBuffer
 */

static const char *midi_out_groups[] = {
	"channel_1", N_("Midi Out 1"), 
	"channel_2", N_("Midi Out 2"),
	"channel_3", N_("Midi Out 3"),
	".beat_detector",      N_("Beat Detector"),
	0
    };

MidiAudioBuffer::MidiAudioBuffer(TunerAdapter& t)
    : PluginDef(),
      midi(),
      tuner(t),
      jack(0),
      jack_overload(load_off),
      overload_change(),
      plugin() {
    version = PLUGINDEF_VERSION;
    flags = PGN_SNOOP;
    id = "midi_out";
    name = N_("Midi Out");
    groups = midi_out_groups;
    mono_audio = fill_buffer;
    set_samplerate = init;
    activate_plugin = activate;
    register_params = regparam;
    plugin.pdef = this;
}

int MidiAudioBuffer::activate(bool start, PluginDef *plugin) {
    MidiAudioBuffer& self = *static_cast<MidiAudioBuffer*>(plugin);
    self.jack_overload = start ? load_normal : load_off;
    self.overload_change();
    return 0;
}

void MidiAudioBuffer::fill_buffer(int count, float *input, float*,
				  PluginDef *plugin) {
    MidiAudioBuffer& self = *static_cast<MidiAudioBuffer*>(plugin);
    if (!self.jack) {
	return;
    }
    void *buf = self.jack->get_midi_buffer(count);
    if (buf) {
	float load = self.jack->get_jcpu_load();
	Load ol = (load < 65.0 ? load_normal : load_over);
	if (self.jack_overload != ol) {
	    self.jack_overload = ol;
	    self.overload_change();
	}
	self.midi.process_midi(count, input, buf, load,
			       self.tuner.get_freq(), self.tuner.get_note());
    }
}

void MidiAudioBuffer::init(unsigned int samplingFreq, PluginDef *plugin) {
    MidiAudioBuffer& self = *static_cast<MidiAudioBuffer*>(plugin);
    self.midi.init(samplingFreq);
}

int MidiAudioBuffer::regparam(const ParamReg& reg) {
    MidiAudioBuffer& self = *static_cast<MidiAudioBuffer*>(reg.plugin);
    self.midi.register_parameter(reg);
    return 0;
}

} // namespace gx_engine
