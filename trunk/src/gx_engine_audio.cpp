/*
 * Copyright (C) 2009 Hermann Meyer and James Warden
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 *
 *
 *    This is the Guitarix Audio Engine
 *
 *
 * --------------------------------------------------------------------------
 */

// denormal prevention is needed in the distortion unit for the low/high/cut part.
inline void GxEngine::add_dc (float& val)
{
  static const float anti_denormal = 1e-20;
  val += anti_denormal;
}

inline float GxEngine::my2powf(float y)
{
  return exp(log_2 * y);
}

inline float GxEngine::my4powf(float y)
{
  return exp(log_4 * y);
}

inline float GxEngine::clip (float x, float a)
{
  float x1,x2;
  float b = -a;

  x1 = fabs (x-a);
  x2 = fabs (x-b);
  x = x1 + (a+b);
  x -= x2;
  x *= 0.5;

  return x;
}

// the hard_cut unit run on sample base
inline float GxEngine::hard_cut(float in, float threshold)
{
  if ( in > threshold)
    {
      in = threshold;
    }
  else if ( in < -threshold)
    {
      in = -threshold;
    }

  return in;
}

// foldback distortion, run on sample base
inline float GxEngine::foldback(float in, float threshold)
{
  if (threshold == 0) threshold = 0.01f;

  if (fabs(in) > threshold)
    {
      in = fabs(fabs(fmod(in - threshold, threshold*4)) - threshold*2) - threshold;
    }
  return in;
}

// it isn't normalize, it's more a waveshaper funktion
inline float GxEngine::normalize(float in, float atan_shape, float shape)
{
  return atan_shape * atan(in*shape);
}


inline float GxEngine::sigmoid(float x)
{
  return x*(1.5f - 0.5f*x*x);
}

inline float GxEngine::saturate(float x, float t)
{
  if (fabs(x)<t)
    return x;
  else
    {
      if (x > 0.f)
        return t + (1.f-t)*sigmoid((x-t)/((1-t)*1.5f));
      else
        return -(t + (1.f-t)*sigmoid((-x-t)/((1-t)*1.5f)));
    }
}

// tube unit to run on sample base, it's unused for now, dont know if we need it any more
inline float GxEngine::valve(float in, float out)
{
  float a = 2.000 ;
  float b = 1.000 ;

  if ( in >= 0.0 )
    {
      out = a * in - b * in * in;
    }
  else
    {
      out = a * in + b * in * in;
    }

  return out;
}

inline void GxEngine::moving_filter(float** input, float** output, int sf)
{
  float *in = input[0];
  float * out = output[0];

  *out++ = (in[0]+in[1])*0.5;

  for (int i=1; i<sf-1; i++)
    {
      *out++ = (in[i-1]+in[i]+in[i+1])*0.3333334f;
    }
  *out++ = (in[sf]+in[sf-1])*0.5;

}

// oversample the input signal 2*, give a nice antialised effect
inline void GxEngine::over_sample(float** input, float** output, int sf)
{
  float * in = input[0];
  float * out = output[0];
  float x = in[0];
  float y = 0;
  for (int i=0; i<sf; i++)
    {
      x = in[i];
      *out++ = x;
      y = in[i+1];
      *out++ = (y+ x)*0.5;
    }
}

// downsample the processed signal to the jack_buffer size
inline void GxEngine::down_sample(float **input,float **output, int sf)
{
  float * in = input[0];
  float * out = output[0];
  float x = in[0];
  float y = 0;
  for (int i=0; i<sf; i++)
    {

      y = *in++;
      out[i] = x*0.75 + y*0.3;
      x = *in++;
    }
}

inline void GxEngine::noise_gate (int sf, float** input)
{
  float* in = input[0];
  float noisepulse = 0;
  float sumnoise = 0;
  int count = 0;
  float f_gate = fnglevel*0.01;

  for (int i=0; i<sf; i++)
    {
      count += 1;
      sumnoise += sqrf(fabs(*in++));
      noisepulse = sqrtf(sumnoise/count);
    }
  if (noisepulse > f_gate) ngate = 1; // -75db 0.001 = 65db
  else if (ngate > 0.01)ngate *= 0.996;

}

inline void GxEngine::noise_shaper (int sf, float** input, float** output)
{
  float* in = input[0];
  float* out = output[0];
  //float sharp = fsharp0;
  float press = fsharp0 * 5;




  for (int i=0; i<sf; i++)
    {
      float fTempgate0 = *in++;
      float fTempgate1 = max(1, fabsf(fTempgate0));
      float fTempgate2 = ((fSlowgate3 * (fRecgate0[1] >= fTempgate1)) + (fSlowgate2 * (fRecgate0[1] < fTempgate1)));
      fRecgate0[0] = ((fTempgate1 * (0 - (fTempgate2 - 1))) + (fRecgate0[1] * fTempgate2));
      float fTempgate3 = max(0, ((20 * log10f(fRecgate0[0])) + press));
      float fTempgate4 = (0.5f * min(1, max(0, (fSlowgate4 * fTempgate3))));
      *out++ = (fTempgate0 * powf(10, (5.000000e-02f * (fsharp0+((fTempgate3 * (0 - fTempgate4)) / (1 + fTempgate4))))));
      // post processing
      fRecgate0[1] = fRecgate0[0];
    }


}

// anti aliasing the sine wav, this unit can nicly run oversampeled
inline void GxEngine::AntiAlias (int sf, float** input, float** output)
{
  float* in = input[0];
  float* out = output[0];
  float alias[gx_jack::jack_bs] ;
  int state = 0;
  for (int i=0; i<sf; i++)
    {
      float x = *in++;
      add_dc(x);
      float a = alias[state];
      alias[state++] = x + a * faas1;
      if (state > 1.5)
        state = 0;
      *out++ = a ;
    }
}

// the resonace tube unit on frame base
inline void GxEngine::reso_tube (int fuzzy, int sf, float reso, float vibra,
                                 float** input, float** output)
{
  float* in = input[0];
  float* out = output[0];
  float ot = 0;
  float x = in[0];

  //----- resonator
  int 	iSlowRESO2 = int((int((vibra - 1)) & 4095));
  int 	iSlowRESO3 = int((int(vibra) & 4095));

  for (int i=0; i<sf; i++)
    {
      x = *in++;
      add_dc(x);
      if ( x >= 0.0 )
        {
          ot = ((2.f * x - 1.f * x * x) -x)*0.5;
        }
      else
        {
          ot =  ((2.f * x + 1.f * x * x) -x)*0.5;
        }
      //bit shifting
      ot = ot*0.001;
      //----- resonator
      fVecRESO0[IOTARESO&4095] = (ot + (reso * fRecRESO0[1]));
      fRecRESO0[0] = (0.5f * (fVecRESO0[(IOTARESO-iSlowRESO3)&4095] + fVecRESO0[(IOTARESO-iSlowRESO2)&4095]));
      ot = fRecRESO0[0];
      //bit shift back
      ot = (ot*fuzzy) *1000;
      *out++ = hard_cut(x + clip(ot*0.5,0.7),0.7);
      // post processing
      fRecRESO0[1] = fRecRESO0[0];
      IOTARESO = IOTARESO+1;

    }
}


