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

#include "gx_resampler.h"
#include <iostream>

namespace gx_resample
{

// copied gcd from (zita) resampler.cc to get ratio_a and ratio_b for
// calculate the correct buffer size resulting from resample
static uint32_t gcd (int32_t a, int32_t b)
{
  if (a == 0) return b;
  if (b == 0) return a;
  while (1)
    {
      if (a > b)
        {
          a = a % b;
          if (a == 0) return b;
          if (a == 1) return 1;
        }
      else
        {
          b = b % a;
          if (b == 0) return a;
          if (b == 1) return 1;
        }
    }
  return 1;
}


int FixedRateResampler::setup(int _inputRate, int _outputRate)
{
    const int qual = 16; // resulting in a total delay of 2*qual (0.7ms @44100)
    inputRate = _inputRate;
    outputRate = _outputRate;
    if (inputRate == outputRate) {
	return 0;
    }
    // upsampler
    int ret = r_up.setup(inputRate, outputRate, 1, qual);
    if (ret) {
	return ret;
    }
    // k == filtlen() == 2 * qual
    // pre-fill with k-1 zeros
    r_up.inp_count = r_up.filtlen() - 1;
    r_up.out_count = 1;
    r_up.inp_data = r_up.out_data = 0;
    r_up.process();
    // downsampler
    ret = r_down.setup(outputRate, inputRate, 1, qual);
    if (ret) {
	return ret;
    }
    // k == filtlen() == 2 * qual * fact
    // pre-fill with k-2 zeros
    r_down.inp_count = r_down.filtlen() - 2;
    r_down.out_count = 1;
    r_down.inp_data = r_down.out_data = 0;
    r_down.process();
    return 0;
}

int FixedRateResampler::up(int count, float *input, float *output)
{
    if (inputRate == outputRate) {
	memcpy(output, input, count*sizeof(float));
	r_down.out_count = count;
	return count;
    }
    r_up.inp_count = count;
    r_down.out_count = count+1; // +1 == trick to drain input
    r_up.inp_data = input;
    int m = max_out_count(count);
    r_up.out_count = m;
    r_up.out_data = output;
    r_up.process();
    assert(r_up.inp_count == 0);
    assert(r_up.out_count <= 1);
    r_down.inp_count = m - r_up.out_count;
    return r_down.inp_count;
}

void FixedRateResampler::down(float *input, float *output)
{
    if (inputRate == outputRate) {
	memcpy(output, input, r_down.out_count*sizeof(float));
	return;
    }
    r_down.inp_data = input;
    r_down.out_data = output;
    r_down.process();
    assert(r_down.inp_count == 0);
    assert(r_down.out_count == 1);
}

void SimpleResampler::setup(int32_t sampleRate, uint32_t factum)
{
  int32_t fact = static_cast<int32_t>(factum);
  int32_t d = gcd(sampleRate, sampleRate*fact);
  ratio_a = sampleRate / d;
  ratio_b = (sampleRate*fact) / d;

  assert(fact <= MAX_UPSAMPLE);
  m_fact = fact;
  const int32_t qual = 16; // resulting in a total delay of 2*qual (0.7ms @44100)
  // upsampler
  r_up.setup(sampleRate, sampleRate*fact, 1, qual);
  // k == inpsize() == 2 * qual
  // pre-fill with k-1 zeros
  r_up.inp_count = r_up.inpsize() - 1;
  r_up.out_count = 1;
  r_up.inp_data = r_up.out_data = 0;
  r_up.process();
  // downsampler
  r_down.setup(sampleRate*fact, sampleRate, 1, qual);
  // k == inpsize() == 2 * qual * fact
  // pre-fill with k-1 zeros
  r_down.inp_count = r_down.inpsize() - 1;
  r_down.out_count = 1;
  r_down.inp_data = r_down.out_data = 0;
  r_down.process();
  // std::cout<<"SimpleResampler::setup "<<sampleRate<<" "<<fact<<std::endl;
}

int32_t SimpleResampler::up(int32_t count, float *input, float *output)
{
  r_up.inp_count = count;
  r_up.inp_data = input;
  int m = get_max_out_size(count);
  r_up.out_count = m;
  r_up.out_data = output;
  r_up.process();
  assert(r_up.inp_count == 0);
  assert(r_up.out_count <= 1);
  r_down.inp_count = m - r_up.out_count;
  return r_down.inp_count;
}

void SimpleResampler::down(int32_t count, float *input, float *output)
{
  r_down.inp_count = count * m_fact;
  r_down.inp_data = input;
  r_down.out_count = count+1; // +1 == trick to drain input
  r_down.out_data = output;
  r_down.process();
  assert(r_down.inp_count == 0);
  assert(r_down.out_count == 1);
}

float *BufferResampler::process(int32_t fs_inp, int32_t ilen, float *input, int32_t fs_outp, int32_t *olen)
{
  int32_t d = gcd(fs_inp, fs_outp);
  int32_t ratio_a = fs_inp / d;
  int32_t ratio_b = fs_outp / d;

  const int32_t qual = 32;
  if (setup(fs_inp, fs_outp, 1, qual) != 0)
    {
      return 0;
    }
  // pre-fill with k/2-1 zeros
  int32_t k = inpsize();
  inp_count = k/2-1;
  inp_data = 0;
  out_count = 1; // must be at least 1 to get going
  out_data = 0;
  if (Resampler::process() != 0)
    {
      return 0;
    }
  inp_count = ilen;
  int32_t nout = out_count = (ilen * ratio_b + ratio_a - 1) / ratio_a;
  inp_data = input;
  float *p = out_data = new float[out_count];
  if (Resampler::process() != 0)
    {
      delete[] p;
      return 0;
    }
  inp_data = 0;
  inp_count = k/2;
  if (Resampler::process() != 0)
    {
      delete[] p;
      return 0;
    }
  assert(inp_count == 0);
  assert(out_count <= 1);
  *olen = nout - out_count;
  //printf("resampled from %i to: %i\n",fs_inp, fs_outp );
  return p;
}

bool StreamingResampler::setup(int32_t srcRate, int32_t dstRate, int32_t nchan)
{
  int32_t d = gcd(srcRate, dstRate);
  ratio_a = srcRate / d;
  ratio_b = dstRate / d;

  const int32_t qual = 32;
  if (Resampler::setup(srcRate, dstRate, nchan, qual) != 0)
    {
      return false;
    }
  inp_count = inpsize()/2-1;
  inp_data = 0;
  out_count = 1; // must be at least 1 to get going
  out_data = 0;
  if (Resampler::process() != 0)
    {
      return false;
    }
  assert(inp_count == 0);
  assert(out_count == 1);
  return true;
}

int32_t StreamingResampler::process(int32_t count, float *input, float *output)
{
  inp_count = count;
  int32_t olen = out_count = get_max_out_size(count);
  inp_data = input;
  out_data = output;
  if (Resampler::process() != 0)
    {
      return 0;
    }
  assert(inp_count == 0);
  return olen - out_count;
}

int32_t StreamingResampler::flush(float *output)
{
  // maximum data written to output:
  // srcRate > dstRate:  ~ 2 * qual
  // srcRate < dstRate:  ~ 2 * qual * dstRate/srcRate
  inp_data = 0;
  inp_count = inpsize()/2;
  out_data = output;
  int32_t olen = out_count = get_max_out_size(inp_count);
  if (Resampler::process() != 0)
    {
      return 0;
    }
  assert(inp_count == 0);
  return olen - out_count;
}

} // namespace gx_resample
