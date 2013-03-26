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

#include "valve.h"

class TiltTone {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	float 	fRec0[2];
	int 	iConst0;
	float 	fConst1;
	float 	fConst2;
	float 	fConst3;
	float 	fConst4;
	float 	fConst5;
	float 	fConst6;
	float 	fConst7;
	float 	fConst8;
	float 	fConst9;
	float 	fConst10;
	float 	fConst11;
	float 	fConst12;
	float 	fConst13;
	float 	fConst14;
	float 	fConst15;
	float 	fConst16;
	float 	fConst17;
	float 	fConst18;
	float 	fConst19;
	float 	fConst20;
	float 	fConst21;
	float 	fConst22;
	float 	fConst23;
	float 	fConst24;
	float 	fConst25;
	float 	fRec10[2];
	float 	fRec9[3];
	float 	fConst26;
	float 	fConst27;
	float 	fRec8[2];
	float 	fConst28;
	float 	fRec7[2];
	float 	fRec6[3];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	float 	fVec0[2];
	float 	fConst29;
	float 	fConst30;
	float 	fRec5[2];
	float 	fRec4[3];
	float 	fConst31;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fRec11[2];
	float 	fVec1[2];
	float 	fConst32;
	float 	fRec3[2];
	float 	fRec12[2];
	float 	fRec2[3];
	float 	fRec1[2];
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void run(uint32_t count, float *input0, float *output0);
    void connect(uint32_t port,void* data);

public:
    static void init_static(uint32_t samplingFreq, TiltTone*);
	static void run_static(uint32_t count, float *input0, float *output0, TiltTone*);
    static void connect_static(uint32_t port,void* data, TiltTone *p);
    static void clear_state_static(TiltTone*);
	TiltTone();
	~TiltTone();
};


void TiltTone::connect(uint32_t port,void* data)
{
  switch ((EffectPortIndex)port)
    {
    case DRIVE:
      fslider0_ = (float*)data;
      break;
    case TONE:
      fslider1_ = (float*)data;
      break;
    case GAIN:
      fslider2_ = (float*)data;
      break;
    default:
      break;
    }
}


TiltTone::TiltTone() {
}

TiltTone::~TiltTone() {
}

inline void TiltTone::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec0[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec11[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<3; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
}

inline void TiltTone::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (1.0f / tanf((97.38937226128358f / iConst0)));
	fConst2 = (1 + fConst1);
	fConst3 = (0 - ((1 - fConst1) / fConst2));
	fConst4 = (1.0f / tanf((20517.741620594938f / iConst0)));
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
	fConst22 = (1.0f / tanf((270.1769682087222f / iConst0)));
	fConst23 = (1 + fConst22);
	fConst24 = (0 - ((1 - fConst22) / fConst23));
	fConst25 = (0.027f / fConst23);
	fConst26 = (0 - fConst1);
	fConst27 = (0.025f / fConst2);
	fConst28 = (1.0f / fConst20);
	fConst29 = (0 - fConst10);
	fConst30 = (1.0f / fConst13);
	fConst31 = (2 * (0 - fConst8));
	fConst32 = (1.0f / fConst5);

	clear_state_f();
}

inline void TiltTone::run(uint32_t count, float *input0, float *output0)
{
    fslider0 = (*fslider0_);
    fslider1 = (*fslider1_);
    fslider2 = (*fslider2_);

	float 	fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * fslider0)));
	float 	fSlow1 = fslider1;
	float 	fSlow2 = (fConst19 * (powf(10,(0.05f * (0 - fSlow1))) - 1));
	float 	fSlow3 = (fConst12 * (powf(10,(0.05f * fSlow1)) - 1));
	float 	fSlow4 = (0.0010000000000000009f * powf(10,(0.05f * fslider2)));
	for (uint32_t i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
		fRec10[0] = ((fConst25 * (fRec9[1] + fRec9[2])) + (fConst24 * fRec10[1]));
		fRec9[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec10[0] + ((float)input0[i] * fRec0[0])) - 1.581656f)) - 191.42014814814814f);
		fRec8[0] = ((fConst27 * ((fConst26 * fRec9[1]) + (fConst1 * fRec9[0]))) + (fConst3 * fRec8[1]));
		fRec7[0] = ((fConst28 * (fRec8[0] + fRec8[1])) + (fConst21 * fRec7[1]));
		fRec6[0] = (fRec7[0] - (fConst19 * ((fConst18 * fRec6[2]) + (fConst16 * fRec6[1]))));
		float fTemp0 = (fRec8[0] + (fSlow2 * (fRec6[2] + (fRec6[0] + (2 * fRec6[1])))));
		fVec0[0] = fTemp0;
		fRec5[0] = ((fConst30 * ((fConst29 * fVec0[1]) + (fConst10 * fVec0[0]))) + (fConst14 * fRec5[1]));
		fRec4[0] = (fRec5[0] - (fConst12 * ((fConst11 * fRec4[2]) + (fConst9 * fRec4[1]))));
		fRec11[0] = (fSlow4 + (0.999f * fRec11[1]));
		float fTemp1 = (fRec11[0] * (fVec0[0] + (fSlow3 * (((fConst8 * fRec4[0]) + (fConst31 * fRec4[1])) + (fConst8 * fRec4[2])))));
		fVec1[0] = fTemp1;
		fRec3[0] = ((fConst32 * (fVec1[0] + fVec1[1])) + (fConst6 * fRec3[1]));
		fRec12[0] = ((fConst25 * (fRec2[1] + fRec2[2])) + (fConst24 * fRec12[1]));
		fRec2[0] = (Ftube(TUBE_TABLE_12AX7_68k, ((fRec12[0] + fRec3[0]) - 1.581656f)) - 191.42014814814814f);
		fRec1[0] = ((fConst27 * ((fConst26 * fRec2[1]) + (fConst1 * fRec2[0]))) + (fConst3 * fRec1[1]));
		output0[i] = (FAUSTFLOAT)(fRec1[0] / fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
		fRec12[1] = fRec12[0];
		fRec3[1] = fRec3[0];
		fVec1[1] = fVec1[0];
		fRec11[1] = fRec11[0];
		fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
		fVec0[1] = fVec0[0];
		fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
		fRec7[1] = fRec7[0];
		fRec8[1] = fRec8[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec10[1] = fRec10[0];
		fRec0[1] = fRec0[0];
	}

}

void TiltTone::run_static(uint32_t count, float *input0, float *output0, TiltTone *p)
{
	p->run(count, input0, output0);
}

void TiltTone::init_static(uint32_t samplingFreq, TiltTone *p)
{
	p->init(samplingFreq);
}

void TiltTone::connect_static(uint32_t port,void* data, TiltTone *p)
{
  p->connect(port, data);
}

void TiltTone::clear_state_static(TiltTone *p)
{
	p->clear_state_f();
}


