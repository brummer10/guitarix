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

#include "gx_convolver.h"
#include "gx_compiler.h"
#include <string.h>
/****************************************************************
 ** some pieces in this file are copied from jconvolver
 */

#define max(x, y) (((x) > (y)) ? (x) : (y))
/****************************************************************
 ** GxConvolverBase
 */

GxConvolverBase::~GxConvolverBase()
{
  if (is_runnable())
    {
      stop_process();
    }
}

void GxConvolverBase::adjust_values(
  uint32_t audio_size, uint32_t& count, uint32_t& offset,
  uint32_t& delay, uint32_t& ldelay, uint32_t& length,
  uint32_t& size, uint32_t& bufsize)
{

  if (bufsize < count)
    {
      bufsize = count;
    }
  if (bufsize < Convproc::MINPART)
    {
      bufsize = Convproc::MINPART;
    }
  if (offset > audio_size)
    {
      offset = audio_size;
    }
  if (!size)
    {
      if (offset + length > audio_size)
        {

          length = audio_size - offset;
        }
      if (!length)
        {
          length = audio_size - offset;
        }
      size = max(delay, ldelay) + offset + length;
    }
  else
    {
      if (delay > size)
        {
          delay = size;
        }
      if (ldelay > size)
        {
          ldelay = size;
        }
      if (offset > size - max(delay, ldelay))
        {
          offset = size - max(delay, ldelay);
        }
      if (length > size - max(delay, ldelay) - offset)
        {
          length = size - max(delay, ldelay) - offset;

        }
      if (!length)
        {
          length = size - max(delay, ldelay) - offset;
        }
    }
}

bool GxConvolverBase::start(int32_t policy, int32_t priority)
{
  int32_t rc = start_process(priority, policy);
  if (rc != 0)
    {

      return false;
    }
  ready = true;
  return true;
}

bool GxConvolverBase::checkstate()
{
  if (state() == Convproc::ST_WAIT)
    {
      if (check_stop())
        {
          ready = false;
        }
      else
        {
          return false;
        }
    }
  else if (state() == ST_STOP)
    {
      ready = false;
    }
  return true;
}

/****************************************************************
 ** GxSimpleConvolver
 */

class CheckResample
{
private:
  float *vec;
  gx_resample::BufferResampler& resamp;
public:
  CheckResample(gx_resample::BufferResampler& resamp_): vec(0), resamp(resamp_) {}
  float *resample(int32_t *count, float *impresp, uint32_t imprate, uint32_t samplerate)
  {
    if (imprate != samplerate)
      {
        vec = resamp.process(imprate, *count, impresp, samplerate, count);
        if (!vec)
          {
            if (samplerate)
              {
              }
            else
              {
              }
            return 0;
          }
        return vec;
      }
    return impresp;
  }
  ~CheckResample()
  {
    if (vec)
      {
        delete vec;
      }
  }
};

bool GxSimpleConvolver::configure(int32_t count, float *impresp, uint32_t imprate)
{
  //printf("try configure()\n");
  CheckResample r(resamp);
  impresp = r.resample(&count, impresp, imprate, samplerate);
  if (!impresp)
    {
      printf("no impresp\n");
      return false;
    }
  cleanup();
  uint32_t bufsize = buffersize;
  if (bufsize < Convproc::MINPART)
    {
      bufsize = Convproc::MINPART;
    }
#if ZITA_CONVOLVER_VERSION == 4
        if (Convproc::configure(1, 1, count, buffersize,
                                bufsize, Convproc::MAXPART,0.0)) {
            printf("no configure\n");
            return false;
        }        
#else 
  if (Convproc::configure(1, 1, count, buffersize,
                          bufsize, bufsize)) // Convproc::MAXPART
    {
      printf("no configure\n");
      return false;
    }
#endif
  if (impdata_create(0, 0, 1, impresp, 0, count))
    {
      printf("no impdata_create()\n");
      return false;
    }
  //printf("configure()\n");

  return true;
}

bool GxSimpleConvolver::update(int32_t count, float *impresp, uint32_t imprate)
{
  CheckResample r(resamp);
  impresp = r.resample(&count, impresp, imprate, samplerate);
  if (!impresp)
    {
      return false;
    }
#if ZITA_CONVOLVER_VERSION == 4
        impdata_clear(0, 0);
#endif
  if (impdata_update(0, 0, 1, impresp, 0, count))
    {
      return false;
    }
  return true;
}

