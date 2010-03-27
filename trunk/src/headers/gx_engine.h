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

class AudioVariables
{
public:
	GxMidiState midistate;
	float fConsta1;
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
	int fautowah;
	int fcheckboxcom1;
	float posit1;
	float posit2;
	float posit3;
	float posit4;
	float posit5;
	float posit6;
	float posit7;
	float posit8;
	int foverdrive4;
	int fcheckbox4;
	int fcheckbox6;
	int fcheckbox7;
	int fcheckbox8;
	int fdelay;
	int fmultifilter;
	int   fboost;
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
	float cache_note;
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
void gx_engine_init();
void gx_engine_reset();
void faust_init(int samplingFreq);
void compute_midi(int len);
void compute_midi_in(void* midi_input_port_buf);
void process_midi(int count);
void compute (int count, float* input, float* output0, float* output1);

void convolver_filter(float* input, float* output, int sf, int iconvolvefilter);
void moving_filter(float* input, float* output, int sf);
void process_buffers(int count, float* input, float* output0, float* output1);


/* ------------------------------------------------------------------- */
} /* end of gx_engine namespace */
