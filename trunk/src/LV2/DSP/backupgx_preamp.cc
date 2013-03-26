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


inline void GxPreAmpMono::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
}

inline void GxPreAmpMono::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / tanf((62831.853071795864f / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0f / tanf((97.38937226128358f / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0f / tanf((62.83185307179586f / iConst0)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = tanf((1413.7166941154069f / iConst0));
	fConst11 = (2 * (1 - (1.0f / faustpower<2>(fConst10))));
	fConst12 = (1.0f / fConst10);
	fConst13 = (1 + ((fConst12 - 1.0000000000000004f) / fConst10));
	fConst14 = (1.0f / (1 + ((1.0000000000000004f + fConst12) / fConst10)));
	fConst15 = tanf((3141.592653589793f / iConst0));
	fConst16 = (1.0f / faustpower<2>(fConst15));
	fConst17 = (2 * (1 - fConst16));
	fConst18 = (1.0f / fConst15);
	fConst19 = (1 + ((fConst18 - 1.0000000000000004f) / fConst15));
	fConst20 = (1.0f / (1 + ((1.0000000000000004f + fConst18) / fConst15)));
	fConst21 = (1 + fConst18);
	fConst22 = (0 - ((1 - fConst18) / fConst21));
	fConst23 = (1.0f / fConst2);
	fConst24 = (0 - fConst18);
	fConst25 = (1.0f / fConst21);
	fConst26 = (2 * (0 - fConst16));
	fConst27 = (1 + fConst12);
	fConst28 = (1.0f / fConst27);
	fConst29 = (0 - ((1 - fConst12) / fConst27));
	fConst30 = (0 - fConst7);
	fConst31 = (1.0f / fConst8);
	fConst32 = (1.0f / tanf((125.66370614359172f / iConst0)));
	fConst33 = (1 + fConst32);
	fConst34 = (0 - ((1 - fConst32) / fConst33));
	fConst35 = (0.015f / fConst33);
	fConst36 = (0 - fConst4);
	fConst37 = (0.025f / fConst5);
	fConst38 = (0.015f / fConst8);
	clear_state_f();
}

void GxPreAmpMono::connect(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case OUTPUT_LEVEL:
      fslider0_ = (float*)data;
      break;
    case INPUT_LEVEL:
      fslider1_ = (float*)data;
      break;
    case RESONANCE:
      fslider2_ = (float*)data;
      break;
    case PRESENCE:
      fslider3_ = (float*)data;
    case FEEDBACK:
      fslider4_ = (float*)data;
      break;
    default:
      break;
    }
}

void GxPreAmpMono::run(uint32_t n_samples, float* input0, float* output0)
{
    fslider0  = (*fslider0_);
    fslider1  = (*fslider1_);
    fslider2  = (*fslider2_);
    fslider3  = (*fslider3_);
    fslider4  = (*fslider4_);

	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * fslider0)));
	float 	fSlow1 = (0.0010000000000000009f * powf(10,(0.05f * fslider1)));
	float 	fSlow2 = (0.0001000000000000001f * fslider2);
	float 	fSlow3 = (0.0001000000000000001f * fslider3);
	float 	fSlow4 = (0.0010000000000000009f * powf(10,(0.05f * fslider4)));
	for (uint32_t i=0; i<n_samples; i++) {
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		fRec9[0] = (fSlow1 + (0.999f * fRec9[1]));
		fRec10[0] = (fSlow2 + (0.999f * fRec10[1]));
		fRec13[0] = (fSlow3 + (0.999f * fRec13[1]));
		fRec16[0] = (fSlow4 + (0.999f * fRec16[1]));
		fRec17[0] = ((fConst23 * (fRec1[1] + fRec1[2])) + (fConst3 * fRec17[1]));
		float fTemp0 = (fRec17[0] * fRec16[0]);
		fVec0[0] = fTemp0;
		fRec15[0] = ((fConst25 * ((fConst24 * fVec0[1]) + (fConst18 * fVec0[0]))) + (fConst22 * fRec15[1]));
		fRec14[0] = (fRec15[0] - (fConst20 * ((fConst19 * fRec14[2]) + (fConst17 * fRec14[1]))));
		float fTemp1 = (fVec0[0] + (fConst20 * ((((fConst16 * fRec14[0]) + (fConst26 * fRec14[1])) + (fConst16 * fRec14[2])) * (powf(10,(0.05f * (0 - (24 * fRec13[0])))) - 1))));
		fVec1[0] = fTemp1;
		fRec12[0] = ((fConst29 * fRec12[1]) + (fConst28 * (fVec1[0] + fVec1[1])));
		fRec11[0] = (fRec12[0] - (fConst14 * ((fConst13 * fRec11[2]) + (fConst11 * fRec11[1]))));
		float fTemp2 = (0 - ((fVec1[0] + (fConst14 * ((fRec11[2] + (fRec11[0] + (2 * fRec11[1]))) * (powf(10,(0.05f * (0 - (36 * fRec10[0])))) - 1)))) - ((float)input0[i] * fRec9[0])));
		fVec2[0] = fTemp2;
		fRec8[0] = ((fConst31 * ((fConst30 * fVec2[1]) + (fConst7 * fVec2[0]))) + (fConst9 * fRec8[1]));
		fRec18[0] = ((fConst35 * (fRec7[1] + fRec7[2])) + (fConst34 * fRec18[1]));
		fRec7[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec18[0] + fRec8[0]) - 1.5025f)) - 149.83333333333331f);
		fRec6[0] = ((fConst37 * ((fConst36 * fRec7[1]) + (fConst4 * fRec7[0]))) + (fConst6 * fRec6[1]));
		fRec5[0] = ((fConst23 * (fRec6[0] + fRec6[1])) + (fConst3 * fRec5[1]));
		fRec19[0] = ((fConst38 * (fRec4[1] + fRec4[2])) + (fConst9 * fRec19[1]));
		fRec4[0] = (Ftube(TUBE_TABLE_12AU7_68k, ((fRec19[0] + (0.6918309709189365f * fRec5[0])) - 1.4925f)) - 150.5f);
		fRec3[0] = ((fConst37 * ((fConst36 * fRec4[1]) + (fConst4 * fRec4[0]))) + (fConst6 * fRec3[1]));
		fRec2[0] = ((fConst23 * (fRec3[0] + fRec3[1])) + (fConst3 * fRec2[1]));
		fRec1[0] = (3.427677865464503f * fRec2[0]);
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec19[1] = fRec19[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec18[1] = fRec18[0];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec1[1] = fVec1[0];
		fRec14[2] = fRec14[1]; fRec14[1] = fRec14[0];
		fRec15[1] = fRec15[0];
		fVec0[1] = fVec0[0];
		fRec17[1] = fRec17[0];
		fRec16[1] = fRec16[0];
		fRec13[1] = fRec13[0];
		fRec10[1] = fRec10[0];
		fRec9[1] = fRec9[0];
		fRec0[1] = fRec0[0];
	}

}



