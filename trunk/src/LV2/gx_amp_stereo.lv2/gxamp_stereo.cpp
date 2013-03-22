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
#include <glibmm.h>
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


#include "gxamp_stereo.h"
#include "gx_resampler.h"
#include "gx_convolver.h"
#include "gx_tonestack_stereo.h"
#include "gx_amp_stereo.h"
#include "impulse_former.h"
#include "ampulse_former.h"

#include "cab_data_table.cc"

////////////////////////////// MONO ////////////////////////////////////

class GxPluginStereo
{
private:
  // internal stuff
  float*                       output;
  float*                       output1;
  float*                       input;
  float*                       input1;
  uint32_t                     s_rate;
  int32_t                      prio;
  PluginLV2*                   amplifier[AMP_COUNT];
  PluginLV2*                   tonestack[TS_COUNT];
  float*                       a_model;
  uint32_t                     a_model_;
  float*                       t_model;
  uint32_t                     t_model_;
  gx_resample::BufferResampler resamp;
  GxSimpleConvolver            cabconv;
  Impf                         impf;
  gx_resample::BufferResampler resamp1;
  GxSimpleConvolver            ampconv;
  Ampf                         ampf;
  uint32_t                     bufsize;
  LV2_Atom_Sequence*           c_notice;
  LV2_Atom_Sequence*           n_notice;
  float                        *clevel;
  float                        clevel_;
  float                        cab;
  float                        *c_model;
  float                        c_model_;
  float                        c_old_model_;
  
  bool cab_changed()
  {
    return abs(cab - (clevel_ + c_model_)) > 0.1;
  }
  void update_cab()
  {
    cab = (clevel_ + c_model_);
    c_old_model_ = c_model_;
  }
  bool change_cab()
  {
    return abs(c_old_model_ - c_model_) > 0.1;
  }
  float                        *alevel;
  float                        alevel_;
  float                        pre;
  bool pre_changed()
  {
    return abs(pre - alevel_) > 0.1;
  }
  void update_pre()
  {
    pre = (alevel_);
  }
  float                        val;
  bool val_changed()
  {
    return abs(val - ((*alevel) + (*clevel) + (*c_model))) > 0.1;
  }
  void update_val()
  {
    val = (alevel_) + (clevel_) + (c_model_);
  }
  bool                         doit;
  volatile int32_t             schedule_wait;

public:
  // LV2 stuff
  LV2_URID_Map*                map;
  LV2_Worker_Schedule*         schedule;

  void clean();
  inline void run_dsp_stereo(uint32_t n_samples);
  void connect_stereo(uint32_t port,void* data);
  inline void init_dsp_stereo(uint32_t rate, uint32_t bufsize_);
  inline void do_work_stereo();
  inline void connect_all_stereo_ports(uint32_t port, void* data);
  // constructor
  GxPluginStereo() :
    output(NULL),
    input(NULL),
    s_rate(0),
    prio(0),
    a_model(NULL),
    a_model_(0), 
    t_model(NULL),
    t_model_(1),
    cabconv(GxSimpleConvolver(resamp)),
    impf(Impf()),
    ampconv(GxSimpleConvolver(resamp1)),
    ampf(Ampf()),
    bufsize(0),
    clevel(NULL),
    clevel_(0),
    cab(0),
    c_model(NULL),
    c_model_(0),
    c_old_model_(0),
    alevel(NULL),
    alevel_(0),
    pre(0),
    val(0)
  {
    atomic_set(&schedule_wait,0);
  };
  // destructor
  ~GxPluginStereo()
  {
    cabconv.stop_process();
    cabconv.cleanup();
    ampconv.stop_process();
    ampconv.cleanup();
  };
};

// plugin stuff

