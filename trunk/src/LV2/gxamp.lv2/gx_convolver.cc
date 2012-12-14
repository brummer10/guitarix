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


#include <string.h>
/****************************************************************
 ** some pieces in this file are copied from jconvolver
 */


/****************************************************************
 ** GxConvolverBase
 */

GxConvolverBase::~GxConvolverBase()
{
  if (is_runnable())
    {
      stop_process();
    }
}

void GxConvolverBase::adjust_values(
  unsigned int audio_size, unsigned int& count, unsigned int& offset,
  unsigned int& delay, unsigned int& ldelay, unsigned int& length,
  unsigned int& size, unsigned int& bufsize)
{

  if (bufsize < count)
    {
      bufsize = count;
    }
  if (bufsize < Convproc::MINPART)
    {
      bufsize = Convproc::MINPART;
    }
  if (offset > audio_size)
    {
      offset = audio_size;
    }
  if (!size)
    {
      if (offset + length > audio_size)
        {

          length = audio_size - offset;
        }
      if (!length)
        {
          length = audio_size - offset;
        }
      size = max(delay, ldelay) + offset + length;
    }
  else
    {
      if (delay > size)
        {
          delay = size;
        }
      if (ldelay > size)
        {
          ldelay = size;
        }
      if (offset > size - max(delay, ldelay))
        {
          offset = size - max(delay, ldelay);
        }
      if (length > size - max(delay, ldelay) - offset)
        {
          length = size - max(delay, ldelay) - offset;

        }
      if (!length)
        {
          length = size - max(delay, ldelay) - offset;
        }
    }
}

bool GxConvolverBase::start(int policy, int priority)
{
  int rc = start_process(priority, policy);
  if (rc != 0)
    {

      return false;
    }
  ready = true;
  return true;
}

bool GxConvolverBase::checkstate()
{
  if (state() == Convproc::ST_WAIT)
    {
      if (check_stop())
        {
          ready = false;
        }
      else
        {
          return false;
        }
    }
  else if (state() == ST_STOP)
    {
      ready = false;
    }
  return true;
}

struct CabDesc
{
  int ir_count;
  int ir_sr;
  float ir_data[];
};

