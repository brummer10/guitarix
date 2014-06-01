import("music.lib");
import("effect.lib");
import("filter.lib");

//------------------------------- par_ps --------------------------------------
// Wariable delay lines based pitch shifter with parametric controller. 
// Pitch shifter implementation borrowed from faust examples : pitch_shifter.dsp 
// Paramertric conroller represented by oscillator with frequency dependent of
// envelope of input signal.
//
// USAGE:
//   _:par_ps(shift, envelope, control, freq, depth, dry_wet):_
//
// WHERE:
//   shift = frequency shifting (semitones)
//   envelope  = amplitude-envelope time-constant (sec) going down
//   control   = envelope follower to pitch shifter influence coefficient (0..1)
//   freq  = oscillator frequency in Hz
//   depth = oscillator amplitude
//   dry_wet = mix processed and input signals
//
// DEPENDENCIES:
//   effect.lib (amp_follower)
//   music.lib  (fdelay1s)

par_ps(shift, envelope, control, freq, depth, dry_wet) = 
	_<:_,(_<:
	parametric_controller(control, envelope, freq, depth)*shift,_:
	transpose(c_samples,c_xfade)):mixer(dry_wet)
with {
	c_samples = 2048;
	c_xfade   = 1024;
	c_folower_colibration = 6;

	parametric_controller(mix, envelope_t, freq, depth) = 
		(amp_follower(envelope_t):_*c_folower_colibration:
		_*depth,osc(freq)*0.5:_,_*depth):mixer(mix):_+0.5;
	
	transpose (w, x, s, sig)  =
		fdelay1s(d,sig)*fmin(d/x,1) + fdelay1s(d+w,sig)*(1-fmin(d/x,1))
		   	with {
				i = 1 - pow(2, s/12);
				d = i : (+ : +(w) : fmod(_,w)) ~ _;
			    };
	        
    mixer(mix) = _*(1 - mix),_*mix:>_; 
};

//------------------------------- shimmizita_rev_fdn -------------------------------
// Modifiend version of zita FDN reverb. The parametric pitch shifters bank
// embedded into it. 
//
// USAGE:
//   bus(8) : shimmizita_rev_fdn(f1,f2,t60dc,t60m, mode, shift,envelope,control,freq,depth,dry_wet, fsmax) : bus(8)
//
// WHERE
//   f1    = crossover frequency (Hz) separating dc and midrange frequencies
//   f2    = frequency (Hz) above f1 where T60 = t60m/2 (see below)
//   t60dc = desired decay time (t60) at frequency 0 (sec)
//   t60m  = desired decay time (t60) at midrange frequencies (sec)
//   mode   = correlation between pithch shift.
//   shift    = -- 
//   envelope =   |
//   control  =    See par_ps implementation above.
//   freq     =   |
//   depth    =   |
//   dry_wet  = --
//   fsmax = maximum sampling rate to be used (Hz)
//
// REFERENCES from zita:
//   http://www.kokkinizita.net/linuxaudio/zita-rev1-doc/quickguide.html
//   https://ccrma.stanford.edu/~jos/pasp/Zita_Rev1.html
//
// DEPENDENCIES:
//   filter.lib (allpass_comb, lowpass, smooth)
//   math.lib (hadamard, take, etc.)

shimmizita_rev_fdn(f1,f2,t60dc,t60m, mode, shift,envelope,control,freq,depth,dry_wet, fsmax) =
  ((bus(2*N) :> allpass_combs(N) : feedbackmatrix(N)) ~
   (delayfilters(N,freqs,durs) : pitchshifters(N) : fbdelaylines(N)))
