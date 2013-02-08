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



inline void TonestackMono::clear_state_f()
{
  for (int32_t i=0; i<4; i++) fRec0[i] = 0;
}

inline void TonestackMono::init(uint32_t samplingFreq)
{

  fSamplingFreq = samplingFreq;
  fConst0 = (2 * double(min(192000, max(1, fSamplingFreq))));
  fConst1 = faustpower<2>(fConst0);
  fConst2 = (3 * fConst0);
  clear_state_f();
}

void TonestackMono::connect(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case MID:
      fslider0_ = (float*)data;
      break;
    case BASS:
      fslider1_ = (float*)data;
      break;
    case TREBLE:
      fslider2_ = (float*)data;
      break;
    default:
      break;
    }
}

inline void TonestackMono::run(uint32_t n_samples, float *output)   //sovtek
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
      for (int32_t i=3; i>0; i--) fRec0[i] = fRec0[i-1];
    }
}


inline void TonestackMono::run_soldano(uint32_t n_samples, float *output)   //soldano
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
      output[i] = (float)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
      // post processing
      for (int32_t i=3; i>0; i--) fRec0[i] = fRec0[i-1];
    }
}

inline void TonestackMono::run_bassman(uint32_t n_samples, float *output)   //bassman
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
  for (uint32_t i=0; i<n_samples; i++)
    {
      fRec0[0] = ((double)output[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
      output[i] = (float)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
      // post processing
      for (int32_t i=3; i>0; i--) fRec0[i] = fRec0[i-1];
    }

}


inline void TonestackMono::run_ampeg(uint32_t n_samples, float *output)   //ampeg
{
  float fslider0 = *fslider0_;
  float fslider1 = *fslider1_;
  float fslider2 = *fslider2_;
  double 	fSlow0 = fslider0;
  double 	fSlow1 = (3.0896250000000005e-07 * fSlow0);
  double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
  double 	fSlow3 = (6.338090000000001e-07 + ((1.8734760000000003e-05 * fSlow2) + (fSlow0 * (((1.2358500000000002e-05 * fSlow2) - 1.361249999999999e-08) - fSlow1))));
  double 	fSlow4 = ((1.6037340000000005e-09 * fSlow2) - (4.0093350000000015e-11 * fSlow0));
  double 	fSlow5 = (1.8198400000000004e-09 * fSlow2);
  double 	fSlow6 = (4.5496000000000015e-11 + (fSlow5 + (fSlow0 * (fSlow4 - 5.40265e-12))));
  double 	fSlow7 = (fConst0 * fSlow6);
  double 	fSlow8 = (0.00055 * fSlow0);
  double 	fSlow9 = (0.022470000000000004 * fSlow2);
  double 	fSlow10 = (fConst0 * (0.00208725 + (fSlow9 + fSlow8)));
  double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
  double 	fSlow12 = (fConst2 * fSlow6);
  double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
  double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
  double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
  double 	fSlow16 = fslider2;
  double 	fSlow17 = ((fSlow0 * (4.0093350000000015e-11 + fSlow4)) + (fSlow16 * (fSlow5 + (4.5496000000000015e-11 - (4.5496000000000015e-11 * fSlow0)))));
  double 	fSlow18 = (fConst2 * fSlow17);
  double 	fSlow19 = (8.1169e-08 + (((1.6544000000000003e-07 * fSlow16) + (fSlow0 * (3.735875000000001e-07 - fSlow1))) + (fSlow2 * (3.24676e-06 + (1.2358500000000002e-05 * fSlow0)))));
  double 	fSlow20 = (0.0005617500000000001 + (fSlow9 + (fSlow8 + (0.00011750000000000001 * fSlow16))));
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
      for (int32_t i=3; i>0; i--) fRec0[i] = fRec0[i-1];
    }
}

