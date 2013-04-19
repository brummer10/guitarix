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

#include "gx_pitch_tracker.h"

/****************************************************************
 ** class tuner
 */

class tuner: public PluginLV2, public sigc::trackable {
private:
    static void feed_tuner(int count, float *input, float *output, PluginLV2*);
    static int activate(bool start, PluginLV2 *plugin);
    static void init(unsigned int samplingFreq, PluginLV2 *plugin);
    void connect(uint32_t port,void* data);
	PitchTracker pitch_tracker;
    int state;
    enum { tuner_use = 0x01, livetuner_use = 0x02, switcher_use = 0x04, midi_use = 0x08 };
    void set_and_check(int use, bool on);
public:
    static void connect_static(uint32_t port,void* data, PluginLV2 *p);
    tuner();
    Glib::Dispatcher& signal_freq_changed() { return pitch_tracker.new_freq; }
    float get_freq() { return pitch_tracker.get_estimated_freq(); }
    float get_note() { return pitch_tracker.get_estimated_note(); }
    void set_threshold_level(float v) {pitch_tracker.set_threshold(v);}
    static void del_instance(PluginLV2 *p);
};

tuner::tuner()
    : PluginLV2(),
      trackable(),
      pitch_tracker(),
      state() {
    version = PLUGINLV2_VERSION;
    id = "tuner";
    name = "Rack Tuner";
    mono_audio = feed_tuner;
    set_samplerate = init;
    activate_plugin = activate;
    connect_ports = connect_static;
    delete_instance = del_instance;
}

void tuner::init(unsigned int samplingFreq, PluginLV2 *plugin) {
    tuner& self = *static_cast<tuner*>(plugin);
    int priority = 0, policy = 0;
#ifdef _POSIX_PRIORITY_SCHEDULING
    int priomax = sched_get_priority_max(SCHED_FIFO);
    if ((priomax/2.2) > 0) {
        priority = priomax/2.2;
        policy = SCHED_FIFO;
    }
#endif
    self.pitch_tracker.init(policy, priority, samplingFreq);
}

void tuner::set_and_check(int use, bool on) {
    if (on) {
	state |= use;
    } else {
	state &= ~use;
    }
    if (use == switcher_use) {
	pitch_tracker.set_fast_note_detection(on);
    }
}

int tuner::activate(bool start, PluginLV2 *plugin) {
    if (!start) {
	static_cast<tuner*>(plugin)->pitch_tracker.reset();
    }
    return 0;
}

void tuner::feed_tuner(int count, float* input, float*, PluginLV2* plugin) {
    tuner& self = *static_cast<tuner*>(plugin);
    self.pitch_tracker.add(count, input);
}


void tuner::connect(uint32_t port,void* data)
{
	
}

void tuner::connect_static(uint32_t port,void* data, PluginLV2 *p)
{
	static_cast<tuner*>(p)->connect(port, data);
}


PluginLV2 *plugin() {
	return new tuner();
}

void tuner::del_instance(PluginLV2 *p)
{
	delete static_cast<tuner*>(p);
}
