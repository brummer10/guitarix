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

#ifndef SRC_HEADERS_GX_TONESTACK_H_
#define SRC_HEADERS_GX_TONESTACK_H_

class TonestackMono
{
private:
  int32_t         fSamplingFreq;
  float       fslider0;
  float       *fslider0_;
  float       fslider1;
  float       *fslider1_;
  double      fConst0;
  double      fConst1;
  double      fConst2;
  double      fRec0[4];
  float       fslider2;
  float       *fslider2_;
  void        clear_state_f();
  void        init(uint32_t samplingFreq);
  void        connect(uint32_t port,void* data);


public:
  void        run_bassman(uint32_t n_samples, float *output);
  void        run(uint32_t n_samples, float *output);
  void        run_soldano(uint32_t n_samples, float *output);
  void        run_ampeg(uint32_t n_samples, float *output);
  static void init_static(uint32_t samplingFreq, TonestackMono *p);
  static void connect_static(uint32_t port,void* data, TonestackMono *p);
  static void run_static(uint32_t n_samples, TonestackMono*, float *output);

  TonestackMono() {};
  ~TonestackMono() {};
};

// define run pointer typs
typedef void (TonestackMono::*run_tonestack_mono)
(uint32_t count, float *output);

run_tonestack_mono    _t_ptr;


class TonestackStereo
{
private:
  int32_t fSamplingFreq;
  FAUSTFLOAT 	fslider0;
  FAUSTFLOAT	*fslider0_;
  FAUSTFLOAT 	fslider1;
  FAUSTFLOAT	*fslider1_;
  double 	fConst0;
  double 	fConst1;
  double 	fConst2;
  double 	fRec0[4];
  double 	fRec1[4];
  FAUSTFLOAT 	fslider2;
  FAUSTFLOAT	*fslider2_;
  void        clear_state_f();
  void        init(uint32_t samplingFreq);
  void        connect(uint32_t port,void* data);
public:

  void        run_bassman(uint32_t n_samples, float *output, float *output1);
  void        run(uint32_t n_samples, float *output, float *output1);
  void        run_soldano(uint32_t n_samples, float *output, float *output1);
  void        run_ampeg(uint32_t n_samples, float *output, float *output1);
  static void init_static(uint32_t samplingFreq, TonestackStereo *p);
  static void connect_static(uint32_t port,void* data, TonestackStereo *p);
  static void run_static(uint32_t n_samples, TonestackStereo*, float *output, float *output1);
  TonestackStereo() {};
  ~TonestackStereo() {};
};

// define run pointer typs
typedef void (TonestackStereo::*run_tonestack_stereo)
(uint32_t count, float *output, float *output1);

run_tonestack_stereo    _ts_ptr;


#endif  //SRC_HEADERS_GX_TONESTACK_H_