bool __rt_func GxSimpleConvolver::compute(int32_t count, float* input, float *output)
{
  // printf("try run\n");
  if (state() != Convproc::ST_PROC)
    {
      //printf("state() != ST_PROC\n");
      if (input != output)
        {
          memcpy(output, input, count * sizeof(float));
        }
      if (state() == Convproc::ST_WAIT)
        {
          //printf("state() == ST_WAIT\n");
          check_stop();
        }
      if (state() == ST_STOP)
        {
          //printf("state() == ST_STOP\n");
          ready = false;
        }
      return true;
    }
  int32_t flags = 0;
  if (static_cast<uint32_t>(count) == buffersize)
    {
      memcpy(inpdata(0), input, count * sizeof(float));

      flags = process(sync);

      memcpy(output, outdata(0), count * sizeof(float));
    } else if (static_cast<uint32_t>(count) < buffersize) {
      float in[buffersize];
      memset(in, 0, buffersize * sizeof(float));
      memcpy(in, input, count * sizeof(float));
      memcpy(inpdata(0), in, buffersize * sizeof(float));
      flags = process(sync);
      memcpy(output, outdata(0), count * sizeof(float));
    } else {
      float *in, *out;
      in = inpdata(0);
      out = outdata(0);
      uint32_t b = 0;
      uint32_t c = 1;
      uint32_t d = 0;
      for(int32_t i = 0; i<count; ++i){
        in[b] = input[i];
        if(++b == buffersize) {
          b=0;
          flags = process();
          for(d = 0; d<buffersize; ++d) {
            output[d*c] = out[d];
          }
          ++c;
        }
      }
      if (d*c < static_cast<uint32_t>(count)) {
        uint32_t r = static_cast<uint32_t>(count) - (d*c);          
        printf("convolver missing %u samples", r);
      }
    }
  return flags == 0;
}

void GxSimpleConvolver::run_static(uint32_t n_samples, GxSimpleConvolver *p, float *output)
{
  if (!p->compute((int32_t)n_samples, output))
    printf("convolver didn't run\n");
}

void GxSimpleConvolver::run_static(uint32_t n_samples, GxSimpleConvolver *p, float *input, float *output)
{
  if (!p->compute((int32_t)n_samples, input, output))
    printf("convolver didn't run\n");
}

//////////////stero/////////////////

bool GxSimpleConvolver::configure_stereo(int32_t count, float *impresp, uint32_t imprate)
{
  //printf("try configure()\n");
  CheckResample r(resamp);
  impresp = r.resample(&count, impresp, imprate, samplerate);
  if (!impresp)
    {
      printf("no impresp\n");
      return false;
    }
  cleanup();
  uint32_t bufsize = buffersize;
  if (bufsize < Convproc::MINPART)
    {
      bufsize = Convproc::MINPART;
    }
#if ZITA_CONVOLVER_VERSION == 4
      if (Convproc::configure(2, 2, count, buffersize,
                              bufsize, bufsize,0.0)) // Convproc::MAXPART
        {
          printf("no configure\n");
          return false;
        }
#else 
  if (Convproc::configure(2, 2, count, buffersize,
                          bufsize, bufsize)) // Convproc::MAXPART
    {
      printf("no configure\n");
      return false;
    }
#endif
  if (impdata_create(0, 0, 1, impresp, 0, count) & impdata_create(1, 1, 1, impresp, 0, count))
    {
      printf("no impdata_create()\n");
      return false;
    }
  //printf("configure()\n");

  return true;
}

bool GxSimpleConvolver::update_stereo(int32_t count, float *impresp, uint32_t imprate)
{
  CheckResample r(resamp);
  impresp = r.resample(&count, impresp, imprate, samplerate);
  if (!impresp)
    {
      return false;
    }
#if ZITA_CONVOLVER_VERSION == 4
      impdata_clear(0, 0);
      impdata_clear(1, 1);
#endif
  if (impdata_update(0, 0, 1, impresp, 0, count) & impdata_update(1, 1, 1, impresp, 0, count))
    {
      return false;
    }
  return true;
}

bool __rt_func GxSimpleConvolver::compute_stereo(int32_t count, float* input, float* input1, float *output, float *output1)
{
  // printf("try run\n");
  if (state() != Convproc::ST_PROC)
    {
      //printf("state() != ST_PROC\n");
      if (input != output)
        {
          memcpy(output, input, count * sizeof(float));
          memcpy(output1, input1, count * sizeof(float));
        }
      if (state() == Convproc::ST_WAIT)
        {
          //printf("state() == ST_WAIT\n");
          check_stop();
        }
      if (state() == ST_STOP)
        {
          //printf("state() == ST_STOP\n");
          ready = false;
        }
      return true;
    }
  int32_t flags = 0;
  if (static_cast<uint32_t>(count) == buffersize)
    {
      memcpy(inpdata(0), input, count * sizeof(float));
      memcpy(inpdata(1), input1, count * sizeof(float));

      flags = process(sync);

      memcpy(output, outdata(0), count * sizeof(float));
      memcpy(output1, outdata(1), count * sizeof(float));
    } else {
        float *in, *in1, *out, *out1;
      in = inpdata(0);
      in1 = inpdata(1);
      out = outdata(0);
      out1 = outdata(1);
      uint32_t b = 0;
      uint32_t c = 1;
      for(int32_t i = 0; i<count; ++i){
        in[b] = input[i];
        in1[b] = input1[i];
        if(++b == buffersize) {
          b=0;
          flags = process();
          for(uint32_t d = 0; d<buffersize; ++d) {
            output[d*c] = out[d];
            output1[d*c] = out1[d];
          }
          ++c;
        }
      }
    }
  //printf("run\n");
  return flags == 0;
}

void GxSimpleConvolver::run_static_stereo(uint32_t n_samples, GxSimpleConvolver *p, float *output, float *output1)
{
  if (!p->compute_stereo((int32_t)n_samples, output, output1))
    printf("convolver didn't run\n");
}
