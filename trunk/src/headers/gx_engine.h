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

#ifndef SRC_HEADERS_GX_ENGINE_H_
#define SRC_HEADERS_GX_ENGINE_H_

#include <string>
#include <set>
#include <errno.h>
#include <glibmm/i18n.h>     // NOLINT

// --- defines the processing type
#define ZEROIZE_BUFFERS  (0)
#define JUSTCOPY_BUFFERS (1)
#define PROCESS_BUFFERS  (2)

namespace gx_engine {

/* -- guitarix main engine -- */
/* engine state : can be on or off or bypassed */
typedef enum {
    kEngineOff    = 0,
    kEngineOn     = 1,
    kEngineBypass = 2
} GxEngineState;

/****************************************************************/

class AudioVariables {
public:
    bool  initialized;  /* engine init state  */
    bool  buffers_ready;  /* buffer ready state */
    float fwarn;
    float fwarn_swap;
    float fskin;

    //FIXME:
    float filebutton;

    float fConsta1t;

    float* oversample;
    float* result;

    void register_parameter();
};

extern AudioVariables audio;

/****************************************************************/

class MidiVariables {
 public:
    float fslider45;
    float fslider38;
    float fslider31;
    float fslider27;
    float fslider29;
    float fslider30;
    float fslider26;
    float fslider33;
    float fslider34;
    float fslider35;
    float fslider36;
    float fslider42;
    float fslider43;
    float fslider40;
    float fslider41;
    float fslider44;
    float fslider37;
    float fslider39;
    float fslider46;
    float fslider47;
    float fslider48;
    float fConsta4;
    float fConstlog;
    float fConstlog2;
    float beat0;
    float midi_gain;
    float fConstun0;
    float fautogain;
    bool fpitch;
    float fslider32;
    float fautogain1;
    bool fpitch1;
    bool fpitch2;
    float fautogain2;
    float BeatFilter1;
    float BeatFilter2;
    float BeatFilterk;
    bool midistat;
    bool  midistat1;
    bool  midistat2;
    bool  midistat3;

    int   weg;
    int   program;
    int   program2;
    int   volume2;
    int   Beat_is;
    int   send;
    int   volume;
    int   noten;
    int   program1;
    int   send1;
    int   noten1;
    int   volume1;
    int   send2;
    int   noten2;

    bool  fcheckbox10;
    bool  fcheckbox11;

    unsigned char* midi_send;
    unsigned char* midi_send1;
    unsigned char* midi_send2;

