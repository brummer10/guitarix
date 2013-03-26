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
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;}

inline void GxPreAmpMono::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / tanf((56548.66776461628f / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0f / tanf((97.38937226128358f / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = tanf((4712.38898038469f / iConst0));
	fConst8 = (1.0f / faustpower<2>(fConst7));
	fConst9 = (2 * (1 - fConst8));
	fConst10 = (1.0f / fConst7);
	fConst11 = (1 + ((fConst10 - 1.0000000000000004f) / fConst7));
	fConst12 = (1.0f / (1 + ((1.0000000000000004f + fConst10) / fConst7)));
	fConst13 = (1 + fConst10);
	fConst14 = (0 - ((1 - fConst10) / fConst13));
	fConst15 = tanf((2356.194490192345f / iConst0));
	fConst16 = (2 * (1 - (1.0f / faustpower<2>(fConst15))));
	fConst17 = (1.0f / fConst15);
	fConst18 = (1 + ((fConst17 - 1.0000000000000004f) / fConst15));
	fConst19 = (1.0f / (1 + ((1.0000000000000004f + fConst17) / fConst15)));
	fConst20 = (1 + fConst17);
	fConst21 = (0 - ((1 - fConst17) / fConst20));
	fConst22 = (1.0f / fConst20);
	fConst23 = (0 - fConst10);
	fConst24 = (1.0f / fConst13);
	fConst25 = (2 * (0 - fConst8));
	fConst26 = (1.0f / tanf((125.66370614359172f / iConst0)));
	fConst27 = (1 + fConst26);
	fConst28 = (0 - ((1 - fConst26) / fConst27));
	fConst29 = (0.015f / fConst27);
	fConst30 = (0 - fConst4);
	fConst31 = (0.025f / fConst5);
	fConst32 = (1.0f / tanf((62.83185307179586f / iConst0)));
	fConst33 = (1 + fConst32);
	fConst34 = (0 - ((1 - fConst32) / fConst33));
	fConst35 = (0.015f / fConst33);
	fConst36 = (1.0f / fConst2);
	clear_state_f();
}

void GxPreAmpMono::connect(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case OUTPUT_LEVEL:
      fslider0_ = (float*)data;
      break;
    case PRESENCE:
      fslider1_ = (float*)data;
      break ;
    case RESONANCE:
      fslider2_ = (float*)data;
      break;
    case FEEDBACK:
      fslider3_ = (float*)data;
      break;
    case DRIVE:
      fslider4_ = (float*)data;
      break;
    case INPUT_LEVEL:
      fslider5_ = (float*)data;
      break;
    default:
      break;
    }
}

void GxPreAmpMono::run(uint32_t count, float* input0, float* output0)
{
    fslider0  = (*fslider0_);
    fslider1  = (*fslider1_);
    fslider2  = (*fslider2_);
    fslider3  = (*fslider3_);
    fslider4  = (*fslider4_);
    fslider5  = (*fslider5_);


	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * fslider0)));
	float 	fSlow1 = (0.0001000000000000001f * fslider1);
	float 	fSlow2 = (0.0001000000000000001f * fslider2);
	float 	fSlow3 = (0.0010000000000000009f * powf(10,(0.05f * fslider3)));
	float 	fSlow4 = (0.0010000000000000009f * powf(10,(0.05f * fslider4)));
	float 	fSlow5 = (0.0010000000000000009f * powf(10,(0.05f * fslider5)));
	for (uint32_t i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		fRec7[0] = (fSlow1 + (0.999f * fRec7[1]));
		fRec10[0] = (fSlow2 + (0.999f * fRec10[1]));
		fRec12[0] = ((fConst22 * (fRec2[1] + fRec2[2])) + (fConst21 * fRec12[1]));
		fRec11[0] = (fRec12[0] - (fConst19 * ((fConst18 * fRec11[2]) + (fConst16 * fRec11[1]))));
		float fTemp0 = (fRec2[1] + (fConst19 * ((fRec11[2] + (fRec11[0] + (2 * fRec11[1]))) * (powf(10,(0.05f * (0 - (24 * fRec10[0])))) - 1))));
		fVec0[0] = fTemp0;
		fRec9[0] = ((fConst24 * ((fConst23 * fVec0[1]) + (fConst10 * fVec0[0]))) + (fConst14 * fRec9[1]));
		fRec8[0] = (fRec9[0] - (fConst12 * ((fConst11 * fRec8[2]) + (fConst9 * fRec8[1]))));
		fRec13[0] = (fSlow3 + (0.999f * fRec13[1]));
		fRec14[0] = (fSlow4 + (0.999f * fRec14[1]));
		fRec15[0] = (fSlow5 + (0.999f * fRec15[1]));
		fRec16[0] = ((fConst29 * (fRec6[1] + fRec6[2])) + (fConst28 * fRec16[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec16[0] + (((float)input0[i] * fRec15[0]) * fRec14[0])) - (1.5025f + (fRec13[0] * (fVec0[0] + (fConst12 * ((((fConst8 * fRec8[0]) + (fConst25 * fRec8[1])) + (fConst8 * fRec8[2])) * (powf(10,(0.05f * (0 - (24 * fRec7[0])))) - 1)))))))) - 149.83333333333331f);
		fRec5[0] = ((fConst31 * ((fConst30 * fRec6[1]) + (fConst4 * fRec6[0]))) + (fConst6 * fRec5[1]));
		fRec17[0] = ((fConst35 * (fRec4[1] + fRec4[2])) + (fConst34 * fRec17[1]));
		fRec4[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec17[0] + (0.6918309709189365f * fRec5[0])) - 1.4925f)) - 150.5f);
		fRec3[0] = ((fConst31 * ((fConst30 * fRec4[1]) + (fConst4 * fRec4[0]))) + (fConst6 * fRec3[1]));
		fRec2[0] = (0.6918309709189365f * fRec3[0]);
		fRec1[0] = ((fConst36 * (fRec2[0] + fRec2[1])) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec17[1] = fRec17[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec0[1] = fVec0[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fRec10[1] = fRec10[0];
		fRec7[1] = fRec7[0];
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
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec27[i] = 0;
	for (int i=0; i<3; i++) fRec26[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec25[i] = 0;
	for (int i=0; i<3; i++) fRec24[i] = 0;
	for (int i=0; i<2; i++) fRec28[i] = 0;
	for (int i=0; i<3; i++) fRec23[i] = 0;
	for (int i=0; i<2; i++) fRec22[i] = 0;
	for (int i=0; i<2; i++) fRec29[i] = 0;
	for (int i=0; i<3; i++) fRec21[i] = 0;
	for (int i=0; i<2; i++) fRec20[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
}


inline void GxPreAmpStereo::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / tanf((56548.66776461628f / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0f / tanf((97.38937226128358f / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = tanf((4712.38898038469f / iConst0));
	fConst8 = (1.0f / faustpower<2>(fConst7));
	fConst9 = (2 * (1 - fConst8));
	fConst10 = (1.0f / fConst7);
	fConst11 = (1 + ((fConst10 - 1.0000000000000004f) / fConst7));
	fConst12 = (1.0f / (1 + ((1.0000000000000004f + fConst10) / fConst7)));
	fConst13 = (1 + fConst10);
	fConst14 = (0 - ((1 - fConst10) / fConst13));
	fConst15 = tanf((2356.194490192345f / iConst0));
	fConst16 = (2 * (1 - (1.0f / faustpower<2>(fConst15))));
	fConst17 = (1.0f / fConst15);
	fConst18 = (1 + ((fConst17 - 1.0000000000000004f) / fConst15));
	fConst19 = (1.0f / (1 + ((1.0000000000000004f + fConst17) / fConst15)));
	fConst20 = (1 + fConst17);
	fConst21 = (0 - ((1 - fConst17) / fConst20));
	fConst22 = (1.0f / fConst20);
	fConst23 = (0 - fConst10);
	fConst24 = (1.0f / fConst13);
	fConst25 = (2 * (0 - fConst8));
	fConst26 = (1.0f / tanf((125.66370614359172f / iConst0)));
	fConst27 = (1 + fConst26);
	fConst28 = (0 - ((1 - fConst26) / fConst27));
	fConst29 = (0.015f / fConst27);
	fConst30 = (0 - fConst4);
	fConst31 = (0.025f / fConst5);
	fConst32 = (1.0f / tanf((62.83185307179586f / iConst0)));
	fConst33 = (1 + fConst32);
	fConst34 = (0 - ((1 - fConst32) / fConst33));
	fConst35 = (0.015f / fConst33);
	fConst36 = (1.0f / fConst2);
	clear_state_f();
}

void GxPreAmpStereo::connect(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case OUTPUT_LEVEL:
      fslider0_ = (float*)data;
      break;
    case RESONANCE:
      fslider1_ = (float*)data;
      break;
    case PRESENCE:
      fslider2_ = (float*)data;
      break;
    case FEEDBACK:
      fslider3_ = (float*)data;
      break;
    case DRIVE:
      fslider4_ = (float*)data;
      break;
    case INPUT_LEVEL:
      fslider5_ = (float*)data;
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
	fslider5 = (*fslider5_);
	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * fslider0)));
	float 	fSlow1 = (0.0001000000000000001f * fslider1);
	float 	fSlow2 = (0.0001000000000000001f * fslider2);
	float 	fSlow3 = (0.0010000000000000009f * powf(10,(0.05f * fslider3)));
	float 	fSlow4 = (0.0010000000000000009f * powf(10,(0.05f * fslider4)));
	float 	fSlow5 = (0.0010000000000000009f * powf(10,(0.05f * fslider5)));
	for (uint32_t i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		fRec10[0] = ((fConst22 * (fRec2[1] + fRec2[2])) + (fConst21 * fRec10[1]));
		fRec9[0] = (fRec10[0] - (fConst19 * ((fConst18 * fRec9[2]) + (fConst16 * fRec9[1]))));
		fRec11[0] = (fSlow1 + (0.999f * fRec11[1]));
		float fTemp0 = (powf(10,(0.05f * (0 - (24 * fRec11[0])))) - 1);
		float fTemp1 = (fRec2[1] + (fConst19 * (fTemp0 * (fRec9[2] + (fRec9[0] + (2 * fRec9[1]))))));
		fVec0[0] = fTemp1;
		fRec8[0] = ((fConst24 * ((fConst23 * fVec0[1]) + (fConst10 * fVec0[0]))) + (fConst14 * fRec8[1]));
		fRec7[0] = (fRec8[0] - (fConst12 * ((fConst11 * fRec7[2]) + (fConst9 * fRec7[1]))));
		fRec12[0] = (fSlow2 + (0.999f * fRec12[1]));
		float fTemp2 = (powf(10,(0.05f * (0 - (24 * fRec12[0])))) - 1);
		fRec13[0] = (fSlow3 + (0.999f * fRec13[1]));
		fRec14[0] = (fSlow4 + (0.999f * fRec14[1]));
		fRec15[0] = (fSlow5 + (0.999f * fRec15[1]));
		fRec16[0] = ((fConst29 * (fRec6[1] + fRec6[2])) + (fConst28 * fRec16[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec16[0] + (((float)input0[i] * fRec15[0]) * fRec14[0])) - (1.5025f + (fRec13[0] * (fVec0[0] + (fConst12 * (fTemp2 * (((fConst8 * fRec7[0]) + (fConst25 * fRec7[1])) + (fConst8 * fRec7[2]))))))))) - 149.83333333333331f);
		fRec5[0] = ((fConst31 * ((fConst30 * fRec6[1]) + (fConst4 * fRec6[0]))) + (fConst6 * fRec5[1]));
		fRec17[0] = ((fConst35 * (fRec4[1] + fRec4[2])) + (fConst34 * fRec17[1]));
		fRec4[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec17[0] + (0.6918309709189365f * fRec5[0])) - 1.4925f)) - 150.5f);
		fRec3[0] = ((fConst31 * ((fConst30 * fRec4[1]) + (fConst4 * fRec4[0]))) + (fConst6 * fRec3[1]));
		fRec2[0] = (0.6918309709189365f * fRec3[0]);
		fRec1[0] = ((fConst36 * (fRec2[0] + fRec2[1])) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		fRec27[0] = ((fConst22 * (fRec19[1] + fRec19[2])) + (fConst21 * fRec27[1]));
		fRec26[0] = (fRec27[0] - (fConst19 * ((fConst18 * fRec26[2]) + (fConst16 * fRec26[1]))));
		float fTemp3 = (fRec19[1] + (fConst19 * ((fRec26[2] + (fRec26[0] + (2 * fRec26[1]))) * fTemp0)));
		fVec1[0] = fTemp3;
		fRec25[0] = ((fConst24 * ((fConst23 * fVec1[1]) + (fConst10 * fVec1[0]))) + (fConst14 * fRec25[1]));
		fRec24[0] = (fRec25[0] - (fConst12 * ((fConst11 * fRec24[2]) + (fConst9 * fRec24[1]))));
		fRec28[0] = ((fConst29 * (fRec23[1] + fRec23[2])) + (fConst28 * fRec28[1]));
		fRec23[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec28[0] + (((float)input1[i] * fRec15[0]) * fRec14[0])) - (1.5025f + (fRec13[0] * (fVec1[0] + (fConst12 * ((((fConst8 * fRec24[0]) + (fConst25 * fRec24[1])) + (fConst8 * fRec24[2])) * fTemp2))))))) - 149.83333333333331f);
		fRec22[0] = ((fConst31 * ((fConst30 * fRec23[1]) + (fConst4 * fRec23[0]))) + (fConst6 * fRec22[1]));
		fRec29[0] = ((fConst35 * (fRec21[1] + fRec21[2])) + (fConst34 * fRec29[1]));
		fRec21[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec29[0] + (0.6918309709189365f * fRec22[0])) - 1.4925f)) - 150.5f);
		fRec20[0] = ((fConst31 * ((fConst30 * fRec21[1]) + (fConst4 * fRec21[0]))) + (fConst6 * fRec20[1]));
		fRec19[0] = (0.6918309709189365f * fRec20[0]);
		fRec18[0] = ((fConst36 * (fRec19[0] + fRec19[1])) + (fConst3 * fRec18[1]));
		output1[i] = (FAUSTFLOAT)(fRec0[0] * fRec18[0]);
		// post processing
		fRec18[1] = fRec18[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec21[2] = fRec21[1]; fRec21[1] = fRec21[0];
		fRec29[1] = fRec29[0];
		fRec22[1] = fRec22[0];
		fRec23[2] = fRec23[1]; fRec23[1] = fRec23[0];
		fRec28[1] = fRec28[0];
		fRec24[2] = fRec24[1]; fRec24[1] = fRec24[0];
		fRec25[1] = fRec25[0];
		fVec1[1] = fVec1[0];
		fRec26[2] = fRec26[1]; fRec26[1] = fRec26[0];
		fRec27[1] = fRec27[0];
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec17[1] = fRec17[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec16[1] = fRec16[0];
		fRec15[1] = fRec15[0];
		fRec14[1] = fRec14[0];
		fRec13[1] = fRec13[0];
		fRec12[1] = fRec12[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fVec0[1] = fVec0[0];
		fRec11[1] = fRec11[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
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