template <int tab_size>
struct CabDesc_imp
{
  int ir_count;
  int ir_sr;
  float ir_data[tab_size];
  operator CabDesc&()
  {
    return *(CabDesc*)this;
  }
};
/**----------------------------- cabinet impulse response data --------------------------------**/
CabDesc_imp<192> cab_data_HighGain =
{
  192, 48000,
  {
    0.147081, 0.208808, 0.208996, 0.163228, 0.0858905, -0.0119104, -0.0932825, -0.121011, -0.0999426, -0.071073, -0.0403973, -0.00214844, 0.0287018,
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

CabDesc_imp<192> cab_data_AC30 = {
    192, 48000,
    { 7.32422e-05, 0.00015564, 0.00302429, 0.0057251, 0.00652466, 0.00614014, 0.00662537, 0.00419922, 0.00424194, -0.00379334, -0.00308838, -0.0103577, -0.0165436, 
      -0.0208832, -0.0206482, -0.027774, -0.0240204, -0.0231415, -0.0195801, -0.0178253, -0.015921, -0.0149628, -0.0164642, -0.0195465, -0.0218109, -0.0230652, 
      -0.0246216, -0.0256104, -0.0260925, -0.0210358, -0.0207489, -0.015863, -0.0106201, -0.0106628, -0.00259705, 0.00690613, 0.0146484, 0.026236, 0.0348633, 
      0.0506409, 0.0615387, 0.0747467, 0.0847351, 0.0917419, 0.0999908, 0.0957062, 0.093335, 0.0774262, 0.0564789, 0.0312073, 0.00177002, -0.0296539, 
      -0.047522, -0.0584259, -0.0557098, -0.0279785, 0.00585632, 0.0454926, 0.0777039, 0.0871948, 0.0838074, 0.0664886, 0.039389, 0.0180054, 0.00166931, 
      -0.00537415, 0.00290527, 0.00549622, 0.0210938, 0.0162201, 0.0135376, 0.00706482, 0.00458679, -0.00133667, 0.00446777, 0.00727539, 0.0085144, 0.00765076, 
      0.00744324, 0.00810852, 0.011911, 0.0117432, 0.00995789, 0.0141144, 0.0146301, 0.01651, 0.0221497, 0.0218842, 0.0201477, 0.0221466, 0.0210632, 
      0.0162018, 0.0183746, 0.0163727, 0.0168152, 0.0135895, 0.013208, 0.013208, 0.0101379, 0.0105713, 0.0109039, 0.0103699, 0.00718689, 0.0068634, 
      0.00429993, 0.0033844, 0.00050354, -9.15527e-05, 0.00460815, 0.00307617, 0.00213318, 0.00421143, 0.00546875, 0.00121155, 0.00124817, 0.0053894, 0.00281677, 
      0.0017395, 0.00368652, 0.00334778, 0.00233459, 0.00368347, 0.000366211, 0.00219727, 0.00175476, -0.00145874, 0.0006073, -0.000961304, -0.000509644, 0.00078125, 
      -0.00332336, 0.00331726, 0.000183105, -0.000747681, 0.00293274, -0.000637817, 0.000924683, -0.00149231, -0.00195312, -0.000564575, -0.00177917, 0.000491333, 0.00137024, 
      0.00274353, -0.000256348, 0.0024353, -0.00281372, -0.00131531, -0.00141602, -0.00289307, 0.000964355, 0.00017395, 0.00233765, -0.000726318, -0.000454712, -0.00398254, 
      -0.00518494, 0.000839233, 0.0168152, 0.0135895, 0.013208, 0.013208, 0.0101379, 0.0105713, 0.0109039, 0.0103699, 0.00718689, 0.0068634, 0.00429993, 
      0.0033844, 0.00050354, -9.15527e-05, 0.00460815, 0.00307617, 0.00213318, 0.00421143, 0.00546875, 0.00121155, 0.00124817, 0.0053894, 0.00281677, 0.0017395, 
      0.00368652, 0.00334778, 0.00233459, 0.00368347, 0.000366211, 0.00219727, 0.00175476, -0.00145874, 0.0006073, -0.000961304
    }
};

CabDesc_imp<192> contrast_ir_desc =
{
  192, 48000,
  {
    0.147081, 0.208808, 0.208996, 0.163228, 0.0858905, -0.0119104, -0.0932825, -0.121011, -0.0999426, -0.071073, -0.0403973, -0.00214844, 0.0287018,
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


/****************************************************************
 ** GxSimpleConvolver
 */

class CheckResample
{
private:
  float *vec;
  gx_resample::BufferResampler& resamp;
public:
  CheckResample(gx_resample::BufferResampler& resamp_): vec(0), resamp(resamp_) {}
  float *resample(int *count, float *impresp, unsigned int imprate, unsigned int samplerate)
  {
    if (imprate != samplerate)
      {
        vec = resamp.process(imprate, *count, impresp, samplerate, count);
        if (!vec)
          {
            if (samplerate)
              {
              }
            else
              {
              }
            return 0;
          }
        return vec;
      }
    return impresp;
  }
  ~CheckResample()
  {
    if (vec)
      {
        delete vec;
      }
  }
};

bool GxSimpleConvolver::configure(int count, float *impresp, unsigned int imprate)
{
  //printf("try configure()\n");
  CheckResample r(resamp);
  impresp = r.resample(&count, impresp, imprate, samplerate);
  if (!impresp)
    {
      printf("no impresp\n");
      return false;
    }
  cleanup();
  unsigned int bufsize = buffersize;
  if (bufsize < Convproc::MINPART)
    {
      bufsize = Convproc::MINPART;
    }
  if (Convproc::configure(1, 1, count, buffersize,
                          bufsize, Convproc::MAXPART))
    {
      printf("no configure\n");
      return false;
    }
  if (impdata_create(0, 0, 1, impresp, 0, count))
    {
      printf("no impdata_create()\n");
      return false;
    }
  //printf("configure()\n");

  return true;
}

bool GxSimpleConvolver::update(int count, float *impresp, unsigned int imprate)
{
  CheckResample r(resamp);
  impresp = r.resample(&count, impresp, imprate, samplerate);
  if (!impresp)
    {
      return false;
    }
  if (impdata_update(0, 0, 1, impresp, 0, count))
    {
      return false;
    }
  return true;
}

bool GxSimpleConvolver::compute(int count, float* input, float *output)
{
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
  memcpy(inpdata(0), input, count * sizeof(float));

  int flags = process(sync);

  memcpy(output, outdata(0), count * sizeof(float));
  //printf("run\n");
  return flags == 0;
}

void GxSimpleConvolver::run_static(uint32_t n_samples, GxSimpleConvolver *p, float *output)
{
  p->compute(n_samples, output, output);
}