    void register_parameter();
    void init(int samplingFreq);
};

extern MidiVariables midi;


/****************************************************************
 ** class ProcessingChainBase
 ** members and methods accessed by the rt thread are marked RT
 */

class ProcessingChainBase {
public:
    enum RampMode { ramp_mode_down_dead, ramp_mode_down, ramp_mode_up_dead, ramp_mode_up, ramp_mode_off };
private:
    sem_t sync_sem; // RT
    list<Plugin*> to_release;
    int ramp_value; // RT
    RampMode ramp_mode; // RT
    bool stopped;
protected:
    int steps_up;		// RT; >= 1
    int steps_up_dead;		// RT; >= 0
    int steps_down;		// RT; >= 1
    volatile bool latch; // RT; set between commit and end of rt cycle
    list<Plugin*> modules;
    inline void set_ramp_value(int n) { g_atomic_int_set(&ramp_value, n); } // RT
    inline void set_ramp_mode(RampMode n) { g_atomic_int_set(&ramp_mode, n); } // RT
    void try_set_ramp_mode(RampMode oldmode, RampMode newmode, int oldrv, int newrv); // RT
public:
    bool next_commit_needs_ramp;
    ProcessingChainBase();
    inline RampMode get_ramp_mode() {
      return static_cast<RampMode>(g_atomic_int_get(&ramp_mode)); // RT
    }
    inline int get_ramp_value() { return g_atomic_int_get(&ramp_value); } // RT
    void set_samplefreq(int samplefreq);
    bool set_plugin_list(const list<Plugin*> &p);
    void clear_module_states();
    void post_rt_finished() { // RT
	int val;
	latch = false;
	if (sem_getvalue(&sync_sem, &val) == 0 && val == 0) {
	    sem_post(&sync_sem);
	}
    }
    void wait_rt_finished() {
	if (stopped) {
	    return;
	}
	while (sem_wait(&sync_sem) == EINTR);
    }
    inline void wait_latch() {
	if (latch) {
	    wait_rt_finished();
	}
    }
    inline bool check_release() {
	return !to_release.empty();
    }
    void release();
    void wait_ramp_down_finished() {
	if (stopped) {
	    return;
	}
	while (ramp_mode == ramp_mode_down) {
	    wait_rt_finished();
	}
    }
    inline void start_ramp_up() { set_ramp_value(0); set_ramp_mode(ramp_mode_up_dead); }
    inline void start_ramp_down() { set_ramp_value(steps_down); set_ramp_mode(ramp_mode_down); }
    inline void set_down_dead() { set_ramp_mode(ramp_mode_down_dead); }
    inline void set_stopped(bool v) { stopped = v; }
};


/****************************************************************
 ** template class ThreadSafeChainPointer
 ** members and methods accessed by the rt thread are marked RT
 */

template <class F>
class ThreadSafeChainPointer: public ProcessingChainBase {
private:
    F *rack_order_ptr[2]; // RT
    int size[2];
    int current_index;
    F *current_pointer;
    void setsize(int n);
    F get_audio(PluginDef *p);
protected:
    F *processing_pointer; // RT
    inline F* get_rt_chain() { return reinterpret_cast<F*>(g_atomic_pointer_get(&processing_pointer)); } // RT
public:
    ThreadSafeChainPointer();
    ~ThreadSafeChainPointer();
    inline void empty_chain() {
	list<Plugin*> p;
	if (set_plugin_list(p)) {
	    commit(true);
	}
    }
    void commit(bool clear);
};

template <class F>
ThreadSafeChainPointer<F>::ThreadSafeChainPointer():
    rack_order_ptr(),
    size(),
    current_index(0),
    current_pointer(),
    processing_pointer() {
    setsize(1);
    current_pointer[0] = 0;
    processing_pointer = current_pointer;
    current_index = 1;
    current_pointer = rack_order_ptr[1];
}

template <class F>
ThreadSafeChainPointer<F>::~ThreadSafeChainPointer() {
    delete rack_order_ptr[0];
    delete rack_order_ptr[1];
}

template <class F>
void ThreadSafeChainPointer<F>::setsize(int n)
{
    if (n <= size[current_index]) {
	return;
    }
    delete rack_order_ptr[current_index];
    rack_order_ptr[current_index] = new F[n];
    size[current_index] = n;
    current_pointer = rack_order_ptr[current_index];
}

template <class F>
void ThreadSafeChainPointer<F>::commit(bool clear) {
    setsize(modules.size()+1);  // leave one slot for 0 marker
    int active_counter = 0;
    for (list<Plugin*>::const_iterator p = modules.begin(); p != modules.end(); p++) {
	PluginDef* pd = (*p)->pdef;
	if (pd->activate_plugin) {
	    pd->activate_plugin(true, pd);
	} else if (pd->clear_state && clear) {
	    pd->clear_state(pd);
	}
	F f = get_audio(pd);
	assert(f);
	current_pointer[active_counter++] = f;
    }
    current_pointer[active_counter] = 0;
    g_atomic_pointer_set(&processing_pointer, current_pointer);
    latch = true;
    current_index = (current_index+1) % 2;
    current_pointer = rack_order_ptr[current_index];
}

typedef void (*monochainorder)(int count, float *output, float *output1);
typedef void (*stereochainorder)(int count, float* input, float* input1,
				 float *output, float *output1);

template <>
inline monochainorder ThreadSafeChainPointer<monochainorder>::get_audio(PluginDef *p)
{
    return p->mono_audio;
}

template <>
inline stereochainorder ThreadSafeChainPointer<stereochainorder>::get_audio(PluginDef *p)
{
    return p->stereo_audio;
}

/****************************************************************
 ** class MonoModuleChain, class StereoModuleChain
 */

class MonoModuleChain: public ThreadSafeChainPointer<monochainorder> {
public:
    MonoModuleChain(): ThreadSafeChainPointer<monochainorder>() {}
    void process(int count, float *input, float *output);
    inline void print() { printlist("Mono", modules); }
};

class StereoModuleChain: public ThreadSafeChainPointer<stereochainorder> {
public:
    StereoModuleChain(): ThreadSafeChainPointer<stereochainorder>() {}
    void process(int count, float *input, float *output1, float *output2);
    inline void print() { printlist("Stereo", modules); }
};


/****************************************************************
 ** classes ModuleSelector
 */

class ModuleSelectorFromList: public ModuleSelector, private PluginDef {
private:
    unsigned int selector;
    const char* select_id;
    const char* select_name;
    Plugin* current_plugin;
    PluginDef **modules;
    unsigned int size;
    static int static_register(const ParamReg& reg);
    int register_parameter(const ParamReg& reg);
public:
    Plugin plugin;
    ModuleSelectorFromList(
	const char* id, const char* name, PluginDef **module_ids,
	const char* select_id, const char* select_name,
	const char** groups = 0, int flags = 0);
    void set_module();
    void set_selector(unsigned int n);
    unsigned int get_selector() { return selector; }
};


/****************************************************************
 ** class ModuleSequencer
 */

class ModuleSequencer {
protected:
    list<ModuleSelector*> selectors;
    PluginList& pluginlist;
    bool rack_changed;
    int audio_mode;
public:
    MonoModuleChain mono_chain;
    StereoModuleChain stereo_chain;
public:
    ModuleSequencer(PluginList& pl);
    ~ModuleSequencer();
    void set_samplefreq(int samplefreq);
    void clear_module_states() {
	mono_chain.clear_module_states();
	stereo_chain.clear_module_states();
    }
    void start_ramp_up() {
	mono_chain.start_ramp_up();
	stereo_chain.start_ramp_up();
    }
    void start_ramp_down() {
	mono_chain.start_ramp_down();
	stereo_chain.start_ramp_down();
    }
    void wait_ramp_down_finished() {
	mono_chain.wait_ramp_down_finished();
	stereo_chain.wait_ramp_down_finished();
    }
    void ramp_down() {
	start_ramp_down();
	wait_ramp_down_finished();
    }
    void set_down_dead() {
	mono_chain.set_down_dead();
	stereo_chain.set_down_dead();
    }
    void add_selector(ModuleSelector& sel);
    bool prepare_module_lists();
    void commit_module_lists();
    void set_rack_changed() { rack_changed = true; }
    void clear_rack_changed() { rack_changed = false; }
    bool update_module_lists() {
	if (prepare_module_lists()) {
	    commit_module_lists();
	    return true;
	}
	return false;
    }
    inline void check_module_lists() {
	if (mono_chain.check_release()) {
	    mono_chain.release();
	}
	if (stereo_chain.check_release()) {
	    stereo_chain.release();
	}
	if (rack_changed) {
	    update_module_lists();
	}
    }
};


/****************************************************************
 ** class GxEngine
 */

class GxEngine: public ModuleSequencer {
private:
    gx_ui::GxUI ui;
    int stateflags;
public:
    enum StateFlag {
	SF_NO_CONNECTION = 0x01,
	SF_JACK_RECONFIG = 0x02,
    };
    NoiseGate noisegate;
    MonoMute monomute;
    StereoMute stereomute;
    MidiAudioBuffer midiaudiobuffer;
    TunerAdapter tuner;
    MaxLevel maxlevel;
    OscilloscopeAdapter oscilloscope;
    ConvolverAdapter convolver;
    CabinetConvolver cabinet;
    ContrastConvolver contrast;
public:
    GxEngine(PluginList& pl);
    ~GxEngine();
    void set_stateflag(StateFlag flag);
    void clear_stateflag(StateFlag flag);
    void set_state(GxEngineState state);
    GxEngineState get_state();
    void load_plugins(string plugin_dir);
};

GxEngine& get_engine();

/****************************************************************/

// wrap the state of the latency change warning (dis/enable) to
// the interface settings to load and save it
inline void set_latency_warning_change()   {audio.fwarn_swap = audio.fwarn;}
inline void get_latency_warning_change()   {audio.fwarn = audio.fwarn_swap;}

inline bool isInitialized()                {return audio.initialized;}

/****************************************************************/

/* function declarations  */

void gx_engine_init(const string *optvar);
void gx_engine_reset();

void compute_midi_in(void* midi_input_port_buf);
void process_midi(int count, float *input);

void load_plugins(string plugin_dir);

/* ------------------------------------------------------------------- */
} /* end of gx_engine namespace */
#endif  // SRC_HEADERS_GX_ENGINE_H_

