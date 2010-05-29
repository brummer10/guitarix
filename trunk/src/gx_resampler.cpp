/*
 * Copyright (C) 2009-2010 Hermann Meyer, James Warden, Andreas Degert
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 *
 *
 *    This is the Guitarix resampler
 *    to use zita-resampler
 *
 * --------------------------------------------------------------------------
 */

#include <assert.h>
#include <cstring>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include <array>
#include <zita-convolver.h>
#include <fftw3.h>
#include <zita-resampler.h>

#include <cassert>
#include <sigc++/sigc++.h>
#include <semaphore.h>

#include <cmath>
#include <gtk/gtk.h>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <sndfile.h>

using namespace std;

#include "guitarix.h"

namespace gx_resample {


void SimpleResampler::setup(int sampleRate, unsigned int fact)
{
	assert(fact <= MAX_UPSAMPLE);
	const int qual = 16;
	r_up.setup(sampleRate, sampleRate*fact, 1, qual);
	r_up.inp_count = (2*qual);
	r_up.out_count = (2*qual) * fact;
	r_up.inp_data = r_up.out_data = 0;
	r_up.process();
	assert(r_up.inp_count == 0);
	assert(r_up.out_count != (2*qual) * fact);
	r_down.setup(sampleRate*fact, sampleRate, 1, qual);
	r_down.inp_count = (2*qual) * fact;
	r_down.out_count = (2*qual);
	r_down.inp_data = r_down.out_data = 0;
	r_down.process();
	m_fact = fact;
	assert(r_down.inp_count == 0);
	assert(r_down.out_count != (2*qual));
}

void SimpleResampler::up(int count, float *input, float *output)
{
	r_up.inp_count = count;
	r_up.inp_data = input;
	r_up.out_count = count * m_fact;
	r_up.out_data = output;
	r_up.process();
	assert(r_up.inp_count == 0);
	//assert(r_up.out_count == 0);
	//if (r_up.out_count != 0) cout << "# " << r_up.out_count << endl;
}

void SimpleResampler::down(int count, float *input, float *output)
{
	r_down.inp_count = count * m_fact;
	r_down.inp_data = input;
	r_down.out_count = count;
	r_down.out_data = output;
	r_down.process();
	assert(r_down.inp_count == 0);
	assert(r_down.out_count == 0);
}

SimpleResampler resampTube, resampDist;


float *BufferResampler::process(int fs_inp, int ilen, float *input, int fs_outp, int& olen)
{
	if (setup(fs_inp, fs_outp, 1, 32) != 0) {
		return 0;
	}
	int k = filtlen();
	inp_count = k/2-1;
	inp_data = 0;
	out_count = 1; // must be at least 1 to get going
	out_data = 0;
	if (Resampler::process() != 0) {
		return 0;
	}
	assert(inp_count == 0);
	assert(out_count == 1);
	inp_count = ilen;
	out_count = olen = (ilen * ratio_b() + ratio_a() - 1) / ratio_a();
	inp_data = input;
	float *p = out_data = new float[out_count];
	if (Resampler::process() != 0) {
		delete out_data;
		return 0;
	}
	assert(inp_count == 0);
	inp_data = 0;
	inp_count = k/2;
	if (Resampler::process() != 0) {
		delete out_data;
		return 0;
	}
	assert(inp_count == 0);
	assert(out_count == 0);
	return p;
}

} // namespace gx_engine