void GxPluginStereo::do_work_stereo()
{
  if (cab_changed())
    {
      if (cabconv.is_runnable())
        {
          cabconv.set_not_runnable();
          cabconv.stop_process();
        }
      // selected cabinet have changed?
      if (change_cab())
      {
        cabconv.cleanup();
        CabDesc& cab = *getCabEntry(static_cast<uint32_t>(c_model_)).data;
        cabconv.cab_count = cab.ir_count;
        cabconv.cab_sr = cab.ir_sr;
        cabconv.cab_data = cab.ir_data;
        
        cabconv.set_samplerate(s_rate);
        cabconv.set_buffersize(bufsize);
        cabconv.configure_stereo(cabconv.cab_count, cabconv.cab_data, cabconv.cab_sr);
        //printf("cabconv.changed.\n");
      }
      float cab_irdata_c[cabconv.cab_count];
      float adjust_1x8 = 1;
      if ( c_model_ == 17.0) adjust_1x8 = 0.5;
      impf.compute(cabconv.cab_count, cabconv.cab_data, cab_irdata_c, (clevel_ * adjust_1x8));
      cabconv.cab_data_new = cab_irdata_c;
      while (!cabconv.checkstate());
      if (!cabconv.update_stereo(cabconv.cab_count, cabconv.cab_data_new, cabconv.cab_sr))
        printf("cabconv.update fail.\n");
      if(!cabconv.start(prio, SCHED_FIFO))
        printf("cabinet convolver disabled\n");
      update_cab();
      //printf("cabinet convolver updated\n");
    }
  if (pre_changed())
    {
      if (ampconv.is_runnable())
        {
          ampconv.set_not_runnable();
          ampconv.stop_process();
        }
      float pre_irdata_c[contrast_ir_desc.ir_count];
      ampf.compute(contrast_ir_desc.ir_count,contrast_ir_desc.ir_data, pre_irdata_c, alevel_);
      while (!ampconv.checkstate());
      if (!ampconv.update_stereo(contrast_ir_desc.ir_count, pre_irdata_c, contrast_ir_desc.ir_sr))
        printf("ampconv.update fail.\n");
      if(!ampconv.start(prio, SCHED_FIFO))
        printf("presence convolver disabled\n");
      update_pre();
      //printf("presence convolver updated\n");
    }
  update_val();
  atomic_set(&schedule_wait,0);
}

void GxPluginStereo::init_dsp_stereo(uint32_t rate, uint32_t bufsize_)
{
  AVOIDDENORMALS();

  bufsize = bufsize_;
  s_rate = rate;
  
  for(uint32_t i=0; i<AMP_COUNT; i++) {
        amplifier[i] = amp_model[i]();
        amplifier[i]->set_samplerate(static_cast<unsigned int>(rate), amplifier[i]);
    }
  for(uint32_t i=0; i<TS_COUNT; i++) {
        tonestack[i] = tonestack_model[i]();
        tonestack[i]->set_samplerate(static_cast<unsigned int>(rate), tonestack[i]);
    }
  
  if (bufsize )
    {
#ifdef _POSIX_PRIORITY_SCHEDULING
      int priomax = sched_get_priority_max(SCHED_FIFO);
      if ((priomax/2) > 0) prio = priomax/2;
#endif
      // set cabinet data
      CabDesc& cab = *getCabEntry(static_cast<uint32_t>(c_model_)).data;
      cabconv.cab_count = cab.ir_count;
      cabconv.cab_sr = cab.ir_sr;
      cabconv.cab_data = cab.ir_data;
        
      cabconv.set_samplerate(rate);
      cabconv.set_buffersize(bufsize);
      cabconv.configure_stereo(cabconv.cab_count, cabconv.cab_data, cabconv.cab_sr);
      while (!cabconv.checkstate());
      if(!cabconv.start(prio, SCHED_FIFO))
        printf("cabinet convolver disabled\n");

      ampconv.set_samplerate(rate);
      ampconv.set_buffersize(bufsize);
      ampconv.configure_stereo(contrast_ir_desc.ir_count, contrast_ir_desc.ir_data, contrast_ir_desc.ir_sr);
      while (!ampconv.checkstate());
      if(!ampconv.start(prio, SCHED_FIFO))
        printf("presence convolver disabled\n");
    }
  else
    {
      printf("convolver disabled\n");
    }
}


