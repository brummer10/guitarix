/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 *	This is the guitarix engine definitions
 *
 *
 * --------------------------------------------------------------------------
 */

#include <cstring>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>

#include <array>
#include <zita-convolver.h>
#include <fftw3.h>
#include <zita-resampler.h>

#include <cassert>
#include <sigc++/sigc++.h>
#include <semaphore.h>

using namespace std;

#include <cmath>
#include <gtk/gtk.h>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <sndfile.h>

#include "guitarix.h"

using namespace gx_system;

namespace gx_engine
{
// static member
GxMidiState midistate = kMidiOff;
float midistat;
float ffuse;
float fskin;

/* --- forward definition of useful namespace functions --- */
void gx_engine_init( const string *optvar )
{
	//----- lock the buffer for the oscilloscope
	const int frag = (const int)gx_jack::jack_bs;

	get_frame  = new float[frag];
	get_frame1  = new float[frag];
	checkfreq  = new float[frag];
	oversample = new float[frag*2];
	result = new float[frag+46];

	(void)memset(get_frame,  0, frag*sizeof(float));
	(void)memset(get_frame1,  0, frag*sizeof(float));
	(void)memset(checkfreq,  0, frag*sizeof(float));
	(void)memset(oversample, 0, frag*2*sizeof(float));
	(void)memset(result, 0, (frag+46)*sizeof(float));

	/** disable fft need some fix for work prop **/
	/*
	  fftin = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * frag);
	  fftout = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * frag);
	  fftin1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * frag);
	  fftout1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * frag);
	  fftresult = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * frag);

	  p = fftw_plan_dft_1d(frag, fftin, fftout, FFTW_FORWARD, FFTW_ESTIMATE);
	  p1 = fftw_plan_dft_1d(frag, fftout, fftresult, FFTW_BACKWARD, FFTW_ESTIMATE);
	  pf = fftw_plan_dft_1d(frag, fftin1, fftout1, FFTW_FORWARD, FFTW_ESTIMATE);
	*/

	midi.init(gx_jack::jack_sr);
	faust_init(gx_jack::jack_sr);
	if( !optvar[LOAD_FILE].empty() )
		gx_preset::gx_recall_settings_file( optvar[LOAD_FILE] );
	else
		gx_preset::gx_recall_main_setting(NULL, NULL);

	initialized = true;
}

/* --- forward definition of useful namespace functions --- */
void gx_engine_reset()
{
	if (checkfreq)  delete[] checkfreq;
	if (get_frame)  delete[] get_frame;
	if (get_frame1)  delete[] get_frame1;
	if (oversample) delete[] oversample;
	if (result) delete[] result;

	/** disable fft need some fix for work prop **/
	/*
	  fftw_destroy_plan(p);
	  fftw_destroy_plan(p1);
	  fftw_destroy_plan(pf);
	  fftw_free(fftin);
	  fftw_free(fftout);
	  fftw_free(fftin1);
	  fftw_free(fftout1);
	  fftw_free(fftresult);
	*/

	initialized = false;
}

} /* end of gx_engine namespace */