// the oscilate tube unit on frame base
inline void GxEngine::osc_tube (int fuzzy, int sf, float reso, float vibra,
                                float** input, float** output)
{
  float* in = input[0];
  float* out = output[0];
  float ot = 0;
  float x = in[0];

  //----- resonator
  int 	iSlowRESO2 = int((int((vibra - 1)) & 4095));
  int 	iSlowRESO3 = int((int(vibra) & 4095));

  for (int i=0; i<sf; i++)
    {
      x = *in++;
      add_dc(x);
      if ( x >= 0.0 )
        {
          ot = ((2.f * x - 1.f * x * x) -x)*0.5;
        }
      else
        {
          ot =  ((2.f * x + 1.f * x * x) -x)*0.5;
        }
      // ocsillator
      iVecoscb0[0] = 1;
      fRecoscb0[0] = (0 - (((fRecoscb0[2] + (fConstoscb0 * fRecoscb0[1])) + iVecoscb0[1]) - 1));
      //bit shifting
      ot = ot*0.001;

      // resonator
      fVecRESO0[IOTARESO&4095] = (ot + (reso * fRecRESO0[1]));
      fRecRESO0[0] = (0.5f * (fVecRESO0[(IOTARESO-iSlowRESO3)&4095] + fVecRESO0[(IOTARESO-iSlowRESO2)&4095]));
      // speaker emulation 130Hz - 5000Hz
      fVecsp0[0] = fRecRESO0[0] * (3+fRecoscb0[0])*0.25f;
      fRecsp3[0] = (fConstsp9 * ((fVecsp0[0] - fVecsp0[1]) + (fConstsp8 * fRecsp3[1])));
      fRecsp2[0] = (fConstsp9 * ((fRecsp3[0] - fRecsp3[1]) + (fConstsp8 * fRecsp2[1])));
      fRecsp1[0] = (fRecsp2[0] - (fConstsp6 * ((fConstsp5 * fRecsp1[2]) + (fConstsp1 * fRecsp1[1]))));
      fRecsp0[0] = ((fConstsp6 * (fRecsp1[2] + (fRecsp1[0] + (2 * fRecsp1[1])))) - (fConstsp4 * ((fConstsp3 * fRecsp0[2]) + (fConstsp1 * fRecsp0[1]))));
      ot = (fConstsp4 * (fRecsp0[2] + (fRecsp0[0] + (2 * fRecsp0[1]))));
      //bit shift back
      ot = (ot*fuzzy) *1000;
      // output
      *out++ = clip(x + (ot*0.5),0.7);
      // post processing
      // resonator
      fRecRESO0[1] = fRecRESO0[0];
      IOTARESO = IOTARESO+1;
      // oscilloscope
      fRecoscb0[2] = fRecoscb0[1];
      fRecoscb0[1] = fRecoscb0[0];
      iVecoscb0[1] = iVecoscb0[0];
      // speaker emulation
      fRecsp0[2] = fRecsp0[1];
      fRecsp0[1] = fRecsp0[0];
      fRecsp1[2] = fRecsp1[1];
      fRecsp1[1] = fRecsp1[0];
      fRecsp2[1] = fRecsp2[0];
      fRecsp3[1] = fRecsp3[0];
      fVecsp0[1] = fVecsp0[0];
    }
}

// the tube unit on frame base, it's also the drive unit just with other variables
inline void GxEngine::fuzzy_tube (int fuzzy, int mode, int sf,
                                  float** input, float** output)
{
  float* in = input[0];
  float* out = output[0];
  float ot = 0;
  float x = in[0];
  float a = 2.000 ;
  float b = 1.000 ;
  double c = 0.5;

  if (mode)
    {
      a = 4.000 ;
      b = 4.000 ;
      c = 0.125;
    }

  for (int i=0; i<sf; i++)
    {
      x = *in++;
      if ( x >= 0.0 )
        {
          ot = ((a * x - b * x * x) -x)*c;
        }
      else
        {
          ot =  ((a * x + b * x * x) -x)*c;
        }
      *out++ = hard_cut(x + ot*fuzzy*0.5,0.7);
    }
}

// the preamp on frame base, it's a gloubi-boulga followed by a third-degree polynomial
// and then the "normalize", output will smoth down by 0.75
inline void GxEngine::preamp(int sf, float** input, float** output,
                             float atan_shape,float f_atan)
{
  float* in = input[0];
  float* out = output[0];

  for (int i=0; i<sf; i++)
    {
      float  x = *in++ *0.001 ;
      float  fTemp0in = (x-0.15*(x*x))-(0.15*(x*x*x));
      x = 1.5f * fTemp0in - 0.5f * fTemp0in *fTemp0in * fTemp0in;
      fTemp0in = normalize(x,atan_shape,f_atan);
      *out++ = fTemp0in*750;

    }

}

void GxEngine::get_jconv_output(float **input,float **output,int sf)
{
  float*  input1 = input[1];
  float*  input2 = input[2];
  float*  out1 = output[0];
  float*  out2 = output[1];

  for (int i=0; i<sf; i++)
    {
      *out1++ +=  (*input1++ );
      *out2++ +=  (*input2++ );
    }

}

