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

#include "gxts9.h"
#include "ts9sim.cc"

////////////////////////////// MONO ////////////////////////////////////

class Gxts9
{
private:
  // internal stuff
  float*                       output;
  float*                       input;
  ts9sim                       ts9;

public:

  inline void run_dsp_mono(uint32_t n_samples);
  void connect_mono(uint32_t port,void* data);
  inline void init_dsp_mono(uint32_t rate);
  inline void connect_all_mono_ports(uint32_t port, void* data);
  void activate_f();
  // constructor
  Gxts9() :
    output(NULL),
    input(NULL),
    ts9(ts9sim())
  {
  };
  // destructor
  ~Gxts9()
  {
  };
};

// plugin stuff

void Gxts9::init_dsp_mono(uint32_t rate)
{
  AVOIDDENORMALS();
  ts9.init_static(rate, &ts9);
}

void Gxts9::connect_mono(uint32_t port,void* data)
{
  switch ((PortIndex)port)
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

void Gxts9::activate_f()
{
    ts9.clear_state_static(&ts9);
}

void Gxts9::run_dsp_mono(uint32_t n_samples)
{
  if (n_samples< 1) return;
  // run dsp
  ts9.run_static(n_samples, input, output, &ts9);
}

void Gxts9::connect_all_mono_ports(uint32_t port, void* data)
{
  connect_mono(port,data);
  ts9.connect_static(port,data, &ts9);
}

///////////////////////////// LV2 defines //////////////////////////////

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{

  Gxts9 *self = new Gxts9();
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
  Gxts9* self = (Gxts9*)instance;
  self->connect_all_mono_ports(port, data);
}

static void
activate(LV2_Handle instance)
{
  Gxts9* self = (Gxts9*)instance;
  self->activate_f();
}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  Gxts9* self = (Gxts9*)instance;
  self->run_dsp_mono(n_samples);
}

static void
cleanup(LV2_Handle instance)
{
  Gxts9* self = (Gxts9*)instance;
  delete self;
}

//////////////////////////////////////////////////////////////////

static const LV2_Descriptor descriptor =
{
  GXPLUGIN_URI "#ts9sim",
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
