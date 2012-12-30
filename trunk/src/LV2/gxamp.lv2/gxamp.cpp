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


#include "gxamp.h"
#include "gx_resampler.h"
#include "gx_convolver.h"
#include "gx_tonestack.h"
#include "gx_amp.h"
#include "impulse_former.h"
#include "ampulse_former.h"

////////////////////////////// MONO ////////////////////////////////////

class GxPluginMono
{
private:
  // internal stuff
  float*                       output;
  float*                       input;
  uint32_t                     tubesel;
  int32_t                      prio;
  TonestackMono                ts;
  GxAmpMono                    amplifier;
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
  bool cab_changed()
  {
    return abs(cab - (clevel_)) > 0.1;
  }
  void update_cab()
  {
    cab = (clevel_);
  }
  float                        *alevel;
  float                        alevel_;
  float                        pre;
  bool pre_changed()
  {
    return abs(pre - (alevel_)) > 0.1;
  }
  void update_pre()
  {
    pre = (alevel_);
  }
  float                        val;
  bool val_changed()
  {
    return abs(val - (alevel_) -(clevel_)) > 0.1;
  }
  void update_val()
  {
    val = (alevel_) + (clevel_);
  }
  bool                         doit;
  volatile int32_t             schedule_wait;
  // threading stuff
  Glib::Threads::Thread        *thread;
  volatile bool                noexit;
  void                         create_thread();
  void                         watch_thread();
  bool                         timeout_handler(); 
  Glib::Threads::Cond          time_cond;
  Glib::Threads::Mutex         _mutex;
  volatile int32_t             schedule_doit;


public:
  // LV2 stuff
  LV2_URID_Map*                map;
  LV2_Worker_Schedule*         schedule;

  void set_tubesel_mono(const LV2_Descriptor* descriptor);
  inline void run_dsp_mono(uint32_t n_samples);
  void connect_mono(uint32_t port,void* data);
  inline void init_dsp_mono(uint32_t rate, uint32_t bufsize_);
  inline void do_work_mono();
  inline void connect_all_mono_ports(uint32_t port, void* data);
  // constructor
  GxPluginMono() :
    output(NULL),
    input(NULL),
    tubesel(0),
    prio(0),
    ts(TonestackMono()),
    amplifier(GxAmpMono()),
    cabconv(GxSimpleConvolver(resamp)),
    impf(Impf()),
    ampconv(GxSimpleConvolver(resamp1)),
    ampf(Ampf()),
    bufsize(0),
    clevel(NULL),
    clevel_(0),
    cab(0),
    alevel(NULL),
    alevel_(0),
    pre(0),
    val(0),
    doit(true),
    thread(),
    noexit(true),
    time_cond(),
    _mutex()
  {
    atomic_set(&schedule_wait,0);
    atomic_set(&schedule_doit,0);
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &GxPluginMono::timeout_handler), 200);
  };
  // destructor
  ~GxPluginMono()
  {
    cabconv.stop_process();
    ampconv.stop_process();
    noexit = false;
    if (thread) 
    {
      time_cond.signal();
      thread->join();
    }
  };
};

#include "cab_data.cc"
#include "gx_tonestack.cc"
#include "gx_amp.cc"
#include "impulse_former.cc"
#include "ampulse_former.cc"

// watch thread to fetch value changes from outside

bool GxPluginMono::timeout_handler() 
{ 
  time_cond.signal();
  return noexit;
}

void GxPluginMono::watch_thread() 
{
  while (noexit) {
    time_cond.wait(_mutex);
    if (!atomic_get(schedule_wait) && val_changed())
      {
        atomic_set(&schedule_doit,1);
        //schedule->schedule_work(schedule->handle, sizeof(bool), &doit);
      }
  }
}

void GxPluginMono::create_thread() 
{
  try {
    thread = Glib::Threads::Thread::create(
        sigc::mem_fun(*this, &GxPluginMono::watch_thread));
    } catch (Glib::Threads::ThreadError& e) {
      throw printf("Thread create failed (signal): %s",  e.what().c_str());
    }
}

// plugin stuff

void GxPluginMono::do_work_mono()
{
  atomic_set(&schedule_wait,1);
  if (cab_changed())
    {
      if (cabconv.is_runnable())
        {
          cabconv.set_not_runnable();
          cabconv.stop_process();
        }
      float cab_irdata_c[cabconv.cab_count];
      impf.compute(cabconv.cab_count, cabconv.cab_data, cab_irdata_c, clevel_);
      cabconv.cab_data_new = cab_irdata_c;
      while (!cabconv.checkstate());
      if (!cabconv.update(cabconv.cab_count, cabconv.cab_data_new, cabconv.cab_sr))
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
      if (!ampconv.update(contrast_ir_desc.ir_count, pre_irdata_c, contrast_ir_desc.ir_sr))
        printf("ampconv.update fail.\n");
      if(!ampconv.start(prio, SCHED_FIFO))
        printf("presence convolver disabled\n");
      update_pre();
      //printf("presence convolver updated\n");
    }
  update_val();
  atomic_set(&schedule_wait,0);
}

