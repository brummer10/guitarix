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

/* ------- This is the guitarix convolution Engine  ------- */

#pragma once

#include <zita-convolver.h>
#include <gxwmm/gainline.h>

namespace gx_engine
{

/* GxConvolver */

class Audiofile
{
public:

	enum {
		TYPE_OTHER,
		TYPE_CAF,
		TYPE_WAV,
		TYPE_AMB
	};

	enum {
		FORM_OTHER,
		FORM_16BIT,
		FORM_24BIT,
		FORM_32BIT,
		FORM_FLOAT
	};

	enum {
		ERR_NONE    = 0,
		ERR_MODE    = -1,
		ERR_TYPE    = -2,
		ERR_FORM    = -3,
		ERR_OPEN    = -4,
		ERR_SEEK    = -5,
		ERR_DATA    = -6,
		ERR_READ    = -7,
		ERR_WRITE   = -8
	};

	Audiofile (void);
	~Audiofile (void);

	//int mode(void) const { return _mode; }
	int type(void) const { return _type; }
	int form(void) const { return _form; }
	int rate(void) const { return _rate; }
	int chan(void) const { return _chan; }
	uint32_t size(void) const { return _size; }

	int open_read (string name);
	int close (void);

	int seek(uint32_t posit);
	int read(float *data, uint32_t frames);

private:

	void reset(void);

	SNDFILE  *_sndfile;
	int       _mode;
	int       _type;
	int       _form;
	int       _rate;
	int       _chan;
	uint32_t  _size;
};

class GxConvolverBase: protected Convproc
{
protected:
	volatile bool ready;
	void adjust_values(unsigned int audio_size, unsigned int& count, unsigned int& offset,
	                   unsigned int& delay, unsigned int& ldelay, unsigned int& length,
	                   unsigned int& size, unsigned int& bufsize);
	GxConvolverBase(): ready(false) {}
public:
	bool checkstate();
	void set_not_runnable() { ready = false; }
	bool is_runnable() { return ready; }
	bool start();
	void stop() { stop_process(); }
};

class GxConvolver: public GxConvolverBase
{
private:
	bool read_sndfile (Audiofile& audio, int nchan, int samplerate, const float *gain,
	                   unsigned int *delay, unsigned int offset, unsigned int length,
	                   const Gainline& points);
public:
	bool configure(
		unsigned int count, int samplerate, string fname, float gain, float lgain,
		unsigned int delay, unsigned int ldelay, unsigned int offset,
		unsigned int length, unsigned int size, unsigned int bufsize,
		const Gainline& gainline);
	bool compute(int count, float* input1, float *input2, float *output1, float *output2);
};

extern GxConvolver conv;

class GxSimpleConvolver: public GxConvolverBase
{
private:
public:
	bool configure(int count, float *impresp, unsigned int samplerate);
	bool compute(int count, float* input, float *output);
	bool compute(int count, float* buffer) { return is_runnable() ? compute(count, buffer, buffer) : true; }
};

extern GxSimpleConvolver cab_conv;
extern GxSimpleConvolver contrast_conv;
} /* end of gx_engine namespace */

