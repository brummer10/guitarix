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

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#include "ts9nonlin.h"

class ts9sim {
private:
	uint32_t fSamplingFreq;
    float 	*fslider0_;
	float 	fslider0;
	double 	fRec0[2];
	float 	*fslider1_;
    float 	fslider1;
	int32_t 	iConst0;
	double 	fConst1;
	double 	fVec0[2];
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	float 	*fslider2_;
	float 	fslider2;
	double 	fConst5;
	double 	fConst6;
	double 	fRec2[2];
	double 	fVec1[2];
	double 	fRec1[2];
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void run(uint32_t count, float *input0, float *output0);
    void connect(uint32_t port,void* data);
public:
    static void init_static(uint32_t samplingFreq, ts9sim*);
	static void run_static(uint32_t count, float *input0, float *output0, ts9sim*);
	static void connect_static(uint32_t port, void* data, ts9sim*);
    static void clear_state_static(ts9sim*);
	ts9sim();
	~ts9sim();
};

ts9sim::ts9sim() {
}

ts9sim::~ts9sim() {
}

inline void ts9sim::clear_state_f()
{
	for (int32_t i=0; i<2; i++) fRec0[i] = 0;
	for (int32_t i=0; i<2; i++) fVec0[i] = 0;
	for (int32_t i=0; i<2; i++) fRec2[i] = 0;
	for (int32_t i=0; i<2; i++) fVec1[i] = 0;
	for (int32_t i=0; i<2; i++) fRec1[i] = 0;
}

inline void ts9sim::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = (3.141592653589793 / iConst0);
	fConst2 = (0.00044179999999999995 * iConst0);
	fConst3 = (1 + fConst2);
	fConst4 = (0 - ((1 - fConst2) / fConst3));
	fConst5 = (9.4e-08 * iConst0);
	fConst6 = (1.0 / fConst3);
	clear_state_f();
}

void ts9sim::connect(uint32_t port,void* data)
{
  switch ((EffectPortIndex)port)
    {
    case TS9_LEVEL:
      fslider0_ = (float*)data;
      break;
    case TS9_TONE:
      fslider1_ = (float*)data;
      break;
    case TS9_DRIVE:
      fslider2_ = (float*)data;
      break;
    default:
      break;
    }
}

inline void ts9sim::run(uint32_t count, float *input0, float *output0)
{
    fslider0 = (*fslider0_);
    fslider1 = (*fslider1_);
    fslider2 = (*fslider2_);
    
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * fslider0)));
	double 	fSlow1 = (1.0 / tan((fConst1 * fslider1)));
	double 	fSlow2 = (1 + fSlow1);
	double 	fSlow3 = (0 - ((1 - fSlow1) / fSlow2));
	double 	fSlow4 = (fConst5 * ((500000 * fslider2) + 55700));
	double 	fSlow5 = (1 + fSlow4);
	double 	fSlow6 = (1 - fSlow4);
	double 	fSlow7 = (1.0 / fSlow2);
	for (uint32_t i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec2[0] = ((fConst6 * ((fSlow6 * fVec0[1]) + (fSlow5 * fVec0[0]))) + (fConst4 * fRec2[1]));
		double fTemp1 = (fVec0[0] - ts9nonlin((fRec2[0] - fVec0[0])));
		fVec1[0] = fTemp1;
		fRec1[0] = ((fSlow7 * (fVec1[0] + fVec1[1])) + (fSlow3 * fRec1[1]));
		output0[i] = (float)(fRec1[0] * fRec0[0]);
		// post processing
		fRec1[1] = fRec1[0];
		fVec1[1] = fVec1[0];
		fRec2[1] = fRec2[0];
		fVec0[1] = fVec0[0];
		fRec0[1] = fRec0[0];
	}
}

void ts9sim::init_static(uint32_t samplingFreq, ts9sim *p)
{
	p->init(samplingFreq);
}

void ts9sim::run_static(uint32_t count, float *input0, float *output0, ts9sim *p)
{
	p->run(count, input0, output0);
}

void ts9sim::connect_static(uint32_t port,void* data, ts9sim *p)
{
  p->connect(port, data);
}

void ts9sim::clear_state_static(ts9sim *p)
{
	p->clear_state_f();
}
