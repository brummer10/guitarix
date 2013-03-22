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

#ifndef SRC_HEADERS_GX_REDEYE_H_
#define SRC_HEADERS_GX_REDEYE_H_

#include "valve.h"

// plugin class
class GxRedeyeMono
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
	FAUSTFLOAT 	fcheckbox0;
	FAUSTFLOAT 	*fcheckbox0_;
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
	float 	fConst26;
	float 	fConst27;
	float 	fConst28;
	float 	fConst29;
	float 	fConst30;
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	float 	fRec13[2];
	float 	fConst31;
	float 	fConst32;
	float 	fConst33;
	float 	fConst34;
	float 	fRec16[2];
	float 	fRec15[3];
	float 	fConst35;
	float 	fConst36;
	float 	fRec14[2];
	float 	fVec0[2];
	float 	fConst37;
	float 	fRec12[2];
	float 	fRec11[3];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	float 	fRec10[3];
	float 	fConst38;
	float 	fConst39;
	float 	fConst40;
	float 	fVec1[2];
	float 	fConst41;
	float 	fConst42;
	float 	fRec9[2];
	float 	fRec8[3];
	float 	fConst43;
	float 	fVec2[2];
	float 	fConst44;
	float 	fRec7[2];
	float 	fConst45;
	float 	fConst46;
	float 	fConst47;
	float 	fConst48;
	float 	fRec17[2];
	float 	fRec6[3];
	float 	fRec5[2];
	float 	fConst49;
	float 	fConst50;
	float 	fConst51;
	float 	fConst52;
	float 	fRec18[2];
	float 	fRec4[3];
	float 	fRec3[3];
	float 	fRec2[2];
	float 	fRec1[2];
 void        clear_state_f();
  void        init(uint32_t samplingFreq);
  void        connect(uint32_t port,void* data);

public:
  void        run_chump(uint32_t n_samples,float* input, float* output);
  void        run_chump2(uint32_t n_samples,float* input, float* output);
  static void init_static(uint32_t samplingFreq, GxRedeyeMono *p);
  static void connect_static(uint32_t port,void* data, GxRedeyeMono *p);
  //static void run_static(uint32_t n_samples, float* input, float* output, GxRedeyeMono *p);
  GxRedeyeMono() {};
  ~GxRedeyeMono() {};
};




#endif  //SRC_HEADERS_GX_REDEYE_H_
