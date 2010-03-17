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

#include <array>
#include <zita-convolver.h>
#include <fftw3.h>
#include <zita-resampler.h>

// --- defines the processing type
#define ZEROIZE_BUFFERS  (0)
#define JUSTCOPY_BUFFERS (1)
#define PROCESS_BUFFERS  (2)

namespace gx_engine
{

/* GxConvolver */

class Audiofile
{
public:

	enum {
		TYPE_OTHER,
		TYPE_CAF,
		TYPE_WAV,
		TYPE_AMB
	};

	enum {
		FORM_OTHER,
		FORM_16BIT,
		FORM_24BIT,
		FORM_32BIT,
		FORM_FLOAT
	};

	enum {
		ERR_NONE    = 0,
		ERR_MODE    = -1,
		ERR_TYPE    = -2,
		ERR_FORM    = -3,
		ERR_OPEN    = -4,
		ERR_SEEK    = -5,
		ERR_DATA    = -6,
		ERR_READ    = -7,
		ERR_WRITE   = -8
	};

	Audiofile (void);
	~Audiofile (void);

	//int mode(void) const { return _mode; }
	int type(void) const { return _type; }
	//int form(void) const { return _form; }
	int rate(void) const { return _rate; }
	int chan(void) const { return _chan; }
	uint32_t size(void) const { return _size; }

	int open_read (string name);
	int close (void);

	int seek(uint32_t posit);
	int read(float *data, uint32_t frames);

private:

	void reset(void);

