declare id 		"flanger_mono";
declare name            "Flanger Mono";
declare category        "Modulation";
declare license 	"BSD";

import("stdfaust.lib");
import("guitarix.lib");

flangermono(curdel)
  = _<: _, (-:de.fdelay(2048,curdel)) ~ *(0.5) : _, 
  *(-1) : + : *(0.5);
  

flangermonogx = *(level):flangermono(curdel)
with {
	  lfol = os.oscrs; 
	  dflange = 0.001 * ma.SR *  10.0;
	  odflange = 0.001 * ma.SR *  1.0;
	  //freq	 = hslider("freq [unit:Hz]", 0.2, 0, 5, 0.01);
      freq   = hslider("lfobpm[name:BPM][unit:bpm][tooltip:LFO in Beats per Minute]",24,24,360,1)/60;
	  level	 = hslider("level[name:Level][unit:dB]", 0, -60, 10, 0.1) : ba.db2linear;
	  curdel = odflange+dflange*(1 + lfol(freq))/2; 
  };
  
wet = vslider("wet_dry[name:Wet/Dry][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;
  
process =  _<:*(dry),(*(wet): flangermonogx ):>_;