void GxPluginMono::set_tubesel_mono(const LV2_Descriptor*     descriptor)
{
  if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#12ax7",descriptor->URI)== 0)
    {
      printf("12ax7\n");
      _a_ptr = &GxAmpMono::run_12ax7;
      _t_ptr = &TonestackMono::run;
      cabconv.cab_count = cab_data_4x12.ir_count;
      cabconv.cab_sr = cab_data_4x12.ir_sr;
      cabconv.cab_data = cab_data_4x12.ir_data;
      tubesel  = 1;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#12AT7",descriptor->URI)== 0)
    {
      printf("12AT7\n");
      _a_ptr = &GxAmpMono::run_12AT7;
      _t_ptr = &TonestackMono::run_soldano;
      cabconv.cab_count = cab_data_AC30.ir_count;
      cabconv.cab_sr = cab_data_AC30.ir_sr;
      cabconv.cab_data = cab_data_AC30.ir_data;
      tubesel  = 2;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#6C16",descriptor->URI)== 0)
    {
      printf("6C16\n");
      _a_ptr = &GxAmpMono::run_6C16;
      _t_ptr = &TonestackMono::run_bassman;
      cabconv.cab_count = cab_data_1x15.ir_count;
      cabconv.cab_sr =  cab_data_1x15.ir_sr;
      cabconv.cab_data = cab_data_1x15.ir_data;
      tubesel  = 3;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#6V6",descriptor->URI)== 0)
    {
      printf("6V6\n");
      _a_ptr = &GxAmpMono::run_6V6;
      _t_ptr = &TonestackMono::run_soldano;
      cabconv.cab_count = cab_data_mesa.ir_count;
      cabconv.cab_sr = cab_data_mesa.ir_sr;
      cabconv.cab_data = cab_data_mesa.ir_data;
      tubesel  = 4;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#6DJ8",descriptor->URI)== 0)
    {
      printf("6DJ8\n");
      _a_ptr = &GxAmpMono::run_6DJ8;
      _t_ptr = &TonestackMono::run_ampeg;
      cabconv.cab_count = cab_data_HighGain.ir_count;
      cabconv.cab_sr = cab_data_HighGain.ir_sr;
      cabconv.cab_data = cab_data_HighGain.ir_data;
      tubesel  = 5;
    }
  else
    {
      _a_ptr = &GxAmpMono::run_12ax7;
      _t_ptr = &TonestackMono::run;
      cabconv.cab_count = cab_data_4x12.ir_count;
      cabconv.cab_sr = cab_data_4x12.ir_sr;
      cabconv.cab_data = cab_data_4x12.ir_data;
      tubesel  = 0;
    }
}

void GxPluginMono::init_dsp_mono(uint32_t rate, uint32_t bufsize_)
{
  AVOIDDENORMALS();

  bufsize = bufsize_;
  amplifier.init_static(rate, &amplifier);
  ts.init_static(rate, &ts);
  //impf.init_static(rate, &impf);
  //ampf.init_static(rate, &ampf);

  if (bufsize )
    {
#ifdef _POSIX_PRIORITY_SCHEDULING
      int priomax = sched_get_priority_max(SCHED_FIFO);
      if ((priomax/2) > 0) prio = priomax/2;
#endif
      cabconv.set_samplerate(rate);
      cabconv.set_buffersize(bufsize);
      cabconv.configure(cabconv.cab_count, cabconv.cab_data, cabconv.cab_sr);
      if(!cabconv.start(prio, SCHED_FIFO))
        printf("cabinet convolver disabled\n");

      ampconv.set_samplerate(rate);
      ampconv.set_buffersize(bufsize);
      ampconv.configure(contrast_ir_desc.ir_count, contrast_ir_desc.ir_data, contrast_ir_desc.ir_sr);
      if(!ampconv.start(prio, SCHED_FIFO))
        printf("presence convolver disabled\n");
      create_thread();
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
      clevel = (float*)data;
      break;
    case ALevel:
      alevel = (float*)data;
      break;
    case AMP_CONTROL:
      c_notice = (LV2_Atom_Sequence*)data;
      break;
    case AMP_NOTIFY:
      n_notice = (LV2_Atom_Sequence*)data;
      break;
    case AMP_OUTPUT:
      output = (float*)data;
      break;
    case AMP_INPUT:
      input = (float*)data;
      break;
    case AMP_OUTPUT1:
      break;
    case AMP_INPUT1:
      break;
    }
}

void GxPluginMono::run_dsp_mono(uint32_t n_samples)
{
  clevel_ = (*clevel);
  alevel_ = (*alevel);
  // run dsp
  amplifier.run_static(n_samples, input, output, &amplifier);
  ampconv.run_static(n_samples, &ampconv, output);
  ts.run_static(n_samples, &ts, output);
  cabconv.run_static(n_samples, &cabconv, output);
  // work ?
  if (atomic_get(schedule_doit))
    {
      atomic_set(&schedule_doit,0);
      schedule->schedule_work(schedule->handle, sizeof(bool), &doit);
    }
}

void GxPluginMono::connect_all_mono_ports(uint32_t port, void* data)
{
  connect_mono(port,data);
  amplifier.connect_static(port,data, &amplifier);
  ts.connect_static(port,data, &ts);
  //impf.connect_static(port,data, &impf);
  //ampf.connect_static(port,data, &ampf);
}

///////////////////////////// LV2 defines //////////////////////////////

static LV2_Worker_Status
work(LV2_Handle                  instance,
     LV2_Worker_Respond_Function respond,
     LV2_Worker_Respond_Handle   handle,
     uint32_t                    size,
     const void*                 data)
{
  GxPluginMono* self = (GxPluginMono*)instance;
  self->do_work_mono();
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
  self->set_tubesel_mono( descriptor);
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
