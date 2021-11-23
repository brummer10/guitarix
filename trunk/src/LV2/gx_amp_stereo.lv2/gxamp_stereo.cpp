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


#include "gxamp_stereo.h"
#include "gx_resampler.h"
#include "gx_convolver.h"
#include "gx_pluginlv2.h"   // define struct PluginLV2
#include "impulse_former.h"
#include "ampulse_former.h"
#include "gx_bypass.cc"     // bypass ramping

#ifndef __SSE__
#include "stereo_noiser.cc"
#endif
#include "cab_data_table.cc"

#include "gx_mlock.cc"

//////////////////////// define dsp namespaces /////////////////////////

#define declare(n) namespace n { PluginLV2 *plugin(); }

declare(gxamp_stereo);
declare(gxamp2_stereo);
declare(gxamp3_stereo);
declare(gxamp4_stereo);
declare(gxamp5_stereo);
declare(gxamp6_stereo);
declare(gxamp7_stereo);
declare(gxamp8_stereo);
declare(gxamp9_stereo);
declare(gxamp10_stereo);
declare(gxamp11_stereo);
declare(gxamp12_stereo);
declare(gxamp13_stereo);
declare(gxamp14_stereo);
declare(gxamp15_stereo);
declare(gxamp16_stereo);
declare(gxamp17_stereo);
declare(gxamp18_stereo);

static plug amp_model [] = {
    gxamp_stereo::plugin, //0
    gxamp3_stereo::plugin, //1
    gxamp14_stereo::plugin, //2
    gxamp10_stereo::plugin, //3
    gxamp18_stereo::plugin, //4

    gxamp2_stereo::plugin, //5

    gxamp9_stereo::plugin, //6
    gxamp11_stereo::plugin, //7
    gxamp17_stereo::plugin, //8
    gxamp13_stereo::plugin, //9

    gxamp5_stereo::plugin, //10
    gxamp4_stereo::plugin, //11
    gxamp15_stereo::plugin, //12
    gxamp12_stereo::plugin, //13

    gxamp7_stereo::plugin, //14
    gxamp8_stereo::plugin, //15
    gxamp16_stereo::plugin, //16
    gxamp6_stereo::plugin, //17
};

static const size_t AMP_COUNT = sizeof(amp_model) / sizeof(amp_model[0]);

declare(tonestack_default_stereo)
declare(tonestack_bassman_stereo)
declare(tonestack_twin_stereo)
declare(tonestack_princeton_stereo)
declare(tonestack_jcm800_stereo)
declare(tonestack_jcm2000_stereo)
declare(tonestack_mlead_stereo)
declare(tonestack_m2199_stereo)
declare(tonestack_ac30_stereo)
declare(tonestack_soldano_stereo)
declare(tonestack_mesa_stereo)
declare(tonestack_jtm45_stereo)
declare(tonestack_ac15_stereo)
declare(tonestack_peavey_stereo)
declare(tonestack_ibanez_stereo)
declare(tonestack_roland_stereo)
declare(tonestack_ampeg_stereo)
declare(tonestack_ampeg_rev_stereo)
declare(tonestack_sovtek_stereo)
declare(tonestack_bogner_stereo)
declare(tonestack_groove_stereo)
declare(tonestack_crunch_stereo)
declare(tonestack_fender_blues_stereo)
declare(tonestack_fender_default_stereo)
declare(tonestack_fender_deville_stereo)
declare(tonestack_gibsen_stereo)

static plug tonestack_model[] = {
    tonestack_default_stereo::plugin,
    tonestack_bassman_stereo::plugin,
    tonestack_twin_stereo::plugin,
    tonestack_princeton_stereo::plugin,
    tonestack_jcm800_stereo::plugin,
    tonestack_jcm2000_stereo::plugin,
    tonestack_mlead_stereo::plugin,
    tonestack_m2199_stereo::plugin,
    tonestack_ac30_stereo::plugin,
    tonestack_soldano_stereo::plugin,
    tonestack_mesa_stereo::plugin,
    tonestack_jtm45_stereo::plugin,
    tonestack_ac15_stereo::plugin,
    tonestack_peavey_stereo::plugin,
    tonestack_ibanez_stereo::plugin,
    tonestack_roland_stereo::plugin,
    tonestack_ampeg_stereo::plugin,
    tonestack_ampeg_rev_stereo::plugin,
    tonestack_sovtek_stereo::plugin,
    tonestack_bogner_stereo::plugin,
    tonestack_groove_stereo::plugin,
    tonestack_crunch_stereo::plugin,
    tonestack_fender_blues_stereo::plugin,
    tonestack_fender_default_stereo::plugin,
    tonestack_fender_deville_stereo::plugin,
    tonestack_gibsen_stereo::plugin,
};

