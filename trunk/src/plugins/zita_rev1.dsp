// this code is copied from faust effect.lib and
// some parameter texts and defaults changed

declare id "zita_rev1";
declare name "Zita Rev1";

import("filter.lib");

process(x,y) = component("effect.lib").zita_rev1_stereo(rdel,f1,f2,t60dc,t60m,fsmax,x,y)
	  : out_eq : dry_wet(x,y) : out_level
with {

  fsmax = 48000.0;  // highest sampling rate that will be used

  fdn_group(x) = hgroup(
    "zita_rev1[name:Zita_Rev1] [tooltip: ~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER ALLPASS-COMB REVERBERATOR (8x8). See Faust's effect.lib for documentation and references]", x);

  in_group(x) = fdn_group(hgroup("input[name:Input]", x));

  rdel = in_group(vslider("in_delay[name:In Delay] [unit:ms] [style:knob] 
                  [tooltip: Delay in ms before reverberation begins]",
                  60,20,100,1));

  freq_group(x) = fdn_group(hgroup("decay_times[name:Decay Times in Bands]", x));

  f1 = freq_group(vslider("lf_x[name:Freq X] [unit:Hz] [style:knob] 
       [tooltip: Crossover frequency (Hz) separating low and middle frequencies]",
       200, 50, 1000, 1));

  t60dc = freq_group(vslider("low_rt60[name:Low] [unit:s] [style:knob] 
          [style:knob] [tooltip: T60 = time (in seconds) to decay 60dB in low-frequency band]", 
	  3, 1, 8, 0.1));

  t60m = freq_group(vslider("mid_rt60[name:Mid] [unit:s] [style:knob]
          [tooltip: T60 = time (in seconds) to decay 60dB in middle band]", 
	  2, 1, 8, 0.1));

  f2 = freq_group(vslider("hf_damping[name:HF Damping] [unit:Hz] [style:knob]
       [tooltip: Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60]",
       6000, 1500, 0.49*fsmax, 1));

  out_eq = pareq_stereo(eq1f,eq1l,eq1q) : pareq_stereo(eq2f,eq2l,eq2q);
// Zolzer style peaking eq (not used in zita-rev1) (filter.lib):
// pareq_stereo(eqf,eql,Q) = peak_eq(eql,eqf,eqf/Q), peak_eq(eql,eqf,eqf/Q);
// Regalia-Mitra peaking eq with "Q" hard-wired near sqrt(g)/2 (filter.lib):
  pareq_stereo(eqf,eql,Q) = peak_eq_rm(eql,eqf,tpbt), peak_eq_rm(eql,eqf,tpbt)
  with {
    tpbt = wcT/sqrt(g); // tan(PI*B/SR) where B bandwidth in Hz (Q^2 ~ g/4)
    wcT = 2*PI*eqf/SR;  // peak frequency in rad/sample
    g = db2linear(eql); // peak gain
  };

  eq1_group(x) = fdn_group(hgroup("equalizer1[name:RM Peaking Equalizer 1]", x));

  eq1f = eq1_group(vslider("eq1_freq[name:Freq] [unit:Hz] [style:knob]
       [tooltip: Center-frequency of second-order Regalia-Mitra peaking equalizer section 1]",
       315, 40, 2500, 1));
  
  eq1l = eq1_group(vslider("eq1_level[name:Level] [unit:dB] [style:knob]
       [tooltip: Peak level in dB of second-order Regalia-Mitra peaking equalizer section 1]",
       0, -15, 15, 0.1));
  
  eq1q = eq1_group(vslider("eq1_q[name:Q] [style:knob]
       [tooltip: Q = centerFrequency/bandwidth of second-order peaking equalizer section 1]",
       3, 0.1, 10, 0.1));
  
  eq2_group(x) = fdn_group(hgroup("equalizer2[name:RM Peaking Equalizer 2]", x));

  eq2f = eq2_group(vslider("eq2_freq[name:Freq] [unit:Hz] [style:knob]
       [tooltip: Center-frequency of second-order Regalia-Mitra peaking equalizer section 2]",
       315, 40, 2500, 1));
  
  eq2l = eq2_group(vslider("eq2_level[name:Level] [unit:dB] [style:knob]
       [tooltip: Peak level in dB of second-order Regalia-Mitra peaking equalizer section 2]",
       0, -15, 15, 0.1));

  eq2q = eq2_group(vslider("eq2_q[name:Q] [style:knob]
       [tooltip: Q = centerFrequency/bandwidth of second-order peaking equalizer section 2]",
       3, 0.1, 10, 0.1));
  
  out_group(x)  = fdn_group(hgroup("output[name:Output]", x));

  dry_wet(x,y) = *(wet) + dry*x, *(wet) + dry*y with { 
    wet = 0.5*(drywet+1.0);
    dry = 1.0-wet; 
  };

  drywet = out_group(vslider("dry_wet_mix[name:Dry/Wet] [style:knob]
       [tooltip: -1 = dry, 1 = wet]",
       0, -1.0, 1.0, 0.01)) : smooth(0.999);

  out_level = *(gain),*(gain);

  gain = out_group(vslider("level[name:Level] [unit:dB] [style:knob]
    [tooltip: Output scale factor]", 0, -70, 40, 0.1)) 
    : smooth(0.999) : db2linear; 

};
