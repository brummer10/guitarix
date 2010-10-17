declare name 		"phaser";
declare license 	"BSD";


import("effect.lib");
import("osc.lib");

phaser_mono(dmax,curdel,depth,fb,invert)
  = _ <: _, _': _, _'
  : _, _': _, _': _, _': _, (-:fdelay(dmax,curdel)) ~ *(fb)
  : _, *(select2(invert,depth,0-depth)) : + : *(0.5);
  
phaser_stereo(dmax,curdel1,curdel2,depth,fb,invert)
  =  phaser_mono(dmax,curdel1,depth,fb,invert),
     phaser_mono(dmax,curdel2,depth,fb,invert); 

phaser_stereogx = *(level),*(level) : phaser_stereo(dmax,curdel1,curdel2,depth,fb,invert)
with {
  lfol = component("osc.lib").oscrs; // sine for left channel
  lfor = component("osc.lib").oscrc; // cosine for right channel
  dmax = 2048;
  dflange = 0.001 * SR * hslider("delay [unit:ms]", 10, 0, 20, 0.01);
  odflange = 0.001 * SR * hslider("delay offset [unit:ms]", 1, 0, 20, 0.01);
  freq	 = hslider("LFO freq [unit:Hz]", 0.2, 0, 5, 0.01);
  depth	 = hslider("depth", 1, 0, 1, 0.01);
  fb	 = hslider("feedback gain", 0, 0, 1, 0.01);
  invert   = checkbox("invert[enum:linear|invert]");
  level	 = hslider("level [unit:dB]", 0, -60, 10, 0.1) : db2linear;
  curdel1 = odflange+dflange*(1 + lfol(freq))/2; 
  curdel2 = odflange+dflange*(1 + lfor(freq))/2; 
};

process = phaser_stereogx;
