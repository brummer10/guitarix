/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose
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


#pragma once

#ifndef SRC_HEADERS_GX_CONVOLVER_H_
#define SRC_HEADERS_GX_CONVOLVER_H_

#include <zita-convolver.h>

/* GxConvolver */


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
    static void run_static(uint32_t n_samples, GxSimpleConvolver*, float *output);
};


#endif  // SRC_HEADERS_GX_CONVOLVER_H_
