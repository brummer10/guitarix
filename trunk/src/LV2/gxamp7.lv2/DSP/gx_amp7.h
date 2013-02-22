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

#ifndef SRC_HEADERS_GX_AMP7_H_
#define SRC_HEADERS_GX_AMP7_H_

#include "valve.h"

// plugin class
class GxAmp7Mono
{
private:
	int fSamplingFreq;
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fRec5[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec8[2];
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fVec0[2];
	double 	fConst29;
	double 	fRec21[2];
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fRec18[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fRec22[2];
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fRec23[2];
	double 	fRec17[3];
	double 	fConst34;
	double 	fConst35;
	double 	fRec16[2];
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fRec24[2];
	double 	fRec15[2];
	double 	fConst40;
	double 	fRec14[2];
	double 	fRec27[2];
	double 	fRec13[3];
	double 	fRec12[2];
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fRec30[2];
	double 	fRec29[3];
	double 	fRec28[2];
	double 	fRec11[2];
	double 	fRec31[2];
	double 	fRec10[3];
	double 	fRec9[2];
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec34[2];
	int 	IOTA;
	double 	fVec1[32768];
	int 	iConst45;
	double 	fRec33[2];
	double 	fConst46;
	double 	fRec32[2];
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fRec42[3];
	double 	fVec2[2];
	double 	fConst77;
	double 	fRec41[2];
	double 	fConst78;
	double 	fRec40[2];
	double 	fRec39[3];
	double 	fVec3[2];
	double 	fConst79;
	double 	fConst80;
	double 	fRec38[2];
	double 	fRec37[3];
	double 	fConst81;
	double 	fRec36[3];
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fRec46[2];
	double 	fRec45[3];
	double 	fVec4[2];
	double 	fConst86;
	double 	fConst87;
	double 	fRec44[2];
	double 	fRec43[3];
	double 	fConst88;
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fRec50[2];
	double 	fRec49[3];
	double 	fConst92;
	double 	fRec48[3];
	double 	fRec47[3];
	double 	fRec52[2];
	double 	fRec51[3];
	double 	fVec5[2];
	double 	fRec35[2];
	double 	fVec6[2];
	double 	fRec7[2];
	double 	fRec4[3];
	double 	fRec3[2];
	double 	fRec55[2];
	double 	fRec54[3];
	double 	fRec53[2];
	double 	fVec7[3];
	double 	fConst93;
	double 	fConst94;
	double 	fRec2[3];
	double 	fConst95;
	double 	fConst96;
	double 	fRec1[3];
	double 	fConst97;
	double 	fConst98;
	double 	fRec0[3];
	void        clear_state_f();
  	void        init(uint32_t samplingFreq);
  void        connect(uint32_t port,void* data
);
// SHP : this is a compromise as init method above should be different for each amp!
// Can either have a switch in the init or have separate amps code for each type
// in which case run_12ax7 is only one needed here.
// same for the stereo version 
public:
  void        run_12ax7pp6v6(uint32_t n_samples, float* input, float* output);
  static void init_static(uint32_t samplingFreq, GxAmp7Mono *p);
  static void connect_static(uint32_t port,void* data, GxAmp7Mono *p);
  //static void run_static(uint32_t n_samples, float* input, float* output, GxAmp7Mono *p);
  GxAmp7Mono() {};
  ~GxAmp7Mono() {};
};


class GxAmp7Stereo
{
private:
  void        clear_state_f();
  void        init(uint32_t samplingFreq);
  void        connect(uint32_t port,void* data);


public:
  void        run_12ax7pp6v6(uint32_t n_samples, float* input,float* input1, float* output, float* output1);
  static void init_static(uint32_t samplingFreq, GxAmp7Stereo *p);
  static void connect_static(uint32_t port,void* data, GxAmp7Stereo *p);
  //static void run_static(uint32_t n_samples, float* input,float* input1, float* output, float* output1, GxAmp7Stereo *p);
  GxAmp7Stereo() {};
  ~GxAmp7Stereo() {};
};



#endif  //SRC_HEADERS_GX_AMP7_H_
