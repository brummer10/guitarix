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

// --- defines the processing type
#define ZEROIZE_BUFFERS  (0)
#define JUSTCOPY_BUFFERS (1)
#define PROCESS_BUFFERS  (2)

namespace gx_engine {

/* -- guitarix main engine -- */

/****************************************************************/

class AudioVariables {
 public:
    GxMidiState midistate;

    bool fnoise_g;
    bool fng;
    bool foverdrive4;
    bool fcheckbox4;
    bool fcheckbox5;
    bool fcheckbox6;
    bool fcheckbox8;
    bool ftube;
    bool fboost;
    bool fcheckboxcom1;
    bool midistat1;
    bool midistat2;
    bool midistat3;
    bool feq;
    bool fmoog;
    bool fflanger;
    bool fbiquad;
    bool fcab;
    bool fcon;
    bool flh;
    bool fmi;
    bool fwv;
    bool fwv_on;
    bool famp;
    bool fampout;
    bool ftone;
    bool ftremolo;
    bool fpm;
    bool fflanger_mono;
    bool ffeedback;
    bool ftonestack;
    bool rack_change;

    unsigned int effect_pre_post[20];
    unsigned int effect_buffer[6];

    int fcheckbox7;
    int fdelay;
    int fchorus;
    int fchorus_mono;
    int fphaser;
    int tonestack;
    int cur_tonestack;
    int cabinet;
    int cab_switched;
    int fsd;
    int fse;
    int gxtube;
    int cur_gxtube;
    int mono_plug_counter;
    int stereo_plug_counter;

    float posit[30];

    float fnglevel;
    float fautowah;
    float ffuse;
    float fwarn;
    float fwarn_swap;
    float fskin;
    float viv;
    float vivi;
    float filebutton;
    float fConsta1t;
    float midistat;
    float fampexpand;
    float cab_level;
    float cab_bass;
    float cab_treble;
    float cab_sum;

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
    float fpitch;
    float fslider32;
    float fautogain1;
    float fpitch1;
    float fpitch2;
    float fautogain2;
    float BeatFilter1;
    float BeatFilter2;
    float BeatFilterk;

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

    bool fcheckbox10;
    bool fcheckbox11;

    unsigned char* midi_send;
    unsigned char* midi_send1;
    unsigned char* midi_send2;

    void register_parameter();
    void init(int samplingFreq);
};

extern MidiVariables midi;

/****************************************************************/

/* square function */
inline double sqrf(float x) { return x * x; }

// wrap the state of the latency change warning (dis/enable) to
// the interface settings to load and save it
inline void set_latency_warning_change() { audio.fwarn_swap = audio.fwarn; }
inline void get_latency_warning_change() { audio.fwarn = audio.fwarn_swap; }

inline bool isMidiOn() { return (audio.midistate == kMidiOn ? true : false); }
inline void turnOffMidi() { audio.midistate = kMidiOff; }
inline void turnOnMidi() { audio.midistate = kMidiOn; }

inline void set_tube_model(int x) {audio.gxtube = x;}
inline void set_cab_mode(float x) {audio.cab_sum = x;}
inline void set_mono_plug_counter(int x) {audio.mono_plug_counter = x;}
inline void set_stereo_plug_counter(int x) {audio.stereo_plug_counter = x;}

/****************************************************************/

/* function declarations  */
void register_faust_parameters();
void gx_engine_init(const string *optvar);
void gx_engine_reset();
void faust_init(int samplingFreq);
void compute_midi(int len);
void compute_midi_in(void* midi_input_port_buf);
void process_midi(int count);
void compute(int count, float* input, float* output0);
void compute_insert(int count, float* input1, float* output2, float* output3);

void convolver_filter(float* input, float* output, int sf, int iconvolvefilter);
void moving_filter(float* input, float* output, int sf);
void process_buffers(int count, float* input, float* output0);
void process_insert_buffers(int count, float* input1, float* output0, float* output1);

void init_non_rt_processing();
void non_rt_processing(int count, float* input, float* output0);

extern void (*amp_ptr)(int count, float *output, float *output1);
extern void (*tonestack_ptr)(int count, float *output, float *output1);
gboolean gx_check_engine_state(gpointer args);

typedef void (*chainorder) (int count, float *output, float *output1);
typedef void (*stereochainorder) 
             (int count, float* input, float* input1, float *output, float *output1);

extern chainorder pre_rack_order_ptr[];
extern chainorder post_rack_order_ptr[];
extern stereochainorder stereo_rack_order_ptr[];
gboolean gx_reorder_rack(gpointer args);


/* ------------------------------------------------------------------- */
} /* end of gx_engine namespace */
#endif  // SRC_HEADERS_GX_ENGINE_H_

