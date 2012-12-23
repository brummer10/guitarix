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


class Impf
{
private:
  int32_t             fSamplingFreq;
  FAUSTFLOAT      fslider0;
  FAUSTFLOAT      *fslider0_;
  void            init(uint32_t samplingFreq);
  void            connect(uint32_t port,void* data);

public:
  void            compute(int32_t count, float *input0, float *output0);
  static void     connect_static(uint32_t port,void* data, Impf *p);
  static void     init_static(uint32_t samplingFreq, Impf *p);
  Impf();
  ~Impf();
};

