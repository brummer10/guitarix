ml = library("music.lib");
fl = library("filter.lib");
ol = library("oscillator.lib");

// Port from SuperCollider (SC) to Faust of SOSkick in 
// <SuperCollider>/examples/demonstrations/DrumSynths.scd
// based on a Sound-on-Sound 'synth secrets' tutorial:
// http://www.soundonsound.com/sos/jan02/articles/synthsecrets0102.asp

//https://github.com/josmithiii/faust-jos/tree/master/percussion

decay(n,x) = x - (x>0.0)/n;
release(n) = + ~ decay(n);
envgate(dur,trigger) = trigger : release(int(dur*float(ml.SR))) : >(0.0);

perc(att,rel,trigger) = ml.adsr(att,0,1.0,rel,envgate(att,trigger));
pmosc(carfreq,modfreq,index) = ol.oscrs(carfreq + (index*modfreq)
			     * ol.oscrs(modfreq));

line(start,end,dur,trigger) = trigger : release(int(dur*float(ml.SR))) 
		    : *(start-end)+end;
		    
lpf(freq) = fl.lowpass(3,freq);
hpf(freq) = fl.highpass(3,freq);

gate = checkbox(" gate [nomidi:no][alias]");
ampdb  = vslider("Gain [tooltip: Volume level in decibels]",-20,-60,40,0.1);
amp = ampdb : fl.smooth(0.999) : ml.db2linear;
freq = 50;
mod_freq = 5.0;
mod_index = 5.0;
sustain = 0.4;
beater_noise_level = 0.03;

trigger = gate>gate';
pitch_contour = line(freq*2, freq, 0.02, trigger);
drum_osc = pmosc(pitch_contour, mod_freq, mod_index/1.3);
drum_lpf = drum_osc : lpf(1000);
drum_env = drum_lpf * perc(0.005,sustain,trigger);

beater_source = ml.noise * beater_noise_level;
beater_hpf = beater_source : hpf(500);
lpf_cutoff_contour = line(6000, 500, 0.03, trigger);
beater_lpf = beater_hpf : lpf(lpf_cutoff_contour);
beater_env = beater_lpf * perc(0.01, 1.0, trigger);
kick_mix = (drum_env + beater_env) * 2 * amp;

process = kick_mix;






