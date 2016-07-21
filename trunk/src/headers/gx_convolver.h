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

/* ------- This is the guitarix convolution Engine  ------- */

#pragma once

#ifndef SRC_HEADERS_GX_CONVOLVER_H_
#define SRC_HEADERS_GX_CONVOLVER_H_

#include <zita-convolver.h>
#include <gxwmm/gainline.h>

#include <sndfile.hh>

namespace gx_engine {

/* GxConvolver */

class Audiofile {
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

    Audiofile(void);
    ~Audiofile(void);

    int type(void) const      { return _type; }
    int form(void) const      { return _form; }
    int rate(void) const      { return _rate; }
    int chan(void) const      { return _chan; }
    unsigned int size(void) const { return _size; }

    int open_read(string name);
    int close(void);

    int seek(unsigned int posit);
    int read(float *data, unsigned int frames);

private:

    void reset(void);

    SNDFILE     *_sndfile;
    int          _type;
    int          _form;
    int          _rate;
    int          _chan;
    unsigned int _size;
};

bool read_audio(const std::string& filename, unsigned int *audio_size, int *audio_chan,
		int *audio_type, int *audio_form, int *audio_rate, float **buffer);

class GxConvolverBase: protected Convproc {
protected:
    volatile bool ready;
    bool sync;
    void adjust_values(unsigned int audio_size, unsigned int& count, unsigned int& offset,
                       unsigned int& delay, unsigned int& ldelay, unsigned int& length,
                       unsigned int& size, unsigned int& bufsize);
    unsigned int buffersize;
    unsigned int samplerate;
    GxConvolverBase(): ready(false), sync(false), buffersize(), samplerate() {}
    ~GxConvolverBase();
public:
    inline void set_buffersize(unsigned int sz) { buffersize = sz; }
    inline unsigned int get_buffersize() { return buffersize; }
    inline void set_samplerate(unsigned int sr) { samplerate = sr; }
    inline unsigned int get_samplerate() { return samplerate; }
    bool checkstate();
    using Convproc::state;
    inline void set_not_runnable()   { ready = false; }
    inline bool is_runnable()        { return ready; }
    bool start(int policy, int priority);
    using Convproc::stop_process;
    inline void set_sync(bool val)   { sync = val; }
};

class GxConvolver: public GxConvolverBase {
private:
    gx_resample::StreamingResampler resamp;
    bool read_sndfile(Audiofile& audio, int nchan, int samplerate, const float *gain,
		      unsigned int *delay, unsigned int offset, unsigned int length,
		      const Gainline& points);
public:
    GxConvolver(): GxConvolverBase(), resamp() {}
    bool configure(
        string fname, float gain, float lgain,
        unsigned int delay, unsigned int ldelay, unsigned int offset,
        unsigned int length, unsigned int size, unsigned int bufsize,
        const Gainline& gainline);
    bool compute(int count, float* input1, float *input2, float *output1, float *output2);
    bool configure(string fname, float gain, unsigned int delay, unsigned int offset,
		   unsigned int length, unsigned int size, unsigned int bufsize,
		   const Gainline& gainline);
    bool compute(int count, float* input, float *output);
    static void compute_interpolation(double& fct, double& gp, unsigned int& idx,
				      const Gainline& points, int offset);
};

inline void GxConvolver::compute_interpolation(
    double& fct, double& gp, unsigned int& idx, const Gainline& points, int offset) {
    fct = (points[idx+1].g-points[idx].g)/(20*(points[idx+1].i-points[idx].i));
    gp = points[idx].g/20 + fct * (offset-points[idx].i);
    idx++;
}


class GxSimpleConvolver: public GxConvolverBase {
private:
    gx_resample::BufferResampler& resamp;
public:
    GxSimpleConvolver(gx_resample::BufferResampler& resamp_)
	: GxConvolverBase(), resamp(resamp_) {}
    bool configure(int count, float *impresp, unsigned int imprate);
    bool update(int count, float *impresp, unsigned int imprate);
    bool compute(int count, float* input, float *output);
    bool compute(int count, float* buffer) {
        return is_runnable() ? compute(count, buffer, buffer) : true;
    }
  
    bool configure_stereo(int count, float *impresp, unsigned int imprate);
    bool update_stereo(int count, float *impresp, unsigned int imprate);
    bool compute_stereo(int count, float* input, float* input1, float *output, float *output1);
    bool compute_stereo(int count, float* buffer, float* buffer1)
    {
      return is_runnable() ? compute_stereo(count, buffer, buffer1, buffer, buffer1) : true;
    }
};

} /* end of gx_engine namespace */
#endif  // SRC_HEADERS_GX_CONVOLVER_H_
