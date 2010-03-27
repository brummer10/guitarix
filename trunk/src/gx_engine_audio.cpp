/*
 * Copyright (C) 2009-2010 Hermann Meyer, James Warden, Andreas Degert
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
 *
 *
 *    This is the Guitarix Audio Engine
 *
 *
 * --------------------------------------------------------------------------
 */

#include <assert.h>
#include <cstring>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <array>
#include <zita-convolver.h>
#include <fftw3.h>
#include <zita-resampler.h>

#include <cassert>
#include <sigc++/sigc++.h>
#include <semaphore.h>

#include <cmath>
#include <gtk/gtk.h>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <sndfile.h>

using namespace std;

#include "guitarix.h"

namespace gx_engine {

// static convolution filters
static float filters[][45] = {

	// filter 0
	{0.0222473, 0.0253601, 0.0159607, 0.0184326, 0.0240784,
	 0.02771, 0.0483398, 0.0802917, 0.12915, 0.196259, 0.259521,
	 0.334656, 0.398376, 0.421448, 0.401306, 0.340759, 0.216827,
	 0.058197, -0.117432, -0.287354, -0.438507, -0.540161,
	 0.0583801, 0.0596924, 0.0499573, 0.0406799, 0.0445862,
	 0.0334473, 0.0296021, 0.022644, 0.0142212, 0.0027771,
	 -0.00805664, -0.0206909, -0.0270386, -0.0247498,
	 -0.0259399, -0.0132751, 0.216827, 0.058197, -0.117432,
	 -0.287354, -0.438507, -0.540161, -0.438507
	},

	// filter 1
	{0.19,0.15,0.12,0.05,-0.08,-0.15,-0.18,-0.12,-0.05,0.07,
	 0.12,0.16,0.14,0.11,0.05,0.01,0.04,0.12,0.14,0.08,0.02,
	 -0.01,0.8,0.19,0.15,0.12,0.05,-0.08,-0.15,-0.18,-0.12,
	 -0.05,0.07,0.12,0.16,0.14,0.11,0.05,0.01,0.04,0.12,0.14,
	 0.08,0.02,-0.01
	},

	// filter 2
	{0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,0.19265,
	 0.19265,0.19265,0.19265
	},

	// filter 3
	{-0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851,
	 -0.1111851,-0.1811851,-0.1811851,-0.1811851,-0.1811851
	},

	// filter 4
	{-0.0400391, 0.0591736, 0.0404663, 0.065155, 0.065094,
	 0.0524597, 0.0325012, -0.0254211, -0.0797119, -0.118561,
	 -0.192902, -0.1763, -0.169861, -0.0974426, 0.0567932,
	 0.207458, 0.468079, 0.637085, 0.786072, 0.911835, 0.868347,
	 0.873199, 0.720001, 0.598633, 0.416168, 0.24173, 0.0201416,
	 -0.177277, -0.397614, -0.538208, -0.64505, -0.582642,
	 -0.43161, -0.0495605, 0.361603, 0.724304, 0.981934, 0.953583,
	 0.770233, 0.515625, 0.21106, -0.0998535, -0.162781,
	 -0.171173, 0.042572
	},

	// filter 5
	{0.000610352, 0.00604248, 0.0153809, 0.0246277, 0.0340576,
	 0.0418701, 0.0494385, 0.059082, 0.069458, 0.0871277,
	 0.0636292, -0.0269165, -0.208862, -0.453522, -0.7146,
	 -0.915344, -0.999939, -0.938538, -0.752472, -0.494629,
	 -0.240662, -0.0461426, 0.0594788, 0.0810852, 0.0621643,
	 0.0324707, 0.00180054, -0.0244751, -0.0487061,
	 -0.0654602, -0.0780334, -0.0823669, -0.0776978, -0.0677185,
	 -0.0529175, -0.0342102, -0.0135803, 0.00839233, 0.0301208,
	 0.053833, 0.0252563, 0.0058252, 0.002138, 0.0012851, 0.0009252
	},

	// filter 6
	{-0.0573425, 0.0429382, 0.1698, 0.325623, 0.496429,
	 0.673615, 0.831726, 0.948944, 0.999939, 0.962616,
	 0.822021, 0.57666, 0.25769, -0.091156, -0.393341,
	 -0.568726, -0.545746, -0.315643, 0.052948, 0.422028,
	 0.634552, 0.612579, 0.383606, 0.0856323, -0.142151,
	 -0.233185, -0.185608, -0.0593262, 0.0916748, 0.228333,
	 0.302521, 0.295105, 0.226959, 0.130402, 0.0578308,
	 0.0231018, 0.0189514, 0.0299988, 0.0453186, 0.0602722,
	 0.079834, 0.092804, 0.0980225, 0.0977783, 0.0834351
	},
};

inline void convolver_filter(float* input, float* output, int sf, unsigned int iconvolvefilter)
{
	/** disable fft need some fix for work prop **/
	/*
	    for (int i = 0; i < sf; i++ )
	    {
	    fftin[i][0] = *input++;
	    fftin[i][1] = 0;
	    }


	    fftw_execute(p);
	    // Set result to zero:
	    int j = 0;
	    for (int i = 0; i < sf; i++ )
	    {
	    fftin1[i][0] = filter[j];
	    fftin1[i][1] = 0;
	    j++;
	    if(j>45)j=0;
	    }
	    fftw_execute(pf);
	    for (int i = 0; i < sf; i++ )
	    {
	    fftout[i][0] *= 1.3666  ;
	    fftout[i][1] *= 1.3322  ;
	    }
	    fftw_execute(p1);
	    for (int i = 0; i < sf; i++ )
	    {
	    *output++ = fftresult[i][0] /sf  ;

	    }*/
	if (iconvolvefilter >= sizeof(filters) / sizeof(filters[0])) {
		iconvolvefilter = 0;
	}
	for (int i=0; i < 45; i++) {
		result[i] = result[sf+i];
	}
	for (int i=45; i < sf+46; i++) {
		result[i] = 0;
	}

// Do convolution:
	for (int i = 0; i < sf; i++) {
		for (int j = 0; j < 45; j++) {
			result[i+j] += input[i] * filters[iconvolvefilter][j];
		}
	}
	for (int i = 0; i < sf; i++) {
		*output++ = result[i];
	}
}

inline void moving_filter(float* input, float* output, int sf)
{
	assert(input != output);
	*output++ = (input[0]+input[1])*0.5;
	for (int i=1; i<sf-1; i++) {
		*output++ = (input[i-1]+input[i]+input[i+1])*0.3333334f;
	}
	*output++ = (input[sf]+input[sf-1])*0.5;

}

/****************************************************************
 ** GxConvolver
 **
 ** some parts are copied from jconvolver
 */

Audiofile::Audiofile (void)
{
	reset();
}


Audiofile::~Audiofile (void)
{
	close();
}


void Audiofile::reset (void)
{
	_sndfile = 0;
	_type = TYPE_OTHER;
	_form = FORM_OTHER;
	_rate = 0;
	_chan = 0;
	_size = 0;
}


int Audiofile::open_read (string name)
{
	SF_INFO I;

	reset ();

	if ((_sndfile = sf_open (name.c_str(), SFM_READ, &I)) == 0) return ERR_OPEN;

	switch (I.format & SF_FORMAT_TYPEMASK)
	{
	case SF_FORMAT_CAF:
		_type = TYPE_CAF;
		break;
	case SF_FORMAT_WAV:
		_type = TYPE_WAV;
		break;
	case SF_FORMAT_WAVEX:
		if (sf_command (_sndfile, SFC_WAVEX_GET_AMBISONIC, 0, 0) == SF_AMBISONIC_B_FORMAT)
			_type = TYPE_AMB;
		else
			_type = TYPE_WAV;
	}

	switch (I.format & SF_FORMAT_SUBMASK)
	{
	case SF_FORMAT_PCM_16:
		_form = FORM_16BIT;
		break;
	case SF_FORMAT_PCM_24:
		_form = FORM_24BIT;
		break;
	case SF_FORMAT_PCM_32:
		_form = FORM_32BIT;
		break;
	case SF_FORMAT_FLOAT:
		_form = FORM_FLOAT;
		break;
	}

	_rate = I.samplerate;
	_chan = I.channels;
	_size = I.frames;

	return 0;
}


int Audiofile::close (void)
{
	if (_sndfile) sf_close (_sndfile);
	reset ();
	return 0;
}


int Audiofile::seek (uint32_t posit)
{
	if (!_sndfile) return ERR_MODE;
	if (sf_seek (_sndfile, posit, SEEK_SET) != posit) return ERR_SEEK;
	return 0;
}


int Audiofile::read (float *data, uint32_t frames)
{
	return sf_readf_float (_sndfile, data, frames);
}


bool GxConvolver::read_sndfile (
	Audiofile& audio, int nchan, const float *gain,
	unsigned int *delay, unsigned int offset, unsigned int length)
{
	unsigned int nfram;
	float *buff, *p;
	const unsigned int BSIZE = 0x4000;

	nfram = audio.size();
	if (offset && audio.seek(offset)) {
		gx_system::gx_print_error("convolver", "Can't seek to offset");
		audio.close ();
		return false;
	}
	try {
		buff = new float [BSIZE * nchan];
	} catch (...) {
		audio.close ();
		gx_system::gx_print_error("convolver", "out of memory");
		return false;
	}

	while (length) {
		nfram = (length > BSIZE) ? BSIZE : length;
		nfram = audio.read(buff, nfram);
		if (nfram < 0) {
			gx_system::gx_print_error("convolver", "Error reading file");
			audio.close ();
			delete[] buff;
			return false;
		}
		if (nfram) {
			for (int ichan = 0; ichan < nchan; ichan++) {
				int rc;
				if (ichan >= audio.chan()) {
					rc = impdata_copy(0, 0, ichan, ichan);
				} else {
					p = buff + ichan;
					if (gain[ichan] != 1.0) {
						for (unsigned int ifram = 0; ifram < nfram; ifram++) {
							p[ifram * nchan] *= gain[ichan];
						}
					}
					rc = impdata_create(ichan, ichan, audio.chan(), p,
					                    delay[ichan], delay[ichan] + nfram);
				}
				if (rc) {
					audio.close ();
					delete[] buff;
					gx_system::gx_print_error("convolver", "out of memory");
					return false;
				}
				delay[ichan] += nfram;
			}
			length -= nfram;
		}
	}

	audio.close ();
	delete[] buff;
	return true;
}

void GxConvolver::adjust_values(
	unsigned int audio_size, unsigned int& count, unsigned int& offset,
	unsigned int& delay, unsigned int& ldelay, unsigned int& length,
	unsigned int& size, unsigned int& bufsize)
{
	if (bufsize < count) {
		bufsize = count;
	}
	if (offset > audio_size) {
		offset = audio_size;
	}
	if (!size) {
		if (offset + length > audio_size) {
			gx_system::gx_print_warning("convolver", "data truncated");
			length = audio_size - offset;
		}
		if (!length) {
			length = audio_size - offset;
		}
		size = max(delay, ldelay) + offset + length;
	} else {
		if (delay > size) {
			delay = size;
		}
		if (ldelay > size) {
			ldelay = size;
		}
		if (offset > size - max(delay, ldelay)) {
			offset = size - max(delay, ldelay);
		}
		if (length > size - max(delay, ldelay) - offset) {
			length = size - max(delay, ldelay) - offset;
			gx_system::gx_print_warning("convolver", "data truncated");
		}
		if (!length) {
			length = size - max(delay, ldelay) - offset;
		}
	}
}

bool GxConvolver::configure(
	unsigned int count, int samplerate, string fname, float gain, float lgain,
	unsigned int delay, unsigned int ldelay, unsigned int offset,
	unsigned int length, unsigned int size, unsigned int bufsize)
{
    Audiofile     audio;
    cleanup();
	if (audio.open_read (fname)) {
		gx_system::gx_print_error("convolver", "Unable to open '" + fname + "'");
		return false;
	}
	if (audio.rate() != samplerate) {
		ostringstream buf;
		buf << "sample rate (" << audio.rate() << ") of '" << fname << "' does not match.";
		gx_system::gx_print_warning("convolver", buf.str());
	}
	if (audio.chan() > 2) {
		ostringstream buf;
		buf << "only taking 2 of " << audio.chan() << " channels in impulse response";
		gx_system::gx_print_error("convolver", buf.str());
		return false;
	}
	adjust_values(audio.size(), count, offset, delay, ldelay, length, size, bufsize);
	/* FIXME remove
	cout << "state=" << state() << ", ready=" << ready << endl;
	cout << "fname=" << fname << ", size=" << audio.size()
	     << ", channels=" << audio.chan() << endl;
	cout << "convolver: size=" << size << ", count=" << count << ", bufsize="
	     << bufsize << ", offset=" << offset << ", delay=" << delay
	     << ", ldelay=" << ldelay << ", length=" << length << ", gain" << gain
	     << ", lgain" << lgain << endl;
	*/
	if (Convproc::configure(2, 2, size, count, bufsize, Convproc::MAXPART)) {
		gx_system::gx_print_error("convolver", "error in Convproc::configure");
		return false;
	}
	float gain_a[2] = {gain, lgain};
	unsigned int delay_a[2] = {delay, ldelay};
	return read_sndfile(audio, 2, gain_a, delay_a, offset, length);
}

bool GxConvolver::start()
{
	int abspri, policy;
    struct sched_param  spar;
    pthread_getschedparam(jack_client_thread_id(gx_jack::client), &policy, &spar);
    abspri = spar.sched_priority;
	int rc = start_process(abspri, policy);
	if (rc != 0) {
		gx_system::gx_print_error("convolver", "can't start convolver");
		return false;
	}
	ready = true;
	return true;
}

void GxConvolver::checkstate()
{
	if (state() == Convproc::ST_WAIT) {
		check();
	} else if (state() == ST_STOP) {
		ready = false;
	}
}

bool GxConvolver::compute(int count, float* input1, float *input2, float *output1, float *output2)
{
	if (state() == Convproc::ST_WAIT) {
		check();
	}
	if (state() != Convproc::ST_PROC) {
		if (input1 != output1) {
			memcpy(output1, input1, count * sizeof(float));
		}
		if (input2 != output2) {
			memcpy(output2, input2, count * sizeof(float));
		}
		if (state() == ST_STOP) {
			ready = false;
			return flags() == 0;
		}
		return true;
	}
	memcpy(inpdata(0), input1, count * sizeof(float));
	memcpy(inpdata(1), input2, count * sizeof(float));

	process();

	memcpy (output1, outdata(0), count * sizeof(float));
	memcpy (output2, outdata(1), count * sizeof(float));
	return true;
}

GxConvolver conv;


/****************************************************************
 ** Pitch Tracker
 **
 ** some code and ideas taken from K4Guitune (William Spinelli)
 **
 */
const int DOWNSAMPLE = 16; // downsampling factor
const int ZERO_PADDING_FACTOR = 64;	// Number of times that the FFT is zero-padded to increase frequency resolution.
const float	SIGNAL_THRESHOLD_ON = 0.001; // Value of the threshold above which the processing is activated.
const float SIGNAL_THRESHOLD_OFF = 0.0009; // Value of the threshold below which the input audio signal is deactivated.
const float TRACKER_PERIOD = 0.1; // Time between frequency estimates (in seconds)

void *PitchTracker::static_run(void *p)
{
	((PitchTracker *)p)->run();
	return NULL;
}

PitchTracker::PitchTracker():
	error(false),
	busy(false),
	tick(0),
	m_pthr(0),
	m_buffer(new float[MAX_FFT_SIZE]),
	m_bufferIndex(0),
	m_audioLevel(false),
	m_fftwPlanFFT(0),
	m_fftwPlanIFFT(0)
{
	const int fftw_buffer_size = MAX_FFT_SIZE * ZERO_PADDING_FACTOR;
	m_fftwBufferTime = (float*)fftwf_malloc(fftw_buffer_size * sizeof(float));
	m_fftwBufferFreq = (fftwf_complex*)fftwf_malloc(fftw_buffer_size * sizeof(fftwf_complex));

	memset(m_buffer, 0, MAX_FFT_SIZE * sizeof(float));
	memset(m_fftwBufferTime, 0, fftw_buffer_size * sizeof(float));
	memset(m_fftwBufferFreq, 0, fftw_buffer_size * sizeof(fftwf_complex));

    sem_init(&m_trig, 0, 0);

	if (!m_buffer || !m_fftwBufferTime || !m_fftwBufferFreq) {
		error = true;
	}
}


PitchTracker::~PitchTracker()
{
	fftwf_destroy_plan(m_fftwPlanFFT);
	fftwf_destroy_plan(m_fftwPlanIFFT);
	fftwf_free(m_fftwBufferTime);
	fftwf_free(m_fftwBufferFreq);
	delete[] m_buffer;
}


bool PitchTracker::setParameters(int sampleRate, int fftSize)
{
	assert(fftSize <= MAX_FFT_SIZE);

	if (error) {
		return false;
	}
	m_sampleRate = sampleRate / DOWNSAMPLE;
	resamp.setup(sampleRate, m_sampleRate, 1, 16); // 16 == least quality

	if (m_fftSize != fftSize) {
		m_fftSize = fftSize;
		fftwf_destroy_plan(m_fftwPlanFFT);
		fftwf_destroy_plan(m_fftwPlanIFFT);
		m_fftwPlanFFT = fftwf_plan_dft_r2c_1d(
			m_fftSize, m_fftwBufferTime, m_fftwBufferFreq, FFTW_ESTIMATE); // FFT
		m_fftwPlanIFFT = fftwf_plan_dft_c2r_1d(
			ZERO_PADDING_FACTOR * m_fftSize, m_fftwBufferFreq, m_fftwBufferTime, FFTW_ESTIMATE); // IFFT zero-padded
	}

	if (!m_fftwPlanFFT || !m_fftwPlanIFFT) {
		error = true;
		return false;
	}

	if (!m_pthr) {
		start_thread();
	}
	return !error;
}

void PitchTracker::start_thread()
{
    int                min, max;
    pthread_attr_t     attr;
    struct sched_param  spar;
    int priority, policy;
    pthread_getschedparam(jack_client_thread_id(gx_jack::client), &policy, &spar);
    priority = spar.sched_priority;
    min = sched_get_priority_min(policy);
    max = sched_get_priority_max(policy);
    priority -= 6; // zita-convoler uses 5 levels
    if (priority > max) priority = max;
    if (priority < min) priority = min;
    spar.sched_priority = priority;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setschedpolicy (&attr, policy);
    pthread_attr_setschedparam (&attr, &spar);
    pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setinheritsched (&attr, PTHREAD_EXPLICIT_SCHED);
    //pthread_attr_setstacksize (&attr, 0x10000);
    if (pthread_create (&m_pthr, &attr, static_run, (void*)this)) {
	    error = true;
    }
    pthread_attr_destroy (&attr);
}

int PitchTracker::find_minimum()
{
	const int peakwidth = 3;
	float *p = &m_fftwBufferTime[peakwidth];
	for ( ; p < &m_fftwBufferTime[ZERO_PADDING_FACTOR * m_fftSize / 2 + 1 - peakwidth]; p++) {
		int i;
		for (i = -peakwidth; i <= peakwidth; i++) {
			if (*p > p[i]) {
				break;
			}
		}
		if (i > peakwidth) {
			break;
		}
	}
	return (int)(p - m_fftwBufferTime);
}

int PitchTracker::find_maximum(int l)
{
	float	maxAutocorr			= 0.0;
	int		maxAutocorrIndex	= 0;
	while ( l < ZERO_PADDING_FACTOR * m_fftSize / 2 + 1) {
		if (m_fftwBufferTime[l] > maxAutocorr) {
			maxAutocorr = m_fftwBufferTime[l];
			maxAutocorrIndex = l;
		}
		++l;
	}
	if (maxAutocorr == 0.0) {
		return -1;
	}
	return maxAutocorrIndex;
}

float show_level(int n, float *buf)
{
	float sum = 0.0;
	for (int k = 0; k < n; ++k) {
		sum += fabs(buf[k]);
	}
	return sum;
}

void PitchTracker::add(int count, float* input)
{
	if (error) {
		return;
	}
	resamp.inp_count = count;
	resamp.inp_data = input;
	for (;;) {
		resamp.out_data = &m_buffer[m_bufferIndex];
		int n = MAX_FFT_SIZE - m_bufferIndex;
		resamp.out_count = n;
		resamp.process();
		n -= resamp.out_count; // n := number of output samples
		if (!n) { // all soaked up by filter
			return;
		}
		m_bufferIndex = (m_bufferIndex + n) % MAX_FFT_SIZE;
		if (resamp.inp_count == 0) {
			break;
		}
	}
	if (++tick * count >= m_sampleRate * DOWNSAMPLE * TRACKER_PERIOD) {
		if (busy) {
			return;
		}
		tick = 0;
		copy();
		sem_post(&m_trig);
	}
}

void PitchTracker::copy()
{
	int start = (MAX_FFT_SIZE + m_bufferIndex - m_fftSize) % MAX_FFT_SIZE;
	int end = (MAX_FFT_SIZE + m_bufferIndex) % MAX_FFT_SIZE;
	int cnt = 0;
	if (start >= end) {
		cnt = MAX_FFT_SIZE - start;
		memcpy(m_fftwBufferTime, &m_buffer[start], cnt * sizeof(float));
		start = 0;
	}
	memcpy(&m_fftwBufferTime[cnt], &m_buffer[start], (end - start) * sizeof(float));
}

void PitchTracker::run()
{
	for (;;) {
		busy = false;
		sem_wait(&m_trig);
		busy = true;
		if (error) {
			continue;
		}
		float sum = 0.0;
		for (int k = 0; k < m_fftSize; ++k) {
			sum += fabs(m_fftwBufferTime[k]);
		}
		float threshold = (m_audioLevel ? SIGNAL_THRESHOLD_OFF : SIGNAL_THRESHOLD_ON);
		m_audioLevel = (sum / m_fftSize >= threshold);
		if ( m_audioLevel == false ) {
			setEstimatedFrequency(0.0);
			continue;
		}

		/* Compute the transform of the autocorrelation given in time domain by
		 *           k=-N
		 *    r[t] = sum( x[k] * x[t-k] )
		 *            N
		 * or in the frequency domain (for a real signal) by
		 *    R[f] = X[f] * X[f]' = |X[f]|^2 = Re(X[f])^2 + Im(X[f])^2
		 * When computing the FFT with fftwf_plan_dft_r2c_1d there are only N/2+1
		 * significant samples, so |.|^2 is computed for m_fftSize/2+1 samples only
		 */
		int fftRSize = m_fftSize/2 + 1;
		fftwf_execute(m_fftwPlanFFT);
		for (int k = 0; k < fftRSize; ++k) {
			fftwf_complex& v = m_fftwBufferFreq[k];
			v[0] = v[0]*v[0] + v[1]*v[1];
			v[1] = 0.0;
		}

		// pad the FFT with zeros to increase resolution in time domain after IFFT
		int size_with_padding = ZERO_PADDING_FACTOR * m_fftSize - fftRSize;
		memset(&m_fftwBufferFreq[fftRSize][0], 0, size_with_padding * sizeof(fftwf_complex));
		fftwf_execute(m_fftwPlanIFFT);

		// search for a minimum and then for the next maximum to get the estimated frequency
		int maxAutocorrIndex = find_maximum(find_minimum());

		// compute the frequency of the maximum considering the padding factor
		if (maxAutocorrIndex >= 0) {
			setEstimatedFrequency(ZERO_PADDING_FACTOR * m_sampleRate / (float)maxAutocorrIndex);
		} else {
			setEstimatedFrequency(0.0);
		}
		busy = false;
	}
}

void PitchTracker::setEstimatedFrequency(float freq)
{
	midi.fConsta4 = freq;
	audio.fConsta1t = (freq == 0.0 ? 1000.0 : 12 * log2f(2.272727e-03f * freq));
}

PitchTracker pitch_tracker;


/****************************************************************
 ** functions and variables used by faust dsp files
 */

inline float sigmoid(float x)
{
	return x*(1.5f - 0.5f*x*x);
}

inline float saturate(float x, float t)
{
	if (fabs(x)<t)
		return x;
	else {
		if (x > 0.f)
			return t + (1.f-t)*sigmoid((x-t)/((1-t)*1.5f));
		else
			return -(t + (1.f-t)*sigmoid((-x-t)/((1-t)*1.5f)));
	}
}

inline float hard_cut(float in, float threshold)
{
	if ( in > threshold) {
		in = threshold;
	} else if ( in < -threshold) {
		in = -threshold;
	}

	return in;
}

inline float foldback(float in, float threshold)
{
	if (threshold == 0) threshold = 0.01f;

	if (fabs(in) > threshold) {
		in = fabs(fabs(fmod(in - threshold, threshold*4)) - threshold*2) - threshold;
	}
	return in;
}

inline float fold(float threshold, float v)
{
	// switch between hard_cut or foldback distortion, or plain output
	switch ((int)audio.ffuse) {
	case 0:
		break;
	case 1:
		v = hard_cut(saturate(v,threshold),threshold);
		break;
	case 2:
		v = foldback(v,threshold);
		break;
	}
	return v;
}

inline float add_dc (float val)
{
	return val + 1e-20; // avoid denormals
}

// foreign variable added to faust module feed
// it's set in process_buffers()
namespace feed { float ngate = 1; }  // noise-gate, modifies output gain


/****************************************************************
 ** definitions for code generated with faust / dsp2cc
 */

typedef void (*inifunc)(int);
list<inifunc> inilist;

void faust_init(int samplingFreq)
{
	for (list<inifunc>::iterator i = inilist.begin(); i != inilist.end(); i++) {
		(*i)(samplingFreq);
	}
}

float& get_alias(const char *id)
{
	static float dummy;
	if (!gx_gui::parameter_map.hasId(id)) {
		gx_system::gx_print_error("engine", string("can't define alias for unknown (or not yet defined) parameter id: ") + id);
		return dummy;
	} else {
		return gx_gui::parameter_map[id].getFloat().value;
	}
}

void registerVar(const char* id, const char* name, const char* tp,
                 const char* tooltip, float* var, float val=0,
                 float low=0, float up=0, float step=0)
{
	if (!name[0]) {
		assert(strrchr(id, '.'));
		name = strrchr(id, '.')+1;
	}
	gx_gui::parameter_map.insert(new gx_gui::FloatParameter(id, name, gx_gui::Parameter::Continuous, true, *var, val, low, up, step, true));
}

void registerInit(inifunc f)
{
	inilist.push_back(f);
}

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))

