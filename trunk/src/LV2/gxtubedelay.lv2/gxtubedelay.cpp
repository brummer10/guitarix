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
// faust support
#define FAUSTFLOAT float
#ifndef N_
#define N_(String) (String)
#endif

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

#include "gxtubedelay.h"
#include "gx_tubedelay.cc"

////////////////////////////// MONO ////////////////////////////////////

class GxTubeDelay
{
private:
  // internal stuff
  float*                       output;
  float*                       input;
  PluginLV2*			tubedelay;
public:

  void clean();
  inline void run_dsp_mono(uint32_t n_samples);
  void connect_mono(uint32_t port,void* data);
  inline void init_dsp_mono(uint32_t rate);
  inline void connect_all_mono_ports(uint32_t port, void* data);
  void activate_f();
   // constructor
  GxTubeDelay() :
    output(NULL),
    input(NULL)
  {
  };
  // destructor
  ~GxTubeDelay()
  {
  };
};

// plugin stuff

void GxTubeDelay::init_dsp_mono(uint32_t rate)
{
  AVOIDDENORMALS();
   std::cout << "Init SR = "<< rate << std::endl;
  tubedelay = tubedelay::plugin() ;
  tubedelay->set_samplerate(static_cast<unsigned int>(rate), tubedelay );
}

void GxTubeDelay::connect_mono(uint32_t port,void* data)
{
 //  std::cout << "connect_mpno " << std::endl;
 //std::cout << "port = " << port << std::endl;
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

void GxTubeDelay::activate_f()
{
//   std::cout << "activate_f" << std::endl;
    tubedelay->clear_state(tubedelay);
}

void GxTubeDelay::run_dsp_mono(uint32_t n_samples)
{
  // run dsp
  //std::cout << "run_dsp"<< std::endl;

  tubedelay->mono_audio(static_cast<int>(n_samples), input, output, tubedelay);
}

void GxTubeDelay::connect_all_mono_ports(uint32_t port, void* data)
{
  connect_mono(port,data);
  tubedelay->connect_ports(port,data, tubedelay);
}


void GxTubeDelay::clean()
{
    tubedelay->delete_instance(tubedelay);
}


///////////////////////////// LV2 defines //////////////////////////////

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{

  GxTubeDelay *self = new GxTubeDelay();
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
  GxTubeDelay* self = (GxTubeDelay*)instance;
  self->connect_all_mono_ports(port, data);
}

static void
activate(LV2_Handle instance)
{
 
}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  GxTubeDelay* self = (GxTubeDelay*)instance;
  self->run_dsp_mono(n_samples);
}

static void
cleanup(LV2_Handle instance)
{
  GxTubeDelay* self = (GxTubeDelay*)instance;
  self->clean();
  delete self;
}

//////////////////////////////////////////////////////////////////

static const LV2_Descriptor descriptor =
{
  GXPLUGIN_URI "#tubedelay",
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
