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

/* ------- This is the guitarix convolver, part of gx_engine_audio ------- */


#include <cstring>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>

#include <array>
#include <zita-convolver.h>
#include <fftw3.h>
#include <zita-resampler.h>

#include <cassert>
#include <sigc++/sigc++.h>
#include <semaphore.h>

using namespace std;

#include <cmath>
#include <gtk/gtk.h>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <sndfile.h>

#include "guitarix.h"


/****************************************************************
 ** GxConvolver
 **
 ** some parts are copied from jconvolver
 */

namespace gx_engine
{

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
#ifdef 	SFC_WAVEX_GET_AMBISONIC
		if (sf_command (_sndfile, SFC_WAVEX_GET_AMBISONIC, 0, 0) == SF_AMBISONIC_B_FORMAT)
			_type = TYPE_AMB;
		else
#endif
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

}


