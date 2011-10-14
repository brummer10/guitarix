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
#include <glibmm/i18n.h>     // NOLINT

namespace gx_jack { class GxJack; }

namespace gx_engine {

/* -- guitarix main engine -- */

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
 ** class ModuleSelectorFromList
 */

class ModuleSelectorFromList: public ModuleSelector, private PluginDef {
private:
    ModuleSequencer& seq;
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
	ModuleSequencer& seq, const char* id, const char* name,
	PluginDef **module_ids,	const char* select_id,
	const char* select_name, const char** groups = 0, int flags = 0);
    void set_module();
    void set_selector(unsigned int n);
    unsigned int get_selector() { return selector; }
};


/****************************************************************
 ** class GxEngine
 */

class GxEngine: public ModuleSequencer {
private:
    gx_ui::GxUI ui;
public:
    // internal audio modules
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
    GxEngine();
    ~GxEngine();
    void load_plugins(string plugin_dir);
    void set_jack(gx_jack::GxJack *jack) { midiaudiobuffer.set_jack(jack); }
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

/* ------------------------------------------------------------------- */
} /* end of gx_engine namespace */
#endif  // SRC_HEADERS_GX_ENGINE_H_

