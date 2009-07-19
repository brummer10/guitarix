declare name 		"emptty";
declare version 	"0.01";
declare author 		"brummer";
declare license 	"BSD";
declare copyright 	"(c)brummer 2008";

import("math.lib");
import("music.lib");
import("effect.lib"); 
import("filter.lib");


//-resonator
resonator(d,a) 	= (+ <: (delay(4096, d-1) + delay(4096, d))/2.0)~*(1.0-a) ;
d 		= vslider("vibrato", 0.5, 0, 1, 0.01);
a 		= vslider("trigger", 0.12, 0, 1, 0.01);
reso = vgroup("resonans", resonator(d,a));

process 	= reso;
