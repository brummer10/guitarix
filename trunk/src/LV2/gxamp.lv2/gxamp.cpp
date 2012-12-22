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
template <int N> inline float faustpower(float x)
{
  return powf(x, N);
}
template <int N> inline double faustpower(double x)
{
  return pow(x, N);
}
template <int N> inline int faustpower(int x)
{
  return faustpower<N/2>(x) * faustpower<N-N/2>(x);
}
template <>      inline int faustpower<0>(int x)
{
  return 1;
}
template <>      inline int faustpower<1>(int x)
{
  return x;
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
public:
  // LV2 stuff
  LV2_Atom_Sequence*           c_notice;
  LV2_Atom_Sequence*           n_notice;
  LV2_URID_Map*                map;
  LV2_Atom_Forge               forge;
  GXPluginURIs                 uris;
  LV2_Atom_Forge_Frame         notify_frame;
  LV2_Worker_Schedule*         schedule;
  // internal stuff
  uint32_t                     tubesel;
  Tonestack                    *ts;
  GxAmp                        *amplifier;
  gx_resample::BufferResampler resamp;
  GxSimpleConvolver            *cabconv;
  Impf                         *impf;
  gx_resample::BufferResampler resamp1;
  GxSimpleConvolver            *ampconv;
  Ampf                         *ampf;
  uint32_t                     bufsize;
  bool                         schedule_wait;
  static void connect(uint32_t port,void* data, GXPlugin* self);
  GXPlugin() :
    tubesel(0),
    ts(new Tonestack()),
    amplifier(new GxAmp()),
    cabconv(new GxSimpleConvolver(resamp)),
    impf(new Impf()),
    ampconv(new GxSimpleConvolver(resamp1)),
    ampf(new Ampf()),
    bufsize(0),
    schedule_wait(false)
    {};
  ~GXPlugin() {
    cabconv->stop_process();
    ampconv->stop_process();
    delete amplifier;
    delete ts;
    delete cabconv;
    delete impf;
    delete ampconv;
    delete ampf;
      };
};