// static wrappers
void GxPreAmpMono::init_static(uint32_t samplingFreq, GxPreAmpMono *p)
{
  p->init(samplingFreq);
}

void GxPreAmpMono::connect_static(uint32_t port,void* data, GxPreAmpMono *p)
{
  p->connect(port, data);
}


/////////////////////////////// STEREO /////////////////////////////////


inline void GxPreAmpStereo::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec32[i] = 0;
	for (int i=0; i<2; i++) fVec3[i] = 0;
	for (int i=0; i<2; i++) fRec31[i] = 0;
	for (int i=0; i<3; i++) fRec30[i] = 0;
	for (int i=0; i<2; i++) fVec4[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec28[i] = 0;
	for (int i=0; i<2; i++) fVec5[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<2; i++) fRec33[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<2; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec34[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec21[i] = 0;
	for (int i=0; i<3; i++) fRec20[i] = 0; 
}


inline void GxPreAmpStereo::init(uint32_t samplingFreq)
{
 	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / tanf((62831.853071795864f / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0f / tanf((97.38937226128358f / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = (1.0f / tanf((62.83185307179586f / iConst0)));
	fConst8 = (1 + fConst7);
	fConst9 = (0 - ((1 - fConst7) / fConst8));
	fConst10 = tanf((1413.7166941154069f / iConst0));
	fConst11 = (2 * (1 - (1.0f / faustpower<2>(fConst10))));
	fConst12 = (1.0f / fConst10);
	fConst13 = (1 + ((fConst12 - 1.0000000000000004f) / fConst10));
	fConst14 = (1.0f / (1 + ((1.0000000000000004f + fConst12) / fConst10)));
	fConst15 = (1 + fConst12);
	fConst16 = (0 - ((1 - fConst12) / fConst15));
	fConst17 = tanf((3141.592653589793f / iConst0));
	fConst18 = (1.0f / faustpower<2>(fConst17));
	fConst19 = (2 * (1 - fConst18));
	fConst20 = (1.0f / fConst17);
	fConst21 = (1 + ((fConst20 - 1.0000000000000004f) / fConst17));
	fConst22 = (1.0f / (1 + ((1.0000000000000004f + fConst20) / fConst17)));
	fConst23 = (1 + fConst20);
	fConst24 = (0 - ((1 - fConst20) / fConst23));
	fConst25 = (1.0f / fConst2);
	fConst26 = (0 - fConst20);
	fConst27 = (1.0f / fConst23);
	fConst28 = (2 * (0 - fConst18));
	fConst29 = (1.0f / fConst15);
	fConst30 = (0 - fConst7);
	fConst31 = (1.0f / fConst8);
	fConst32 = (1.0f / tanf((125.66370614359172f / iConst0)));
	fConst33 = (1 + fConst32);
	fConst34 = (0 - ((1 - fConst32) / fConst33));
	fConst35 = (0.015f / fConst33);
	fConst36 = (0 - fConst4);
	fConst37 = (0.025f / fConst5);
	fConst38 = (0.015f / fConst8);
	clear_state_f();
}

void GxPreAmpStereo::connect(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case OUTPUT_LEVEL:
      fslider0_ = (float*)data;
      break;
    case INPUT_LEVEL:
      fslider1_ = (float*)data;
      break;
    case FEEDBACK:
      fslider2_ = (float*)data;
      break;
    case RESONANCE:
      fslider3_ = (float*)data;
      break;
    case PRESENCE:
      fslider4_ = (float*)data;
      break;
    default:
      break;
    }
}

inline void GxPreAmpStereo::run(uint32_t count, float *input0, float *input1, float *output0, float *output1)
{
	fslider0 = (*fslider0_);
	fslider1 = (*fslider1_);
	fslider2 = (*fslider2_);
	fslider3 = (*fslider3_);
	fslider4 = (*fslider4_);

	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * fslider0)));
	float 	fSlow1 = (0.0010000000000000009f * powf(10,(0.05f * fslider1)));
	float 	fSlow2 = (0.0010000000000000009f * powf(10,(0.05f * fslider2)));
	float 	fSlow3 = (0.0001000000000000001f * fslider3);
	float 	fSlow4 = (0.0001000000000000001f * fslider4);
	for (uint32_t i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		fRec9[0] = (fSlow1 + (0.999f * fRec9[1]));
		fRec14[0] = (fSlow2 + (0.999f * fRec14[1]));
		fRec15[0] = ((fConst25 * (fRec1[1] + fRec1[2])) + (fConst3 * fRec15[1]));
		float fTemp0 = (fRec15[0] * fRec14[0]);
		fVec0[0] = fTemp0;
		fRec13[0] = ((fConst27 * ((fConst26 * fVec0[1]) + (fConst20 * fVec0[0]))) + (fConst24 * fRec13[1]));
		fRec12[0] = (fRec13[0] - (fConst22 * ((fConst21 * fRec12[2]) + (fConst19 * fRec12[1]))));
		fRec16[0] = (fSlow3 + (0.999f * fRec16[1]));
		float fTemp1 = (powf(10,(0.05f * (0 - (24 * fRec16[0])))) - 1);
		float fTemp2 = (fVec0[0] + (fConst22 * (fTemp1 * (((fConst18 * fRec12[0]) + (fConst28 * fRec12[1])) + (fConst18 * fRec12[2])))));
		fVec1[0] = fTemp2;
		fRec11[0] = ((fConst29 * (fVec1[0] + fVec1[1])) + (fConst16 * fRec11[1]));
		fRec10[0] = (fRec11[0] - (fConst14 * ((fConst13 * fRec10[2]) + (fConst11 * fRec10[1]))));
		fRec17[0] = (fSlow4 + (0.999f * fRec17[1]));
		float fTemp3 = (powf(10,(0.05f * (0 - (36 * fRec17[0])))) - 1);
		float fTemp4 = (0 - ((fVec1[0] + (fConst14 * (fTemp3 * (fRec10[2] + (fRec10[0] + (2 * fRec10[1])))))) - ((float)input0[i] * fRec9[0])));
		fVec2[0] = fTemp4;
		fRec8[0] = ((fConst31 * ((fConst30 * fVec2[1]) + (fConst7 * fVec2[0]))) + (fConst9 * fRec8[1]));
		fRec18[0] = ((fConst35 * (fRec7[1] + fRec7[2])) + (fConst34 * fRec18[1]));
		fRec7[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec18[0] + fRec8[0]) - 1.5025f)) - 149.83333333333331f);
		fRec6[0] = ((fConst37 * ((fConst36 * fRec7[1]) + (fConst4 * fRec7[0]))) + (fConst6 * fRec6[1]));
		fRec5[0] = ((fConst25 * (fRec6[0] + fRec6[1])) + (fConst3 * fRec5[1]));
		fRec19[0] = ((fConst38 * (fRec4[1] + fRec4[2])) + (fConst9 * fRec19[1]));
		fRec4[0] = (Ftube(TUBE_TABLE_12AU7_68k, ((fRec19[0] + (0.6918309709189365f * fRec5[0])) - 1.4925f)) - 150.5f);
		fRec3[0] = ((fConst37 * ((fConst36 * fRec4[1]) + (fConst4 * fRec4[0]))) + (fConst6 * fRec3[1]));
		fRec2[0] = ((fConst25 * (fRec3[0] + fRec3[1])) + (fConst3 * fRec2[1]));
		fRec1[0] = (3.427677865464503f * fRec2[0]);
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		fRec32[0] = ((fConst25 * (fRec20[1] + fRec20[2])) + (fConst3 * fRec32[1]));
		float fTemp5 = (fRec14[0] * fRec32[0]);
		fVec3[0] = fTemp5;
		fRec31[0] = ((fConst27 * ((fConst26 * fVec3[1]) + (fConst20 * fVec3[0]))) + (fConst24 * fRec31[1]));
		fRec30[0] = (fRec31[0] - (fConst22 * ((fConst21 * fRec30[2]) + (fConst19 * fRec30[1]))));
		float fTemp6 = (fVec3[0] + (fConst22 * ((((fConst18 * fRec30[0]) + (fConst28 * fRec30[1])) + (fConst18 * fRec30[2])) * fTemp1)));
		fVec4[0] = fTemp6;
		fRec29[0] = ((fConst29 * (fVec4[0] + fVec4[1])) + (fConst16 * fRec29[1]));
		fRec28[0] = (fRec29[0] - (fConst14 * ((fConst13 * fRec28[2]) + (fConst11 * fRec28[1]))));
		float fTemp7 = (0 - ((fVec4[0] + (fConst14 * ((fRec28[2] + (fRec28[0] + (2 * fRec28[1]))) * fTemp3))) - ((float)input1[i] * fRec9[0])));
		fVec5[0] = fTemp7;
		fRec27[0] = ((fConst31 * ((fConst30 * fVec5[1]) + (fConst7 * fVec5[0]))) + (fConst9 * fRec27[1]));
		fRec33[0] = ((fConst35 * (fRec26[1] + fRec26[2])) + (fConst34 * fRec33[1]));
		fRec26[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec33[0] + fRec27[0]) - 1.5025f)) - 149.83333333333331f);
		fRec25[0] = ((fConst37 * ((fConst36 * fRec26[1]) + (fConst4 * fRec26[0]))) + (fConst6 * fRec25[1]));
		fRec24[0] = ((fConst25 * (fRec25[0] + fRec25[1])) + (fConst3 * fRec24[1]));
		fRec34[0] = ((fConst38 * (fRec23[1] + fRec23[2])) + (fConst9 * fRec34[1]));
		fRec23[0] = (Ftube(TUBE_TABLE_12AU7_68k, ((fRec34[0] + (0.6918309709189365f * fRec24[0])) - 1.4925f)) - 150.5f);
		fRec22[0] = ((fConst37 * ((fConst36 * fRec23[1]) + (fConst4 * fRec23[0]))) + (fConst6 * fRec22[1]));
		fRec21[0] = ((fConst25 * (fRec22[0] + fRec22[1])) + (fConst3 * fRec21[1]));
		fRec20[0] = (3.427677865464503f * fRec21[0]);
		output1[i] = (FAUSTFLOAT)(fRec0[0] * fRec20[0]);
		// post processing
		fRec20[2] = fRec20[1]; fRec20[1] = fRec20[0];
		fRec21[1] = fRec21[0];
		fRec22[1] = fRec22[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec34[1] = fRec34[0];
		fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec33[1] = fRec33[0];
		fRec27[1] = fRec27[0];
		fVec5[1] = fVec5[0];
		fRec28[2] = fRec28[1]; fRec28[1] = fRec28[0];
		fRec29[1] = fRec29[0];
		fVec4[1] = fVec4[0];
		fRec30[2] = fRec30[1]; fRec30[1] = fRec30[0];
		fRec31[1] = fRec31[0];
		fVec3[1] = fVec3[0];
		fRec32[1] = fRec32[0];
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec19[1] = fRec19[0];
		fRec5[1] = fRec5[0];
		fRec6[1] = fRec6[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec18[1] = fRec18[0];
		fRec8[1] = fRec8[0];
		fVec2[1] = fVec2[0];
		fRec17[1] = fRec17[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[1] = fRec11[0];
		fVec1[1] = fVec1[0];
		fRec16[1] = fRec16[0];
		fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
		fRec13[1] = fRec13[0];
		fVec0[1] = fVec0[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec9[1] = fRec9[0];
		fRec0[1] = fRec0[0];
	}

}


// static wrappers
void GxPreAmpStereo::init_static(uint32_t samplingFreq, GxPreAmpStereo *p)
{
  p->init(samplingFreq);
}

void GxPreAmpStereo::connect_static(uint32_t port,void* data, GxPreAmpStereo *p)
{
  p->connect(port, data);
}