void GxPluginStereo::connect_stereo(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case CLevel:
      clevel = static_cast<float*>(data);
      break;
    case ALevel:
      alevel = static_cast<float*>(data);
      break;
    case AMP_CONTROL:
      c_notice = (LV2_Atom_Sequence*)data;
      break;
    case AMP_NOTIFY:
      n_notice = (LV2_Atom_Sequence*)data;
      break;
    case MODEL:
      a_model =  static_cast<float*>(data);
      break;
    case T_MODEL:
      t_model =  static_cast<float*>(data);
      break;
    case C_MODEL:
      c_model =  static_cast<float*>(data);
      break;
    case AMP_OUTPUT:
      output = static_cast<float*>(data);
      break;
    case AMP_OUTPUT1:
      output1 = static_cast<float*>(data);
      break;
    case AMP_INPUT:
      input = static_cast<float*>(data);
      break;
    case AMP_INPUT1:
      input1 = static_cast<float*>(data);
      break;
    default:
      break;
    }
}

void GxPluginStereo::run_dsp_stereo(uint32_t n_samples)
{
  // run dsp
  // run selected tube model
  a_model_ = static_cast<uint32_t>(*(a_model));
  amplifier[a_model_]->stereo_audio(static_cast<int>(n_samples), input, input1, output, output1, amplifier[a_model_]);
  // run presence convolver
  ampconv.run_static_stereo(n_samples, &ampconv, output, output1);
  // run selected tonestack
  t_model_ = static_cast<uint32_t>(*(t_model));
  tonestack[t_model_]->stereo_audio(static_cast<int>(n_samples), output, output1, output, output1, tonestack[t_model_]);
  // run selected cabinet convolver
  cabconv.run_static_stereo(n_samples, &cabconv, output, output1);

  // work ?
  if (!atomic_get(schedule_wait) && val_changed())
    {
      clevel_ = (*clevel);
      alevel_ = (*alevel);
      c_model_= (*c_model);
      atomic_set(&schedule_wait,1);
      schedule->schedule_work(schedule->handle, sizeof(bool), &doit);
    }
}

void GxPluginStereo::connect_all_stereo_ports(uint32_t port, void* data)
{
  connect_stereo(port,data);
  
  for(uint32_t i=0; i<AMP_COUNT; i++) {
        amplifier[i]->connect_ports(port, data, amplifier[i]);
    }
  for(uint32_t i=0; i<TS_COUNT; i++) {
        tonestack[i]->connect_ports(port, data, tonestack[i]);
    }
}

void GxPluginStereo::clean()
{
  for(uint32_t i=0; i<AMP_COUNT; i++) {
    amplifier[i]->delete_instance(amplifier[i]);
  }
  for(uint32_t i=0; i<TS_COUNT; i++) {
    tonestack[i]->delete_instance(tonestack[i]);
  }
}
///////////////////////////// LV2 defines //////////////////////////////

static LV2_Worker_Status
work(LV2_Handle                  instance,
     LV2_Worker_Respond_Function respond,
     LV2_Worker_Respond_Handle   handle,
     uint32_t                    size,
     const void*                 data)
{
  GxPluginStereo* self = (GxPluginStereo*)instance;
  self->do_work_stereo();
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


static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{

  GxPluginStereo *self = new GxPluginStereo();
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
      printf("using block size: %d\n", bufsize);
    }
  self->init_dsp_stereo((uint32_t)rate, bufsize);

  return (LV2_Handle)self;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
  GxPluginStereo* self = (GxPluginStereo*)instance;
  self->connect_all_stereo_ports(port, data);
}

static void
activate(LV2_Handle instance)
{

}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  GxPluginStereo* self = (GxPluginStereo*)instance;
  self->run_dsp_stereo(n_samples);
}

static void
deactivate(LV2_Handle instance)
{

}

static void
cleanup(LV2_Handle instance)
{
  GxPluginStereo* self = (GxPluginStereo*)instance;
  self->clean();
  delete self;
}

//////////////////////////////////////////////////////////////////

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
  GXPLUGIN_URI "#GUITARIX_ST",
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
    default:
      return NULL;
    }
}
