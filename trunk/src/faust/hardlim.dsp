declare id "hardlim";
declare name "?limiter";
//declare category "Guitar Effects";

import("stdfaust.lib");
import("guitarix.lib");
rd = library("reducemaps.lib");

//------------------------------------------------------------------------
// Lookahead compressor with an meter attachment point.
//
// This is a modification of Dario Sanfilippo's co.limiter_lad_N in the
// faust library compressors.dsp.
//------------------------------------------------------------------------
limiter_lad_with_meter_N(N, LD, ceiling, attack, hold, release, meter) = 
      si.bus(N) <: par(i, N, @(LD * ma.SR)), 
                   (scaling : meter <: si.bus(N)) : ro.interleave(N, 2) :
                   par(i, N, *) with {
  scaling = ceiling / max(amp_profile, ma.EPSILON) : min(1);
  amp_profile = par(i, N, abs) : maxN(N) : ba.peakholder(hold * ma.SR) :
  att_smooth(attack) : rel_smooth(release);
  att_smooth(time, in) = si.smooth(ba.tau2pole(time), in);
  rel_smooth(time, in) = an.peak_envelope(time, in);
  maxN(1) = _;
  maxN(2) = max;
  maxN(N) = max(maxN(N - 1));
};


//------------------------------------------------------------------------
// The limiter/clipper used by the main guitarix amp.
//
// The clipper is necessary beacuse the limiter does not completely
// eliminate peaks above its ceiling. See Geraint Luff's exellent
// writeup about this class of device at:
//      https://signalsmith-audio.co.uk/writing/2022/limiter/
//------------------------------------------------------------------------
master_limiter(min_freq) = limiter : stereo_clipper with {
  // ::: Limiter :::
  // Values selected for a colorless limiter according the discussion
  // in the "Lookahead Limiters" section of:
  //     https://faustlibraries.grame.fr/libs/compressors/
  limiter = limiter_lad_with_meter_N(2,lim_lookahead,lim_ceiling,
                                     lim_attack,lim_hold,lim_release,
                                     vmeter1);

  // attack and release smoothed by one pole filters.  A paramater of
  // tau/twopi creates a smoother will reach 1-exp(-2*pi) of its peak
  // in tau seconds.
  //
  // hold is explicitly a time, later rounded to the nearest sample.
  twopi = 2 * ma.PI;
  lim_attack = 1.0/min_freq/twopi;
  lim_hold = 1.0/min_freq;
  lim_release = (0.5 - lim_hold)/twopi;

  // The lookahead also adds latency necessary to align the limiter
  // amplitude follower with the input signal.
  lim_lookahead = lim_attack;   

  // ::: Clipper ::
  // Leave room for an occasional peak overshooting the limiter
  lim_ceiling = ba.db2linear(-2.0);   // below 0.0dB
  // This is where soft clipping will start
  clip_ceiling = ba.db2linear(-1.0);  // below 0.0dB

  softclip(th,x) = softsat(preclip(x)) with {
    // The softsat function will map [-cth,cth] to [-1,1], but outside of that input range
    // it is not well behaved.  So, hard clip to the valid input range first.
    preclip(x) = aa.clip(-cth,cth,x);
    // Defines a transfer function with linearly decaying derivative ouside of [-th,th]
    softsat(x) = ba.if(ax<=th,x,ma.signum(x)*((cth-(ax+th)/2.0)*(ax-th)/2.0/(1.0-th) + th));
    cth = 2-th;                
    ax=abs(x);
  };
  clip(x) = softclip(clip_ceiling,x);
  stereo_clipper(x,y) = clip(x),clip(y);

  // ::: Meter :::
  vmeter1(x) = attach(x, envelop(1.0-x) :
                      vbargraph("v1[nomidi][tooltip:Rack output Limiter]", 0.0, 1.0));
  envelop    = abs : max ~ (1.0/ma.SR) : rd.maxn(1024); 
};

// Limiter latency should be minimized to avoid coloring the signal.
// However, if the attack time is faster than a cycle of the minimum
// imput signal, then the amplitude follower in the limiter will be
// changing over the period of a single cycle leading, to an unpleasant
// AM modulation.
//
// The minimum frequency typically perceived as a tone is 15 Hz.  So,
// this is a safe lower bound for frequency content.  At 15 Hz
// frequency, the limiter latency is about 10.6ms.
min_perceptible_freq = 15.0;

// If there is some guaranteed lower bound on the frequency content,
// and it is greater than min_perceptible_freq.  It can be set here
// and used to improve latency.  For example, 25 Hz (6.4ms) is below
// the lowest note on a piano and also below the lowest note on a
// 5-string bass guitar, and 50 Hz (3.2ms) is below most drop tunings
// on a guitar and also below an low B string on a 7-string.  For a
// guitar is standard tuning 75 Hz (2.1ms) might work.
//
// Real instruments will find a way to generate lower content by
// various mechanical and electrical intermodulations.  Unless lower
// frequencies are actually filtered out, higher freqency setting
// might not work.
min_input_freq = 0.0;

// The higher minimum the frequency, the lower the latency.
min_freq=max(min_input_freq,min_perceptible_freq);

process = master_limiter(min_freq);

