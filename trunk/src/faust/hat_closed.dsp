ml = library("music.lib");
ol = library("oscillator.lib");
fl = library("filter.lib");

// Port from SuperCollider (SC) to Faust of SynthDef \SOShat in 
// <SuperCollider>/examples/demonstrations/DrumSynths.scd
// e.g., /usr/local/share/SuperCollider/examples/demonstrations/DrumSynths.scd
// on Linux
// based on a Sound-on-Sound 'synth secrets' tutorial:
// http://www.soundonsound.com/sos/Jun02/articles/synthsecrets0602.asp

//https://github.com/josmithiii/faust-jos/tree/master/percussion

pi = ml.PI;

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

bpf(freq, rq) = fl.tf2(1.0,0,-1.0,-2.0*R*cos(theta),R^2) with {
  theta = 2.0*pi*freq/ml.SR;
  R = -pi*freq*rq/ml.SR;
};
pulse0p5(freq) = ol.square(freq); // phase 0, duty cycle 0.5

gate = checkbox("gate [nomidi:no][alias]");

ampdb  = vslider("Gain [tooltip: Volume level in decibels]",-20,-60,40,0.1);
amp = ampdb : fl.smooth(0.999) : ml.db2linear;

freq = 1600.0; 
sustain = 0.01; 

//freq = 6000; // orig value
// sustain = 0.1; // orig value

trigger = gate > gate';

root_cymbal_square = pulse0p5(freq);
root_cymbal = root_cymbal_square <: 
    pmosc(freq*1.34, 310.0/1.3) + 
    pmosc(freq*2.405, 26.0/0.5) +
    pmosc(freq*3.09, 11.0/3.4) + 
    pmosc(freq*1.309, 0.72772);
initial_bpf_contour = line(15000, 9000, 0.1, trigger);
initial_env = perc(0.005, 0.1, trigger);
initial_bpf = root_cymbal : bpf(initial_bpf_contour,1.0) * initial_env;

body_env = sqrt(perc(0.005, sustain, trigger)); 
body_hpf = root_cymbal : hpf(line(9000, 12000, sustain, trigger)) 
	 * body_env;
cymbal_mix = (initial_bpf + body_hpf) * amp;

process = cymbal_mix;






