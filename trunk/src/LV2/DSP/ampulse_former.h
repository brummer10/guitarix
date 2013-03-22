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
#include <stdint.h>
// level 1 - 10 
class Ampf
{
public:
  inline void  compute(int32_t count, float *input0, float *output0, float value) {
    double 	fSlow0 = value*0.5;
	double 	fSlow1 = (fSlow0 * pow(10,(0 - (0.1 * fSlow0))));
	for (int i=0; i<count; i++) {
		output0[i] = fSlow1 * input0[i];
	}
  };
  Ampf() {};
  ~Ampf() {};
};