template <int N> inline float faustpower(float x)       { return powf(x,N); }
template <int N> inline double faustpower(double x)     { return pow(x,N); }
template <int N> inline int faustpower(int x)           { return faustpower<N/2>(x) * faustpower<N-N/2>(x); }
template <>      inline int faustpower<0>(int x)        { return 1; }
template <>      inline int faustpower<1>(int x)        { return x; }
#define FAUSTFLOAT float

// amp
#include "faust-cc/preamp.cc"
#include "faust-cc/inputgain.cc"
#include "faust-cc/noise_shaper.cc"
#include "faust-cc/AntiAlias.cc"
#include "faust-cc/HighShelf.cc"
#include "faust-cc/drive.cc"
#include "faust-cc/osc_tube.cc"
#include "faust-cc/reso_tube.cc"
#include "faust-cc/tube.cc"
#include "faust-cc/tubevibrato.cc"
#include "faust-cc/tone.cc"
#include "faust-cc/multifilter.cc"
#include "faust-cc/bassbooster.cc"
#include "faust-cc/feed.cc"
#include "faust-cc/outputgain.cc"
#include "faust-cc/balance.cc"
#include "faust-cc/jconv_post.cc"
#include "faust-cc/balance1.cc"

// effects
#include "faust-cc/overdrive.cc"
#include "faust-cc/compressor.cc"
#include "faust-cc/crybaby.cc"
#include "faust-cc/autowah.cc"
#include "faust-cc/echo.cc"
#include "faust-cc/delay.cc"
#include "faust-cc/distortion.cc"
#include "faust-cc/freeverb.cc"
#include "faust-cc/impulseresponse.cc"
#include "faust-cc/chorus.cc"


