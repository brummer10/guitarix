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

#ifdef __SSE__
/* On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
   flags to avoid costly denormals */
#ifdef __SSE3__
#include <pmmintrin.h>
inline void AVOIDDENORMALS() {
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
}
#else
#include <xmmintrin.h>
inline void AVOIDDENORMALS() { _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON); }
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
template <int N> inline float faustpower(float x)       {return powf(x, N);}
template <int N> inline double faustpower(double x)     {return pow(x, N);}
template <int N> inline int faustpower(int x) {return faustpower<N/2>(x) * faustpower<N-N/2>(x);}
template <>      inline int faustpower<0>(int x)        {return 1;}
template <>      inline int faustpower<1>(int x)        {return x;}

#include "gxamp.h"
#include "gx_resampler.h"
#include "gx_convolver.h"
#include "gx_amp.h"
#include "gx_tonestack.h"

typedef enum {
  AMP_MASTERGAIN   = 0,
  AMP_PREGAIN,
  AMP_WET_DRY,
  AMP_DRIVE,
  MID,
  BASS,
  TREBLE,
  AMP_OUTPUT,
  AMP_INPUT,
} PortIndex;

struct GXPlugin {
  Tonestack *ts;
  LV2_URID_Map*        map;
  GxAmp *amplifier;
  gx_resample::BufferResampler resamp;
  GxSimpleConvolver *cabconv;
  uint32_t bufsize;
  GXPlugin() {}
};

#include "gx_tonestack.cc"
#include "gx_amp.cc"
#include "gx_convolver.cc"
#include "gx_resampler.cc"

// LV2 defines
static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
  const LV2_Options_Option* options  = NULL;
  LV2_URID_Map*             map      = NULL;
  uint32_t bufsize = 0;

  for (int i = 0; features[i]; ++i) {
    if (!strcmp(features[i]->URI, LV2_URID__map)) {
      map = (LV2_URID_Map*)features[i]->data;
    } else if (!strcmp(features[i]->URI, LV2_OPTIONS__options)) {
      options = (const LV2_Options_Option*)features[i]->data;
    }
  }

  if (!map) {
    fprintf(stderr, "Missing feature uri:map.\n");
  } else if (!options) {
    fprintf(stderr, "Missing feature options.\n");
  } else {
    LV2_URID bufsz_max = map->map(map->handle, LV2_BUF_SIZE__maxBlockLength);
    LV2_URID atom_Int = map->map(map->handle, LV2_ATOM__Int);
  
    for (const LV2_Options_Option* o = options; o->key; ++o) {
      if (o->context == LV2_OPTIONS_INSTANCE &&
        o->key == bufsz_max &&
        o->type == atom_Int) {
        bufsize = *(const int32_t*)o->value;
      }
    }

    if (bufsize == 0) {
      fprintf(stderr, "No maximum buffer size given.\n");
    }

    if (bufsize < 64 || bufsize > 8192 ) {
      fprintf(stderr, "unsupported block-size: %d\n", bufsize);
      bufsize = 0;
    }
    printf("using block size: %d\n", bufsize);
  }

  AVOIDDENORMALS();
  GXPlugin *self = new GXPlugin();
  self->bufsize = bufsize;
  self->amplifier = new GxAmp();
  self->ts = new Tonestack();
  self->amplifier->init_static(rate, self->amplifier);
  self->ts->init_static(rate, self->ts);
    
  self->cabconv = new GxSimpleConvolver(self->resamp);
  self->cabconv->set_samplerate(rate);
  if (bufsize) {
    self->cabconv->set_buffersize(bufsize);
    self->cabconv->configure(cab_data_4x12.ir_count, cab_data_4x12.ir_data,cab_data_4x12.ir_sr);
    self->cabconv->start(0, 0);
  } else {
    printf("convolver disabled\n");
  }
  return (LV2_Handle)self;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
  GXPlugin* self = (GXPlugin*)instance;
  self->amplifier->connect_static(port,data, self->amplifier);
  self->ts->connect_static(port,data, self->ts);
}

static void
activate(LV2_Handle instance)
{

}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  GXPlugin* self = (GXPlugin*)instance;
  self->amplifier->run_static(n_samples, self->amplifier, instance);
}

static void
deactivate(LV2_Handle instance)
{

}

static void
cleanup(LV2_Handle instance)
{
  GXPlugin* self = (GXPlugin*)instance;
  self->cabconv->stop_process();
  delete self->amplifier;
  delete self->ts;
  delete self->cabconv;
  delete self; 
}

const void*
extension_data(const char* uri)
{
  return NULL;
}

static const LV2_Descriptor descriptor = {
  GXPLUGIN_URI,
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  extension_data
};

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
  switch (index) {
  case 0:
    return &descriptor;
  default:
    return NULL;
  }
}
