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

class Tonestack
{
private:
  int         fSamplingFreq;
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
  void        init(unsigned int samplingFreq);
  void        connect(uint32_t port,void* data);
  void        run(uint32_t n_samples, float *output);

public:
  static void init_static(unsigned int samplingFreq, Tonestack*);
  static void connect_static(uint32_t port,void* data, Tonestack *p);
  static void run_static(uint32_t n_samples, Tonestack*, float *output);

  Tonestack() {};
  ~Tonestack() {};
};

#endif  //SRC_HEADERS_GX_TONESTACK_H_

