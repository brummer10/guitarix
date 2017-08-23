ml = library("music.lib");
ol = library("oscillator.lib");
fl = library("filter.lib");

// Port from SuperCollider (SC) to Faust of SynthDef \SOStom in 
// <SuperCollider>/examples/demonstrations/DrumSynths.scd
// e.g., /usr/local/share/SuperCollider/examples/demonstrations/DrumSynths.scd
// based on a Sound-on-Sound 'synth secrets' tutorial:
// http://www.soundonsound.com/sos/Mar02/articles/synthsecrets0302.asp

// SOStom -------
// http://www.soundonsound.com/sos/Mar02/articles/synthsecrets0302.asp

//https://github.com/josmithiii/faust-jos/tree/master/percussion

gate = checkbox("gate [nomidi:no][alias]");
trigger = gate > gate';

ampdb  = vslider("Gain [tooltip: Volume level in decibels]",-20,-60,40,0.1);
amp = ampdb : fl.smooth(0.999) : ml.db2linear;

freq = 90;
sustain = 0.4;
drum_timbre = 1.0;
drum_mode_level = 0.25;

decay(n,x) = x - (x>0.0)/n;
release(n) = + ~ decay(n);
envgate(dur,trigger) = trigger : release(int(dur*float(ml.SR))) : >(0.0);

perc(att,rel,trigger) = ml.adsr(att,0,1.0,rel,envgate(att,trigger));
sinosc0(freq) = ol.oscrs(freq); // SinOsc at phase zero
pmosc(carfreq,modfreq,index) = ol.oscrs(carfreq + (index*modfreq)
			     * ol.oscrs(modfreq));

drum_mode_env = perc(0.005, sustain, trigger);
drum_mode_sin_1 = sinosc0(freq*0.8) * drum_mode_env * 0.5;
drum_mode_sin_2 = sinosc0(freq) * drum_mode_env * 0.5;
drum_mode_pmosc = pmosc(ol.saw2(freq*0.9), freq*0.85, drum_timbre/1.3)
		  * drum_mode_env * 5;
drum_mode_mix = (drum_mode_sin_1 + drum_mode_sin_2 + drum_mode_pmosc)
	      * drum_mode_level;
stick_env = perc(0.005, 0.01, trigger) * 3;
tom_mix = (drum_mode_mix + stick_env) * 2 * amp;

process = tom_mix;