static const size_t TS_COUNT = sizeof(tonestack_model) / sizeof(tonestack_model[0]);



////////////////////////////// STEREO ////////////////////////////////////

class GxPluginStereo
{
private:
  GxBypass                     bp;
  float*                       bypass;
  DenormalProtection           MXCSR;
  // internal stuff
  float*                       output;
  float*                       output1;
  float*                       input;
  float*                       input1;
  uint32_t                     s_rate;
  int32_t                      prio;
#ifndef __SSE__
  PluginLV2*                   wn;
#endif
  PluginLV2*                   amplifier[AMP_COUNT];
  PluginLV2*                   tonestack[TS_COUNT];
  float*                       a_model;
  uint32_t                     a_model_;
  uint32_t                     a_max;
  float*                       t_model;
  uint32_t                     t_model_;
  uint32_t                     t_max;
  gx_resample::BufferResampler resamp;
  GxSimpleConvolver            cabconv;
  Impf                         impf;
  gx_resample::BufferResampler resamp1;
  GxSimpleConvolver            ampconv;
  Ampf                         ampf;
  uint32_t                     bufsize;
  uint32_t                     cur_bufsize;
  LV2_Atom_Sequence*           c_notice;
  LV2_Atom_Sequence*           n_notice;
  float                        *clevel;
  float                        clevel_;
  float                        cab;
  float                        *c_model;
  float                        c_model_;
  float                        c_old_model_;
  float                        *alevel;
  float                        alevel_;
  float                        pre;
  bool                         doit;
  float*                       schedule_ok;
  float                        schedule_ok_;
  volatile int32_t             schedule_wait;
  
  bool cab_changed()
    {return std::abs(cab - clevel_ ) > 0.1;}
  bool buffsize_changed() 
    {return bufsize != cur_bufsize;}
  void update_cab()
    {cab = (clevel_ ); c_old_model_ = c_model_;}
  bool change_cab()
    {return std::abs(c_old_model_ - c_model_) > 0.1;}
  bool pre_changed()
    {return std::abs(pre - alevel_) > 0.1;}
  void update_pre()
    {pre = (alevel_);}
  inline bool val_changed() 
    {return  std::abs(alevel_ - (*alevel)) > 0.1 || abs(clevel_ - (*clevel)) > 0.1 || std::abs(c_model_ - (*c_model)) > 0.1;}

  // LV2 stuff
  LV2_URID_Map*                map;
  LV2_Worker_Schedule*         schedule;

  inline void clean();
  inline void run_dsp_stereo(uint32_t n_samples);
  inline void connect_stereo(uint32_t port,void* data);
  inline void init_dsp_stereo(uint32_t rate, uint32_t bufsize_);
  inline void do_work_stereo();
  inline void connect_all_stereo_ports(uint32_t port, void* data);
  inline void activate_f();
  inline void deactivate_f();

public:

    // LV2 Descriptor
  static const LV2_Descriptor descriptor;
  static const void* extension_data(const char* uri);
  // static wrapper to private functions
  static void deactivate(LV2_Handle instance);
  static void cleanup(LV2_Handle instance);
  static void run(LV2_Handle instance, uint32_t n_samples);
  static void activate(LV2_Handle instance);
  static void connect_port(LV2_Handle instance, uint32_t port, void* data);

  static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                                double rate, const char* bundle_path,
                                const LV2_Feature* const* features);
  
  static LV2_Worker_Status work(LV2_Handle                 instance,
                                LV2_Worker_Respond_Function respond,
                                LV2_Worker_Respond_Handle   handle,
                                uint32_t size, const void*    data);
  
  static LV2_Worker_Status work_response(LV2_Handle  instance,
                                         uint32_t    size,
                                         const void* data);

  GxPluginStereo();
  ~GxPluginStereo();
};

// constructor
GxPluginStereo::GxPluginStereo() :
  bp(),
  bypass(0),
  MXCSR(),
  output(NULL),
  output1(NULL),
  input(NULL),
  input1(NULL),
  s_rate(0),
  prio(0),
  a_model(NULL),
  a_model_(0), 
  a_max(0),
  t_model(NULL),
  t_model_(1),
  t_max(1),
  cabconv(GxSimpleConvolver(resamp)),
  impf(Impf()),
  ampconv(GxSimpleConvolver(resamp1)),
  ampf(Ampf()),
  bufsize(0),
  cur_bufsize(0),
  clevel(NULL),
  clevel_(0),
  cab(0),
  c_model(NULL),
  c_model_(0),
  c_old_model_(0),
  alevel(NULL),
  alevel_(0),
  pre(0),
  schedule_ok(NULL),
  schedule_ok_(0)
{
  atomic_set(&schedule_wait,0);
};
  