//==============================================================================
//
//             this is the process callback called from jack
//
//==============================================================================
void GxEngine::compute (int count, float** input, float** output)
{
  // retrieve engine state
  const GxEngineState estate = (GxEngineState)checky;

  //------------ determine processing type
  unsigned short process_type = ZEROIZE_BUFFERS;

  if (gx_jack::NO_CONNECTION == 0) // ports connected
    {
      switch (estate)
        {
        case kEngineOn:
          process_type = PROCESS_BUFFERS;
          break;

        case kEngineBypass:
          process_type = JUSTCOPY_BUFFERS;
          break;

        default: // engine off or whatever: zeroize
          break;
        }
    }

  //------------ main processing routine
  switch (process_type)
    {

    case PROCESS_BUFFERS:
      process_buffers(count, input, output);
      break;

      // --------- just copy input to outputs
    case JUSTCOPY_BUFFERS:

      // only when jconv is not running: copy input to output
      if (!gx_jconv::jconv_is_running)
        {
          // copy input to output
          (void)memcpy(output[0], input[0], sizeof(float)*count);
          (void)memcpy(output[1], input[0], sizeof(float)*count);

          int tuner_on = gx_gui::shownote + (int)dsp::isMidiOn() + 1;

          // copy clean audio input for the tuner and midi_process
          if (tuner_on > 0)
            {
              float sumt = 0;
              int cts = 0;

              (void)memcpy(checkfreq, input[0], sizeof(float)*count);
              for (int i=0; i<count; i++)
                {

                  if (gx_gui::showwave == 1) vivi = checkfreq[i];

                  float fTemphp0 = checkfreq[i] *2;
                  // low and highpass filter
                  tunerstage1=tunerstage1+(tunerfilter*(fTemphp0-tunerstage1));
                  tunerstage2=tunerstage2+(tunerfilter*(tunerstage1-tunerstage2));
                  tunerstageh1=tunerstageh1+(tunerfilterh*(tunerstage2-tunerstageh1));
                  tunerstageh2=tunerstageh2+(tunerfilterh*(tunerstageh1-tunerstageh2));
                  fTemphp0 = tunerstage2-tunerstageh2;
                  // waveshaper
                  float fTemphps0 = (1.5f * fTemphp0 - 0.5f * fTemphp0 *fTemphp0 * fTemphp0);
                  // now run a fft
                  fVechp0[0] = fTemphps0;
                  fRechp0[0] = ((fConsthp3 * (fVechp0[0] - fVechp0[1])) + (fConsthp2 * fRechp0[1]));
                  float fTemphp1  = fRechp0[0];
                  int iTempt0 = (1 + iRect2[1]);
                  float fTempt1 = (1.0f / tanf((fConstan0 * max(100, fRect0[1]))));
                  float fTempt2 = (1 + fTempt1);
                  fVect0[0] = fTemphp1;
                  fRect5[0] = (fConstan3 * ((fVect0[0] - fVect0[1]) + (fConstan2 * fRect5[1])));
                  fVect1[0] = (fRect5[0] / fTempt2);
                  fRect4[0] = (fVect1[1] + ((fRect5[0] + ((fTempt1 - 1) * fRect4[1])) / fTempt2));
                  int iTempt4 = ((fRect4[1] < 0) & (fRect4[0] >= 0));
                  iRect3[0] = (iTempt4 + (iRect3[1] % 10));
                  iRect2[0] = ((1 - (iTempt4 & (iRect3[0] ==  10.0f))) * iTempt0);
                  int iTempt5 = (iRect2[0] == 0);
                  iRect1[0] = ((iTempt5 * iTempt0) + ((1 - iTempt5) * iRect1[1]));
                  fRect0[0] = (fSamplingFreq * ((10.0f / max(iRect1[0], 1)) - (10.0f * (iRect1[0] == 0))));
                  // get the frequence here
                  float fConsta4s = fRect0[0];
                  // smoth tuner output by rms the value peer frame
                  cts += 1;
                  sumt += sqrf(fConsta4s);
                  fConsta4 = sqrtf(sumt/cts);

                  if (gx_gui::shownote == 0)
                    {
                      fConsta1 = 1000.0f;
                      gx_gui::shownote = -1;
                    }

                  fRect0[1] = fRect0[0];
                  iRect1[1] = iRect1[0];
                  iRect2[1] = iRect2[0];
                  iRect3[1] = iRect3[0];
                  fRect4[1] = fRect4[0];
                  fVect1[1] = fVect1[0];
                  fRect5[1] = fRect5[0];
                  fVect0[1] = fVect0[0];
                  fRechp0[1] = fRechp0[0];
                  fVechp0[1] = fVechp0[0];


                }



            }

           (void)memcpy(get_frame, output[0], sizeof(float)*count);
           (void)memcpy(get_frame1, output[1], sizeof(float)*count);


        }
      else // when jconv is running, init the wet/dry slider and run a minimal loop
        {
          // get the wet/dry slider settings
          float fSlow81 = fslider24;
          float fSlow82 = (1 - max(0, (0 - fSlow81)));
          float fSlow83 = fslider25;
          float fSlow84 = (1 - max(0, fSlow83));
          float fSlow85 = (fSlow84 * fSlow82);
          float fSlow89 = (1 - max(0, (0 - fSlow83)));
          float fSlow90 = (fSlow89 * fSlow82);
          float sumt = 0;

          // pointer to the jack_buffer
          float*  input0 = input[0];
          float* output0 = output[2];
          float* output1 = output[0];
          float* output2 = output[3];
          float* output3 = output[1];

          int cts = 0;
          int tuner_on = gx_gui::shownote + (int)dsp::isMidiOn() + 1;

          // copy clean audio input for the tuner and midi_process
          if (tuner_on > 0)
            (void)memcpy(checkfreq, input0, sizeof(float)*count);

          for (int i=0; i<count; i++)
            {

              if (gx_gui::showwave == 1) vivi = input0[i];

              if (tuner_on > 0) // enable tuner when show note or play midi
                {
                  float fTemphp0 = checkfreq[i] *2;
                  // low and highpass filter
                  tunerstage1=tunerstage1+(tunerfilter*(fTemphp0-tunerstage1));
                  tunerstage2=tunerstage2+(tunerfilter*(tunerstage1-tunerstage2));
                  tunerstageh1=tunerstageh1+(tunerfilterh*(tunerstage2-tunerstageh1));
                  tunerstageh2=tunerstageh2+(tunerfilterh*(tunerstageh1-tunerstageh2));
                  fTemphp0 = tunerstage2-tunerstageh2;
                  // waveshaper
                  float fTemphps0 = (1.5f * fTemphp0 - 0.5f * fTemphp0 *fTemphp0 * fTemphp0);
                  // now run a fft
                  fVechp0[0] = fTemphps0;
                  fRechp0[0] = ((fConsthp3 * (fVechp0[0] - fVechp0[1])) + (fConsthp2 * fRechp0[1]));
                  float fTemphp1  = fRechp0[0];
                  int iTempt0 = (1 + iRect2[1]);
                  float fTempt1 = (1.0f / tanf((fConstan0 * max(100, fRect0[1]))));
                  float fTempt2 = (1 + fTempt1);
                  fVect0[0] = fTemphp1;
                  fRect5[0] = (fConstan3 * ((fVect0[0] - fVect0[1]) + (fConstan2 * fRect5[1])));
                  fVect1[0] = (fRect5[0] / fTempt2);
                  fRect4[0] = (fVect1[1] + ((fRect5[0] + ((fTempt1 - 1) * fRect4[1])) / fTempt2));
                  int iTempt4 = ((fRect4[1] < 0) & (fRect4[0] >= 0));
                  iRect3[0] = (iTempt4 + (iRect3[1] % 10));
                  iRect2[0] = ((1 - (iTempt4 & (iRect3[0] ==  10.0f))) * iTempt0);
                  int iTempt5 = (iRect2[0] == 0);
                  iRect1[0] = ((iTempt5 * iTempt0) + ((1 - iTempt5) * iRect1[1]));
                  fRect0[0] = (fSamplingFreq * ((10.0f / max(iRect1[0], 1)) - (10.0f * (iRect1[0] == 0))));
                  // get the frequence here
                  float fConsta4s = fRect0[0];
                  // smoth tuner output by rms the value peer frame
                  cts += 1;
                  sumt += sqrf(fConsta4s);
                  fConsta4 = sqrtf(sumt/cts);
                }
              if (gx_gui::shownote == 0)
                {
                  fConsta1 = 1000.0f;
                  gx_gui::shownote = -1;
                }


              // this is the left "extra" port to run jconv in bybass mode
              *output0++ = (fSlow85 * input0[i]);
              // the left output port
              *output1++ = (fSlow84 * input0[i]);
              // this is the right "extra" port to run jconv in bybass mode
              *output2++ = (fSlow90 * input0[i]);
              // the right output port
              *output3++ = (fSlow89 * input0[i]);

              // post processing tuner
              if (tuner_on > 0) // enable tuner when show note or play midi
                {
                  fRect0[1] = fRect0[0];
                  iRect1[1] = iRect1[0];
                  iRect2[1] = iRect2[0];
                  iRect3[1] = iRect3[0];
                  fRect4[1] = fRect4[0];
                  fVect1[1] = fVect1[0];
                  fRect5[1] = fRect5[0];
                  fVect0[1] = fVect0[0];
                  fRechp0[1] = fRechp0[0];
                  fVechp0[1] = fVechp0[0];
                }

            }



            output1 = output[0];
            output3 = output[1];
            (void)memcpy(get_frame, output1, sizeof(float)*count);
            (void)memcpy(get_frame1, output3, sizeof(float)*count);
        }


      break;


      // ------- zeroize buffers
    case ZEROIZE_BUFFERS:
    default:

      // the extra port register can only run clean on frame base, therfor the
      // variable jconv_is_running must check on frame base, not in the inner loop.

      // no need of loop.
      // You will avoid triggering an if statement for each frame
      (void)memset(output[0], 0, count*sizeof(float));
      (void)memset(output[1], 0, count*sizeof(float));

      // only when jconv is running
      if (gx_jconv::jconv_is_running)
        {
          (void)memset(output[2], 0, count*sizeof(float));
          (void)memset(output[3], 0, count*sizeof(float));
        }

      break;
    }
}


