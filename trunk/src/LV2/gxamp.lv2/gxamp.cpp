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
#include <glib.h>

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

/****************************************************************
 ** "atomic" value access
 */

inline void atomic_set(volatile int32_t* p, int32_t v)
{
  g_atomic_int_set(p, v);
}

inline int atomic_get(volatile int32_t& p)
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



class GXPlugin;

#include "gxamp.h"
#include "gx_resampler.h"
#include "gx_convolver.h"
#include "gx_tonestack.h"
#include "gx_amp.h"
#include "impulse_former.h"
#include "ampulse_former.h"


class GXPlugin
{
private:
  // internal stuff
  float*                       output;
  float*                       input;
  uint32_t                     tubesel;
  Tonestack                    ts;
  GxAmp                        amplifier;
  gx_resample::BufferResampler resamp;
  GxSimpleConvolver            cabconv;
  Impf                         impf;
  gx_resample::BufferResampler resamp1;
  GxSimpleConvolver            ampconv;
  Ampf                         ampf;
  uint32_t                     bufsize;
  LV2_Atom_Sequence*           c_notice;
  LV2_Atom_Sequence*           n_notice;
  volatile int32_t             schedule_wait;

public:
  // LV2 stuff

  LV2_URID_Map*                map;
  LV2_Atom_Forge               forge;
  GXPluginURIs                 uris;
  LV2_Atom_Forge_Frame         notify_frame;
  LV2_Worker_Schedule*         schedule;

  void set_tubesel(const LV2_Descriptor* descriptor);
  inline void run_dsp(uint32_t n_samples);
  void connect(uint32_t port,void* data);
  inline void init_dsp(uint32_t rate, uint32_t bufsize_);
  inline void do_work(const LV2_Atom_Object* obj, GXPluginURIs* uris);
  inline void connect_all_ports(uint32_t port, void* data);

  GXPlugin() :
    output(NULL),
    input(NULL),
    tubesel(0),
    ts(Tonestack()),
    amplifier(GxAmp()),
    cabconv(GxSimpleConvolver(resamp)),
    impf(Impf()),
    ampconv(GxSimpleConvolver(resamp1)),
    ampf(Ampf()),
    bufsize(0)
  {
    atomic_set(&schedule_wait,false);
  };

  ~GXPlugin()
  {
    cabconv.stop_process();
    ampconv.stop_process();
  };
};

#include "cab_data.cc"
#include "gx_tonestack.cc"
#include "gx_amp.cc"
#include "impulse_former.cc"
#include "ampulse_former.cc"

void GXPlugin::do_work(const LV2_Atom_Object* obj, GXPluginURIs* uris)
{
  if (obj->body.otype == uris->gx_cab)
    {
      if (cabconv.is_runnable()) 
        {
          cabconv.set_not_runnable();
          cabconv.stop_process();
        }
      float cab_irdata_c[cabconv.cab_count];
      impf.compute(cabconv.cab_count, cabconv.cab_data, cab_irdata_c);
      cabconv.cab_data_new = cab_irdata_c;
      while (!cabconv.checkstate());
      if (!cabconv.update(cabconv.cab_count, cabconv.cab_data_new, cabconv.cab_sr))
        printf("cabconv.update fail.\n");
      printf("worker 1 done.\n");
      if(!cabconv.start(0, SCHED_FIFO))
        printf("cabinet convolver disabled\n");
    }
  else if (obj->body.otype == uris->gx_pre)
    {
      if (ampconv.is_runnable()) 
        {
          ampconv.set_not_runnable();
          ampconv.stop_process();
        }
      //printf("worker run. %d id= %d type= %d\n", obj->body.otype, obj->body.id, obj->atom.type);
      float pre_irdata_c[contrast_ir_desc.ir_count];
      ampf.compute(contrast_ir_desc.ir_count,contrast_ir_desc.ir_data, pre_irdata_c);
      while (!ampconv.checkstate());
      if (!ampconv.update(contrast_ir_desc.ir_count, pre_irdata_c, contrast_ir_desc.ir_sr))
        printf("cabconv.update fail.\n");
      printf("worker 2 done.\n");
      if(!ampconv.start(0, SCHED_FIFO))
        printf("cabinet convolver disabled\n");
    }
  printf("worker thread is running.\n");
  atomic_set(&schedule_wait,false);
}

