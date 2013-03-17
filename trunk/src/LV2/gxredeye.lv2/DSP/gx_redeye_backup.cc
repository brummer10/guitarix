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


inline void GxRedeyeMono::clear_state_f()
{
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
}

inline void GxRedeyeMono::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / tanf((20517.741620594938f / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0f / tanf((97.38937226128358f / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0f / tanf((270.1769682087222f / iConst0)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = (0.027f / fConst8);
	fConst11 = (0 - fConst4);
	fConst12 = (0.025f / fConst5);
	fConst13 = (1.0f / fConst2);
	fConst14 = (1.0f / tanf((414.6902302738527f / iConst0)));
	fConst15 = (1 + fConst14);
	fConst16 = (0 - ((1 - fConst14) / fConst15));
	fConst17 = (0.015f / fConst15);
	fConst18 = (0.0082f / fConst2);
	clear_state_f();
}

void GxRedeyeMono::connect(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case MASTER:
      fslider0_ = (float*)data;
      break;
    case GAIN:
      fslider1_ = (float*)data;
      break;
    default:
      break;
    }
}

void GxRedeyeMono::run_Champ(uint32_t count, float* input0, float* output0)
{
  fslider0  = (*fslider0_);
  fslider1  = (*fslider1_);

	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * fslider0)));
	float 	fSlow1 = (0.0010000000000000009f * powf(10,(0.05f * fslider1)));
	for (uint32_t i=0; i<count; i++) {
		fRec3[0] = (fSlow0 + (0.999f * fRec3[1]));
		fRec7[0] = (fSlow1 + (0.999f * fRec7[1]));
		fRec10[0] = ((fConst10 * (fRec9[1] + fRec9[2])) + (fConst9 * fRec10[1]));
		fRec9[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((float)input0[i] + fRec10[0]) - 1.581656f)) - 191.42014814814814f);
		fRec8[0] = ((fConst12 * ((fConst11 * fRec9[1]) + (fConst4 * fRec9[0]))) + (fConst6 * fRec8[1]));
		float fTemp0 = (fRec8[0] * fRec7[0]);
		fVec0[0] = fTemp0;
		fRec6[0] = ((fConst13 * (fVec0[0] + fVec0[1])) + (fConst3 * fRec6[1]));
		fRec11[0] = ((fConst17 * (fRec5[1] + fRec5[2])) + (fConst16 * fRec11[1]));
		fRec5[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec11[0] + fRec6[0]) - 1.204285f)) - 169.71433333333334f);
		fRec4[0] = ((fConst12 * ((fConst11 * fRec5[1]) + (fConst4 * fRec5[0]))) + (fConst6 * fRec4[1]));
		fRec12[0] = ((fConst18 * (fRec2[1] + fRec2[2])) + (fConst3 * fRec12[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec12[0] + (fRec4[0] * fRec3[0])) - 1.130462f)) - 112.13878048780487f);
		fRec1[0] = ((fConst12 * ((fConst11 * fRec2[1]) + (fConst4 * fRec2[0]))) + (fConst6 * fRec1[1]));
		fRec0[0] = ((fConst13 * (fRec1[0] + fRec1[1])) + (fConst3 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec12[1] = fRec12[0];
		fRec4[1] = fRec4[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec11[1] = fRec11[0];
		fRec6[1] = fRec6[0];
		fVec0[1] = fVec0[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec7[1] = fRec7[0];
		fRec3[1] = fRec3[0];
	}

}


// static wrappers
void GxRedeyeMono::init_static(uint32_t samplingFreq, GxRedeyeMono *p)
{
  p->init(samplingFreq);
}

void GxRedeyeMono::connect_static(uint32_t port,void* data, GxRedeyeMono *p)
{
  p->connect(port, data);
}


