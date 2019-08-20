/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose, Steve Poskitt
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
#include <stdint.h>
#include "gx_resampler.h"
#include "../../../config.h"
/* GxConvolver */

class GxConvolverBase: protected Convproc
{
protected:
  volatile bool ready;
  bool sync;
  void adjust_values(uint32_t audio_size, uint32_t& count, uint32_t& offset,
                     uint32_t& delay, uint32_t& ldelay, uint32_t& length,
                     uint32_t& size, uint32_t& bufsize);
  uint32_t buffersize;
  uint32_t samplerate;
  GxConvolverBase(): ready(false), sync(false), buffersize(), samplerate() {}
  ~GxConvolverBase();
public:
  inline void set_buffersize(uint32_t sz)
  {
    buffersize = sz;
  }
  inline uint32_t get_buffersize()
  {
    return buffersize;
  }
  inline void set_samplerate(uint32_t sr)
  {
    samplerate = sr;
  }
  inline uint32_t get_samplerate()
  {
    return samplerate;
  }
  bool checkstate();
  using Convproc::state;
  inline void set_not_runnable()
  {
    ready = false;
  }
  inline bool is_runnable()
  {
    return ready;
  }
  bool start(int32_t policy, int32_t priority);
  using Convproc::stop_process;
  using Convproc::cleanup;
  inline void set_sync(bool val)
  {
    sync = val;
  }
};


class GxSimpleConvolver: public GxConvolverBase
{
private:
  gx_resample::BufferResampler& resamp;
public:
  int32_t cab_count;
  uint32_t cab_sr;
  float *cab_data;
  float *cab_data_new;
  GxSimpleConvolver(gx_resample::BufferResampler& resamp_)
    : GxConvolverBase(), resamp(resamp_), cab_count(0), cab_sr(0),
    cab_data(NULL), cab_data_new(NULL) {}
  bool configure(int32_t count, float *impresp, uint32_t imprate);
  bool update(int32_t count, float *impresp, uint32_t imprate);
  bool compute(int32_t count, float* input, float *output);
  bool compute(int32_t count, float* buffer)
  {
    return is_runnable() ? compute(count, buffer, buffer) : true;
  }
  
  bool configure_stereo(int32_t count, float *impresp, uint32_t imprate);
  bool update_stereo(int32_t count, float *impresp, uint32_t imprate);
  bool compute_stereo(int32_t count, float* input, float* input1, float *output, float *output1);
  bool compute_stereo(int32_t count, float* buffer, float* buffer1)
  {
    return is_runnable() ? compute_stereo(count, buffer, buffer1, buffer, buffer1) : true;
  }
  static void run_static(uint32_t n_samples, GxSimpleConvolver *p, float *output);
  static void run_static(uint32_t n_samples, GxSimpleConvolver *p, float *input, float *output);
  static void run_static_stereo(uint32_t n_samples, GxSimpleConvolver *p, float *output, float *output1);
};


#endif  // SRC_HEADERS_GX_CONVOLVER_H_