void GXPlugin::set_tubesel(const LV2_Descriptor*     descriptor)
{
  if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#12ax7",descriptor->URI)== 0)
    {
      printf("12ax7\n");
      _a_ptr = &GxAmp::run_12ax7;
      _t_ptr = &Tonestack::run;
      cabconv.cab_count = cab_data_4x12.ir_count;
      cabconv.cab_sr = cab_data_4x12.ir_sr;
      cabconv.cab_data = cab_data_4x12.ir_data;
      tubesel  = 1;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#12AT7",descriptor->URI)== 0)
    {
      printf("12AT7\n");
      _a_ptr = &GxAmp::run_12AT7;
      _t_ptr = &Tonestack::run_soldano;
      cabconv.cab_count = cab_data_AC30.ir_count;
      cabconv.cab_sr = cab_data_AC30.ir_sr;
      cabconv.cab_data = cab_data_AC30.ir_data;
      tubesel  = 2;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#6C16",descriptor->URI)== 0)
    {
      printf("6C16\n");
      _a_ptr = &GxAmp::run_6C16;
      _t_ptr = &Tonestack::run_bassman;
      cabconv.cab_count = cab_data_1x15.ir_count;
      cabconv.cab_sr =  cab_data_1x15.ir_sr;
      cabconv.cab_data = cab_data_1x15.ir_data;
      tubesel  = 3;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#6V6",descriptor->URI)== 0)
    {
      printf("6V6\n");
      _a_ptr = &GxAmp::run_6V6;
      _t_ptr = &Tonestack::run_soldano;
      cabconv.cab_count = cab_data_mesa.ir_count;
      cabconv.cab_sr = cab_data_mesa.ir_sr;
      cabconv.cab_data = cab_data_mesa.ir_data;
      tubesel  = 4;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#6DJ8",descriptor->URI)== 0)
    {
      printf("6DJ8\n");
      _a_ptr = &GxAmp::run_6DJ8;
      _t_ptr = &Tonestack::run_ampeg;
      cabconv.cab_count = cab_data_HighGain.ir_count;
      cabconv.cab_sr = cab_data_HighGain.ir_sr;
      cabconv.cab_data = cab_data_HighGain.ir_data;
      tubesel  = 5;
    }
  else
    {
      _a_ptr = &GxAmp::run_12ax7;
      _t_ptr = &Tonestack::run;
      cabconv.cab_count = cab_data_4x12.ir_count;
      cabconv.cab_sr = cab_data_4x12.ir_sr;
      cabconv.cab_data = cab_data_4x12.ir_data;
      tubesel  = 0;
    }
}

void GXPlugin::init_dsp(uint32_t rate, uint32_t bufsize_)
{
  AVOIDDENORMALS();

  bufsize = bufsize_;
  amplifier.init_static(rate, &amplifier);
  ts.init_static(rate, &ts);
  impf.init_static(rate, &impf);
  ampf.init_static(rate, &ampf);

  if (bufsize )
    {
      cabconv.set_samplerate(rate);
      cabconv.set_buffersize(bufsize);
      cabconv.configure(cabconv.cab_count, cabconv.cab_data, cabconv.cab_sr);
      if(!cabconv.start(0, SCHED_FIFO))
        printf("cabinet convolver disabled\n");

      ampconv.set_samplerate(rate);
      ampconv.set_buffersize(bufsize);
      ampconv.configure(contrast_ir_desc.ir_count, contrast_ir_desc.ir_data, contrast_ir_desc.ir_sr);
      if(!ampconv.start(0, SCHED_FIFO))
        printf("presence convolver disabled\n");
    }
  else
    {
      printf("convolver disabled\n");
    }
}


void GXPlugin::connect(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case AMP_MASTERGAIN:
      break;
    case AMP_PREGAIN:
      break;
    case AMP_WET_DRY:
      break;
    case AMP_DRIVE:
      break;
    case MID:
      break;
    case BASS:
      break;
    case TREBLE:
      break;
    case CLevel:
      break;
    case ALevel:
      break;
    case AMP_OUTPUT:
      output = (float*)data;
      break;
    case AMP_INPUT:
      input = (float*)data;
      break;
    case AMP_CONTROL:
      c_notice = (LV2_Atom_Sequence*)data;
      break;
    case AMP_NOTIFY:
      n_notice = (LV2_Atom_Sequence*)data;
      break;
    }

}

void GXPlugin::run_dsp(uint32_t n_samples)
{
  /* Set up forge to write directly to notify output port. */
  const uint32_t notify_capacity = n_notice->atom.size;
  lv2_atom_forge_set_buffer(&forge,
                            (uint8_t*)n_notice,
                            notify_capacity);

  /* Start a sequence in the notify output port. */
  lv2_atom_forge_sequence_head(&forge, &notify_frame, 0);

  /* Read incoming events if scheduler is free*/
  if (!atomic_get(schedule_wait))
    {
      LV2_ATOM_SEQUENCE_FOREACH(c_notice, ev)
      {
        atomic_set(&schedule_wait,true);
        schedule->schedule_work(schedule->handle,
                                lv2_atom_total_size(&ev->body), &ev->body);
      }
    }
  // run dsp
  amplifier.run_static(n_samples, input, output, &amplifier);
  ampconv.run_static(n_samples, &ampconv, output);
  ts.run_static(n_samples, &ts, output);
  cabconv.run_static(n_samples, &cabconv, output);
}

void GXPlugin::connect_all_ports(uint32_t port, void* data)
{
  connect(port,data);
  amplifier.connect_static(port,data, &amplifier);
  ts.connect_static(port,data, &ts);
  impf.connect_static(port,data, &impf);
  ampf.connect_static(port,data, &ampf);
}

static LV2_Worker_Status
work(LV2_Handle                  instance,
     LV2_Worker_Respond_Function respond,
     LV2_Worker_Respond_Handle   handle,
     uint32_t                    size,
     const void*                 data)
{
  GXPlugin* self = (GXPlugin*)instance;
  GXPluginURIs* uris        = &self->uris;
  const LV2_Atom_Object* obj = (LV2_Atom_Object*)data;
  self->do_work(obj, uris);
  return LV2_WORKER_SUCCESS;
}

static LV2_Worker_Status
work_response(LV2_Handle  instance,
              uint32_t    size,
              const void* data)
{
  printf("worker respose.\n");
  return LV2_WORKER_SUCCESS;
}

// LV2 defines
static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
  GXPlugin *self = new GXPlugin();
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
      else if (!strcmp(features[i]->URI, LV2_WORKER__schedule))
        {
          self->schedule = (LV2_Worker_Schedule*)features[i]->data;
        }
      else if (!strcmp(features[i]->URI, LV2_OPTIONS__options))
        {
          options = (const LV2_Options_Option*)features[i]->data;
        }
    }
  if (!self->schedule)
    {
      fprintf(stderr, "Missing feature work:schedule.\n");
      delete self;
      return NULL;
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

      //if (bufsize < 64 || bufsize > 8192 ) {
      //  fprintf(stderr, "unsupported block-size: %d\n", bufsize);
      //  bufsize = 0;
      //}
      printf("using block size: %d\n", bufsize);
    }

  LV2_URID_Map*             map      = self->map;
  map_gx_uris(map, &self->uris);
  lv2_atom_forge_init(&self->forge, self->map);
  self->set_tubesel( descriptor);
  self->init_dsp((uint32_t)rate, bufsize);

  return (LV2_Handle)self;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
  GXPlugin* self = (GXPlugin*)instance;
  self->connect_all_ports(port, data);
}

static void
activate(LV2_Handle instance)
{

}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  GXPlugin* self = (GXPlugin*)instance;
  self->run_dsp(n_samples);
}

