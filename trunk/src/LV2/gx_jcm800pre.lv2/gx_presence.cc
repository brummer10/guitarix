/*
 * Copyright (C) 2015 Guitarix project
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

#include "gx_convolver.cc"

struct CabDesc
{
  int32_t ir_count;
  uint32_t ir_sr;
  float ir_data[];
};

template <int32_t tab_size>
struct CabDesc_imp
{
  int32_t ir_count;
  uint32_t ir_sr;
  float ir_data[tab_size];
  operator CabDesc&()
  {
    return *(CabDesc*)this;
  }
};

CabDesc_imp<192> presence_ir_desc __rt_data = {
    192, 48000,
    { 0.147081, 0.208808, 0.208996, 0.163228, 0.0858905, -0.0119104, -0.0932825, -0.121011, -0.0999426, -0.071073, -0.0403973, -0.00214844, 0.0287018, 
      0.0381079, 0.0372284, 0.0330389, 0.0252979, 0.0141394, 0.00118835, -0.00764709, -0.00751953, 0.00262512, 0.0143475, 0.0174762, 0.0168384, 0.0179126, 
      0.00738525, -0.0114069, -0.0192352, -0.0145825, -0.0179932, -0.0244049, -0.0173956, -0.00357178, 0.00643188, 0.0108966, 0.0132935, 0.0123737, 0.00680786, 
      -0.000214844, -0.0040686, -0.00533752, -0.00738525, -0.00539124, -0.00171875, 0.00156433, 0.00481384, 0.0038739, -0.00666016, -0.018866, -0.0216522, -0.0171606, 
      -0.00717712, 0.00770081, 0.0209003, 0.0251971, 0.0221222, 0.0157977, 0.00453857, -0.0107892, -0.022478, -0.029165, -0.0303467, 0, -0.0169592, 
      -0.00966125, -0.00163147, 0.00273254, 0.000436401, -0.00282654, -0.00791565, -0.0136493, -0.0128436, -0.00564636, 0.00298096, 0.0090033, 0.00841248, 0.00201416, 
      -0.00579407, -0.0119171, -0.0145624, -0.0128436, -0.00741211, 0.000543823, 0.00414917, 0.00414917, 0.00114136, -0.00778809, -0.021377, -0.0325623, -0.0386584, 
      -0.038974, -0.0333679, -0.0221289, -0.0107825, -0.00453186, -0.00127563, -0.000261841, 0.000631104, 0.000537109, 0.000355835, 0.00114136, 0.00174561, 0.00104065, 
      -0.000100708, -0.00128906, -0.00083252, 0.00146362, 0.00234314, 0.000443115, -0.00245056, -0.00782165, -0.0164423, -0.0250092, -0.0309644, -0.0314343, -0.0265063, 
      -0.0176508, -0.00496155, 0.00805664, 0.0157843, 0.0171069, 0.0131055, 0.00613647, -0.00216187, -0.00804321, -0.0117157, 0, -0.015321, -0.0154352, 
      -0.013374, -0.00994995, -0.00672058, -0.00353821, -0.00110779, 0.000678101, 0.00250427, -0.00564636, 0.00298096, 0.0090033, 0.00841248, 0.00201416, -0.00579407, 
      -0.0119171, -0.0145624, -0.0128436, -0.00741211, 0.000543823, 0.00414917, 0.00414917, 0.00114136, -0.00778809, -0.021377, -0.0325623, -0.0386584, -0.038974, 
      -0.0333679, -0.0221289, -0.0107825, -0.00453186, -0.00127563, -0.000261841, 0.000631104, 0.000537109, 0.000355835, 0.00114136, 0.00174561, 0.00104065, -0.000100708, 
      -0.00128906, -0.00083252, 0.00146362, 0.00234314, 0.000443115, -0.00245056, -0.00782165, -0.0164423, -0.0250092, -0.0309644, -0.0314343, -0.0265063, -0.0176508, 
      -0.00496155, 0.00805664, 0.0157843, 0.0171069, 0.0131055, 0.00613647, -0.00216187, -0.00804321, -0.0117157, 0
    }
};


class GxPresence: public GxConvolverBase
{
private:
  float 	fslider0;
  float 	*fslider0_;
  float 	fRec0[2];
  float 	fslider1;
  float 	*fslider1_;
  gx_resample::BufferResampler& resamp;
public:
  int32_t cab_count;
  uint32_t cab_sr;
  float *cab_data;
  float *cab_data_new;
  GxPresence(gx_resample::BufferResampler& resamp_)
    : GxConvolverBase(), resamp(resamp_), cab_count(0), cab_sr(0),
    cab_data(NULL), cab_data_new(NULL) {}
  bool configure(int32_t count, float *impresp, uint32_t imprate);
  bool update(int32_t count, float *impresp, uint32_t imprate);
  bool compute(int32_t count, float* input, float *output);
  bool compute(int32_t count, float* buffer)
  {
    return is_runnable() ? compute(count, buffer, buffer) : true;
  }
  inline void connect_(uint32_t port,void* data);
  static void connect_ports(uint32_t port, void* data, GxPresence *p);
  static void run_static(uint32_t n_samples, GxPresence *p, float *output);
};

bool GxPresence::configure(int32_t count, float *impresp, uint32_t imprate)
{
  for (int i=0; i<2; i++) fRec0[i] = 0;
  //printf("try configure()\n");
  CheckResample r(resamp);
  impresp = r.resample(&count, impresp, imprate, samplerate);
  if (!impresp)
    {
      printf("no impresp\n");
      return false;
    }
  cleanup();
  uint32_t bufsize = buffersize;
  if (bufsize < Convproc::MINPART)
    {
      bufsize = Convproc::MINPART;
    }
#if ZITA_CONVOLVER_VERSION == 4
  if (Convproc::configure(1, 1, count, buffersize,
                          bufsize, bufsize,0.0)) // Convproc::MAXPART
    {
      printf("no configure\n");
      return false;
    }
#else
  if (Convproc::configure(1, 1, count, buffersize,
                          bufsize, bufsize)) // Convproc::MAXPART
    {
      printf("no configure\n");
      return false;
    }
#endif
  if (impdata_create(0, 0, 1, impresp, 0, count))
    {
      printf("no impdata_create()\n");
      return false;
    }
  //printf("configure()\n");

  return true;
}

bool GxPresence::update(int32_t count, float *impresp, uint32_t imprate)
{
  CheckResample r(resamp);
  impresp = r.resample(&count, impresp, imprate, samplerate);
  if (!impresp)
    {
      return false;
    }
#if ZITA_CONVOLVER_VERSION == 4
    impdata_clear(0, 0);
#endif
  if (impdata_update(0, 0, 1, impresp, 0, count))
    {
      return false;
    }
  return true;
}

void GxPresence::connect_(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case WET_DRY:
      fslider0_ = static_cast<float*>(data);
      break;
    case GAIN:
      fslider1_ = static_cast<float*>(data);
      break;
    default:
      break;
    }
}

void GxPresence::connect_ports(uint32_t port,void* data, GxPresence *p)
{
	p->connect_(port, data);
}

bool __rt_func GxPresence::compute(int32_t count, float* input, float *output)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
  
  float 	fSlow0 = float(fslider0);
  float 	fSlow1 = (0.1f * fSlow0);
  float 	fSlow2 = (1 - (0.01f * fSlow0));
  float 	fSlow3 = (0.0010000000000000009f * powf(10,(0.05f * float(fslider1))));
  // printf("try run\n");
  if (state() != Convproc::ST_PROC)
    {
      //printf("state() != ST_PROC\n");
      if (input != output)
        {
          memcpy(output, input, count * sizeof(float));
        }
      if (state() == Convproc::ST_WAIT)
        {
          //printf("state() == ST_WAIT\n");
          check_stop();
        }
      if (state() == ST_STOP)
        {
          //printf("state() == ST_STOP\n");
          ready = false;
        }
      return true;
    }
  int32_t flags = 0;
  float *in, *out;
  in = inpdata(0);
  out = outdata(0);
  uint32_t b = 0;
  uint32_t c = 1;
  for(int32_t i = 0; i<count; ++i){
	in[b] = input[i];
	if(++b == buffersize) {
	  b=0;
	  flags = process();
	  for(uint32_t d = 0; d<buffersize; ++d) {
		float fTemp0 = input[d*c];
		fRec0[0] = ((0.999f * fRec0[1]) + fSlow3);
		output[d*c] = fRec0[0] * ((fSlow2 * fTemp0) + (fSlow1 * out[d]));
		// post processing
		fRec0[1] = fRec0[0];
	  }
	  ++c;
	}
  }
#undef fslider0
#undef fslider1
  return flags == 0;
}

void GxPresence::run_static(uint32_t n_samples, GxPresence *p, float *output)
{
  if (!p->compute((int32_t)n_samples, output))
    printf("convolver didn't run\n");
}
