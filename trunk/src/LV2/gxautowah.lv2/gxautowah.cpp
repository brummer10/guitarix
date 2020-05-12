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

#include "gx_common.h"
#include "gx_bypass.cc"

#include "gxautowah.h"
#include "dunwahauto.cc"

// define run pointer typs
typedef void (crybaby::*run_crybaby)
(uint32_t count,float* input, float* output);

////////////////////////////// MONO ////////////////////////////////////

class Gxautowah
{
private:
  GxBypass                     bp;
  float*                       bypass;
  DenormalProtection           MXCSR;
  // internal stuff
  float*                       output;
  float*                       input;
  crybaby                      wah;
  run_crybaby                  _wah;
  bool                         a_w;
  //dunwahauto                   wah;
public:
  void activate_f();
  inline void run_dsp_mono(uint32_t n_samples);
  void connect_mono(uint32_t port,void* data);
  inline void init_dsp_mono(uint32_t rate, const LV2_Descriptor* descriptor);
  inline void connect_all_mono_ports(uint32_t port, void* data);
  // constructor
  Gxautowah() :
    bp(),
    bypass(0),
    MXCSR(),
    output(NULL),
    input(NULL),
    wah(crybaby()),
    _wah(NULL),
    a_w(true)
  {
  };
  // destructor
  ~Gxautowah()
  {
  };
};

// plugin stuff

void Gxautowah::init_dsp_mono(uint32_t rate, const LV2_Descriptor* descriptor)
{
  bp.init_bypass(rate);
  if (strcmp("http://guitarix.sourceforge.net/plugins/gxautowah#autowah",descriptor->URI)== 0)
    {
      _wah = &crybaby::run;
      wah.init(rate);
      a_w = true;
    }
  else if (strcmp("http://guitarix.sourceforge.net/plugins/gxautowah#wah",descriptor->URI)== 0)
    {
      _wah = &crybaby::run_d;
      wah.init_d(rate);
      a_w = false;
    }
  else 
    {
      _wah = &crybaby::run;
      wah.init(rate);
      a_w = true;
    }
}

void Gxautowah::connect_mono(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case AUTOWAH_OUTPUT:
      output = static_cast<float*>(data);
      break;
    case AUTOWAH_INPUT:
      input = static_cast<float*>(data);
      break;
    case BYPASS: 
      bypass = static_cast<float*>(data); // , 0.0, 0.0, 1.0, 1.0 
      break;
    default:
      break;
    }
}

void Gxautowah::activate_f()
{
    if(a_w) wah.clear_state_f();
    else wah.clear_state_fd();
}

void Gxautowah::run_dsp_mono(uint32_t n_samples)
{
  if (n_samples< 1) return;
  MXCSR.set_();
  // run dsp
  FAUSTFLOAT buf[n_samples];
  // do inplace processing at default
  if (output != input)
    memcpy(output, input, n_samples*sizeof(float));
  // check if bypass is pressed
  if (!bp.pre_check_bypass(bypass, buf, input, n_samples)) 
    (&wah->*_wah)(n_samples, input, output);
  bp.post_check_bypass(buf, output, n_samples);

  MXCSR.reset_();
}

void Gxautowah::connect_all_mono_ports(uint32_t port, void* data)
{
  connect_mono(port,data);
  if (!a_w) wah.connect_d(port,data);
}

///////////////////////////// LV2 defines //////////////////////////////

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{

  Gxautowah *self = new Gxautowah();
  if (!self)
    {
      return NULL;
    }

  self->init_dsp_mono((uint32_t)rate, descriptor);

  return (LV2_Handle)self;
}

static void
connect_port(LV2_Handle instance,
             uint32_t   port,
             void*      data)
{
  Gxautowah* self = (Gxautowah*)instance;
  self->connect_all_mono_ports(port, data);
}

static void
run(LV2_Handle instance, uint32_t n_samples)
{
  Gxautowah* self = (Gxautowah*)instance;
  self->run_dsp_mono(n_samples);
}

static void
activate(LV2_Handle instance)
{
  Gxautowah* self = (Gxautowah*)instance;
  self->activate_f();
}

static void
cleanup(LV2_Handle instance)
{
  Gxautowah* self = (Gxautowah*)instance;
  delete self;
}

//////////////////////////////////////////////////////////////////

static const LV2_Descriptor descriptor =
{
  GXPLUGIN_URI "#autowah",
  instantiate,
  connect_port,
  activate,
  run,
  NULL,
  cleanup,
  NULL
};

static const LV2_Descriptor descriptor1 =
{
  GXPLUGIN_URI "#wah",
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
    case 1:
      return &descriptor1;
    default:
      return NULL;
    }
}
