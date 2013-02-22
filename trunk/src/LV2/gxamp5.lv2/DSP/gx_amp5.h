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

#ifndef SRC_HEADERS_GX_AMP5_H_
#define SRC_HEADERS_GX_AMP5_H_

#include "valve.h"

// plugin class
class GxAmp5Mono
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
	double 	fRec2[2];
	float 	fslider0;
	float	*fslider0_;
	double 	fRec3[2];
	float 	fslider1;
	float	*fslider1_;
	double 	fRec5[2];
	float 	fslider2;
	float	*fslider2_;
	double 	fRec13[2];
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fRec14[2];
	double 	fRec12[3];
	double 	fConst12;
	double 	fConst13;
	double 	fRec11[2];
	double 	fConst14;
	double 	fRec10[2];
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fRec15[2];
	double 	fRec9[3];
	double 	fRec8[2];
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fRec16[2];
	double 	fRec7[3];
	double 	fRec6[2];
	float 	fslider3;
	float	*fslider3_;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fRec24[3];
	double 	fVec0[2];
	double 	fConst53;
	double 	fRec23[2];
	double 	fConst54;
	double 	fRec22[2];
	double 	fRec21[3];
	double 	fVec1[2];
	double 	fConst55;
	double 	fConst56;
	double 	fRec20[2];
	double 	fRec19[3];
	double 	fConst57;
	double 	fRec18[3];
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fRec28[2];
	double 	fRec27[3];
	double 	fVec2[2];
	double 	fConst62;
	double 	fConst63;
	double 	fRec26[2];
	double 	fRec25[3];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
	double 	fRec32[2];
	double 	fRec31[3];
	double 	fConst68;
	double 	fRec30[3];
	double 	fRec29[3];
	double 	fRec34[2];
	double 	fRec33[3];
	double 	fVec3[2];
	double 	fRec17[2];
	double 	fVec4[2];
	double 	fRec4[2];
	double 	fRec1[3];
	double 	fRec0[2];
	double 	fRec37[2];
	double 	fRec36[3];
	double 	fRec35[2];
	void        clear_state_f();
  	void        init(uint32_t samplingFreq);
  void        connect(uint32_t port,void* data
);
// SHP : this is a compromise as init method above should be different for each amp!
// Can either have a switch in the init or have separate amps code for each type
// in which case run_12ax7 is only one needed here.
// same for the stereo version 
public:
  void        run_12ax76v6(uint32_t n_samples, float* input, float* output);
  static void init_static(uint32_t samplingFreq, GxAmp5Mono *p);
  static void connect_static(uint32_t port,void* data, GxAmp5Mono *p);
  //static void run_static(uint32_t n_samples, float* input, float* output, GxAmp5Mono *p);
  GxAmp5Mono() {};
  ~GxAmp5Mono() {};
};


class GxAmp5Stereo
{
private:
  void        clear_state_f();
  void        init(uint32_t samplingFreq);
  void        connect(uint32_t port,void* data);


public:
  void        run_12ax76v6(uint32_t n_samples, float* input,float* input1, float* output, float* output1);
  static void init_static(uint32_t samplingFreq, GxAmp5Stereo *p);
  static void connect_static(uint32_t port,void* data, GxAmp5Stereo *p);
  //static void run_static(uint32_t n_samples, float* input,float* input1, float* output, float* output1, GxAmp5Stereo *p);
  GxAmp5Stereo() {};
  ~GxAmp5Stereo() {};
};



#endif  //SRC_HEADERS_GX_AMP5_H_
