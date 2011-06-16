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

/* ------- This is the guitarix convolver, part of gx_engine_audio ------- */

#include <cstring>
#include <jack/jack.h>
#include "guitarix.h"

/****************************************************************
 ** some pieces in this file are copied from jconvolver
 */

/****************************************************************
 ** AudioFile
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


/****************************************************************
 ** GxConvolverBase
 */

void GxConvolverBase::adjust_values(
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
			gx_system::gx_print_warning(
				"convolver",
				(boost::format("length adjusted (%1% + %2% > %3%")
				 % offset % length % audio_size).str());
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

bool GxConvolverBase::start()
{
	int abspri, policy;
    struct sched_param  spar;
    pthread_getschedparam(jack_client_thread_id(gx_jack::gxjack.client), &policy, &spar);
    abspri = spar.sched_priority;
	int rc = start_process(abspri, policy);
	if (rc != 0) {
		gx_system::gx_print_error("convolver", "can't start convolver");
		return false;
	}
	ready = true;
	return true;
}

bool GxConvolverBase::checkstate()
{
	if (state() == Convproc::ST_WAIT) {
		check();
		return false;
	} else if (state() == ST_STOP) {
		ready = false;
	}
	return true;
}


/****************************************************************
 ** GxConvolver
 */

inline void compute_interpolation(double& fct, double& gp, unsigned int& idx, const Gainline& points, int offset)
{
	fct = (points[idx+1].g-points[idx].g)/(20*(points[idx+1].i-points[idx].i));
	gp = points[idx].g/20 + fct * (offset-points[idx].i);
	idx++;
}

bool GxConvolver::read_sndfile (
	Audiofile& audio, int nchan, int samplerate, const float *gain,
	unsigned int *delay, unsigned int offset, unsigned int length,
	const Gainline& points)
{
	unsigned int nfram;
	float *buff;
	float *rbuff = 0;
	float *bufp;
	// keep BSIZE big enough so that resamp.flush() doesn't cause overflow
	// (> 100 should be enough, and should be kept bigger anyhow)
	const unsigned int BSIZE = 0x4000;
	gx_resample::StreamingResampler resamp;

	if (offset && audio.seek(offset)) {
		gx_system::gx_print_error("convolver", "Can't seek to offset");
		audio.close ();
		return false;
	}
	try {
		buff = new float[BSIZE * nchan];
	} catch (...) {
		audio.close();
		gx_system::gx_print_error("convolver", "out of memory");
		return false;
	}
	if (samplerate != audio.rate()) {
		ostringstream buf;
		buf << "resampling from " << audio.rate() << " to " << samplerate;
		gx_system::gx_print_info("convolver", buf.str());
		if (!resamp.setup(audio.rate(), samplerate, nchan)) {
			assert(false);
		}
		try {
			rbuff = new float[resamp.get_max_out_size(BSIZE)*nchan];
		} catch (...) {
			audio.close();
			gx_system::gx_print_error("convolver", "out of memory");
			return false;
		}
		bufp = rbuff;
	} else {
		bufp = buff;
	}
	bool done = false;
	unsigned int idx = 0; // current index in gainline point array
	double gp = 0.0, fct = 0.0; // calculated parameter of interpolation line
	if (points.size()) {
		while ((unsigned int)points[idx].i < offset) {
			idx++;
			assert(idx < points.size());
		}
		if ((unsigned int)points[idx].i > offset) {
			idx--;
			compute_interpolation(fct, gp, idx, points, offset);
		}
	}
	while (!done) {
		unsigned int cnt;
		nfram = (length > BSIZE) ? BSIZE : length;
		if (length) {
			nfram = audio.read(buff, nfram);
			if (nfram < 0) {
				gx_system::gx_print_error("convolver", "Error reading file");
				audio.close ();
				delete[] buff;
				delete[] rbuff;
				return false;
			}
			for (unsigned int ix = 0; ix < nfram; ix++) {
				if (idx+1 < points.size() && (unsigned int)points[idx].i == offset + ix) {
					compute_interpolation(fct, gp, idx, points, offset);
				}
				for (int ichan = 0; ichan < nchan; ichan++) {
					buff[ix*nchan+ichan] *= pow(10, gp + ix*fct) * gain[ichan];
				}
			}
			offset += nfram;
			gp += nfram*fct;
			cnt = nfram;
			if (rbuff) {
				cnt = resamp.process(nfram, buff, rbuff);
			}
		} else {
			if (rbuff) {
				cnt = resamp.flush(rbuff);
				done = true;
			} else {
				break;
			}
		}
		if (cnt) {

			for (int ichan = 0; ichan < nchan; ichan++) {
				int rc;
				if (ichan >= audio.chan()) {
					rc = impdata_copy(0, 0, ichan, ichan);
				} else {
					rc = impdata_create(ichan, ichan, audio.chan(), bufp + ichan,
					                    delay[ichan], delay[ichan] + cnt);
				}
				if (rc) {
					audio.close ();
					delete[] buff;
					delete[] rbuff;
					gx_system::gx_print_error("convolver", "out of memory");
					return false;
				}
				delay[ichan] += cnt;
			}
			length -= nfram;
		}
	}

	audio.close ();
	delete[] buff;
	delete[] rbuff;
	return true;
}

bool GxConvolver::configure(
	unsigned int count, int samplerate, string fname, float gain, float lgain,
	unsigned int delay, unsigned int ldelay, unsigned int offset,
	unsigned int length, unsigned int size, unsigned int bufsize,
	const Gainline& points)
{
    Audiofile     audio;
    cleanup();
	if (audio.open_read (fname)) {
		gx_system::gx_print_error("convolver", "Unable to open '" + fname + "'");
		return false;
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
	return read_sndfile(audio, 2, samplerate, gain_a, delay_a, offset, length, points);
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
 ** GxSimpleConvolver
 */

bool GxSimpleConvolver::configure(int count, float *impresp, unsigned int samplerate)
{
	bool dyn = false;
	if (samplerate != gx_jack::gxjack.jack_sr) {
		gx_resample::BufferResampler r;
		impresp = r.process(samplerate, count, impresp, gx_jack::gxjack.jack_sr, count);
		if (!impresp) {
			gx_system::gx_print_error("convolver", "failed to resample");
			return false;
		}
		dyn = true;
	}
	cleanup();
	bool ret;
    if (Convproc::configure(1, 1, count, gx_jack::gxjack.jack_bs, gx_jack::gxjack.jack_bs, Convproc::MAXPART)) {
		gx_system::gx_print_error("convolver", "error in Convproc::configure");
		ret = false;
    } else if (impdata_create(0, 0, 1, impresp, 0, count)) {
		gx_system::gx_print_error("convolver", "out of memory");
		ret = false;
    } else {
	    ret = true;
    }
    if (dyn) {
	    delete impresp;
    }
    return ret;
}

bool GxSimpleConvolver::compute(int count, float* input, float *output)
{
	if (state() == Convproc::ST_WAIT) {
		check();
	}
	if (state() != Convproc::ST_PROC) {
		if (input != output) {
			memcpy(output, input, count * sizeof(float));
		}
		if (state() == ST_STOP) {
			ready = false;
			return flags() == 0;
		}
		return true;
	}
	memcpy(inpdata(0), input, count * sizeof(float));

	process();

	memcpy (output, outdata(0), count * sizeof(float));
	return true;
}

GxSimpleConvolver cab_conv;
GxSimpleConvolver contrast_conv;

}
