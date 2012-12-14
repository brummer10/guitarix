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



inline void Tonestack::clear_state_f()
{
  for (int i=0; i<4; i++) fRec0[i] = 0;
}

inline void Tonestack::init(unsigned int samplingFreq, GXPlugin *self)
{
  if (self->tubesel == 1)
    {
      _t_ptr = &Tonestack::run;
    }
  else if (self->tubesel == 2)
    {
      _t_ptr = &Tonestack::run_soldano;
    }
  else if (self->tubesel == 3)
    {
      _t_ptr = &Tonestack::run_bassman;
    }
  fSamplingFreq = samplingFreq;
  fConst0 = (2 * double(min(192000, max(1, fSamplingFreq))));
  fConst1 = faustpower<2>(fConst0);
  fConst2 = (3 * fConst0);
  clear_state_f();
}

void Tonestack::connect(uint32_t port,void* data)
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
      fslider0_ = (float*)data;
      break;
    case BASS:
      fslider1_ = (float*)data;
      break;
    case TREBLE:
      fslider2_ = (float*)data;
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
      break;
    case AMP_NOTIFY:
      break;
    }
}

inline void Tonestack::run(uint32_t n_samples, float *output) //sovtek
{
  float fslider0 = *fslider0_;
  float fslider1 = *fslider1_;
  float fslider2 = *fslider2_;
  double 	fSlow0 = fslider0;
  double 	fSlow1 = (4.9434000000000004e-08 * fSlow0);
  double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
  double 	fSlow3 = (7.748796000000001e-07 + ((2.8889960000000004e-05 * fSlow2) + (fSlow0 * (((4.943400000000001e-06 * fSlow2) - 1.2634599999999999e-07) - fSlow1))));
  double 	fSlow4 = ((1.2443156000000004e-09 * fSlow2) - (1.2443156000000002e-11 * fSlow0));
  double 	fSlow5 = (5.345780000000001e-09 * fSlow2);
  double 	fSlow6 = (5.345780000000001e-11 + (fSlow5 + (fSlow0 * (fSlow4 - 4.101464400000001e-11))));
  double 	fSlow7 = (fConst0 * fSlow6);
  double 	fSlow8 = (0.00022 * fSlow0);
  double 	fSlow9 = (0.022470000000000004 * fSlow2);
  double 	fSlow10 = (fConst0 * (0.0025277 + (fSlow9 + fSlow8)));
  double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
  double 	fSlow12 = (fConst2 * fSlow6);
  double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
  double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
  double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
  double 	fSlow16 = fslider2;
  double 	fSlow17 = ((fSlow0 * (1.2443156000000002e-11 + fSlow4)) + (fSlow16 * (fSlow5 + (5.345780000000001e-11 - (5.345780000000001e-11 * fSlow0)))));
  double 	fSlow18 = (fConst2 * fSlow17);
  double 	fSlow19 = (6.141960000000001e-08 + (((4.859800000000001e-07 * fSlow16) + (fSlow0 * (1.0113400000000001e-07 - fSlow1))) + (fSlow2 * (6.141960000000001e-06 + (4.943400000000001e-06 * fSlow0)))));
  double 	fSlow20 = (0.00022470000000000001 + (fSlow9 + (fSlow8 + (0.00023500000000000002 * fSlow16))));
  double 	fSlow21 = (fConst0 * fSlow20);
  double 	fSlow22 = (fSlow21 + (fConst1 * (fSlow19 - fSlow18)));
  double 	fSlow23 = (fConst0 * fSlow17);
  double 	fSlow24 = (fSlow21 + (fConst1 * (fSlow23 - fSlow19)));
  double 	fSlow25 = (fConst0 * (0 - fSlow20));
  double 	fSlow26 = (fSlow25 + (fConst1 * (fSlow19 + fSlow18)));
  double 	fSlow27 = (fSlow25 - (fConst1 * (fSlow19 + fSlow23)));
  for (uint32_t i=0; i<n_samples; i++)
    {
      fRec0[0] = ((double)output[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
      output[i] = (float)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
      // post processing
      for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
    }
}


inline void Tonestack::run_soldano(uint32_t n_samples, float *output) //soldano
{
  float fslider0 = *fslider0_;
  float fslider1 = *fslider1_;
  float fslider2 = *fslider2_;
  double 	fSlow0 = fslider0;
  double 	fSlow1 = (2.5587500000000006e-07 * fSlow0);
  double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
  double 	fSlow3 = (7.717400000000001e-07 + ((2.2033600000000005e-05 * fSlow2) + (fSlow0 * (((1.0235000000000001e-05 * fSlow2) - 1.5537499999999997e-07) - fSlow1))));
  double 	fSlow4 = ((1.3959000000000001e-09 * fSlow2) - (3.48975e-11 * fSlow0));
  double 	fSlow5 = (2.2090000000000005e-09 * fSlow2);
  double 	fSlow6 = (5.522500000000001e-11 + (fSlow5 + (fSlow0 * (fSlow4 - 2.0327500000000007e-11))));
  double 	fSlow7 = (fConst0 * fSlow6);
  double 	fSlow8 = (0.0005 * fSlow0);
  double 	fSlow9 = (0.020470000000000002 * fSlow2);
  double 	fSlow10 = (fConst0 * (0.0025092499999999998 + (fSlow9 + fSlow8)));
  double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
  double 	fSlow12 = (fConst2 * fSlow6);
  double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
  double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
  double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
  double 	fSlow16 = fslider2;
  double 	fSlow17 = ((fSlow0 * (3.48975e-11 + fSlow4)) + (fSlow16 * (fSlow5 + (5.522500000000001e-11 - (5.522500000000001e-11 * fSlow0)))));
  double 	fSlow18 = (fConst2 * fSlow17);
  double 	fSlow19 = (8.084000000000001e-08 + (((2.2090000000000003e-07 * fSlow16) + (fSlow0 * (3.146250000000001e-07 - fSlow1))) + (fSlow2 * (3.2336000000000007e-06 + (1.0235000000000001e-05 * fSlow0)))));
  double 	fSlow20 = (0.00051175 + (fSlow9 + (fSlow8 + (0.00011750000000000001 * fSlow16))));
  double 	fSlow21 = (fConst0 * fSlow20);
  double 	fSlow22 = (fSlow21 + (fConst1 * (fSlow19 - fSlow18)));
  double 	fSlow23 = (fConst0 * fSlow17);
  double 	fSlow24 = (fSlow21 + (fConst1 * (fSlow23 - fSlow19)));
  double 	fSlow25 = (fConst0 * (0 - fSlow20));
  double 	fSlow26 = (fSlow25 + (fConst1 * (fSlow19 + fSlow18)));
  double 	fSlow27 = (fSlow25 - (fConst1 * (fSlow19 + fSlow23)));
  for (uint32_t i=0; i<n_samples; i++)
    {
      fRec0[0] = ((double)output[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
      output[i] = (FAUSTFLOAT)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
      // post processing
      for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
    }
}

inline void Tonestack::run_bassman(uint32_t n_samples, float *output) //bassman
{
  float fslider0 = *fslider0_;
  float fslider1 = *fslider1_;
  float fslider2 = *fslider2_;
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (2.5312500000000006e-07 * fSlow0);
	double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
	double 	fSlow3 = (7.4525e-07 + ((2.4210000000000004e-05 * fSlow2) + (fSlow0 * (((1.0125e-05 * fSlow2) - 2.75625e-07) - fSlow1))));
	double 	fSlow4 = ((7.650000000000002e-10 * fSlow2) - (1.9125000000000002e-11 * fSlow0));
	double 	fSlow5 = (1.4000000000000001e-09 * fSlow2);
	double 	fSlow6 = (3.500000000000001e-11 + (fSlow5 + (fSlow0 * (fSlow4 - 1.5875000000000007e-11))));
	double 	fSlow7 = (fConst0 * fSlow6);
	double 	fSlow8 = (0.0005 * fSlow0);
	double 	fSlow9 = (0.02025 * fSlow2);
	double 	fSlow10 = (fConst0 * (0.0028087500000000005 + (fSlow9 + fSlow8)));
	double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
	double 	fSlow12 = (fConst2 * fSlow6);
	double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
	double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
	double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
	double 	fSlow16 = fslider2;
	double 	fSlow17 = ((fSlow0 * (1.9125000000000002e-11 + fSlow4)) + (fSlow16 * (fSlow5 + (3.500000000000001e-11 - (3.500000000000001e-11 * fSlow0)))));
	double 	fSlow18 = (fConst2 * fSlow17);
	double 	fSlow19 = (4.525e-08 + (((1.4e-07 * fSlow16) + (fSlow0 * (2.8437500000000003e-07 - fSlow1))) + (fSlow2 * (1.8100000000000002e-06 + (1.0125e-05 * fSlow0)))));
	double 	fSlow20 = (0.00050625 + (fSlow9 + (fSlow8 + (6.25e-05 * fSlow16))));
	double 	fSlow21 = (fConst0 * fSlow20);
	double 	fSlow22 = (fSlow21 + (fConst1 * (fSlow19 - fSlow18)));
	double 	fSlow23 = (fConst0 * fSlow17);
	double 	fSlow24 = (fSlow21 + (fConst1 * (fSlow23 - fSlow19)));
	double 	fSlow25 = (fConst0 * (0 - fSlow20));
	double 	fSlow26 = (fSlow25 + (fConst1 * (fSlow19 + fSlow18)));
	double 	fSlow27 = (fSlow25 - (fConst1 * (fSlow19 + fSlow23)));
	for (uint32_t i=0; i<n_samples; i++) {
		fRec0[0] = ((double)output[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
		output[i] = (FAUSTFLOAT)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}

}

void Tonestack::init_static(unsigned int samplingFreq, GXPlugin *self)
{
  self->ts->init(samplingFreq, self);
}

void Tonestack::connect_static(uint32_t port,void* data, Tonestack *p)
{
  p->connect(port, data);
}

void Tonestack::run_static(uint32_t n_samples, Tonestack *p, float *output)
{
  (p->*_t_ptr)(n_samples, output);
}

