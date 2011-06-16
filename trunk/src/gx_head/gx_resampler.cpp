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
 *
 *
 *    This is the Guitarix resampler
 *    to use zita-resampler
 *
 * --------------------------------------------------------------------------
 */

#include "guitarix.h"

namespace gx_resample {

void SimpleResampler::setup(int sampleRate, unsigned int fact)
{
	assert(fact <= MAX_UPSAMPLE);
	m_fact = fact;
	const int qual = 16; // resulting in a total delay of 2*qual (0.7ms @44100)
	// upsampler
	r_up.setup(sampleRate, sampleRate*fact, 1, qual);
	// k == filtlen() == 2 * qual
	// pre-fill with k-1 zeros
	r_up.inp_count = r_up.filtlen() - 1;
	r_up.out_count = 1;
	r_up.inp_data = r_up.out_data = 0;
	r_up.process();
	// downsampler
	r_down.setup(sampleRate*fact, sampleRate, 1, qual);
	// k == filtlen() == 2 * qual * fact
	// pre-fill with k-1 zeros
	r_down.inp_count = r_down.filtlen() - 1;
	r_down.out_count = 1;
	r_down.inp_data = r_down.out_data = 0;
	r_down.process();
}

void SimpleResampler::up(int count, float *input, float *output)
{
	r_up.inp_count = count;
	r_up.inp_data = input;
	r_up.out_count = count * m_fact;
	r_up.out_data = output;
	r_up.process();
	assert(r_up.inp_count == 0);
	assert(r_up.out_count == 0);
}

void SimpleResampler::down(int count, float *input, float *output)
{
	r_down.inp_count = count * m_fact;
	r_down.inp_data = input;
	r_down.out_count = count+1; // +1 == trick to drain input
	r_down.out_data = output;
	r_down.process();
	assert(r_down.inp_count == 0);
	assert(r_down.out_count == 1);
}

SimpleResampler resampTube, resampDist;


float *BufferResampler::process(int fs_inp, int ilen, float *input, int fs_outp, int& olen)
{
	const int qual = 32;
	if (setup(fs_inp, fs_outp, 1, qual) != 0) {
		return 0;
	}
	// pre-fill with k/2-1 zeros
	int k = filtlen();
	inp_count = k/2-1;
	inp_data = 0;
	out_count = 1; // must be at least 1 to get going
	out_data = 0;
	if (Resampler::process() != 0) {
		return 0;
	}
	inp_count = ilen;
	int nout = out_count = (ilen * ratio_b() + ratio_a() - 1) / ratio_a();
	inp_data = input;
	float *p = out_data = new float[out_count];
	if (Resampler::process() != 0) {
		delete out_data;
		return 0;
	}
	inp_data = 0;
	inp_count = k/2;
	if (Resampler::process() != 0) {
		delete out_data;
		return 0;
	}
	assert(inp_count == 0);
	assert(out_count <= 1);
	olen = nout - out_count;
	return p;
}

bool StreamingResampler::setup(int srcRate, int dstRate, int nchan)
{
	const int qual = 32;
	if (Resampler::setup(srcRate, dstRate, nchan, qual) != 0) {
		return false;
	}
	inp_count = filtlen()/2-1;
	inp_data = 0;
	out_count = 1; // must be at least 1 to get going
	out_data = 0;
	if (Resampler::process() != 0) {
		return false;
	}
	assert(inp_count == 0);
	assert(out_count == 1);
	return true;
}

int StreamingResampler::process(int count, float *input, float *output)
{
	inp_count = count;
	int olen = out_count = get_max_out_size(count);
	inp_data = input;
	out_data = output;
	if (Resampler::process() != 0) {
		return 0;
	}
	assert(inp_count == 0);
	return olen - out_count;
}

int StreamingResampler::flush(float *output)
{
	// maximum data written to output:
	// srcRate > dstRate:  ~ 2 * qual
	// srcRate < dstRate:  ~ 2 * qual * dstRate/srcRate
	inp_data = 0;
	inp_count = filtlen()/2;
	out_data = output;
	int olen = out_count = get_max_out_size(inp_count);
	if (Resampler::process() != 0) {
		return 0;
	}
	assert(inp_count == 0);
	return olen - out_count;
}

} // namespace gx_engine
