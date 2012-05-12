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

#include "engine.h"

/****************************************************************
 ** some pieces in this file are copied from jconvolver
 */

/****************************************************************
 ** AudioFile
 */

namespace gx_engine {

Audiofile::Audiofile(void) {
    reset();
}


Audiofile::~Audiofile(void) {
    close();
}


void Audiofile::reset(void) {
    _sndfile = 0;
    _type = TYPE_OTHER;
    _form = FORM_OTHER;
    _rate = 0;
    _chan = 0;
    _size = 0;
}


int Audiofile::open_read(string name) {
    SF_INFO I;

    reset();

    if ((_sndfile = sf_open(name.c_str(), SFM_READ, &I)) == 0) return ERR_OPEN;

    switch (I.format & SF_FORMAT_TYPEMASK) {
    case SF_FORMAT_CAF:
        _type = TYPE_CAF;
        break;
    case SF_FORMAT_WAV:
        _type = TYPE_WAV;
        break;
    case SF_FORMAT_WAVEX:
#ifdef     SFC_WAVEX_GET_AMBISONIC
        if (sf_command(_sndfile, SFC_WAVEX_GET_AMBISONIC, 0, 0) == SF_AMBISONIC_B_FORMAT)
            _type = TYPE_AMB;
        else
#endif
            _type = TYPE_WAV;
    }

    switch (I.format & SF_FORMAT_SUBMASK) {
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


int Audiofile::close(void) {
    if (_sndfile) sf_close(_sndfile);
    reset();
    return 0;
}


int Audiofile::seek(uint32_t posit) {
    if (!_sndfile) return ERR_MODE;
    if (sf_seek(_sndfile, posit, SEEK_SET) != posit) return ERR_SEEK;
    return 0;
}


int Audiofile::read(float *data, uint32_t frames) {
    return sf_readf_float(_sndfile, data, frames);
}


/****************************************************************
 ** GxConvolverBase
 */

GxConvolverBase::~GxConvolverBase() {
    if (is_runnable()) {
	stop_process();
    }
}

void GxConvolverBase::adjust_values(
    unsigned int audio_size, unsigned int& count, unsigned int& offset,
    unsigned int& delay, unsigned int& ldelay, unsigned int& length,
    unsigned int& size, unsigned int& bufsize) {

    if (bufsize < count) {
        bufsize = count;
    }
    if (bufsize < Convproc::MINPART) {
        bufsize = Convproc::MINPART;
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

bool GxConvolverBase::start(int policy, int priority) {
    int rc = start_process(priority, policy);
    if (rc != 0) {
        gx_system::gx_print_error("convolver", "can't start convolver");
        return false;
    }
    ready = true;
    return true;
}

bool GxConvolverBase::checkstate() {
    if (state() == Convproc::ST_WAIT) {
        if (check_stop()) {
	    ready = false;
	} else {
	    return false;
	}
    } else if (state() == ST_STOP) {
        ready = false;
    }
    return true;
}

/****************************************************************
 ** GxConvolver
 */

/*
** GxConvolver::read_sndfile()
**
** read samples from soundfile into convolver
** the convolver is working at rate samplerate, the audio file has audio.rate
**
** offset, length, points are based on audio.rate, delay and the count of
** samples written into the convolver are based on samplerate.
**
** Arguments:
**    Audiofile& audio        already opened, will be converted to samplerate
**                            on the fly
**    int nchan               channel count for convolver (can be less
**                            or more than audio.chan())
**    int samplerate          current engine samplerate
**    const float *gain       array[nchan] of gains to be applied
**    unsigned int *delay     array[nchan], starting sample index for values
**                            stored into convolver
**    unsigned int offset     offset into audio file
**    unsigned int length     number of samples to be read from audio
**    const Gainline& points  gain line to be applied
**
** returns false if some error occurred, else true
*/
bool GxConvolver::read_sndfile(
    Audiofile& audio, int nchan, int samplerate, const float *gain,
    unsigned int *delay, unsigned int offset, unsigned int length,
    const Gainline& points) {
    unsigned int nfram;
    float *buff;
    float *rbuff = 0;
    float *bufp;
    // keep BSIZE big enough so that resamp.flush() doesn't cause overflow
    // (> 100 should be enough, and should be kept bigger anyhow)
    const unsigned int BSIZE = 0x8000; //  0x4000;
    

    if (offset && audio.seek(offset)) {
        gx_system::gx_print_error("convolver", "Can't seek to offset");
        audio.close();
        return false;
    }
    try {
        buff = new float[BSIZE * nchan];
    } catch(...) {
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
        } catch(...) {
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
                audio.close();
                delete[] buff;
                delete[] rbuff;
                return false;
            }
            for (unsigned int ix = 0; ix < nfram; ix++) {
                if (idx+1 < points.size() && (unsigned int)points[idx].i == offset + ix) {
                    compute_interpolation(fct, gp, idx, points, offset);
                }

                for (int ichan = 0; ichan < nchan; ichan++) {
                    buff[ix*nchan+ichan] *= pow(10, gp + ix*fct) *  gain[ichan];
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
                    audio.close();
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

    audio.close();
    delete[] buff;
    delete[] rbuff;
    
    return true;
}

bool GxConvolver::configure(
    string fname, float gain, float lgain,
    unsigned int delay, unsigned int ldelay, unsigned int offset,
    unsigned int length, unsigned int size, unsigned int bufsize,
    const Gainline& points) {
    Audiofile     audio;
    cleanup();
    if (fname.empty()) {
        return false;
    }
    if (audio.open_read(fname)) {
        gx_system::gx_print_error("convolver", "Unable to open '" + fname + "'");
        return false;
    }
    if (audio.chan() > 2) {
        ostringstream buf;
        buf << "only taking 2 of " << audio.chan() << " channels in impulse response";
        gx_system::gx_print_error("convolver", buf.str());
        return false;
    }
    adjust_values(audio.size(), buffersize, offset, delay, ldelay, length, size, bufsize);
    /* FIXME remove
    cout << "state=" << state() << ", ready=" << ready << endl;
    cout << "fname=" << fname << ", size=" << audio.size()
         << ", channels=" << audio.chan() << endl;
    cout << "convolver: size=" << size << ", count=" << buffersize << ", bufsize="
         << bufsize << ", offset=" << offset << ", delay=" << delay
         << ", ldelay=" << ldelay << ", length=" << length << ", gain" << gain
         << ", lgain" << lgain << endl;
    */

    if (samplerate != static_cast<unsigned int>(audio.rate())) {
	float f = float(samplerate) / audio.rate();
	size = round(size * f) + 2; // 2 is safety margin for rounding differences
	delay = round(delay * f);
	ldelay = round(ldelay * f);
    }
    if (Convproc::configure(2, 2, size, buffersize, bufsize, Convproc::MAXPART)) {
        gx_system::gx_print_error("convolver", "error in Convproc::configure ");
        return false;
    }

    float gain_a[2] = {gain, lgain};
    unsigned int delay_a[2] = {delay, ldelay};
    return read_sndfile(audio, 2, samplerate, gain_a, delay_a, offset, length, points);
}

bool GxConvolver::compute(int count, float* input1, float *input2, float *output1,
                          float *output2) {
    if (state() != Convproc::ST_PROC) {
        if (input1 != output1) {
            memcpy(output1, input1, count * sizeof(float));
        }
        if (input2 != output2) {
            memcpy(output2, input2, count * sizeof(float));
        }
	if (state() == Convproc::ST_WAIT) {
	    check_stop();
	}
        if (state() == ST_STOP) {
            ready = false;
        }
        return true;
    }
    memcpy(inpdata(0), input1, count * sizeof(float));
    memcpy(inpdata(1), input2, count * sizeof(float));

    int flags = process(sync);

    memcpy(output1, outdata(0), count * sizeof(float));
    memcpy(output2, outdata(1), count * sizeof(float));
    return flags == 0;
}


/****************************************************************
 ** GxSimpleConvolver
 */

class CheckResample {
private:
    float *vec;
    gx_resample::BufferResampler& resamp;
public:
    CheckResample(gx_resample::BufferResampler& resamp_): vec(0), resamp(resamp_) {}
    float *resample(int *count, float *impresp, unsigned int imprate, unsigned int samplerate) {
	if (imprate != samplerate) {
	    vec = resamp.process(imprate, *count, impresp, samplerate, count);
	    if (!vec) {
		boost::format msg = boost::format("failed to resample %1% -> %2%") % imprate % samplerate;
		if (samplerate) {
		    gx_system::gx_print_error("convolver", msg);
		} else {
		    // not need for extra error when no samplerate (probably not connected to jack)
		    gx_system::gx_print_warning("convolver", msg);
		}
		return 0;
	    }
	    return vec;
	}
        return impresp;
    }
    ~CheckResample() {
	if (vec) {
	    delete vec;
	}
    }
};

bool GxSimpleConvolver::configure(int count, float *impresp, unsigned int imprate) {
    CheckResample r(resamp);
    impresp = r.resample(&count, impresp, imprate, samplerate);
    if (!impresp) {
	return false;
    }
    cleanup();
    unsigned int bufsize = buffersize;
    if (bufsize < Convproc::MINPART) {
        bufsize = Convproc::MINPART;
    }
    if (Convproc::configure(1, 1, count, buffersize,
                            bufsize, Convproc::MAXPART)) {
        gx_system::gx_print_error("convolver", "error in Convproc::configure");
        return false;
    }
    if (impdata_create(0, 0, 1, impresp, 0, count)) {
        gx_system::gx_print_error("convolver", "out of memory");
        return false;
    }
    return true;
}

bool GxSimpleConvolver::update(int count, float *impresp, unsigned int imprate) {
    CheckResample r(resamp);
    impresp = r.resample(&count, impresp, imprate, samplerate);
    if (!impresp) {
	return false;
    }
    if (impdata_update(0, 0, 1, impresp, 0, count)) {
        gx_system::gx_print_error("convolver", "update: internal error");
        return false;
    }
    return true;
}

bool GxSimpleConvolver::compute(int count, float* input, float *output) {
    if (state() != Convproc::ST_PROC) {
        if (input != output) {
            memcpy(output, input, count * sizeof(float));
        }
	if (state() == Convproc::ST_WAIT) {
	    check_stop();
	}
        if (state() == ST_STOP) {
            ready = false;
        }
        return true;
    }
    memcpy(inpdata(0), input, count * sizeof(float));

    int flags = process(sync);

    memcpy(output, outdata(0), count * sizeof(float));
    return flags == 0;
}

}
