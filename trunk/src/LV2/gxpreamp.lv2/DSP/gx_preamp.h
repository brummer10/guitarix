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

#pragma once

#ifndef SRC_HEADERS_GX_PREAMP_H_
#define SRC_HEADERS_GX_PREAMP_H_

#include "valve.h"

// plugin class
class GxPreAmpMono
{
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
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	float 	fRec7[2];
	float 	fConst7;
	float 	fConst8;
	float 	fConst9;
	float 	fConst10;
	float 	fConst11;
	float 	fConst12;
	float 	fConst13;
	float 	fConst14;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fRec10[2];
	float 	fConst15;
	float 	fConst16;
	float 	fConst17;
	float 	fConst18;
	float 	fConst19;
	float 	fConst20;
	float 	fConst21;
	float 	fConst22;
	float 	fRec12[2];
	float 	fRec11[3];
	float 	fVec0[2];
	float 	fConst23;
	float 	fConst24;
	float 	fRec9[2];
	float 	fRec8[3];
	float 	fConst25;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	float 	fRec13[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	float 	fRec14[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	float 	fRec15[2];
	float 	fConst26;
	float 	fConst27;
	float 	fConst28;
	float 	fConst29;
	float 	fRec16[2];
	float 	fRec6[3];
	float 	fConst30;
	float 	fConst31;
	float 	fRec5[2];
	float 	fConst32;
	float 	fConst33;
	float 	fConst34;
	float 	fConst35;
	float 	fRec17[2];
	float 	fRec4[3];
	float 	fRec3[2];
	float 	fRec2[3];
	float 	fConst36;
	float 	fRec1[2];
  void        clear_state_f();
  void        init(uint32_t samplingFreq);
  void        connect(uint32_t port,void* data);

public:
  void        run(uint32_t n_samples,float* input0, float* output0);
  static void init_static(uint32_t samplingFreq, GxPreAmpMono *p);
  static void connect_static(uint32_t port,void* data, GxPreAmpMono *p);
  //static void run_static(uint32_t n_samples, float* input, float* output, GxPreAmpMono *p);
  GxPreAmpMono() {};
  ~GxPreAmpMono() {};
};


class GxPreAmpStereo
{
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
	float 	fRec10[2];
	float 	fRec9[3];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	float 	fRec11[2];
	float 	fVec0[2];
	float 	fConst23;
	float 	fConst24;
	float 	fRec8[2];
	float 	fRec7[3];
	float 	fConst25;
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fRec12[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	float 	fRec13[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT	*fslider4_;
	float 	fRec14[2];
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT	*fslider5_;
	float 	fRec15[2];
	float 	fConst26;
	float 	fConst27;
	float 	fConst28;
	float 	fConst29;
	float 	fRec16[2];
	float 	fRec6[3];
	float 	fConst30;
	float 	fConst31;
	float 	fRec5[2];
	float 	fConst32;
	float 	fConst33;
	float 	fConst34;
	float 	fConst35;
	float 	fRec17[2];
	float 	fRec4[3];
	float 	fRec3[2];
	float 	fRec2[3];
	float 	fConst36;
	float 	fRec1[2];
	float 	fRec27[2];
	float 	fRec26[3];
	float 	fVec1[2];
	float 	fRec25[2];
	float 	fRec24[3];
	float 	fRec28[2];
	float 	fRec23[3];
	float 	fRec22[2];
	float 	fRec29[2];
	float 	fRec21[3];
	float 	fRec20[2];
	float 	fRec19[3];
	float 	fRec18[2];
  void        clear_state_f();
  void        init(uint32_t samplingFreq);
  void        connect(uint32_t port,void* data);


public:
  void        run(uint32_t n_samples,float* input,float* input1, float* output, float* output1);
  static void init_static(uint32_t samplingFreq, GxPreAmpStereo *p);
  static void connect_static(uint32_t port,void* data, GxPreAmpStereo *p);
  //static void run_static(uint32_t n_samples, float* input,float* input1, float* output, float* output1, GxPreAmpStereo *p);
  GxPreAmpStereo() {};
  ~GxPreAmpStereo() {};
};



#endif  //SRC_HEADERS_GX_PREAMP_H_