//==============================================================================
//
//             this is the process callback called from jack
//
//==============================================================================
void compute (int count, float* input, float* output0, float* output1)
{
	// retrieve engine state
	const GxEngineState estate = (GxEngineState)checky;

	//------------ determine processing type
	unsigned short process_type = ZEROIZE_BUFFERS;

	if (gx_jack::NO_CONNECTION == 0) { // ports connected
		switch (estate) {
		case kEngineOn:
			process_type = PROCESS_BUFFERS;
			break;

		case kEngineBypass:
			process_type = JUSTCOPY_BUFFERS;
			break;

		default: // engine off or whatever: zeroize
			break;
		}
	}

	//------------ main processing routine
	switch (process_type) {

	case PROCESS_BUFFERS:
		process_buffers(count, input, output0, output1);
		break;

		// --------- just copy input to outputs
	case JUSTCOPY_BUFFERS:
		if (conv.is_runnable()) {
			conv.checkstate();
		}
	    balance1::compute(count, input, output0, output1);
		break;


		// ------- zeroize buffers
	case ZEROIZE_BUFFERS:
	default:

		if (conv.is_runnable()) {
			conv.checkstate();
		}
		// the extra port register can only run clean on frame base, therfor the
		// variable jconv_is_running must check on frame base, not in the inner loop.

		// no need of loop.
		// You will avoid triggering an if statement for each frame
		(void)memset(output0, 0, count*sizeof(float));
		(void)memset(output1, 0, count*sizeof(float));

		break;
	}
}

