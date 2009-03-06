
// ***** BEATDETECTOR.cpp *****
/******************************************************************************
part of guitarix, found at ttp://www.musicdsp.org/archive.php?classid=2#200 
postet by DSPMaster[at]free[dot]fr
modified for guitarix by hermann meyer
******************************************************************************/

#include "./guitarix/BEATDETECTOR.h"
//#include "math.h"

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
  setSampleRate(jackframe);
}

TBeatDetector::~TBeatDetector()
{
  // Nothing specific to do...
}

void TBeatDetector::setSampleRate (float sampleRate)
// Compute all sample frequency related coeffs
{
  KBeatFilter=1.0/(sampleRate*T_FILTER);
  BeatRelease=(float)exp(-1.0f/(sampleRate*BEAT_RTIME));
}

void TBeatDetector::AudioProcess (float input, float triggerpoint)
// Process incoming signal
{
  float EnvIn;
  // Step 1 : Compute all sample frequency related coeffs
  KBeatFilter=1.0/(jackframe*T_FILTER);
  BeatRelease=(float)exp(-1.0f/(jackframe*BEAT_RTIME));
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
    if (PeakEnv<triggerpoint/1.1) BeatTrigger=false;   // 0.015
  }

  // Step 5 : rising edge detector
  BeatPulse=false;
  if ((BeatTrigger)&&(!PrevBeatPulse))
    BeatPulse=true;
  PrevBeatPulse=BeatTrigger;
}

