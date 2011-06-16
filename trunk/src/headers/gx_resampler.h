/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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

/* ------- This is the guitarix resampler, to use zita-resampler ------- */

#pragma once

#include <zita-resampler.h>

namespace gx_resample
{

#define MAX_UPSAMPLE 8

class SimpleResampler
{
private:
	Resampler r_up, r_down;
	int m_fact;
public:
	void setup(int sampleRate, unsigned int fact);
	void up(int count, float *input, float *output);
	void down(int count, float *input, float *output);
};

extern SimpleResampler resampTube, resampDist;

class BufferResampler: Resampler
{
public:
	float *process(int fs_inp, int ilen, float *input, int fs_outp, int& olen);
};

class StreamingResampler: Resampler
{
public:
	bool setup(int srcRate, int dstRate, int nchan);
	int get_max_out_size(int i_size) { return (i_size * ratio_b()) / ratio_a() + 1; }
	int process(int count, float *input, float *output);
	int flush(float *output); // check source for max. output size
};

}