//****************************************************************

inline float noise_gate(int sf, float* input, float ngate)
{
	float sumnoise = 0;
	for (int i = 0; i < sf; i++) {
		sumnoise += sqrf(fabs(input[i]));
	}
	float noisepulse = sqrtf(sumnoise/sf);
	if (noisepulse > audio.fnglevel * 0.01) {
		return 1; // -75db 0.001 = 65db
	} else if (ngate > 0.01) {
		return ngate * 0.996;
	} else {
		return ngate;
	}
}

inline void over_sample(int sf, float *input, float *output)
{
	static float old = 0;
	for (int i = 0; i < sf; i++) {
		float x = *input++;
		*output++ = (old + x) * 0.5;
		*output++ = x;
		old = x;
	}
}

inline void down_sample(int sf, float *input, float *output)
{
	for (int i=0; i<sf; i++) {
		float x = *input++;
		*output++ = (x + *input++) * 0.5;
	}
}

// registering of audio variables
inline void registerNonPresetParam(const char*a, float*c, bool d, float std=0, float lower=0, float upper=1)
{
	gx_gui::parameter_map.insert(new gx_gui::FloatParameter(a,"",gx_gui::Parameter::None,d,*c,std,lower,upper,0,false));
}

// should be int
inline void registerEnumParam(const char*a,const char*b,float*c,float std=0,float lower=0,float upper=1,float step=1)
{
	gx_gui::parameter_map.insert(new gx_gui::FloatParameter(a,b,gx_gui::Parameter::Enum,true,*c,std,lower,upper,step,true));
}

