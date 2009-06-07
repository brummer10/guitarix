/*
  * Copyright (C) 2009 Hermann Meyer
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

// ***** BEATDETECTOR.h *****
/******************************************************************************
part of guitarix, found at ttp://www.musicdsp.org/archive.php?classid=2#200
postet by DSPMaster[at]free[dot]fr
modified for guitarix by hermann meyer
******************************************************************************/

#ifndef BeatDetectorH
#define BeatDetectorH

class TBeatDetector
{
private:
    float KBeatFilter;        // Filter coefficient
    float Filter1Out, Filter2Out;
    float BeatRelease;        // Release time coefficient
    float PeakEnv;            // Peak enveloppe follower
    bool BeatTrigger;         // Schmitt trigger output
    bool PrevBeatPulse;       // Rising edge memory
public:
    bool BeatPulse;           // Beat detector output

    TBeatDetector();
    ~TBeatDetector();
    virtual void setSampleRate(float SampleRate);
    virtual void AudioProcess (float input, float triggerpoint);
};
#endif

