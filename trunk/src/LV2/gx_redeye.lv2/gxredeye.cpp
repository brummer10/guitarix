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

#include <glibmm.h>
#include "gx_common.h"

/****************************************************************
 ** "atomic" value access
 */

inline void atomic_set(volatile int32_t* p, int32_t v)
{
  g_atomic_int_set(p, v);
}

inline int32_t atomic_get(volatile int32_t& p)
{
  return g_atomic_int_get(&p);
}

inline bool atomic_compare_and_exchange(volatile int32_t *p, int32_t oldv, int32_t newv)
{
  return g_atomic_int_compare_and_exchange(p, oldv, newv);
}

template <class T>
inline void atomic_set(T **p, T *v)
{
  g_atomic_pointer_set(p, v);
}

template <class T>
inline void atomic_set_0(T **p)
{
  g_atomic_pointer_set(p, 0);
}

template <class T>
inline T *atomic_get(T*& p)
{
  return static_cast<T*>(g_atomic_pointer_get(&p));
}

template <class T>
inline bool atomic_compare_and_exchange(T **p, T *oldv, T *newv)
{
  return g_atomic_pointer_compare_and_exchange(reinterpret_cast<void* volatile*>(p), oldv, newv);
}

#include "gxredeye.h"
#include "gx_resampler.h"
#include "gx_convolver.h"
namespace gx_redeye {
#include "gx_redeye.h"
#include "impulse_former.h"
#include "ampulse_former.h"
#ifndef __SSE__
#include "noiser.cc"
#endif
#include "cab_data_table.cc"

////////////////////////////// MONO ////////////////////////////////////

class GxPluginMono
{
private:
  // internal stuff
  float*                       output;
  float*                       input;
  uint32_t                     s_rate;
  int32_t                      prio;
  PluginLV2*                   amplifier[AMP_COUNT];
#ifndef __SSE__
  PluginLV2*                   wn;
#endif
  uint32_t                     a_model_;
  uint32_t                     c_model_;
  gx_resample::BufferResampler resamp;
  GxSimpleConvolver            cabconv;
  Impf                         impf;
  gx_resample::BufferResampler resamp1;
  uint32_t                     bufsize;
  LV2_Atom_Sequence*           c_notice;
  LV2_Atom_Sequence*           n_notice;
  float                        cab;

public:
  // LV2 stuff
  LV2_URID_Map*                map;

