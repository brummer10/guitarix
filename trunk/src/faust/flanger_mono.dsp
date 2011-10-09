declare name            "Flanger Mono";
declare id 		"flanger_mono";
declare license 	"BSD";

import("effect.lib");
import("guitarix.lib");
import("oscillator.lib");

flangermono(curdel)
  = _<: _, (-:fdelay(2048,curdel)) ~ *(0.5) : _, 
  *(-1) : + : *(0.5);
  

flangermonogx = *(level):flangermono(curdel)
with {
	  lfol = component("oscillator.lib").oscrs; 
	  dflange = 0.001 * SR *  10.0;
	  odflange = 0.001 * SR *  1.0;
	  freq	 = hslider("freq [unit:Hz]", 0.2, 0, 5, 0.01);
	  level	 = hslider("level [unit:dB]", 0, -60, 10, 0.1) : db2linear;
	  curdel = odflange+dflange*(1 + lfol(freq))/2; 
  };
  
wet = vslider("wet_dry[name:wet/dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;
  
process =  _<:*(dry),(*(wet): flangermonogx ):>_;