// destructor
GxPluginStereo::~GxPluginStereo()
{
  cabconv.stop_process();
  cabconv.cleanup();
  ampconv.stop_process();
  ampconv.cleanup();
};


// plugin stuff

void GxPluginStereo::do_work_stereo()
{
 /* if (buffsize_changed()) 
   {
     printf("buffersize changed to %u\n",cur_bufsize);
     if (cabconv.is_runnable())
        {
          cabconv.set_not_runnable();
          cabconv.stop_process();
        }
     if (ampconv.is_runnable())
        {
          ampconv.set_not_runnable();
          ampconv.stop_process();
        }
     bufsize = cur_bufsize;

	 cabconv.cleanup();
     CabDesc& cab = *getCabEntry(static_cast<uint32_t>(c_model_)).data;
     cabconv.cab_count = cab.ir_count;
     cabconv.cab_sr = cab.ir_sr;
     cabconv.set_samplerate(s_rate);
     cabconv.set_buffersize(bufsize);
     float cab_irdata_c[cabconv.cab_count];
     float adjust_1x8 = 1;
     if ( c_model_ == 17.0) adjust_1x8 = 0.5;
     impf.compute(cabconv.cab_count, cabconv.cab_data, cab_irdata_c, (clevel_ * adjust_1x8));
     cabconv.cab_data_new = cab_irdata_c;
     cabconv.configure_stereo(cabconv.cab_count, cabconv.cab_data_new, cabconv.cab_sr);
     while (!cabconv.checkstate());
     if(!cabconv.start(prio, SCHED_FIFO))
        printf("cabinet convolver update buffersize fail\n");

     ampconv.cleanup();
     ampconv.set_samplerate(s_rate);
     ampconv.set_buffersize(bufsize);
     float pre_irdata_c[contrast_ir_desc.ir_count];
     ampf.compute(contrast_ir_desc.ir_count,contrast_ir_desc.ir_data, pre_irdata_c, alevel_);
     ampconv.configure_stereo(contrast_ir_desc.ir_count, pre_irdata_c, contrast_ir_desc.ir_sr);
     while (!ampconv.checkstate());
     if(!ampconv.start(prio, SCHED_FIFO))
        printf("presence convolver update buffersize fail\n");
   }*/
  if (cab_changed() || change_cab())
    {
      if (cabconv.is_runnable())
        {
          cabconv.set_not_runnable();
          cabconv.stop_process();
        }
      // selected cabinet have changed?
    if (c_model_ < cab_table_size) {
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
  atomic_set(&schedule_wait,0);
}

void GxPluginStereo::init_dsp_stereo(uint32_t rate, uint32_t bufsize_)
{
  bufsize = bufsize_;
  s_rate = rate;
  bp.init_bypass(rate);

#ifdef _POSIX_MEMLOCK_RANGE
  GX_LOCK::lock_rt_memory();
#endif
#ifndef __SSE__
  wn = stereo_noiser::plugin();
  wn->set_samplerate(rate, wn);
#endif

  for(uint32_t i=0; i<AMP_COUNT; i++) {
        amplifier[i] = amp_model[i]();
        amplifier[i]->set_samplerate(rate, amplifier[i]);
    }
  a_max = AMP_COUNT-1;
  for(uint32_t i=0; i<TS_COUNT; i++) {
        tonestack[i] = tonestack_model[i]();
        tonestack[i]->set_samplerate(rate, tonestack[i]);
    }
  t_max = TS_COUNT-1;
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
    case SCHEDULE:
      schedule_ok =  static_cast<float*>(data);
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
    case BYPASS: 
      bypass = static_cast<float*>(data); // , 0.0, 0.0, 1.0, 1.0 
      break;
    default:
      break;
    }
}

void GxPluginStereo::run_dsp_stereo(uint32_t n_samples)
{
  if (n_samples< 1) return;
  MXCSR.set_();
  cur_bufsize = n_samples;
  if (*(schedule_ok) != schedule_ok_) *(schedule_ok) = schedule_ok_;
  // run dsp
  FAUSTFLOAT buf[n_samples];
  FAUSTFLOAT buf1[n_samples];
  // do inplace processing at default
  if (output != input)
    memcpy(output, input, n_samples*sizeof(float));
  if (output1 != input1)
    memcpy(output1, input1, n_samples*sizeof(float));
  // check if bypass is pressed
  if (!bp.pre_check_bypass(bypass, buf, buf1, input, input1, n_samples)) {
#ifndef __SSE__
    wn->stereo_audio(static_cast<int>(n_samples), input, input1, input, input1, wn);;
#endif
    // run selected tube model
    a_model_ = min(a_max, static_cast<uint32_t>(*(a_model)));
    amplifier[a_model_]->stereo_audio(static_cast<int>(n_samples), input, input1, output, output1, amplifier[a_model_]);
    // run presence convolver
    ampconv.run_static_stereo(n_samples, &ampconv, output, output1);
    // run selected tonestack
    t_model_ = static_cast<uint32_t>(*(t_model));
    if (t_model_ <= t_max)
    tonestack[t_model_]->stereo_audio(static_cast<int>(n_samples), output, output1, output, output1, tonestack[t_model_]);
    // run selected cabinet convolver
    cabconv.run_static_stereo(n_samples, &cabconv, output, output1);
  }
  bp.post_check_bypass(buf, buf1, output, output1, n_samples);

  MXCSR.reset_();
  // work ?
  if (!atomic_get(schedule_wait) && (val_changed() || buffsize_changed() ))
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

void GxPluginStereo::activate_f()
{
  // allocate the internal DSP mem

}

void GxPluginStereo::deactivate_f()
{
  // delete the internal DSP mem

}

void GxPluginStereo::clean()
{

#ifdef _POSIX_MEMLOCK_RANGE
  GX_LOCK::unlock_rt_memory();
#endif
#ifndef __SSE__
  wn->delete_instance(wn);;
#endif

  for(uint32_t i=0; i<AMP_COUNT; i++) {
    amplifier[i]->delete_instance(amplifier[i]);
  }
  for(uint32_t i=0; i<TS_COUNT; i++) {
    tonestack[i]->delete_instance(tonestack[i]);
  }
}
///////////////////////////// LV2 defines //////////////////////////////

LV2_Worker_Status GxPluginStereo::work(LV2_Handle   instance,
                        LV2_Worker_Respond_Function respond,
                        LV2_Worker_Respond_Handle   handle,
                        uint32_t                    size,
                        const void*                 data)
{
  static_cast<GxPluginStereo*>(instance)->do_work_stereo();
  return LV2_WORKER_SUCCESS;
}

LV2_Worker_Status
GxPluginStereo::work_response(LV2_Handle  instance,
                                uint32_t    size,
                                const void* data)
{
  //printf("worker respose.\n");
  return LV2_WORKER_SUCCESS;
}


LV2_Handle
GxPluginStereo::instantiate(const LV2_Descriptor*     descriptor,
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
      atomic_set(&self->schedule_wait,1);
      self->schedule_ok_ = 1;
      //delete self;
      //return NULL;
    }
  if (!self->map)
    {
      fprintf(stderr, "Missing feature uri:map.\n");
      //atomic_set(&self->schedule_wait,1);
      //self->schedule_ok_ = 1;
    }
  else if (!options)
    {
      fprintf(stderr, "Missing feature options.\n");
      //atomic_set(&self->schedule_wait,1);
      //self->schedule_ok_ = 1;
    }
  else
    {
      LV2_URID bufsz_max = self->map->map(self->map->handle, LV2_BUF_SIZE__maxBlockLength);
      LV2_URID bufsz_    = self->map->map(self->map->handle,"http://lv2plug.in/ns/ext/buf-size#nominalBlockLength");
      LV2_URID atom_Int  = self->map->map(self->map->handle, LV2_ATOM__Int);

      for (const LV2_Options_Option* o = options; o->key; ++o)
        {
          if (o->context == LV2_OPTIONS_INSTANCE &&
              o->key == bufsz_ &&
              o->type == atom_Int)
            {
              bufsize = *(const int32_t*)o->value;
              break;
            }
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
          //atomic_set(&self->schedule_wait,1);
          //self->schedule_ok_ = 1;
      }
      printf("using block size: %d\n", bufsize);
    }
  self->init_dsp_stereo((uint32_t)rate, bufsize);

  return (LV2_Handle)self;
}

void GxPluginStereo::connect_port(LV2_Handle instance,
                                    uint32_t   port,
                                    void*      data)
{
  static_cast<GxPluginStereo*>(instance)->connect_all_stereo_ports(port, data);
}

void GxPluginStereo::activate(LV2_Handle instance)
{

}

void GxPluginStereo::run(LV2_Handle instance, uint32_t n_samples)
{
  static_cast<GxPluginStereo*>(instance)->run_dsp_stereo(n_samples);
}

void GxPluginStereo::deactivate(LV2_Handle instance)
{

}

void GxPluginStereo::cleanup(LV2_Handle instance)
{
  GxPluginStereo* self = (GxPluginStereo*)instance;
  self->clean();
  delete self;
}

//////////////////////////////////////////////////////////////////

const void* GxPluginStereo::extension_data(const char* uri)
{
  static const LV2_Worker_Interface worker = { work, work_response, NULL };
  if (!strcmp(uri, LV2_WORKER__interface))
    {
      return &worker;
    }
  return NULL;
}

const LV2_Descriptor GxPluginStereo::descriptor =
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
      return &GxPluginStereo::descriptor;
    default:
      return NULL;
    }
}
