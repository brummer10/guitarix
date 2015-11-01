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

#include "gxcabinet.h"
#include "gx_resampler.h"
#include "gx_convolver.h"
#include "cabinet_impulse_former.h"
#include "cab_data_table.cc"
#include "gx_mlock.cc"

////////////////////////////// MONO ////////////////////////////////////

class GxCabinet
{
private:
  // internal stuff
  float*                       output;
  float*                       input;
  uint32_t                     s_rate;
  int32_t                      prio;

  gx_resample::BufferResampler resamp;
  GxSimpleConvolver            cabconv;
  Impf                         impf;
  uint32_t                     bufsize;
  uint32_t                     cur_bufsize;
  LV2_Atom_Sequence*           c_notice;
  LV2_Atom_Sequence*           n_notice;
  float                        *clevel;
  float                        clevel_;
  float                        *cbass;
  float                        cbass_;
  float                        *ctreble;
  float                        ctreble_;
  float                        cab;
  float                        *c_model;
  float                        c_model_;
  float                        c_old_model_;
  float                        val;
  bool                         doit;
  float*                       schedule_ok;
  float                        schedule_ok_;
  volatile int32_t             schedule_wait;

  inline bool cab_changed() 
    {return abs(cab - (cbass_ + ctreble_ + clevel_ + c_model_)) > 0.1;}
  inline bool buffsize_changed() 
    {return abs(bufsize - cur_bufsize) != 0;}
  inline void update_cab() 
    {cab = (cbass_ + ctreble_ + clevel_ + c_model_); c_old_model_ = c_model_;}
  inline bool change_cab() 
    {return abs(c_old_model_ - c_model_) > 0.1;}
  inline bool val_changed() 
    {return abs(val - ((*cbass) + (*ctreble) + (*clevel) + (*c_model))) > 0.1;}
  inline void update_val() 
    {val = (cbass_) + (ctreble_) + (clevel_) + (c_model_);}

  // LV2 stuff
  LV2_URID_Map*                map;
  LV2_Worker_Schedule*         schedule;

  inline void clean();
  inline void run_dsp_mono(uint32_t n_samples);
  inline void connect_mono(uint32_t port,void* data);
  inline void init_dsp_mono(uint32_t rate, uint32_t bufsize_);
  inline void do_work_mono();
  inline void connect_all_mono_ports(uint32_t port, void* data);
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

  GxCabinet();
  ~GxCabinet();
};

  // constructor
GxCabinet::GxCabinet() :
  output(NULL),
  input(NULL),
  s_rate(0),
  prio(0),
  cabconv(GxSimpleConvolver(resamp)),
  impf(Impf()),
  bufsize(0),
  cur_bufsize(0),
  clevel(NULL),
  clevel_(0),
  cbass(NULL),
  cbass_(0),
  ctreble(NULL),
  ctreble_(0),
  cab(0),
  c_model(NULL),
  c_model_(0),
  c_old_model_(0),
  val(0),
  schedule_ok(NULL),
  schedule_ok_(0)
{
  atomic_set(&schedule_wait,0);
};
  // destructor
GxCabinet::~GxCabinet()
{
  cabconv.stop_process();
  cabconv.cleanup();
};

// plugin stuff

void GxCabinet::do_work_mono()
{
  if (buffsize_changed()) 
   {
     printf("buffersize changed to %u\n",cur_bufsize);
     if (cabconv.is_runnable())
        {
          cabconv.set_not_runnable();
          cabconv.stop_process();
        }
     bufsize = cur_bufsize;

	 cabconv.cleanup();
     CabDesc& cab = *getCabEntry(static_cast<uint32_t>(c_model_)).data;
     cabconv.cab_count = cab.ir_count;
     cabconv.cab_sr = cab.ir_sr;
     cabconv.cab_data = cab.ir_data;
     cabconv.set_samplerate(s_rate);
     cabconv.set_buffersize(bufsize);
     cabconv.configure(cabconv.cab_count, cabconv.cab_data, cabconv.cab_sr);
     while (!cabconv.checkstate());
     if(!cabconv.start(prio, SCHED_FIFO))
        printf("cabinet convolver update buffersize fail\n");
   }
  if (cab_changed())
    {
      if (cabconv.is_runnable())
        {
          cabconv.set_not_runnable();
          cabconv.stop_process();
        }
     if (c_model_ < cab_table_size) {
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
        cabconv.configure(cabconv.cab_count, cabconv.cab_data, cabconv.cab_sr);
        //printf("cabconv.changed.\n");
      }
      float cab_irdata_c[cabconv.cab_count];
      float adjust_1x8 = 1;
      if ( c_model_ == 17.0) adjust_1x8 = 0.5;
      impf.compute(cabconv.cab_count, cabconv.cab_data, cab_irdata_c, cbass_, ctreble_, (clevel_ * adjust_1x8) );
      cabconv.cab_data_new = cab_irdata_c;
      while (!cabconv.checkstate());
      if (!cabconv.update(cabconv.cab_count, cabconv.cab_data_new, cabconv.cab_sr))
        printf("cabconv.update fail.\n");
      if(!cabconv.start(prio, SCHED_FIFO))
        printf("cabinet convolver disabled\n");
      update_cab();
      //printf("cabinet convolver updated\n");
    } // else printf("cabinet convolver disabled\n");
    }
  update_val();
  atomic_set(&schedule_wait,0);
}