inline void registerEnumParam(const char*a,const char*b,int*c,int std=0,int lower=0,int upper=1)
{
	gx_gui::parameter_map.insert(new gx_gui::IntParameter(a,b,gx_gui::Parameter::Enum,true,*c,std,lower,upper,true));
}

AudioVariables::AudioVariables()
{
	registerEnumParam("amp.threshold", "threshold", &ffuse, 0.f, 0.f, 3.f, 1.0f);
	gx_gui::registerParam("MultiBandFilter.on_off", "on/off", &fmultifilter, 0);
	gx_gui::registerParam("crybaby.autowah", "autowah", &fautowah, 0);
	gx_gui::registerParam("overdrive.on_off", "on/off", &foverdrive4, 0);
	gx_gui::registerParam("distortion.on_off", "on/off", &fcheckbox4, 0);
	gx_gui::registerParam("freeverb.on_off", "on/off", &fcheckbox6, 0);
	gx_gui::registerParam("IR.on_off", "on/off", &fcheckbox8, 0);
	gx_gui::registerParam("crybaby.on_off", "on/off", &fcheckbox5, 0);
	gx_gui::registerParam("echo.on_off", "on/off", &fcheckbox7, 0);
	gx_gui::registerParam("delay.on_off", "on/off", &fdelay, 0);
	gx_gui::registerParam("chorus.on_off", "on/off", &fchorus, 0);
	gx_gui::registerParam("compressor.on_off", "on/off", &fcheckboxcom1, 0);
	gx_gui::registerParam("tube2.on_off", "on/off", &ftube3, 0);
	gx_gui::registerParam("tube.vibrato.on_off", "on/off", &fresoon, 0);
	gx_gui::registerParam("tube.on_off", "on/off", &ftube, 0);
	gx_gui::registerParam("drive.on_off", "on/off", &fprdr, 0);
	gx_gui::registerParam("preamp.on_off", "on/off", &fcheckbox1, 0);
	registerEnumParam("convolve.select", "select", &convolvefilter, 0.f, 0.f, 7.f, 1.0f);
	gx_gui::registerParam("convolve.on_off", "on/off", &fconvolve, 0);
	gx_gui::registerParam("amp.bass_boost.on_off", "on/off", &fboost, 0);
	gx_gui::registerParam("amp.oversample.on_off", "on/off", &fupsample, 0);
	gx_gui::registerParam("anti_aliase.on_off", "on/off", &antialis0, 0);
	gx_gui::registerParam("noise_gate.on_off", "on/off", &fnoise_g, 0);
	gx_gui::registerParam("noise_gate.threshold", "Threshold", &fnglevel, 0.017f, 0.01f, 0.21f, 0.001f);
	gx_gui::registerParam("shaper.on_off", "on/off", &fng, 0);
	gx_gui::registerParam("jconv.on_off", "Run", &gx_jconv::GxJConvSettings::checkbutton7);
	// only save and restore, no midi control

	// positions of effects
	registerNonPresetParam("crybaby.position", &posit0, true, 5, 0, 8);
	registerNonPresetParam("overdrive.position", &posit1, true, 2, 0, 8);
	registerNonPresetParam("distortion.position", &posit2, true, 1, 0, 8);
	registerNonPresetParam("freeverb.position", &posit3, true, 3, 0, 8);
	registerNonPresetParam("IR.position", &posit4, true, 4, 0, 8);
	registerNonPresetParam("compressor.position", &posit5, true, 0, 0, 8);
	registerNonPresetParam("echo.position", &posit6, true, 6, 0, 8);
	registerNonPresetParam("delay.position", &posit7, true, 8, 0, 8);
	registerNonPresetParam("chorus.position", &posit8, true, 7, 0, 8);

	// togglebuttons for dialogboxes and expander for effect details
	registerNonPresetParam("compressor.dialog", &fdialogbox8, false);
	registerNonPresetParam("distortion.dialog", &fdialogbox1, false);
	registerNonPresetParam("freeverb.dialog", &fdialogbox2, false);
	registerNonPresetParam("IR.dialog", &fdialogbox3, false);
	registerNonPresetParam("crybaby.dialog", &fdialogbox4, false);
	registerNonPresetParam("chorus.dialog", &fchorusbox, false);
	registerNonPresetParam("midi_out.dialog", &fdialogbox6, false);
	registerNonPresetParam("jconv.dialog", &fdialogboxj, false);
	registerNonPresetParam("jconv.expander", &fexpand2, false);
	registerNonPresetParam("jconv.filedialog", &filebutton, false);

	// user interface options
	registerNonPresetParam("ui.latency_nowarn", &fwarn, false, 0);
	registerNonPresetParam("ui.skin", &fskin, false, 0, 0, 100);
	registerNonPresetParam("ui.main_expander", &fexpand, false);

	// shouldn't be saved, only output?
	registerNonPresetParam("system.fConsta1t", &fConsta1t, false);
	registerNonPresetParam("system.midistat", &midistat, false);
	registerNonPresetParam("system.waveview", &viv, false);
}