with {
  N = 8;

  // Delay-line lengths in seconds:
  apdelays = (0.020346, 0.024421, 0.031604, 0.027333, 0.022904,
              0.029291, 0.013458, 0.019123); // feedforward delays in seconds
  tdelays = ( 0.153129, 0.210389, 0.127837, 0.256891, 0.174713,
              0.192303, 0.125000, 0.219991); // total delays in seconds
  tdelay(i) = floor(0.5 + SR*take(i+1,tdelays)); // samples
  apdelay(i) = floor(0.5 + SR*take(i+1,apdelays));
  fbdelay(i) = tdelay(i) - apdelay(i);
  // NOTE: Since SR is not bounded at compile time, we can't use it to
  // allocate delay lines; hence, the fsmax parameter:
  tdelaymaxfs(i) = floor(0.5 + fsmax*take(i+1,tdelays));
  apdelaymaxfs(i) = floor(0.5 + fsmax*take(i+1,apdelays));
  fbdelaymaxfs(i) = tdelaymaxfs(i) - apdelaymaxfs(i);
  nextpow2(x) = ceil(log(x)/log(2.0));
  maxapdelay(i) = int(2.0^max(1.0,nextpow2(apdelaymaxfs(i))));
  maxfbdelay(i) = int(2.0^max(1.0,nextpow2(fbdelaymaxfs(i))));

  apcoeff(i) = select2(i&1,0.6,-0.6);  // allpass comb-filter coefficient
  allpass_combs(N) =
    par(i,N,(allpass_comb(maxapdelay(i),apdelay(i),apcoeff(i)))); // filter.lib
  fbdelaylines(N) = par(i,N,(delay(maxfbdelay(i),(fbdelay(i)))));
  
  //Pitch shifters bank
  shiftcoefs_m1 = (1/2,1/3,1/2,1/4,1/2,1/8,1/2,1/3);
  shiftcoefs_m2 = (1/5,-1/2,1/3,-1/2,1/6,-1/3,1/3,1/2);
  shiftdunc(i, shift, mode) = mode<:_>=0,_<0:((_*(shift+shift*mode*take(i+1,shiftcoefs_m1))),(_*(shift+shift*mode*take(i+1,shiftcoefs_m2)))):>_;
  pitchshifters(N) = par(i, N, (_:par_ps(shiftdunc(i, shift, mode), envelope, control, freq, depth, dry_wet):_));
  
  freqs = (f1,f2); durs = (t60dc,t60m);
  delayfilters(N,freqs,durs) = par(i,N,filter(i,freqs,durs));
  feedbackmatrix(N) = hadamard(N); // math.lib

  staynormal = 10.0^(-20); // let signals decay well below LSB, but not to zero

  special_lowpass(g,f) = smooth(p) with {
    // unity-dc-gain lowpass needs gain g at frequency f => quadratic formula:
    p = mbo2 - sqrt(max(0,mbo2*mbo2 - 1.0)); // other solution is unstable
    mbo2 = (1.0 - gs*c)/(1.0 - gs); // NOTE: must ensure |g|<1 (t60m finite)
    gs = g*g;
    c = cos(2.0*PI*f/float(SR));
  };

  filter(i,freqs,durs) = lowshelf_lowpass(i)/sqrt(float(N))+staynormal
  with {
    lowshelf_lowpass(i) = gM*low_shelf1_l(g0/gM,f(1)):special_lowpass(gM,f(2));
    low_shelf1_l(G0,fx,x) = x + (G0-1)*lowpass(1,fx,x); // filter.lib
    g0 = g(0,i);
    gM = g(1,i);
    f(k) = take(k,freqs);
    dur(j) = take(j+1,durs);
    n60(j) = dur(j)*SR; // decay time in samples
    g(j,i) = exp(-3.0*log(10.0)*tdelay(i)/n60(j));
  };
};

// Stereo input delay used by zita_rev1 in both stereo and ambisonics mode:
shimmizita_in_delay(rdel) = zita_delay_mono(rdel), zita_delay_mono(rdel) with {
  zita_delay_mono(rdel) = delay(8192,SR*rdel*0.001) * 0.3;
};

// Stereo input mapping used by zita_rev1 in both stereo and ambisonics mode:
shimmizita_distrib2(N) = _,_ <: fanflip(N) with {
   fanflip(4) = _,_,*(-1),*(-1);
   fanflip(N) = fanflip(N/2),fanflip(N/2);
};