static void
deactivate(LV2_Handle instance)
{

}

static void
cleanup(LV2_Handle instance)
{
  GXPlugin* self = (GXPlugin*)instance;

  delete self;
}

const void*
extension_data(const char* uri)
{
  static const LV2_Worker_Interface worker = { work, work_response, NULL };
  if (!strcmp(uri, LV2_WORKER__interface))
    {
      return &worker;
    }
  return NULL;
}

static const LV2_Descriptor descriptor =
{
  GXPLUGIN_URI "#12ax7",
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  extension_data
};

static const LV2_Descriptor descriptor1 =
{
  GXPLUGIN_URI "#12AT7",
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  extension_data
};
static const LV2_Descriptor descriptor2 =
{
  GXPLUGIN_URI "#6C16",
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  extension_data
};
static const LV2_Descriptor descriptor3 =
{
  GXPLUGIN_URI "#6V6",
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  extension_data
};
static const LV2_Descriptor descriptor4 =
{
  GXPLUGIN_URI "#6DJ8",
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
  switch (index)
    {
    case 0:
      return &descriptor;
    case 1:
      return &descriptor1;
    case 2:
      return &descriptor2;
    case 3:
      return &descriptor3;
    case 4:
      return &descriptor4;
    default:
      return NULL;
    }
}