inline void TonestackMono::run_ac30(uint32_t n_samples, float *output)   //ac30
{
    fslider0 = (*fslider0_);
    fslider1 = (*fslider1_);
    fslider2 = (*fslider2_);
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (4.851e-08 * fSlow0);
	double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
	double 	fSlow3 = (7.172000000000001e-07 + ((4.972000000000001e-05 * fSlow2) + (fSlow0 * (((4.8510000000000015e-06 * fSlow2) - 4.2449000000000006e-07) - fSlow1))));
	double 	fSlow4 = ((2.6620000000000007e-10 * fSlow2) - (2.662e-12 * fSlow0));
	double 	fSlow5 = (2.4200000000000003e-09 * fSlow2);
	double 	fSlow6 = (2.4200000000000004e-11 + (fSlow5 + (fSlow0 * (fSlow4 - 2.1538000000000003e-11))));
	double 	fSlow7 = (fConst0 * fSlow6);
	double 	fSlow8 = (0.00022 * fSlow0);
	double 	fSlow9 = (0.022050000000000004 * fSlow2);
	double 	fSlow10 = (fConst0 * (0.0046705 + (fSlow9 + fSlow8)));
	double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
	double 	fSlow12 = (fConst2 * fSlow6);
	double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
	double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
	double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
	double 	fSlow16 = fslider2;
	double 	fSlow17 = ((fSlow0 * (2.662e-12 + fSlow4)) + (fSlow16 * (fSlow5 + (2.4200000000000004e-11 - (2.4200000000000004e-11 * fSlow0)))));
	double 	fSlow18 = (fConst2 * fSlow17);
	double 	fSlow19 = (1.32e-08 + (((2.2000000000000004e-07 * fSlow16) + (fSlow0 * (5.951000000000001e-08 - fSlow1))) + (fSlow2 * (1.32e-06 + (4.8510000000000015e-06 * fSlow0)))));
	double 	fSlow20 = (0.00022050000000000002 + (fSlow9 + (fSlow8 + (5e-05 * fSlow16))));
	double 	fSlow21 = (fConst0 * fSlow20);
	double 	fSlow22 = (fSlow21 + (fConst1 * (fSlow19 - fSlow18)));
	double 	fSlow23 = (fConst0 * fSlow17);
	double 	fSlow24 = (fSlow21 + (fConst1 * (fSlow23 - fSlow19)));
	double 	fSlow25 = (fConst0 * (0 - fSlow20));
	double 	fSlow26 = (fSlow25 + (fConst1 * (fSlow19 + fSlow18)));
	double 	fSlow27 = (fSlow25 - (fConst1 * (fSlow19 + fSlow23)));
	for (uint32_t i=0; i<n_samples; i++) {
		fRec0[0] = ((double)output[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
		output[i] = (float)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
}

inline void TonestackMono::run_bogner(uint32_t n_samples, float *output)   //bogener
{
    fslider0 = (*fslider0_);
    fslider1 = (*fslider1_);
    fslider2 = (*fslider2_);
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (7.790052600000002e-07 * fSlow0);
	double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
	double 	fSlow3 = (1.4106061200000003e-06 + ((3.7475640000000014e-05 * fSlow2) + (fSlow0 * (((2.3606220000000006e-05 * fSlow2) - 3.2220474e-07) - fSlow1))));
	double 	fSlow4 = ((1.5406083e-09 * fSlow2) - (5.08400739e-11 * fSlow0));
	double 	fSlow5 = (1.9775250000000004e-09 * fSlow2);
	double 	fSlow6 = (6.5258325e-11 + (fSlow5 + (fSlow0 * (fSlow4 - 1.4418251099999996e-11))));
	double 	fSlow7 = (fConst0 * fSlow6);
	double 	fSlow8 = (0.001551 * fSlow0);
	double 	fSlow9 = (0.015220000000000001 * fSlow2);
	double 	fSlow10 = (fConst0 * (0.0037192600000000003 + (fSlow9 + fSlow8)));
	double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
	double 	fSlow12 = (fConst2 * fSlow6);
	double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
	double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
	double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
	double 	fSlow16 = fslider2;
	double 	fSlow17 = ((fSlow0 * (5.08400739e-11 + fSlow4)) + (fSlow16 * (fSlow5 + (6.5258325e-11 - (6.5258325e-11 * fSlow0)))));
	double 	fSlow18 = (fConst2 * fSlow17);
	double 	fSlow19 = (5.018112e-08 + (((1.7391e-07 * fSlow16) + (fSlow0 * (8.643102600000002e-07 - fSlow1))) + (fSlow2 * (1.5206400000000001e-06 + (2.3606220000000006e-05 * fSlow0)))));
	double 	fSlow20 = (0.0005022600000000001 + (fSlow9 + (fSlow8 + (5.4999999999999995e-05 * fSlow16))));
	double 	fSlow21 = (fConst0 * fSlow20);
	double 	fSlow22 = (fSlow21 + (fConst1 * (fSlow19 - fSlow18)));
	double 	fSlow23 = (fConst0 * fSlow17);
	double 	fSlow24 = (fSlow21 + (fConst1 * (fSlow23 - fSlow19)));
	double 	fSlow25 = (fConst0 * (0 - fSlow20));
	double 	fSlow26 = (fSlow25 + (fConst1 * (fSlow19 + fSlow18)));
	double 	fSlow27 = (fSlow25 - (fConst1 * (fSlow19 + fSlow23)));
	for (uint32_t i=0; i<n_samples; i++) {
		fRec0[0] = ((double)output[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
		output[i] = (float)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
}

inline void TonestackMono::run_jcm2000(uint32_t n_samples, float *output)   //jcm2000
{
    fslider0 = (*fslider0_);
    fslider1 = (*fslider1_);
    fslider2 = (*fslider2_);
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (3.0937500000000006e-07 * fSlow0);
	double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
	double 	fSlow3 = (1.08515e-06 + ((3.108600000000001e-05 * fSlow2) + (fSlow0 * (((1.2375000000000003e-05 * fSlow2) - 2.99475e-07) - fSlow1))));
	double 	fSlow4 = ((1.8513000000000002e-09 * fSlow2) - (4.628250000000001e-11 * fSlow0));
	double 	fSlow5 = (3.3880000000000003e-09 * fSlow2);
	double 	fSlow6 = (8.470000000000002e-11 + (fSlow5 + (fSlow0 * (fSlow4 - 3.8417500000000006e-11))));
	double 	fSlow7 = (fConst0 * fSlow6);
	double 	fSlow8 = (0.00055 * fSlow0);
	double 	fSlow9 = (0.022500000000000003 * fSlow2);
	double 	fSlow10 = (fConst0 * (0.0031515000000000002 + (fSlow9 + fSlow8)));
	double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
	double 	fSlow12 = (fConst2 * fSlow6);
	double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
	double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
	double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
	double 	fSlow16 = fslider2;
	double 	fSlow17 = ((fSlow0 * (4.628250000000001e-11 + fSlow4)) + (fSlow16 * (fSlow5 + (8.470000000000002e-11 - (8.470000000000002e-11 * fSlow0)))));
	double 	fSlow18 = (fConst2 * fSlow17);
	double 	fSlow19 = (9.955000000000001e-08 + (((3.08e-07 * fSlow16) + (fSlow0 * (3.781250000000001e-07 - fSlow1))) + (fSlow2 * (3.982e-06 + (1.2375000000000003e-05 * fSlow0)))));
	double 	fSlow20 = (0.0005625000000000001 + (fSlow9 + (fSlow8 + (0.000125 * fSlow16))));
	double 	fSlow21 = (fConst0 * fSlow20);
	double 	fSlow22 = (fSlow21 + (fConst1 * (fSlow19 - fSlow18)));
	double 	fSlow23 = (fConst0 * fSlow17);
	double 	fSlow24 = (fSlow21 + (fConst1 * (fSlow23 - fSlow19)));
	double 	fSlow25 = (fConst0 * (0 - fSlow20));
	double 	fSlow26 = (fSlow25 + (fConst1 * (fSlow19 + fSlow18)));
	double 	fSlow27 = (fSlow25 - (fConst1 * (fSlow19 + fSlow23)));
	for (uint32_t i=0; i<n_samples; i++) {
		fRec0[0] = ((double)output[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
		output[i] = (float)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
		// post processing
		for (int i=3; i>0; i--) fRec0[i] = fRec0[i-1];
	}
}


void TonestackMono::init_static(uint32_t samplingFreq, TonestackMono *p)
{
  p->init(samplingFreq);
}

void TonestackMono::connect_static(uint32_t port,void* data, TonestackMono *p)
{
  p->connect(port, data);
}

////////////////////////////// STEREO //////////////////////////////////


inline void TonestackStereo::clear_state_f()
{
  for (int32_t i=0; i<4; i++) fRec0[i] = 0;
  for (int32_t i=0; i<4; i++) fRec1[i] = 0;
}


inline void TonestackStereo::init(uint32_t  samplingFreq)
{
  fSamplingFreq = samplingFreq;
  fConst0 = (2 * double(min(192000, max(1, fSamplingFreq))));
  fConst1 = faustpower<2>(fConst0);
  fConst2 = (3 * fConst0);
  clear_state_f();
}


void TonestackStereo::connect(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case MID:
      fslider0_ = (float*)data;
      break;
    case BASS:
      fslider1_ = (float*)data;
      break;
    case TREBLE:
      fslider2_ = (float*)data;
      break;
    default:
      break;
    }
}

inline void TonestackStereo::run(uint32_t count, float *output0, float *output1)
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
  for (uint32_t i=0; i<count; i++)
    {
      fRec0[0] = ((double)output0[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
      output0[i] = (float)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
      fRec1[0] = ((double)output1[i] - (fSlow15 * (((fSlow14 * fRec1[2]) + (fSlow13 * fRec1[1])) + (fSlow11 * fRec1[3]))));
      output1[i] = (float)(fSlow15 * ((fSlow27 * fRec1[0]) + ((fSlow26 * fRec1[1]) + ((fSlow24 * fRec1[3]) + (fSlow22 * fRec1[2])))));
      // post processing
      for (int32_t i=3; i>0; i--) fRec1[i] = fRec1[i-1];
      for (int32_t i=3; i>0; i--) fRec0[i] = fRec0[i-1];
    }
}


inline void TonestackStereo::run_soldano(uint32_t count, float *output0, float *output1) //soldano
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
  for (uint32_t i=0; i<count; i++)
    {
      fRec0[0] = ((double)output0[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
      output0[i] = (float)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
      fRec1[0] = ((double)output1[i] - (fSlow15 * (((fSlow14 * fRec1[2]) + (fSlow13 * fRec1[1])) + (fSlow11 * fRec1[3]))));
      output1[i] = (float)(fSlow15 * ((fSlow27 * fRec1[0]) + ((fSlow26 * fRec1[1]) + ((fSlow24 * fRec1[3]) + (fSlow22 * fRec1[2])))));
      // post processing
      for (int32_t i=3; i>0; i--) fRec1[i] = fRec1[i-1];
      for (int32_t i=3; i>0; i--) fRec0[i] = fRec0[i-1];
    }
}

inline void TonestackStereo::run_bassman(uint32_t count, float *output0, float *output1) // bassman
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
  for (uint32_t i=0; i<count; i++)
    {
      fRec0[0] = ((double)output0[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
      output0[i] = (float)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
      fRec1[0] = ((double)output1[i] - (fSlow15 * (((fSlow14 * fRec1[2]) + (fSlow13 * fRec1[1])) + (fSlow11 * fRec1[3]))));
      output1[i] = (float)(fSlow15 * ((fSlow27 * fRec1[0]) + ((fSlow26 * fRec1[1]) + ((fSlow24 * fRec1[3]) + (fSlow22 * fRec1[2])))));
      // post processing
      for (int32_t i=3; i>0; i--) fRec1[i] = fRec1[i-1];
      for (int32_t i=3; i>0; i--) fRec0[i] = fRec0[i-1];
    }
}

inline void TonestackStereo::run_ampeg(uint32_t count, float *output0, float *output1)  //ampeg
{
  float fslider0 = *fslider0_;
  float fslider1 = *fslider1_;
  float fslider2 = *fslider2_;
  double 	fSlow0 = fslider0;
  double 	fSlow1 = (3.0896250000000005e-07 * fSlow0);
  double 	fSlow2 = exp((3.4 * (fslider1 - 1)));
  double 	fSlow3 = (6.338090000000001e-07 + ((1.8734760000000003e-05 * fSlow2) + (fSlow0 * (((1.2358500000000002e-05 * fSlow2) - 1.361249999999999e-08) - fSlow1))));
  double 	fSlow4 = ((1.6037340000000005e-09 * fSlow2) - (4.0093350000000015e-11 * fSlow0));
  double 	fSlow5 = (1.8198400000000004e-09 * fSlow2);
  double 	fSlow6 = (4.5496000000000015e-11 + (fSlow5 + (fSlow0 * (fSlow4 - 5.40265e-12))));
  double 	fSlow7 = (fConst0 * fSlow6);
  double 	fSlow8 = (0.00055 * fSlow0);
  double 	fSlow9 = (0.022470000000000004 * fSlow2);
  double 	fSlow10 = (fConst0 * (0.00208725 + (fSlow9 + fSlow8)));
  double 	fSlow11 = ((fSlow10 + (fConst1 * (fSlow7 - fSlow3))) - 1);
  double 	fSlow12 = (fConst2 * fSlow6);
  double 	fSlow13 = ((fConst1 * (fSlow3 + fSlow12)) - (3 + fSlow10));
  double 	fSlow14 = ((fSlow10 + (fConst1 * (fSlow3 - fSlow12))) - 3);
  double 	fSlow15 = (1.0 / (0 - (1 + (fSlow10 + (fConst1 * (fSlow3 + fSlow7))))));
  double 	fSlow16 = fslider2;
  double 	fSlow17 = ((fSlow0 * (4.0093350000000015e-11 + fSlow4)) + (fSlow16 * (fSlow5 + (4.5496000000000015e-11 - (4.5496000000000015e-11 * fSlow0)))));
  double 	fSlow18 = (fConst2 * fSlow17);
  double 	fSlow19 = (8.1169e-08 + (((1.6544000000000003e-07 * fSlow16) + (fSlow0 * (3.735875000000001e-07 - fSlow1))) + (fSlow2 * (3.24676e-06 + (1.2358500000000002e-05 * fSlow0)))));
  double 	fSlow20 = (0.0005617500000000001 + (fSlow9 + (fSlow8 + (0.00011750000000000001 * fSlow16))));
  double 	fSlow21 = (fConst0 * fSlow20);
  double 	fSlow22 = (fSlow21 + (fConst1 * (fSlow19 - fSlow18)));
  double 	fSlow23 = (fConst0 * fSlow17);
  double 	fSlow24 = (fSlow21 + (fConst1 * (fSlow23 - fSlow19)));
  double 	fSlow25 = (fConst0 * (0 - fSlow20));
  double 	fSlow26 = (fSlow25 + (fConst1 * (fSlow19 + fSlow18)));
  double 	fSlow27 = (fSlow25 - (fConst1 * (fSlow19 + fSlow23)));
  for (uint32_t i=0; i<count; i++)
    {
      fRec0[0] = ((double)output0[i] - (fSlow15 * (((fSlow14 * fRec0[2]) + (fSlow13 * fRec0[1])) + (fSlow11 * fRec0[3]))));
      output0[i] = (float)(fSlow15 * ((fSlow27 * fRec0[0]) + ((fSlow26 * fRec0[1]) + ((fSlow24 * fRec0[3]) + (fSlow22 * fRec0[2])))));
      fRec1[0] = ((double)output1[i] - (fSlow15 * (((fSlow14 * fRec1[2]) + (fSlow13 * fRec1[1])) + (fSlow11 * fRec1[3]))));
      output1[i] = (float)(fSlow15 * ((fSlow27 * fRec1[0]) + ((fSlow26 * fRec1[1]) + ((fSlow24 * fRec1[3]) + (fSlow22 * fRec1[2])))));
      // post processing
      for (int32_t i=3; i>0; i--) fRec1[i] = fRec1[i-1];
      for (int32_t i=3; i>0; i--) fRec0[i] = fRec0[i-1];
    }
}


void TonestackStereo::init_static(uint32_t samplingFreq, TonestackStereo *p)
{
  p->init(samplingFreq);
}

void TonestackStereo::connect_static(uint32_t port,void* data, TonestackStereo *p)
{
  p->connect(port, data);
}
