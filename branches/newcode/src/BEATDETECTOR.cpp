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
*/

// ***** BEATDETECTOR.cpp *****
/******************************************************************************
part of guitarix, found at ttp://www.musicdsp.org/archive.php?classid=2#200
postet by DSPMaster[at]free[dot]fr
modified for guitarix by hermann meyer
******************************************************************************/

#include <cmath>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include <sndfile.h>
#include <jack/jack.h>
#include <gtk/gtk.h>

#include "guitarix.h"

#include "BEATDETECTOR.h"

#define FREQ_LP_BEAT 150.0f    // Low Pass filter frequency
#define T_FILTER 1.0f/(2.0f*M_PI*FREQ_LP_BEAT)  // Low Pass filter time constant
#define BEAT_RTIME 0.02f  // Release time of enveloppe detector in second

TBeatDetector::TBeatDetector()
// Beat detector constructor
{
    Filter1Out=0.0;
    Filter2Out=0.0;
    PeakEnv=0.0;
    BeatTrigger=false;
    PrevBeatPulse=false;
    setSampleRate(gx_jack::jack_sr);
}

TBeatDetector::~TBeatDetector()
{
    // Nothing specific to do...
}

void TBeatDetector::setSampleRate (float sampleRate)
// Compute all sample frequency related coeffs
{
    // Step 1 : Compute all sample frequency related coeffs
    KBeatFilter=1.0/(sampleRate*T_FILTER);
    BeatRelease=(float)exp(-1.0f/(sampleRate*BEAT_RTIME));
}

void TBeatDetector::AudioProcess (float input, float triggerpoint)
// Process incoming signal
{
    float EnvIn;
    // Step 2 : 2nd order low pass filter (made of two 1st order RC filter)
    Filter1Out=Filter1Out+(KBeatFilter*(input-Filter1Out));
    Filter2Out=Filter2Out+(KBeatFilter*(Filter1Out-Filter2Out));

    // Step 3 : peak detector
    EnvIn=fabs(Filter2Out);
    if (EnvIn>PeakEnv) PeakEnv=EnvIn;  // Attack time = 0
    else
    {
        PeakEnv*=BeatRelease;
        PeakEnv+=(1.0f-BeatRelease)*EnvIn;
    }

    // Step 4 : Schmitt trigger
    if (!BeatTrigger)
    {
        if (PeakEnv>triggerpoint) BeatTrigger=true;    // 0.03
    }
    else
    {
        if (PeakEnv<triggerpoint*0.8) BeatTrigger=false;   // 0.015
    }

    // Step 5 : rising edge detector
    BeatPulse=false;
    if ((BeatTrigger)&&(!PrevBeatPulse))
        BeatPulse=true;
    PrevBeatPulse=BeatTrigger;
}

