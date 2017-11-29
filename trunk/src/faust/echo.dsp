declare name "Echo";
declare category "Echo / Delay";

declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("stdfaust.lib");

//t = vslider("time", 1, 1, 2000, 1);
t       = ba.tempo(hslider("bpm[name:BPM][tooltip:Echo in Beats per Minute]",120,24,360,1));
release = vslider("percent[name:Percent]", 0, 0,  100, 0.1)/100.0 : si.smooth(0.999);
N       = int( 2^19);
interp  = 100*ba.millisec;
echo1   = +~(de.sdelay(N, interp, int(t)-1) * (release));
process = echo1;