void GxCabinet::init_dsp_mono(uint32_t rate, uint32_t bufsize_)
{
  AVOIDDENORMALS();

  bufsize = bufsize_;
  s_rate = rate;
#ifdef _POSIX_MEMLOCK_RANGE
  GX_LOCK::lock_rt_memory();
#endif
  if (bufsize )
    {
#ifdef _POSIX_PRIORITY_SCHEDULING
      int priomax = sched_get_priority_max(SCHED_FIFO);
      if ((priomax/2) > 0) prio = priomax/2;
#endif
      impf.init(rate);
      // set cabinet data
      CabDesc& cab = *getCabEntry(static_cast<uint32_t>(c_model_)).data;
      cabconv.cab_count = cab.ir_count;
      cabconv.cab_sr = cab.ir_sr;
      cabconv.cab_data = cab.ir_data;
        
      cabconv.set_samplerate(rate);
      cabconv.set_buffersize(bufsize);
      cabconv.configure(cabconv.cab_count, cabconv.cab_data, cabconv.cab_sr);
      while (!cabconv.checkstate());
      if(!cabconv.start(prio, SCHED_FIFO))
        printf("cabinet convolver disabled\n");

    }
  else
    {
      printf("convolver disabled\n");
      schedule_ok_ = 1.;
    }
}


void GxCabinet::connect_mono(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case CLevel:
      clevel = static_cast<float*>(data);
      break;
    case CBass:
      cbass = static_cast<float*>(data);
      break;
    case CTreble:
      ctreble = static_cast<float*>(data);
      break;
    case AMP_CONTROL:
      c_notice = (LV2_Atom_Sequence*)data;
      break;
    case AMP_NOTIFY:
      n_notice = (LV2_Atom_Sequence*)data;
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
    case AMP_INPUT:
      input = static_cast<float*>(data);
      break;
    default:
      break;
    }
}

void GxCabinet::run_dsp_mono(uint32_t n_samples)
{
  cur_bufsize = n_samples;
  if (*(schedule_ok) != schedule_ok_) *(schedule_ok) = schedule_ok_;
  // run dsp
  memcpy(output, input, n_samples * sizeof(float));
  // run selected cabinet convolver
  cabconv.run_static(n_samples, &cabconv, output);

  // work ?
  if (!atomic_get(schedule_wait) && (val_changed() || buffsize_changed()))
    {
      clevel_ = (*clevel);
      cbass_ = (*cbass);
      ctreble_ = (*ctreble);
      c_model_= (*c_model);
      atomic_set(&schedule_wait,1);
      schedule->schedule_work(schedule->handle, sizeof(bool), &doit);
    }
}

void GxCabinet::connect_all_mono_ports(uint32_t port, void* data)
{
  connect_mono(port,data);
}

void GxCabinet::activate_f()
{
  // allocate the internal DSP mem

}

void GxCabinet::deactivate_f()
{
  // delete the internal DSP mem

}

void GxCabinet::clean()
{
#ifdef _POSIX_MEMLOCK_RANGE
  GX_LOCK::unlock_rt_memory();
#endif
}
///////////////////////////// LV2 defines //////////////////////////////

LV2_Worker_Status GxCabinet::work(LV2_Handle                  instance,
     LV2_Worker_Respond_Function respond,
     LV2_Worker_Respond_Handle   handle,
     uint32_t                    size,
     const void*                 data)
{
  static_cast<GxCabinet*>(instance)->do_work_mono();
  return LV2_WORKER_SUCCESS;
}

LV2_Worker_Status GxCabinet::work_response(LV2_Handle  instance,
              uint32_t    size,
              const void* data)
{
  //printf("worker respose.\n");
  return LV2_WORKER_SUCCESS;
}


LV2_Handle GxCabinet::instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{

  GxCabinet *self = new GxCabinet();
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
      self->schedule_ok_ = 1.;
      //delete self;
      //return NULL;
    } else {
      self->schedule_ok_ = 0.;
    }
  if (!self->map)
    {
      fprintf(stderr, "Missing feature uri:map.\n");
      //atomic_set(&self->schedule_wait,1);
      //self->schedule_ok_ = 1.;
    }
  else if (!options)
    {
      fprintf(stderr, "Missing feature options.\n");
      //atomic_set(&self->schedule_wait,1);
      //self->schedule_ok_ = 1.;
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
          //atomic_set(&self->schedule_wait,1);
          //self->schedule_ok_ = 1.;
        }
      printf("using block size: %d\n", bufsize);
      self->schedule_ok_ = 0.;
    }
  self->init_dsp_mono((uint32_t)rate, bufsize);

  return (LV2_Handle)self;
}

void GxCabinet::connect_port(LV2_Handle instance,
                                uint32_t   port,
                                void*      data)
{
  static_cast<GxCabinet*>(instance)->connect_all_mono_ports(port, data);
}

void GxCabinet::activate(LV2_Handle instance)
{

}

void GxCabinet::run(LV2_Handle instance, uint32_t n_samples)
{
  static_cast<GxCabinet*>(instance)->run_dsp_mono(n_samples);
}

void GxCabinet::deactivate(LV2_Handle instance)
{

}

void GxCabinet::cleanup(LV2_Handle instance)
{
  GxCabinet* self = (GxCabinet*)instance;
  self->clean();
  delete self;
}

//////////////////////////////////////////////////////////////////

const void* GxCabinet::extension_data(const char* uri)
{
  static const LV2_Worker_Interface worker = { work, work_response, NULL };
  if (!strcmp(uri, LV2_WORKER__interface))
    {
      return &worker;
    }
  return NULL;
}

const LV2_Descriptor GxCabinet::descriptor =
{
  GXPLUGIN_URI "#CABINET",
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
      return &GxCabinet::descriptor;
    default:
      return NULL;
    }
}
