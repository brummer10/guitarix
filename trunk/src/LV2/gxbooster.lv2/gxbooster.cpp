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

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <unistd.h>

#ifdef __SSE__
/* On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
   flags to avoid costly denormals */
#ifdef __SSE3__
#include <pmmintrin.h>
inline void AVOIDDENORMALS()
{
  _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
  _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
}
#else
#include <xmmintrin.h>
inline void AVOIDDENORMALS()
{
  _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
}
#endif //__SSE3__

#else
inline void AVOIDDENORMALS() {}
#endif //__SSE__

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
template <int32_t N> inline float faustpower(float x)
{
  return powf(x, N);
}
template <int32_t N> inline double faustpower(double x)
{
  return pow(x, N);
}
template <int32_t N> inline int32_t faustpower(int32_t x)
{
  return faustpower<N/2>(x) * faustpower<N-N/2>(x);
}
template <>      inline int32_t faustpower<0>(int32_t x)
{
  return 1;
}
template <>      inline int32_t faustpower<1>(int32_t x)
{
  return x;
}

#include "gxbooster.h"
#include "bassbooster.cc"
#include "highbooster.cc"

////////////////////////////// MONO ////////////////////////////////////

class Gxbooster
{
private:
  // internal stuff
  float*                       output;
  float*                       input;
  BassBooster                  bb;
  HighBooster                  hb;
public:

  inline void run_dsp_mono(uint32_t n_samples);
  void connect_mono(uint32_t port,void* data);
  inline void init_dsp_mono(uint32_t rate);
  inline void connect_all_mono_ports(uint32_t port, void* data);
  void activate_f();
   // constructor
  Gxbooster() :
    output(NULL),
    input(NULL),
    bb(BassBooster()),
    hb(HighBooster())
  {
  };
  // destructor
  ~Gxbooster()
  {
  };
};

// plugin stuff

void Gxbooster::init_dsp_mono(uint32_t rate)
{
  AVOIDDENORMALS();
  bb.init_static(rate, &bb);
  hb.init_static(rate, &hb);
}

void Gxbooster::connect_mono(uint32_t port,void* data)
{
  switch ((EffectPortIndex)port)
    {
    case EFFECTS_OUTPUT:
      output = static_cast<float*>(data);
      break;
    case EFFECTS_INPUT:
      input = static_cast<float*>(data);
      break;
    default:
      break;
    }
}

void Gxbooster::activate_f()
{
    bb.clear_state_static(&bb);
    hb.clear_state_static(&hb);
}

void Gxbooster::run_dsp_mono(uint32_t n_samples)
{
  if (n_samples< 1) return;
  // run dsp
  bb.run_static(n_samples, input, output, &bb);
  hb.run_static(n_samples, output, output, &hb);
}

void Gxbooster::connect_all_mono_ports(uint32_t port, void* data)
{
  connect_mono(port,data);
  bb.connect_static(port,data, &bb);
  hb.connect_static(port,data, &hb);
}

///////////////////////////// LV2 defines //////////////////////////////

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{

  Gxbooster *self = new Gxbooster();
  if (!self)
    {
      return NULL;
    }

  self->init_dsp_mono((uint32_t)rate);

  return (LV2_Handle)self;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
  Gxbooster* self = (Gxbooster*)instance;
  self->connect_all_mono_ports(port, data);
}

static void
activate(LV2_Handle instance)
{
  Gxbooster* self = (Gxbooster*)instance;
  self->activate_f();
}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  Gxbooster* self = (Gxbooster*)instance;
  self->run_dsp_mono(n_samples);
}

static void
cleanup(LV2_Handle instance)
{
  Gxbooster* self = (Gxbooster*)instance;
  delete self;
}

//////////////////////////////////////////////////////////////////

static const LV2_Descriptor descriptor =
{
  GXPLUGIN_URI "#booster",
  instantiate,
  connect_port,
  activate,
  run,
  NULL,
  cleanup,
  NULL
};

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
  switch (index)
    {
    case 0:
      return &descriptor;
    default:
      return NULL;
    }
}
