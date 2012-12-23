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

#ifndef SRC_HEADERS_GX_AMP_H_
#define SRC_HEADERS_GX_AMP_H_

#include "valve.h"

// plugin class
class GxAmp
{
private:
  int32_t         fSamplingFreq;
  float       fslider0;
  float       *fslider0_;
  double      fRec0[2];
  int32_t         iConst0;
  double      fConst1;
  double      fConst2;
  double      fConst3;
  double      fConst4;
  double      fConst5;
  double      fConst6;
  float       fslider1;
  float       *fslider1_;
  double      fRec7[2];
  double      fConst7;
  double      fConst8;
  double      fConst9;
  double      fConst10;
  double      fConst11;
  double      fConst12;
  double      fConst13;
  double      fConst14;
  double      fConst15;
  double      fConst16;
  double      fConst17;
  double      fConst18;
  double      fConst19;
  double      fConst20;
  double      fConst21;
  double      fConst22;
  double      fConst23;
  double      fConst24;
  double      fConst25;
  double      fConst26;
  double      fConst27;
  double      fConst28;
  double      fConst29;
  double      fConst30;
  double      fConst31;
  double      fConst32;
  double      fConst33;
  double      fConst34;
  double      fConst35;
  double      fConst36;
  float       fslider2;
  float       *fslider2_;
  double      fRec18[2];
  double      fRec17[3];
  double      fVec0[2];
  double      fConst37;
  double      fConst38;
  double      fRec16[2];
  double      fConst39;
  double      fRec15[2];
  double      fRec14[3];
  double      fVec1[2];
  double      fConst40;
  double      fConst41;
  double      fRec13[2];
  double      fRec12[3];
  double      fConst42;
  double      fRec11[3];
  float       fslider3;
  float       *fslider3_;
  double      fConst43;
  double      fConst44;
  double      fConst45;
  double      fConst46;
  double      fRec22[2];
  double      fRec21[3];
  double      fVec2[2];
  double      fConst47;
  double      fConst48;
  double      fRec20[2];
  double      fRec19[3];
  double      fConst49;
  double      fConst50;
  double      fConst51;
  double      fConst52;
  double      fRec26[2];
  double      fRec25[3];
  double      fConst53;
  double      fRec24[3];
  double      fRec23[3];
  double      fRec28[2];
  double      fRec27[3];
  double      fVec3[2];
  double      fConst54;
  double      fRec10[2];
  double      fConst55;
  double      fConst56;
  double      fConst57;
  double      fConst58;
  double      fRec29[2];
  double      fRec9[3];
  double      fConst59;
  double      fRec8[2];
  double      fVec4[2];
  double      fRec6[2];
  double      fConst60;
  double      fConst61;
  double      fConst62;
  double      fConst63;
  double      fRec30[2];
  double      fRec5[3];
  double      fRec4[2];
  double      fVec5[2];
  double      fRec3[2];
  double      fConst64;
  double      fConst65;
  double      fConst66;
  double      fConst67;
  double      fRec31[2];
  double      fRec2[3];
  double      fRec1[2];
  //float*      input;
  //float*      output;
  void        clear_state_f();
  void        init(uint32_t samplingFreq);
  void        connect(uint32_t port,void* data);
  
public:
  void        run_6V6(uint32_t n_samples,float* input, float* output);
  void        run_6C16(uint32_t n_samples, float* input, float* output);
  void        run_12AT7(uint32_t n_samples, float* input, float* output);
  void        run_12ax7(uint32_t n_samples, float* input, float* output);
  void        run_6DJ8(uint32_t n_samples, float* input, float* output);
  static void init_static(uint32_t samplingFreq, GxAmp *p);
  static void connect_static(uint32_t port,void* data, GxAmp *p);
  static void run_static(uint32_t n_samples, float* input, float* output, GxAmp *p);
  GxAmp() {};
  ~GxAmp() {};
};
// define run pointer typs
typedef void (GxAmp::*run_this)
             (uint32_t count,float* input, float* output);

run_this    _a_ptr;

#endif  //SRC_HEADERS_GX_AMP_H_