AudioVariables audio;

void process_buffers(int count, float* input, float* output0, float* output1)
{
	int tuner_on = gx_gui::shownote + (int)isMidiOn() + 1;
	if (tuner_on > 0) {
		if (gx_gui::shownote == 0) {
			audio.fConsta1 = 1000.0f;
			gx_gui::shownote = -1;
		} else {
			pitch_tracker.add(count, input);
			moving_filter(input, checkfreq, count);
		}
	}
	HighShelf::compute(count, input, output0);

	if (audio.fnoise_g) {
		feed::ngate = noise_gate(count,output0, feed::ngate);
    } else {
		feed::ngate = 1;
    }
    if (audio.fng) {
	    noise_shaper::compute(count, output0, output0);
    }
    if (audio.fcheckbox1) {
	    preamp::compute(count, output0, output0);
    }

    // *** Start (maybe) oversampled processing ***
    static int fupsample_old = 0; // startup always initialises with SR
    int ovs_count, ovs_sr;
    float *ovs_buffer;
    if (audio.fupsample) {
		// 2*oversample
	    over_sample(count, output0, oversample);
	    ovs_sr = 2 * gx_jack::jack_sr;
	    ovs_count = 2 * count;
	    ovs_buffer = oversample;
    } else {
	    ovs_sr = gx_jack::jack_sr;
	    ovs_count = count;
	    ovs_buffer = output0;
    }
    if (audio.fupsample != fupsample_old) {
	    fupsample_old = audio.fupsample;
	    osc_tube::init(ovs_sr);
    }
    if (audio.antialis0) {
	    AntiAlias::compute(ovs_count, ovs_buffer, ovs_buffer);
    }
    if (audio.ftube) {
	    tube::compute(ovs_count, ovs_buffer, ovs_buffer);
    }
    if (audio.ftube3) {
	    osc_tube::compute(ovs_count, ovs_buffer, ovs_buffer);
	    //reso_tube::compute(ovs_count, ovs_buffer, ovs_buffer);
    }
    if (audio.fprdr) {
	    drive::compute(ovs_count, ovs_buffer, ovs_buffer);
    }
    if (audio.fupsample) {
	    down_sample(count, oversample, output0);
    }
    //*** End (maybe) oversampled processing ***

    if (audio.fconvolve) {
	    convolver_filter(output0, output0, count, (unsigned int)audio.convolvefilter);
    }
    inputgain::compute(count, output0, output0);
    tone::compute(count, output0, output0);
    if (audio.fresoon) {
	    tubevibrato::compute(count, output0, output0);
    }
    for (int m = 0; m < 8; m++) {
	    if (audio.posit0 == m && audio.fcheckbox5 && !audio.fautowah) {
		    crybaby::compute(count, output0, output0);
	    } else if (audio.posit0 == m && audio.fcheckbox5 && audio.fautowah) {
		    autowah::compute(count, output0, output0);
	    } else if (audio.posit5 == m && audio.fcheckboxcom1) {
		    compressor::compute(count, output0, output0);
	    } else if (audio.posit1 == m && audio.foverdrive4) {
		    overdrive::compute(count, output0, output0);
	    } else if (audio.posit2 == m && audio.fcheckbox4) {
		    distortion::compute(count, output0, output0);
	    } else if (audio.posit3 == m && audio.fcheckbox6) {
		    freeverb::compute(count, output0, output0);
	    } else if (audio.posit6 == m && audio.fcheckbox7) {
		    echo::compute(count, output0, output0);
	    } else if (audio.posit4 == m && audio.fcheckbox8) {
		    impulseresponse::compute(count, output0, output0);
	    } else if (audio.posit7 == m && audio.fdelay) {
		    delay::compute(count, output0, output0);
	    }
    }

    // Multibandfilter
    if (audio.fmultifilter) {
		multifilter::compute(count, output0, output0);
	}

    outputgain::compute(count, output0, output0);

    if (audio.fboost) {
	    bassbooster::compute(count, output0, output0);
    }
    feed::compute(count, output0, output0, output1);

    if (audio.fchorus) {
	    chorus::compute(count, output0, output1, output0, output1);
    }
    if (conv.is_runnable()) {
	    // reuse oversampling buffer
	    float *conv_out0 = oversample;
	    float *conv_out1 = oversample+count;
	    if (!conv.compute(count, output0, output1, conv_out0, conv_out1)) {
		    gx_jconv::GxJConvSettings::checkbutton7 = 0;
		    cout << "overload" << endl;
		    //FIXME error message??
	    } else {
		    jconv_post::compute(count, output0, output1, conv_out0, conv_out1, output0, output1);
	    }
    } else {
	    balance::compute(count, output0, output1, output0, output1);
    }
	(void)memcpy(get_frame, output0, sizeof(float)*count);
	(void)memcpy(get_frame1, output1, sizeof(float)*count);
}

} // namespace gx_engine
