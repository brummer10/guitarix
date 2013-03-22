declare name "Chorus Mono";
declare category "Modulation";

declare author "Albert Graef";
declare version "1.0";

import("music.lib");

level	= hslider("level", 0.5, 0, 1, 0.01);
freq	= hslider("freq", 2, 0, 10, 0.01);
dtime	= 0.02 ;//hslider("delay", 0.02, 0, 0.2, 0.01);

depth	= 0.02 ;//hslider("depth", 0.02, 0, 1, 0.01);
wet = vslider("wet_dry[name:wet/dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;

process			= _<:*(dry),(*(wet): component("chorus.dsp").chorus(dtime,freq,depth,0)):>_;