#include "gx_tonestack.cc"
#include "gx_amp.cc"
#include "gx_convolver.cc"
#include "gx_resampler.cc"
#include "impulse_former.cc"
#include "ampulse_former.cc"


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
  if (obj->body.otype == uris->gx_cab)
    {
      if (self->tubesel == 1)
        {
          //printf("worker run. %d id= %d type= %d\n", obj->body.otype, obj->body.id, obj->atom.type);
          float cab_irdata_c[cab_data_HighGain.ir_count];
          self->impf->compute(cab_data_HighGain.ir_count, cab_data_HighGain.ir_data, cab_irdata_c);
          if (!self->cabconv->update(cab_data_HighGain.ir_count, cab_irdata_c, cab_data_HighGain.ir_sr))
            printf("cabconv->update fail.\n");
          //printf("worker 1 ready.\n");
        }
      else if (self->tubesel == 2)
        {
          float cab_irdata_c[cab_data_AC30.ir_count];
          self->impf->compute(cab_data_AC30.ir_count, cab_data_AC30.ir_data, cab_irdata_c);
          if (!self->cabconv->update(cab_data_AC30.ir_count, cab_irdata_c, cab_data_AC30.ir_sr))
            printf("cabconv->update fail.\n");
        }
      else if (self->tubesel == 3)
        {
          float cab_irdata_c[cab_data_1x15.ir_count];
          self->impf->compute(cab_data_1x15.ir_count, cab_data_1x15.ir_data, cab_irdata_c);
          if (!self->cabconv->update(cab_data_1x15.ir_count, cab_irdata_c, cab_data_1x15.ir_sr))
            printf("cabconv->update fail.\n");
        }
      else if (self->tubesel == 4)
        {
          float cab_irdata_c[cab_data_mesa.ir_count];
          self->impf->compute(cab_data_mesa.ir_count, cab_data_mesa.ir_data, cab_irdata_c);
          if (!self->cabconv->update(cab_data_mesa.ir_count, cab_irdata_c, cab_data_mesa.ir_sr))
            printf("cabconv->update fail.\n");
        }
      else
        {
          float cab_irdata_c[cab_data_HighGain.ir_count];
          self->impf->compute(cab_data_HighGain.ir_count, cab_data_HighGain.ir_data, cab_irdata_c);
          if (!self->cabconv->update(cab_data_HighGain.ir_count, cab_irdata_c, cab_data_HighGain.ir_sr))
            printf("cabconv->update fail.\n");
        }
    }
  else if (obj->body.otype == uris->gx_pre)
    {
      //printf("worker run. %d id= %d type= %d\n", obj->body.otype, obj->body.id, obj->atom.type);
      float pre_irdata_c[contrast_ir_desc.ir_count];
      self->ampf->compute(contrast_ir_desc.ir_count,contrast_ir_desc.ir_data, pre_irdata_c);
      // cab_data_HighGain.ir_count, cab_data_HighGain.ir_data,cab_data_HighGain.ir_sr
      if (!self->ampconv->update(contrast_ir_desc.ir_count, pre_irdata_c, contrast_ir_desc.ir_sr))
        printf("cabconv->update fail.\n");
      //printf("worker 2 ready.\n");
    }
  self->schedule_wait = false;
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
  if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#12ax7",descriptor->URI)== 0)
    {
      printf("12ax7\n");
      self->tubesel  = 1;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#12AT7",descriptor->URI)== 0)
    {
      printf("12AT7\n");
      self->tubesel  = 2;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#6C16",descriptor->URI)== 0)
    {
      printf("6C16\n");
      self->tubesel  = 3;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxamp#6V6",descriptor->URI)== 0)
    {
      printf("6V6\n");
      self->tubesel  = 4;
    }
  else self->tubesel  = 0;
  for (int i = 0; features[i]; ++i)
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


  AVOIDDENORMALS();

  LV2_URID_Map*             map      = self->map;
  map_gx_uris(map, &self->uris);
  lv2_atom_forge_init(&self->forge, self->map);

  self->bufsize = bufsize;
  self->amplifier->init_static(rate, self);
  self->ts->init_static(rate, self);

  self->cabconv->set_samplerate(rate);
  self->impf->init_static(rate, self->impf);

  self->ampconv->set_samplerate(rate);
  self->ampf->init_static(rate, self->ampf);

  if (self->bufsize )
    {
      self->cabconv->set_buffersize(self->bufsize);
      if (self->tubesel == 1)
        {
          self->cabconv->configure(cab_data_HighGain.ir_count, cab_data_HighGain.ir_data, cab_data_HighGain.ir_sr);
        }
      else if (self->tubesel == 2)
        {
          self->cabconv->configure(cab_data_AC30.ir_count, cab_data_AC30.ir_data, cab_data_AC30.ir_sr);
        }
      else if (self->tubesel == 3)
        {
          self->cabconv->configure(cab_data_1x15.ir_count, cab_data_1x15.ir_data, cab_data_1x15.ir_sr);
        }
      else if (self->tubesel == 4)
        {
          self->cabconv->configure(cab_data_mesa.ir_count, cab_data_mesa.ir_data, cab_data_mesa.ir_sr);
        }
      else self->cabconv->configure(cab_data_HighGain.ir_count, cab_data_HighGain.ir_data, cab_data_HighGain.ir_sr);

      if(!self->cabconv->start(0, SCHED_FIFO))
        printf("cabinet convolver disabled\n");

      self->ampconv->set_buffersize(self->bufsize);
      self->ampconv->configure(contrast_ir_desc.ir_count, contrast_ir_desc.ir_data, contrast_ir_desc.ir_sr);
      if(!self->ampconv->start(0, SCHED_FIFO))
        printf("presence convolver disabled\n");
    }
  else
    {
      printf("convolver disabled\n");
    }
  return (LV2_Handle)self;
}

void GXPlugin::connect(uint32_t port,void* data, GXPlugin* self)
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
      break;
    case AMP_INPUT:
      break;
    case AMP_CONTROL:
      self->c_notice = (LV2_Atom_Sequence*)data;
      break;
    case AMP_NOTIFY:
      self->n_notice = (LV2_Atom_Sequence*)data;
      break;
    }

}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
  GXPlugin* self = (GXPlugin*)instance;
  self->connect(port,data, self);
  self->amplifier->connect_static(port,data, self->amplifier);
  self->ts->connect_static(port,data, self->ts);
  self->impf->connect_static(port,data, self->impf);
  self->ampf->connect_static(port,data, self->ampf);
}

static void
activate(LV2_Handle instance)
{

}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  GXPlugin* self = (GXPlugin*)instance;
  /* Set up forge to write directly to notify output port. */
  const uint32_t notify_capacity = self->n_notice->atom.size;
  lv2_atom_forge_set_buffer(&self->forge,
                            (uint8_t*)self->n_notice,
                            notify_capacity);

  /* Start a sequence in the notify output port. */
  lv2_atom_forge_sequence_head(&self->forge, &self->notify_frame, 0);

  /* Read incoming events if scheduler is free*/
  if (self->schedule_wait == false)
    {
      LV2_ATOM_SEQUENCE_FOREACH(self->c_notice, ev)
      {

        self->schedule_wait = true;
        self->schedule->schedule_work(self->schedule->handle,
                                      lv2_atom_total_size(&ev->body), &ev->body);
      }
    }
  self->amplifier->run_static(n_samples, self);
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
    default:
      return NULL;
    }
}
