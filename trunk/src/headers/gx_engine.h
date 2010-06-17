/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 */

/* ------- This is the guitarix Engine namespace ------- */

#pragma once

// --- defines the processing type
#define ZEROIZE_BUFFERS  (0)
#define JUSTCOPY_BUFFERS (1)
#define PROCESS_BUFFERS  (2)

namespace gx_engine
{


/* -- guitarix main engine -- */

class AudioVariables
{
public:
	GxMidiState midistate;
	int fnoise_g;
	int fng;
	float fnglevel;
	int fcheckbox1;
	int fupsample;
	int antialis0;
	int ftube;
	int ftube3;
	int fprdr;
	int fconvolve;
	float convolvefilter;
	int fresoon;
	float posit0;
	int fcheckbox5;
	float fautowah;
	int fcheckboxcom1;
	float posit1;
	float posit2;
	float posit3;
	float posit4;
	float posit5;
	float posit6;
	float posit7;
	float posit8;
	float posit9;
	int foverdrive4;
	int fcheckbox4;
	int fcheckbox6;
	int fcheckbox7;
	int fcheckbox8;
	int fdelay;
	int fmultifilter;
	int fboost;
	int fchorus;
	float ffuse;
	float fdialogbox1;
	float fdialogbox2;
	float fdialogbox3;
	float fdialogbox4;
//float fdialogbox5;
	float fdialogbox6;
	float fdialogbox8;
	float fdialogboxj;
	float fexpand;
	float fexpand2;
	float fwarn;
	float fwarn_swap;
	float fskin;
	float viv;
	float vivi;
	float fchorusbox;
	float filebutton;
	float fConsta1t;
	float midistat;
	int feq;
	float fdialogbox_eq;
	float fdialogbox_mbf;
	float fdialogbox_moo;
	int fmoog;
	int fflanger;
	float fflangerbox;
	int fbiquad;
	float fbiquadbox;
	int ftube3e;
	float upsample_mode;
	float fampexpand;
	int fsloop;
	float witchdistortion;
	float fdis1;
	int fcab;
	float fdialogbox_echo;
	float fdialogbox_delay;

	AudioVariables();
};

extern AudioVariables audio;


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
	int   weg;
	int   program;
	unsigned char* midi_send;
	int   send;
	float fautogain;
	int   volume;
	float fpitch;
	int   noten;
	float fslider32;
	int fcheckbox10;
	int   program1;
	int   send1;
	int   noten1;
	float fautogain1;
	int   volume1;
	unsigned char* midi_send1;
	int   send2;
	int   noten2;
	float fpitch1;
	float fpitch2;
	int fcheckbox11;
	int   program2;
	int   volume2;
	int Beat_is;
	unsigned char* midi_send2;
	float fautogain2;
	float BeatFilter1;
	float BeatFilter2;
	float BeatFilterk;

	MidiVariables();
	void init(int samplingFreq);
};

extern MidiVariables midi;


/* square function */
inline double sqrf(float x) { return x * x; }

// wrap the state of the latency change warning (dis/enable) to
// the interface settings to load and save it
inline void set_latency_warning_change() { audio.fwarn_swap = audio.fwarn; }
inline void get_latency_warning_change() { audio.fwarn = audio.fwarn_swap; }

inline bool isMidiOn() { return (audio.midistate == kMidiOn ? true : false); }
inline void turnOffMidi() { audio.midistate = kMidiOff; }
inline void turnOnMidi() { audio.midistate = kMidiOn; }

/* function declarations  */
void gx_engine_init( const std::string *optvar );
void gx_engine_reset();
void faust_init(int samplingFreq);
void compute_midi(int len);
void compute_midi_in(void* midi_input_port_buf);
void process_midi(int count);
void compute (int count, float* input, float* output0);
void compute_insert (int count, float* input1, float* output2, float* output3);

void convolver_filter(float* input, float* output, int sf, int iconvolvefilter);
void moving_filter(float* input, float* output, int sf);
void process_buffers(int count, float* input, float* output0);
void process_insert_buffers (int count, float* input1, float* output0, float* output1);

#ifdef EXPERIMENTAL
void faust_setup();
void toggle_exp_window(bool v);
#endif

/* ------------------------------------------------------------------- */
} /* end of gx_engine namespace */
