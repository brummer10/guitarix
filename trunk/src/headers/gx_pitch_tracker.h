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

#ifndef SRC_HEADERS_GX_PITCH_TRACKER_H_
#define SRC_HEADERS_GX_PITCH_TRACKER_H_

#include <zita-resampler.h>

namespace gx_engine {
/* ------------- Pitch Tracker ------------- */

const int MAX_FFT_SIZE = 512; // The size of the read buffer (max FFT window size).

class PitchTracker {
 public:
    PitchTracker();
    ~PitchTracker();
    bool            pt_initialized;
    bool            setParameters(int sampleRate, int fftSize );
    void            init()
                    {setParameters(static_cast<int>(gx_jack::gxjack.jack_sr), MAX_FFT_SIZE);}
    void            add(int count, float *input);
    float           tuner_estimate();
    void            stop_thread();

 private:
    void            run();
    static void     *static_run(void* p);
    void            setEstimatedFrequency(float freq);
    int             find_minimum();
    int             find_maximum(int l);
    void            start_thread();
    void            copy();
    bool            error;
    volatile bool   busy;
    int             tick;
    sem_t           m_trig;
    pthread_t       m_pthr;
    Resampler       *resamp;
    int             m_sampleRate;
    // Size of the FFT window.
    int             m_fftSize;
    // The audio buffer that stores the input signal.
    float           *m_buffer;
    // Index of the first empty position in the buffer.
    int             m_bufferIndex;
    // Whether or not the input level is high enough.
    bool            m_audioLevel;
    // Support buffer used to store signals in the time domain.
    float          *m_fftwBufferTime;
    // Support buffer used to store signals in the frequency domain.
    fftwf_complex  *m_fftwBufferFreq;
    // Plan to compute the FFT of a given signal.
    fftwf_plan      m_fftwPlanFFT;
    // Plan to compute the IFFT of a given signal (with additional zero-padding).
    fftwf_plan      m_fftwPlanIFFT;
};

extern PitchTracker pitch_tracker;
}
#endif  // SRC_HEADERS_GX_PITCH_TRACKER_H_