	SNDFILE  *_sndfile;
	int       _mode;
	int       _type;
	int       _form;
	int       _rate;
	int       _chan;
	uint32_t  _size;
};

class GxConvolver: Convproc
{
private:
	bool ready;
	bool read_sndfile (Audiofile& audio, int nchan, const float *gain, unsigned int *delay,
	                   unsigned int offset, unsigned int length);
	void adjust_values(unsigned int audio_size, unsigned int& count, unsigned int& offset,
	                   unsigned int& delay, unsigned int& ldelay, unsigned int& length,
	                   unsigned int& size, unsigned int& bufsize);
public:
	GxConvolver(): ready(false) {}
	bool configure(
		unsigned int count, int samplerate, string fname, float gain=1.0, float lgain=1.0,
		unsigned int delay=0, unsigned int ldelay=0, unsigned int offset=0,
		unsigned int length=0, unsigned int size=0, unsigned int bufsize=0);
	bool compute(int count, float* input1, float *input2, float *output1, float *output2);
	void checkstate();
	bool is_runnable() { return ready; }
	bool start();
	void stop() { stop_process(); }
};

extern GxConvolver conv;

/* ------------- Pitch Tracker ------------- */

const int MAX_FFT_SIZE = 512; // The size of the read buffer (max FFT window size).

class PitchTracker
{
public:
	PitchTracker();
	~PitchTracker();
	bool setParameters( int sampleRate, int fftSize );
	void init() { setParameters((int)gx_jack::jack_sr, MAX_FFT_SIZE); }
	void add(int count, float *input);
	float tuner_estimate();

private:
	void run();
	static void *static_run(void*);
	void setEstimatedFrequency(float freq);
	int find_minimum();
	int find_maximum(int l);
	void start_thread();
	void copy();
	bool error;
	volatile bool busy;
	int tick;
    sem_t m_trig;
    pthread_t m_pthr;
	Resampler resamp;
	int m_sampleRate;
	int	m_fftSize; // Size of the FFT window.
	float *m_buffer; // The audio buffer that stores the input signal.
	int m_bufferIndex; // Index of the first empty position in the buffer.
	bool m_audioLevel; // Whether or not the input level is high enough.
	float *m_fftwBufferTime; // Support buffer used to store signals in the time domain.
	fftwf_complex *m_fftwBufferFreq; // Support buffer used to store signals in the frequency domain.
	fftwf_plan m_fftwPlanFFT; // Plan to compute the FFT of a given signal.
	fftwf_plan m_fftwPlanIFFT; // Plan to compute the IFFT of a given signal (with additional zero-padding).
};

extern PitchTracker pitch_tracker;


/* -- guitarix main engine -- */

// variables
extern GxMidiState midistate;
extern float fConsta1;
extern int fnoise_g;
extern int fng;
extern float fnglevel;
extern int fcheckbox1;
extern int fupsample;
extern int antialis0;
extern int ftube;
extern int ftube3;
extern int fprdr;
extern int fconvolve;
extern float convolvefilter;
extern int fresoon;
extern float posit0;
extern int fcheckbox5;
extern int fautowah;
extern int fcheckboxcom1;
extern float posit1;
extern float posit2;
extern float posit3;
extern float posit4;
extern float posit5;
extern float posit6;
extern float posit7;
extern float posit8;
extern int foverdrive4;
extern int fcheckbox4;
extern int fcheckbox6;
extern int fcheckbox7;
extern int fcheckbox8;
extern int fdelay;
extern int fmultifilter;
extern int   fboost;
extern int fchorus;
extern float ffuse;
extern float fdialogbox1;
extern float fdialogbox2;
extern float fdialogbox3;
extern float fdialogbox4;
//extern float fdialogbox5;
extern float fdialogbox6;
extern float fdialogbox8;
extern float fdialogboxj;
extern float fexpand;
extern float fexpand2;
extern float fwarn;
extern float fwarn_swap;
extern float fskin;
extern float viv;
extern float vivi;
extern float fchorusbox;
extern float filebutton;
extern float fConsta1t;
extern float midistat;


// MIDI variables

extern float fslider45;
extern float fslider38;
extern float fslider31;
extern float fslider27;
extern float fslider29;
extern float fslider30;
extern float fslider26;
extern float fslider33;
extern float fslider34;
extern float fslider35;
extern float fslider36;
extern float fslider42;
extern float fslider43;
extern float fslider40;
extern float fslider41;
extern float fslider44;
extern float fslider37;
extern float fslider39;
extern float fslider46;
extern float fslider47;
extern float fslider48;
extern float fConsta4;
extern float fConstlog;
extern float fConstlog2;
extern float beat0;
extern float midi_gain;
extern float fConstun0;
extern int   weg;
extern int   program;
extern unsigned char* midi_send;
extern int   send;
extern float fautogain;
extern int   volume;
extern float fpitch;
extern int   noten;
extern float fslider32;
extern float cache_note;
extern int fcheckbox10;
extern int   program1;
extern int   send1;
extern int   noten1;
extern float fautogain1;
extern int   volume1;
extern unsigned char* midi_send1;
extern int   send2;
extern int   noten2;
extern float fpitch1;
extern float fpitch2;
extern int fcheckbox11;
extern int   program2;
extern int   volume2;
extern int Beat_is;
extern unsigned char* midi_send2;
extern float fautogain2;


/* square function */
inline double sqrf(float x) { return x * x; }

// wrap the state of the latency change warning (dis/enable) to
// the interface settings to load and save it
inline void set_latency_warning_change() { fwarn_swap = fwarn; }
inline void get_latency_warning_change() { fwarn = fwarn_swap; }

inline bool isMidiOn() { return (midistate == kMidiOn ? true : false); }
inline void turnOffMidi() { midistate = kMidiOff; }
inline void turnOnMidi() { midistate = kMidiOn; }

/* function declarations  */
void gx_engine_init();
void gx_engine_reset();
void faust_init(int samplingFreq);
void initMidi(int samplingFreq);
void compute_midi(int len);
void compute_midi_in(void* midi_input_port_buf);
void process_midi(int count);
void compute (int count, float* input, float* output0, float* output1);

void convolver_filter(float* input, float* output, int sf, int iconvolvefilter);
void moving_filter(float* input, float* output, int sf);
void process_buffers(int count, float* input, float* output0, float* output1);


/* ------------------------------------------------------------------- */
} /* end of gx_engine namespace */
