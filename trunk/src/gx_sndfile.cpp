/*
 * Copyright (C) 2009 Hermann Meyer and James Warden
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
 */

/**************************************************************
	gx_sndfile.cpp

***************************************************************/

// ------------ This is the gx_sdnfile namespace ---------------
// This namespace mainly wraps around sndfile's functions
// And has some native functionality

#include <cstring>
#include <list>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>


using namespace std;

#include <libgen.h>
#include <sndfile.h>
#include <jack/jack.h>
#include <gtk/gtk.h>
#include "guitarix.h"

using namespace gx_system;

namespace gx_sndfile 
{
  
  // --------------- sf_open writer wrapper : returns file desc. and audio file info
  SNDFILE* openOutputSoundFile(const char* name, int chans, int sr)
  {
    // initialise the SF_INFO structure
    SF_INFO info;

    info.samplerate = sr;
    info.channels   = chans;
    info.format     = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    return sf_open(name, SFM_WRITE, &info);
  }
  
  // --------------- sf_open reader wrapper : returns file desc. and audio file info
  SNDFILE* openInputSoundFile(const char* name, int* chans, int* sr, int* length)
  {
    SF_INFO info;
    SNDFILE *sf = sf_open(name, SFM_READ, &info);

    *sr     = info.samplerate;
    *chans  = info.channels;
    *length = info.frames;

    return sf;
  }

  // --------------- sf_writer wrapper 
  sf_count_t writeSoundOutput(SNDFILE *pOutput, float *buffer, int vecsize)
  {
    return sf_writef_float(pOutput, buffer, vecsize);
  }
  
  // --------------- sf_reader wrapper 
  sf_count_t readSoundInput(SNDFILE *pInput, float *buffer, int vecsize)
  {
    return sf_readf_float(pInput, buffer, vecsize);
  }

  // --------------- audio resampler
  GxResampleStatus resampleSoundFile(const char*  pInputi, 
				     const char*  pOutputi, 
				     int jackframe)
  {
    int chans, length=0, length2=0, sr;
    GxResampleStatus status = kNoError;

    // Note: what is length used for ? only length2 used

    // --- open audio files
    SNDFILE* pInput  = openInputSoundFile (pInputi,  &chans, &sr, &length2);
    SNDFILE* pOutput = openOutputSoundFile(pOutputi, chans, jackframe);

    // check input
    if (!pInput)
    {
      ostringstream msg;
      msg << "Error opening input file " << pInputi;
      (void)gx_gui::gx_message_popup(msg.str().c_str());
      status = kErrorInput;
    }

    // check input
    else if (!pOutput)
    {
      ostringstream msg;
      msg << "Error opening output file " << pOutputi;
      (void)gx_gui::gx_message_popup(msg.str().c_str());
      status = kErrorOutput;
    }
    else
    {
      const int	vecsize=64;
      float* sig = new float[vecsize*2];
      int counter = 0;

      // note: what is the length variable doing ??
      while (counter < length+length2-1)
      {
	readSoundInput   (pInput,  sig, vecsize);
	writeSoundOutput (pOutput, sig, vecsize);
	counter += vecsize;
      }

      // close files
      sf_close(pInput);
      sf_close(pOutput);

      delete[] sig;
      
      ostringstream lab;
      lab << "fileinfo: " << endl
	  << chans        << " channel(s) "
	  << jackframe    << " Sample rate "
	  << length2      << " Frames ";

      gtk_label_set_text(GTK_LABEL(gx_gui::label1), lab.str().c_str());
    }

    return status;
  }

  // --------------- sf_close wrapper 
  void closeSoundFile(SNDFILE *psf_in)
  {
    sf_close(psf_in);
  }
} /* end of gx_sndfile namespace */
