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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec13[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fVec2[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<2; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

inline void GxRedeyeMono::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / tanf((51933.66815649287f / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0f / tanf((97.38937226128358f / iConst0)));
	fConst5 = (1 + fConst4);
	fConst6 = (0 - ((1 - fConst4) / fConst5));
	fConst7 = tanf((6283.185307179586f / iConst0));
	fConst8 = (1.0f / faustpower<2>(fConst7));
	fConst9 = (2 * (1 - fConst8));
	fConst10 = (1.0f / fConst7);
	fConst11 = (1 + ((fConst10 - 1.0000000000000004f) / fConst7));
	fConst12 = (1.0f / (1 + ((1.0000000000000004f + fConst10) / fConst7)));
	fConst13 = (1 + fConst10);
	fConst14 = (0 - ((1 - fConst10) / fConst13));
	fConst15 = tanf((3141.592653589793f / iConst0));
	fConst16 = (2 * (1 - (1.0f / faustpower<2>(fConst15))));
	fConst17 = float((1.0f / iConst0));
	fConst18 = (fConst17 / sinf((6283.185307179586f * fConst17)));
	fConst19 = (8854.211111863275f * fConst18);
	fConst20 = (1.0f / fConst15);
	fConst21 = (1 + ((fConst20 - fConst19) / fConst15));
	fConst22 = (1 + ((fConst19 + fConst20) / fConst15));
	fConst23 = (1.0f / fConst22);
	fConst24 = tanf((1570.7963267948965f / iConst0));
	fConst25 = (2 * (1 - (1.0f / faustpower<2>(fConst24))));
	fConst26 = (1.0f / fConst24);
	fConst27 = (1 + ((fConst26 - 1.0000000000000004f) / fConst24));
	fConst28 = (1.0f / (1 + ((1.0000000000000004f + fConst26) / fConst24)));
	fConst29 = (1 + fConst26);
	fConst30 = (0 - ((1 - fConst26) / fConst29));
	fConst31 = (1.0f / tanf((270.1769682087222f / iConst0)));
	fConst32 = (1 + fConst31);
	fConst33 = (0 - ((1 - fConst31) / fConst32));
	fConst34 = (0.027f / fConst32);
	fConst35 = (0 - fConst4);
	fConst36 = (0.025f / fConst5);
	fConst37 = (1.0f / fConst29);
	fConst38 = (3141.592653589793f * fConst18);
	fConst39 = (1 + ((fConst20 - fConst38) / fConst15));
	fConst40 = (1 + ((fConst38 + fConst20) / fConst15));
	fConst41 = (0 - fConst10);
	fConst42 = (1.0f / (fConst22 * fConst13));
	fConst43 = (2 * (0 - fConst8));
	fConst44 = (1.0f / fConst2);
	fConst45 = (1.0f / tanf((314.1592653589793f / iConst0)));
	fConst46 = (1 + fConst45);
	fConst47 = (0 - ((1 - fConst45) / fConst46));
	fConst48 = (0.015f / fConst46);
	fConst49 = (1.0f / tanf((376.99111843077515f / iConst0)));
	fConst50 = (1 + fConst49);
	fConst51 = (0 - ((1 - fConst49) / fConst50));
	fConst52 = (0.0082f / fConst50);
	clear_state_f();
}

void GxRedeyeMono::connect(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case VOLUME:
      fslider0_ = (float*)data;
      break;
    case FEEDBACK:
	fcheckbox0_ = (float*)data;
      break;
    case GAIN:
      fslider1_ = (float*)data;
      break;
    case TONE:
      fslider2_ = (float*)data;
      break;
    default:
      break;
    }
}

void GxRedeyeMono::run_chump(uint32_t count, float* input0, float* output0)
{
  fslider0  = (*fslider0_);
  fslider1  = (*fslider1_);
  fslider2  = (*fslider2_);
  fcheckbox0 = (*fcheckbox0_) ;

	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * fslider0)));
	float 	fSlow1 = (0.5011872336272722f * (1 - fcheckbox0));
	float 	fSlow2 = (0.0010000000000000009f * powf(10,(0.05f * fslider1)));
	float 	fSlow3 = fslider2;
	float 	fSlow4 = (fConst28 * (powf(10,(0.05f * (0 - fSlow3))) - 1));
	float 	fSlow5 = (fConst12 * (powf(10,(0.05f * fSlow3)) - 1));
	for (uint32_t i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		float fTemp0 = (fConst16 * fRec10[1]);
		fRec13[0] = (fSlow2 + (0.999f * fRec13[1]));
		fRec16[0] = ((fConst34 * (fRec15[1] + fRec15[2])) + (fConst33 * fRec16[1]));
		fRec15[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((float)input0[i] + fRec16[0]) - 1.581656f)) - 191.42014814814814f);
		fRec14[0] = ((fConst36 * ((fConst35 * fRec15[1]) + (fConst4 * fRec15[0]))) + (fConst6 * fRec14[1]));
		float fTemp1 = (fRec14[0] * fRec13[0]);
		fVec0[0] = fTemp1;
		fRec12[0] = ((fConst37 * (fVec0[0] + fVec0[1])) + (fConst30 * fRec12[1]));
		fRec11[0] = (fRec12[0] - (fConst28 * ((fConst27 * fRec11[2]) + (fConst25 * fRec11[1]))));
		fRec10[0] = ((fVec0[0] + (fSlow4 * (fRec11[2] + (fRec11[0] + (2 * fRec11[1]))))) - (fConst23 * ((fConst21 * fRec10[2]) + fTemp0)));
		float fTemp2 = ((fTemp0 + (fConst40 * fRec10[0])) + (fConst39 * fRec10[2]));
		fVec1[0] = fTemp2;
		fRec9[0] = ((fConst42 * ((fConst41 * fVec1[1]) + (fConst10 * fVec1[0]))) + (fConst14 * fRec9[1]));
		fRec8[0] = (fRec9[0] - (fConst12 * ((fConst11 * fRec8[2]) + (fConst9 * fRec8[1]))));
		float fTemp3 = (((fConst23 * fVec1[0]) + (fSlow5 * (((fConst8 * fRec8[0]) + (fConst43 * fRec8[1])) + (fConst8 * fRec8[2])))) + (fSlow1 * fRec2[1]));
		fVec2[0] = fTemp3;
		fRec7[0] = ((fConst44 * (fVec2[0] + fVec2[1])) + (fConst3 * fRec7[1]));
		fRec17[0] = ((fConst48 * (fRec6[1] + fRec6[2])) + (fConst47 * fRec17[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec17[0] + fRec7[0]) - 1.204285f)) - 169.71433333333334f);
		fRec5[0] = ((fConst36 * ((fConst35 * fRec6[1]) + (fConst4 * fRec6[0]))) + (fConst6 * fRec5[1]));
		fRec18[0] = ((fConst52 * (fRec4[1] + fRec4[2])) + (fConst51 * fRec18[1]));
		fRec4[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec18[0] + fRec5[0]) - 1.130462f)) - 112.13878048780487f);
		fRec3[0] = ((fConst36 * ((fConst35 * fRec4[1]) + (fConst4 * fRec4[0]))) + (fConst6 * fRec3[1]));
		fRec2[0] = fRec3[0];
		fRec1[0] = ((fConst44 * (fRec2[0] + fRec2[1])) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[1] = fRec3[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec18[1] = fRec18[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec17[1] = fRec17[0];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec1[1] = fVec1[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec0[1] = fVec0[0];
		fRec14[1] = fRec14[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec13[1] = fRec13[0];
		fRec0[1] = fRec0[0];
	}

}


void GxRedeyeMono::run_chump2(uint32_t count, float* input0, float* output0)
{
  fslider0  = (*fslider0_);
  fslider1  = (*fslider1_);
  fslider2  = (*fslider2_);
  fcheckbox0 = (*fcheckbox0_) ;
	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * fslider0)));
	float 	fSlow1 = (0.5011872336272722f * (1 - fcheckbox0));
	float 	fSlow2 = (0.0010000000000000009f * powf(10,(0.05f * fslider1)));
	float 	fSlow3 = fslider2;
	float 	fSlow4 = (fConst28 * (powf(10,(0.05f * (0 - fSlow3))) - 1));
	float 	fSlow5 = (fConst12 * (powf(10,(0.05f * fSlow3)) - 1));
	for (uint32_t i=0; i<count; i++) {
		fRec4[0] = (fSlow0 + (0.999f * fRec4[1]));
		float fTemp0 = (fConst16 * fRec10[1]);
		fRec13[0] = (fSlow2 + (0.999f * fRec13[1]));
		fRec16[0] = ((fConst34 * (fRec15[1] + fRec15[2])) + (fConst33 * fRec16[1]));
		fRec15[0] = (Ftube(TUBE_TABLE_12AX7_68k, (((float)input0[i] + fRec16[0]) - 1.581656f)) - 191.42014814814814f);
		fRec14[0] = ((fConst36 * ((fConst35 * fRec15[1]) + (fConst4 * fRec15[0]))) + (fConst6 * fRec14[1]));
		float fTemp1 = (fRec14[0] * fRec13[0]);
		fVec0[0] = fTemp1;
		fRec12[0] = ((fConst37 * (fVec0[0] + fVec0[1])) + (fConst30 * fRec12[1]));
		fRec11[0] = (fRec12[0] - (fConst28 * ((fConst27 * fRec11[2]) + (fConst25 * fRec11[1]))));
		fRec10[0] = ((fVec0[0] + (fSlow4 * (fRec11[2] + (fRec11[0] + (2 * fRec11[1]))))) - (fConst23 * ((fConst21 * fRec10[2]) + fTemp0)));
		float fTemp2 = ((fTemp0 + (fConst40 * fRec10[0])) + (fConst39 * fRec10[2]));
		fVec1[0] = fTemp2;
		fRec9[0] = ((fConst42 * ((fConst41 * fVec1[1]) + (fConst10 * fVec1[0]))) + (fConst14 * fRec9[1]));
		fRec8[0] = (fRec9[0] - (fConst12 * ((fConst11 * fRec8[2]) + (fConst9 * fRec8[1]))));
		float fTemp3 = (((fConst23 * fVec1[0]) + (fSlow5 * (((fConst8 * fRec8[0]) + (fConst43 * fRec8[1])) + (fConst8 * fRec8[2])))) + (fSlow1 * fRec1[1]));
		fVec2[0] = fTemp3;
		fRec7[0] = ((fConst44 * (fVec2[0] + fVec2[1])) + (fConst3 * fRec7[1]));
		fRec17[0] = ((fConst48 * (fRec6[1] + fRec6[2])) + (fConst47 * fRec17[1]));
		fRec6[0] = (Ftube(TUBE_TABLE_12AX7_250k, ((fRec17[0] + fRec7[0]) - 1.204285f)) - 169.71433333333334f);
		fRec5[0] = ((fConst36 * ((fConst35 * fRec6[1]) + (fConst4 * fRec6[0]))) + (fConst6 * fRec5[1]));
		fRec18[0] = ((fConst52 * (fRec3[1] + fRec3[2])) + (fConst51 * fRec18[1]));
		fRec3[0] = (Ftube(TUBE_TABLE_6V6_250k, ((fRec18[0] + (fRec5[0] * fRec4[0])) - 1.130462f)) - 112.13878048780487f);
		fRec2[0] = ((fConst36 * ((fConst35 * fRec3[1]) + (fConst4 * fRec3[0]))) + (fConst6 * fRec2[1]));
		fRec1[0] = fRec2[0];
		fRec0[0] = ((fConst44 * (fRec1[0] + fRec1[1])) + (fConst3 * fRec0[1]));
		output0[i] = (FAUSTFLOAT)fRec0[0];
		// post processing
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec18[1] = fRec18[0];
		fRec5[1] = fRec5[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec17[1] = fRec17[0];
		fRec7[1] = fRec7[0];
		fVec2[1] = fVec2[0];
		fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
		fRec9[1] = fRec9[0];
		fVec1[1] = fVec1[0];
		fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec12[1] = fRec12[0];
		fVec0[1] = fVec0[0];
		fRec14[1] = fRec14[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec16[1] = fRec16[0];
		fRec13[1] = fRec13[0];
		fRec4[1] = fRec4[0];
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