//======== private method: process buffers on demand
void GxEngine::process_buffers(int count, float** input, float** output)
{
  // precalculate values with need update peer frame
  // compressor
  float fSlowcom0 = fentrycom0;
  float fSlowcom1 = expf((0 - (fConstcom2 / max(fConstcom2, fslidercom0))));
  float fSlowcom2 = expf((0 - (fConstcom2 / max(fConstcom2, fslidercom1))));
  float fSlowcom3 = fentrycom1;
  float fSlowcom4 = (1.000000f / (1.000000e-03f + fSlowcom3));
  float fSlowcom5 = fentrycom2;
  // compressor end
  float 	fSlow0 = fslider0;

  // float 	fSlow15 = checky;
  // float 	fSlow16 = (7.118644f * fSlow15);
  float fSlow18 = (9.999871e-04f * powf(10, (5.000000e-02f * fslider3)));
  // distortion
  float fSlow19 = (1.0f - fslider4);
  float fSlow20 = fslider5;
  float fSlow23 = (1.0f / tanf((fConst6 * fentry0)));
  float fSlow24 = (fSlow23 - 1);
  float fSlow25 = (1.0f / (1 + fSlow23));
  float fSlow26 = (1.0f / tanf((fConst8 * (fConst7 - (6.283185f * fentry1)))));
  float fSlow27 = (1 + fSlow26);
  float fSlow28 = (1.0f / fSlow27);
  float fSlow29 = (0 - ((fSlow26 - 1) / fSlow27));
  float fSlow31 = tanf((fConst6 * fslider6));
  float fSlow32 = (2 * (1 - (1.0f / (fSlow31 * fSlow31))));
  float fSlow33 = (1.0f / fSlow31);
  float fSlow34 = (1 + ((fSlow33 - 0.765367f) / fSlow31));
  float fSlow35 = (1.0f / (1 + ((0.765367f + fSlow33) / fSlow31)));
  float fSlow36 = (1 + ((fSlow33 - 1.847759f) / fSlow31));
  float fSlow37 = (1.0f / (1 + ((1.847759f + fSlow33) / fSlow31)));
  float fSlow38 = (fConst6 * fslider7);
  float fSlow39 = (1.0f / (1 + fSlow38));
  float fSlow40 = (1 - fSlow38);
  float fSlow42 = fslider8;
  float fSlow43 = powf(10.0f, (2 * fslider9));
  float fSlow44 = (9.999871e-04f * powf(10, (5.000000e-02f * (fslider10 - 10))));
  // distortion end
  float fSlow56 = fslider11;
  float fmapping = (2.384186e-10f*(20*fSlow56));
  float fSlow57 = (9.999872e-05f * powf(4.0f, fSlow56));
  float fSlow58 = fslider13;
  float fSlow59 = ((1 - max(0, (0 - fSlow58))) * fslider12);
  float fSlow60 = powf(2.0f, (2.3f * fSlow56));
  float fSlow61 = (1 - (fConst10 * (fSlow60 / powf(2.0f, (1.0f + (2.0f * (1.0f - fSlow56)))))));
  float fSlow62 = (9.999871e-04f * (0 - (2.0f * (fSlow61 * cosf((fConst9 * fSlow60))))));
  float fSlow63 = (9.999871e-04f * (fSlow61 * fSlow61));
  float fSlow64 = (1 - max(0, fSlow58));
  float fSlow66 = (0.5 + fslider14);
  float fSlow67 = (2 * (1 - fSlow66));
  float fSlow68 = fslider15;
  float fSlow69 = (1 - fSlow68);
  float fSlow70 = (0.7f + (0.28f * fslider16));
  float fSlow72 = (9.999871e-04f * powf(10, (5.000000e-02f * fslider17)));
  float fSlow74 = (1.000000e-02f * fslider19);
  float fSlow76 = expf((0 - (fConst6 * fslider20)));
  float fSlow77 = (2 * cosf((fConst12 * fslider21)));
  float fSlow78 = (0.5f * (fslider22 * (1 - (fSlow76 * fSlow76))));
  float fSlow80 = fslider23;
  float fSlow81 = fslider24;
  float fSlow82 = (1 - max(0, (0 - fSlow81)));
  float fSlow83 = fslider25;
  float fSlow84 = (1 - max(0, fSlow83));
  float fSlow85 = (fSlow84 * fSlow82);
  float fSlow86 = (1 - max(0, fSlow81));
  float fSlow87 = (fSlow84 * fSlow86);
  float fSlow89 = (1 - max(0, (0 - fSlow83)));
  float fSlow90 = (fSlow89 * fSlow82);
  float fSlow91 = (fSlow89 * fSlow86);
  float drivem1 = drive - 1.0f;
  float fSlowover0 = (9.999871e-04f * powf(10, (5.000000e-02f * (drive*-0.5))));
  float fSlowvib0 = fvibrato;
  float sumt = 0;
  float atan_shape = 1.0/atan(fatan);
  float f_atan = fatan;
  float threshold = fthreshold;
  float	f_resotube1 = fresotube1;
  float f_resotube2 = fresotube2;
  //chorus
  float 	fSlow_CH0 = (fConst_CH0 * fslider_CH0);
  float 	fSlow_CH1 = fslider_CH1;
  float 	fSlow_CH2 = (fConst_CH1 * fslider_CH2);
  float 	fSlow_CH3 = fslider_CH3;

  float fSlowinjc = (9.999871e-04f * powf(10, (5.000000e-02f * fjc_ingain)));


  //----- tone only reset when value have change
  fslider_tone_check1 = (fslider_tone1+fslider_tone0+fslider_tone2)*100;
  if (fslider_tone_check1 != fslider_tone_check)
    {
      fSlow_mid_tone = (fslider_tone1*0.5);
      fSlow_tone0 = powf(10, (2.500000e-02f * (fslider_tone0- fSlow_mid_tone)));
      fSlow_tone1 = (1 + fSlow_tone0);
      fSlow_tone2 = (fConst_tone1 * fSlow_tone1);
      fSlow_tone3 = (2 * (0 - ((1 + fSlow_tone2) - fSlow_tone0)));
      fSlow_tone4 = (fConst_tone1 * (fSlow_tone0 - 1));
      fSlow_tone5 = (fConst_tone2 * sqrtf(fSlow_tone0));
      fSlow_tone6 = (fSlow_tone1 - (fSlow_tone5 + fSlow_tone4));
      fSlow_tone7 = powf(10, (2.500000e-02f * fSlow_mid_tone));
      fSlow_tone8 = (1 + fSlow_tone7);
      fSlow_tone9 = (fConst_tone4 * fSlow_tone8);
      fSlow_tone10 = (2 * (0 - ((1 + fSlow_tone9) - fSlow_tone7)));
      fSlow_tone11 = (fSlow_tone7 - 1);
      fSlow_tone12 = (fConst_tone4 * fSlow_tone11);
      fSlow_tone13 = sqrtf(fSlow_tone7);
      fSlow_tone14 = (fConst_tone5 * fSlow_tone13);
      fSlow_tone15 = (fSlow_tone8 - (fSlow_tone14 + fSlow_tone12));
      fSlow_tone16 = (fConst_tone1 * fSlow_tone8);
      fSlow_tone17 = (0 - (2 * ((fSlow_tone7 + fSlow_tone16) - 1)));
      fSlow_tone18 = (fConst_tone2 * fSlow_tone13);
      fSlow_tone19 = (fConst_tone1 * fSlow_tone11);
      fSlow_tone20 = ((1 + (fSlow_tone7 + fSlow_tone19)) - fSlow_tone18);
      fSlow_tone21 = powf(10, (2.500000e-02f * (fslider_tone2-fSlow_mid_tone)));
      fSlow_tone22 = (1 + fSlow_tone21);
      fSlow_tone23 = (fConst_tone4 * fSlow_tone22);
      fSlow_tone24 = (0 - (2 * ((fSlow_tone21 + fSlow_tone23) - 1)));
      fSlow_tone25 = (fConst_tone5 * sqrtf(fSlow_tone21));
      fSlow_tone26 = (fConst_tone4 * (fSlow_tone21 - 1));
      fSlow_tone27 = ((1 + (fSlow_tone21 + fSlow_tone26)) - fSlow_tone25);
      fSlow_tone28 = (2 * (0 - ((1 + fSlow_tone23) - fSlow_tone21)));
      fSlow_tone29 = (fSlow_tone21 + fSlow_tone25);
      fSlow_tone30 = ((1 + fSlow_tone29) - fSlow_tone26);
      fSlow_tone31 = (fSlow_tone22 - (fSlow_tone25 + fSlow_tone26));
      fSlow_tone32 = (1.0f / (1 + (fSlow_tone26 + fSlow_tone29)));
      fSlow_tone33 = (fSlow_tone8 - (fSlow_tone18 + fSlow_tone19));
      fSlow_tone34 = (2 * (0 - ((1 + fSlow_tone16) - fSlow_tone7)));
      fSlow_tone35 = (fSlow_tone7 + fSlow_tone18);
      fSlow_tone36 = ((1 + fSlow_tone35) - fSlow_tone19);
      fSlow_tone37 = (1.0f / (1 + (fSlow_tone19 + fSlow_tone35)));
      fSlow_tone38 = (fSlow_tone7 * ((1 + (fSlow_tone7 + fSlow_tone12)) - fSlow_tone14));
      fSlow_tone39 = (fSlow_tone7 + fSlow_tone14);
      fSlow_tone40 = (fSlow_tone7 * (1 + (fSlow_tone12 + fSlow_tone39)));
      fSlow_tone41 = (((fSlow_tone7 + fSlow_tone9) - 1) * (0 - (2 * fSlow_tone7)));
      fSlow_tone42 = (1.0f / ((1 + fSlow_tone39) - fSlow_tone12));
      fSlow_tone43 = (fSlow_tone0 * ((1 + (fSlow_tone0 + fSlow_tone4)) - fSlow_tone5));
      fSlow_tone44 = (fSlow_tone0 + fSlow_tone5);
      fSlow_tone45 = (fSlow_tone0 * (1 + (fSlow_tone4 + fSlow_tone44)));
      fSlow_tone46 = (((fSlow_tone0 + fSlow_tone2) - 1) * (0 - (2 * fSlow_tone0)));
      fSlow_tone47 = (1.0f / ((1 + fSlow_tone44) - fSlow_tone4));
      fslider_tone_check = (fslider_tone1+fslider_tone0+fslider_tone2)*100;
    }
  // tone end


  int ifuzzytube = int(ffuzzytube);
  int itube = int(ftube);
  int iresotube3 = int(fresotube3);
  int itube3 = int(ftube3);
  int ipredrive = int(fpredrive);
  int iprdr = int(fprdr);
  int iupsample = int(fupsample);

  // distortion
  int iSlow21 = int((int((fSlow20 - 1)) & 4095));
  int iSlow22 = int((int(fSlow20) & 4095));
  int iSlow30 = int(fcheckbox2);
  int iSlow41 = int(fcheckbox3);
  // distortion end
  int iSlow45 = int(fcheckbox4);
  int iSlow65 = int(fcheckbox5);
  int iSlow71 = int(fcheckbox6);
  int iSlow73 = int((1 + int((int((int((fConst11 * fslider18)) - 1)) & 131071))));
  int iSlow75 = int(fcheckbox7);
  int iSlow79 = int(fcheckbox8);
  int iSlow88 = int(gx_jconv::checkbox7);
  int icheckboxcom1 = int(fcheckboxcom1);
  int icheckbox1 = int(fcheckbox1);
  int ioverdrive4 = int(foverdrive4);
  int cts = 0;
  int ifuse = ffuse;
  int tuner_on = gx_gui::shownote + (int)dsp::isMidiOn() + 1;
  int ing = int(fng);
  int iboost = int(fboost);
  int inoise_g = int(fnoise_g);
  // autowah
  int iautowah = int(fautowah);
  //chorus
  int ichorus = fchorus;


  // pointer to the jack_buffer
  float*  input0 = input[0];
  //moving_filter(input, input, count);
  // copy clean audio input for the tuner and midi_process
  if (tuner_on > 0) {
    (void)memcpy(checkfreq, input0, sizeof(float)*count);
   moving_filter(&checkfreq, &checkfreq, count);
  }


  // run pre_funktions on frame base
  if (inoise_g) noise_gate (count,input);
  else ngate = 1;
  if (ing) noise_shaper(count,input,input);


  // 2*oversample
  if (iupsample)
    {
      over_sample(input,&oversample,count);
      //  if (icheckbox1 == 1)  preamp(count*2,&oversample,&oversample,atan_shape,f_atan);
      // if (ing)  noise_gate(count*2,&oversample,&oversample);
      if (itube)    fuzzy_tube(ifuzzytube, 0,count*2,&oversample,&oversample);
      if (itube3)   reso_tube(iresotube3,count*2,f_resotube1, f_resotube2, &oversample,&oversample);
      if (iprdr)    fuzzy_tube(ipredrive, 1,count*2,&oversample,&oversample);
      if (antialis0)  AntiAlias(count*2,&oversample,&oversample);
      down_sample(&oversample,input,count);
    }
  // or plain sample
  else
    {
      //   if (icheckbox1 == 1)  preamp(count,input,input,atan_shape,f_atan);
      //if (ing)  noise_gate(count,input,input);
      if (itube)    fuzzy_tube(ifuzzytube, 0,count,input,input);
      if (itube3)   osc_tube(iresotube3,count,f_resotube1, f_resotube2,input,input);
      if (iprdr)    fuzzy_tube(ipredrive, 1,count,input,input);
      if (antialis0)  AntiAlias(count,input,input);
    }

  // pointers to the jack_output_buffers
  float* output0 = output[2];
  float* output1 = output[0];
  float* output2 = output[3];
  float* output3 = output[1];
  register float fTemp0 = input0[0];
  // start the inner loop count = jack_frame
  for (int i=0; i<count; i++)
    {

      fTemp0 = *input0++;
      // when the ocilloscope draw wav by sample (mode 3) get the input value
      if (gx_gui::showwave == 1) vivi = fTemp0;

      if (tuner_on > 0) // enable tuner when show note or play midi
        {
          float fTemphp0 = checkfreq[i] *2;
          // low and highpass filter
          tunerstage1=tunerstage1+(tunerfilter*(fTemphp0-tunerstage1));
          tunerstage2=tunerstage2+(tunerfilter*(tunerstage1-tunerstage2));
          tunerstageh1=tunerstageh1+(tunerfilterh*(tunerstage2-tunerstageh1));
          tunerstageh2=tunerstageh2+(tunerfilterh*(tunerstageh1-tunerstageh2));
          fTemphp0 = tunerstage2-tunerstageh2;
          // waveshaper
          float fTemphps0 = (1.5f * fTemphp0 - 0.5f * fTemphp0 *fTemphp0 * fTemphp0);
          // now calculate the frequence
          fVechp0[0] = fTemphps0;
          fRechp0[0] = ((fConsthp3 * (fVechp0[0] - fVechp0[1])) + (fConsthp2 * fRechp0[1]));
          float fTemphp1  = fRechp0[0];
          int iTempt0 = (1 + iRect2[1]);
          float fTempt1 = (1.0f / tanf((fConstan0 * max(100, fRect0[1]))));
          float fTempt2 = (1 + fTempt1);
          fVect0[0] = fTemphp1;
          fRect5[0] = (fConstan3 * ((fVect0[0] - fVect0[1]) + (fConstan2 * fRect5[1])));
          fVect1[0] = (fRect5[0] / fTempt2);
          fRect4[0] = (fVect1[1] + ((fRect5[0] + ((fTempt1 - 1) * fRect4[1])) / fTempt2));
          int iTempt4 = ((fRect4[1] < 0) & (fRect4[0] >= 0));
          iRect3[0] = (iTempt4 + (iRect3[1] % 10));
          iRect2[0] = ((1 - (iTempt4 & (iRect3[0] ==  10.0f))) * iTempt0);
          int iTempt5 = (iRect2[0] == 0);
          iRect1[0] = ((iTempt5 * iTempt0) + ((1 - iTempt5) * iRect1[1]));
          fRect0[0] = (fSamplingFreq * ((10.0f / max(iRect1[0], 1)) - (10.0f * (iRect1[0] == 0))));
          // get the frequence here
          float fConsta4s = fRect0[0];
          // smoth tuner output by rms the value peer frame
          if (fTemphp0>0.0001)
          {
          cts += 1;
          sumt += sqrf(old_freq);
          cts += 1;
          sumt += sqrf(fConsta4s);
          fConsta4 = sqrtf(sumt/cts);
          }
          else if(fConsta4>0) fConsta4 -= 0.05;
        }
      if (gx_gui::shownote == 0)
        {
          fConsta1 = 1000.0f;
          gx_gui::shownote = -1;
        }

      if (iSlow65)    //crybaby
        {

          if (iautowah)
            {
              //float fTempw0 = (fTemp0*0.001);
              //fTempw0 = (fTempw0*1000);
              int iTempwah1 = abs(int((4194304 * (fTemp0+ 1e-20))));
              iVecwah0[IOTAWAH&1023] = iTempwah1;
              iRecwah2[0] = ((iVecwah0[IOTAWAH&1023] + iRecwah2[1]) - iVecwah0[(IOTAWAH-1000)&1023]);
              float fTempwah2 = min(1, max(0, (fmapping * float(iRecwah2[0]))));
              fRec19[0] = ((9.999872e-05f * my4powf( fTempwah2)) + (0.999f * fRec19[1]));
              add_dc(fTempwah2);
              float fTempwah3 = my2powf(2.3f * fTempwah2);
              float fTempwah4 = (1 - (fConst10 * (fTempwah3 / my2powf(1.0f + (2.0f * (1.0f - fTempwah2))))));
              fRec20[0] = ((9.999871e-04f * (0 - (2.0f * (fTempwah4 * cosf((fConst9 * fTempwah3)))))) + (0.999f * fRec20[1]));
              fRec21[0] = ((9.999871e-04f * (fTempwah4 * fTempwah4)) + (0.999f * fRec21[1]));
              fRec18[0] = (0 - (((fRec21[0] * fRec18[2]) + (fRec20[0] * fRec18[1])) - (fSlow59 * (fTemp0 * fRec19[0]))));
              fTemp0 = (((fSlow64 *fTemp0) + fRec18[0]) - fRec18[1]);
            }
          else
            {

              fRec19[0] = (fSlow57 + (0.999f * fRec19[1])); //wah slider
              fRec20[0] = (fSlow62 + (0.999f * fRec20[1]));
              fRec21[0] = (fSlow63 + (0.999f * fRec21[1]));  // wah slider


              fRec18[0] = (0 - (((fRec21[0] * fRec18[2]) + (fRec20[0] * fRec18[1])) - (fSlow59 * (fTemp0 * fRec19[0]))));
              fTemp0 = ((fRec18[0] + (fSlow64 * fTemp0)) - fRec18[1]);
            }
        }                                     //crybaby ende


      if (icheckboxcom1)     // compressor
        {
          add_dc(fTemp0);
          float fTempcom0 = fTemp0;
          fReccom1[0] = ((fConstcom1 * fabsf(fTempcom0)) + (fConstcom0 * fReccom1[1]));
          float fTempcom2 = max(fReccom1[0], fReccom1[0]);
          float fTempcom3 = ((fSlowcom2 * (fReccom0[1] >= fTempcom2)) + (fSlowcom1 * (fReccom0[1] < fTempcom2)));
          fReccom0[0] = ((fTempcom2 * (1 - fTempcom3)) + (fReccom0[1] * fTempcom3));
          float fTempcom4 = max(0, ((fSlowcom3 + (20 * log10f(fReccom0[0]))) - fSlowcom0));
          float fTempcom5 = min(1, max(0, (fSlowcom4 * fTempcom4)));
          float fTempcom6 = (fSlowcom5 * fTempcom5);
          float fTempcom7 = ((fTempcom4 / ((1 + fTempcom6) - fTempcom5)) * (fTempcom5 - fTempcom6));
          float fTempcom8 = powf(10, (5.000000e-02f * fTempcom7));
          fTemp0 = (fTempcom0 * fTempcom8);
        }
      else  add_dc(fTemp0);
      // compressor end


      // gain in
      fRec4[0] = ((0.999f * fRec4[1]) + fSlow18);
      fTemp0 = (fRec4[0] * fTemp0);

      if (icheckbox1)     // preamp
        {
          float  fTemp0in = (fTemp0-0.15*(fTemp0*fTemp0))-(0.15*(fTemp0*fTemp0*fTemp0));
          fTemp0 = 1.5f * fTemp0in - 0.5f * fTemp0in *fTemp0in * fTemp0in;
          fTemp0in = normalize(fTemp0,atan_shape,f_atan);
          //fTemp0 = valve(fTemp0in,fTemp0in)*0.75;
          fTemp0 = hard_cut(fTemp0in,0.7);
        }  //preamp ende


      // vibrato
      if (fresoon)
        {
          fRec3[0] = hard_cut (0.5f * ((2.0 * fTemp0) + ( fSlowvib0* fRec3[1])),0.7);  //resonanz 1.76f
          fTemp0 = fRec3[0];
        }

      if (ioverdrive4)     // overdrive
        {
          //float fTempdr0 = fTemp0;
          float fTempdr1 = fabs(fTemp0);
          fRecover0[0] = (fSlowover0 + (0.999000f * fRecover0[1]));
          fTemp0 = (fTemp0*(fTempdr1 + drive)/(fTemp0*fTemp0 + drivem1*fTempdr1 + 1.0f)) * fRecover0[0];

        }

      if (iSlow45)     // distortion
        {
          float 	S6[2];
          float 	S7[2];
          float 	S8[2];
          fTemp0 = (fTemp0*0.001);
          fVec1[IOTA&4095] = ((fTemp0*1000) + (fSlow19 * fRec6[1]));
          fRec6[0] = (0.5f * (fVec1[(IOTA-iSlow22)&4095] + fVec1[(IOTA-iSlow21)&4095]));
          add_dc(fRec6[0]);
          S8[0] = fRec6[0];
          fVec2[0] = (fSlow25 * fRec6[0]);
          fRec8[0] = (fVec2[1] + (fSlow25 * (fRec6[0] + (fSlow24 * fRec8[1]))));
          fVec3[0] = (fSlow28 * fRec8[0]);
          fRec7[0] = ((fVec3[0] + (fSlow29 * fRec7[1])) - fVec3[1]);
          S8[1] = fRec7[0];
          float fTemp3 = S8[iSlow30];
          add_dc(fTemp3);
          S7[0] = fTemp3;
          fVec4[0] = (fSlow39 * fTemp3);
          fRec12[0] = ((fSlow39 * (fTemp3 + (fSlow40 * fRec12[1]))) - fVec4[1]);
          fVec5[0] = (fSlow39 * fRec12[0]);
          fRec11[0] = ((fSlow39 * (fRec12[0] + (fSlow40 * fRec11[1]))) - fVec5[1]);
          fRec10[0] = (fRec11[0] - (fSlow37 * ((fSlow36 * fRec10[2]) + (fSlow32 * fRec10[1]))));
          fRec9[0] = ((fSlow37 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1])))) - (fSlow35 * ((fSlow34 * fRec9[2]) + (fSlow32 * fRec9[1]))));
          S7[1] = (fSlow35 * (fRec9[2] + (fRec9[0] + (2 * fRec9[1]))));
          add_dc(S7[1]);
          float fTemp4 = max(-1, min(1, (fSlow43 * (fSlow42 + S7[iSlow41]))));
          add_dc(fTemp4);
          fVec6[0] = (fTemp4 * (1 - (0.333333f * (fTemp4 * fTemp4))));
          fRec5[0] = ((fVec6[0] + (0.995f * fRec5[1])) - fVec6[1]);
          fRec13[0] = (fSlow44 + (0.999f * fRec13[1]));
          float fTemp6 = (fRec13[0] * fRec5[0]);
          add_dc(fTemp6);
          S6[0] = fTemp6;
          fVec7[0] = (fSlow39 * fTemp6);
          fRec17[0] = ((fSlow39 * (fTemp6 + (fSlow40 * fRec17[1]))) - fVec7[1]);
          fVec8[0] = (fSlow39 * fRec17[0]);
          fRec16[0] = ((fSlow39 * (fRec17[0] + (fSlow40 * fRec16[1]))) - fVec8[1]);
          fRec15[0] = (fRec16[0] - (fSlow37 * ((fSlow36 * fRec15[2]) + (fSlow32 * fRec15[1]))));
          fRec14[0] = ((fSlow37 * (fRec15[2] + (fRec15[0] + (2 * fRec15[1])))) - (fSlow35 * ((fSlow34 * fRec14[2]) + (fSlow32 * fRec14[1]))));
          S6[1] = (fSlow35 * (fRec14[2] + (fRec14[0] + (2 * fRec14[1]))));
          fVec_tone0[0] = S6[iSlow41];
        }
      else  fVec_tone0[0] = fTemp0;   		// distortion end

      // tone
      fRec_tone3[0] = (fSlow_tone32 * ((fSlow_tone21 * ((fSlow_tone31 * fVec_tone0[2]) + ((fSlow_tone30 * fVec_tone0[0]) + (fSlow_tone28 * fVec_tone0[1])))) - ((fSlow_tone27 * fRec_tone3[2]) + (fSlow_tone24 * fRec_tone3[1]))));
      fRec_tone2[0] = (fSlow_tone37 * ((fSlow_tone7 * (((fSlow_tone36 * fRec_tone3[0]) + (fSlow_tone34 * fRec_tone3[1])) + (fSlow_tone33 * fRec_tone3[2]))) - ((fSlow_tone20 * fRec_tone2[2]) + (fSlow_tone17 * fRec_tone2[1]))));
      fRec_tone1[0] = (fSlow_tone42 * ((((fSlow_tone41 * fRec_tone2[1]) + (fSlow_tone40 * fRec_tone2[0])) + (fSlow_tone38 * fRec_tone2[2])) + (0 - ((fSlow_tone15 * fRec_tone1[2]) + (fSlow_tone10 * fRec_tone1[1])))));
      fRec_tone0[0] = (fSlow_tone47 * ((((fSlow_tone46 * fRec_tone1[1]) + (fSlow_tone45 * fRec_tone1[0])) + (fSlow_tone43 * fRec_tone1[2])) + (0 - ((fSlow_tone6 * fRec_tone0[2]) + (fSlow_tone3 * fRec_tone0[1])))));
      // tone end

      fTemp0 = fRec_tone0[0];

      if (iSlow71)     //freeverb
        {
          float fTemp9 = (1.500000e-02f * fTemp0);
          fRec31[0] = ((fSlow69 * fRec30[1]) + (fSlow68 * fRec31[1]));
          fVec10[IOTA&2047] = (fTemp9 + (fSlow70 * fRec31[0]));
          fRec30[0] = fVec10[(IOTA-1640)&2047];
          fRec33[0] = ((fSlow69 * fRec32[1]) + (fSlow68 * fRec33[1]));
          fVec11[IOTA&2047] = (fTemp9 + (fSlow70 * fRec33[0]));
          fRec32[0] = fVec11[(IOTA-1580)&2047];
          fRec35[0] = ((fSlow69 * fRec34[1]) + (fSlow68 * fRec35[1]));
          fVec12[IOTA&2047] = (fTemp9 + (fSlow70 * fRec35[0]));
          fRec34[0] = fVec12[(IOTA-1514)&2047];
          fRec37[0] = ((fSlow69 * fRec36[1]) + (fSlow68 * fRec37[1]));
          fVec13[IOTA&2047] = (fTemp9 + (fSlow70 * fRec37[0]));
          fRec36[0] = fVec13[(IOTA-1445)&2047];
          fRec39[0] = ((fSlow69 * fRec38[1]) + (fSlow68 * fRec39[1]));
          fVec14[IOTA&2047] = (fTemp9 + (fSlow70 * fRec39[0]));
          fRec38[0] = fVec14[(IOTA-1379)&2047];
          fRec41[0] = ((fSlow69 * fRec40[1]) + (fSlow68 * fRec41[1]));
          fVec15[IOTA&2047] = (fTemp9 + (fSlow70 * fRec41[0]));
          fRec40[0] = fVec15[(IOTA-1300)&2047];
          fRec43[0] = ((fSlow69 * fRec42[1]) + (fSlow68 * fRec43[1]));
          fVec16[IOTA&2047] = (fTemp9 + (fSlow70 * fRec43[0]));
          fRec42[0] = fVec16[(IOTA-1211)&2047];
          fRec45[0] = ((fSlow69 * fRec44[1]) + (fSlow68 * fRec45[1]));
          fVec17[IOTA&2047] = (fTemp9 + (fSlow70 * fRec45[0]));
          fRec44[0] = fVec17[(IOTA-1139)&2047];
          float fTemp10 = (((((((fRec44[0] + fRec42[0]) + fRec40[0]) + fRec38[0]) + fRec36[0]) + fRec34[0]) + fRec32[0]) + fRec30[0]);
          fVec18[IOTA&1023] = (fTemp10 + (0.5f * fRec28[1]));
          fRec28[0] = fVec18[(IOTA-579)&1023];
          float 	fRec29 = (0 - (fTemp10 - fRec28[1]));
          fVec19[IOTA&511] = (fRec29 + (0.5f * fRec26[1]));
          fRec26[0] = fVec19[(IOTA-464)&511];
          float 	fRec27 = (fRec26[1] - fRec29);
          fVec20[IOTA&511] = (fRec27 + (0.5f * fRec24[1]));
          fRec24[0] = fVec20[(IOTA-364)&511];
          float 	fRec25 = (fRec24[1] - fRec27);
          fVec21[IOTA&255] = (fRec25 + (0.5f * fRec22[1]));
          fRec22[0] = fVec21[(IOTA-248)&255];
          float 	fRec23 = (fRec22[1] - fRec25);
          fTemp0 = ((fSlow66 * (fRec23 + fTemp9)) + (fSlow67 * fTemp0));
        }
      // gain out
      fRec46[0] = (fSlow72 + (0.999f * fRec46[1]));
      fTemp0 =  (fRec46[0] * fTemp0);

      // bass booster
      if (iboost)
        {
          fRec_boost0[0] = (fTemp0 - (fConst_boost4 * ((fConst_boost3 * fRec_boost0[2]) + (fConst_boost2 * fRec_boost0[1]))));
          fTemp0 = (fConst_boost4 * (((fConst_boost8 * fRec_boost0[0]) + (fConst_boost7 * fRec_boost0[1])) + (fConst_boost6 * fRec_boost0[2])));
        }

      //chorus
      if (ichorus)
        {
          fVec_CH0[IOTA_CH&65535] = fTemp0;
          float fTemp_CH1 = (fSlow_CH0 + fRec_CH0[1]);
          fRec_CH0[0] = (fTemp_CH1 - floorf(fTemp_CH1));
          float fTemp_CH2 = (65536 * (fRec_CH0[0] - floorf(fRec_CH0[0])));
          float fTemp_CH3 = floorf(fTemp_CH2);
          int iTemp_CH4 = int(fTemp_CH3);
          float fTemp_CH5 = (fSlow_CH2 * (1 + (fSlow_CH1 * ((ftbl0[((1 + iTemp_CH4) & 65535)] * (fTemp_CH2 - fTemp_CH3)) + (ftbl0[(iTemp_CH4 & 65535)] * ((1 + fTemp_CH3) - fTemp_CH2))))));
          int iTemp_CH6 = int(fTemp_CH5);
          int iTemp_CH7 = (1 + iTemp_CH6);
          fTemp0 = (fVec_CH0[IOTA_CH&65535] + (fSlow_CH3 * (((fTemp_CH5 - iTemp_CH6) * fVec_CH0[(IOTA_CH-int((int(iTemp_CH7) & 65535)))&65535]) + ((iTemp_CH7 - fTemp_CH5) * fVec_CH0[(IOTA_CH-int((iTemp_CH6 & 65535)))&65535]))));
        }

      if (iSlow75)    //echo
        {
          fRec47[IOTA&262143] = (fTemp0 + (fSlow74 * fRec47[(IOTA-iSlow73)&262143]));
          fTemp0 = fRec47[(IOTA-0)&262143];
        }                                     //echo ende

      if (iSlow79)     //impulseResponse
        {
          fVec22[0] = fTemp0;
          fRec48[0] = ((fSlow78 * (fVec22[0] - fVec22[2])) + (fSlow76 * ((fSlow77 * fRec48[1]) - (fSlow76 * fRec48[2]))));
          fVec23[0] = (fRec48[0] + fVec22[0]);
        }
      else  fVec23[0] = fTemp0;   //impulseResponse ende

      // this is the output value from the mono process
      fRec0[0] = ((fVec23[0] + (fSlow80 * fVec23[3])) - (fSlow0 * fRec0[5]))*ngate;
      // switch between hard_cut or foldback distortion, or plain output

      switch (ifuse)
        {
        case 0:
          break;
        case 1:
          fRec0[0] = hard_cut(saturate(fRec0[0],threshold),threshold);
          break;
        case 2:
          fRec0[0] = foldback(fRec0[0],threshold);
          break;
        }
      // trigger the oscilloscope to update peer sample. I know that some samples dont will show, but it will
      // update fast as  posible this way (mode 3)
      if ((gx_gui::showwave == 1) &&(gx_gui::wave_view_mode == gx_gui::kWvMode3)) viv = fRec0[0];


      float 	S9[2];
      // copy the output for the frame based mode of the oscilloscope
      //  if ((gx_gui::showwave == 1) &&((gx_gui::wave_view_mode == 1) || (gx_gui::wave_view_mode == 2) )) get_frame[i] = fRec0[0];
      S9[0] = (fSlow87 * fRec0[0]);
      S9[1] = (fSlow84 * fRec0[0]);
      // the left output port
      *output1++ = S9[iSlow88];

      if (gx_jconv::jconv_is_running)
      {
       fRecinjc[0] = (fSlowinjc + (0.999f * fRecinjc[1]));
       // this is the left "extra" port to run jconv in bybass mode
       *output0++ = (fSlow85 * fRec0[0]* fRecinjc[0]);
       // this is the right "extra" port to run jconv in bybass mode
       *output2++ = (fSlow90 * fRec0[0]* fRecinjc[0]);
      }
      float 	S10[2];
      S10[0] = (fSlow91 * fRec0[0]);
      S10[1] = (fSlow89 * fRec0[0]);
      // the right output port
      *output3++ = S10[iSlow88];
      // post processing
      for (int i=5; i>0; i--) fRec0[i] = fRec0[i-1];
      for (int i=3; i>0; i--) fVec23[i] = fVec23[i-1];
      fRec48[2] = fRec48[1];
      fRec48[1] = fRec48[0];
      fVec22[2] = fVec22[1];
      fVec22[1] = fVec22[0];
      fRec46[1] = fRec46[0];
      fRec22[1] = fRec22[0];
      fRec24[1] = fRec24[0];
      fRec26[1] = fRec26[0];
      fRec28[1] = fRec28[0];
      fRec44[1] = fRec44[0];
      fRec45[1] = fRec45[0];
      fRec42[1] = fRec42[0];
      fRec43[1] = fRec43[0];
      fRec40[1] = fRec40[0];
      fRec41[1] = fRec41[0];
      fRec38[1] = fRec38[0];
      fRec39[1] = fRec39[0];
      fRec36[1] = fRec36[0];
      fRec37[1] = fRec37[0];
      fRec34[1] = fRec34[0];
      fRec35[1] = fRec35[0];
      fRec32[1] = fRec32[0];
      fRec33[1] = fRec33[0];
      fRec30[1] = fRec30[0];
      fRec31[1] = fRec31[0];
      fRec18[2] = fRec18[1];
      fRec18[1] = fRec18[0] *0.996f;
      fRec21[1] = fRec21[0];
      fRec20[1] = fRec20[0];
      fRec19[1] = fRec19[0];
      //----- tone
      fRec_tone0[2] = fRec_tone0[1];
      fRec_tone0[1] = fRec_tone0[0];
      fRec_tone1[2] = fRec_tone1[1];
      fRec_tone1[1] = fRec_tone1[0];
      fRec_tone2[2] = fRec_tone2[1];
      fRec_tone2[1] = fRec_tone2[0];
      fRec_tone3[2] = fRec_tone3[1];
      fRec_tone3[1] = fRec_tone3[0];
      fVec_tone0[2] = fVec_tone0[1];
      fVec_tone0[1] = fVec_tone0[0];
      // tone end
      // distortion
      fRec14[2] = fRec14[1];
      fRec14[1] = fRec14[0];
      fRec15[2] = fRec15[1];
      fRec15[1] = fRec15[0];
      fRec16[1] = fRec16[0];
      fVec8[1] = fVec8[0];
      fRec17[1] = fRec17[0];
      fVec7[1] = fVec7[0];
      fRec13[1] = fRec13[0];
      fRec5[1] = fRec5[0];
      fVec6[1] = fVec6[0];
      fRec9[2] = fRec9[1];
      fRec9[1] = fRec9[0];
      fRec10[2] = fRec10[1];
      fRec10[1] = fRec10[0];
      fRec11[1] = fRec11[0];
      fVec5[1] = fVec5[0];
      fRec12[1] = fRec12[0];
      fVec4[1] = fVec4[0];
      fRec7[1] = fRec7[0];
      fVec3[1] = fVec3[0];
      fRec8[1] = fRec8[0];
      fVec2[1] = fVec2[0];
      fRec6[1] = fRec6[0];
      // distortion end
      IOTA = IOTA+1;
      fRec3[1] = fRec3[0];
      fRec4[1] = fRec4[0];
      fReccom0[1] = fReccom0[0];
      fReccom1[1] = fReccom1[0];
      //fVec0[1] = fVec0[0];
      fRecover0[1] = fRecover0[0];
      // post processing tuner
      fRect0[1] = fRect0[0];
      iRect1[1] = iRect1[0];
      iRect2[1] = iRect2[0];
      iRect3[1] = iRect3[0];
      fRect4[1] = fRect4[0];
      fVect1[1] = fVect1[0];
      fRect5[1] = fRect5[0];
      fVect0[1] = fVect0[0];
      fRechp0[1] = fRechp0[0];
      fVechp0[1] = fVechp0[0];
      // post processing bass booster
      fRec_boost0[2] = fRec_boost0[1];
      fRec_boost0[1] = fRec_boost0[0];
      //autowah
      iRecwah2[1] = iRecwah2[0];
      IOTAWAH = IOTAWAH+1;
      //chorus
      fRec_CH0[1] = fRec_CH0[0];
      IOTA_CH = IOTA_CH+1;
      fRecinjc[1] = fRecinjc[0];
      old_freq = fConsta4;

    }

  // trigger the oscilloscope to update on frame base (mode 1 and 2)
 /* if ((gx_gui::showwave == 1) &&
      ((gx_gui::wave_view_mode == gx_gui::kWvMode1) ||
       (gx_gui::wave_view_mode == gx_gui::kWvMode2)))
      viv = fRec0[1]; */

    output1 = output[0];
    output3 = output[1];
    (void)memcpy(get_frame, output1, sizeof(float)*count);
    (void)memcpy(get_frame1, output3, sizeof(float)*count);
}


