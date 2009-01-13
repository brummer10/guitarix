
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

