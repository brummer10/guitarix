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


class HighBooster {
private:
	uint32_t fSamplingFreq;
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fVec0[2];
	double 	fConst3;
	double 	fConst4;
	double 	fRec0[2];
    float 	*fslider0_;
	float 	fslider0;
	void clear_state_f();
	void init(uint32_t samplingFreq);
	void run(uint32_t count, float *input0, float *output0);
	void connect(uint32_t port,void* data);
public:
    
    static void init_static(uint32_t samplingFreq, HighBooster*);
	static void run_static(uint32_t count, float *input0, float *output0, HighBooster*);
    static void connect_static(uint32_t port,void* data, HighBooster *p);
	static void clear_state_static(HighBooster*);
	HighBooster();
	~HighBooster();
};



HighBooster::HighBooster() {
}

HighBooster::~HighBooster() {
}

void HighBooster::connect(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case T_LEVEL:
      fslider0_ = (float*)data;
      break;
    default:
      break;
    }
}

inline void HighBooster::clear_state_f()
{
	for (int32_t i=0; i<2; i++) fVec0[i] = 0;
	for (int32_t i=0; i<2; i++) fRec0[i] = 0;
}

inline void HighBooster::init(uint32_t samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (1.0 / tan((4712.38898038469 / min(192000, max(1, fSamplingFreq)))));
	fConst1 = (1 + fConst0);
	fConst2 = (0 - ((1 - fConst0) / fConst1));
	fConst3 = (0 - fConst0);
	fConst4 = (1.0 / fConst1);
	clear_state_f();
}


inline void HighBooster::run(uint32_t count, float *input0, float *output0)
{
	fslider0 = (*fslider0_);
	double 	fSlow0 = (pow(10,(0.05 * fslider0)) - 1);
	for (uint32_t i=0; i<count; i++) {
		double fTemp0 = (double)input0[i];
		fVec0[0] = fTemp0;
		fRec0[0] = ((fConst4 * ((fConst3 * fVec0[1]) + (fConst0 * fVec0[0]))) + (fConst2 * fRec0[1]));
		output0[i] = (float)(fVec0[0] + (fSlow0 * fRec0[0]));
		// post processing
		fRec0[1] = fRec0[0];
		fVec0[1] = fVec0[0];
	}
}

void HighBooster::run_static(uint32_t count, float *input0, float *output0, HighBooster *p)
{
	p->run(count, input0, output0);
}

void HighBooster::init_static(uint32_t samplingFreq, HighBooster *p)
{
	p->init(samplingFreq);
}

void HighBooster::connect_static(uint32_t port,void* data, HighBooster *p)
{
  p->connect(port, data);
}

void HighBooster::clear_state_static(HighBooster *p)
{
	p->clear_state_f();
}