  void clean();
  inline void run_dsp_mono(uint32_t n_samples);
  void connect_mono(uint32_t port,void* data);
  inline void init_dsp_mono(uint32_t rate, uint32_t bufsize_);
  void set_amp_mono(const LV2_Descriptor* descriptor);
  inline void connect_all_mono_ports(uint32_t port, void* data);
  // constructor
  GxPluginMono() :
    output(NULL),
    input(NULL),
    s_rate(0),
    prio(0),
    a_model_(0), 
    c_model_(0), 
    cabconv(GxSimpleConvolver(resamp)),
    impf(Impf()),
    bufsize(0),
    cab(0)
  {
  };
  // destructor
  ~GxPluginMono()
  {
    cabconv.stop_process();
    cabconv.cleanup();
     };
};

// plugin stuff

void GxPluginMono::set_amp_mono(const LV2_Descriptor*     descriptor)
{

  if (strcmp("http://guitarix.sourceforge.net/plugins/gx_redeye#chump",descriptor->URI)== 0)
    {
      printf("chump\n");
      a_model_ =  0 ;
      c_model_ = 17.0 ;	// 1x8 
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gx_redeye#bigchump",descriptor->URI)== 0)
    {
      printf("bigchump\n");
      a_model_ =  1 ;	
      c_model_ = 1.0 ;	// 2x12
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gx_redeye#vibrochump",descriptor->URI)== 0)
    {
      printf("vibrochump\n");
      a_model_ =  2 ;	
      c_model_ = 1.0 ;	// 2x12
    }
}

void GxPluginMono::init_dsp_mono(uint32_t rate, uint32_t bufsize_)
{
  AVOIDDENORMALS();

  bufsize = bufsize_;
  s_rate = rate;
#ifndef __SSE__
  wn = noiser::plugin();
  wn->set_samplerate(rate, wn);
#endif  
  for(uint32_t i=0; i<AMP_COUNT; i++) {
        amplifier[i] = amp_model[i]();
        amplifier[i]->set_samplerate(static_cast<unsigned int>(rate), amplifier[i]);
    }
  
  if (bufsize )
    {
#ifdef _POSIX_PRIORITY_SCHEDULING
      int priomax = sched_get_priority_max(SCHED_FIFO);
      if ((priomax/2) > 0) prio = priomax/2;
#endif

      CabDesc& cab = *getCabEntry(static_cast<uint32_t>(c_model_)).data;

      cabconv.cab_count = cab.ir_count;
      cabconv.cab_sr = cab.ir_sr;
      cabconv.cab_data = cab.ir_data;
        
      cabconv.set_samplerate(rate);
      cabconv.set_buffersize(bufsize);
      cabconv.configure(cabconv.cab_count, cabconv.cab_data, cabconv.cab_sr);

      float cab_irdata_c[cabconv.cab_count];

      // Here we are at present hard wiring the cab volume so need to experiment
      //impf.compute(cabconv.cab_count, cabconv.cab_data, cab_irdata_c, 10.0*adjust_1x8);
      impf.compute(cabconv.cab_count, cabconv.cab_data, cab_irdata_c, 1.0);
      cabconv.cab_data_new = cab_irdata_c;

      while (!cabconv.checkstate());
      if(!cabconv.start(prio, SCHED_FIFO))
        printf("cabinet convolver disabled\n");

    }
  else
    {
      printf("convolver disabled\n");
    }
}


void GxPluginMono::connect_mono(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case AMP_OUTPUT:
      output = static_cast<float*>(data);
      break;
    case AMP_INPUT:
      input = static_cast<float*>(data);
      break;
    default:
      break;
    }
}

void GxPluginMono::run_dsp_mono(uint32_t n_samples)
{
  if (n_samples< 1) return;
  // run dsp
#ifndef __SSE__
  wn->mono_audio(static_cast<int>(n_samples), input, input, wn);;
#endif
  // run selected tube model
  amplifier[a_model_]->mono_audio(static_cast<int>(n_samples), input, output, amplifier[a_model_]);

  // run selected cabinet convolver
  cabconv.run_static(n_samples, &cabconv, output);

}

void GxPluginMono::connect_all_mono_ports(uint32_t port, void* data)
{
  connect_mono(port,data);
  
  for(uint32_t i=0; i<AMP_COUNT; i++) {
        amplifier[i]->connect_ports(port, data, amplifier[i]);
    }
}

void GxPluginMono::clean()
{
#ifndef __SSE__
  wn->delete_instance(wn);;
#endif
  for(uint32_t i=0; i<AMP_COUNT; i++) {
    amplifier[i]->delete_instance(amplifier[i]);
  }
}
///////////////////////////// LV2 defines //////////////////////////////

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{

  GxPluginMono *self = new GxPluginMono();
  if (!self)
    {
      return NULL;
    }

  const LV2_Options_Option* options  = NULL;
  uint32_t bufsize = 0;
  //printf(" %s\n",descriptor->URI);

  for (int32_t i = 0; features[i]; ++i)
    {
      if (!strcmp(features[i]->URI, LV2_URID__map))
        {
          self->map = (LV2_URID_Map*)features[i]->data;
        }
      else if (!strcmp(features[i]->URI, LV2_OPTIONS__options))
        {
          options = (const LV2_Options_Option*)features[i]->data;
        }
    }
  if (!self->map)
    {
      fprintf(stderr, "Missing feature uri:map.\n");
    }
  else if (!options)
    {
      fprintf(stderr, "Missing feature options.\n");
    }
  else
    {
      LV2_URID bufsz_max = self->map->map(self->map->handle, LV2_BUF_SIZE__maxBlockLength);
      LV2_URID atom_Int = self->map->map(self->map->handle, LV2_ATOM__Int);

      for (const LV2_Options_Option* o = options; o->key; ++o)
        {
          if (o->context == LV2_OPTIONS_INSTANCE &&
              o->key == bufsz_max &&
              o->type == atom_Int)
            {
              bufsize = *(const int32_t*)o->value;
            }
        }

      if (bufsize == 0)
        {
          fprintf(stderr, "No maximum buffer size given.\n");
        }
      printf("using block size: %d\n", bufsize);
    }

  self->set_amp_mono( descriptor);
  self->init_dsp_mono((uint32_t)rate, bufsize);

  return (LV2_Handle)self;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
  GxPluginMono* self = (GxPluginMono*)instance;
  self->connect_all_mono_ports(port, data);
}

static void
activate(LV2_Handle instance)
{

}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  GxPluginMono* self = (GxPluginMono*)instance;
  self->run_dsp_mono(n_samples);
}

static void
deactivate(LV2_Handle instance)
{

}

static void
cleanup(LV2_Handle instance)
{
  GxPluginMono* self = (GxPluginMono*)instance;
  self->clean();
  delete self;
}

//////////////////////////////////////////////////////////////////

static const LV2_Descriptor descriptor =
{
  GXPLUGIN_URI "#chump",
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  NULL
};
static const LV2_Descriptor descriptor1 =
{
  GXPLUGIN_URI "#bigchump",
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  NULL
};
static const LV2_Descriptor descriptor2 =
{
  GXPLUGIN_URI "#vibrochump",
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  NULL
};

} //end namespace gx_redeye

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
  switch (index)
    {
    case 0:
      return &gx_redeye::descriptor;
    case 1:
      return &gx_redeye::descriptor1;
    case 2:
      return &gx_redeye::descriptor2;
    default:
      return NULL;
    }
}
