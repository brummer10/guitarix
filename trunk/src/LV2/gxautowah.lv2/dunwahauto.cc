/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose, Steve Poskitt
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

class dunwahauto {
private:
	uint32_t fSamplingFreq;
	int32_t 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fRec2[2];
	double 	fConst3;
	double 	fRec1[2];
	double 	fConst4;
	double 	fConst5;
	double 	fRec3[2];
	double 	fConst6;
	double 	fRec4[2];
	double 	fRec0[4];
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
public:
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void run(uint32_t count, float *input0, float *output0);
	dunwahauto();
	~dunwahauto();
};

dunwahauto::dunwahauto() {
}

dunwahauto::~dunwahauto() {
}

inline void dunwahauto::clear_state_f()
{
	for (int32_t i=0; i<2; i++) fRec2[i] = 0;
	for (int32_t i=0; i<2; i++) fRec1[i] = 0;
	for (int32_t i=0; i<2; i++) fRec3[i] = 0;
	for (int32_t i=0; i<2; i++) fRec4[i] = 0;
	for (int32_t i=0; i<4; i++) fRec0[i] = 0;
}

inline void dunwahauto::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = exp((0 - (1e+01 / iConst0)));
	fConst2 = (1.0 - fConst1);
	fConst3 = (0.007000000000000006 * ((iConst0 * (1.73888e-06 - (8.38823e-12 * iConst0))) - 0.193457));
	fConst4 = (0.5 / iConst0);
	fConst5 = (1.0 / iConst0);
	fConst6 = exp((0 - (1236.9027460477864 / iConst0)));
	fConst7 = (1.77528e-06 - (8.52216e-12 * iConst0));
	fConst8 = (0.879905 + (iConst0 * fConst7));
	fConst9 = (1.54419e-05 - (6.43963e-11 * iConst0));
	fConst10 = ((iConst0 * fConst9) - 0.386688);
	fConst11 = (fConst10 * (0 - (1.00038 * fConst8)));
	fConst12 = ((fConst10 * fConst8) + (1.00038 * (fConst10 + fConst8)));
	fConst13 = (0 - ((iConst0 * (fConst9 + fConst7)) + 1.4935970000000003));
	clear_state_f();
}

inline void dunwahauto::run(uint32_t count, float *input0, float *output0)
{
	for (uint32_t i=0; i<count; i++) {
		double fTemp0 = min(1.0,fabs((double)input0[i]));
		fRec2[0] = ((fConst2 * fTemp0) + (fConst1 * max(fTemp0, fRec2[1])));
		fRec1[0] = ((fConst3 * (0 - ((1.0 / ((fRec2[0] * (0.270546 + (fRec2[0] * ((fRec2[0] * (3.64419 + (fRec2[0] * ((2.85511 * fRec2[0]) - 5.20364)))) - 0.86331)))) - 0.814203)) + 0.933975))) + (0.993 * fRec1[1]));
		double fTemp1 = (1973.48 - (1000 / ((fRec2[0] * (1.9841 + (fRec2[0] * (5.76598 + (fRec2[0] * ((fRec2[0] * (49.9836 + (fRec2[0] * ((12.499 * fRec2[0]) - 40.3658)))) - 28.3434)))))) - 1.6086)));
		double fTemp2 = (1 - (fConst4 * (fTemp1 / (21.9737 + (fRec2[0] * ((fRec2[0] * (42.2734 + (fRec2[0] * ((fRec2[0] * (115.375 - (52.3051 * fRec2[0]))) - 99.7712)))) - 24.555))))));
		fRec3[0] = ((0.007000000000000006 * (cos((fConst5 * fTemp1)) * (0 - (2.0 * fTemp2)))) + (0.993 * fRec3[1]));
		fRec4[0] = ((0.007000000000000006 * faustpower<2>(fTemp2)) + (0.993 * fRec4[1]));
		fRec0[0] = (0 - (((fRec0[1] * (fRec3[0] - fConst6)) + ((fConst6 * ((0 - fRec4[0]) * fRec0[3])) + (fRec0[2] * (fRec4[0] - (fConst6 * fRec3[0]))))) - ((double)input0[i] * fRec1[0])));
		output0[i] = (float)((fConst13 * fRec0[1]) + ((fConst12 * fRec0[2]) + (fRec0[0] + (fConst11 * fRec0[3]))));
		// post processing
		for (int32_t i=3; i>0; i--) fRec0[i] = fRec0[i-1];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
	}
}

//////////////////////////////////////////////////////////////////////

