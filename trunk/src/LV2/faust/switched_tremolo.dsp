//------------------------------------
//Inspired by:Line 6 POD-3
//Found this effect somewhere here
//------------------------------------

//------------------------------------
//Description:
//The modulated signal got using 4 oscillations,
//which are switched.
//
//Parameters description:
//steps - number of oscillators in bank
//sw_freq - oscillators switching freq
//freq0..4 - oscillators freqs
//depth - as is
//------------------------------------

import("stdfaust.lib");

steps = hslider("Steps", 4, 1, 4, 1);
sw_freq = hslider("Switch Freq", 1, 0.25, 5, 0.25);
freq0 = hslider("Freq 0", 1, 0.25, 15, 0.5);
freq1 = hslider("Freq 1", 1, 0.25, 15, 0.5);
freq2 = hslider("Freq 2", 1, 0.25, 15, 0.5);
freq3 = hslider("Freq 3", 1, 0.25, 15, 0.5);
depth = hslider("Depth", 0.5, 0, 1, 0.05);

wet = vslider("wet_dry[name:wet/dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;

in_range(min_val, max_val, x) = x>min_val,x<=max_val:*:_;

N = 4;
freqs = (freq0, freq1, freq2, freq3);
process = _<:*(dry),(*(wet):(par(i,N,os.osc(ba.take(i+1,freqs))),
	(os.lf_sawpos(sw_freq)<:par(i,N,in_range(i/steps,(i+1)/steps):
	si.smooth(ba.tau2pole(0.05))))),_:
	(si.dot(N):_*depth:_+1:_-depth),_:_*_:_):>_;
