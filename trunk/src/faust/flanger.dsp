declare id 		"flanger";
declare name            "Flanger";
declare license 	"BSD";

import("effect.lib");
import("guitarix.lib");
import("osc.lib");

flangerstereogx = *(level),*(level) : flangerstereoN(dmax,curdel1,curdel2,depth,fb,invert) // change to flanger_stereo for faust >= 0.9.27
with {
  lfol = component("osc.lib").oscrs; // sine for left channel
  lfor = component("osc.lib").oscrc; // cosine for right channel
  dmax = 2048;
  dflange = 0.001 * SR * hslider("flange delay [unit:ms]", 10, 0, 20, 0.01);
  odflange = 0.001 * SR * hslider("flange delay offset [unit:ms]", 1, 0, 20, 0.01);
  freq	 = hslider("LFO freq [unit:Hz]", 0.2, 0, 5, 0.01);
  depth	 = hslider("depth", 1, 0, 1, 0.01);
  fb	 = hslider("feedback gain", 0, 0, 1, 0.01);
  invert   = checkbox("invert[enum:linear|invert]");
  level	 = hslider("level [unit:dB]", 0, -60, 10, 0.1) : db2linear;
  curdel1 = odflange+dflange*(1 + lfol(freq))/2; 
  curdel2 = odflange+dflange*(1 + lfor(freq))/2; 
};

process = flangerstereogx;