class dunwah {
private:
	uint32_t fSamplingFreq;
	float 	*fslider0_;
	float 	fslider0;
	int32_t 	iConst0;
	double 	fConst1;
	double 	fRec1[2];
	double 	fConst2;
	double 	fConst3;
	double 	fRec2[2];
	double 	fConst4;
	double 	fRec3[2];
	double 	fRec0[4];
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
public:
    void clear_state_fd();
	void init_d(uint32_t samplingFreq);
	void run_d(uint32_t count, float *input0, float *output0);
    void connect_d(uint32_t port,void* data);
	dunwah();
	~dunwah();
};

dunwah::dunwah() {
}

dunwah::~dunwah() {
}

inline void dunwah::clear_state_fd()
{
	for (int32_t i=0; i<2; i++) fRec1[i] = 0;
	for (int32_t i=0; i<2; i++) fRec2[i] = 0;
	for (int32_t i=0; i<2; i++) fRec3[i] = 0;
	for (int32_t i=0; i<4; i++) fRec0[i] = 0;
}

void dunwah::connect_d(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case WAH:
      fslider0_ = (float*)data;
      break;
    default:
      break;
    }
}

inline void dunwah::init_d(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (0.007000000000000006 * ((iConst0 * (1.73888e-06 - (8.38823e-12 * iConst0))) - 0.193457));
	fConst2 = (0.5 / iConst0);
	fConst3 = (1.0 / iConst0);
	fConst4 = exp((0 - (1236.9027460477864 / iConst0)));
	fConst5 = (1.77528e-06 - (8.52216e-12 * iConst0));
	fConst6 = (0.879905 + (iConst0 * fConst5));
	fConst7 = (1.54419e-05 - (6.43963e-11 * iConst0));
	fConst8 = ((iConst0 * fConst7) - 0.386688);
	fConst9 = (fConst8 * (0 - (1.00038 * fConst6)));
	fConst10 = ((fConst8 * fConst6) + (1.00038 * (fConst8 + fConst6)));
	fConst11 = (0 - ((iConst0 * (fConst7 + fConst5)) + 1.4935970000000003));
	clear_state_fd();
}

inline void dunwah::run_d(uint32_t count, float *input0, float *output0)
{
    fslider0 = (*fslider0_);
	double 	fSlow0 = fslider0;
	double 	fSlow1 = (fConst1 * (0 - ((1.0 / ((fSlow0 * (0.270546 + (fSlow0 * ((fSlow0 * (3.64419 + (fSlow0 * ((2.85511 * fSlow0) - 5.20364)))) - 0.86331)))) - 0.814203)) + 0.933975)));
	double 	fSlow2 = (1973.48 - (1000 / ((fSlow0 * (1.9841 + (fSlow0 * (5.76598 + (fSlow0 * ((fSlow0 * (49.9836 + (fSlow0 * ((12.499 * fSlow0) - 40.3658)))) - 28.3434)))))) - 1.6086)));
	double 	fSlow3 = (1 - (fConst2 * (fSlow2 / (21.9737 + (fSlow0 * ((fSlow0 * (42.2734 + (fSlow0 * ((fSlow0 * (115.375 - (52.3051 * fSlow0))) - 99.7712)))) - 24.555))))));
	double 	fSlow4 = (0.007000000000000006 * (cos((fConst3 * fSlow2)) * (0 - (2.0 * fSlow3))));
	double 	fSlow5 = (0.007000000000000006 * faustpower<2>(fSlow3));
	for (uint32_t i=0; i<count; i++) {
		fRec1[0] = (fSlow1 + (0.993 * fRec1[1]));
		fRec2[0] = (fSlow4 + (0.993 * fRec2[1]));
		fRec3[0] = (fSlow5 + (0.993 * fRec3[1]));
		fRec0[0] = (0 - (((fRec0[1] * (fRec2[0] - fConst4)) + ((fConst4 * ((0 - fRec3[0]) * fRec0[3])) + (fRec0[2] * (fRec3[0] - (fConst4 * fRec2[0]))))) - ((double)input0[i] * fRec1[0])));
		output0[i] = (float)((fConst11 * fRec0[1]) + ((fConst10 * fRec0[2]) + (fRec0[0] + (fConst9 * fRec0[3]))));
		// post processing
		for (int32_t i=3; i>0; i--) fRec0[i] = fRec0[i-1];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
	}
}

class crybaby: public dunwahauto, public dunwah
{
  public:
    crybaby(){};
    ~crybaby(){};
};
